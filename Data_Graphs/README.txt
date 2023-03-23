-->Compilacion

-->Debugeo
g++ -std=c++17 -g -o main *.cpp

-->Valgrind
valgrind --leak-check=full ./main < bitacoraGrafos.txt
valgrind --leak-check=full ./main < bitacoraGrafosChiquita.txt

-->Compilacion para ejecucion
g++ -std=c++17 -O3 -o main *.cpp

-->Ejecucion
./main < bitacoraGrafos.txt
./main < bitacoraGrafosChiquita.txt

Hecho por: Jorge Daniel Cruz Case A01634536 & Fernanda Monserrat Galvan Romero A00344712

--->Consideraciones
Por la manera en la que se esta manejando la lectura de archivos y la creacion del Heap, la ejecucion puede ser bastante lenta, buen tambien considerando que son como 100,000 datos

--->Esta es una correción tomando en cuenta lo dicho en la clase del 12/2/2021