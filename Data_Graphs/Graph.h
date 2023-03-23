#ifndef __GRAPH_H_
#define __GRAPH_H_

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>

#include "Ip.h"
#include "MaxHeap.h"


class Graph {
  private:
    int numNodes;
    int numEdges;
    // Lista de adyacencia (vector de vectores)
    std::vector<std::vector<std::pair<std::string,std::string>>> adjList;

    std::vector<bool> visited;

    std::vector<int> grados;
    std::vector<std::string> Nodos;
    std::vector<IP> Aristas;
    
    void loadDirectedGraph(std::istream& input);
    void assignGrade();
    std::pair<std::string, int> escribeHeap();
    
  public:
    Graph(int representacion, std::istream& input);
    ~Graph();
    int getNumNodes();
    void printAdjList();
    void escribeGrados();   
    void encontrarBootMaster();
};



Graph::Graph(int representa, std::istream& input) {
  loadDirectedGraph(input);
  Nodos.resize(numNodes+1);
  Aristas.resize(numEdges+1);
  grados.resize(numNodes+1);
}

Graph::~Graph() {
  std::cout << "\n--->Borrando grafo" << std::endl;
  adjList.clear();
  Nodos.clear();
  Aristas.clear();
  grados.clear();
  std::cout << "--->Success!" << std::endl;
}

//Funcion para Cargar los datos a un grafo dirigido
void Graph::loadDirectedGraph(std::istream& input) {
  std::cout << "--->Creando grafo" << std::endl;
  std::string line;
  int i = 0;
  while (std::getline(input, line)) {
    //Leemos las primeras 2 lineas con numero de nodos y aristas
    if (i == 0) {
      std::vector<std::string> res;
      std::stringstream sstr(line);
      std::string data;
      //Lo separa por espacios
      while (std::getline(sstr, data, ' ')){
        res.push_back(data);
      }
      numNodes = stoi(res[0]);
      numEdges = stoi(res[1]);
      // Reservar memoria para la lista de adyacencia
      adjList.resize(numNodes+1);
      i++;
      continue; 
    }
    //Leemos los demas datos
    std::stringstream sstr(line); 
    std::string dato;
    std::vector<string> m;
    //Separa la linea por espacios 
    while (getline(sstr, dato,' ')){
      m.push_back(dato); 
    }

    //Solamente se leen los nodos
    if(i< numNodes+1){
      Nodos.push_back(m[0]);
    }
    
    //Ya pasamos de los nodos
    if(i > numNodes){
      //Construimos el mensaje de error
      string problema = m[5]; 
      int n = m.size();
      //Juntamos los errores
      for (int i = 6; i<n; i++){
        problema += (" " +m[6]);
        m[5] = problema;
        m.erase(m.begin()+6);
      }

      //Separamos la primera ip de su puerto
      std::string penultima_ip = m[3];
      std::stringstream linea_penultima_ip(penultima_ip);
      std::vector<std::string> penul_ipe;
      std::string penul_ipe_util = "";
      while(getline(linea_penultima_ip, penul_ipe_util, ':')){
        penul_ipe.push_back(penul_ipe_util);
      }

      //Separamos la segunda ip de su puerto
      std::string ultima_ip = m[4];
      std::stringstream linea_ultima_ip(ultima_ip);
      std::vector<std::string> ul_ipe;
      std::string ul_ipe_util = "";
      while(getline(linea_ultima_ip, ul_ipe_util, ':')){
        ul_ipe.push_back(ul_ipe_util);
      }

      //Creamos los datos
      std::string mes = m[0];
      std::string dia = m[1];
      std::string horario = m[2];
      std::string ip1 = penul_ipe[0];
      std::string puerto1 = penul_ipe[1];
      std::string ip2 = ul_ipe[0];
      std::string puerto2 = ul_ipe[1];
      std::string error = m[5];
      //Creamos el objeto, Mes Dia Horario IP1 IP2 Mensaje de error
      //ej. Oct 21 13:58:34 67.254.87.109:6861 76.37.140.180:1103 Failed password for illegal user root
      IP registro(mes, dia, horario, ip1, puerto1, ip2, puerto2, error);
      //Se guardan las aristas
      Aristas.push_back(registro);
    }
    i++;
  }
  //v = vertice & a = dato conectado mediante arista
  std::string v, a;
  int m, n;
  m = Nodos.size();
  n = Aristas.size();
  for(int j = 0; j<m; j++){
    for(int k = 0; k<n; k++){
      //Checamos las aristas con el nodo para encontrar sus conexiones o vecinos
      if(Nodos[j] == Aristas[k].getIP1()){
        v = Nodos[j];
        a = Aristas[k].getIP2();
        std::pair<std::string, std::string> p (v, a);
        adjList[j].push_back(p);
      }
    }
  }
  std::cout << "--->Success!" << std::endl;
}


void Graph::printAdjList(){
	std::cout << "\nAdjacency List" << std::endl;
	for (int i = 0; i <= numNodes-1; i++){
    std::cout << "vertice con valor de " << Nodos[i] << ": ";
    for (int j = 0; j < (int)adjList[i].size(); j ++){
      std::cout << " (" << adjList[i][j].second << ") ";
    }
    std::cout << std::endl;
  }
}

//Funcion para asignarle un grado a cada nodo del grafo
//Funciona mediante un vector a la par de los nodos, llenando cada casilla con el grado del nodo i
//Si tomamos n como el numero de nodos, la complejidad es O(2n+1) -> O(n)
void Graph::assignGrade(){
  std::cout << "\n--->Asignandole un grado a cada nodo del grafo" << std::endl;
  int grade;
  for(int i = 0; i<numNodes+1; i++){//O(n+1)
    grados[i] = 0;
  }
  //Contamos la cantidad de conexiones de un nodo para obtener su grado
  for(int j = 0; j<numNodes; j++){//O(n)
    grade = (int)adjList[j].size();
    grados[j] = grade;
  }
  std::cout << "--->Success!" << std::endl;
}

//Funcion para ejecutar la funcion "assignGrade" y escribir el archivo mediante su resultado
//Complejidad de la funcion: O(n)
void Graph::escribeGrados(){
  //Le asignamos un grado a los nodos del grafo
  assignGrade();
  //std::cout << "\n--->Escribiendo el archivo grados_ips" << std::endl;
  //Creamos el archivo
  std::ofstream file;
  std::string nombreArchivo = "grados_ips.txt";
  file.open(nombreArchivo.c_str(), std::fstream::out);
  //file << "Direccion IP\tGrado" << std::endl;
  int n = numNodes;
  for(int i = 0; i<n; i++){ //O(n)
    file << Nodos[i] << ", " << grados[i] << std::endl;
  }
  file.close();
  std::cout << "--->Success!" << std::endl;
}


//Funcion para crear el Max Heap y encontrar las ips con mayor grado
//Complejidad aproximada: Si tomamos numNodes como n la complejidad es O(n)
//Retorna el boot master para otra funcion
std::pair<std::string, int> Graph::escribeHeap(){
  std::cout << "\n--->Creando Max Heap" << std::endl;
  MaxHeap<std::pair<std::string, int>> myMaxHeap(100000);

  //Rellenamos el heap con <Nodo, grado>
  for(int i = 0; i<Nodos.size()-1; i++){
    std::pair<std::string, int> p (Nodos[i], grados[i]);
    myMaxHeap.push(p);
  }

  //Par para encontrar las 5 ips con mayor grado
  std::pair<std::string, int> par;
  //Se guardara la ip con mayor grado, o la primera raiz del heap
  std::pair<std::string, int> bootMaster;
  bootMaster = myMaxHeap.top(); //Guardamos al potencial bootmaster

  //Creamos el archivo
  std::ofstream file;
  std::string nombreArchivo = "mayores_grados_ips.txt";
  file.open(nombreArchivo.c_str(), std::fstream::out);
  //Realizamos 5 pops para las 5 mayores ips
  for(int i = 0; i<5; i++){
    par = myMaxHeap.top();
    file << par.first << ", " << par.second << std::endl;
    myMaxHeap.pop();
  }
  std::cout << "--->Success!" << std::endl;
  return bootMaster;
}

//Funcion para mostrar al potencial boot master
//Complejidad de la funcion O(1)
void Graph::encontrarBootMaster(){
  std::pair<std::string, int> bootMaster;
  bootMaster = escribeHeap();
  std::cout << "\nEl Boot Master esta presumiblemente en la ip: " << bootMaster.first << " ya que tiene un grado de " << bootMaster.second << std::endl;
}
#endif // __GRAPH_H_