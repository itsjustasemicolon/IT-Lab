/*************************************************************************************************
* Assignment No.: 4
* Assignment    : Program to demonstrate mmap and page faults
* Date          : 21/08/2025
* Group No.     : A3
* Team No.      : 09
* Roll No.      : 002311001004, 002311001011, 002311001049
* Name          : Soham Das, Sarbo Sarcar, Arnob Bhakta
* Details       : C program to allocate space for 8GB file using fallocate and perform read/write operations in random offsets
*
* fallocate function : pre-allocate space for 8GB file in disk 
*
* mmap function : maps the file to the process's address space(virtual address space)
*
* random read and write operations : triggers page faults and sar running in the background shows the number of page faults
*
* Input         : None
* Output        : goes for a infinite loop where it waits for 1 sec and writes a random character anywhere in the file and also reads it immediately ,if they match it continues doing so otherwise exits out of loop . 
* Press Ctrl-C to stop
*
*
* Compilation   : gcc A3_09_4.c -o A3_09_4
* Execution     : ./A3_09_4
*

== sample output ==

file bigfile created with size 8589934592
matched : OK at offset 0x57fabbd: value 87
matched : OK at offset 0x127015d6: value 207
matched : OK at offset 0x1c292b1cc: value 73
matched : OK at offset 0x1ccb050f2: value 28
matched : OK at offset 0x73b5b6f: value 192
matched : OK at offset 0x57ee0e24: value 74
matched : OK at offset 0x122c5d7df: value 208
matched : OK at offset 0x189681e75: value 175
matched : OK at offset 0x1518082ee: value 15
matched : OK at offset 0x204c8e4d: value 237
matched : OK at offset 0x139fb8b9d: value 171
matched : OK at offset 0x9ddd2d81: value 129
matched : OK at offset 0x127e4379: value 77
matched : OK at offset 0x14f86c688: value 63
matched : OK at offset 0x1633b1354: value 174
matched : OK at offset 0x165a140bc: value 210
matched : OK at offset 0x1fa56f96: value 177

******************************************************************************

 === sar command running in th background ===
$ sar -B 1

Linux 6.14.0-24-generic (user-pc)    08/21/2025      _x86_64_        (16 CPU)

07:42:56 PM  pgpgin/s pgpgout/s   fault/s  majflt/s  pgfree/s pgscank/s pgscand/s pgsteal/s    %vmeff
07:42:57 PM      0.00    728.00     71.00      0.00  19856.00      0.00      0.00      0.00      0.00
07:42:58 PM    128.00    156.00   1815.00      0.00   2588.00      0.00      0.00      0.00      0.00
07:42:59 PM      0.00      0.00    750.00      0.00    466.00      0.00      0.00      0.00      0.00
07:43:00 PM      0.00      0.00    305.00      1.00    257.00      0.00      0.00      0.00      0.00
07:43:01 PM      0.00      0.00   2134.00      1.00    591.00      0.00      0.00      0.00      0.00
07:43:02 PM    128.00    824.00    185.00      1.00    264.00      0.00      0.00      0.00      0.00
07:43:03 PM      0.00      0.00   1161.00      1.00    654.00      0.00      0.00      0.00      0.00
07:43:04 PM      0.00      8.00    119.00      1.00    231.00      0.00      0.00      0.00      0.00
07:43:05 PM    128.00     12.00     37.00      1.00    653.00      0.00      0.00      0.00      0.00
07:43:06 PM      0.00      0.00     24.00      1.00    603.00      0.00      0.00      0.00      0.00
07:43:07 PM      0.00     80.00     86.00      1.00     74.00      0.00      0.00      0.00      0.00
07:43:08 PM      0.00      0.00   1201.00      1.00    691.00      0.00      0.00      0.00      0.00
07:43:09 PM      0.00      0.00     19.00      1.00    147.00      0.00      0.00      0.00      0.00
07:43:10 PM    256.00      0.00     19.00      1.00     98.00      0.00      0.00      0.00      0.00
07:43:11 PM      0.00      0.00     41.00      1.00    224.00      0.00      0.00      0.00      0.00
07:43:12 PM      0.00    432.00    102.00      1.00    226.00      0.00      0.00      0.00      0.00
07:43:13 PM      0.00    676.00  31903.00      1.00  10377.00      0.00      0.00      0.00      0.00
07:43:14 PM      0.00      0.00  13593.00      1.00   6326.00      0.00      0.00      0.00      0.00
07:43:15 PM    128.00    600.00    845.00      1.00    900.00      0.00      0.00      0.00      0.00
07:43:16 PM      0.00    132.00     19.00      1.00    350.00      0.00      0.00      0.00      0.00
07:43:17 PM      0.00    144.00   2190.00      0.00   1331.00      0.00      0.00      0.00      0.00
07:43:18 PM    256.00      0.00   4833.00      0.00  32599.00      0.00      0.00      0.00      0.00
******************************************************************************

 */


#define _GNU_SOURCE // this header is important for fallocate
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<time.h>


#define CHAR_SIZE 256
#define endl printf("\n");

const char  *FILE_NAME  = "bigfile";
const off_t FILE_SIZE = 8LL * 1024 * 1024 * 1024;

int main(){
	int fd;
	fd = open(FILE_NAME, O_CREAT | O_RDWR, 0644); // rw-r-r permission
	if(fd==-1){
		perror("open");
		exit(EXIT_FAILURE);
	}

	if(fallocate(fd, 0,0, FILE_SIZE) !=0){
		perror("fallocate");
		close(fd);
		exit(EXIT_FAILURE);
	}
	printf("file %s created with size %lld \n" , FILE_NAME, (long long)FILE_SIZE);

	void * map = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE , MAP_SHARED, fd, 0);
	if(map == MAP_FAILED){
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	// seeding with system time
	srand(time(NULL));

	while(1){
		size_t rand_off = ((size_t)rand() <<31 | rand() )% FILE_SIZE;
		unsigned char rand_char = rand() % CHAR_SIZE;

		// writing into the file
		((unsigned char*)map)[rand_off] = rand_char;
		// reading from same location
		unsigned char read_byte = ((unsigned char*)map)[rand_off];

		if (rand_char != read_byte) {
			printf("Error at offset 0x%zx: expected %u, got %u\n", rand_off, rand_char, read_byte);
			break;
		}

		printf("matched : OK at offset 0x%zx: value %u\n", rand_off, rand_char);
		sleep(1);
	}

	// unmapping virtual memory
	if (munmap(map, FILE_SIZE) == -1){
		perror("unmapping failed\n");
		close(fd);
		exit(EXIT_FAILURE);
	}

	printf("umapped sucessfully\n");
	close(fd);

	return 0;
}
