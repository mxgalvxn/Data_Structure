//Hecho por Monserrat Galván A00344712

#ifndef _DOUBLELINKEDLIST_H_
#define _DOUBLELINKEDLIST_H_

#include <climits>
#include "Node.h"
#include "Stack.h"
#include "dateTime.h"
#include <fstream>
#include <sstream>

template <class T>
class DoubleLinkedList {
  public:
    DoubleLinkedList();
    ~DoubleLinkedList();

    //Metodos
    void addFirst(T value);
    void addLast(T value);
    T findData(int search);
    void printList();

    //Funciones usadas anteriormente
    void clear();  
    void duplicate(); 
    void removeDuplicates();
    void getReversedSublist(int, int);


    void swap(T&, T&);
    Node<T>* partition(Node<T>*, Node<T>*);
    void quickSortIterative();
    bool isgreater(Node<T>*, Node<T>*);

    //Funciones para la bitacora
    int binarySearch(time_t);
    void escribirArchivo(int,int);
    void cargaDatos(string);


    //Getters
    Node<T>* getHead();
    Node<T>* getTail();
    int getNumElements();

    private:
    Node<T>* head;
    Node<T>* tail;
    int numElements;
};

//Constructor
template<class T>
DoubleLinkedList<T>::DoubleLinkedList() {
  std::cout << "--->Creando una lista vacia" << std::endl;
  head = NULL;
  tail = NULL;
  numElements = 0;
}

//Destructor
template<class T>
DoubleLinkedList<T>::~DoubleLinkedList() {
  std::cout << "\n--->Liberando memoria de la lista" << std::endl;
  Node<T> *p, *q;
  p = head;
  while (p != NULL) {
    q = p->next;
    delete p;
    p = q;
  }
  head = NULL;
  tail = NULL;
  numElements = 0;
}

//Funcion para añadir algo al inicio de la lista
//Complejidad O(1)
template<class T>
void DoubleLinkedList<T>::addFirst(T value) {
  Node<T> *newNode = new Node<T>(value);
  if(head == NULL){
    head = newNode;
    tail = newNode;
  }
  else{
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
  }
  numElements++;
}

//Funcion para añadir algo al final de la lista
//Complejidad O(1)
template<class T>
void DoubleLinkedList<T>::addLast(T value) {
  //La lista esta vacia
  if (head == NULL) {
    addFirst(value);
  }
  else {
    Node<T> *newNode = new Node<T>(value);
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
    numElements++;
  }    
}

//Funcion findData, busca un elemento en a lista
//Regresa la posicion del elemento ingresado , si no existe regresa -1, si el arreglo esta vacio regresa -2
template<class T>
T DoubleLinkedList<T>::findData(int search) {//Complejidad O(n)
  Node<T> *p = head;
  int index = 0;
  //El arreglo esta vacio
  if(p == NULL){
    return -2;
  }
  //El arreglo no esta vacio
  else{
    while (p != NULL) {
      if (p->data == search){
        return index;
      }
      index++;
      p = p->next;
    }
    return -1;
  }
}

//Funcion para la impresion de la lista
//Complejidad total de la funcion: O(n)
template<class T>
void DoubleLinkedList<T>::printList(){
    Node<dateTime> *p;
    p = head;
    if(p == NULL){
        std::cout << "La lista esta vacia" << std::endl;
    }
    else{
        while(p!=NULL){//Si tomamos "p!=NULL" como n, la complejidad es O(n)
            p->data.imprime();
            p = p->next;
        }
    }
    std::cout << std::endl;
}

//Funcion que limpia la memoria de la lista
//Complejidad: O(n)
//Recorre todos los nodos de la lista y los devuelve a null
template<class T>
void DoubleLinkedList<T>::clear(){ 
  Node<T> *p, *q;
  p = head;
  while (p != NULL) { //O(n)
    q = p->next;
    delete p;
    p = q;
  }
  head = NULL;
  tail = NULL;
  numElements = 0;
} 


//Funcion para duplicar cada elemento de la lista
//Complejidad de la funcion: O(n)
template<class T>
void DoubleLinkedList<T>::duplicate(){
  Node<T> *p;
  p = head;

  int value, valor;
  int n = numElements-1;

  for(int i = 0; i<n; i++){//Complejidad: O(n)

    value = p->data;
    valor = p->next->data;

    Node<T> *newNode = new Node<T>(value);
    head->prev = newNode;
    newNode->next = head;
    head = newNode;
    p = p->next;

    numElements++;
    if(p->next == NULL){
      addFirst(p->data);
    }
  }  
}

//Funcion para remover los elementos duplicados en una lista
//Complejidad: O(n)
template<class T>
void DoubleLinkedList<T>::removeDuplicates(){//Complejidad O(n)
  Node<T>* p = head;
  Node<T>* q;
  if (p == NULL){
    std::cout << "La lista esta vacia" << std::endl;
    return;
  }
  while (p->next != NULL){//O(n)
    if (p->data == p->next->data){
      q = p->next->next;
      delete p->next;
      p->next = q;
    }
    else{
      p = p->next;
    }
  }
}

//Funcion para invertir una sublista entre los limites 
//Complejidad de la funcion: O(n)
template<class T>
void DoubleLinkedList<T>::getReversedSublist(int x, int y){
  Node<T> *p;
  Stack<int> myStack;
  p = head;
  int i = 0;
  int value;
  if(x>y){
    std::cout << "\nLimites invalidos, el inferior es mayor al superior!" << std::endl;
  }
  else if(y>numElements){
    std::cout << "\nLimites invalidos, el superior es demadiado grande" << std::endl;
  }
  else{
    std::cout << "\nLista original: ";
    printList();
    std::cout << "\nLos parametros: " << x << " y " << y << " son validos" <<std::endl;
    while(i<x){//O(n/x) = O()
      p = p->next;
      i++;
    }
    while(i<=y){//O(n/y) = O(n)
      myStack.push(p->data);
      i++;
      p = p->next;
    }
    i = x;
    p = head;
    for(int j = 0; j<x; j++){//O(n/x) = O(n)
      p = p->next;
    }
    while(i<=y){//O(n/y) = O(n)
      value = myStack.pop();
      p->data = value;
      p = p->next;
      i++;
    }
  }
}

//Funcion para buscar un dato dentro de la lista
//Complejidad: O(log n)
//Puede haber similitudes con el de Monserrat, esto ya que le ayude a implementarlo
template<class T>
int DoubleLinkedList<T>::binarySearch(time_t k){
  Node<dateTime> *p;
  p = head;
  int n = numElements;
  int inf = 0;
  int sup = n-1;
  int i = 0;
  while(inf<=sup){
    int m = (inf + (sup - inf) / 2);
    int fecha;
    while(i<m){
      p = p->next;
      fecha = p->data.getDate();
      i++;
    }
    i = 0;
    if (k == fecha) {
      return m;
    }
    else if (k < fecha) {
      sup = m - 1;
    }
    else {
      inf = m + 1;
    }
    p = head;
    fecha = p->data.getDate();
  }
  return -1;
}

//Funcion para la lectura del archivo "bitacora.txt"
//Funcion reciclada de la actividad integral anterior
//La funcion nos crea un objeto tipo dateTime con lo elementos de un renglos de la bitacora
//Complejidad :O(n)
template<class T>
void DoubleLinkedList<T>::cargaDatos(string doc){
    ifstream archivo;
    archivo.open(doc);
    if (archivo.is_open()){
        string linea;
        while(getline(archivo,linea)){ 
            stringstream sstr(linea); 
            string dato;
            vector<string> m;
            while (getline(sstr, dato,' ')) { 
                m.push_back(dato); 
            }  
            string problema = m[4];
            int tamanio = m.size();
            for (int i = 5; i<tamanio; i++) { 
                problema += (" " +m[5]);
                m[4] = problema;
                m.erase(m.begin()+5);
            }
            string horario = m[2];
            stringstream lineahora(horario);
            vector<string> h; 
            string hora = "";
            while (getline(lineahora, hora,':')){ 
                    h.push_back(hora);
            }  
            string horas = (h[0]);
            string minutos = (h[1]);
            string segundos = (h[2]);
            string dia = (m[1]);
            string mes = m[0];
            string ip = m[3];
            string error = m[4];
            dateTime tiempo(mes,dia,horas, minutos, segundos,ip,error);
            this->addLast(tiempo);
        }
         archivo.close(); 
    }
    else{
        cout<< "Error de lectura de archivo"<<endl;
    }
}

//Funcion reciclada de la actividad integral anterior
//Funcion para la escritura del archivo 
//Dependiendo de los limites nos crea un archivo ordenado o los resultados de la busqueda
//Complejidad: O(n)

template<class T>
void DoubleLinkedList<T>::escribirArchivo(int x, int y){
    ofstream file;
    string nombreArchivo;
    Node<dateTime> *ptr = head;
    int i = 0;
    
    if (x==0){
        nombreArchivo = "bitacora_Ordenada.txt";
    }
    else{
        nombreArchivo = "resultado_busqueda.txt";
        while(i<x){
          ptr = ptr->next;
          i++;
        }
    }
    
    file.open(nombreArchivo.c_str(), fstream::out);
    if(ptr == NULL){
        std::cout << "La lista esta vacia" << std::endl;
    }
    else{
        while(ptr!=NULL && x<y){//O(n)
        file << "\nRegistro no. " << x+1<<endl;
        file << ptr->data.getMes()<< " ";
        file << ptr->data.getDia()<<" ";
        file << ptr->data.getHoras() <<":"<<ptr->data.getMinutos()<<":"<<ptr->data.getSegundos()<<" ";
        file << ptr->data.getIP()<<" "; 
        file << ptr->data.getError()<<endl;
        ptr = ptr->next;
        x++;
        }
    }
    std::cout << std::endl;
    file.close();
}

//Funcion para intercambiar 2 datos
//Funcion en apoyo al quickSort
//Compeljidad: O(1)
template<class T>
void DoubleLinkedList<T>::swap(T &a, T &b ){ 
  T t = a; //O(1)
  a = b; 
  b = t; 
}

//Funcion para "partir" la lista
//Funcion de apoyo al quickSort
//Complejidad O(log n)
template<class T>
Node<T>* DoubleLinkedList<T>::partition(Node<T> *l, Node<T> *h){
    if ( h != NULL && l != h && l != h->next){
      T x = h->data;
      Node<T> *i = l->prev;
      Node<T> *j = l;
      while(j!=h){//O(log n)
        if(j->data <= x){
          i = (i == NULL)? l: i->next;
          swap((i->data), (j->data));
        }
        j = j->next;
      }
      i = (i == NULL)? l: i->next;
      swap((i->data), (h->data));
      return i;
    }
    else{
      return NULL;
    }
}

//Funcion para comprobar que el numero menor este al menos 2 nodos a la derecha y si es mayor que este al menos 2 nodos a la izquierda
//Funcion de apoyo a quickSort
//Complejidad O(n)
template<class T>
bool DoubleLinkedList<T>::isgreater(Node<T>* x, Node<T>* y){
  Node<T>* p;
  p = x;
  if(x != NULL && y!= NULL){
    int i = 1;
    while(p!=NULL){ //O(n)
      if(p==y){
        break;
      }
      p = p->next;
      i++;
    }
    if( i>1){
      return true;
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
}

//Funcion iterativa de ordenamiento
//Complejidad O(n log n)
template<class T>
void DoubleLinkedList<T>::quickSortIterative(){
  Node<T> *h, *l;
  Stack<Node<T>*> stack;
  l = head;
  h = tail;

  stack.push(l);
  stack.push(h);

  while(!stack.isEmpty() ){ //O(n)
    h = stack.pop();
    l = stack.pop();

    Node<T>* p = partition(l,h);//O(log n)
    if(p != NULL){
      if(isgreater(l,p->prev)){
        stack.push(l);
        stack.push(p->prev);
      }

      if(isgreater(p->next,h)){
        stack.push(p->next);
        stack.push(h);
      }
    }
  }
  
  
}

//Getters clasicos
template<class T>
Node<T>* DoubleLinkedList<T>::getHead(){
  return head;
}

template<class T>
Node<T>* DoubleLinkedList<T>::getTail(){
  return tail;
}

template<class T>
int DoubleLinkedList<T>::getNumElements() {
  return numElements;
}

#endif 