/*

Jesus Ramirez Delgado
A01274723
Programacion 10

*/

#include <iostream>
#include <iomanip>
#include <cmath> // Librearia para facilitar la raiz cuadarada
// #include <thread>
#include <pthread.h>

// Apoyandome con el codigo de la clase:


using namespace std;

const int MAXIMUM = 5;
const int MAX_THREADS = 8;

typedef struct {
    int id, start, end;
} Block;

// Función para calcular y mostrar la raíz cuadrada de los primeros 10 números enteros
void* task1(void* param) {
    Block* block = (Block*)param;
    cout << "tid = " << block->id << " is starting...\n";
    for (int i = block->start; i <= block->end; i++) {
        double raiz = std::sqrt(i);
        std::cout << "Raíz cuadrada de " << i << ": " << raiz << std::endl;
    }
    cout << "tid = " << block->id << " is going to terminate\n";
    pthread_exit(0);
}

// Función para calcular y mostrar el cuadrado de los primeros 10 números enteros
void* task2(void* param) {
    Block* block = (Block*)param;
    cout << "tid = " << block->id << " is starting...\n";
    for (int i = block->start; i <= block->end; i++) {
        int cuadrado = i * i;
        std::cout << "Cuadrado de " << i << ": " << cuadrado << std::endl;
    }
    cout << "tid = " << block->id << " is going to terminate\n";
    pthread_exit(0);
}

int main(int argc, char* argv[]) {
    pthread_t tid[MAX_THREADS];
    Block blocks[MAX_THREADS];

    cout << "This is the main thread.\n";

    // FORK
    for (int i = 0; i < MAX_THREADS; i++) {
        blocks[i].id = i;
        blocks[i].start = i * 5 + 1;
        blocks[i].end = (i + 1) * 5;
        if (i % 2 == 0)
            pthread_create(&tid[i], NULL, task1, &blocks[i]); // Tarea 1 Raiz
        else
            pthread_create(&tid[i], NULL, task2, &blocks[i]); // Tarea 2 Cuadrado
    }

    // JOIN
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}

// AVISO
// Investige y tambien llegue a esta solucion extra
// Utilizando la libreria <thread> en vez de <pthread.h>

/*

using namespace std;

// Función para calcular y mostrar la raíz cuadrada de los primeros 10 números enteros
void raizCuadrada() {
    for (int i = 1; i <= 10; ++i) { // Ciclo for de 1-10
        double raiz = std::sqrt(i); // Operacion raiz 
        std::cout << "Raíz cuadrada de " << i << ": " << raiz << std::endl;
    }
}

// Función para calcular y mostrar el cuadrado de los primeros 10 números enteros
void cuadrado() {
    for (int i = 1; i <= 10; ++i) { // Ciclo for de 1-10
        int cuadrado = i * i; // Operacion cuadrado
        std::cout << "Cuadrado de " << i << ": " << cuadrado << std::endl;
    }
}

int main() {
    // Se asocian las funciones previas a los hilos creados
    thread threadRaizCuadrada(raizCuadrada);
    thread threadCuadrado(cuadrado);

    // Esperar a que los hilos terminen de ejecutarse
    threadRaizCuadrada.join();
    threadCuadrado.join();

    return 0;
}

*/

