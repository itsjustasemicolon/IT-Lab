/**************************************************************************************************
 * Assignment No  : 6
 * Assignment     : Parallel Programming using Pthread in C
 * Date           : 09/09/2025
 * Group No.      : A3
 * Team No.       : 09
 * Roll No.       : 002311001004, 002311001011, 002311001049
 *
 * Name           : Soham Das, Sarbo Sarcar, Arnob Bhakta
 *
 * Details        : A C program that multiplies two large square matrices in parallel using
 *                  the pthread library. The program divides the first matrix into row chunks,
 *                  assigns each chunk to a separate thread for computation. The execution
 *                  time is measured using gettimeofday.
 * Input          : Command-line arguments specifying matrix dimension, number of threads,
 *                  modulus value for initialization, and a print flag.
 * Output         : Elapsed execution time and optional printing of matrices.
 *
 * Compilation    : gcc -o A3_09_6 A3_09_6.c -pthread -O2
 *                  NOTE: The -O2 is an optimization flag. -O2 tells the compiler to make the
 *                  code run much faster.
 *
 * Execution      : ./A3_09_6 <dimension> <threads> <mod_val> <print_switch>
 *
 * Sample Input   : ./A3_09_6 3000 6 50 0
 *
 * Sample Output  :
 *
 * Initializing 3000x3000 matrices...
 * Initialization complete.
 *
 * Starting matrix multiplication with 6 threads...
 * Matrix multiplication complete.
 * Time Elapsed: 14.4719 seconds
 *
 * Matrix printing is suppressed (print_switch=0).
 *
 *
 * === Process and CPU Utilization Snapshot ===
 *
 * >$ pgrep A3_09_6
 * 8521
 *
 * >$ ps -T -p 8521
 * PID    SPID TTY          TIME CMD
 * 8521    8521 pts/0    00:00:00 A3_09_6
 * 8521    8522 pts/0    00:00:06 A3_09_6
 * 8521    8523 pts/0    00:00:06 A3_09_6
 * 8521    8524 pts/0    00:00:06 A3_09_6
 * 8521    8525 pts/0    00:00:06 A3_09_6
 * 8521    8526 pts/0    00:00:06 A3_09_6
 * 8521    8527 pts/0    00:00:06 A3_09_6
 *
 * >$ cpustat
  %CPU   %USR   %SYS     PID S  CPU    Time Task
  4.00   3.00   1.00    5298 S   11  15.95s /usr/libexec/gnome-terminal-server
  3.00   3.00   0.00    1739 S    3  59.37s /usr/lib/xorg/Xorg
  3.00   2.00   1.00    1869 S    8   1.23m /usr/bin/gnome-shell
  3.00   2.00   1.00    3448 S    2   4.09m /usr/lib/firefox/firefox
  2.00   0.00   2.00     657 S    9  28.21s [irq/162-rtw88_p]
  2.00   2.00   0.00    3702 S    5  29.60s /usr/lib/firefox/firefox

  %CPU   %USR   %SYS     PID S  CPU    Time Task
  2.00   2.00   0.00    1869 S    8   1.23m /usr/bin/gnome-shell
  2.00   2.00   0.00    3702 S    5  29.62s /usr/lib/firefox/firefox
  1.00   0.00   1.00    5298 S   11  15.96s /usr/libexec/gnome-terminal-server
  1.00   1.00   0.00    1739 S    3  59.38s /usr/lib/xorg/Xorg
  1.00   0.00   1.00    7860 R    4   0.02s cpustat
  1.00   1.00   0.00    3448 S    2   4.09m /usr/lib/firefox/firefox

  %CPU   %USR   %SYS     PID S  CPU    Time Task
601.00 599.00   2.00    7862 S   10   8.69s ./A3_09_6
  2.00   1.00   1.00    1739 S    3  59.40s /usr/lib/xorg/Xorg
  1.00   1.00   0.00    5298 S   11  15.97s /usr/libexec/gnome-terminal-server
  1.00   1.00   0.00     920 S    8   2.00s /usr/sbin/NetworkManager
  1.00   1.00   0.00    1869 S    8   1.23m /usr/bin/gnome-shell

  %CPU   %USR   %SYS     PID S  CPU    Time Task
600.00 600.00   0.00    7862 S   10  14.69s ./A3_09_6
  2.00   2.00   0.00    1869 S    8   1.23m /usr/bin/gnome-shell
  1.00   1.00   0.00    5298 S   11  15.98s /usr/libexec/gnome-terminal-server
  1.00   0.00   1.00     657 S    9  28.22s [irq/162-rtw88_p]

  %CPU   %USR   %SYS     PID S  CPU    Time Task
600.00 600.00   0.00    7862 S   10  20.69s ./A3_09_6
  1.00   1.00   0.00    5298 S   11  15.99s /usr/libexec/gnome-terminal-server
  1.00   0.00   1.00    1739 S    3  59.41s /usr/lib/xorg/Xorg
  1.00   1.00   0.00    1869 S    8   1.23m /usr/bin/gnome-shell

  %CPU   %USR   %SYS     PID S  CPU    Time Task
600.00 600.00   0.00    7862 S   10  26.69s ./A3_09_6
  2.00   1.00   1.00    1869 S    8   1.23m /usr/bin/gnome-shell
  1.00   1.00   0.00    5298 S   11  16.00s /usr/libexec/gnome-terminal-server
  1.00   1.00   0.00    1739 S    3  59.42s /usr/lib/xorg/Xorg
  1.00   0.00   1.00    7860 R    4   0.03s cpustat
  1.00   1.00   0.00    4536 S   11   2.81s /usr/lib/firefox/firefox
  1.00   1.00   0.00    7655 S    5   0.09s /usr/lib/firefox/firefox

  %CPU   %USR   %SYS     PID S  CPU    Time Task
599.00 599.00   0.00    7862 S   10  32.68s ./A3_09_6
  2.00   2.00   0.00    5298 S   11  16.02s /usr/libexec/gnome-terminal-server
  2.00   1.00   1.00    1739 S    3  59.44s /usr/lib/xorg/Xorg
  1.00   1.00   0.00    1869 S    8   1.23m /usr/bin/gnome-shell
  1.00   1.00   0.00    3702 S    5  29.63s /usr/lib/firefox/firefox
 *
 * (NOTE: The CPU utilization exceeding 100% indicates that multiple cores
 * are being used by the threads of this single process.)
 *
 * === Summary of Timings (Example) ===
 * 1 thread(s): 78.0751 seconds
 * 2 thread(s): 38.8143 seconds
 * 3 thread(s): 27.3550 seconds
 * 4 thread(s): 20.5566 seconds
 * 5 thread(s): 17.1567 seconds
 * 6 thread(s): 14.4719 seconds
 *
 **************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

unsigned int **mat_A;
unsigned int **mat_B;
unsigned int **mat_C;
int dim;

typedef struct {
    int id;
    int start_row;
    int end_row;
} ThreadArgs;

void *multiply_chunk(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int start_row = args->start_row;
    int end_row = args->end_row;

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < dim; j++) {
            mat_C[i][j] = 0;
            for (int k = 0; k < dim; k++) {
                mat_C[i][j] += mat_A[i][k] * mat_B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

void print_matrix(unsigned int **mat) {
    const int PREVIEW_SIZE = 3;
    printf("\n");

    if (dim <= PREVIEW_SIZE * 2) {
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                printf("%u ", mat[i][j]);
            }
            printf("\n");
        }
    } else {

        for (int i = 0; i < PREVIEW_SIZE; i++) {
            for (int j = 0; j < PREVIEW_SIZE; j++) {
                printf("%u ", mat[i][j]);
            }
            printf("... ");
            for (int j = dim - PREVIEW_SIZE; j < dim; j++) {
                printf("%u ", mat[i][j]);
            }
            printf("\n");
        }

        printf("...\n");

        for (int i = dim - PREVIEW_SIZE; i < dim; i++) {
            for (int j = 0; j < PREVIEW_SIZE; j++) {
                printf("%u ", mat[i][j]);
            }
            printf("... ");
            for (int j = dim - PREVIEW_SIZE; j < dim; j++) {
                printf("%u ", mat[i][j]);
            }
            printf("\n");
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <dimension> <threads> <mod_val> <print_switch>\n", argv[0]);
        return 1;
    }

    dim = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    int mod_val = atoi(argv[3]);
    int print_switch = atoi(argv[4]);

    if (dim <= 0 || num_threads <= 0 || mod_val <= 0) {
        fprintf(stderr, "Error: dimension, threads, and mod_val must be positive integers.\n");
        return 1;
    }

    printf("Initializing %dx%d matrices...\n", dim, dim);

    mat_A = (unsigned int **)malloc(dim * sizeof(unsigned int *));
    mat_B = (unsigned int **)malloc(dim * sizeof(unsigned int *));
    mat_C = (unsigned int **)malloc(dim * sizeof(unsigned int *));
    for (int i = 0; i < dim; i++) {
        mat_A[i] = (unsigned int *)malloc(dim * sizeof(unsigned int));
        mat_B[i] = (unsigned int *)malloc(dim * sizeof(unsigned int));
        mat_C[i] = (unsigned int *)malloc(dim * sizeof(unsigned int));
    }

    srand(time(NULL));
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            mat_A[i][j] = rand() % mod_val;
            mat_B[i][j] = rand() % mod_val;
        }
    }
    printf("Initialization complete.\n");

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    printf("\nStarting matrix multiplication with %d threads...\n", num_threads);

    pthread_t threads[num_threads];
    ThreadArgs thread_args[num_threads];
    int rows_per_thread = dim / num_threads;

    for (int i = 0; i < num_threads; i++) {
        thread_args[i].id = i;
        thread_args[i].start_row = i * rows_per_thread;
        thread_args[i].end_row = (i == num_threads - 1) ? dim : (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, multiply_chunk, &thread_args[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end_time, NULL);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1e6;

    printf("Matrix multiplication complete.\n");
    printf("Time Elapsed: %.4f seconds\n", elapsed_time);

    if (print_switch == 1) {
        printf("\n--- Input Matrix A ---");
        print_matrix(mat_A);
        printf("\n--- Input Matrix B ---");
        print_matrix(mat_B);
        printf("\n--- Result Matrix C ---");
        print_matrix(mat_C);
    } else {
        printf("\nMatrix printing is suppressed (print_switch=0).\n");
    }

    for (int i = 0; i < dim; i++) {
        free(mat_A[i]);
        free(mat_B[i]);
        free(mat_C[i]);
    }
    free(mat_A);
    free(mat_B);
    free(mat_C);

    return 0;
}

