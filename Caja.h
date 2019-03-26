#ifndef CAJA_H
#define CAJA_H
#include<string>
#include<iostream>
#include<fstream>
#include<list>
#include "Objeto.h"
using namespace std;
class Caja
{
    public:
            list<float>puntos;
        Caja(string nombre,list<float> puntos,list<float>minMax){
             this->nombre=nombre;
              this->puntos=puntos;
              this->minMax=minMax;
        }
        list<float> getPuntos(){
            return this->puntos;
        }
         list<float> getMinMax(){
            return this->minMax;
        }
        string getNombre(){
            return this->nombre;
        }
        void setPuntos(list<float> x){
            this->puntos=x;
        }
        void setMinMax(list<float> x){
            this->minMax=x;
        }
        void setNombre(string x){
            this->nombre=x;
        }
        void imprimirCaja(){
             int h=0,s=0;
        cout<<"Nombre de la caja: "<<nombre<<endl;
        cout<<"PUNTO MINIMO ";
         for(std::list<float>::iterator it=minMax.begin(); it != minMax.end();it++){
              cout<<*it<<" ";
               if(s==2){
                cout<<endl<<"PUNTO MAXIMO ";
                s++;
               }
               if(h==2){
                    h=0;
               }
               else{
                    h++;
                    s++;
               }
         }
         cout<<endl;
            cout<<"PUNTOS DE LA CAJA ENVOLVENTE"<<endl;
            for(std::list<float>::iterator it=puntos.begin(); it != puntos.end();it++){
                 cout<<*it<<" ";
               if(h==2){
                    cout<<endl;
                    h=0;

               }
               else{
                    h++;
               }
            }
        }
        void escribirDatos(string x){
            ofstream salida((x+".doc").c_str(),ios::out);
             int h=0,s=0;
        salida<<"Nombre de la caja: "<<nombre<<endl;
        salida<<"PUNTO MINIMO ";
         for(std::list<float>::iterator it=minMax.begin(); it != minMax.end();it++){
              salida<<*it<<" ";
               if(s==2){
                salida<<endl<<"PUNTO MAXIMO ";
                s++;
               }
               if(h==2){
                    h=0;
               }
               else{
                    h++;
                    s++;
               }
         }
         salida<<endl;
            salida<<"PUNTOS DE LA CAJA ENVOLVENTE"<<endl;
            for(std::list<float>::iterator it=puntos.begin(); it != puntos.end();it++){
                 salida<<*it<<" ";
               if(h==2){
                    salida<<endl;
                    h=0;

               }
               else{
                    h++;
               }
            }
        }
    protected:

    private:
        list<float> minMax;
        string nombre;
};

#endif // CAJA_H
