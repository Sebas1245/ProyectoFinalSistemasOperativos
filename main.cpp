#include <iostream>
#include "peluquero.cpp"
#include  "P9.cpp"
#include "P7.cpp"
using namespace std;

void correrProblema1()
{
  int clientNo;
  cout << "Cuando termine la simulacion oprima CTRL+C para terminar el programa " << endl;
  cout << "La barberia esta regentada por un peluquero, tiene una silla para pelar a los clientes y sillas para que esperen los clientes. \n";
  cout << "\tSi no hay clientes, el peluqero espera durmiendo a que entren en la peluqeria.\n";
  cout << "\tCuando llega un cliente, tiene que despertar al peluquero.\n";
  cout << "\tSi llegan mas clientes mientras el peluquero esta pelando a un cliente se sientan si hay sillas libres o se van si no pueden sentarse.\n";
  cout << "¿Cuantos clientes intentaran cortarse el pelo? (De 1 a 10)" << endl;
  cin >> clientNo;
  RunSimulation(clientNo);
}

void correrProblema2()
{
  cout << "Supongamos que se tienen dos procesos concurrentes que cooperan como productor y consumidor con la siguiente restricción:\n";
  cout << "\tEl productor siempre produce un dato cada vez y e consumidor debe tomar de dos datos a la vez.\n";
  cout << "\tSuponiendo que el buffer comun es de tamanio 2, plantee una solucion al problema usando semaforos.\n";
  // correr problema Consumidor productor
  RunP7();

}

void correrProblema3()
{
  cout << "Existen dos tipos de procesos, uno para generar oxigeno y el otro para generar hidrogeno." << endl;
  cout << "\tSe sincronizaran los procesos de tal manera que se haya ejecutado un proceso de oxigeno y 2 de hidrogeno para poder formar una molécula de agua." << endl;
  cout << "\tCada uno de los procesos debe de poder ejecutar la función Union()" << endl;
  cout << "\tEn cada proceso existe un tipo de barrera para garantizar que hay un proceso de oxigeno y 2 de hidrogeno en esa barrera para poder pasarla y así ejecutar la función de Union()" << endl;
  cout << "\tPara que los procesos de oxigenos puedan ejecutar la función de Union() tienen que estar 2 procesos de hidrogeno esperando en la barrera." << endl;
  cout << "\tPara que los procesos de hidrogeno puedan ejecutar la función de Union() tiene que estar otro proceso de Hidrogeno y un proceso de Oxigeno en la barrera." << endl;
  cout << "\tHay n procesos de hidrogeno y n procesos de oxigeno" << endl;
  // correr problema H2O
  RunPH2O();
}

void desplegarOpcionesSimulacion()
{
  cout << "Oprima un numero para elegir alguna de las siguientes opciones" << endl;
  cout << "1. Problema de la peluqeria" << endl;
  cout << "2. Ejercicio 7 - Problema Productor/Consumidor" << endl;
  cout << "3. Ejercicio 9 - Problema H2O" << endl;
  cout << "4. Regresar al menu principal" << endl;
}

void desplegarMenuPrincipal()
{
  cout << "Proyecto Final TC2008 - Sistemas Operativos" << endl;
  cout << "SIMULADOR DE PROBLEMAS CON SEMAFOROS" << endl;
  cout << "Oprima un numero para elegir alguna de las siguientes opciones" << endl;
  cout << "1. Simulaciones de los problemas " << endl;
  cout << "2. Que es un semaforo?" << endl;
  cout << "3. Creditos " << endl;
  cout << "4. Salir " << endl;
}
int main()
{
  int opcionPrincipal = 0, opcionSimulaciones;
  while (opcionPrincipal != 4)
  {
    desplegarMenuPrincipal();
    cin >> opcionPrincipal;
    switch (opcionPrincipal)
    {
    case 1:
      opcionSimulaciones = 0;
      while (opcionSimulaciones != 4)
      {
        desplegarOpcionesSimulacion();
        cin >> opcionSimulaciones;
        if (opcionSimulaciones == 1)
        {
          correrProblema1();
        }
        else if (opcionSimulaciones == 2)
        {
          correrProblema2();
        }
        else if (opcionSimulaciones == 3)
        {
          correrProblema3();
        }
        else if (opcionSimulaciones == 4)
        {
          break;
        }
        else
        {
          cout << "Opcion no reconocida, intentelo de nuevo";
        }
      }
      cout << endl;
      break;
    case 2:
      cout << "Variable especial protegida que solo puede tomar valores enteros y nos ayuda en la sincronizacion de procesos." << endl;
      cout << "Unicamente puede ser modificada por sus 3 operaciones atomicas:" << endl;
      cout << "\tWait --> Bloquea al proceso si no se puede acceder al recurso critico" << endl;
      cout << "\tSignal --> Senializa que el recurso critico dejo de utilizarse por el proceso que da la señal" << endl;
      cout << "\tInitSemaphore --> Da valor inicial al semaforo." << endl;
      cout << endl;
      break;
    case 3:
      cout << "Proyecto para la materia TC2008 - Sistemas Operativos en el Tecnologico de Monterrey" << endl;
      cout << "Profesor David Alonso Cantu Delgado" << endl;
      cout << "Integrantes del equipo: " << endl;
      cout << "\tLorena Ang Alcorta" << endl;
      cout << "\tJorge Adrian Besnier Benavides" << endl;
      cout << "\tJose Daniel Hernandez Rios" << endl;
      cout << "\tSebastian Andres Saldana Cardenas" << endl;
      cout << "\tJazmin Yolistli Santibanez de la Rosa" << endl;
      cout << endl;
      break;
    case 4:
      cout << "Adios!" << endl;
      break;
    default:
      cout << "Opcion no reconocida, intentelo de nuevo.";
      break;
    }
  }
  return 0;
}
