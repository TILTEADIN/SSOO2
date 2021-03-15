/***************
*   Project: Práctica 1 Sistemas Operativos II 
*
*   Program name: manager.c
*
*   Author: Eduardo Eiroa Ballester
*
*   Date created: 25-02-2021
*
*   Porpuse: Synchronize processes and create the corresponding ones
*
*   Revision History: None.
|***************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>


#define PATH_A "./bin/pa"
#define PATH_B "./bin/pb"
#define PATH_C "./bin/pc"
#define PATH_D "./bin/pd"

#define WRITE_PIPE 1
#define READ_PIPE 0



pid_t p_list[4]; // process list that will allocate PA PB PC and PD
enum proceskind {pa=0,pb=1,pc=2,pd=3}; //enum so I can use pa,pb, etc as p_list index, helps with readeability


void cleanUp();
struct tm* getTime();
void installSignalHandler();
void signalHandler(int signal_number);
void createAndWriteLog(char buffer[]);
pid_t createProcess(char path[],char r_pipe[256]);
void waitNumberProcesses(int processes_ammount);
void readPipe(int pipe_fd [2]);
void killProcesses();


int main(void){   

    
    
    char buffer[256];
    char r_pipe[256];
    int pipe_fd [2];
    pipe(pipe_fd);
    sprintf(r_pipe,"%d",pipe_fd[READ_PIPE]);


    installSignalHandler();   
    //Writing event to log
    sprintf(buffer,"\nINITIALIZING LOG\n____________________\n");
    createAndWriteLog(buffer);

    //Launching PA
    p_list[pa]=createProcess(PATH_A,r_pipe);
    waitNumberProcesses(1);

    //Writting event to log
    sprintf(buffer,"Process A has succesfully finished its execution");
    createAndWriteLog(buffer);

    //Launching PB
    p_list[pb]=createProcess(PATH_B,r_pipe);
    p_list[pc]=createProcess(PATH_C,r_pipe);
    

    sleep(2);

    waitNumberProcesses(2);

    readPipe(pipe_fd);


    close(pipe_fd[0]);
    close(pipe_fd[1]);

    return  EXIT_SUCCESS;


    
}

void createAndWriteLog(char buffer[]){

    FILE *fptr;

    // fopen with mode "a" allows to append, if the file doesnt exist it will create it.
    if((fptr = fopen("../log.txt", "a"))==NULL){

        fprintf(stdout,"Error while creating log file: %d\n",errno);
        exit(EXIT_FAILURE);

    }else{
        char time_string[256];
        
        struct tm* time;
        time=getTime();
        //format time in a proper way if possible
        sprintf(time_string,"%d:%d:%d",time->tm_hour,time->tm_min,time->tm_sec);
        fprintf(fptr,"%s ----> %s\n" , time_string, buffer);
    }

    fclose(fptr);
}

pid_t createProcess(char path[],char r_pipe[]){
    pid_t pid;

    switch(pid=fork()){

        case -1:
            //Error, log it and exit execution
            exit(EXIT_FAILURE);
        case 0:
            // Child process
            

            if (path=="./pc"){

                execl(path,path,r_pipe);
            
            }else{

                if(execl(path,path,NULL)==-1){
                fprintf(stderr,"Error while creating process : %d\n",errno);
                exit(EXIT_FAILURE);
                }

            }
                
    }

    return pid;
}

struct tm* getTime(){

    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
  
    return timeinfo;
}


void cleanUp(){

    //deletes previous log file execution
    system("rm log.txt");


}

void installSignalHandler(){

    if(signal(SIGINT,signalHandler)==SIG_ERR){
            printf("An error ocurred during signal handler installation at process Manager with PID: %d\n",getpid());
            exit(EXIT_FAILURE);
    }

}

void signalHandler(int signo){

    killProcesses();
    createProcess(PATH_D,NULL);
    wait(NULL);
  
	char buffer [256];
    sprintf(buffer,"Manager process manually interrupted by a SIGINT\n");
    createAndWriteLog(buffer);
    
  
	exit(EXIT_SUCCESS);
}

void waitNumberProcesses(int processes_ammount){
    
    pid_t pid;
    if (processes_ammount>0){

        pid=wait(NULL);

        //Clearing process PID from process table
        if(pid==p_list[pa]) p_list[pa]=0;
        if(pid==p_list[pb]) p_list[pb]=0;
        if(pid==p_list[pc]) p_list[pc]=0;
        if(pid==p_list[pd]) p_list[pd]=0; 
        
        //Decrement of the process number
        processes_ammount--;
    }   
}

void killProcesses(){
    pid_t pid;
    char buffer[256];
    int arrsize,i;
    arrsize=(int)sizeof(p_list)/(int)sizeof(p_list[0]);
    //determining 

    for(i=0;i>arrsize;i++){

        if(p_list[i]!=0){

            sprintf(buffer,"Killing proccess with PID %d",p_list[i]);
            createAndWriteLog(buffer);

            if(kill(p_list[i],SIGINT)==-1){
                sprintf(buffer,"Killing proccess with PID %d resulted in an error",p_list[i]);
                createAndWriteLog(buffer);
            }
        }
    }
}

void readPipe(int pipe_fd[2]){

    char buffer[256];
    char aux[256]; //Auxiliary buffer to help format printing

    read(pipe_fd[READ_PIPE],buffer,sizeof(buffer));
    sprintf(aux,"Avarage Mark of the class is %s",buffer);
    createAndWriteLog(aux);
}






