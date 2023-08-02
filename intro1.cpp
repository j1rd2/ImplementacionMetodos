#include <iostream>
#include <iomanip>
#include <thread>

using namespace std;

void* task(void* param) {
    cout << "tid = " << pthread_self() << " is starting...\n";
    for (int i = 1; i <= MAXIMUM; i++) {
        cout << "tid = " << pthread_self() << " i = " << i << "\n";
    }
    cout << "tid = " << pthread_self() << " is going to terminates \n" << pthread_exit(0);
}

int main(int argc, char* argv[]) {
    
    pthread_t tid;
    
    cout << "This is the main thread. \n";
    pthread_create(&tid, NULL, task, NULL);
    
    cout << "The main thread is going to terminate \n";
    return 0;
}
