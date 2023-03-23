#ifndef _IP_H_
#define _IP_H_

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


class IP{
    public:
        IP();
        IP(string, string, string, int, int, int, int, string, string, string);
        //setters
        void setMes(string);
        void setDia(string);
        void setHora(string);
        //Ip = 123.00.23.234:1266
        void setIP1(int);
        void setIP2(int);
        void setIP3(int);
        void setIP4(int);
        void setPuerto(int);
        void setError(string);
        void setCantidad(int);
        void clear();

        //Getters
        string getMes() const;
        string getDia() const;
        string getHora() const;
        int getIP1() const;
        int getIP2() const;
        int getIP3() const;
        int getIP4() const;
        int getPuerto() const;
        string getError() const;
        int getCantidad() const;

        void imprime();

        bool operator ==(const IP&);
        bool operator !=(const IP&);
        bool operator >(const IP&);
        bool operator <(const IP&);
        bool operator <=(const IP&);
        bool operator >=(const IP&);
    
    private:
        string mes;
        string dia;
        string hora;
        int ip1;
        int ip2;
        int ip3;
        int ip4;
        int puerto;
        string error;
        int cantidad;
};

//Constructor por default
IP::IP(){
    mes = "Jan";
    dia = "";
    hora = "";
    ip1 = 0;
    ip2 = 0;
    ip3 = 0;
    ip4 = 0;
    puerto = 0;
    error = "";
    cantidad = 0;
}

//Constructor con parametros
IP::IP(string mes_, string dia_, string hora_, int ip1_, int ip2_, int ip3_, int ip4_, string puerto_, string error_, string cantidad_){
    mes = mes_;
    dia = dia_;
    hora = hora_;
    ip1 = ip1_;
    ip2 = ip2_;
    ip3 = ip3_;
    ip4 = ip4_;
    puerto = stoi(puerto_);
    error = error_;
    cantidad = stoi(cantidad_);
}


//Setters
void IP::setDia(string dia_){
    dia = dia_;
}

void IP::setMes(string mes_){
    mes = mes_;
}

void IP::setHora(string hora_){
    hora = hora_;
}

void IP::setIP1(int ip1_){
    ip1 = ip1_;
}

void IP::setIP2(int ip2_){
    ip2 = ip2_;
}

void IP::setIP3(int ip3_){
    ip3 = ip3_;
}

void IP::setIP4(int ip4_){
    ip4 = ip4_;
}

void IP::setPuerto(int puerto_){
    puerto = puerto_;
}

void IP::setError(string error_){
    error = error_;
}

void IP::setCantidad(int cantidad_){
    cantidad = cantidad_;
}

//Getters
string IP::getMes() const{
    return mes;
}

string IP::getDia() const{
    return dia;
}

string IP::getHora() const{
    return hora;
}

int IP::getIP1() const{
    return ip1;
}

int IP::getIP2() const{
    return ip2;
}

int IP::getIP3() const{
    return ip3;
}

int IP::getIP4() const{
    return ip4;
}

int IP::getPuerto() const{
    return puerto;
}

string IP::getError() const{
    return error;
}

int IP::getCantidad() const{
    return cantidad;
}

void IP::imprime(){
    cout << mes << " " << dia << " " << hora << " " << ip1 << "." << ip2 << "." << ip3 << "." << ip4 << "." << puerto << " " << error << " Cant: " << cantidad << endl; 
}

void IP::clear(){
    mes = "";
    dia = "";
    hora = "";
    ip1 = 0;
    ip2 = 0;
    ip3 = 0;
    ip4 = 0;
    puerto = 0;
    error = "";
    cantidad = 0;
}

bool IP::operator==(const IP &other) {
    if(this->ip1 == other.ip1 && this->ip2 == other.ip2 && this->ip3 == other.ip3 && this->ip4 == other.ip4){
        return true;
    }
    else{
        return false;
    }
}

bool IP::operator!=(const IP &other) {
    if(this->ip1 != other.ip1 || this->ip2 != other.ip2 || this->ip3 != other.ip3 || this->ip4 != other.ip4){
        return true;
    }
    else{
        return false;
    }
}

bool IP::operator>(const IP &other){
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


bool IP::operator<(const IP &other){
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

bool IP::operator<=(const IP &other){
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


bool IP::operator>=(const IP &other){
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




#endif //IP_H