#include "ArbolKD.h"
#include "NodoKD.h"
#include "math.h"


// ------------------------------------------------------------------------
ArbolKD::ArbolKD() {
  this->raiz = NULL;
}

// ------------------------------------------------------------------------
ArbolKD::ArbolKD(point &val) {
  NodoKD *nnodo = new NodoKD(val);
  this->raiz = nnodo;
}

// ------------------------------------------------------------------------
ArbolKD::~ArbolKD() {
  if (this->raiz != NULL) {
    delete this->raiz;
    this->raiz = NULL;
  }
}

// ------------------------------------------------------------------------
bool ArbolKD::esVacio() {
  return (this->raiz == NULL);
}

// ------------------------------------------------------------------------
point& ArbolKD::datoRaiz() {
  return (this->raiz)->obtenerDato();
}

// ------------------------------------------------------------------------
NodoKD* ArbolKD::obtenerRaiz() {
  return this->raiz;
}

// ------------------------------------------------------------------------
void ArbolKD::fijarRaiz(NodoKD *n_raiz) {
  this->raiz = n_raiz;
}

// ------------------------------------------------------------------------
void ArbolKD::preOrden() {
  if (this->raiz != NULL)
    this->raiz->preOrden();
  std::cout << std::endl;
}

// ------------------------------------------------------------------------
void ArbolKD::inOrden() {
  if (this->raiz != NULL)
    this->raiz->inOrden();
  std::cout << std::endl;
}

// ------------------------------------------------------------------------
void ArbolKD::posOrden() {
  if (this->raiz != NULL)
    this->raiz->posOrden();
  std::cout << std::endl;
}

// ------------------------------------------------------------------------
void ArbolKD::nivelOrden() {
  if (this->raiz != NULL)
    this->raiz->nivelOrden();
  std::cout << std::endl;
}

// ------------------------------------------------------------------------
bool ArbolKD::insertar(point& val) {
  bool res;
  if (this->raiz == NULL) {
    this->raiz = new NodoKD(val);
    res = true;
  } else
    res = this->raiz->insertar(val);

  return res;
}

void ArbolKD::cola(std::queue<int> &colita) {
    if (this->raiz != NULL)
    this->raiz->cola(colita);
}

void ArbolKD::cercano(point valoraux,float &resultado,point &valorfinal){
    if(resultado==0){
        valorfinal=this->raiz->obtenerDato();
        resultado=distancia(valoraux.x,valoraux.y,valoraux.z,this->raiz->obtenerDato().x,this->raiz->obtenerDato().y,this->raiz->obtenerDato().z);
    }
    this->raiz->cercano(valoraux,resultado,valorfinal);
}

float ArbolKD::distancia(float x1,float y1,float z1,float x2,float y2,float z2){
           float Xresul=pow((x2-x1),2);
           float Yresul=pow((y2-y1),2);
           float Zresul=pow((z2-z1),2);
           return sqrt(Xresul+Yresul+Zresul);
        }
// eof - ArbolKD.hxx

