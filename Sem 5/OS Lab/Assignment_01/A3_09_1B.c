/*************************************************************************************************
* Assignment No.: 1B
* Assignment    : Program to get and set environment variables using system calls
* Group No.	: A3
* Team No.	: 09
* Roll No.      : 002311001004, 002311001011, 002311001049
* Name          : Soham Das, Sarbo Sarcar, Arnob Bhakta
* Details       : A program to display several system environment variables and then
* 		  create and display two new custom environment variables.
* Input         : Two command-line arguments: a value for the new 'COURSE' variable
* 		  and a value for the new 'ROLL_NUMBER' variable.
* Output        : Prints a list of system variables and the newly set custom variables.
*
* Compilation   : gcc A3_09_1B.c -o 1b
* Execution     : ./1b <course_name> <roll_number>
* Example       : ./1b IT-OS-2027 002311001004
*
* Sample Input  :
* ./1b IT-OS-2027 002311001004
*
* Sample Output :
* --- Displaying System Environment Variables ---
* USER        : be2304
* HOME        : /home/usr/student/ug/yr23/be2304
* HOST        : (Not Set)
* ARCH        : (Not Set)
* DISPLAY     : (Not Set)
* PRINTER     : (Not Set)
* PATH        : /usr/lib64/qt-3.3/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/usr/student/ug/yr23/be2304/.local/bin:/home/usr/student/ug/yr23/be2304/bin
* ---------------------------------------------
*
* --- Setting Two New Environment Variables ---
* New variables have been set for this process:
* COURSE      : IT-OS-2027
* ROLL_NUMBER : 002311001004
* -------------------------------------------
*************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // An array of environment variables to display
    const char *sys_vars_to_get[] = {
        "USER", "HOME", "HOST", "ARCH", "DISPLAY", "PRINTER", "PATH"
    };
    int num_vars = sizeof(sys_vars_to_get) / sizeof(sys_vars_to_get[0]);

    printf("--- Displaying System Environment Variables ---\n");
    
    // Loop through the array and display each variable using getenv()
    	int i = 0;
	for (i = 0; i < num_vars; i++) {
        char *value = getenv(sys_vars_to_get[i]);
        // Print the variable and its value, or "(Not Set)" if it doesn't exist
        printf("%-10s: %s\n", sys_vars_to_get[i], value ? value : "(Not Set)");
    }
    printf("---------------------------------------------\n\n");

    // Check for the correct number of command-line arguments for setting new variables
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <course_name> <roll_number>\n", argv[0]);
        return 1; // Indicate error
    }

    const char *course_value = argv[1];
    const char *roll_number_value  = argv[2];

    printf("--- Setting Two New Environment Variables ---\n");

    // Set the first new variable and check for errors 
    if (setenv("COURSE", course_value, 1) != 0) {
        perror("setenv for COURSE failed");
        return 1;
    }

    // Set the second new variable and check for errors
    if (setenv("ROLL_NUMBER", roll_number_value, 1) != 0) {
        perror("setenv for ROLL_NUMBER failed");
        return 1;
    }

    printf("New variables have been set for this process:\n");
    printf("%-12s: %s\n", "COURSE", getenv("COURSE"));
    printf("%-12s: %s\n", "ROLL_NUMBER", getenv("ROLL_NUMBER"));
    printf("-------------------------------------------\n");

    return 0;  
}
