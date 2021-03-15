/***************
*   Project: Práctica 1  Sistemas Operativos II 
*
*   Program name: pc.c
*
*   Author: Eduardo Eiroa Ballester
*
*   Date created: 25-02-2021
*
*   Porpuse: Creates a file in which the minimum mark to pass an exam is written
*
*   Revision History: None
|***************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void readFile();
void createAndWriteFile(int neededMark,char dni[]);
void installSignalHandler();
void signalHandler(int signal_number);
int avarageMark;

int main(int argc, char* argv[]){
    
    installSignalHandler();
    readFile(0,12);
    //Writing to pipe as seen in page 52 of the textbook
    
    char mark[12];
    char aux=avarageMark+'0';
    sprintf(mark,"%d",avarageMark);
    write(atoi(argv[0]),mark,strlen(mark)+1);  

    return 0; 
}

//Method to read a file and parse its contents
void readFile(int aux,int j){
    
    
   
    FILE * fp = NULL;
    char * line = NULL;
    size_t len = 0;
    char dni[9];
    int i,previousMark,neededMark;
    int line_counter=0;
    fp = fopen("../src/estudiantes_p1.txt", "r");

    if( fp == NULL ) {
      perror("Error: ");
      exit(EXIT_FAILURE);
    }

    //Initialization of variables
    
    avarageMark=0;
    neededMark=0;
    int totalmark=0;

    while ((getline(&line, &len, fp)) != -1) {
        
        
        for(i=0; i<8;i++){
            dni[i]=line[i];
        }

        
        previousMark=atoi(&line[11]);

        //Calculation of needed mark for a student to pass the subject
        neededMark=10-previousMark;
        
        //Create and Write a file with the minimum needed mark for a student to pass the subject
        createAndWriteFile(neededMark,dni);

        //Aumento el contador para saber que cantidad de alumnos hay
        line_counter++;  // 1 alumno = 1 linea en el archivo

        //Calculating the summ of all student's marks.
        totalmark=totalmark+previousMark;
    }

    //Calculation of class avarage mark
    avarageMark=totalmark/line_counter;
    

    fclose(fp);

}

void createAndWriteFile(int neededMark,char dni[]){

    FILE *fptr;
    char route[256];
    sprintf(route,"../students/%s/minimumMark.txt",dni);
    /* open for writing */
    fptr = fopen(route, "w");

    //Troubleshoting wrong printing caused by using fprinf with a pointer to a file
    neededMark=neededMark+'0';

    if (fptr == NULL)
    {
        printf("Unable to create file\n");
        exit(EXIT_FAILURE);
    }

    //Writting to the file
    fprintf(fptr, "For passing this test you must score at least %c\n", neededMark);

    fclose(fptr);
}

void installSignalHandler(){

    if(signal(SIGINT,signalHandler)==SIG_ERR){
            printf("An error ocurred during signal handler installation at process PC with PID: %d",getpid());
            exit(EXIT_FAILURE);
        }

}

void signalHandler(int singal_number){

    printf("Process PC finished succesfully with PID: %d ",getpid());
    exit (EXIT_SUCCESS);
    
}