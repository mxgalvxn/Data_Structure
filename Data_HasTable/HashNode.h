#ifndef __HASH_NODE_H_
#define __HASH_NODE_H_

#include <vector>
#include <algorithm>
#include <iterator>


class HashNode {

  private:
    std::string key;
    int data;
    int data2;
    int status;  // 0 vacio, 1 datos, 2 borrado
    std::vector<int> overflow; // used to easily find collision elements  
  public:
    HashNode();
    //Getters
    std::string getKey();
    int getData();
    int getData2();
    int getStatus();

    //Setters
    void setKey(std::string keyVal);
    void setData(int dataVal);
    void setData2(int dataVal2);

    void clearData();
    void addToOverflow(int hashIndex);
    int getOverflowSize();
    int getOverflowAt(int index);
    void removeFromOverflow(int value);  
};


HashNode::HashNode() {
  key = "";
  status = 0;
}

std::string HashNode::getKey() {
  if (status != 1) throw "Invalid operation: Empty node";
  return key;
}

int HashNode::getData() {
  return data;
}

int HashNode::getData2() {
  return data2;
}

int HashNode::getStatus() {
  return status;
}

void HashNode::setKey(std::string keyVal) {
  key = keyVal;
}

void HashNode::setData(int dataVal) {
  if (status == 1) throw "Node has been taken";
  data = dataVal;
  status = 1;
}

void HashNode::setData2(int dataVal2) {
  //if (status == 1) throw "Node has been taken";
  data2 = dataVal2;
  status = 1;
}

void HashNode::clearData() {
  status = 0;
}

void HashNode::addToOverflow(int hashIndex) {
  overflow.push_back(hashIndex);
}

int HashNode::getOverflowSize() {
  return overflow.size();
}

int HashNode::getOverflowAt(int index) {
  return overflow[index];
}

void HashNode::removeFromOverflow(int value) {
  std::vector<int>::iterator it = std::find(overflow.begin(), overflow.end(), value);
  // If element was found remove it
  if (it != overflow.end()) {
    // remove element from overflow vector 
    overflow.erase(overflow.begin()+(it - overflow.begin()));
  }
}

#endif // __HASH_NODE_H_