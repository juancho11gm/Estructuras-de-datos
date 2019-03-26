#ifndef __NODOKD__H__
#define __NODOKD__H__

#include <iostream>
#include <queue>

struct point {
  float x;
  float y;
  float z;

  point& operator = (const point &p) {
    x = p.x;
    y = p.y;
    z = p.z;
    return *this;
  }

  bool operator == (const point &p) const {
    return (x == p.x && y == p.y && z==p.z);
  }

  friend std::ostream& operator << (std::ostream &o, const point &p) {
    o << "(" << p.x << "," << p.y << "," << p.z <<")";
    return o;
  }
};

class NodoKD {
  protected:
    point dato;
    NodoKD *hijoIzq;
    NodoKD *hijoDer;
  public:
    //constructores
    NodoKD();
    NodoKD(point &val);
    NodoKD(point &val, NodoKD *izq, NodoKD *der);
    //destructor
    ~NodoKD();
    //manipuladores del nodo
    bool esHoja();
    point& obtenerDato();
    void fijarDato(point &val);
    NodoKD* obtenerHijoIzq();
    NodoKD* obtenerHijoDer();
    void fijarHijoIzq(NodoKD *izq);
    void fijarHijoDer(NodoKD *der);
    //operaciones del arbol
    void preOrden();
    void inOrden();
    void posOrden();
    void nivelOrden();
    bool insertar(point &val);
    void cola(std::queue<int> &colita);
    void cercano(point valoraux,float &resultado,point &valorfinal);
    float distancia(float x1,float y1,float z1,float x2,float y2,float z2);
};

#endif // __NODOKD__H__


// eof - NodoKD.h

