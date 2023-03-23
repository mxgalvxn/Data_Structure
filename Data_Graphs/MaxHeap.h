#ifndef __MAXHEAP_H_
#define __MAXHEAP_H_

#include<vector>
#include<iostream>

template<class T>
class MaxHeap {
  private:
    // contiene los elementos del heap
    std::vector<T> data; 
    // capacidad maxima del heap
    int maxSize;
    // tamaño actual del heap   
    int size;   
    int parent(int i);
    int left(int i);
    int right(int i);

  public:
    //Constructor
    MaxHeap(int capacity);
    //Dsetructor
    ~MaxHeap();
    //Metodos
    void push(T key);
    void pop();
    T top();
    bool isEmpty();
    int getSize();
    int getCapacity();
    void printMaxHeap();
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
    std::cout << "--->Liberando memoria del MaxHeap: " <<  this << std::endl;
    data.clear();
}

//Funcion para comprobar si el heap esta vacio
//Complejidad de la funcion: O(1) 
template <class T> 
bool MaxHeap<T>::isEmpty() {
    return (size <= 0);
}

//-->Getters
template <class T> 
int MaxHeap<T>::getSize() {
    return size;
}

template <class T> 
int MaxHeap<T>::getCapacity() {
    return maxSize;
}


//Funcion para imprimir el heap completo de mayor a menor
//Complejidad de la funcion: O(n)
template <class T> 
void MaxHeap<T>::printMaxHeap() {
    for (int i=0; i < size; i++){//tomamos size como n, la complejidad es O(n)
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

//Funcion para obtener el padre de una hoja
//Complejidad de la funcion: O(1)
template <class T> 
int MaxHeap<T>::parent(int i) {
    return (i-1)/2; 
}

//Funcion para obtener el hijo izquierdo de una hoja
//Complejidad de la funcion: O(1)
template <class T> 
int MaxHeap<T>::left(int i) {
    return (2*i + 1); 
}

//Funcion para obtener el hijo derecho de una hoja
//Complejidad de la funcion: O(1)
template <class T> 
int MaxHeap<T>::right(int i) {
    return (2*i + 2);
}

//Funcion para insertar una hoja en un heap
//Complejidad de la funcion: O(log n)
template <class T> 
void MaxHeap<T>::push(T key) {
  //El heap esta en su tamaño maximo
    
  if (size == maxSize) {
    std::cout << "Overflow: no se puede insertar la llave: " << key.first << std::endl;
    return;
  }
  
  // Insertamos la nueva llave al final del vector
  int i = size;
  data[i] = key;
  size++;
  //Reacomodamos el orden de las hojas para mantener las propiedades de un Max Heap
  while (i != 0 && data[parent(i)].second < data[i].second) {
    std::swap(data[i], data[parent(i)]);
    i = parent(i);
  }
}

//Funcion para sacar el top del Heap
//Complejidad de la funcion: O(log n)
template <class T> 
void MaxHeap<T>::pop(){
  //El heap esta vacio
  if (isEmpty()) {
      std::cout << "El MaxHeap está vacio" << std::endl;
      return;
  }
  else{
    int i = 0;
    data[0].second = 0;
    data[0].first = "";
    size--;
    std::swap(data[0], data[(size)]);
    while(data[right(i)].second != 0 && data[left(i)].second != 0 && i < size-1){
      if (data[right(i)].second > data[left(i)].second){
          std::swap(data[i], data[right(i)]);
          i = right(i);
      }
      else{
          std::swap(data[i].second, data[left(i)].second);
          i = left(i);
      }
    }
  }
}

//Funcion para obtener el top o raiz de un Max Heap, en esta caso el valor mayor
//Complejidad de la funcion: O(1)
template <class T> 
T MaxHeap<T>::top() {
  T result;
  //No hay Raiz
  if (isEmpty()) {
      std::cout << "El MaxHeap está vacio" << std::endl;
      return result;
  }
  return data[0];
}



#endif // __MAXHEAP_H_