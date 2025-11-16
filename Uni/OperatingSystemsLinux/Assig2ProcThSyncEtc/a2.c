#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "a2_helper.h"

int sem_id_sameProcess; // 2.3 sem

int sem_id_diffProcess; // 2.5 sem

int sem_id_processThBarrier; // 2.4 aem

int sem_id_max5;

int thNr = 0;
int activeThreads = 0;

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void P(int semid, int semnum) {
    struct sembuf op = {semnum, -1, 0};
    semop(semid, &op, 1);
}

void V(int semid, int semnum) {
    struct sembuf op = {semnum, 1, 0};
    semop(semid, &op, 1);
}

void* threadsAll(void* arg){
    
    int internalThNr = 0;
    P(sem_id_max5, 0);
    P(sem_id_processThBarrier, 0);
    thNr++;
    internalThNr = thNr;
    //activeThreads++;
    V(sem_id_processThBarrier, 0);

    info(BEGIN, 8, internalThNr);

    if(thNr == 13){
        //int ok = 0;

    }

    info(END, 8, internalThNr);

    V(sem_id_max5, 0);

    return NULL;
}

void* thread31(void* arg){
    info(BEGIN, 3, 1);

    

    info(END, 3, 1);
    return NULL;
}

void* thread32(void* arg){
    info(BEGIN, 3, 2);

    V(sem_id_sameProcess, 0); // da voie



    P(sem_id_sameProcess, 0); // s ar putea sa l si primeasca si sa sara un pas

    info(END, 3, 2);
    return NULL;
}

void* thread33(void* arg){

    P(sem_id_sameProcess, 0); // primeste voie

    info(BEGIN, 3, 3);



    info(END, 3, 3);

    V(sem_id_sameProcess, 0);

    return NULL;
}

void* thread34(void* arg){

    P(sem_id_diffProcess, 0);

    info(BEGIN, 3, 4);



    info(END, 3, 4);

    V(sem_id_diffProcess, 1);

    return NULL;
}

void* thread35(void* arg){
    info(BEGIN, 3, 5);



    info(END, 3, 5);
    return NULL;
}

void* thread51(void* arg){
    info(BEGIN, 5, 1);

    

    info(END, 5, 1);
    return NULL;
}

void* thread52(void* arg){
    info(BEGIN, 5, 2);



    info(END, 5, 2);

    V(sem_id_diffProcess, 0);

    return NULL;
}

void* thread53(void* arg){
    info(BEGIN, 5, 3);



    info(END, 5, 3);
    return NULL;
}

void* thread54(void* arg){

    P(sem_id_diffProcess, 1);

    info(BEGIN, 5, 4);



    info(END, 5, 4);
    return NULL;
}

void* thread55(void* arg){
    info(BEGIN, 5, 5);



    info(END, 5, 5);
    return NULL;
}

void* thread56(void* arg){
    info(BEGIN, 5, 6);

    

    info(END, 5, 6);
    return NULL;
}


int main(){
    init();

    info(BEGIN, 1, 0);

    // sem_id_sameProcess = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
    // union semun argSameProcess;
    // unsigned short arrayfirst[2] = {0, 0};
    // argSameProcess.array = arrayfirst;
    // semctl(sem_id_sameProcess, 0, SETALL, argSameProcess);

    sem_id_sameProcess = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    union semun argSameProcess;
    argSameProcess.val = 0;
    semctl(sem_id_sameProcess, 0, SETVAL, argSameProcess);

    sem_id_diffProcess = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
    union semun argDiffProcess;
    unsigned short array[2] = {0, 0};
    argDiffProcess.array = array;
    semctl(sem_id_diffProcess, 0, SETALL, argDiffProcess);

    sem_id_processThBarrier = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
    union semun argprocessThBarrier;
    unsigned short arrayBar[2] = {1, 1};
    argprocessThBarrier.array = arrayBar;
    semctl(sem_id_processThBarrier, 0, SETALL, argprocessThBarrier);

    sem_id_max5 = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    union semun argmax5;
    argmax5.val = 5;
    semctl(sem_id_max5, 0, SETVAL, argmax5);
    

    pid_t pid2,pid3;
    if((pid2 = fork()) == 0){
        
        info(BEGIN, 2, 0);

        pid_t pid7;
        if((pid7 = fork()) == 0){

            info(BEGIN, 7, 0);



            info(END, 7, 0);
            _exit(0);

        }

        waitpid(pid7, NULL, 0);
        info(END, 2, 0);
        _exit(0);

    } // poate trebe verif

    if((pid3 = fork()) == 0){
        
        info(BEGIN, 3, 0);

        pid_t pid4,pid6;
        if((pid4 = fork()) == 0){

            info(BEGIN, 4, 0);

            pid_t pid5;
            if((pid5 = fork()) == 0){

                info(BEGIN, 5, 0);

                pthread_t thread51aux, thread52aux, thread53aux, thread54aux, thread55aux, thread56aux;
                pthread_create(&thread51aux, NULL, thread51, NULL);
                pthread_create(&thread52aux, NULL, thread52, NULL);
                pthread_create(&thread53aux, NULL, thread53, NULL);
                pthread_create(&thread54aux, NULL, thread54, NULL);
                pthread_create(&thread55aux, NULL, thread55, NULL);
                pthread_create(&thread56aux, NULL, thread56, NULL);
                pthread_join(thread51aux, NULL);
                pthread_join(thread52aux, NULL);
                pthread_join(thread53aux, NULL);
                pthread_join(thread54aux, NULL);
                pthread_join(thread55aux, NULL);
                pthread_join(thread56aux, NULL);

                info(END, 5, 0);
                _exit(0);

            }

            waitpid(pid5, NULL, 0);
            info(END, 4, 0);
            _exit(0);

        }

        if((pid6 = fork()) == 0){

            info(BEGIN, 6, 0);

            pid_t pid8,pid9;
            if((pid8 = fork()) == 0){

                info(BEGIN, 8, 0);

                pthread_t pidAux[48];
                for(int i = 0; i<9; i++){
                    //pthread_t pidAux;
                    //pthread_create(&pidAux[i], NULL, threadsAll, NULL);
                    pthread_create(&pidAux[i*5+1], NULL, threadsAll, NULL);
                    pthread_create(&pidAux[i*5+2], NULL, threadsAll, NULL);
                    pthread_create(&pidAux[i*5+3], NULL, threadsAll, NULL);
                    pthread_create(&pidAux[i*5+4], NULL, threadsAll, NULL);
                    pthread_create(&pidAux[i*5+5], NULL, threadsAll, NULL);

                }

               // pthread_create(&pidAux[45], NULL, threadsAll, NULL);
                pthread_create(&pidAux[46], NULL, threadsAll, NULL);
                pthread_create(&pidAux[47], NULL, threadsAll, NULL);
                pthread_create(&pidAux[48], NULL, threadsAll, NULL);


                for(int i = 1; i<=48; i++){
                    pthread_join(pidAux[i], NULL);
                }

                info(END, 8, 0);
                _exit(0);

            }

            if((pid9 = fork()) == 0){

                info(BEGIN, 9, 0);



                info(END, 9, 0);
                _exit(0);

            }

            waitpid(pid8, NULL, 0);
            waitpid(pid9, NULL, 0);
            info(END, 6, 0);
            _exit(0);

        }

        pthread_t thread31aux, thread32aux, thread33aux, thread34aux, thread35aux;
        pthread_create(&thread31aux, NULL, thread31, NULL);
        pthread_create(&thread32aux, NULL, thread32, NULL);
        pthread_create(&thread33aux, NULL, thread33, NULL);
        pthread_create(&thread34aux, NULL, thread34, NULL);
        pthread_create(&thread35aux, NULL, thread35, NULL);
        pthread_join(thread31aux, NULL);
        pthread_join(thread32aux, NULL);
        pthread_join(thread33aux, NULL);
        pthread_join(thread34aux, NULL);
        pthread_join(thread35aux, NULL);

        waitpid(pid4, NULL, 0);
        waitpid(pid6, NULL, 0);
        info(END, 3, 0);
        _exit(0);

    }

    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    info(END, 1, 0);


    return 0;
}
