/*************************************************************************************************
* Assignment No.: 2A
* Assignment    : Program to catch the sinal SIGINT and display message with using perror.
* Date          : 05/08/2025
* Group No.     : A3
* Team No.      : 09
* Roll No.      : 002311001004, 002311001011, 002311001049
* Name          : Soham Das, Sarbo Sarcar, Arnob Bhakta
* Details       : Program catches the signal SIGINT and display “Ha Ha, Not Stopping”.  
* it uses the signal system call. 
* it also uses perror to check the return status of a library/system call.
* Input         : None
* Output        : goes for a infinite loop where it waits for 1 sec and prompts "try hit ctrl-c"
* if we hit ctrl-c then it shows "Ha Ha , Not Stopping"
*
* in order to stop the program we have to kill it's process from another terminal with the following command
* pkill -9 A3_09_2A
*
* Compilation   : gcc A3_09_2A.c -o A3_09_2A
* Execution     : ./A3_09_2A
*
* Sample Input  :
* ./A3_09_2A
*
* Sample Output :
* try hitting C-c
* try hitting C-c
* ^C
* Ha Ha, Not Stopping
* 
* try hitting C-c
* try hitting C-c
* ^C
* Ha Ha, Not Stopping
* 
* try hitting C-c
* try hitting C-c
* try hitting C-c
* try hitting C-c
* try hitting C-c
* try hitting C-c
* try hitting C-c
* try hitting C-c
* try hitting C-c
* try hitting C-c
* try hitting C-c
* try hitting C-c
* zsh: killed
*
*************************************************************************************************/
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig) { printf("\nHa Ha, Not Stopping\n\n"); }

int main() {
  __sighandler_t result = signal(SIGINT, handler);
  if (result == SIG_ERR) {
    perror("\nerror installing handler for SIGINT\n");
  }
  while (1) {
    printf("try hitting C-c\n");
    int res = sleep(1);
    if (res != 0) {
      printf("\n Sleep was interrupted with %d seconds remaining\n", res);
    }
  }
  return 0;
}
