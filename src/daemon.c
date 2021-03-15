/***************
*   Project: Práctica 1 Sistemas Operativos II 
*
*   Program name: daemon.c
*
*   Author: Eduardo Eiroa Ballester
*
*   Date created: 25-02-2021
*
*   Porpuse: Create Practica 1 backup
*
*   Revision History: None.
|***************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


int main(void){
    
    if(system("mkdir ../backup")==-1){

        fprintf(stderr,"Error while creating backup folder");
        
    }else{
        printf("Creating backup of Practica 1 on its parent directory");

    }

    while (1){

        if(system("cp -R ../* ../backup")==-1){
            fprintf(stderr,"Error while creating backup of Practica 1");
        }

        sleep(60); //Reapeats this action every 1 minute

    }


}
