#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct Nodo {
  struct Nodo *r;
  struct Nodo *l;
  struct Nodo *p;
  char *key;
  bool c;
} Nodo;

typedef Nodo *punt;

punt root= NULL;
punt tnil;
void inizializza(punt p);
punt newnode();
void insert();
void delete();
void search();
void InsertFixup(punt z);
void RightRotate(punt x);
void LeftRotate(punt x);
char buff[100000];

int main(){
  tnil==malloc(sizeof(Nodo));
  tnil->r=NULL;
  tnil->l=NULL;
  tnil->c=false;
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

  y=tnil;
  x=root;
  while (x!=tnil){
    y=x;
    if (strcmp(new->key,x->key)<0) x=x->l;
    else x=x->r;  
  }
  new->p=y;
  if (y==tnil) root=new;
  else if(strcmp(new->key,y->key)<0) y->l=new;
  else y->r=new;
  new->c=true;
  InsertFixup(new);
}


void InsertFixup(punt z){
  punt y,x;
  while (z->p->c==true){
    if((z->p)==(z->p->p->l)){
      y=z->p->p->r;
      if (y->c=true){
	z->p->c=false;
	y->c=false;
	z->p->p->c=true;
	z=z->p->p;
      }
      else {
	if (z==z->p->r){
	    z=z->p;
	    LeftRotate(z);}
	z->p->c=false;
	z->p->p->c=true;
	RightRotate(z->p->p);
      }
    }
    else {
      y=z->p->p->l;
      if (y->c=true){
	z->p->c=false;
	y->c=false;
	z->p->p->c=true;
	z=z->p->p;
      }
      else {
	if (z==z->p->l){
	    z=z->p;
	    RightRotate(z);}
	z->p->c=false;
	z->p->p->c=true;
	LeftRotate(z->p->p);
      }
    }
      
  }
  root->c=false;
  tnil->c=false;
}

void LeftRotate(punt x){
  punt y;
  if (x->r!=tnil){
  y=x->r;
  x->r=y->l;
  if (y->l!=tnil) y->l->p=x;
  y->p=x->p;
  if (x->p==tnil) root=y;
  else if (x==x->p->l) x->p->l=y;
  else x->p->r=y;
  y->l=x;
  x->p=y;
  }
}

void RightRotate(punt x){
   punt y;
  if (x->l!=tnil){
  y=x->l;
  x->l=y->r;
  if (y->r!=tnil) y->r->p=x;
  y->p=x->p;
  if (x->p==tnil) root=y;
  else if (x==x->p->r) x->p->r=y;
  else x->p->r=y;
  y->r=x;
  x->p=y;
  }
}


void inizializza(punt p){
  p->r=tnil;
  p->l=tnil;
  p->p=tnil;
}

punt newnode(){
  punt new= malloc(sizeof(Nodo));
  inizializza(new);
  return new;
}

void delete(){}
void search(){}
