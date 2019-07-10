#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define COUNT 10

typedef struct Nodo {
  struct Nodo *r;
  struct Nodo *l;
  struct Nodo *p;
  char *key;
  bool c;
} Nodo;

typedef Nodo *punt;

punt tnil=NULL; 
punt root=NULL;
void inizializza(punt p);
punt newnode();
void insert();
void delete(punt z);
punt search(punt x);
void InsertFixup(punt z);
void DeleteFixup(punt x);
void RBTransplant(punt u,punt v);
punt TreeMin(punt x);
void RightRotate(punt x);
void LeftRotate(punt x);
void InOrderWalk(punt start);
void print2DUtil(punt root, int space);
void print2D(punt root);
char buff[100000];

int main(){
  tnil=malloc(sizeof(Nodo));
  tnil->r=NULL;
  tnil->l=NULL;
  tnil->c=false;
  root=tnil;
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
      if (y->c==true){
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
      if (y->c==true){
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
  else x->p->l=y;
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

void delete(punt z){
  punt y,x;
 y=z;
 bool yoc= y->c;
 if (z->l==tnil){
   x=z->r;
   RBTransplant(z,z->r);			
 }
 else if (z->r==tnil) {
   x=z->l;
   RBTransplant(z,z->l);
 }
 else {
   y=TreeMin(z->r);
   yoc= y->c;
   x= y->r;
   if (y->p==z) x->p=y;
   else {
     RBTransplant(y,y->r);
     y->r=z->r;
     y->r->p=y;
   }
   RBTransplant(z,y);
   y->l=z->l;
   y->l->p=y;
   y->c=z->c;
 }
 if (yoc==false) DeleteFixup(x);
 free(z);
}

void DeleteFixup(punt x){
  punt w;
  while (x!=root && x->c==false){
    if (x==x->p->l){
      w=x->p->r;
      if (w->c==true){
	w->c=false;
	x->p->c=true;
	LeftRotate(x->p);
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
	RightRotate(w);
	w=x->p->r;
	}
	w->c=x->p->c;
	x->p->c=false;
	w->r->c=false;
	LeftRotate(x->p);
	x=root;
      }
    }
    else{
         w=x->p->l;
      if (w->c==true){
	w->c=false;
	x->p->c=true;
	RightRotate(x->p);
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
	LeftRotate(w);
	w=x->p->l;
	}
	w->c=x->p->c;
	x->p->c=false;
	w->r->c=false;
	RightRotate(x->p);
	x=root;
      } 
    }
  }
  x->c=false;
}
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

void RBTransplant(punt u,punt v){
  if (u->p==tnil) root=v;
  else if (u==u->p->l) u->p->l=v;
  else u->p->r= v;
  v->p=u->p;
}

punt TreeMin(punt x){
  while (x->l!=tnil) x=x->l;
  return x;
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
