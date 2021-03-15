/***************
*   Project: Práctica 1 Sistemas Operativos II 
*
*   Program name: pa.c
*
*   Author: Eduardo Eiroa Ballester
*
*   Date created: 25-02-2021
*
*   Porpuse: Create students folders
*
*   Revision History: None.
|***************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void readFile();
void installSignalHandler();
void signalHandler(int signal_number);


int main(void){

    installSignalHandler();
    readFile(0,10);
    return 0;
}


//Method to read a file and parse its contents
void readFile(int aux,int j){
    
    FILE * fp = NULL;
    char * line = NULL;
    size_t len = 0;
    char dni[9];
    char command [256];
    int i;

    fp = fopen("../src/estudiantes_p1.txt", "r");
    
    if( fp == NULL ) {
      perror("Error: ");
      exit(EXIT_FAILURE);
    }

    while ((getline(&line, &len, fp)) != -1) {
        
        
        for(i=0; i<8;i++){
            dni[i]=line[i];
        }
        
        sprintf(command,"mkdir -p ../students/%s",dni);
            
        if (system(command)==-1) printf("Error whilst creating directory");
        
           
    }
    fclose(fp);

}

void installSignalHandler(){

    if(signal(SIGINT,signalHandler)==SIG_ERR){
            printf("An error ocurred during signal handler installation at process PB with PID: %d",getpid());
            exit(EXIT_FAILURE);
        }

}

void signalHandler(int singal_number){

    printf("Process PB finished succesfully with PID: %d ",getpid());
    exit (EXIT_SUCCESS);
    
}