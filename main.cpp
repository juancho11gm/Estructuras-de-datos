#include <iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<list>
#include<sstream>
#include "Objeto.h"
#include "Caja.h"
#include "ArbolKD.h"
#include "NodoKD.h"
#include "Graph.h"

using namespace std;


void leerDatos(list<Objeto> &objetos,int &numObjetos){
string nombreArchivo;
    cout<<"Ingrese el nombre del archivo texto"<<endl;
    cin>>nombreArchivo;
    string linea;
    list<float> puntos;
    list<float> caras;
    list<string> aristas;
    ifstream archivo;
    int numVertices;
    archivo.open(nombreArchivo.c_str());
    if(archivo){
        string nombreObjeto;
    getline(archivo,nombreObjeto);
    getline(archivo,linea);
    numVertices=atoi(linea.c_str());
    Objeto objeto(nombreObjeto,numVertices);
    int i=0;
    string token;
    while(i<numVertices){
         getline(archivo,linea);
         istringstream is(linea);
          while (getline(is, token, ' ')){
            float punto;
            punto=atof(token.c_str());
            puntos.push_back(punto);
        }
         i++;
    }
    objeto.setPuntos(puntos);
    float cara;
    int numCaras=-1;
    while(linea!="-1"){
            numCaras++;
        getline(archivo,linea);
         istringstream is(linea);
          while (getline(is, token, ' ')&&linea!="-1"){
            float punto;
            cara=atof(token.c_str());
            caras.push_back(cara);
            aristas.push_back(token);
        }
    }
    objeto.setNumCaras(numCaras);
    objeto.setCaras(caras);
    objeto.setAristas(aristas);
    objeto.sacarAristas();
    objetos.push_back(objeto);
    numObjetos++;
    cout<<"Objeto cargado con exito"<<endl;
    }
    else{
        cout<<"No se encontro el archivo"<<endl;
    }
}
void escribirDatos(string nombreGuardar,Objeto objeto){
    objeto.escribirDatos(nombreGuardar);
}
Caja cajaEnvolvente(list<Objeto> objetos){
    list<float>total;
    for(std::list<Objeto>::iterator it=objetos.begin(); it != objetos.end();it++){
            list<float> aux =(*it).getPuntos();
         for(std::list<float>::iterator it2=aux.begin(); it2 != aux.end();it2++){
            total.push_back(*it2);
         }
     }
    float xMenor=0,yMenor=0,zMenor=0,xMayor=0,yMayor=0,zMayor=0;
    int i=0;
    for(std::list<float>::iterator it=total.begin(); it != total.end();it++){
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
verticeCercanoTotalArbol(std::list<Objeto> objetos,float x,float y,float z){
    list<float>total;
    for(std::list<Objeto>::iterator it=objetos.begin(); it != objetos.end();it++){
            list<float> aux =(*it).getPuntos();
         for(std::list<float>::iterator it2=aux.begin(); it2 != aux.end();it2++){
            total.push_back(*it2);
         }
     }
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
            for(std::list<float>::iterator it=total.begin(); it !=total.end();it++){
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
            for(std::list<float>::iterator it=total.begin(); it != total.end();it++){
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

int main(){
 int opcion;
    bool salir=false;
    int numObjetos=0;
    string nombreGuardar;
    int numCajas=0;
     list<Objeto> objetos;
     list<Caja> cajas;
    //menú
    cout<<"---------------------Proyecto estructuras de datos---------------------"<<endl;
    while(salir==false){
        do{
            cout<<endl<<"-------------------INGRESE LA OPCION QUE DESEE (EL NUMERO)---------------------"<<endl;
            cout<<"1. Cargar un objeto"<<endl;
            cout<<"2. Listado de objetos (Imprime info de todos los objetos en memoria)"<<endl;
            cout<<"3. Envolvente objeto (Caja envolvente de un objeto dado)"<<endl;
            cout<<"4. Envolvente (Caja envolvente de todos los objetos)"<<endl;
            cout<<"5. Descargar objeto"<<endl;
            cout<<"6. Guardar objeto"<<endl;
            cout<<"7. Vertice del objeto cercano a un punto"<<endl;
            cout<<"8. Vertice mas cercano a vertices de todos los objetos"<<endl;
            cout<<"9. Vertices mas cercanos a la esquina de la caja envolvente de un objeto"<<endl;
            cout<<"10. Ruta más corta"<<endl;
            cout<<"11. Ruta más corta centro"<<endl;
            cout<<"12. Salir"<<endl;
            cin>>opcion;
            if(opcion<1||opcion>12){
                cout<<"Ingrese una opcion valida por favor"<<endl;
                system("cls");
                system("PAUSE");
            }
            system("cls");
        }while(opcion<1||opcion>12);
        switch(opcion){
            case 1: {
                leerDatos(objetos,numObjetos);
                system("PAUSE");
                break;
            }
            case 2:{
                cout<<"Hay "<<numObjetos+numCajas<<" objetos en memoria"<<endl;
                for(std::list<Objeto>::iterator it=objetos.begin(); it != objetos.end();it++){
                    (*it).imprimirDatos();
                    cout<<endl;
                }
                cout<<"CAJAS: "<<endl;
                if(numCajas==0){
                    cout<<"No se han creado cajas "<<endl;
                }
                for(std::list<Caja>::iterator it=cajas.begin(); it != cajas.end();it++){
                    (*it).imprimirCaja();
                    cout<<endl;
                }
                system("PAUSE");
                break;
            }
            case 3:{
                 cout<<"Ingrese el nombre del objeto que desea calcular"<<endl;
                cin>>nombreGuardar;
                bool encontro=false;
                for(std::list<Objeto>::iterator it=objetos.begin(); it != objetos.end();it++){
                    if((*it).getNombre() == nombreGuardar){
                           cajas.push_back((*it).calcularMalla());
                           numCajas++;
                            encontro=true;
                    }
                }
                if(!encontro){
                    cout<<"No se encontro el objeto"<<endl;
                }
                system("PAUSE");
                break;
            }
            case 4:{
                if(numObjetos!=0){
                    cajas.push_back(cajaEnvolvente(objetos));
                    numCajas++;
                }
                else{
                    cout<<"No hay objetos"<<endl;
                }
                system("PAUSE");
                break;
            }
            case 5:{
                cout<<"Ingrese el nombre del objeto que desea descargar"<<endl;
                cin>>nombreGuardar;
                bool encontro=false;
                for(std::list<Objeto>::iterator it=objetos.begin(); it != objetos.end();it++){
                    if((*it).getNombre() == nombreGuardar){
                            objetos.erase(it);
                            numObjetos--;
                            cout<<"Objeto Descargado con exito"<<endl;
                            encontro=true;
                    }
                }
                 for(std::list<Caja>::iterator it=cajas.begin(); it != cajas.end();it++){
                    if((*it).getNombre() == nombreGuardar){
                             cajas.erase(it);
                             numCajas--;
                            cout<<"Objeto Descargado con exito"<<endl;
                            encontro=true;
                    }
                }
                if(!encontro){
                    cout<<"No se encontro el objeto"<<endl;
                }
                system("PAUSE");
                break;
            }
            case 6:
            {
                cout<<"Ingrese el nombre del objeto que desea guardar por favor"<<endl;
                cin>>nombreGuardar;
                bool encontro=false;
                for(std::list<Objeto>::iterator it=objetos.begin(); it != objetos.end();it++){
                    if((*it).getNombre() == nombreGuardar){
                            escribirDatos(nombreGuardar,(*it));
                            cout<<"Objeto guardado con exito"<<endl;
                            encontro=true;
                    }
                }
                 for(std::list<Caja>::iterator it=cajas.begin(); it != cajas.end();it++){
                    if((*it).getNombre() == nombreGuardar){
                            (*it).escribirDatos(nombreGuardar);
                            cout<<"Objeto guardado con exito"<<endl;
                            encontro=true;
                    }
                }
                if(!encontro){
                    cout<<"No se encontro el objeto"<<endl;
                }
                system("PAUSE");
                break;
            }
            case 7:
            {
                float x,y,z;
                cout<<"Ingrese la coordenada en x"<<endl;
                cin>>x;
                cout<<"Ingrese la coordenada en y"<<endl;
                cin>>y;
                cout<<"Ingrese la coordenada en z"<<endl;
                cin>>z;
                cout<<"Ingrese el nombre del objeto"<<endl;
                cin>>nombreGuardar;
                bool encontro=false;
                for(std::list<Objeto>::iterator it=objetos.begin(); it != objetos.end();it++){
                    if((*it).getNombre() == nombreGuardar){
                            (*it).verticeCercanoArbol(x,y,z);
                            encontro=true;
                    }
                }
                 if(!encontro){
                    cout<<"No se encontro el objeto"<<endl;
                }
                system("PAUSE");
                break;
            }
            case 8:{
                 float x,y,z;
                cout<<"Ingrese la coordenada en x"<<endl;
                cin>>x;
                cout<<"Ingrese la coordenada en y"<<endl;
                cin>>y;
                cout<<"Ingrese la coordenada en z"<<endl;
                cin>>z;
                if(objetos.size()==0){
                    cout<<"No se han cargado objetos al sistema"<<endl;
                }
                else{
                     verticeCercanoTotalArbol(objetos,x,y,z);
                }
                system("PAUSE");
                break;
            }
            case 9:{
                cout<<"Ingrese el nombre del objeto que desea calcular"<<endl;
                cin>>nombreGuardar;
                bool encontro=false;
                for(std::list<Objeto>::iterator it=objetos.begin(); it != objetos.end();it++){
                    if((*it).getNombre() == nombreGuardar){
                            (*it).verticesEsquinas();
                            encontro=true;
                    }
                }
                if(!encontro){
                    cout<<"No se encontro el objeto"<<endl;
                }
                system("PAUSE");
                break;
            }
            case 10:{
                cout<<"Ingrese el nombre del objeto que desea calcular"<<endl;
                cin>>nombreGuardar;
                bool encontro=false;
                for(std::list<Objeto>::iterator it=objetos.begin(); it != objetos.end();it++){
                    if((*it).getNombre() == nombreGuardar){
                            (*it).rutaCorta();
                            encontro=true;
                    }
                }
                if(!encontro){
                    cout<<"No se encontro el objeto"<<endl;
                }
                system("PAUSE");
                break;
            }
            case 11:{
                cout<<"Ingrese el nombre del objeto que desea calcular"<<endl;
                cin>>nombreGuardar;
                bool encontro=false;
                for(std::list<Objeto>::iterator it=objetos.begin(); it != objetos.end();it++){
                    if((*it).getNombre() == nombreGuardar){
                            (*it).rutaCortaCentro();
                            encontro=true;
                    }
                }
                if(!encontro){
                    cout<<"No se encontro el objeto"<<endl;
                }
                system("PAUSE");
                break;
            }
            case 12:{
                salir=true;
                cout<<"HASTA LUEGO"<<endl;
                system("PAUSE");
                break;
            }
        }
        system("cls");
    }

    cout<<endl;
    system("PAUSE");

}
