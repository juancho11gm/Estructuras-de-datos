#ifndef __ARBOLKD__H__
#define __ARBOLKD__H__

#include "NodoKD.h"
#include <queue>


class ArbolKD {
  protected:
    NodoKD *raiz;
  public:
    //constructores
    ArbolKD();
    ArbolKD(point &val);
    //destructor
    ~ArbolKD();
    //manipuladores del arbol
    bool esVacio();
    point& datoRaiz();
    NodoKD* obtenerRaiz();
    void fijarRaiz(NodoKD *n_raiz);
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

#endif // __ARBOLKD__H__

// eof - ArbolKD.h

