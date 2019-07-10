#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define COUNT 10
typedef struct Tiporel{
  char *nomerel;
  struct Tiporel *n;
} Tiporel;

typedef Tiporel *tr;

typedef struct Nodo {
  struct Nodo *r;
  struct Nodo *l;
  struct Nodo *p;
  struct Rel *myrel;
  char *key;
  bool c;
} Nodo;

typedef Nodo *punt;

typedef struct Rel {

  char *nome;
  struct Rel *next;
  int cont;
  punt root;
} Rel;

typedef Rel *list;
tr tipi=NULL;
punt tnil=NULL; 
punt rootent=NULL;
bool flag=false;
void inizializza(punt p);
void initrel(list p);
punt newnode();
void insert(punt *root);
void delete(punt z,punt root);
punt search(punt x);
void InsertFixup(punt z,punt *root);
void DeleteFixup(punt x,punt root);
void RBTransplant(punt u,punt v,punt root);
punt TreeMin(punt x);
void RightRotate(punt x,punt *root);
void LeftRotate(punt x,punt *root);
void InOrderWalk(punt start);
void print2DUtil(punt root, int space);
void print2D(punt root);
char buff[100000];
void Addent();
bool relexists();
void addnewrel();
void Delent();
void Addrel();
void Delrel();
void Report();

int main () {
  tnil=malloc(sizeof(Nodo));
  tnil->r=NULL;
  tnil->l=NULL;
  tnil->c=false;
  rootent=tnil;
  list  iter;
 do {
    scanf("%s",buff);
    if (strcmp(buff,"addent")==0){
      scanf("%s",buff);
      insert(&rootent);
    }
    if (strcmp(buff,"print")==0){
      print2D(rootent);
    }
    if (strcmp(buff,"printsott")==0){
      iter=rootent->myrel;
      while (iter!=NULL){
      print2D(iter->root);
      iter=iter->next;
      }
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


void Delent(){
  scanf("%s",buff);
  char *id1 = (char *) malloc(strlen(buff) * sizeof (char));
  strcpy(id1,buff);
}



void Addrel(){
  punt f;
  list x,y;
  flag=false;
  scanf("%s",buff);
  f=search(rootent);
  if (f==tnil) return;
  char *id1 = (char *) malloc(strlen(buff) * sizeof (char));
  strcpy(id1,buff);
  scanf("%s",buff);
  f=search(rootent);
  if (f==tnil)return;
  scanf("%s",buff);
  if (!relexists()) addnewrel();
  if (f->myrel==NULL) {
    f->myrel=malloc(sizeof(Rel));
    initrel(f->myrel);
    f->myrel->next=NULL;
    x=f->myrel;
  }
  else{
    x=f->myrel;
    y=f->myrel;
    if (x==f->myrel && strcmp(buff,x->nome)<0) {
      x=malloc(sizeof(Rel));
      initrel(x);
      x->next=f->myrel;
      f->myrel=x;
    }
    else{
      while ( x!=NULL && strcmp(buff,x->nome)>0){
	  y=x;
	  x=x->next;
	}
      if (x==NULL || strcmp(buff,x->nome)!=0){
	x=malloc(sizeof(Rel));
	initrel(x);
	x->next=y->next;
	y->next=x;
      }
      }
    }
  strcpy(buff,id1);
  free(id1);
  insert(&(x->root));
  if (flag) x->cont++;
}



void Delrel(){
  scanf("%s",buff);
  char *id1 = (char *) malloc(strlen(buff) * sizeof (char));
  strcpy(id1,buff);
  scanf("%s",buff);
  char *id2 = (char *) malloc(strlen(buff) * sizeof (char));
  strcpy(id2,buff);
  scanf("%s",buff);
  char *idrel = (char *) malloc(strlen(buff) * sizeof (char));
  strcpy(idrel,buff);
}



void Report(){
}



		  /*int main(){

  punt f;
  while (true){
  scanf("%s",buff);
  if (strcmp(buff,"insert")==0) insert();
  if (strcmp(buff,"delete")==0) {
    scanf("%s",buff);
    f= search(root);
    if (f!=tnil) delete(f);
  }
  
  if (strcmp(buff,"search")==0) {
    scanf("%s",buff);
    f=search(root);
  }
  if (strcmp(buff,"visit")==0) InOrderWalk(root);
  if (strcmp(buff,"end")==0) exit(0);
  if (strcmp(buff,"print")==0) print2D(root);
  
  
  }
}
		  */

void insert(punt *root){
  punt y,x;
  punt new;
  y=search(*root);
  if (y!=tnil) return;
  flag=true;
  new=newnode();
  new->key= (char *) malloc(strlen(buff) * sizeof (char));
  strcpy(new->key,buff);
  y=tnil;
  x=*root;
  while (x!=tnil){
    y=x;
    if (strcmp(new->key,x->key)<0) x=x->l;
    else x=x->r;  
  }
  new->p=y;
  if (y==tnil) *root=new;
  else if(strcmp(new->key,y->key)<0) y->l=new;
  else y->r=new;
  new->c=true;
  InsertFixup(new,root);
}


void InsertFixup(punt z,punt *root){
  punt y,x;
  while (z->p->c==true){
    if((z->p)==(z->p->p->l)){
      y=z->p->p->r;
      if (y->c==true){
	z->p->c=false;
	y->c=false;
	z->p->p->c=true;
	z=z->p->p;
      }
      else {
	if (z==z->p->r){
	    z=z->p;
	    LeftRotate(z,root);}
 	z->p->c=false;
	z->p->p->c=true;
	RightRotate(z->p->p,root);
      }
    }
    else {
      y=z->p->p->l;
      if (y->c==true){
	z->p->c=false;
	y->c=false;
	z->p->p->c=true;
	z=z->p->p;
      }
      else {
	if (z==z->p->l){
	    z=z->p;
	    RightRotate(z,root);}
	z->p->c=false;
	z->p->p->c=true;
	LeftRotate(z->p->p,root);
      }
    }
      
  }
  (*root)->c=false;
  tnil->c=false;
}

void LeftRotate(punt x,punt *root){
  punt y;
  if (x->r!=tnil){ 
  y=x->r;
  x->r=y->l;
  if (y->l!=tnil) y->l->p=x;
  y->p=x->p;
  if (x->p==tnil) *root=y;
  else if (x==x->p->l) x->p->l=y;
  else x->p->r=y;
  y->l=x;
  x->p=y;
  }
}

void RightRotate(punt x,punt *root){
   punt y;
  if (x->l!=tnil){
  y=x->l;
  x->l=y->r;
  if (y->r!=tnil) y->r->p=x;
  y->p=x->p;
  if (x->p==tnil) *root=y;
  else if (x==x->p->r) x->p->r=y;
  else x->p->l=y;
  y->r=x;
  x->p=y;
  }
}


void inizializza(punt p){
  p->r=tnil;
  p->l=tnil;
  p->p=tnil;
  p->myrel=NULL;
}

void initrel(list p){
  p->nome=(char *)malloc(sizeof(char)*strlen(buff));
  strcpy(p->nome,buff);
  p->cont=0;
  p->root=tnil;
}

punt newnode(){
  punt new= malloc(sizeof(Nodo));
  inizializza(new);
  return new;
}
/*
void delete(punt z,punt root){
  if (z==NULL) return;
  punt y,x;
 y=z;
 bool yoc= y->c;
 if (z->l==tnil){
   x=z->r;
   RBTransplant(z,z->r,root);			
 }
 else if (z->r==tnil) {
   x=z->l;
   RBTransplant(z,z->l,root);
 }
 else {
   y=TreeMin(z->r);
   yoc= y->c;
   x= y->r;
   if (y->p==z) x->p=y;
   else {
     RBTransplant(y,y->r,root);
     y->r=z->r;
     y->r->p=y;
   }
   RBTransplant(z,y,root);
   y->l=z->l;
   y->l->p=y;
   y->c=z->c;
 }
 if (yoc==false) DeleteFixup(x,root);
 free(z->key);
 free(z);
}

void DeleteFixup(punt x,punt root){
  punt w;
  while (x!=root && x->c==false){
    if (x==x->p->l){
      w=x->p->r;
      if (w->c==true){
	w->c=false;
	x->p->c=true;
	LeftRotate(x->p,root);
	w=x->p->r;	
      }
      if (w->l->c==false && w->r->c==false){
	w->c=true;
	x=x->p;
      }
      else {
	if (w->r->c==false){
	w->l->c=false;
	w->c=true;
	RightRotate(w,root);
	w=x->p->r;
	}
	w->c=x->p->c;
	x->p->c=false;
	w->r->c=false;
	LeftRotate(x->p,root);
	x=root;
      }
    }
    else{
         w=x->p->l;
      if (w->c==true){
	w->c=false;
	x->p->c=true;
	RightRotate(x->p,root);
	w=x->p->l;	
      }
      if (w->r->c==false && w->l->c==false){
	w->c=true;
	x=x->p;
      }
      else {
	if (w->l->c==false){
	w->r->c=false;
	w->c=true;
	LeftRotate(w,root);
	w=x->p->l;
	}
	w->c=x->p->c;
	x->p->c=false;
	w->r->c=false;
	RightRotate(x->p,root);
	x=root;
      } 
    }
  }
  x->c=false;
  }*/
punt search(punt x){
  if (x==tnil || strcmp(buff,x->key)==0) return x;
  if (strcmp(buff,x->key)<0) return search(x->l);
  else return search(x->r);
}

void InOrderWalk(punt start){
  if (start!=tnil){
  InOrderWalk(start->l);
  printf("%s colore: %d \n",start->key,start->c);
  InOrderWalk(start->r);
  }
}

void RBTransplant(punt u,punt v,punt root){
  if (u->p==tnil) root=v;
  else if (u==u->p->l) u->p->l=v;
  else u->p->r= v;
  v->p=u->p;
}

punt TreeMin(punt x){
  while (x->l!=tnil) x=x->l;
  return x;
}

bool relexists(){
  tr iter=tipi;
  while (iter!=NULL){
    if (strcmp(buff,iter->nomerel)==0) return true;
    iter=iter->n;
  }
  return false;
}

void addnewrel(){
  tr iter=tipi;
  while (iter!=NULL && iter->n!=NULL ) {
    iter=iter->n;}
  if (iter==NULL){
    tipi=malloc(sizeof(Tiporel));
    tipi->nomerel=(char *)malloc(sizeof(char)*strlen(buff));
    strcpy(tipi->nomerel,buff);
  }
    else {
   iter->n=malloc(sizeof(Tiporel));
   iter->n->nomerel=(char *)malloc(sizeof(char)*strlen(buff));
   strcpy(iter->n->nomerel,buff);
  }
  }

void print2DUtil(punt root, int space)  
{  
    // Base case  
    if (root == tnil)
        return;  
  
    // Increase distance between levels  
    space += COUNT;  
  
    // Process right child first  
    print2DUtil(root->r, space);  
  
    // Print current node after space  
    // count  
    printf("\n");  
    for (int i = COUNT; i < space; i++)  
      printf(" ");
    printf("%s  %d\n",root->key,root->c);  
  
    // Process left child  
    print2DUtil(root->l, space);  
}  
  
// Wrapper over print2DUtil()  
void print2D(punt root)  
{
    // Pass initial space count as 0  
    print2DUtil(root, 0);  
}  

