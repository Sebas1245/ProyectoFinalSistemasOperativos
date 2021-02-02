#include <iostream>
#include "peluquero.cpp"
#include  "P9.cpp"
#include "P7.cpp"
using namespace std;

void correrProblema1()
{
  int clientNo;
  cout << "La barbería esta regentada por un peluquero, tiene una silla para atender a los clientes y sillas para que esperen los clientes. \n";
  cout << "\tSi no hay clientes, el peluquero espera durmiendo a que entren a la peluquería.\n";
  cout << "\tCuando llega un cliente, tiene que despertar al peluquero.\n";
  cout << "\tSi llegan más clientes mientras el peluquero está atendiendo a un cliente se sientan si hay sillas libres, o se van si no pueden sentarse.\n";
  cout << "¿Cuantos clientes intentarán cortarse el pelo? (De 1 a 10): " << endl;
  cin >> clientNo;
  RunSimulation(clientNo);
}

void correrProblema2()
{
  cout << "Supongamos que se tienen dos procesos concurrentes que cooperan como productor y consumidor con la siguiente restricción:\n";
  cout << "\tEl productor siempre produce un dato cada vez y el consumidor debe tomar de dos datos a la vez.\n";
  cout << "\tSuponiendo que el buffer común es de tamaño 2, plantee una solución al problema usando semáforos.\n";
  // correr problema Consumidor productor
  RunP7();

}

void correrProblema3()
{
  cout << "Existen dos tipos de procesos, uno para generar oxígeno y el otro para generar hidrógeno." << endl;
  cout << "\tSe sincronizarán los procesos de tal manera que se haya ejecutado un proceso de oxígeno y 2 de hidrógeno para poder formar una molécula de agua." << endl;
  cout << "\tCada uno de los procesos debe de poder ejecutar la función Union()" << endl;
  cout << "\tEn cada proceso existe un tipo de barrera para garantizar que hay un proceso de oxígeno y 2 de hidrógeno en esa barrera para poder pasarla y así ejecutar la función de Union()" << endl;
  cout << "\tPara que los procesos de oxígenos puedan ejecutar la función de Union() tienen que estar 2 procesos de hidrógeno esperando en la barrera." << endl;
  cout << "\tPara que los procesos de hidrógeno puedan ejecutar la función de Union() tiene que estar otro proceso de Hidrógeno y un proceso de Oxígeno en la barrera." << endl;
  cout << "\tHay n procesos de hidrógeno y n procesos de oxígeno" << endl;
  // correr problema H2O
  RunPH2O();
}

void desplegarOpcionesSimulacion()
{
  cout << "Oprima un número para elegir alguna de las siguientes opciones: " << endl;
  cout << "1. Problema de la peluquería" << endl;
  cout << "2. Ejercicio 7 - Problema Productor/Consumidor" << endl;
  cout << "3. Ejercicio 9 - Problema H2O" << endl;
  cout << "4. Regresar al menu principal" << endl;
}

void desplegarMenuPrincipal()
{
  cout << "Proyecto Final TC2008 - Sistemas Operativos" << endl;
  cout << "SIMULADOR DE PROBLEMAS CON SEMÁFOROS" << endl;
  cout << "Oprima un número para elegir alguna de las siguientes opciones: " << endl;
  cout << "1. Simulaciones de los problemas." << endl;
  cout << "2. ¿Qué es un semaforo?" << endl;
  cout << "3. Créditos " << endl;
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
          cout << "Opción no reconocida, inténtelo de nuevo";
        }
      }
      cout << endl;
      break;
    case 2:
      cout << "Variable especial protegida que solo puede tomar valores enteros y nos ayuda en la sincronización de procesos." << endl;
      cout << "Únicamente puede ser modificada por sus 3 operaciones atómicas:" << endl;
      cout << "\tWait --> Bloquea al proceso si no se puede acceder al recurso critico" << endl;
      cout << "\tSignal --> Señaliza que el recurso critico dejo de utilizarse por el proceso que da la señal" << endl;
      cout << "\tInitSemaphore --> Da valor inicial al semáforo." << endl;
      cout << endl;
      cout << endl;
      break;
    case 3:
      cout << "Proyecto para la materia TC2008 - Sistemas Operativos en el Instituto Tecnológico y de Estudios Superiores de Monterrey" << endl;
      cout << "Profesor David Alonso Cantú Delgado" << endl;
      cout << "Integrantes del equipo: " << endl;
      cout << "\tLorena Ang Alcorta" << endl;
      cout << "\tJorge Adrián Besnier Benavides" << endl;
      cout << "\tJosé Daniel Hernández Ríos" << endl;
      cout << "\tSebastián Andrés Saldaña Cárdenas" << endl;
      cout << "\tJazmín Yolistli Santibáñez de la Rosa" << endl;
      cout << endl;
      break;
    case 4:
      cout << "¡Adiós!" << endl;
      break;
    default:
      cout << "Opción no reconocida, inténtelo de nuevo.";
      break;
    }
  }
  return 0;
}
