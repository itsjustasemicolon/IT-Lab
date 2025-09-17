/*************************************************************************************************
* Assignment No.: 2B
* Assignment    : Program to transfer a large file between processes using FIFOs.
* Date          : 05/08/2024
* Group No.     : A3
* Team No.      : 09
* Roll No.      : 002311001004, 002311001011, 002311001049
* Name          : Soham Das, Sarbo Sarcar, Arnob Bhakta
* Details       : A program that creates a parent and child process. The parent
* sends a 1GB file to the child via one FIFO, and the child
* sends it back via a second FIFO. The program measures the
* transfer time and verifies the file's integrity.
* Input         : None. The program generates its own 1GB data file.
* Output        : Prints the progress of file transfers, the total time taken for
* the round trip, and a verification message.
*
* Compilation   : gcc A3_09_2B.c -o A3_09_2B 
* Execution     : ./A3_09_2B
*
* Sample Input  : ./A3_09_2B
*
* Sample Output :
* --- Setting up environment ---
* Creating a 1GB file named 'original_file.dat' with random text...
* Creating file: 1024 MB written.
* File created.
* Creating FIFOs: 'fifo_file1' and 'fifo_file2'...
* FIFOs created.
*
* --- Verifying file and FIFO creation ---
* prw-rw-r-- 1 soham soham    0 Aug  5 09:47 fifo_file1
* prw-rw-r-- 1 soham soham    0 Aug  5 09:47 fifo_file2
* -rw-rw-r-- 1 soham soham 1.0G Aug  5 09:47 original_file.txt
* --------------------------------------
*
* [Parent] Process started. PID: 98757
* [Parent] Sending 'original_file.dat' to child via 'fifo_file1'...
* [Child] Process started. PID: 98780, Parent PID: 98757
* [Child] Receiving file from parent via 'fifo_file1'...
* [Parent] Finished sending file to child.
* [Parent] Receiving file back from child via 'fifo_file2'...
* [Child] Finished receiving. File saved to 'child_temp_file.txt'.
* [Child] Re-transmitting file to parent via 'fifo_file2'...
* [Parent] Finished receiving file. Saved as 'returned_file.txt'.
* [Child] Finished re-transmitting file. Exiting.
* [Parent] Child process has terminated.
*
* ------------------- RESULTS -------------------
* Total time for double transfer: 2.7557 seconds
* Comparing 'original_file.dat' and 'returned_file.txt'...
* Verification successful: The files are identical.
* ---------------------------------------------
*
* Cleaning up files and FIFOs...
* Cleanup complete.
*
*************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#define FIFO1_NAME "fifo_file1"
#define FIFO2_NAME "fifo_file2"
#define ORIGINAL_FILE "original_file.txt"
#define RETURNED_FILE "returned_file.txt"
#define CHILD_TEMP_FILE "child_temp_file.txt"
#define BUFFER_SIZE 4096
#define FILE_SIZE (1024LL * 1024 * 1024) // 1 GB

// Function to handle errors and exit
void handle_error(const char *msg) {
    perror(msg);
    // Clean up any created FIFOs before exiting on error
    unlink(FIFO1_NAME);
    unlink(FIFO2_NAME);
    exit(EXIT_FAILURE);
}

// Function to create a large file with random text content
void create_large_text_file(const char *filename, long long size) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        handle_error("Failed to open file for writing");
    }

    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    const int charset_size = sizeof(charset) - 1;
    char buffer[BUFFER_SIZE];
    long long total_bytes_written = 0;

    printf("Creating file: ");
    fflush(stdout);

    while (total_bytes_written < size) {
        long long bytes_to_write = BUFFER_SIZE;
        if (total_bytes_written + BUFFER_SIZE > size) {
            bytes_to_write = size - total_bytes_written;
        }

        // Fill the buffer with random characters
        for (int i = 0; i < bytes_to_write; ++i) {
            buffer[i] = charset[rand() % charset_size];
        }

        if (fwrite(buffer, 1, bytes_to_write, fp) != bytes_to_write) {
            fclose(fp);
            handle_error("Failed to write to file");
        }

        total_bytes_written += bytes_to_write;

        // Print progress indicator every 1MB
        if ((total_bytes_written % (1024 * 1024)) == 0) {
            printf("\rCreating file: %lld MB written.", total_bytes_written / (1024 * 1024));
            fflush(stdout);
        }
    }
    printf("\n");
    fclose(fp);
}


int main() {
    pid_t pid;
    struct timespec start_time, end_time;

    // Seed the random number generator once at the start of the program
    srand(time(NULL));

    // --- Setup: Create large file and FIFOs ---
    printf("--- Setting up environment ---\n");

    printf("Creating a 1GB file named '%s' with random text...\n", ORIGINAL_FILE);
    create_large_text_file(ORIGINAL_FILE, FILE_SIZE);
    printf("File created.\n");

    printf("Creating FIFOs: '%s' and '%s'...\n", FIFO1_NAME, FIFO2_NAME);
    if (mkfifo(FIFO1_NAME, 0666) == -1 && errno != EEXIST) {
        handle_error("mkfifo fifo_file1 failed");
    }
    if (mkfifo(FIFO2_NAME, 0666) == -1 && errno != EEXIST) {
        handle_error("mkfifo fifo_file2 failed");
    }
    printf("FIFOs created.\n");

    printf("\n--- Verifying file and FIFO creation ---\n");
    char command[256];
    snprintf(command, sizeof(command), "ls -lh %s %s %s", ORIGINAL_FILE, FIFO1_NAME, FIFO2_NAME);
    system(command);
    printf("--------------------------------------\n\n");


    // --- Fork and Transfer ---
    pid = fork();

    if (pid < 0) {
        handle_error("fork failed");
    }

    // --- Parent Process ---
    if (pid > 0) {
        printf("[Parent] Process started. PID: %d\n", getpid());

        // Start the timer
        clock_gettime(CLOCK_MONOTONIC, &start_time);

        // --- 1. Parent sends file to Child via FIFO1 ---
        printf("[Parent] Sending '%s' to child via '%s'...\n", ORIGINAL_FILE, FIFO1_NAME);
        int fd_fifo1_w = open(FIFO1_NAME, O_WRONLY);
        if (fd_fifo1_w == -1) handle_error("[Parent] open fifo_file1 for writing failed");

        int fd_orig = open(ORIGINAL_FILE, O_RDONLY);
        if (fd_orig == -1) handle_error("[Parent] open original file for reading failed");

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        while ((bytes_read = read(fd_orig, buffer, BUFFER_SIZE)) > 0) {
            if (write(fd_fifo1_w, buffer, bytes_read) != bytes_read) {
                handle_error("[Parent] write to fifo_file1 failed");
            }
        }
        if (bytes_read == -1) handle_error("[Parent] read from original file failed");
        
        close(fd_orig);
        close(fd_fifo1_w); // Close write end to signal EOF to child
        printf("[Parent] Finished sending file to child.\n");

        // --- 4. Parent receives file back from Child via FIFO2 ---
        printf("[Parent] Receiving file back from child via '%s'...\n", FIFO2_NAME);
        int fd_fifo2_r = open(FIFO2_NAME, O_RDONLY);
        if (fd_fifo2_r == -1) handle_error("[Parent] open fifo_file2 for reading failed");

        int fd_ret = open(RETURNED_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd_ret == -1) handle_error("[Parent] open returned file for writing failed");

        while ((bytes_read = read(fd_fifo2_r, buffer, BUFFER_SIZE)) > 0) {
            if (write(fd_ret, buffer, bytes_read) != bytes_read) {
                handle_error("[Parent] write to returned file failed");
            }
        }
        if (bytes_read == -1) handle_error("[Parent] read from fifo_file2 failed");
        
        close(fd_ret);
        close(fd_fifo2_r);
        printf("[Parent] Finished receiving file. Saved as '%s'.\n", RETURNED_FILE);

        // Stop the timer
        clock_gettime(CLOCK_MONOTONIC, &end_time);

        // Wait for child to terminate
        wait(NULL);
        printf("[Parent] Child process has terminated.\n");

        // --- Verification and Cleanup ---
        double time_taken = (end_time.tv_sec - start_time.tv_sec);
        time_taken += (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
        printf("\n------------------- RESULTS -------------------\n");
        printf("Total time for double transfer: %.4f seconds\n", time_taken);

        printf("Comparing '%s' and '%s'...\n", ORIGINAL_FILE, RETURNED_FILE);
        snprintf(command, sizeof(command), "cmp -s %s %s", ORIGINAL_FILE, RETURNED_FILE);
        if (system(command) == 0) {
            printf("Verification successful: The files are identical.\n");
        } else {
            printf("Verification FAILED: The files are different.\n");
        }
        printf("---------------------------------------------\n");

        printf("\nCleaning up files and FIFOs...\n");
        unlink(ORIGINAL_FILE);
        unlink(RETURNED_FILE);
        unlink(FIFO1_NAME);
        unlink(FIFO2_NAME);
        printf("Cleanup complete.\n");

    }
    // --- Child Process ---
    else {
        printf("[Child] Process started. PID: %d, Parent PID: %d\n", getpid(), getppid());

        // --- 2. Child receives from Parent via FIFO1 and saves to a temp file ---
        printf("[Child] Receiving file from parent via '%s'...\n", FIFO1_NAME);
        int fd_fifo1_r = open(FIFO1_NAME, O_RDONLY);
        if (fd_fifo1_r == -1) handle_error("[Child] open fifo_file1 for reading failed");

        int fd_temp = open(CHILD_TEMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd_temp == -1) handle_error("[Child] open temp file for writing failed");

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        while ((bytes_read = read(fd_fifo1_r, buffer, BUFFER_SIZE)) > 0) {
            if (write(fd_temp, buffer, bytes_read) != bytes_read) {
                handle_error("[Child] write to temp file failed");
            }
        }
        if (bytes_read == -1) handle_error("[Child] read from fifo_file1 failed");

        close(fd_fifo1_r);
        close(fd_temp);
        printf("[Child] Finished receiving. File saved to '%s'.\n", CHILD_TEMP_FILE);

        // --- 3. Child sends the temp file back to Parent via FIFO2 ---
        printf("[Child] Re-transmitting file to parent via '%s'...\n", FIFO2_NAME);
        int fd_fifo2_w = open(FIFO2_NAME, O_WRONLY);
        if (fd_fifo2_w == -1) handle_error("[Child] open fifo_file2 for writing failed");

        fd_temp = open(CHILD_TEMP_FILE, O_RDONLY);
        if (fd_temp == -1) handle_error("[Child] open temp file for reading failed");

        while ((bytes_read = read(fd_temp, buffer, BUFFER_SIZE)) > 0) {
            if (write(fd_fifo2_w, buffer, bytes_read) != bytes_read) {
                handle_error("[Child] write to fifo_file2 failed");
            }
        }
        if (bytes_read == -1) handle_error("[Child] read from temp file failed");

        close(fd_temp);
        close(fd_fifo2_w);
        
        unlink(CHILD_TEMP_FILE); // Clean up the temporary file
        printf("[Child] Finished re-transmitting file. Exiting.\n");
        exit(EXIT_SUCCESS);
    }

    return 0;
}
