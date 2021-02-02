#include <iostream>
#include <thread>
#include <vector>
#include "semaphore.h"
using namespace std;

Semaphore sCliente(0);
Semaphore sAccesoClientes(1);
Semaphore sPeluquero(0);

int N = 10;
int numClientes = 0;

void Peluquero(int inputClients)
{
  int clientsServed = inputClients;
  while (clientsServed--)
  {
    sCliente.P();
    sAccesoClientes.P();
    numClientes--;
    sPeluquero.V();
    sAccesoClientes.V();
    // cortar pelo
    cout << "Ha salido un cliente!" << endl;
  }
}

void Cliente()
{
  cout << "Ha entrado un cliente a la peluqueria " << endl;
  sAccesoClientes.P();
  if (numClientes < N)
  {
    numClientes++;
    sCliente.V();
    sAccesoClientes.V();
    sPeluquero.P();
    // le cortan el pelo
  }
  else
  {
    sAccesoClientes.V();
  }
}

int RunSimulation(int clients)
{
  vector<thread> clientThs;
  thread p([&]() {
    Peluquero(clients);
  });

  for (int i = 0; i < clients; i++)
  {
    clientThs.emplace_back(Cliente);
  }
  /* Se termina la ejecucion de los threads y se unen al main */
  for (auto &t : clientThs)
  {
      t.join();
  }

  p.join();
  return 0;
}