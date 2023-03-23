#ifndef _IPCONEX_H_
#define _IPCONEX_H_

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


class IPConex{
  public:
    IPConex();
    IPConex(int, int, int, int);
    //setters
    //Ip = 123.00.23.234:1266
    void setIP1(int);
    void setIP2(int);
    void setIP3(int);
    void setIP4(int);

    //Getters
    int getIP1() const;
    int getIP2() const;
    int getIP3() const;
    int getIP4() const;

    void imprime();

    bool operator ==(const IPConex&);
    bool operator !=(const IPConex&);
    bool operator >(const IPConex&);
    bool operator <(const IPConex&);
    bool operator <=(const IPConex&);
    bool operator >=(const IPConex&);

  private:
    int ip1;
    int ip2;
    int ip3;
    int ip4;
};

//Constructor por default
IPConex::IPConex(){
  ip1 = 0;
  ip2 = 0;
  ip3 = 0;
  ip4 = 0;
}

//Constructor con parametros
IPConex::IPConex(int ip1_, int ip2_, int ip3_, int ip4_){
  ip1 = ip1_;
  ip2 = ip2_;
  ip3 = ip3_;
  ip4 = ip4_;
}


//Setters

void IPConex::setIP1(int ip1_){
  ip1 = ip1_;
}

void IPConex::setIP2(int ip2_){
  ip2 = ip2_;
}

void IPConex::setIP3(int ip3_){
  ip3 = ip3_;
}

void IPConex::setIP4(int ip4_){
  ip4 = ip4_;
}

//Getters
int IPConex::getIP1() const{
  return ip1;
}

int IPConex::getIP2() const{
  return ip2;
}

int IPConex::getIP3() const{
  return ip3;
}

int IPConex::getIP4() const{
  return ip4;
}

void IPConex::imprime(){
  cout << ip1 << "." << ip2 << "." << ip3 << "." << ip4  << endl; 
}

bool IPConex::operator==(const IPConex &other) {
    if(this->ip1 == other.ip1 && this->ip2 == other.ip2 && this->ip3 == other.ip3 && this->ip4 == other.ip4){
        return true;
    }
    else{
        return false;
    }
}

bool IPConex::operator!=(const IPConex &other) {
    if(this->ip1 != other.ip1 || this->ip2 != other.ip2 || this->ip3 != other.ip3 || this->ip4 != other.ip4){
        return true;
    }
    else{
        return false;
    }
}

bool IPConex::operator>(const IPConex &other){
    if(this->ip1 > other.ip1){
        return true;
    }
    //Los primeros son iwales
    else if(this->ip1 == other.ip1){
        //Checamos los 2°
        if(this->ip2 > other.ip2){
            return true;
        }
        else if(this->ip2 == other.ip2){
            if(this->ip3 > other.ip3){
                return true;
            }
            else if(this->ip3 == other.ip3){
                if(this->ip4 > other.ip4){
                    return true;
                }
            }
        }
    }
    return false;
}


bool IPConex::operator<(const IPConex &other){
    if(this->ip1 < other.ip1){
        return true;
    }
    //Los primeros son iwales
    else if(this->ip1 == other.ip1){
        //Checamos los 2°
        if(this->ip2 < other.ip2){
            return true;
        }
        //Los segundos son iwales
        else if(this->ip2 == other.ip2){
            //Checamos los 3°
            if(this->ip3 < other.ip3){
                return true;
            }
            //los terceros son iwales
            else if(this->ip3 == other.ip3){
                //checamos los 4°
                if(this->ip4 < other.ip4){
                    return true;
                }
            }
        }
    }
    return false;
}

bool IPConex::operator<=(const IPConex &other){
    if(this->ip1 == other.ip1 && this->ip2 == other.ip2 && this->ip3 == other.ip3 && this->ip4 == other.ip4){
        return true;
    }
    else{
        if(this->ip1 < other.ip1){
            return true;
        }
        //Los primeros son iwales
        else if(this->ip1 == other.ip1){
            //Checamos los 2°
            if(this->ip2 < other.ip2){
                return true;
            }
            else if(this->ip2 == other.ip2){
                if(this->ip3 < other.ip3){
                    return true;
                }
                else if(this->ip3 == other.ip3){
                    if(this->ip4 < other.ip4){
                        return true;
                    }
                }
            }
        }
        return false;
    }
}


bool IPConex::operator>=(const IPConex &other){
  if(this->ip1 == other.ip1 && this->ip2 == other.ip2 && this->ip3 == other.ip3 && this->ip4 == other.ip4){
    return true;
  }
  else{
    if(this->ip1 > other.ip1){
        return true;
    }
    //Los primeros son iwales
    else if(this->ip1 == other.ip1){
        //Checamos los 2°
        if(this->ip2 > other.ip2){
            return true;
        }
        else if(this->ip2 == other.ip2){
            if(this->ip3 > other.ip3){
                return true;
            }
            else if(this->ip3 == other.ip3){
                if(this->ip4 > other.ip4){
                    return true;
                }
            }
        }
    }
    return false;
  }
}




#endif //IPCONEX_H