--->Hecho por: Jorge Daniel Cruz Case A01634536 & Fernanda Monserrat Galvan Romero A00344712, 12/4/2021

-->Compilacion

-->Debugeo
g++ -std=c++17 -g -o main *.cpp

-->Valgrind
valgrind --leak-check=full ./main 

-->Compilacion para ejecucion
g++ -std=c++17 -O3 -o main *.cpp

-->Ejecucion
./main 

-->Variables:
g++ -std=c++17 *.cpp -Wall

--->No tengo idea si los unsigned long ints funcionan en todos los sistemas operativos, supongo que si ya que solamente utilizan 8 bits, si hay algun problema de compatibilidad con este tipo de datos o con el programa en general porfavor hagamelo saber.

-->La clase IP.h es para el manejo de las aristas en el grafo
-->La clase IPConex.h es para el ordenamiento de las conexiones desde una IP, esta sacada de la act 3.4 de Heaps