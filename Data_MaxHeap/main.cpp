//Fernanda Monserrat Galván Romero
//Actividad Actividad Integral estructura de datos lineales 3.4
//Codigo para el ordenamiento y lectura del archivo "Bitacora" mediante algoritmos vistos en clase mediante un Max Heap
//04/11/2021

//-->Compilacion:

//g++ -std=c++17 -o main -g *.cpp 
//valgrind --leak-check=full ./main
//g++ -std=c++17 *.cpp -Wall
//g++ -std=c++17 -o main -O3 *.cpp

#include "MaxHeap.h"
#include "Ip.h"

#include <iostream>
#include <chrono>

using namespace std;


int main(){
    auto startTime = std::chrono::high_resolution_clock::now();
    auto startTime_cant = std::chrono::high_resolution_clock::now();

    MaxHeap <IP> lista(100000);
    try{
        lista.cargaDatos("bitacora.txt");
    }
    catch(const char* msg){
        std::cerr << msg << std::endl;
    }
    
    lista.escribirArchivo(0);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto totalTime = endTime - startTime;
    std::cout << std::endl;
    //Termina el tiempo contado
    cout << "Tiempo de llenado y ordenamiento mediante IP: " << totalTime/std::chrono::milliseconds(1) <<" ms"<<endl;

    lista.escribirArchivo(1);    
    
    auto endTime_cant = std::chrono::high_resolution_clock::now();
    auto totalTime_cant = endTime_cant - startTime_cant;
    cout << "\nTiempo de llenado y ordenamiento mediante su cantidad: " << totalTime_cant/std::chrono::milliseconds(1) <<" ms"<<endl;

}