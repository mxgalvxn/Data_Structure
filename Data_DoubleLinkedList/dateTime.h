//Hecho por: Jorge Daniel Cruz Case
//Clase para el manejo de los objetos
//21/09/2021
#ifndef _DATETIME_H_
#define _DATETIME_H_

#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class dateTime{
    public:
        //Constructores
        dateTime();
        dateTime(string, string, string, string, string, string, string);
        time_t getDate();

        //Sobrecarga
        bool operator ==(const dateTime&);
        bool operator !=(const dateTime&);
        bool operator >(const dateTime&);
        bool operator <(const dateTime&);
        bool operator >=(const dateTime&);
        bool operator <=(const dateTime&);

        //Setters
        void setMes(string);
        void setDia(int);
        void setHoras(int);
        void setMinutos(int);
        void setSegundos(int);
        void setIP(string);
        void setError(string);
        void setDate(time_t);

        //Getters
        string getMes() const;
        string getDia() const;
        string getHoras() const;
        string getMinutos() const;
        string getSegundos() const;
        string getIP() const;
        string getError() const;
        
        //Métodos
        void imprime();
    private:
        //Vector con los meses
        vector<string> meses = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        // Struct que contiene todos los datos de la fecha-hora
        struct tm dateStruct;
        // Unix timestamp (segundos transcurridos desde 00:00 hrs, Jan 1, 1970 UTC)
        time_t date;
        string mes;
        string dia;
        string horas;
        string minutos;
        string segundos;
        string ip;
        string error;
};

//Constructor por default
dateTime::dateTime(){
    mes = "Jan";
    dia = "";
    horas = "";
    minutos = "";
    segundos = "";
    ip = "";
    error = "";
}

//Constructor con parámetros con lineamientos de fecha
dateTime::dateTime(string mes_, string dia_, string horas_, string minutos_, string segundos_, string ip_, string error_) {
    mes = mes_;
    dia = dia_;
    horas = horas_;
    minutos = minutos_;
    segundos = segundos_;
    ip = ip_;
    error = error_;

    // Almacenar los campos de la fecha-hora en el struct tm
    dateStruct.tm_sec = stoi(segundos_);
    dateStruct.tm_min = stoi(minutos_);
    dateStruct.tm_hour = stoi(horas_);
    dateStruct.tm_mday = stoi(dia_);
    dateStruct.tm_isdst = 0; 
    for (int i=0; i < meses.size(); i++) {
        if (meses[i]==mes)
        dateStruct.tm_mon = i;
    }
    dateStruct.tm_year = 2021 - 1900;  // Asumimos el año 2021
    // Obtener el Unix timestamp a partir del struct tm anterior 
    date = mktime(&dateStruct);
}

//Setters
void dateTime::setMes(string mes_){
    mes = mes_;
}

void dateTime::setDia(int dia_){
    dia = dia_;
}

void dateTime::setHoras(int horas_){
    horas = horas_;
}

void dateTime::setMinutos(int minutos_){
    minutos = minutos_;
}

void dateTime::setSegundos(int segundos_){
    segundos = segundos_;
}

void dateTime::setIP(string ip_){
    ip = ip_;
}

void dateTime::setError(string error_){
    error = error_;
}

void dateTime::setDate(time_t date_){
    date = date_;
}

//Getters
string dateTime::getMes() const{
    return mes;
}

string dateTime::getDia() const{
    return dia;
}

string dateTime::getHoras() const{
    return horas;
}

string dateTime::getMinutos() const{
    return minutos;
}

string dateTime::getSegundos() const{
    return segundos;
}

time_t dateTime::getDate() {
  return date;
}

string dateTime::getIP() const{
    return ip;
}

string dateTime::getError() const{
    return error;
}

//Sobrecarga de operadores
bool dateTime::operator==(const dateTime &other) {
  return this->date == other.date;
}

bool dateTime::operator!=(const dateTime &other) {
  return this->date != other.date;
}

bool dateTime::operator>(const dateTime &other) {
  return this->date > other.date;
}

bool dateTime::operator<(const dateTime &other) {
  return this->date < other.date;
}

bool dateTime::operator>=(const dateTime &other) {
  return this->date >= other.date;
}

bool dateTime::operator<=(const dateTime &other) {
  return this->date <= other.date;

}
void dateTime::imprime(){
    cout << mes << " " << dia << " " << horas << ":" << minutos << ":" << segundos << " " <<ip << " " << error << " " << date<< endl;
}

#endif