#ifndef OBJETO_H
#define OBJETO_H
#include<string>
#include<iostream>
#include<fstream>
#include<list>
#include<math.h>
#include "Caja.h"
#include "ArbolKD.h"
#include "Graph.h"

using namespace std;

struct Punto
{
  float X, Y, Z;
  float distanciaA( const Punto& b ) const
    {
      float x = X - b.X;
      float y = Y - b.Y;
      float z = Z - b.Z;
      return( sqrt( ( x * x ) + ( y * y ) + ( z * z ) ) );
    }
};

typedef Graph< Punto, float > TGrafo;
typedef std::vector< unsigned long > TRuta;
typedef std::vector< TRuta > TCaminos;
typedef std::vector< float > TDist;


class Objeto
{
    public:
        Objeto(string nombre,int numVertices){
            this->nombre=nombre;
            this->numVertices=numVertices;
        }
        string getNombre(){
            return this->nombre;
        }
        int getNumVertices(){
            return this->numVertices;
        }
        list<float> getPuntos(){
            return this->puntos;
        }
        list<float> getCaras(){
            return this->caras;
        }
        list<string> getAristas(){
            return this->aristas;
        }
        int getNumCaras(){
            return this->numCaras;
        }
        int getNumAristas(){
            return this->numAristas;
        }
        int setNumCaras(int x){
            this->numCaras=x;
        }
        int setNumAristas(int x){
            this->numAristas=x;
        }
        void setNombre(string x){
             this->nombre=x;
        }
        void setNumVertices(int n){
             this->numVertices=n;
        }
        void setPuntos(list<float> puntos){
            this->puntos=puntos;
        }
         void setCaras(list<float> caras){
            this->caras=caras;
        }
        void setAristas(list<string> aristas){
            this->aristas=aristas;
        }
        void imprimirDatos(){
            cout<<"Nombre: "<<nombre<<endl;
            cout<<"# Vertices: "<<numVertices<<endl;
            cout<<"Puntos: "<<endl;
            int i=0;
            for(std::list<float>::iterator it=this->puntos.begin(); it != this->puntos.end();it++){
                cout<<*it<<" ";
               if(i==2){
                    cout<<endl;
                    i=0;

               }
               else{
                    i++;
               }
            }
            cout<<endl<<"# Caras: "<<numCaras<<endl;
            cout<<"# Aristas : "<<numAristas<<endl;
        }
        void escribirDatos(string nombreGuardar){
            ofstream salida((nombreGuardar+".doc").c_str(),ios::out);
            salida<<"Nombre: "<<nombre<<endl;
            salida<<"# Vertices: "<<numVertices<<endl;
            salida<<"Puntos: "<<endl;
            int i=0;
            for(std::list<float>::iterator it=this->puntos.begin(); it != this->puntos.end();it++){
                salida<<*it<<" ";
               if(i==2){
                    salida<<endl;
                    i=0;

               }
               else{
                    i++;
               }
            }
            salida<<endl<<"# Caras: "<<numCaras<<endl;
            salida<<"# Aristas : "<<numAristas<<endl;
        }
        Caja calcularMalla(){
        float xMenor=0,yMenor=0,zMenor=0,xMayor=0,yMayor=0,zMayor=0;
            int i=0;
            for(std::list<float>::iterator it=this->puntos.begin(); it != this->puntos.end();it++){
                if(i==0){
                    if(*it>xMayor){
                        xMayor=*it;
                    }
                    if(*it<xMenor){
                        xMenor=*it;
                    }
                }
                if(i==1){
                    if(*it>yMayor){
                        yMayor=*it;
                    }
                    if(*it<yMenor){
                        yMenor=*it;
                    }
                }
                if(i==2){
                     if(*it>zMayor){
                        zMayor=*it;
                    }
                    if(*it<xMenor){
                        zMenor=*it;
                    }
                }
                if(i==0||i==1){
                    i++;
                }
                else{
                    i=0;
                }
            }
            string nombreCaja;
        cout<<"Ingrese el nombre de la caja"<<endl;
        cin>>nombreCaja;
        list<float>minMax;
        minMax.push_back(xMenor);
        minMax.push_back(yMenor);
        minMax.push_back(zMenor);
        minMax.push_back(xMayor);
        minMax.push_back(yMayor);
        minMax.push_back(zMayor);

         list<float> puntosCaja;
            puntosCaja.push_back(xMenor);
            puntosCaja.push_back(yMenor);
            puntosCaja.push_back(zMenor);

            puntosCaja.push_back(xMayor);
            puntosCaja.push_back(yMayor);
            puntosCaja.push_back(zMayor);

            puntosCaja.push_back(xMayor);
            puntosCaja.push_back(yMenor);
            puntosCaja.push_back(zMenor);

            puntosCaja.push_back(xMenor);
            puntosCaja.push_back(yMayor);
            puntosCaja.push_back(zMenor);

            puntosCaja.push_back(xMenor);
            puntosCaja.push_back(yMenor);
            puntosCaja.push_back(zMayor);

            puntosCaja.push_back(xMayor);
            puntosCaja.push_back(yMenor);
            puntosCaja.push_back(zMayor);

            puntosCaja.push_back(xMenor);
            puntosCaja.push_back(yMayor);
            puntosCaja.push_back(zMayor);

            puntosCaja.push_back(xMayor);
            puntosCaja.push_back(yMayor);
            puntosCaja.push_back(zMenor);
            Caja caja(nombreCaja,puntosCaja,minMax);
            caja.imprimirCaja();
            return caja;

        }
        bool esta(string aux,list<string>mezclados){
            for(std::list<string>::iterator it=mezclados.begin(); it != mezclados.end();it++){
                if(aux==*it){
                    return true;
                }
            }
            return false;
        }
        void mezclar(list<string> numeros,list<string>&mezclados){
            string aux;
            list<string> nueva=numeros;
            nueva.pop_front();
            std::list<string>::iterator it=numeros.begin();
            std::list<string>::iterator it2=nueva.begin();
            for(; it != numeros.end();it++,it2++){
                        if(it2==nueva.end()){
                                it2=numeros.begin();
                        }
                        if((*it)>(*it2)){
                             aux=(*it)+(*it2);
                        }else{
                            aux=(*it2)+(*it);
                        }
                        if(!esta(aux,mezclados)){
                            mezclados.push_back(aux);
                        }
                }
        }
        void sacarAristas(){
            list<string> aux=this->aristas;
            list<string> mezclados;
            list<string> numeros;
            int b;
            int i=0;
              for(std::list<string>::iterator it=aux.begin(); it != aux.end();it++){
                    if(i==0){
                        b=atoi((*it).c_str());
                    }
                    else{
                        numeros.push_back(*it);
                    }
                    if(i==b){
                        i=0;
                        mezclar(numeros,mezclados);
                        numeros.clear();
                    }else{
                        i++;
                    }
              }
              this->numAristas=mezclados.size();
        }
        void verticeCercanoArbol(float x,float y,float z){
            point valor;
            point valoraux;
            point valorfinal;
            float resultado=0;
            valoraux.x=x;
            valoraux.y=y;
            valoraux.z=z;
            int i=0;
              bool resul;
            int j=0;
            for(std::list<float>::iterator it=this->puntos.begin(); it != this->puntos.end();it++){
                if(j<3){
                    if(i==0){
                        valor.x=*it;
                    }
                    if(i==1){
                        valor.y=*it;
                    }
                    if(i==2){
                        valor.z=*it;
                    }
                }
                i++;
                j++;
            }
            ArbolKD arb(valor);
            j=0;
            i=0;
            for(std::list<float>::iterator it=this->puntos.begin(); it != this->puntos.end();it++){
                if(j>=3){
                    if(i==0){
                        valor.x=*it;
                    }
                    if(i==1){
                        valor.y=*it;
                    }
                    if(i==2){
                        valor.z=*it;
                        resul=arb.insertar(valor);
                        i=0;
                    }
                   else{
                        i++;
                    }
                }
                j++;
            }
            std::queue<int> colita;
            arb.cola(colita);
            arb.cercano(valoraux,resultado,valorfinal);
            cout<<"El vertice mas cercano al punto ("<<valoraux.x<<","<<valoraux.y<<","<<valoraux.z<<")  es el punto ("<<valorfinal.x<<","<<valorfinal.y<<","<<valorfinal.z<<")"<<endl;

        }
        void verticesEsquinas(){
            Caja cajita=this->calcularMalla();
            point valor;
            point valoraux;
            point valorfinal;
            float resultado=0;
              bool resul;
            int j=0;
            int i=0;
            for(std::list<float>::iterator it=this->puntos.begin(); it != this->puntos.end();it++){
                if(j<3){
                    if(i==0){
                        valor.x=*it;
                    }
                    if(i==1){
                        valor.y=*it;
                    }
                    if(i==2){
                        valor.z=*it;
                    }
                }
                i++;
                j++;
            }
            ArbolKD arbi(valor);
            j=0;
            i=0;

            for(std::list<float>::iterator it=this->puntos.begin(); it != this->puntos.end();it++){

                if(j>=3){
                    if(i==0){
                        valor.x=*it;
                    }
                    if(i==1){
                        valor.y=*it;
                    }
                    if(i==2){
                        valor.z=*it;
                        resul=arbi.insertar(valor);
                        i=0;
                    }
                   else{
                        i++;
                    }
                }
                j++;
            }
            cout<<"ESQUINA       VERTICE      DISTANCIA"<<endl;
            i=0;
            for(std::list<float>::iterator it=cajita.puntos.begin(); it != cajita.puntos.end();it++){
                if(i==0){
                        valoraux.x=*it;
                    }
                    if(i==1){
                        valoraux.y=*it;
                    }
                    if(i==2){
                        valoraux.z=*it;
                        arbi.cercano(valoraux,resultado,valorfinal);
                        cout<<"("<<valoraux.x<<","<<valoraux.y<<","<<valoraux.z<<")   "<<"("<<valorfinal.x<<","<<valorfinal.y<<","<<valorfinal.z<<")    "<<     resultado<<endl;
                        i=0;
                        resultado=0;
                    }
                   else{
                        i++;
                    }

            }
        }
        float distancia(float x1,float y1,float z1,float x2,float y2,float z2){
           float Xresul=pow((x2-x1),2);
           float Yresul=pow((y2-y1),2);
           float Zresul=pow((z2-z1),2);
           return sqrt(Xresul+Yresul+Zresul);
        }
        void mezclar2(list<string> numeros,list<string>&mezclados){
            string aux;
            list<string> nueva=numeros;
            nueva.pop_front();
            std::list<string>::iterator it=numeros.begin();
            std::list<string>::iterator it2=nueva.begin();
            for(; it != numeros.end();it++,it2++){
                        if(it2==nueva.end()){
                                it2=numeros.begin();
                        }
                        if((*it)>(*it2)){
                             aux=(*it)+" "+(*it2);
                        }else{
                            aux=(*it2)+" "+(*it);
                        }
                        if(!esta(aux,mezclados)){
                            mezclados.push_back(aux);
                        }
                }
        }
        void rutaCorta(){
            TGrafo g;
            Punto p;
            int j=0;
            int i=0;
            for(std::list<float>::iterator it=this->puntos.begin(); it != this->puntos.end();it++){
                if(i==0){
                    p.X=*it;
                }
                if(i==1){
                    p.Y=*it;
                }
                if(i==2){
                    p.Z=*it;
                    g.AddVertex(p);
                    i=0;
                }
                else{
                    i++;
                }
            }
            list<string> aux=this->aristas;
            list<string> mezclados;
            list<string> numeros;
            int b;
             i=0;
              for(std::list<string>::iterator it=aux.begin(); it != aux.end();it++){
                    if(i==0){
                        b=atoi((*it).c_str());
                    }
                    else{
                        numeros.push_back(*it);
                    }
                    if(i==b){
                        i=0;
                        mezclar2(numeros,mezclados);
                        numeros.clear();
                    }else{
                        i++;
                    }
              }
              int x,y,cont=0;
               string token;
            for(std::list<string>::iterator it=mezclados.begin(); it != mezclados.end();it++){
                cont=0;
                istringstream is(*it);
               while (getline(is, token, ' ')){
                    if(cont==1){
                        x=atoi(token.c_str());
                    }
                    else{
                        y=atoi(token.c_str());
                    }
                    cont++;
                }
                g.SetArc(x,y,g.GetVertex(x).distanciaA(g.GetVertex(y)));
                g.SetArc(y,x,g.GetVertex(x).distanciaA(g.GetVertex(y)));
            }
            int punto1,punto2;
            cout<<"Ingrese el primer indice"<<endl;
            cin>>punto1;
            cout<<"Ingrese el segundo indice"<<endl;
            cin>>punto2;
            if(punto1==punto2){
                cout<<"Es el mismo vertice. Costo=0"<<endl;
            }
            else{
                    int aux;
                    bool b=false;
                    if(punto1>punto2){
                        aux=punto2;
                        punto2=punto1;
                        punto1=aux;
                        b=true;
                    }
                TCaminos caminosDijkstra = g.Dijkstra(punto1);
                TRuta ruta;
                float cosTotal;
                ruta = caminosDijkstra[punto2-1];
                cout<<"El camino mas corto es"<<endl;
                if(!b){
                     for(int i=0;i<ruta.size();i++){
                        cout<<ruta[i]<<" ";
                    }
                }else{
                    for(int i=ruta.size()-1;i>=0;i--){
                        cout<<ruta[i]<<" ";
                    }
                }
                for( unsigned int j = 0; j < ruta.size( ) - 1; ++j ){
                    cosTotal += g.GetCost( ruta[ j ], ruta[ j + 1 ] );
                }
                cout << "costo Total: "<<cosTotal <<endl;
            }

        }
        void rutaCortaCentro(){
            TGrafo g;
            Punto p;
            int j=0;
            int i=0;
            float xp=0,yp=0,zp=0;
            list<Punto> listaP;
            for(std::list<float>::iterator it=this->puntos.begin(); it != this->puntos.end();it++){
                if(i==0){
                    p.X=*it;
                    xp+=*it;
                }
                if(i==1){
                    p.Y=*it;
                    yp+=*it;
                }
                if(i==2){
                    p.Z=*it;
                    g.AddVertex(p);
                    zp+=*it;
                    i=0;
                    listaP.push_back(p);
                }
                else{
                    i++;
                }
            }
            list<string> aux=this->aristas;
            list<string> mezclados;
            list<string> numeros;
            int b;
             i=0;
              for(std::list<string>::iterator it=aux.begin(); it != aux.end();it++){
                    if(i==0){
                        b=atoi((*it).c_str());
                    }
                    else{
                        numeros.push_back(*it);
                    }
                    if(i==b){
                        i=0;
                        mezclar2(numeros,mezclados);
                        numeros.clear();
                    }else{
                        i++;
                    }
              }
              int x,y,cont=0;
               string token;
            for(std::list<string>::iterator it=mezclados.begin(); it != mezclados.end();it++){
                cont=0;
                istringstream is(*it);
               while (getline(is, token, ' ')){
                    if(cont==1){
                        x=atoi(token.c_str());
                    }
                    else{
                        y=atoi(token.c_str());
                    }
                    cont++;
                }
                g.SetArc(x,y,g.GetVertex(x).distanciaA(g.GetVertex(y)));
                g.SetArc(y,x,g.GetVertex(x).distanciaA(g.GetVertex(y)));
            }
            int punto1;
            cout<<"Ingrese el primer indice"<<endl;
            cin>>punto1;
            p.X=xp/this->getNumVertices();
            p.Y=yp/this->getNumVertices();
            p.Z=zp/this->getNumVertices();
            cout<<"CENTROIDE :"<<p.X<<","<<p.Y<<","<<p.Z<<endl;
            g.AddVertex(p);
            float dist=10000000;

            list<Punto> puntoss;
            for(std::list<Punto>::iterator it=listaP.begin(); it != listaP.end();it++){
                if(distancia((*it).X,(*it).Y,(*it).Z,p.X,p.Y,p.Z)<=dist){
                    dist=distancia((*it).X,(*it).Y,(*it).Z,p.X,p.Y,p.Z);
                    puntoss.push_back(*it);
                }
            }
             i=0,j=0;
             dist=0;
             int indexi,indexj;
            for(std::list<Punto>::iterator it=puntoss.begin(); it != puntoss.end();it++){
                    j=0;

                for(std::list<Punto>::iterator it2=puntoss.begin(); it2 != puntoss.end();it2++){
                        if(distancia((*it).X,(*it).Y,(*it).Z,(*it2).X,(*it2).Y,(*it2).Z)>dist&&g.HasArc(i,j)){
                            dist=distancia((*it).X,(*it).Y,(*it).Z,(*it2).X,(*it2).Y,(*it2).Z);
                            indexi=i;
                            indexj=j;
                        }
                        j++;
                }
                i++;
            }
            g.SetArc(indexi,this->getNumVertices(),g.GetVertex(indexi).distanciaA(g.GetVertex(this->getNumVertices())));
            g.SetArc(this->getNumVertices(),indexi,g.GetVertex(indexi).distanciaA(g.GetVertex(this->getNumVertices())));
            g.SetArc(indexj,this->getNumVertices(),g.GetVertex(indexj).distanciaA(g.GetVertex(this->getNumVertices())));
            g.SetArc(this->getNumVertices(),indexj,g.GetVertex(indexj).distanciaA(g.GetVertex(this->getNumVertices())));
                TCaminos caminosDijkstra = g.Dijkstra(this->getNumVertices());
                TRuta ruta;
                float cosTotal;
                ruta = caminosDijkstra[punto1];
                cout<<"El camino mas corto es"<<endl;
                if(!b){
                     for(int i=0;i<ruta.size();i++){
                        cout<<ruta[i]<<" ";
                    }
                }else{
                    for(int i=ruta.size()-1;i>=0;i--){
                        cout<<ruta[i]<<" ";
                    }
                }
                for( unsigned int j = 0; j < ruta.size( ) - 1; ++j ){
                    cosTotal += g.GetCost( ruta[ j ], ruta[ j + 1 ] );
                }
                cout << "costo Total: "<<cosTotal <<endl;

        }
    protected:

    private:
        string nombre;
        int numVertices;
        list<float> puntos;
        list<float> caras;
        list<string> aristas;
        int numCaras;
        int numAristas;
};
#endif // OBJETO_H
