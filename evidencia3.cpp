#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <thread>

using namespace std;

bool esPrimo(int n) {
    if (n < 2)
        return false;
    for (int i = 2; i <= std::sqrt(n); ++i) {
        if (n % i == 0)
            return false;
    }
    return true;
}

void calcularSumaPrimos(int inicio, int fin, long long& suma) {
    for (int i = inicio; i < fin; ++i) {
        if (esPrimo(i))
            suma += i;
    }
}


int main() {
    const int limite = 5000000;
    long long suma = 0;

    // Version secuencial

    auto start_secuencial = std::chrono::high_resolution_clock::now();

    for (int i = 2; i < limite; ++i) {
        if (esPrimo(i))
            suma += i;
    }

    auto end_secuencial = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_secuencial = end_secuencial - start_secuencial;
    double tiempo_secuencial = duration_secuencial.count();

    cout << "Suma de primos (versión secuencial): " << suma << endl;
    cout << "Tiempo de ejecución (secuencial): " << tiempo_secuencial << " segundos" << endl;

    // Version paralela

    const int num_hilos = std::thread::hardware_concurrency();
    std::vector<std::thread> hilos(num_hilos);
    std::vector<long long> sumas_parciales(num_hilos, 0);
    long long sumaParalela = 0;

    auto start_paralelo = std::chrono::high_resolution_clock::now();

    int intervalo = limite / num_hilos;
    for (int i = 0; i < num_hilos; ++i) {
        int inicio = i * intervalo;
        int fin = (i == num_hilos - 1) ? limite : (i + 1) * intervalo;
        hilos[i] = std::thread(calcularSumaPrimos, inicio, fin, std::ref(sumas_parciales[i]));
    }

    for (int i = 0; i < num_hilos; ++i) {
        hilos[i].join();
        sumaParalela += sumas_parciales[i];
    }

    auto end_paralelo = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_paralelo = end_paralelo - start_paralelo;
    double tiempo_paralelo = duration_paralelo.count();

    cout << "Suma de primos (versión paralela): " << sumaParalela << endl;
    cout << "Tiempo de ejecución (paralelo): " << tiempo_paralelo << " segundos" << endl;

    // SpeedUp

    long long speedUp;
    speedUp = tiempo_secuencial / tiempo_paralelo;

    cout << "El speedup fue de: " << speedUp << " segundos" << endl;

    return 0;
}
