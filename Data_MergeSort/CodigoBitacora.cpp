//Act 1.3 - Actividad Integral de Conceptos Básicos y Algoritmos Fundamentales (Evidencia Competencia)
//Codigo de busqueda de datos
//Hecho por Fernanda Monserrat Galván Romero

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include "dateTime.h"
using namespace std;

//Función para la lectura de los textos
//Complejidad total: O(1) o constante
void cargaDatos(string doc, vector <dateTime*>& lista){
    ifstream archivo;
    archivo.open(doc);
    int contador = 0;
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
            int horas = stoi(h[0]);
            int minutos = stoi(h[1]);
            int segundos = stoi(h[2]);
            int dia = stoi(m[1]);
            string mes = m[0];
            string ip = m[3];
            string error = m[4];
            m.clear();
            h.clear();
            lista.push_back(new dateTime(mes,dia,horas, minutos, segundos,ip,error));
        }
         archivo.close(); 
    }
    else{
        cout<< "Error de lectura de archivo"<<endl;
    }
}

//La complejidad es de O(n)
void merge(vector<dateTime*>& a, int low, int mid, int high, vector<int>& s) {
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 = high - mid;
    dateTime* left[n1];
    dateTime* right[n2];
  
    for (i = 0; i < n1; i++){
        left[i] = a[low + i]; 
    }
        
    for (j = 0; j < n2; j++){
        right[j] = a[mid + 1 + j];
    }
     
    i = j = 0; 
    k = low;
    while (i < n1 && j < n2) {
        s[0]++;
        if (left[i]->getDate() <= right[j]->getDate()) {
            a[k] = left[i];
            i++;
        }
        else {
            a[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        s[1]++;
        a[k] = left[i];
        i++;
        k++;
    }
  
    while (j < n2) {
        s[1]++;
        a[k] = right[j];
        j++;
        k++;
  }
}

//Algoritmo de ordenamiento por fusion (Merge Sort)
//Complejidad total: O(n log(n)) 
void ordenaMerge(vector<dateTime*>& a, int low, int high, vector<int>& s) { 
    if (low >= high) {
        return; 
    }
    int m = low + (high - low)/2;
    //Complejidad: O(n^d) para a,b,d > 0
    ordenaMerge(a, low, m, s);  
    ordenaMerge(a, m+1, high,s); 
    merge(a, low, m, high, s); 
    
    
}

//Algoritmos para la busqueda binaria
//Complejidad O(log2 (n)) utilizando la complejidad temporal promedio
int busquedaBinaria(vector<dateTime*>& a, time_t k) {
    int n = a.size();
    int inferior = 0;
    int superior = n - 1;
    while (inferior <= superior) {
        int m = (inferior + (superior - inferior) / 2);
        int fecha = a[m]->getDate();
        if (k == fecha) {
            return m;
        }
        else if (k < fecha) {
            superior = m - 1;
        }
        else {
        inferior = m + 1;
        }
    }
    return -1;  
}


//Función para imprimir el vector
//Complejidad total: O(n)
void printVector(vector <dateTime*>& lista, int total, int inicio){
    cout<<endl;
    cout<<"Resultado: "<< (total-inicio)+1 << " registros";
    cout<<endl;
    for (int i=inicio;  i <=total;  i++){// Complejidad es O(n)
            lista[i]->imprime();
    }
    cout<<endl;
}

void escribirArchivo(vector <dateTime*>& lista){
    ofstream file;
    string nombreArchivo = "bitacora_Ordenada.txt";
    file.open(nombreArchivo.c_str(), fstream::out);
    int total = lista.size();
    for (int i=0;  i <total;  i++){
        file << "Registro " << i+1<<endl;
        file<<"\n";
        file << "Dia: "<< lista[i]->getDia()<<endl;
        file << "Mes: "<< lista[i]->getMes() <<endl;
        file << "Hora: "<<  lista[i]->getHoras() <<":"<<lista[i]->getMinutos()<<":"<<lista[i]->getSegundos()<<endl;
        file << "IP: "<< lista[i]->getIP() <<endl; 
        file << "Causa del problema: "<< lista[i]->getError()<<endl;
        file<<"\n";

    }
    file.close();
}


int main(){ 
    auto startTime = std::chrono::high_resolution_clock::now();

    string mes_inferior, mes_superior;

    vector<int> solucion{0,0};
    vector<string> b{};
    vector <dateTime*> lista;
    vector <dateTime*> fecha;
    lista.clear();
    fecha.clear();
    dateTime fecha1;
    dateTime* fecha2;
    dateTime* fecha3;

    int busqueda_inferior;
    int busqueda_superior;
    int inferior;
    int superior;
    int dia_inferior;
    int dia_superior;
    int hora_inferior;
    int hora_superior;
    int min_inferior;
    int min_superior;
    int seg_inferior;
    int seg_superior;
    int total = b.size() / 5;
    bool inferior_busq = false;
    bool superior_busq = false;

    cargaDatos("bitacora.txt", lista);
    ordenaMerge(lista, 0, lista.size()-1, solucion);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto totalTime = endTime - startTime;
    
    escribirArchivo(lista);

    cout << "Tiempo de llenado y ordenamiento: " << totalTime/std::chrono::milliseconds(1) <<" ms"<<endl;
    
    while(inferior_busq==false){ //Verificacion de la fecha encontrada en internet
        cout << "\nIngrese la fecha inferior: " << endl;
        cout << "Ingresa el mes (Aug): ";
        cin >>mes_inferior;
        cout << "Ingresa el dia: ";
        cin>>dia_inferior;
        cout << "Ingresa la hora: ";
        cin>>hora_inferior;
        cout << "Ingresa los minutos: ";
        cin>>min_inferior;
        cout << "Ingresa los segundos: ";
        cin>>seg_inferior;

        dateTime* f1 = new dateTime(mes_inferior, dia_inferior, hora_inferior, min_inferior, seg_inferior, "", "");
        
        for(int i = 0; i<lista.size();i++){
            if(lista[i]->getDia() == f1->getDia() && lista[i]->getMes()==f1->getMes() && lista[i]->getHoras()==f1->getHoras() && lista[i]->getMinutos()==f1->getMinutos() && lista[i]->getSegundos() == f1->getSegundos()){
                f1->setDate(lista[i]->getDate());
                inferior = i;
            }
        }
         time_t fecha_comparacion1 = f1->getDate();
        busqueda_inferior = busquedaBinaria(lista, fecha_comparacion1);
        if(busqueda_inferior!=-1){
            inferior_busq = true;
            int busqueda_inferior = busquedaBinaria(lista, fecha_comparacion1);
        }
        else{
            cout << "La fecha ingresada no se encontro, porfavor reingresela: ";
        }
    }

    
    while(superior_busq==false){
        cout << "\nIngrese la fecha inferior: " << endl;
        cout << "Ingresa el mes (Aug): ";
        cin >>mes_superior;
        cout << "Ingresa el dia: ";
        cin>>dia_superior;
        cout << "Ingresa la hora: ";
        cin>>hora_superior;
        cout << "Ingresa los minutos: ";
        cin>>min_superior;
        cout << "Ingresa los segundos: ";
        cin>>seg_superior;
        dateTime* f2 = new dateTime(mes_superior, dia_superior, hora_superior, min_superior, seg_superior, "", "");
        for(int k = 0; k<lista.size();k++){
            if( lista[k]->getMes()==f2->getMes() &&lista[k]->getDia() == f2->getDia() && lista[k]->getHoras()==f2->getHoras() && lista[k]->getMinutos()==f2->getMinutos() && lista[k]->getSegundos() == f2->getSegundos()){
                f2->setDate(lista[k]->getDate());
                superior = k;
            }
        }
        time_t fecha_comparacion = f2->getDate();
        busqueda_superior = busquedaBinaria(lista, fecha_comparacion);
        if(busqueda_superior!=-1){
            superior_busq = true;
            int busqueda_superior = busquedaBinaria(lista, fecha_comparacion);

        }
        else{
            cout << "La fecha ingresada no se encontro, porfavor reingresela: ";
        }
    }
    printVector(lista, busqueda_superior, busqueda_inferior);
    
}     