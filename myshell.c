/**
 * CS2106 AY22/23 Semester 2 - Lab 2
 *
 * This file contains function definitions. Your implementation should go in
 * this file.
 */

#include "myshell.h"

#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


/*******************************************************************************
 * Signal handler : ex4
 ******************************************************************************/

static void signal_handler(int signo) {

        // Use the signo to identy ctrl-Z or ctrl-C and print “[PID] stopped or print “[PID] interrupted accordingly.
        // Update the status of the process in the PCB table 

}



static void proc_update_status(/* pass necessary parameters*/) {


       /******* FILL IN THE CODE *******/

        // Call everytime you need to update status and exit code of a process in PCBTable

        // May use WIFEXITED, WEXITSTATUS, WIFSIGNALED, WTERMSIG, WIFSTOPPED


}


/*******************************************************************************
 * Built-in Commands
 ******************************************************************************/

static void command_info(/* pass necessary parameters*/) {

        /******* FILL IN THE CODE *******/


    // If option is 0
        //Print details of all processes in the order in which they were run. You will need to print their process IDs, their current status (Exited, Running, Terminating, Stopped)
        // For Exited processes, print their exit codes.
    // If option is 1
        //Print the number of exited process.
    // If option is 2
        //Print the number of running process.
    // If option is 3
        //Print the number of terminating process.
    // If option is 4
        //Print the number of stopped process.

    //For all other cases print “Wrong command” to stderr.


}

static void command_wait(/* pass necessary parameters*/) {

        /******* FILL IN THE CODE *******/


    // Find the {PID} in the PCBTable
    // If the process indicated by the process id is RUNNING, wait for it (can use waitpid()).
    // After the process terminate, update status and exit code (call proc_update_status())
    // Else, continue accepting user commands.

}


static void command_terminate(/* pass necessary parameters*/) {

        /******* FILL IN THE CODE *******/

    // Find the pid in the PCBTable
    // If {PID} is RUNNING:
        //Terminate it by using kill() to send SIGTERM
        // The state of {PID} should be “Terminating” until {PID} exits

}

static void command_fg(/* pass necessary parameters*/) {

        /******* FILL IN THE CODE *******/
        

    // if the {PID} status is stopped
        //Print “[PID] resumed”
        // Use kill() to send SIGCONT to {PID} to get it continue and wait for it
        // After the process terminate, update status and exit code (call proc_update_status())
}


/*******************************************************************************
 * Program Execution
 ******************************************************************************/

static void command_exec(char program[],char *args[],int args_count) {

        /******* FILL IN THE CODE *******/


    // check if program exists and is executable : use access()
    
    // if not executable
    if (access(program, F_OK | X_OK) == -1) {
        printf("%s not found\n",program);
        return;
    }
    // fork a subprocess and execute the program
    pid_t pid = fork();
    if (pid == 0) {
        // CHILD PROCESS


        // check file redirection operation is present : ex3
        
        // if < or > or 2> present: 
            // use fopen/open file to open the file for reading/writing with  permission O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC, O_SYNC and 0644
            // use dup2 to redirect the stdin, stdout and stderr to the files
            // call execv() to execute the command in the child process

        // else : ex1, ex2 
        // call execv() to execute the command in the child process

        execv(program,args);

        // Exit the child
        exit(0);


    } else {

        // PARENT PROCESS
        // register the process in process table

        // If  child process need to execute in the background  (if & is present at the end )
        //print Child [PID] in background

        // else wait for the child process to exit
        int status; 
        waitpid(pid, &status,0);
        
        // Use waitpid() with WNOHANG when not blocking during wait and  waitpid() with WUNTRACED when parent needs to block due to wait 
        while (waitpid(pid, &status, WNOHANG) == 0) {
            // Child process is still running
            printf("Child process still running\n");
            sleep(1);
        }

    }
}

/*******************************************************************************
 * Command Processor
 ******************************************************************************/

static void command(char command_str[],char *args[],int args_count) {


    /******* FILL IN THE CODE *******/
    // printf("command %s\n",command_str);
    // for (int i = 0; i < args_count; i++)
    // {
    //     printf("args: %s\n", args[i]);
    // }
    
    // if command is "info" call command_info()             : ex1
    // if command is "wait" call command_wait()             : ex2
    // if command is "terminate" call command_terminate()   : ex2
    // if command is "fg" call command_fg()                 : ex4

    // call command_exec() for all other commands           : ex1, ex2, ex3
    if(strcmp(command_str,"info") == 0 ){

    } else if (strcmp(command_str,"wait") == 0){

    } else if (strcmp(command_str,"terminate") == 0){
        
    } else if (strcmp(command_str,"fg") == 0){
        
    } else{
        command_exec(command_str,args,args_count);
    }

}

/*******************************************************************************
 * High-level Procedure
 ******************************************************************************/

void my_init(void) {

           /******* FILL IN THE CODE *******/

        // use signal() with SIGTSTP to setup a signalhandler for ctrl+z : ex4
        // use signal() with SIGINT to setup a signalhandler for ctrl+c  : ex4

        // anything else you require

}

void my_process_command(size_t num_tokens, char **tokens) {


        /******* FILL IN THE CODE *******/

        // Split tokens at NULL or ; to get a single command (ex1, ex2, ex3, ex4(fg command))

        // for example :  /bin/ls ; /bin/sleep 5 ; /bin/pwd
        // split the above line as first command : /bin/ls , second command: /bin/sleep 5 and third command:  /bin/pwd
        // Call command() and pass each individual command as arguements
        size_t i;
        char *token, *temp="", *delimiters = ";";
        char *first_cmd_token="";
        char *args[] = {};
        int args_count = 0; 

        for (i = 0; i < num_tokens; i++) {
            token = tokens[i];

            if(token == NULL || strcmp(token, ";") == 0 ){
                command(first_cmd_token,args,args_count);
                // reset args and token
                for (int i = 0; i < args_count; i++){
                    args[i] = "";
                }
                args_count = 0;
                first_cmd_token = "";
            } else{
                if(!strcmp(first_cmd_token, "") == 0){
                    args[args_count++] = token;
                } else {
                    first_cmd_token = token;
                    args[args_count++] = first_cmd_token;
                }
            }
        }
        
}

void my_quit(void) {


    /******* FILL IN THE CODE *******/
    // Kill every process in the PCB that is either stopped or running



    printf("\nGoodbye\n");
}
