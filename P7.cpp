#include <iostream>
#include <thread>
#include <vector>
#include "semaphore.h"

using namespace std;

Semaphore sDisponible(2); // Semaforo que controla la cantidad de semaforos disponibles
Semaphore sBuffer(0);     // Semaforo que indica si hay espacios ocupados
int coop = 0;             // Contador de cooperaciones exitosas - cuando el consumidor consume lo producido

void Productor()
{
  cout << "\nProductor";
  sDisponible.P(); // Esperar que haya un espacio disponible
  // Producir
  sBuffer.V(); // Espacio ocupado
}

void Consumidor()
{
  cout << "\nConsumidor";
  sBuffer.P(); // Esperar que haya espacio ocupado
  sBuffer.P(); // Esperar que haya espacio ocupado
  // Consumir
  sDisponible.V(); // Espacio disponible
  sDisponible.V(); // Espacio disponible
  coop++;
  cout << "\n+1 cooperación exitosa";
}

int RunP7()
{
  vector<thread> tP;
  vector<thread> tC;
  int iP, iC;

  cout << "¿Cuántos productores?: " << endl;
  cin >> iP;
  cout << "¿Cuántos consumidores?: " << endl;
  cin >> iC;

  // Creación de procesos de productor
  for (int i = 0; i < iP; i++)
  {
    tP.emplace_back(Productor);
  }

  // Creación de procesos de consumidor
  for (int i = 0; i < iC; i++)
  {
    tC.emplace_back(Consumidor);
  }

  // Se termina la ejecucion de los threads y se unen al main
  for (auto &t : tP)
  {
    t.join();
  }

  for (auto &t : tC)
  {
    t.join();
  }

  cout << "\nCooperaciones exitosas: " << coop << endl;

  /* 
  // Input manual de productores y consumidores

  thread t1(Productor);
  thread t2(Consumidor);
  thread t3(Productor);
  thread t4(Productor);
  thread t5(Productor);
  thread t6(Consumidor);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  */

  return 0;
}