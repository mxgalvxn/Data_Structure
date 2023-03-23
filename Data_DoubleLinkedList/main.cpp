//Fernanda Monserrat Galvan Romero
//A00344712
//Act 2.3 - Actividad Integral estructura de datos lineales
//Programa para leer datos de un archivo de texto, ordenarlos y hacer una busqueda

// g++ -std=c++17 -o main -g *.cpp
//valgrind --leak-check=full ./main
//g++ -std=c++17 *.cpp -Wall
//g++ -std=c++17 -o main -O3 *.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

#include "dateTime.h"
#include "DoubleLinkedList.h"


int main(){
    //Declaraciion de variables
    DoubleLinkedList <dateTime> lista;
    int busqueda_inferior;
    int busqueda_superior;
    string inferior;
    string superior;
    string dia;
    string hora;
    string min;
    string seg;
    string mes;
   
    //Se cargan los datos a la lista doblemente ligada
    lista.cargaDatos("bitacora.txt");
    cout<<"Datos cargados"<<endl;
    int n = lista.getNumElements();
    //Se ordenan los datos
    lista.quickSortIterative();
    //Exportamos el archivo ordenado
     cout<<"Archivo de Ordenamiento Generado";
    lista.escribirArchivo(0,n);

    //Pedimos la fecha inferior a buscar
    cout << "\nIngrese la fecha inferior: " << endl;
    cout << "Ingresa el mes (Aug): ";
    cin >>mes;
    cout << "Ingresa el dia: ";
    cin>>dia;
    cout << "Ingresa la hora: ";
    cin>>hora;
    cout << "Ingresa los minutos: ";
    cin>>min;
    cout << "Ingresa los segundos: ";
    cin>>seg;

    dateTime fecha_comparacion(mes, dia, hora, min, seg, "", "");
    //Buscamos la fecha establecida en la busqueda Binaria
    busqueda_inferior = lista.binarySearch(fecha_comparacion.getDate());

    //Pedimos la fecha superior a buscar
    cout << "\nIngrese la fecha superior: " << endl;
    cout << "Ingresa el mes (Aug): ";
    cin >>mes;
    cout << "Ingresa el dia: ";
    cin>>dia;
    cout << "Ingresa la hora: ";
    cin>>hora;
    cout << "Ingresa los minutos: ";
    cin>>min;
    cout << "Ingresa los segundos: ";
    cin>>seg;

    dateTime fecha_comparacion2(mes, dia, hora, min, seg, "", "");
    //Buscamos la fecha establecida en la busqueda Binaria
    busqueda_superior = lista.binarySearch(fecha_comparacion2.getDate());

    //Exportamos el archivo con los parametros de busqueda
    lista.escribirArchivo(busqueda_inferior,busqueda_superior);
    cout<<"Archivo de Busqueda Generado";
    //Limpiamos la memoria
    lista.clear();
}