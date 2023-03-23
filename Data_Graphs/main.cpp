/*
Hecho por: Jorge Daniel Cruz Case A01634536 & Fernanda Monserrat Galvan Romero A00344712
11/27/2021

-->Compilacion

-->Debugeo
g++ -std=c++17 -g -o main *.cpp

-->Valgrind
valgrind --leak-check=full ./main < bitacoraGrafos.txt

-->Compilacion para ejecucion
g++ -std=c++17 -O3 -o main *.cpp

-->Ejecucion
./main < bitacoraGrafos.txt

-->Variables:
g++ -std=c++17 *.cpp -Wall
*/

#include <iostream>
#include <vector>
#include <chrono>
#include "Graph.h"

int main() {
  auto startTime = std::chrono::high_resolution_clock::now();
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf(); 
  
  Graph g1(1, inputInfo);
  auto endTime = std::chrono::high_resolution_clock::now();
  auto totalTime = endTime - startTime;
  
  cout << "\nTiempo de llenado del grafo: " << totalTime/std::chrono::milliseconds(1) <<" ms"<<endl;
  g1.escribeGrados();
  g1.encontrarBootMaster();
} 