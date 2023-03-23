//Fernanda Monserrat Galván Romero
//A00344712

#ifndef __MAXHEAP_H_
#define __MAXHEAP_H_

#include "Ip.h"

#include<vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>


using namespace std;

template<class T>
class MaxHeap {
    private:
        std::vector<T> data;  
        int maxSize; 
        int size;   
        int parent(int i);
        int left(int i);
        int right(int i);
    public:
        MaxHeap(int capacity);
        ~MaxHeap();
        void push(T key);
        void pop();
        T top();
        bool isEmpty();
        int getSize();
        int getCapacity();

        void printMaxHeap();
        void escribirArchivo(int);
        void cargaDatos(string);

        void heapify_sort_cant(int, int);
        void heapSort_cant();
        void heapify_sort_ip(int, int);
        void heapSort_ip();;
       
};

//Constructor
template <class T> 
MaxHeap<T>::MaxHeap(int capacity) {
    std::cout << "--->Creando un MaxHeap: " <<  this << std::endl;
    size = 0;
    maxSize = capacity;
    data.resize(maxSize);
}

//Dsetructor
template <class T> 
MaxHeap<T>::~MaxHeap() {
    std::cout << "\n--->Liberando memoria del MaxHeap: " <<  this << std::endl;
    data.clear();
}


//Funcion reciclada de la actividad 2.3
//Complejidad total: O(n)
template<class T>
void MaxHeap<T>::cargaDatos(string doc){
    std::cout << "\n--->Llenando el Heap!" << std::endl;
    ifstream archivo;
    archivo.open(doc);
    if (archivo.is_open()){//Complejidad total: O(n)
        string linea;
        while(getline(archivo,linea)){//Complejidad total: O(1)*O(1)*O(n) = O(n)
            stringstream sstr(linea); 
            string dato;
            vector<string> m;
            while (getline(sstr, dato,' ')){ //Complejidad: O(1)
                m.push_back(dato); 
            }
            string problema = m[4];
            int tamanio = m.size();
            for (int i = 5; i<tamanio; i++){ //Complejidad: O(n)
                problema += (" " +m[5]);
                m[4] = problema;
                m.erase(m.begin()+5);
            }
            string ipes = m[3];
            stringstream lineaIpe(ipes);
            vector<string> ip;
            string ip_util = "";
            while (getline(lineaIpe, ip_util,'.')){//Complejidad: O(1) 
                ip.push_back(ip_util);
            }
            string ip1 = ip[3];
            stringstream lineaIP(ip1);
            vector<string> b;
            string ipp = "";
            while (getline(lineaIP, ipp,':')){ //Complejidad del while: O(1)
                b.push_back(ipp); 
            }
            string horas = m[2];
            string dia = m[1];
            string mes = m[0];
            string error = m[4];
            int ipp1 = stoi(ip[0]); 
            int ipp2 = stoi(ip[1]); 
            int ipp3 = stoi(ip[2]); 
            int ipp4 = stoi(b[0]); 
            string puerto = b[1];
            IP registro (mes, dia ,horas, ipp1, ipp2, ipp3, ipp4, puerto, error, "1");
            this->push(registro);
        }
        archivo.close(); 
        
        this->heapSort_ip();
        int cantidad = 1;
        int cantidadTotal = 0;
        for(int i = 0; i<size; i++){ //Complejidad del ciclo O(n)
            if(data[i] == data[i+1]){
                data[i].setCantidad(cantidad);
                cantidad++;
            }
            else{
                data[i].setCantidad(cantidad);
                cantidadTotal = data[i].getCantidad();

                for(int k = i-(cantidadTotal-1); k<i; k++){ //Complejidad similar a O(n/i)
                    data[k].setCantidad(cantidadTotal);
                }
                cantidad = 1;
                
            }
        }
        cout << "Lectura realizada con exito " << endl;
    }
    else{
        cout<< "Error de lectura de archivo"<<endl;
    }
}

//Funcion reciclada de la actividad 2.3
//Complejidad aproximada de la funcion: O(n)
template<class T>
void MaxHeap<T>::escribirArchivo(int o){
    if (o == 0){
        std::cout << "\n--->Creando el archivo bitacora_Ordenada.txt" << std::endl;
        ofstream file;
        string nombreArchivo = "bitacora_Ordenada.txt";
        file.open(nombreArchivo.c_str(), fstream::out);
        int n = this->getSize();
        for (int i = 0;  i <n;  i++){//Complejidad: O(n)
            file << data[i].getMes() << " " << data[i].getDia() << " " << data[i].getHora() << " " << data[i].getIP1() << "." << data[i].getIP2() << "." << data[i].getIP3() << "." << data[i].getIP4() << "." << data[i].getPuerto() << " " << data[i].getError()<< endl;

        }
        file.close();
        cout << "Archivo Escrito con exito" << endl;
    }
    else{

        std::cout << "\n--->Creando el archivo ips_con_mayor_acceso.txt" << std::endl;
        int num = 0;
        ofstream file;
        std::vector <T> m;
        string nombreArchivo = "ips_con_mayor_acceso.txt";
        file.open(nombreArchivo.c_str(), fstream::out);
        for(int i = 0; i<size; i++){
            if(data[i]!=data[i+1]){
                m.push_back(data[i]);
            }
        }
        int n = size;
        for(int i = 0; i<n; i++){
            this->pop();
        }
        for(int i = 0; i<m.size(); i++){
            this->push(m[i]);
        }

        this->heapSort_cant();
        for(int i = 0; i<size; i++){ //Complejidad: O(n)
            if(num<5){
                file << data[i].getIP1() << "." << data[i].getIP2() << "." << data[i].getIP3() << "." << data[i].getIP4() << ":" << data[i].getPuerto()<<" Cantidad de repeticiones: " << data[i].getCantidad() << endl;
                num++;
            }
        }
        file.close();
        cout << "Archivo escrito con exito " << endl;
    }
}



//Funcion reciclada de la tarea 3.2
//Complejidad de la funcion: O(1) 
template <class T> 
bool MaxHeap<T>::isEmpty() {
    return (size <= 0);
}

template <class T> 
int MaxHeap<T>::getSize() { return size;}

template <class T> 
int MaxHeap<T>::getCapacity() { return maxSize;}

//Funcion reciclada de la tarea 3.2
//Complejidad de la funcion: O(n)
template <class T> 
void MaxHeap<T>::printMaxHeap() {
    for (int i=0; i < size; i++){//tomamos size como n, la complejidad es O(n)
        data[i].imprime();
    }
    std::cout << std::endl;
}

//Funcion reciclada de la tarea 3.2
//Complejidad de la funcion: O(1)
template <class T> 
int MaxHeap<T>::parent(int i) {
    return (i-1)/2; 
}

//Funcion reciclada de la tarea 3.2
//Complejidad de la funcion: O(1)
template <class T> 
int MaxHeap<T>::left(int i) {
    return (2*i + 1); 
}

//Funcion reciclada de la tarea 3.2
//Complejidad de la funcion: O(1)
template <class T> 
int MaxHeap<T>::right(int i) {
    return (2*i + 2);
}

//Funcion reciclada de la tarea 3.2
//Complejidad de la funcion: O(log n)
template <class T> 
void MaxHeap<T>::push(T key) {
    if (size == maxSize) {
        std::cout << "Overflow" << std::endl;
        return;
    }
    int i = size;
    data[i] = key;
    size++;
    while (i != 0 && data[parent(i)] < data[i]) {
        std::swap(data[i], data[parent(i)]);
        i = parent(i);
    }
}

//Funcion reciclada de la tarea 3.2
//Complejidad de la funcion: O(log n)
template <class T> 
void MaxHeap<T>::pop(){
    if (isEmpty()) {
        std::cout << "El MaxHeap está vacio" << std::endl;
        return;
    }
    else{
        int i = 0;
        data[0].clear();
        size--;
        std::swap(data[0], data[(size)]);
        while(data[right(i)].getDia() != "" && data[left(i)].getDia() != "" && i < size-1){
            if (data[right(i)] > data[left(i)]){
                std::swap(data[i], data[right(i)]);
                i = right(i);
            }
            else{
                std::swap(data[i], data[left(i)]);
                i = left(i);
            }
        }
    }
}
//Funcion reciclada de la actividad 3.2
//Complejidad de la funcion: O(1)
template <class T> 
T MaxHeap<T>::top(){
    IP registro ("", "" ,"", 0, 0, 0, 0, "0", "", "1");;
    if (isEmpty()) {
        std::cout << "El MaxHeap está vacio" << std::endl;
        return registro;
    }
    return data[0];
}

//-->Heap sort obtenido de la pagina: https://www.geeksforgeeks.org/heap-sort/
template <class T>
void MaxHeap<T>::heapify_sort_ip(int n, int i){
    int largest = i; 
    int l = 2 * i + 1;
    int r = 2 * i + 2; 
    if (l < n && data[l] > data[largest]){
        largest = l;
    }
    if (r < n && data[r] > data[largest]){
        largest = r;
    }
    if (largest != i) {
        std::swap(data[i], data[largest]);
        heapify_sort_ip(n, largest);
    }
}

//Funcion para ordenar el Heap mediante las IPs
template <class T>
void MaxHeap<T>::heapSort_ip(){
    int tamanio = this->getSize();
    for (int i = tamanio / 2 - 1; i >= 0; i--)
        heapify_sort_ip(tamanio, i);
 
    for (int i = tamanio - 1; i > 0; i--) {
        std::swap(data[0], data[i]);
        heapify_sort_ip(i, 0);
    }
}



//--> Ordenamiento a base de la cantidad de veces que se repite una IP
template <class T>
void MaxHeap<T>::heapify_sort_cant(int n, int i){
    int largest = i; 
    int l = 2 * i + 1;
    int r = 2 * i + 2; 

    if (l < n && data[l].getCantidad() < data[largest].getCantidad()){
        largest = l;
    }

    if (r < n && data[r].getCantidad() < data[largest].getCantidad()){
        largest = r;
    }

    if (largest != i) {
        std::swap(data[i], data[largest]);
        heapify_sort_cant(n, largest);
    }
}


template <class T>
void MaxHeap<T>::heapSort_cant(){
    int tamanio = this->getSize();
    for (int i = tamanio / 2 - 1; i >= 0; i--){
        heapify_sort_cant(tamanio, i);
    }
    for (int i = tamanio - 1; i > 0; i--){
        std::swap(data[0], data[i]);
        heapify_sort_cant(i, 0);
    }
}

//-->Fin del Heap sort


#endif // __MAXHEAP_H_