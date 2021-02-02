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

void Peluquero(const int &tid)
{
  while (true)
  {
    sCliente.wait(tid);
    sAccesoClientes.wait(tid);
    numClientes--;
    sPeluquero.notify(tid);
    sAccesoClientes.notify(tid);
    // cortar pelo
  }
}

void Cliente(const int &tid)
{
  cout << "Ha entrado un cliente a la peluqueria con ID = " << tid << endl;
  sAccesoClientes.wait(tid);
  if (numClientes < N)
  {
    numClientes++;
    sCliente.notify(tid);
    sAccesoClientes.notify(tid);
    sPeluquero.wait(tid);
    // le cortan el pelo
    cout << "El cliente " << tid << " ya tiene el pelo corto!" << endl;
  }
  else
  {
    sAccesoClientes.notify(tid);
  }
}

int RunSimulation(int clients)
{
  vector<thread> children;
  thread p([&]() {
    Peluquero(10);
  });

  for (int i = 0; i < clients; i++)
  {
    cout << "Creando un thread nuevo" << endl;
    children.push_back(thread(Cliente, i));
  }
  for (int i = 0; i < children.size(); i++)
  {
    children[i].join();
  }

  p.join();
  return 0;
}
