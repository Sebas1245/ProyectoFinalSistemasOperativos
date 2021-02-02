#include <iostream>
#include "semaphore.h"
#include <thread>
#include <vector>
using namespace std;

Semaphore sCliente(0);
Semaphore sAccesoClientes(1);
Semaphore sPeluquero(0);

int N = 10;
int numClientes = 0;

void Peluquero(const int& tid) {
  while (true) {
    sCliente.wait(tid);
    sAccesoClientes.wait(tid);
    numClientes--;
    sPeluquero.notify(tid);
    sAccesoClientes.notify(tid);
    // cortar pelo
  }
}

void Cliente(const int& tid) {
  cout << "Ha entrado un cliente a la peluqueria con ID = " << tid << endl;
  sAccesoClientes.wait(tid);
  if (numClientes < N) {
    numClientes++;
    sCliente.notify(tid);
    sAccesoClientes.notify(tid);
    sPeluquero.wait(tid);
    // le cortan el pelo
    cout << "El cliente " << tid << " ya tiene el pelo corto!" << endl;
  } else {
    sAccesoClientes.notify(tid);
  }
}

int RunSimulation() {
  vector<thread> children;

  thread t0([&]() {
    Cliente(0);
  });

  thread t1([&]() {
    Cliente(1);
  });

  thread t2([&]() {
    Cliente(2);
  });

  thread p([&]() {
    Peluquero(10);
  });

  t0.join();
  t1.join();
  t2.join();
  p.join();
  return 0;
}
