/********************************************************************
CSCI 480 - Assignment 2- Spring 2021

Progammer: Cortland Ervins
Section:   0001
Date Due:  2/15/21

Purpose: Functional microshell that accepts unix and some special
commands

*********************************************************************/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h> 
#include <cstring>
#include <iostream>
#include "ls_sys.h"
/****************************************************************

   FUNCTION:   main

   ARGUMENTS:  N/A

   RETURNS:    0

   NOTES:      Runs the microshell, until 'quit' is entered
****************************************************************/
int main(void){
    //Input buffer
    char buf[1024];
    // for ls_sys command
    char ls_sys[] = "ls_sys";
    //for fcfs command
    char fcfs[] = "fcfs";
    //Holds the number of processes for fcfs
    int process_num = 0;
    
    pid_t pid;
    int status;

    //Used to put command into command array
    char* ptr;
    int number = 0;

    //Holds the command, command and args are seperated
    char *command[1024];

    printf("myshell>");

    while(fgets(buf, 1024, stdin) != NULL){
        buf[strlen(buf) -1] = 0;
        
        command[0]=strtok(buf," ");

        //Puts command into command array
        while((ptr=strtok(NULL, " ")) != NULL){ 
                number++;
                command[number]= ptr; 
            }
        command[number+1] = NULL;
        number = 0;

        if(strcmp(command[0], "quit") == 0){
            exit(0);
        }    

        //pid < 0 = error
        if ( pid < 0){
            printf("fork error");
        }

        //pid  = 0, does the thing that was passed to it
        else if((pid = fork()) == 0) { //child

            //Prints out all the OS/Processor information
            if(strcmp(command[0], ls_sys) == 0){
                OS_Questions();

                Processor_Questions();
    
                Processor_1_Questions();

                Swap_Question();

                exit(0);
            }
            
            else if(strcmp(command[0], fcfs) == 0){
                if(command[1] == NULL ){
                    process_num = 5;
                }
                //if number was passed, set process_num to that number
                else{
                    process_num = atoi(command[1]);
                    std::cout << process_num << std::endl;
                }

                //Makes array for cpu bursts
                int *cpu_bursts = new int[process_num];

                //sets seed for rand() to 10
                std::srand(10);


                //fills cpu_bursts will numbers
                for(int i = 0; i < process_num; i++){
                    cpu_bursts[i] = rand() % 100 +1;
                }

                std::cout << "FCFS CPU scheduling simulation with " << process_num << " processes." << std::endl;
                //Prints out cpu_bursts numbers
                for(int i = 0; i < process_num; i++){
                    std::cout << "CPU burst: " << cpu_bursts[i] << " ms" << std::endl;
                }
                
                //calculates the total wait time
                int wait_total = 0;
                for(int i = 0; i < process_num -1; i++){
                    wait_total += cpu_bursts[i];
                                
                    for(int z = 0; z < i; z++){
                        wait_total += cpu_bursts[z];
                    }
                    
                }

                std::cout << "Total waiting time in the ready queue: " << wait_total << " ms" << std::endl;
                //calculates the average wait time
                int wait_average = wait_total/ process_num;

                std::cout << "Average waiting time in the ready queue: " << wait_average << " ms" << std::endl;


                exit(1);

            }
            else{
            //executes command if no special command was given    
            execvp(command[0], command);
            printf("couldn't execute: %s", buf);
            std::cout << std::endl;
            exit(127);
            }
        }

        //waiting for command

        //parent
        if((pid = waitpid(pid, &status, 0)) < 0){
            printf("waitpid error");
        }

        printf("myshell>");
    }

    exit(0);
}