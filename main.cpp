#include <iostream>
#include "peluquero.cpp"

using namespace std;

void desplegarMenu(){
  cout << "SIMULADOR DE PROBLEMAS CON SEMAFOROS" << endl;
  cout << "Oprima un numero para elegir alguna de las siguientes opciones" << endl;
  cout << "Cuando termine la simulacion oprima CTRL+c para terminar el programa " << endl;
  cout << "1. Problema de la peluqeria" << endl;
  cout << "2. Problema X" << endl;
  cout << "4. Salir" << endl;
}

int main()
{
  int opcion = 0;
  while(opcion != 4) {
    desplegarMenu();
    cin >> opcion;
    switch (opcion)
    {
      case 1:
        cout << "La barberia esta regentada por un peluquero, tiene una silla para pelar a los clientes y sillas para que esperen los clientes. \n";
        cout << "Si no hay clientes, el peluqero espera durmiendo a que entren en la peluqeria.\n";
        cout << "Cuando llega un cliente, tiene que despertar al peluquero.\n";
        cout << "Si llegan mas clientes mientras el peluquero esta pelando a un cliente se sientan si hay sillas libres o se van si no pueden sentarse.\n";
        opcion = RunSimulation();
        break;
    
      default:
        break;
    }
  }
  return 0;
}
