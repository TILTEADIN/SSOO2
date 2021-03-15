/***************
*   Project: Práctica 1 Sistemas Operativos II 
*
*   Program name: pb.c
*
*   Author: Eduardo Eiroa Ballester
*
*   Date created: 25-02-2021
*
*   Porpuse: Copy to students folder their corresponding exam
*
*   Revision History: None
|***************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void copyExamModel(char dni[9],char examtype);
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
    char examtype;
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
        examtype=line[9];

        //Calling method to copy the corresponding exam type
        copyExamModel(dni,examtype);
        
           
    }
    fclose(fp);

}

void copyExamModel(char dni[9], char examtype){

    char command[256];
    if(examtype==*"A"){

            sprintf(command,"cp ../MODELOSEXAMEN/MODELOA.pdf ../students/%s",dni);
            
            if (system(command)==-1) printf("Error whilst creating directory");
            
        }
        
        if(examtype==*"B"){
            

            sprintf(command,"cp ../MODELOSEXAMEN/MODELOB.pdf ../students/%s",dni);
            
            if (system(command)==-1) printf("Error whilst creating directory");
            
        }

        if(examtype==*"C"){
            

            sprintf(command,"cp ../MODELOSEXAMEN/MODELOC.pdf ../students/%s",dni);
            
            if (system(command)==-1) printf("Error whilst creating directory");
            
        }


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