#ifndef __HASH_TABLE_H_
#define __HASH_TABLE_H_

#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>
//Para el procesamiento de la ip es importante utilizar un tipo de numero mas grande que 4e^9
#include <stdio.h>

#include "HashNode.h"
#include "Graph.h"
//Clase para el manejo de las ips que se necesiten ordenar
#include "IpConex.h"

class HashTable{
  private:
    std::vector<HashNode> table;
    int size;
    int maxSize; // preferible un numero primo
    int graphSize;
    std::string archivo;
    std::vector<std::vector<std::string>> pares;
    std::vector<std::vector<std::string>> IPinterna;
    void add(std::string, int, int);
    int partition(std::vector<IPConex>&, int, int);
  public:
    HashTable(std::string doc, int selectedMaxSize);
    int getHashIndex(unsigned long int keyVal);
    int getSize();
    void print();
    void add_Graph();
    void calculoAlpha();
    int find(std::string);
    void getIPSummary(std::string);
    void quickSort(std::vector<IPConex>&, int, int);
};

HashTable::HashTable(std::string doc, int selectedMaxSize){
  maxSize = selectedMaxSize;
  size = 0;
  archivo = doc;
  table = std::vector<HashNode>(maxSize);
  //Realizamos las funciones del grafo
  Graph g1(archivo);
  g1.assignGrade();
  g1.assignAristasInternas();
  graphSize = g1.getNumNodes();
  pares.resize(graphSize+1);
  //Llenamos los vectores

  //Regresa los datos del grafo como, IP, conexiones desde la ip, conexiones hacia la IP
  pares = g1.regresaNodos();
  //Regresa las ips conectadas desde una ip
  IPinterna = g1.regresaIpInterna();
  std::cout << "--->Success!" << std::endl;
}

//Funcion para obtener el indice hash, en otras palabras la funcion hash
int HashTable::getHashIndex(unsigned long int keyVal) {
  return keyVal % maxSize;
}

//Funcion para añadir datos a la tabla hash
void HashTable::add(std::string keyVal, int valor1, int valor2){
  if (size == maxSize) {
    throw std::out_of_range("Hash Table is full");
  }
  //Procesamos la IP recibida
  std::vector<int> ip_separar;
  std::string data = keyVal;
  std::stringstream streamData(data);
  std::string valor;
  //La separamos en 4
  while(std::getline(streamData, valor, '.')) {
    ip_separar.push_back(stoi(valor));
  }

  //Se utiliza un unsigned long int ya que algunas ips llevan su conversion a numeros extremadamente grandes
  unsigned long int ipNumero = 0;
  //Ip4*256^3 + Ip3*256^2 + Ip2*256^1 + Ip1
  int ip_size = ip_separar.size();
  for(int i = 0; i<ip_size; i++){
    if(i == 0){
      ipNumero = ip_separar[i]*((unsigned long int)256*(unsigned long int)256*(unsigned long int)256);
    }
    else if(i == 1){
      ipNumero += ip_separar[i]*((unsigned long int)256*(unsigned long int)256);
    }
    else if(i == 2){
      ipNumero += ip_separar[i]*256;
    }
    else{
      ipNumero += ip_separar[i];
    }
  }
  //Creamos el indice en base al modulo del tamaño de la tabla
  int hashVal = getHashIndex(ipNumero); 
  HashNode node = table.at(hashVal);
  //Si esta vacio la celda lo insertamos ahi
  if (node.getStatus() != 1) {
    node.setKey(keyVal);
    
    node.setData(valor1);
    
    node.setData2(valor2);
    
    table.at(hashVal) = node;
  }
  else{
    //Esta ocupada la celda
    int i = 1;
    //Direccion abierta por metodo cuadratico
    int currentHashVal = getHashIndex(hashVal + i * i);
    HashNode currentNode = table.at(currentHashVal);

    while (currentNode.getStatus() == 1) {
      i++;
      currentHashVal = getHashIndex(hashVal + i * i);
      currentNode = table.at(currentHashVal);
    }
    currentNode.setKey(keyVal);
    currentNode.setData(valor1);
    currentNode.setData2(valor2);
    node.addToOverflow(currentHashVal);
    table.at(currentHashVal) = currentNode;
    table.at(hashVal) = node;
  }
  size++;
} 

void HashTable::print(){
  std::cout << "Content of the hash table: " << std::endl;
  for (int i = 0; i < maxSize; i++) {
    if (table.at(i).getStatus()==1){ // Cell is used
      std::cout << "Cell " << i << ": " << table.at(i).getKey() << ", " << table.at(i).getData() << ", " << table.at(i).getData2() << ", Overflow size: " << table.at(i).getOverflowSize() << std::endl; 
    }
    else{
      std::cout << "Cell " << i << ":" << "---------------------------------------" << std::endl;
    }
  }
}

//Funcion para llenar la tabla hash con con los datos del grafo
//Complejidad de la funcion: O(n + m)
void HashTable::add_Graph(){
  std::cout << "\n--->Creando tabla hash" << std::endl;
  int colisionesTotales = 0;
  for(int i = 0; i<graphSize; i++){
    add(pares[i][0], stoi(pares[i][1]), stoi(pares[i][2]));
  }
  for(int j = 0; j<maxSize; j++){
    colisionesTotales+=table.at(j).getOverflowSize();
  }
  std::cout << "--->Success!" << std::endl;
  std::cout << "\nColisiones totales: " << colisionesTotales << std::endl;
  std::cout << std::endl;
}

//Funcion para obtener datos generales de la tabla hash
//Obtendremos la porbabilidad de exito y de colision
//Aceptable, U > 8.5, alpha >75%
//Tamaño del grafo: 13370
void HashTable::calculoAlpha(){
  double alpha;
  double exitoAprox = 0;
  double colisionU = 0;
  int m = maxSize;
  int n = 13370;
  alpha = ((double)n / (double)m);
  exitoAprox = (1 + (1/(1-alpha)))*0.5; 
  colisionU = (1+(1/((1-alpha)*(1-alpha))))*0.5;

  std::cout << "\nAlpha: " << alpha << std::endl;
  std::cout << "Alpha %: " << alpha*100 << " %" << std::endl;
  std::cout << "Exito aproximado al insertar un valor: " << exitoAprox << std::endl;
  std::cout << "Probabilidad de colision: " << colisionU << std::endl;
}

//Funcion para encontrar un valor dentro de la tabla hash
int HashTable::find(std::string keyVal) {
  std::vector<int> ip_separar;
  std::string data = keyVal;
  std::stringstream streamData(data);
  std::string valor;

  //Separamos la ip en 4 partes
  while(std::getline(streamData, valor, '.')) {
    ip_separar.push_back(stoi(valor));
  }

  unsigned long int ipNumero = 0;
  //Ip4*256^3 + Ip3*256^2 + Ip2*256^1 + Ip1
  int ip_size = ip_separar.size();
  for(int i = 0; i<ip_size; i++){
    if(i == 0){
      ipNumero = ip_separar[i]*((unsigned long int)256*(unsigned long int)256*(unsigned long int)256);
    }
    else if(i == 1){
      ipNumero += ip_separar[i]*((unsigned long int)256*(unsigned long int)256);
    }
    else if(i == 2){
      ipNumero += ip_separar[i]*256;
    }
    else{
      ipNumero += ip_separar[i];
    }
  }
  //Generamos el indice
  int hashVal = getHashIndex(ipNumero); 
  if(hashVal<0){
    hashVal = hashVal*-1;
  }
  HashNode node = table.at(hashVal);
  //La celda esta ocupada
  if (node.getStatus() == 1) {
    if (node.getKey() == keyVal) {
      return hashVal;
    }
    for (int i = 0; i < node.getOverflowSize(); i++) {
      int overflowIndex = node.getOverflowAt(i);
      if (table.at(overflowIndex).getKey() == keyVal) {
        return overflowIndex;
      }
    }
    return -1;
  }
  return -1;
}

//Algoritmo de quicksort obtenido de : https://www.geeksforgeeks.org/quick-sort/

//Complejidad total: O(n)
int HashTable::partition(std::vector<IPConex>& a, int low, int high){
  IPConex pivote = a[high];
  int i = (low - 1); 
  for (int j = low; j <= high - 1; j++){//Si tomamos a high como n-1, obtenemos que la complejidad es O(n-1) o O(n)
    if (a[j] < pivote){ 
      i++; 
      IPConex t = a[i]; 
      a[i] = a[j]; 
      a[j] = t;
    } 
  }
  IPConex t = a[i+1]; 
  a[i+1] = a[high]; 
  a[high] = t;
  return (i + 1);
}

//Complejidad total del algoritmo: O(n log n)
void HashTable::quickSort(std::vector<IPConex>& arr, int low, int high){
  if(low>=high){
    return;
  }
  else if (low < high) {
    int pivote = partition(arr, low, high);
    quickSort(arr, low, pivote - 1);
    quickSort(arr, pivote + 1, high);
  }
}


//Funcion para obtener los datos de una ip ingresada, muestra los datos de la tabla hash, asi como las conexiones hechas desde la ip
//Complejidad total seria algo como: O(n + E*M + V)
void HashTable::getIPSummary(std::string keyVal){
  //Vector donde estaran las conexiones
  std::vector<IPConex> vectorIP;
  //Resultado de la busqueda
  int busqueda = find(keyVal);
  //Resultado de la busqueda en el vector
  int index;
  if( busqueda == -1){
    std::cout << "\nLa ip no se encontro en la tabla!" << std::endl;
  }
  else{
    std::cout << "\nDatos de la ip buscada: " << std::endl;
    std::cout << "\nIP buscada\t\tConexiones desde la ip\t Conexiones hacia la ip\t\tOverflow" <<std::endl;
    std::cout << table.at(busqueda).getKey() << "\t\t\t " << table.at(busqueda).getData() << "\t\t\t" << table.at(busqueda).getData2() << "\t\t\t Overflow size: " << table.at(busqueda).getOverflowSize() << std::endl;
    //Buscamos el indice donde se encuentra la busqueda en el vector
    for(int i = 0; i<graphSize; i++){//Si tomamos el tamaño del grafo como n, su complejidad es O(n)
      if(table.at(busqueda).getKey() == pares[i][0]){
        index = i;
      }
    }
    //Imprimimos las conexiones hechas desde la ip
    std::cout << "\nConexiones desde la IP: " << std::endl;
    for(int i = 0; i<(int)IPinterna[index].size(); i++){//Tomamos el size de ip interna como M, la complejidad es O(E*M)
      //Creamos los datos para la division de ip
      std::vector<int> ip_separar;
      std::string data = IPinterna[index][i];
      std::stringstream streamData(data);
      std::string valor;
      //Separamos la ip en 4 partes
      while(std::getline(streamData, valor, '.')){//El tamaño de la ip es 4, si eso lo tomamos como E, su complejidad es O(E);
        ip_separar.push_back(stoi(valor));
      }
      //Creamos el objeto con las partes de la ip
      IPConex ipe(ip_separar[0], ip_separar[1], ip_separar[2], ip_separar[3]);
      //Lo insertamos dentro del vector
      vectorIP.push_back(ipe);
    }
    //Ordenamos el vector de forma ascendente
    quickSort(vectorIP, 0, vectorIP.size()-1);
    //imprimimos el vector
    int vec_size = vectorIP.size();
    for(int i = 0; i<vec_size ; i++){//Tomamos el size del vector como V, la complejidad es O(V)
      vectorIP[i].imprime();
    }
  }
}



#endif // __HASH_TABLE_H_
