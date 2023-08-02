/*

Jesus Ramirez Delgado
A01274723
Programacion 11

*/


#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

// Ejercicio 1

// Función para contar el número de pares del arreglo
int countPairs(const std::vector<int>& arr, int start, int end) {
    int count = 0;
    for (int i = start; i < end; i++) {
        if (arr[i] % 2 == 0) {
            count++; // Contador
        }
    }
    return count;
}

// Función para contar el número de pares secuencialmente
int countPairsSequential(const std::vector<int>& arr) {
    return countPairs(arr, 0, arr.size()); // "Lamamos" a la funcion countPairs
}

/*
La paralelizacion de pares se me dificulto y no logre llegar a la solucion
int countPairsParallel(const std::vector<int>& arr) {

}
*/


// Ejercicio 2

double calculatePi(int n) {

    double pi = 0;
    double sign = 1; // Alterna el signo 

    for (int i = 0; i < n; i++){
        double res = sign / (2 * i + 1);
        pi += term;
        sign = -sign;
    }

    pi *= 4;

    return pi;
}

double piSequential () {
    return CalculatePi(n);
}

double piParallel(int n, int numThreads) {
    double pi = 0.0;
    std::vector<std::thread> threads;
    threads.reserve(numThreads);

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(calculatePi, std::ref(pi), n, i, numThreads);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 4 * pi;
}

int main() {

// Ejercicio 1

// Ejercicio 2
    int n = 10000000;
    int numThreads = 4;

    double seqResult = piSequential(n);
    double parResult = piParallel(n, numThreads);

    double speedUp = seqTime / parTime; // SpeedUp
    double efficiency = speedUp / numThreads; // Eficencia

    std::cout << "SpeedUp: " << speedUp << std::endl;
    std::cout << "Eficiencia: " << efficiency << std::endl;

    return 0;
}