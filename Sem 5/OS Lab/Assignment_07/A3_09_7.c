/**************************************************************************************************
 * Assignment No  : 7
 * Assignment     : Avoiding DEADLOCK using Thread Programming
 * Date           : 15/09/2025
 * Group No.      : A3
 * Team No.       : 09
 * Roll No.       : 002311001004, 002311001011, 002311001049
 *
 * Name           : Soham Das, Sarbo Sarcar, Arnob Bhakta
 *
 * Details        : A multithreaded C program to demonstrate deadlock avoidance using consistent
 *                  mutex locking order with the pthread library. The program defines three shared
 *                  global variables (Total_1, Total_2, Total_3), protected by three mutexes.
 *                  Three threads (Th1, Th2, Th3) continuously transfer random amounts between these
 *                  totals while ensuring deadlock is avoided. A fourth thread (Th4) displays the
 *                  individual totals and their sum, ensuring consistent values are printed.
 *
 * Input          : None (All values initialized in the code).
 *
 * Output         : Continuously prints Total_1, Total_2, Total_3, and the Grand Total in a consistent state.
 *                  Demonstrates that there is no deadlock through uninterrupted and correct output.
 *
 * Compilation    : gcc -o A3_09_7 A3_09_7.c -pthread
 *
 * Execution      : ./A3_09_7
 *
 * Sample Output  :
 *
 * Total_1: 99993, Total_2: 100017, Total_3: 99990, Grand Total: 300000
 * Total_1: 100409, Total_2: 99893, Total_3: 99698, Grand Total: 300000
 * Total_1: 100866, Total_2: 99846, Total_3: 99288, Grand Total: 300000
 * Total_1: 101377, Total_2: 99823, Total_3: 98800, Grand Total: 300000
 * Total_1: 101558, Total_2: 99963, Total_3: 98479, Grand Total: 300000
 * Total_1: 101924, Total_2: 100004, Total_3: 98072, Grand Total: 300000
 * Total_1: 102242, Total_2: 100003, Total_3: 97755, Grand Total: 300000
 * Total_1: 102599, Total_2: 100185, Total_3: 97216, Grand Total: 300000
 * ...
 *
 * (Output continues indefinitely, showing consistent totals and grand total.)
 *
 *
 * === Deadlock Avoidance Strategy ===
 *
 * Mutexes are always locked in a strict global order:
 *     mutex1 -> mutex2 -> mutex3
 * Threads needing multiple mutexes acquire them in ascending order of their memory address.
 *
 * === To Create Deadlock (For demonstration) ===
 *
 * If mutexes are unlocked in incorrect order, circular waiting can occur, leading to a deadlock.
 *
 * === Notes on Parallel Behavior ===
 *
 * - Each of Th1, Th2, and Th3 randomly transfers small amounts between totals.
 * - Th4 prints totals in a consistent, locked state to ensure accurate output.
 * - Program runs indefinitely with no deadlock or data races when locking order is followed.
 *
 **************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int Total_1 = 100000;
int Total_2 = 100000;
int Total_3 = 100000;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

void lock_in_order(pthread_mutex_t *first, pthread_mutex_t *second) {
    if (first < second) {
        pthread_mutex_lock(first);
        pthread_mutex_lock(second);
    } else if (first > second) {
        pthread_mutex_lock(second);
        pthread_mutex_lock(first);
    } else {
        pthread_mutex_lock(first);
    }
}

void unlock_in_order(pthread_mutex_t *first, pthread_mutex_t *second) {
    if (first < second) {
        pthread_mutex_unlock(second);
        pthread_mutex_unlock(first);
    } else if (first > second) {
        pthread_mutex_unlock(first);
        pthread_mutex_unlock(second);
    } else {
        pthread_mutex_unlock(first);
    }
}

void* Th1_func(void* arg) {
    while (1) {
        int amount = rand() % 10 + 1;
        int target = rand() % 2;
        if (target == 0) {
            lock_in_order(&mutex1, &mutex2);
            if (Total_1 >= amount) {
                Total_1 -= amount;
                Total_2 += amount;
            }
            unlock_in_order(&mutex1, &mutex2);
        } else {
            lock_in_order(&mutex1, &mutex3);
            if (Total_1 >= amount) {
                Total_1 -= amount;
                Total_3 += amount;
            }
            unlock_in_order(&mutex1, &mutex3);
        }
        usleep(10000);
    }
    return NULL;
}

void* Th2_func(void* arg) {
    while (1) {
        int amount = rand() % 20 + 1;
        int target = rand() % 2;
        if (target == 0) {
            lock_in_order(&mutex2, &mutex1);
            if (Total_2 >= amount) {
                Total_2 -= amount;
                Total_1 += amount;
            }
            unlock_in_order(&mutex2, &mutex1);
        } else {
            lock_in_order(&mutex2, &mutex3);
            if (Total_2 >= amount) {
                Total_2 -= amount;
                Total_3 += amount;
            }
            unlock_in_order(&mutex2, &mutex3);
        }
        usleep(10000);
    }
    return NULL;
}

void* Th3_func(void* arg) {
    while (1) {
        int amount = rand() % 30 + 1;
        int target = rand() % 2;
        if (target == 0) {
            lock_in_order(&mutex3, &mutex1);
            if (Total_3 >= amount) {
                Total_3 -= amount;
                Total_1 += amount;
            }
            unlock_in_order(&mutex3, &mutex1);
        } else {
            lock_in_order(&mutex3, &mutex2);
            if (Total_3 >= amount) {
                Total_3 -= amount;
                Total_2 += amount;
            }
            unlock_in_order(&mutex3, &mutex2);
        }
        usleep(10000);
    }
    return NULL;
}

void* Th4_func(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex1);
        pthread_mutex_lock(&mutex2);
        pthread_mutex_lock(&mutex3);
        int t1 = Total_1;
        int t2 = Total_2;
        int t3 = Total_3;
        int grand = t1 + t2 + t3;
        printf("Total_1: %d, Total_2: %d, Total_3: %d, Grand Total: %d\n", t1, t2, t3, grand);
        pthread_mutex_unlock(&mutex3);
        pthread_mutex_unlock(&mutex2);
        pthread_mutex_unlock(&mutex1);
        usleep(500000);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t th1, th2, th3, th4;
    pthread_create(&th1, NULL, Th1_func, NULL);
    pthread_create(&th2, NULL, Th2_func, NULL);
    pthread_create(&th3, NULL, Th3_func, NULL);
    pthread_create(&th4, NULL, Th4_func, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    pthread_join(th4, NULL);
    return 0;
}
