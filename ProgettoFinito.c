#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define COUNT 10

typedef struct max{
  struct Nodo *ent;
  struct max *next;
} max;

typedef struct Tiporel{
  char *nomerel;
  max *best;
  int cont;
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


typedef struct Ist {
  struct Ist *r;
  struct Ist *l;
  struct Ist *p;
  punt mitt;
  bool c;
} Ist;

typedef Ist *ista;



typedef struct Rel {

  char *nome;
  struct Rel *next;
  int cont;
  ista root;
} Rel;

typedef Rel *list;

tr tipi=NULL;
punt tnil=NULL; 
ista tnil2=NULL;
punt rootent=NULL;
bool flag=false;
char buff[100000];

punt newnode();
punt search(punt x);
punt TreeMin(punt x);
void insert(punt *root);
void delete(punt z,punt *root);
void InsertFixup(punt z,punt *root);
void DeleteFixup(punt x,punt *root);
void RBTransplant(punt u,punt v,punt *root);
void RightRotate(punt x,punt *root);
void LeftRotate(punt x,punt *root);
void inizializza(punt p);

ista newnode2();
ista search2(ista x);
ista TreeMin2(ista x);
void insert2(ista *root,punt m);
void delete2(ista z,ista *root);
void InsertFixup2(ista z,ista *root);
void DeleteFixup2(ista x,ista *root);
void RBTransplant2(ista u,ista v,ista *root);
void RightRotate2(ista x,ista *root);
void LeftRotate2(ista x,ista *root);
void inizializza2(ista p);

bool relexists();
void findmax(tr *tipor,punt x);
void initrel(list p);
void cleanup(punt node);
void Addent();
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
  tnil2=malloc(sizeof(Ist));
  tnil2->r=NULL;
  tnil2->l=NULL;
  tnil2->c=false;
  tnil2->mitt=NULL;
  rootent=tnil;
 do {
    scanf("%s",buff);
    if (strcmp(buff,"addent")==0){
      scanf("%s",buff);
      insert(&rootent);
    }
    else if (strcmp(buff,"delent")==0){
      Delent();
    } 
    else if (strcmp(buff,"addrel")==0){
      Addrel();
    } 
    else if (strcmp(buff,"delrel")==0){
      Delrel();
    }
    else if (strcmp(buff,"report")==0){
      Report();
    }
 } while (strcmp(buff,"end")!=0);
 return 0;
}


void Delent(){
  punt f=NULL;
  list x;
  tr iter;
  tr iterp;
  scanf("%s",buff);
  f=search(rootent);
  if(f==tnil) return;
  x=f->myrel;
  cleanup(rootent);
  while(f->myrel!=NULL){
    f->myrel=f->myrel->next;
    while(x->root!=tnil2) delete2(x->root,&(x->root));
    free(x->nome);
    free(x);
    x=f->myrel;
  }
  delete(f,&rootent);
  iter=tipi;
  iterp=iter;
  while (iter!=NULL){
    iter->cont=0;
    findmax(&iter,rootent);
    if (iter->cont==0){
      if (iter->n==NULL && iter==tipi){
	tipi=NULL;
      }
      else if (iter==tipi){
	tipi=iter->n;
      }
      else {
	iterp->n=iter->n;
      }
      free(iter->nomerel);
      free(iter);
    }
    iterp=iter;
    iter=iter->n;
  }
}



void Addrel(){
  punt f1,f2;
  list x,y;
  max *del;
  max *tmp;
  tr iter;
  flag=false;
  scanf("%s",buff);
  f1=search(rootent);
  if (f1==tnil) {
    scanf("%s",buff);
    scanf("%s",buff);
    return;}
  scanf("%s",buff);
  f2=search(rootent);
  if (f2==tnil){
     scanf("%s",buff);
    return;}
  scanf("%s",buff);
  if (!relexists()) addnewrel();
  if (f2->myrel==NULL) {
    f2->myrel=malloc(sizeof(Rel));
    initrel(f2->myrel);
    f2->myrel->next=NULL;
    x=f2->myrel;
  }
  else{
    x=f2->myrel;
    y=f2->myrel;
    if (x==f2->myrel && strcmp(buff,x->nome)<0) {
      x=malloc(sizeof(Rel));
      initrel(x);
      x->next=f2->myrel;
      f2->myrel=x;
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
  strcpy(buff,f1->key);
  insert2(&(x->root),f1);
  if (flag){
    x->cont++;
    iter=tipi;
    while (strcmp(iter->nomerel,x->nome)!=0){
      iter=iter->n;
    }
    if (iter->cont==0){
      iter->cont=x->cont;
      iter->best=malloc(sizeof(max));
      iter->best->ent=f2;
      iter->best->next=NULL;
    }
    else{
    if (iter->cont<x->cont){
      iter->cont=x->cont;
      del=iter->best;
      while (del->next != NULL)
	{
	  iter->best=iter->best->next;
	  free(del);
	  del=iter->best;
	}
      del->ent=f2;
      del->next=NULL;
    }
    else if (iter->cont==x->cont){
     del=iter->best;
     while (del->next!=NULL && strcmp(f2->key,del->next->ent->key)>0) del=del->next;
     if (del==iter->best && strcmp(f2->key,del->ent->key)<0){
       tmp=malloc(sizeof(max));
       tmp->next=del;
       tmp->ent=f2;
       iter->best=tmp;
     }
     else{
     tmp=del->next;
     del->next=malloc(sizeof(max));
     del->next->ent=f2;
     del->next->next=tmp;
     }  
    }
   }
  }
}



void Delrel(){
  punt f1,f2;
  ista n=tnil2;
  list x=NULL;
  list y=NULL;
  tr iter=NULL;
  tr iterp=NULL;
  max *del=NULL;
  max *delp=NULL;
  scanf("%s",buff);
  f1=search(rootent);
  if (f1==tnil){
    scanf("%s",buff);
    scanf("%s",buff);
    return;}
  scanf("%s",buff);
  f2=search(rootent);
  if (f2==tnil){
    scanf("%s",buff);
    return;}
  scanf("%s",buff);
  if (!relexists()) return;
  x=f2->myrel;
  while (x!=NULL && strcmp(x->nome,buff)!=0) {
    y=x;
    x=x->next; }
  if(x==NULL) return;
  strcpy(buff,f1->key);
  n=search2(x->root);
  if (n==tnil2) return;
  delete2(n,&(x->root));
  (x->cont)--;
  iter=tipi;
  while (strcmp(iter->nomerel,x->nome)!=0){
    iterp=iter;
    iter=iter->n;
  }
  if ((x->cont)+1==iter->cont){
    del=iter->best;
    while (del->ent!=f2) {
      delp=del;
      del=del->next;
    }
    if (del==iter->best && del->next==NULL){
      iter->cont=x->cont;
      findmax(&iter,rootent);
      if (iter->cont==0){
	  if (iter->n==NULL && iter==tipi){
	    tipi=NULL;
	  }
	  else if (iter==tipi){
	    tipi=iter->n;
	  }
	  else {
	    iterp->n=iter->n;
	  }
	  free(iter->nomerel);
	  free(iter);
      }
    }
    else{
      if (del==iter->best) {
	iter->best=iter->best->next;
	free(del);
      }
      else {
      delp->next=del->next;
      free(del);
      }
    }   
  }
  if (x->cont==0) {
    if (x->next==NULL && x==f2->myrel){
      f2->myrel=NULL;
    }
    else if (x==f2->myrel){
      f2->myrel=x->next;
    }
    else {
      y->next=x->next;
    }
    free(x->nome);
    free(x);
  }
}



void Report(){
  tr iter;
  max *rep;
  iter=tipi;
  if (iter==NULL){
    fputs("none\n",stdout);
    return;
  }
  while (iter!=NULL){
    rep=iter->best;
    if(rep!=NULL);
    fputs(iter->nomerel,stdout);
    fputs(" ",stdout);
    while (rep!=NULL){
      fputs(rep->ent->key,stdout);
      fputs(" ",stdout);
      rep=rep->next;
    }
    printf("%d; ",iter->cont);
    iter=iter->n;
  }
  fputs("\n",stdout);
}

void insert(punt *root){
  punt y,x;
  punt new;
  y=search(*root);
  if (y!=tnil) return;
  flag=true;
  new=newnode();
  new->key= (char *) malloc(strlen(buff) * sizeof (char)+1);
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
  punt y;
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
  p->root=tnil2;
}

punt newnode(){
  punt new= malloc(sizeof(Nodo));
  inizializza(new);
  return new;
}

void delete(punt z,punt *root){
 punt y,x;
 bool yoc= z->c;
 y=z;
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

void DeleteFixup(punt x,punt *root){
  punt w;
  while (x!=*root && x->c==false){
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
	x=*root;
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
	w->l->c=false;
	RightRotate(x->p,root);
	x=*root;
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

void RBTransplant(punt u,punt v,punt *root){
  if (u->p==tnil) *root=v;
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
  tr tmp=NULL;
  while (iter!=NULL && iter->n!=NULL && strcmp(buff,iter->n->nomerel)>0) iter=iter->n;
  if (iter==NULL){
    tipi=malloc(sizeof(Tiporel));
    tipi->nomerel=(char *)malloc(sizeof(char)*strlen(buff)+1);
    strcpy(tipi->nomerel,buff);
    tipi->best=NULL;
    tipi->cont=0;
    tipi->n=NULL;
  }
  else if(iter==tipi && strcmp(buff,iter->nomerel)<0) {
    tmp=malloc(sizeof(Tiporel));
    tmp->nomerel=(char *)malloc(sizeof(char)*strlen(buff)+1);
    strcpy(tmp->nomerel,buff);
    tmp->best=NULL;
    tmp->cont=0;
    tmp->n=iter;
    tipi=tmp;
  }
  else{
   tmp=iter->n;
   iter->n=malloc(sizeof(Tiporel));
   iter->n->nomerel=(char *)malloc(sizeof(char)*strlen(buff)+1);
   strcpy(iter->n->nomerel,buff);
   iter->n->best=NULL;
   iter->n->cont=0;
   iter->n->n=tmp;
  }
}

void findmax(tr *tipor,punt x){
  list y=x->myrel;
  max *ins;
  max *tmp;
  if (x==tnil) return;
  while (y!=NULL && strcmp(y->nome,(*tipor)->nomerel)!=0) y=y->next;
  if (y!=NULL) {
  if (y->cont>(*tipor)->cont) {
    (*tipor)->cont=y->cont;
    ins=(*tipor)->best;
      while (ins->next != NULL)
	{
	  (*tipor)->best=(*tipor)->best->next;
	  free(ins);
	  ins=(*tipor)->best;
	}
      ins->ent=x;
  }
  else if (y->cont!=0 && (*tipor)->cont==y->cont){
    ins=(*tipor)->best;
    if (strcmp(x->key,ins->ent->key)<0){
      tmp=malloc(sizeof(max));
      tmp->ent=x;
      tmp->next=ins;
      (*tipor)->best=tmp;
    }
    else{
      while (ins->next!=NULL && strcmp(x->key,ins->next->ent->key)>0) ins=ins->next;
      if ((ins->next!=NULL && ins->ent!=x && ins->next->ent!=x)||(ins->next==NULL && ins->ent!=x)){
	tmp=ins->next;
	ins->next=malloc(sizeof(max));
	ins->next->ent=x;
	ins->next->next=tmp;
      }
    }
  }
  }
  findmax(tipor,x->r);
  findmax(tipor,x->l);
}
  
void cleanup(punt node){
  list x,y,tmp;
  ista f;
  if(node==tnil) return;
  if(strcmp(buff,node->key)!=0){ 
  x=node->myrel;
  y=x;
  while (x!=NULL) {
    f=search2(x->root);
    if (f!=tnil2){
      delete2(f,&(x->root));
      (x->cont)--;
    if(x->cont==0){
      tmp=x;
      if (x==node->myrel) {
	node->myrel=x->next;
	x=x->next;
	y=x;
      }
      else {
	y->next=x->next;
	x=x->next;
      }
      free(tmp->nome);
      free(tmp);
    }
    }
    else{
      y=x;
      x=x->next;
    }
  }
  }
      cleanup(node->r);
      cleanup(node->l);
}





//albero2

void insert2(ista *root,punt m){
  ista y,x;
  ista new;
  y=search2(*root);
  if (y!=tnil2) return;
  flag=true;
  new=newnode2();
  new->mitt=m;
  y=tnil2;
  x=*root;
  while (x!=tnil2){
    y=x;
    if (strcmp(new->mitt->key,x->mitt->key)<0) x=x->l;
    else x=x->r;  
  }
  new->p=y;
  if (y==tnil2) *root=new;
  else if(strcmp(new->mitt->key,y->mitt->key)<0) y->l=new;
  else y->r=new;
  new->c=true;
  InsertFixup2(new,root);
}


void InsertFixup2(ista z,ista *root){
  ista y;
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
	    LeftRotate2(z,root);}
 	z->p->c=false;
	z->p->p->c=true;
	RightRotate2(z->p->p,root);
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
	    RightRotate2(z,root);}
	z->p->c=false;
	z->p->p->c=true;
	LeftRotate2(z->p->p,root);
      }
    }
      
  }
  (*root)->c=false;
  tnil2->c=false;
}

void LeftRotate2(ista x,ista *root){
  ista y;
  if (x->r!=tnil2){ 
  y=x->r;
  x->r=y->l;
  if (y->l!=tnil2) y->l->p=x;
  y->p=x->p;
  if (x->p==tnil2) *root=y;
  else if (x==x->p->l) x->p->l=y;
  else x->p->r=y;
  y->l=x;
  x->p=y;
  }
}

void RightRotate2(ista x,ista *root){
  ista y;
  if (x->l!=tnil2){
  y=x->l;
  x->l=y->r;
  if (y->r!=tnil2) y->r->p=x;
  y->p=x->p;
  if (x->p==tnil2) *root=y;
  else if (x==x->p->r) x->p->r=y;
  else x->p->l=y;
  y->r=x;
  x->p=y;
  }
}


void inizializza2(ista p){
  p->r=tnil2;
  p->l=tnil2;
  p->p=tnil2;
  p->mitt=NULL;
}

ista newnode2(){
  ista new= malloc(sizeof(Ist));
  inizializza2(new);
  return new;
}

void delete2(ista z,ista *root){
 ista y,x;
 bool yoc= z->c;
 y=z;
 if (z->l==tnil2){
   x=z->r;
   RBTransplant2(z,z->r,root);			
 }
 else if (z->r==tnil2) {
   x=z->l;
   RBTransplant2(z,z->l,root);
 }
 else {
   y=TreeMin2(z->r);
   yoc= y->c;
   x= y->r;
   if (y->p==z) x->p=y;
   else {
     RBTransplant2(y,y->r,root);
     y->r=z->r;
     y->r->p=y;
   }
   RBTransplant2(z,y,root);
   y->l=z->l;
   y->l->p=y;
   y->c=z->c;
 }
 if (yoc==false) DeleteFixup2(x,root);
 free(z);
}

void DeleteFixup2(ista x,ista *root){
  ista w;
  while (x!=*root && x->c==false){
    if (x==x->p->l){
      w=x->p->r;
      if (w->c==true){
	w->c=false;
	x->p->c=true;
	LeftRotate2(x->p,root);
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
	  RightRotate2(w,root);
	  w=x->p->r;
	}
	w->c=x->p->c;
	x->p->c=false;
	w->r->c=false;
	LeftRotate2(x->p,root);
	x=*root;
      }
    }
    else{
         w=x->p->l;
      if (w->c==true){
	w->c=false;
	x->p->c=true;
	RightRotate2(x->p,root);
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
	LeftRotate2(w,root);
	w=x->p->l;
	}
	w->c=x->p->c;
	x->p->c=false;
	w->l->c=false;
	RightRotate2(x->p,root);
	x=*root;
      } 
    }
  }
  x->c=false;
  }
ista search2(ista x){
  if (x==tnil2 || strcmp(buff,x->mitt->key)==0) return x;
  if (strcmp(buff,x->mitt->key)<0) return search2(x->l);
  else return search2(x->r);
}

void RBTransplant2(ista u,ista v,ista *root){
  if (u->p==tnil2) *root=v;
  else if (u==u->p->l) u->p->l=v;
  else u->p->r= v;
  v->p=u->p;
}

ista TreeMin2(ista x){
  while (x->l!=tnil2) x=x->l;
  return x;
}
