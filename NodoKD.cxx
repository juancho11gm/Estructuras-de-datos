#include "NodoKD.h"
#include <queue>
#include <list>
#include <math.h>

// ------------------------------------------------------------------------
NodoKD::NodoKD() {
  this->hijoIzq = NULL;
  this->hijoDer = NULL;
}

// ------------------------------------------------------------------------
NodoKD::NodoKD(point &val){
  this->dato = val;
  this->hijoIzq = NULL;
  this->hijoDer = NULL;
}

// ------------------------------------------------------------------------
NodoKD::NodoKD(point &val, NodoKD *izq, NodoKD *der) {
  this->dato = val;
  this->hijoIzq = izq;
  this->hijoDer = der;
}

// ------------------------------------------------------------------------
NodoKD::~NodoKD() {
  if (this->hijoIzq != NULL) {
    delete this->hijoIzq;
    this->hijoIzq = NULL;
  }
  if (this->hijoDer != NULL) {
    delete this->hijoDer;
    this->hijoDer = NULL;
  }
}

// ------------------------------------------------------------------------
bool NodoKD::esHoja() {
  return (this->hijoIzq == NULL && this->hijoDer == NULL);
}

// ------------------------------------------------------------------------
point& NodoKD::obtenerDato() {
  return this->dato;
}

// ------------------------------------------------------------------------
void NodoKD::fijarDato(point &val) {
  this->dato = val;
}

// ------------------------------------------------------------------------
NodoKD* NodoKD::obtenerHijoIzq() {
  return this->hijoIzq;
}

// ------------------------------------------------------------------------
NodoKD* NodoKD::obtenerHijoDer() {
  return this->hijoDer;
}

// ------------------------------------------------------------------------
void NodoKD::fijarHijoIzq(NodoKD *izq) {
  this->hijoIzq = izq;
}

// ------------------------------------------------------------------------
void NodoKD::fijarHijoDer(NodoKD *der) {
  this->hijoDer = der;
}

// ------------------------------------------------------------------------
void NodoKD::preOrden() {
  std::cout << this->dato << "\t";
  if (this->hijoIzq != NULL)
    this->hijoIzq->preOrden();
  if (this->hijoDer != NULL)
    this->hijoDer->preOrden();
}

// ------------------------------------------------------------------------
void NodoKD::inOrden() {
  if (this->hijoIzq != NULL)
    this->hijoIzq->inOrden();
  std::cout << this->dato << "\t";
  if (this->hijoDer != NULL)
    this->hijoDer->inOrden();
}

// ------------------------------------------------------------------------
void NodoKD::posOrden() {
  if (this->hijoIzq != NULL)
    this->hijoIzq->posOrden();
  if (this->hijoDer != NULL)
    this->hijoDer->posOrden();
  std::cout << this->dato << "\t";
}

// ------------------------------------------------------------------------
void NodoKD::nivelOrden() {
  std::queue< NodoKD* > q;
  NodoKD *t = this;
  while (t != NULL) {
    std::cout << t->dato << "\t";
    if (t->hijoIzq != NULL)
      q.push(t->hijoIzq);
    if (t->hijoDer != NULL)
      q.push(t->hijoDer);
    if (!q.empty()) {
      t = q.front();
      q.pop();
    } else
      t = NULL;
  }
}

// ------------------------------------------------------------------------
bool NodoKD::insertar(point &val) {
  NodoKD *p = this;
  NodoKD *pp = NULL;
  bool insertado = false;
  bool duplicado = false;
  unsigned int dim = 0;
  while (p != NULL) {
    pp = p;
    if (val == p->dato) {
      duplicado = true;
      break;
    } else {
      if (dim == 0) {
        if (val.x < (p->dato).x)
          p = p->hijoIzq;
        else if (val.x > (p->dato).x)
          p = p->hijoDer;
      } else if (dim == 1) {
        if (val.y < (p->dato).y)
          p = p->hijoIzq;
        else if (val.y > (p->dato).y)
          p = p->hijoDer;
      }
        else if(dim==2){
           if (val.z < (p->dato).z)
          p = p->hijoIzq;
        else if (val.z > (p->dato).z)
          p = p->hijoDer;
        }
      dim = (dim + 1) % 3;
    }
  }
  if (!duplicado) {
    NodoKD *n = new NodoKD(val);
    dim = (dim - 1) % 3;
    if (n != NULL) {
      if (dim == 0) {
        if (val.x < (pp->dato).x)
          pp->fijarHijoIzq(n);
        else
          pp->fijarHijoDer(n);
      } else if (dim == 1) {
        if (val.y < (pp->dato).y)
          pp->fijarHijoIzq(n);
        else
          pp->fijarHijoDer(n);
      }
      else if (dim == 2) {
        if (val.z < (pp->dato).z)
          pp->fijarHijoIzq(n);
        else
          pp->fijarHijoDer(n);
      }
    }
    insertado = true;
  }
  return insertado;
}
void NodoKD::cola(std::queue<int> &colita) {
    colita.push(this->dato.x);
    colita.push(this->dato.y);
    colita.push(this->dato.z);
  if (this->hijoIzq != NULL)
    this->hijoIzq->cola(colita);
  if (this->hijoDer != NULL)
    this->hijoDer->cola(colita);
}
void NodoKD::cercano(point valoraux,float &resultado,point &valorfinal){
        float dist;
        dist=this->distancia(valoraux.x,valoraux.y,valoraux.z,this->dato.x,this->dato.y,this->dato.z);
        if(dist<resultado){
            resultado=dist;
            valorfinal=this->dato;
        }
      if (this->hijoIzq != NULL)
    this->hijoIzq->cercano(valoraux,resultado,valorfinal);
  if (this->hijoDer != NULL)
    this->hijoDer->cercano(valoraux,resultado,valorfinal);
}

float NodoKD::distancia(float x1,float y1,float z1,float x2,float y2,float z2){
           float Xresul=pow((x2-x1),2);
           float Yresul=pow((y2-y1),2);
           float Zresul=pow((z2-z1),2);
           return sqrt(Xresul+Yresul+Zresul);
        }
// eof - NodoKD.hxx

