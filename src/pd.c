/***************
*   Project: Práctica 1  Sistemas Operativos II 
*
*   Program name: pd.c
*
*   Author: Eduardo Eiroa Ballester
*
*   Date created: 25-02-2021
*
*   Porpuse: Removes Students Folder once manager receives a Control + C
*
*   Revision History: None
|***************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(void){
 
    if(system("rm -rf ../students")==-1){
    
        fprintf(stderr,"Error while removing students folder");
        exit(EXIT_FAILURE);
    }

}

