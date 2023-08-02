/*

Jesus Ramirez Delgado
A01274723
Programacion 12

*/

#include <iostream>
#include <thread> // Libreria thread para los hilos
#include <mutex> // Libreria mutex para excuclusion mutua
#include <condition_variable> // Libreria para complementar mutex
#include <chrono> // Libreria medir tiempo

using namespace std;

condition_variable cv;  // Variable de condición para esperar a que llegue una nueva pizza
bool pizzaDisp = true;  // Variable booleana que indica si hay pizza
mutex mtx;  // Mutex para asegurar exclusión mutua al acceder a la pizza

void comerPizza(int estudiante) { // Funcion accion de comer pizza
    while (true) {
        unique_lock<mutex> lock(mtx);

        // Verificar si hay pizza disponible
        if (pizzaDisp) {
            cout << "Estudiante " << estudiante << " Agarra una reabanada de pizza." << endl;

            // Simular tiempo de estudio mientras se come la pizza
            this_thread::sleep_for(chrono::seconds(2));

            cout << "Estudiante " << estudiante << " termina de comer." << endl;
        } else {
            // No hay pizza disponible, el estudiante se va a dormir
            cout << "El estudiante " << estudiante << " se va a dormir." << endl;
            cv.wait(lock);  // Esperar a que llegue una nueva pizza
            continue;  // Rectificar si hay pizza nueva
        }

        // La pizza se ha terminado, el estudiante llama a la pizzería
        if (estudiante == 1) {
            // Pide otra pizza por Rappi
            cout << "Estudiante " << estudiante << " pide otra pizzeria por Rappi" << endl;
            pizzaDisp = false;  // Marcar que no hay pizza disponible
            cv.notify_one();  // Notificar que se necesita pedir otra pizza
        }
    }
}

void nuevaPizza() { // Funcion accion entrega pizza
    while (true) {
        unique_lock<mutex> lock(mtx);

        // Esperar a que se agote la pizza
        cv.wait(lock, [] { return !pizzaDisp; });

        // Entregar una nueva pizza (8 rebanadas)
        cout << "Llego el repartidor de Rappi" << endl;
        pizzaDisponible = true;  // Hay pizza disponuble si la condicon es true
        cv.notify_all();  // Para notificar que hay pizza
    }
}

int main() {
    thread estudiantes[3]; // Variable para crear hilos (estudiantes)
    thread pizzeria(nuevaPizza); // Variable hilo de pizzeria

    // Crear hilos (estudiantes)
    for (int i = 0; i < 4; i++) {
        estudiantes[i] = thread(comerPizza, i + 1);
    }

    // Esperar a que los hilos/estudiantes terminen
    for (int i = 0; i < 4; i++) {
        estudiantes[i].join();
    }

    // Esperar a que el hilo de la pizzería termine
    pizzeria.join();

    return 0;
}
