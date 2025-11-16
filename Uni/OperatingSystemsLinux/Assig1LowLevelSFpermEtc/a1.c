#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <arpa/inet.h>


char* getPermission(mode_t mode) {
    static char permission[10];
    strcpy(permission, "---------");
    if (mode & S_IRUSR) permission[0] = 'r';
    if (mode & S_IWUSR) permission[1] = 'w';
    if (mode & S_IXUSR) permission[2] = 'x';
    if (mode & S_IRGRP) permission[3] = 'r';
    if (mode & S_IWGRP) permission[4] = 'w';
    if (mode & S_IXGRP) permission[5] = 'x';
    if (mode & S_IROTH) permission[6] = 'r';
    if (mode & S_IWOTH) permission[7] = 'w';
    if (mode & S_IXOTH) permission[8] = 'x';
    permission[9] = '\0';
    return permission;
}

void list(char *pathName, char *filtering_options, int recursive, int recursionStep) {
    struct stat fileMetaData;
    if (stat(pathName, &fileMetaData) < 0) {
        printf("ERROR\ninvalid directory path\n");
        return;
    }

    if (!S_ISDIR(fileMetaData.st_mode)) {
        printf("ERROR\ninvalid directory\n");
        return;
    }

    if(recursionStep == 0){
        printf("SUCCESS\n");
    }
    //printf("SUCCESS\n");

    DIR* dir = opendir(pathName);
    if (dir == NULL) {
        printf("ERROR\ncannot open directory\n");
        return;
    }

    struct dirent *dirEntry;
    struct stat inode;
    char name[512];

    while ((dirEntry = readdir(dir)) != NULL) {
        if (strcmp(dirEntry->d_name, ".") == 0 || strcmp(dirEntry->d_name, "..") == 0) {
            continue;
        }

        snprintf(name, sizeof(name), "%s/%s", pathName, dirEntry->d_name);

        if (lstat(name, &inode) < 0) {
            continue;
        }

        int printEntry = 1;
        if (filtering_options != NULL) {
            if (strncmp(filtering_options, "size_greater=", 13) == 0) {
                long int size_value = strtol(filtering_options + 13, NULL, 10);

                // if (S_ISREG(inode.st_mode) && inode.st_size < size_value) {
                //    printEntry = 0;     // mi se pare mai corect sa fac asa
                //}

                if (!S_ISREG(inode.st_mode)) {
                    printEntry = 0;
                } else if (inode.st_size <= size_value) {
                    printEntry = 0;
                }

            } else if (strncmp(filtering_options, "permissions=", 12) == 0) {
                char *perm_string = getPermission(inode.st_mode);
                //printf("permissions=%s\n", perm_string);
                if (strcmp(perm_string, filtering_options + 12) != 0) {
                    printEntry = 0;
                }
            }
        }

        if (printEntry) {
            printf("%s\n", name);
        }

        if (recursive && S_ISDIR(inode.st_mode)) {
            list(name, filtering_options, recursive, 1);
        }

    }

    closedir(dir);
}

void parse(char *pathName){
    char magic = 0;
    int fd;
    fd = open(pathName, O_RDONLY);

    if(fd < 0) {
        printf("ERROR\nwrong file\n");
        return;
    }

    if(read(fd, &magic, 1) != 1 || magic != 'I'){
        printf("ERROR\nwrong magic\n");
        close(fd);
        return;
    }

    unsigned short header_size = 0;
    if(read(fd, &header_size, 2) != 2){
        printf("ERROR\nwrong header read\n");
        close(fd);
        return;
    }

    unsigned short version = 0;
    if(read(fd, &version, 2) != 2 || version < 112 || version > 221){
        printf("ERROR\nwrong version\n");
        close(fd);
        return;
    }

    unsigned short no_of_sections = 0;
    if(read(fd, &no_of_sections, 1) != 1 || (no_of_sections != 2 && (no_of_sections < 7 || no_of_sections > 19))){
        printf("ERROR\nwrong sect_nr\n");
        close(fd);
        return;
    }

    char resultString[1000] = {0};
    char tempBuffer[100];

    for(int i = 0; i < no_of_sections; i++) {
        unsigned short sect_type = 0;
        char sect_name[7] = {0};
        unsigned int sect_size = 0;
        unsigned int sect_offset = 0;

        if (read(fd, sect_name, 6) != 6 || read(fd, &sect_type, 2) != 2 || read(fd, &sect_offset, 4) != 4 || read(fd, &sect_size, 4) != 4) {
            printf("ERROR\ninvalid file\n");
            close(fd);
            return;
        }

        unsigned short sect_type_values[3] = {47, 23, 83};
        if(sect_type != sect_type_values[0] && sect_type != sect_type_values[1] && sect_type != sect_type_values[2]) {
            printf("ERROR\nwrong sect_types\n");
            close(fd);
            return;
        }

        snprintf(tempBuffer, sizeof(tempBuffer), "section%d: %s %d %d\n", i + 1, sect_name, sect_type, sect_size);
        strncat(resultString, tempBuffer, sizeof(resultString) - strlen(resultString) - 1);
    }

    printf("SUCCESS\nversion=%d\nnr_sections=%d\n", version, no_of_sections);
    printf("%s", resultString);

    close(fd);
}

void extract(char *pathName, char *sectionNumber, char *lineNumber) {

    int fd = open(pathName, O_RDONLY);
    if (fd < 0) {
        printf("ERROR\nwrong file\n");
        return;
    }

    int sect_nr = atoi(sectionNumber);
    int line_num = atoi(lineNumber);

    lseek(fd, 6, SEEK_SET);
    for (int i = 0; i < sect_nr - 1; i++) {
        lseek(fd, 16, SEEK_CUR);
    }

    char sect_name[7] = {0};
    unsigned short sect_type;
    unsigned int sect_offset, sect_size;
    if (read(fd, sect_name, 6) != 6 ||
        read(fd, &sect_type, 2) != 2 ||
        read(fd, &sect_offset, 4) != 4 ||
        read(fd, &sect_size, 4) != 4) {
        printf("ERROR\ninvalid section\n");
        close(fd);
        return;
    }

    char *buffer = malloc(sect_size + 1);
    lseek(fd, sect_offset, SEEK_SET);
    if (read(fd, buffer, sect_size) != sect_size) {
        printf("ERROR\ninvalid section data\n");
        free(buffer);
        close(fd);
        return;
    }
    buffer[sect_size] = '\0';

    char *finalAdd[1024];
    int line_count = 0;
    char *filter = buffer;
    for (unsigned int i = 0; i < sect_size; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            finalAdd[line_count++] = filter;
            filter = &buffer[i+1];
        }
    }
    if (filter < buffer + sect_size) {
        finalAdd[line_count++] = filter;
    }


    if (line_num < 1 || line_num > line_count) {
        printf("ERROR\ninvalid line\n");
        free(buffer);
        close(fd);
        return;
    }

    char *line = finalAdd[line_count - line_num];

    int len = strlen(line);
    for (int i = 0; i < len/2; i++) {
        char tmp = line[i];
        line[i] = line[len-1-i];
        line[len-1-i] = tmp;
    }

    printf("SUCCESS\n%s\n", line);
    free(buffer);
    close(fd);
}

void findall(char *pathName, int recursionStep) {

    struct stat fileMetaData;
    if (stat(pathName, &fileMetaData) < 0) {
        printf("ERROR\ninvalid directory path\n");
        return;
    }

    if (!S_ISDIR(fileMetaData.st_mode)) {
        //printf("ERROR\ninvalid directory\n");
        return;
    }

    DIR* dir = opendir(pathName);
    if (dir == NULL) {
        printf("ERROR\ncannot open directory\n");
        return;
    }

    if (recursionStep == 0) {
        printf("SUCCESS\n");
    }

    struct dirent *dirEntry;
    char name[512];

    while ((dirEntry = readdir(dir)) != NULL) {
        if (strcmp(dirEntry->d_name, ".") == 0 || strcmp(dirEntry->d_name, "..") == 0) {
            continue;
        }

        strncpy(name, pathName, sizeof(name) - 1);
        strncat(name, "/", sizeof(name) - strlen(name) - 1);
        strncat(name, dirEntry->d_name, sizeof(name) - strlen(name) - 1);

        struct stat entryMetaData;
        if (stat(name, &entryMetaData) < 0) {
            continue;
        }

        int printEntry = 0;

        if (S_ISREG(entryMetaData.st_mode)) {
            int fdin = open(name, O_RDONLY);
            if (fdin < 0) {
                close(fdin);
                continue;
            }

            printEntry = 1;

            unsigned int offset = 5;
            lseek(fdin, offset, SEEK_SET);

            unsigned short nr_sections = 0;
            if (read(fdin, &nr_sections, 1) != 1) {
                close(fdin);
                continue;
            }

            offset = 18;
            lseek(fdin, offset, SEEK_SET);
            for(int i = 0; i < nr_sections; i++){
                unsigned int sect_size = 0;
                if(read(fdin, &sect_size, 4) != 4){
                    printf("ERROR\ninvalid file\n");
                    close(fdin);
                    closedir(dir);
                    return;
                }

                if(sect_size > 1466){
                    printEntry = 0;
                    close(fdin);
                    break;
                }

                offset = offset + 16;
                lseek(fdin, offset, SEEK_SET);

            }

            close(fdin);

        }

        if (printEntry) {
            printf("%s\n", name);
        }

        if (S_ISDIR(entryMetaData.st_mode)) {
            findall(name, 1);
        }
    }

    closedir(dir);
}

int main(int argc, char **argv) {
    if (argc >= 2) {
        if (strcmp(argv[0], "./a1") != 0) {
            printf("ERROR\nwrong program name\n");
            return 0;
        }

        if (strcmp(argv[1], "variant") == 0) {
            printf("92529\n");
        } else if (strcmp(argv[1], "parse") == 0) {
            char *pathName = argv[2] + 5;
            parse(pathName);
        } else if (strcmp(argv[1], "list") == 0) {
            int recursive = 0;
            char *pathName = NULL;
            char *filtering_options = NULL;

            for (int i = 2; i < argc; i++) {
                if (strcmp(argv[i], "recursive") == 0) {
                    recursive = 1;
                } else if (strncmp(argv[i], "path=", 5) == 0) {
                    pathName = argv[i] + 5;
                } else {
                    filtering_options = argv[i];
                }
            }

            if (pathName) {
                list(pathName, filtering_options, recursive, 0);
            } else {
                printf("ERROR\nmissing path\n");
            }

        } else if (strcmp(argv[1], "extract") == 0) {
            char *pathName = argv[2] + 5;
            char *sectionNumber = argv[3] + 8;
            char *lineNumber = argv[4] + 5;
            extract(pathName, sectionNumber, lineNumber);
        } else if (strcmp(argv[1], "findall") == 0) {
            char *pathName = argv[2] +5;
            findall(pathName, 0);
        }
    }
    return 0;
}
