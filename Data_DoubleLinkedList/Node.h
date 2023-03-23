#ifndef _NODE_H_
#define _NODE_H_

  #include<iostream>

  template <class T>
  class Node { 
  public: 
      T data; 
      Node<T>* next;
      Node<T>* prev;
      Node();
      void print();
      Node(T);        
  }; 

  template<class T>
  Node<T>::Node(){
      data = 0;
      next = NULL;
      prev = NULL;
  }
  template<class T>
  Node<T>::Node(T val){
      data = val;
      next = NULL;
      prev = NULL;
  }
template<class T>
void Node<T>::print(){
    std::cout << data<< std::endl;
}
#endif // _NODE_H_