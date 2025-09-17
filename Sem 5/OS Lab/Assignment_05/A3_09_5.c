/*************************************************************************************************
* Assignment No.: 5
* Assignment    : Program to demonstrate threads, synchronization and shared memory
* Date          : 02/09/2025
* Group No.     : A3
* Team No.      : 09
* Roll No.      : 002311001004, 002311001011, 002311001049
* Name          : Soham Das, Sarbo Sarcar, Arnob Bhakta
* Details       : C program to create three threads, and perform computations on a shared memory location using synchronization
*
*
* ipcs : shows  information on the inter-process communication facilities for which the calling process has read access
         The `-m` option is used to display information on active shared memory segments
*
* Input         : one command-line argument to define the number of (X, Y) pairs used
* Output        : displays a table of (X, Y) and A, B, C values for randomly generated (X, Y) pairs
*
*
* Compilation   : gcc A3_09_5.c -o A3_09_5 -pthread
* Execution     : ./A3_09_5 5
*

== sample output ==

key: 52063634
Pairs(X,Y) | A     | B     | C
----------------------------------
(1, 9)   | 9.00  | 21.00  | 2.33
(5, 5)   | 25.00  | 21.00  | 0.84
(8, 6)   | 48.00  | 29.00  | 0.60
(9, 7)   | 63.00  | 33.00  | 0.52
(8, 2)   | 16.00  | 21.00  | 1.31


******************************************************************************

 === ipcs command to display shared memory segments ===
$ ipcs -m

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
0x52060001 65543      adminpc    666        3360       0                       
0x00000000 19         adminpc    600        524288     2          dest         
0x52063634 65562      adminpc    666        3352       0                       
0x00000000 43         adminpc    666        504        0                       
0x00000000 46         adminpc    666        360        0                       
0x00000000 47         adminpc    666        396        0                       
0x00000000 48         adminpc    666        396        0                       
0x00000000 49         adminpc    666        396        0                       
0x00000000 32818      adminpc    666        468        0                       
0x00000000 32819      adminpc    600        524288     2          dest         
0x00000000 54         adminpc    666        396        0                 

******************************************************************************
*/



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#define MAX_N 100

struct shared_data {
    int N;
    int X[MAX_N];
    int Y[MAX_N];
    double A[MAX_N];
    double B[MAX_N];
    double C[MAX_N];
    pthread_mutex_t mutex;
    pthread_cond_t cond_start;
    pthread_cond_t cond_end;
    int current_phase;
    int done_count;
};

void *compute_A(void *arg) {
    struct shared_data *data = (struct shared_data *)arg;
    
    for (int i = 0; i < data->N; i++) {
        pthread_mutex_lock(&data->mutex);
        
        while (data->current_phase != i) {
            pthread_cond_wait(&data->cond_start, &data->mutex);
        }
        
        data->A[i] = (double)data->X[i] * data->Y[i];
        
        data->done_count++;
        if (data->done_count == 3) {
            pthread_cond_signal(&data->cond_end);
        }
        
        pthread_mutex_unlock(&data->mutex);
    }
    return NULL;
}

void *compute_B(void *arg) {
    struct shared_data *data = (struct shared_data *)arg;
    
    for (int i = 0; i < data->N; i++) {
        pthread_mutex_lock(&data->mutex);
        
        while (data->current_phase != i) {
            pthread_cond_wait(&data->cond_start, &data->mutex);
        }
        
        data->B[i] = 2.0 * data->X[i] + 2.0 * data->Y[i] + 1.0;
        
        data->done_count++;
        if (data->done_count == 3) {
            pthread_cond_signal(&data->cond_end);
        }
        
        pthread_mutex_unlock(&data->mutex);
    }
    return NULL;
}

void *compute_C(void *arg) {
    struct shared_data *data = (struct shared_data *)arg;
    
    for (int i = 0; i < data->N; i++) {
        pthread_mutex_lock(&data->mutex);
        
        while (data->current_phase != i) {
            pthread_cond_wait(&data->cond_start, &data->mutex);
        }
        
        if (data->A[i] != 0.0) {
            data->C[i] = data->B[i] / data->A[i];
        } else {
            data->C[i] = 0.0;
        }
        
        data->done_count++;
        if (data->done_count == 3) {
            pthread_cond_signal(&data->cond_end);
        }
        
        pthread_mutex_unlock(&data->mutex);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <N>\n", argv[0]);
        exit(1);
    }
    
    int N = atoi(argv[1]);
    if (N <= 0 || N > MAX_N) {
        fprintf(stderr, "N must be between 1 and %d\n", MAX_N);
        exit(1);
    }
    
    key_t key = ftok(".", 'R'); 
    printf("key: %x\n", key);
    int shmid = shmget(key, sizeof(struct shared_data), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    
    struct shared_data *shm_data = (struct shared_data *)shmat(shmid, NULL, 0);
    if (shm_data == (void *)-1) {
        perror("shmat");
        shmctl(shmid, IPC_RMID, NULL);
        exit(1);
    }
    
    shm_data->N = N;
    shm_data->current_phase = -1;
    shm_data->done_count = 0;
    
    pthread_mutexattr_t mutex_attr;
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&shm_data->mutex, &mutex_attr);
    
    pthread_condattr_t cond_attr;
    pthread_condattr_init(&cond_attr);
    pthread_condattr_setpshared(&cond_attr, PTHREAD_PROCESS_SHARED);
    pthread_cond_init(&shm_data->cond_start, &cond_attr);
    pthread_cond_init(&shm_data->cond_end, &cond_attr);
    
    srand(getpid());
    for (int i = 0; i < N; i++) {
        shm_data->X[i] = 1 + (rand() % 9);
        shm_data->Y[i] = 1 + (rand() % 9);
    }
    
    pthread_t th1, th2, th3;
    pthread_create(&th1, NULL, compute_A, shm_data);
    pthread_create(&th2, NULL, compute_B, shm_data);
    pthread_create(&th3, NULL, compute_C, shm_data);
    
    for (int i = 0; i < N; i++) {
        pthread_mutex_lock(&shm_data->mutex);
        
        shm_data->done_count = 0;
        
        shm_data->current_phase = i;
        pthread_cond_broadcast(&shm_data->cond_start);
        
        while (shm_data->done_count < 3) {
            pthread_cond_wait(&shm_data->cond_end, &shm_data->mutex);
        }

	if (shm_data->C[i] != (shm_data->B[i] / shm_data->A[i])) {
		perror("Value mismatch!\n");
		exit(1);
	}
        
        pthread_mutex_unlock(&shm_data->mutex);
    }
   
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    
    printf("Pairs(X,Y) | A     | B     | C\n");
    printf("----------------------------------\n");
    for (int i = 0; i < N; i++) {
        printf("(%d, %d)   | %.2f  | %.2f  | %.2f\n",
               shm_data->X[i], shm_data->Y[i], shm_data->A[i], shm_data->B[i], shm_data->C[i]);
    }
    
    return 0;
}
