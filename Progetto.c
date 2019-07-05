#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char buff[100];
void Addent();
void Delent();
void Addrel();
void Delrel();
void Report();


int main () {
 do {
    scanf("%s",buff);
    if (strcmp(buff,"addent")==0){
      Addent();
    }
    if (strcmp(buff,"delent")==0){
      Delent();
    } 
    if (strcmp(buff,"addrel")==0){
      Addrel();
    } 
    if (strcmp(buff,"delrel")==0){
      Delrel();
    }
    if (strcmp(buff,"report")==0){
      Report();
    }
 } while (strcmp(buff,"end")!=0);
}


void Addent(){
  scanf("%s",buff);
  char *id = (char *) malloc(strlen(buff) * sizeof (char));
  id=buff;
  printf("%s",id);
}



void Delent(){
}



void Addrel(){
}



void Delrel(){
}



void Report(){
}


