#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
char buff[100000];
void insert();
void delete();
void search();

typedef struct Nodo {
  struct Nodo *r;
  struct Nodo *l;
  struct Nodo *p;
  char *key;
  bool c;
} Nodo;

typedef Nodo *punt;

punt root= NULL;

void inizializza(punt p);
punt newnode();
int main(){
  scanf("%s",buff);
  if (strcmp(buff,"insert")==0) insert();
  if (strcmp(buff,"delete")==0) delete();
  if (strcmp(buff,"search")==0) search();
}

void insert(){
  punt y,x;
  punt new=newnode();
  scanf("%s",buff);
  new->key= (char *) malloc(strlen(buff) * sizeof (char));
  strcpy(new->key,buff);

  y=NULL;
  x=root;
  while (x!=NULL){
    y=x;
    if (strcmp(new->key,x->key)<0) x=x->l;
    else x=x->r;  
  }
  new->p=y;
  if (y==NULL) root=new;
  else if(strcmp(new->key,y->key)<0) y->l=new;
  else y->r=new;
  new->c=true;
  
}

void inizializza(punt p){
  p->r=NULL;
  p->l=NULL;
  p->p=NULL;
}

punt newnode(){
  punt new= malloc(sizeof(Nodo));
  inizializza(new);
  return new;
}

void delete(){}
void search(){}
