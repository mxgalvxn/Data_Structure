#ifndef _IP_H_
#define _IP_H_

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


class IP{
  public:
    IP();
    IP(string, string, string, string, string, string, string, string);
    //setters
    void setMes(string);
    void setDia(string);
    void setHora(string);
    //Ip = 123.00.23.234:1266
    void setIP1(string);
    void setIP2(string);
    void setPuerto1(string);
    void setPuerto2(string);
    void setError(string);

    //Getters
    string getMes() const;
    string getDia() const;
    string getHora() const;
    string getIP1() const;
    string getPuerto1() const;
    string getIP2() const;
    string getPuerto2() const;
    string getError() const;

    void imprime();
  
  private:
    string mes;
    string dia;
    string hora;
    string ip1;
    string puerto1;
    string ip2;
    string puerto2;
    string error;
};

//Constructor por default
IP::IP(){
    mes = "Jan";
    dia = "";
    hora = "";
    ip1 = "";
    puerto1 = "";
    ip2 = "";
    puerto2 = "";
    error = "";
}

//Constructor con parametros
IP::IP(string mes_, string dia_, string hora_, string ip1_, string _puerto1, string ip2_, string _puerto2, string error_){
    mes = mes_;
    dia = dia_;
    hora = hora_;
    ip1 = ip1_;
    ip2 = ip2_;
    error = error_;
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

void IP::setIP1(string ip1_){
    ip1 = ip1_;
}

void IP::setIP2(string ip2_){
    ip2 = ip2_;
}

void IP::setError(string error_){
  error = error_;
}

void IP::setPuerto1(string puerto1_){
  puerto1 = puerto1_;
}

void IP::setPuerto2(string puerto2_){
  puerto2 = puerto2_;
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

string IP::getIP1() const{
    return ip1;
}

string IP::getIP2() const{
  return ip2;
}


string IP::getError() const{
  return error;
}

string IP::getPuerto1() const{
  return puerto1;
}

string IP::getPuerto2() const{
  return puerto2;
}

void IP::imprime(){
  std::cout << mes << " " << dia << " " << hora << " " <<ip1 << ": " << puerto1 << " " << ip2 << ": " << puerto2 << " " << error << std::endl;
}



#endif //IP_H