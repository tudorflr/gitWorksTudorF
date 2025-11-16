#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/mman.h>


int main(void) {
    /*if (argc >= 1) {
        if (strcmp(argv[0], "./a3") != 0) {
            printf("ERROR\nwrong program name\n");
            return 0;
        }
    }
        */

    mkfifo("RESP_PIPE_92529", 0666);

    int fd_req = open("REQ_PIPE_92529", O_RDONLY);
    if (fd_req < 0) {
        printf("ERROR\ncannot open the request pipe\n");
        return 1;
    }

    int fd_resp = open("RESP_PIPE_92529", O_WRONLY);
    if (fd_resp < 0) {
        printf("ERROR\ncannot create the response pipe\n");
        close(fd_resp);
        return 1;
    }

    /*
    if(write(fd_resp, "START", strlen("START"))) {
        printf("ERROR\ncannot create the response pipe | cannot open the request pipe\n");
        close(fd_req);
        close(fd_resp);
        return 1;
    }
        */

    write(fd_resp, "START!", 6);

    printf("SUCCESS");

    while(1){
        char requestMessage[250];
        int cnt = 0;
        ssize_t byteRead;

        while(1){

            char letterRead;
            byteRead = read(fd_req, &letterRead, 1);

            if (byteRead <= 0) {
               break;
            }
            
            if (letterRead == '!') {
                break;
            }

            if(cnt < sizeof(requestMessage) -1){
                requestMessage[cnt] = letterRead;
                cnt++;
            }
        
        }

        if(byteRead <= 0){
            break;
        }

        requestMessage[cnt] = '\0';

        if (strcmp(requestMessage, "PING") == 0) {

            write(fd_resp, "PING!", 5);
            unsigned int id = 92529;
            write(fd_resp, &id, sizeof(id));
            write(fd_resp, "PONG!", 5);

        } else if (strcmp(requestMessage, "CREATE_SHM") == 0) {

            unsigned int size;
            read(fd_req, &size, sizeof(size));
            int shm_fd;
            shm_fd = shm_open("/X1gzEg", O_CREAT | O_RDWR, 0664);

            if(shm_fd < 0){
                write(fd_resp, "CREATE_SHM!", 11);
                write(fd_resp, "ERROR!", 6);
                continue;
            }

            // nush daca trb check

            ftruncate(shm_fd, size);
            write(fd_resp, "CREATE_SHM!", 11);
            write(fd_resp, "SUCCESS!", 8);

        } else if (strcmp(requestMessage, "WRITE_TO_SHM") == 0) {
            unsigned int offset;
            unsigned int value;
            read(fd_req, &offset, sizeof(offset));
            read(fd_req, &value, sizeof(value));
        
            int shm_fd = shm_open("/X1gzEg", O_RDWR, 0664);
            if (shm_fd < 0) {
                write(fd_resp, "WRITE_TO_SHM!", 13);
                write(fd_resp, "ERROR!", 6);
                continue;
            }
        
            unsigned int shm_size = 4532432;
            if (offset + sizeof(unsigned int) > shm_size) {
                write(fd_resp, "WRITE_TO_SHM!", 13);
                write(fd_resp, "ERROR!", 6);
                close(shm_fd);
                continue;
            }
        
            void* shm_ptr = mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
            if (shm_ptr == MAP_FAILED) {
                write(fd_resp, "WRITE_TO_SHM!", 13);
                write(fd_resp, "ERROR!", 6);
                close(shm_fd);
                continue;
            }
        
            *((unsigned int*)((char*)shm_ptr + offset)) = value;
        
            write(fd_resp, "WRITE_TO_SHM!", 13);
            write(fd_resp, "SUCCESS!", 8);
        
            munmap(shm_ptr, shm_size);
            close(shm_fd);

        } else if (strcmp(requestMessage, "MAP_FILE") == 0){
            char fileName[250];
            read(fd_req, fileName, sizeof(fileName));
            
            int fd = open(fileName, O_RDONLY);
            if(fd < 0){
                write(fd_resp, "MAP_FILE!", 9);
                write(fd_resp, "ERROR!", 6);
                continue;
            }

            struct stat fileStat;
            if(fstat(fd, &fileStat) < 0){
                write(fd_resp, "MAP_FILE!", 9);
                write(fd_resp, "ERROR!", 6);
                close(fd);
                continue;
            }

            void* filePtr = mmap(NULL, fileStat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
            if(filePtr == MAP_FAILED){
                write(fd_resp, "MAP_FILE!", 9);
                write(fd_resp, "ERROR!", 6);
                close(fd);
                continue;
            }
            

            write(fd_resp, "MAP_FILE!", 9);
            write(fd_resp, "SUCCES!", 7);

            munmap(filePtr, fileStat.st_size);
            close(fd);

        } else if (strcmp(requestMessage, "EXIT") == 0) {
            close(fd_req);
            close(fd_resp);
            unlink("REQ_PIPE_92529");
            unlink("RESP_PIPE_92529");
            return 0;
            break;

        } else {
            break;
        }

        

    }

    close(fd_req);
    close(fd_resp);

    return 0;
}
