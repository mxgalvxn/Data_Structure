/*
Hecho por: Jorge Daniel Cruz Case A01634536 & Fernanda Monserrat Galvan Romero A00344712
12/4/2021

-->Compilacion

-->Debugeo
g++ -std=c++17 -g -o main *.cpp

-->Valgrind
valgrind --leak-check=full ./main 

-->Compilacion para ejecucion
g++ -std=c++17 -O3 -o main *.cpp

-->Ejecucion
./main 

-->Variables:
g++ -std=c++17 *.cpp -Wall
*/
#include <iostream>
#include <chrono>
#include "HashTable.h"

int main() {
  auto startTime = std::chrono::high_resolution_clock::now();
  //Potencial valor: 19387, 20399, 33863
  //Valor final: 20399
  HashTable myHashTable("bitacoraGrafos.txt", 20399);
  //Se intento la ejecucion con 33863 datos y el tiempo de ejecucion se duplico
  myHashTable.calculoAlpha();
  myHashTable.add_Graph();
  
  std::string ip = "240.74.251.194";
  //Si quiere usted ingresar la ip a buscar solo descomente lo siguiente y comente lo que ya esta
  //std::string ip;
  //std::cout << "Ingrese una ip para mostrar sus datos: ";
  //std::cin>>ip;
  myHashTable.getIPSummary(ip);
  
  
  auto endTime = std::chrono::high_resolution_clock::now();
  auto totalTime = endTime - startTime;
  cout << "\nTiempo de ejecucion: " << totalTime/std::chrono::milliseconds(1) <<" ms"<<endl;
} 