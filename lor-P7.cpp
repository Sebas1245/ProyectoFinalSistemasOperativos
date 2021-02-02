#include <iostream>
#include <thread>
#include "semaphore.h"

using namespace std;

Semaphore sDisponible(2); // Semaforo que controla la cantidad de semaforos disponibles
Semaphore sBuffer(0); // Semaforo que indica si hay espacios ocupados
int coop = 0; // Contador de cooperaciones exitosas - cuando el consumidor consume lo producido

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

int main()
{
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

  cout << "\nCooperaciones exitosas: " << coop << endl;

  return 0;
}