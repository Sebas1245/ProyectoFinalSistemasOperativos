#include <iostream>
#include <thread>
#include <vector>
#include "semaphore.h"
using namespace std;

/* Problema libre */

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
    cout << "\nSale cliente";
  }
}

void Cliente()
{
  cout << "\nEntra cliente";
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

void correrProblemaL()
{
  int clientNo;
  cout << "\nLa barbería esta regentada por un peluquero, tiene una silla para atender a los clientes y sillas para que esperen los clientes. \n";
  cout << "\tSi no hay clientes, el peluquero espera durmiendo a que entren a la peluquería.\n";
  cout << "\tCuando llega un cliente, tiene que despertar al peluquero.\n";
  cout << "\tSi llegan más clientes mientras el peluquero está atendiendo a un cliente se sientan si hay sillas libres, o se van si no pueden sentarse.\n";
  cout << "¿Cuantos clientes intentarán cortarse el pelo? (De 1 a 10): " << endl;
  cin >> clientNo;

  vector<thread> clientThs;
  thread p([&]() {
    Peluquero(clientNo);
  });

  for (int i = 0; i < clientNo; i++)
  {
    clientThs.emplace_back(Cliente);
  }
  /* Se termina la ejecucion de los threads y se unen al main */
  for (auto &t : clientThs)
  {
    t.join();
  }

  p.join();

  cout << endl;
}

/* Problema 4 */

Semaphore sDisp(50);   // Semaforo que controla la cantidad de espacios disponibles
Semaphore sOcupado(0); // Semaforo que indica la cantidad de espacios ocupados
Semaphore sPuerta(1);  // Semaforo binario para que la puerta este disponible al iniciar

Semaphore snCarros(1); //Semaforo para proteccion de la variable carros
int carros = 0;        // Contador de carros dentro del estacionamiento

void Entra()
{
  cout << "Proceso entra \n";
  sDisp.P();   // Esperar que haya espacio ocupado
  sPuerta.P(); // Esperar que haya espacio ocupado

  // Entrar al estacionamiento
  cout << "  > +1 carro (Entrada con exito) \n";

  //Aumento de carros dentro del estacionamiento, con sem
  snCarros.P();
  carros++;
  snCarros.V();

  sPuerta.V();  // Puerta disponible
  sOcupado.V(); // Espacio ocupado
}

void Sale()
{
  cout << "Proceso Sale \n";
  sOcupado.P(); // Esperar que haya un espacio disponible
  sPuerta.P();  // Esperar que la puerta esté libre

  // Salir del estacionamiento
  cout << "  > -1 carro (Salida con exito) \n";
  //Reduccion de carros dentro del estacionamiento, con semaforo para proteccion
  snCarros.P();
  carros--;
  snCarros.V();

  sPuerta.V(); // Puerta disponible
  sDisp.V();   // Espacio disponible
}

void correrProblema4()
{
  cout << "\nSe tiene un estacionamiento que tiene 1 puerta de entrada–salida y 50 lugares individuales. Se desea sincronizar la entrada y salida de carros del estacionamiento.\n";
  cout << "\tSólo se permite que un carro entre o salga del estacionamiento a la vez.\n";
  cout << "\tLos carros siempre están tratando de entrar o salir del estacionamiento.\n";
  cout << "\tSi el estacionamiento está lleno, los carros hacen fila fuera de él.\n";

  // Correr problema del estacionamiento

  vector<thread> tE;
  vector<thread> tS;
  int iE, iS;

  cout << "¿Cuántos carros entran?: " << endl;
  cin >> iE;
  cout << "¿Cuántos carros salen?: " << endl;
  cin >> iS;

  // Creación de procesos de entrar
  for (int i = 0; i < iE; i++)
  {
    tE.emplace_back(Entra);
  }

  // Creación de procesos de salir
  for (int i = 0; i < iS; i++)
  {
    tS.emplace_back(Sale);
  }

  // Se termina la ejecucion de los threads y se unen al main
  for (auto &t : tE)
  {
    t.join();
  }

  for (auto &t : tS)
  {
    t.join();
  }

  cout << "\nCarros dentro del estacionamiento: " << carros << endl;

  /* 
  // Input manual de carros entrando y saliendo

  thread t1(Entra);
  thread t2(Sale);
  thread t3(Entra);
  thread t4(Entra);
  thread t5(Sale);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  */
}

/* Problema 7 */

Semaphore sDisponible(2); // Semaforo que controla la cantidad de semaforos disponibles
Semaphore sBuffer(0);     // Semaforo que indica si hay espacios ocupados

Semaphore snCoop(1); //Semaforo para acceso a la variable coop
int coop = 0;        // Contador de cooperaciones exitosas - cuando el consumidor consume lo producido

void Productor()
{
  cout << "\n Proceso Productor";
  sDisponible.P(); // Esperar que haya un espacio disponible
  // Producir
  cout << "\n  >  +1 Producto ";
  sBuffer.V(); // Espacio ocupado
}

void Consumidor()
{
  cout << "\n Proceso Consumidor";
  sBuffer.P(); // Esperar que haya espacio ocupado
  sBuffer.P(); // Esperar que haya espacio ocupado
  // Consumir
  sDisponible.V(); // Espacio disponible
  sDisponible.V(); // Espacio disponible
  snCoop.P();      // Proteger la variable coop. Solo se accede una a la vez.
  coop++;
  snCoop.V(); //Liberar variable coop
  cout << "\n  > +1 cooperación exitosa";
}

void correrProblema7()
{
  cout << "\nSupongamos que se tienen dos procesos concurrentes que cooperan como productor y consumidor con la siguiente restricción:\n";
  cout << "\tEl productor siempre produce un dato cada vez y el consumidor debe tomar de dos datos a la vez.\n";
  cout << "\tSuponiendo que el buffer común es de tamaño 2, plantee una solución al problema usando semáforos.\n";

  // correr problema productor-consumidor

  vector<thread> tP;
  vector<thread> tC;
  int iP, iC;

  cout << "NOTA: Para que se terminen de ejecutar todos los procesos exitosamente se deben generar el DOBLE de productores que de consumidores." << endl;
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
}

/* Problema 9 */

Semaphore sHidrogenos(0); // Semaforo que controla la cantidad de semaforos disponibles
Semaphore sPaso(0);       //Semaforo que indica si hay un oxigeno y 2 hidrogenos.

Semaphore snH2O(1); //Semaforo para proteccion del contador h20
int h2o = 0;

void Hidrogeno()
{
  cout << "Hidrogeno" << endl;
  sHidrogenos.V(); //Avisa que hay 1 hidrogeno
  sPaso.P();       //Espera la señal diciendo que se encontró otro H y un O
  //Union con Oxigeno
}

void Oxigeno()
{
  cout << "Oxigeno" << endl;
  sHidrogenos.P(); //Espera un hidrogeno
  sHidrogenos.P(); //Espera al segundo hidrogeno
  //Union con el oxigeno
  sPaso.V(); //Libera señal de paso para un hidrogeno
  sPaso.V(); //Libera señal de paso para el segundo hidrogeno
  cout << "  > +1 H2O" << endl;

  snH2O.P();
  h2o++; // Necesitaria semaforo para proteger variable
  snH2O.V();
}

void correrProblema9()
{
  cout << "\nExisten dos tipos de procesos, uno para generar oxígeno y el otro para generar hidrógeno." << endl;
  cout << "\tSe sincronizarán los procesos de tal manera que se haya ejecutado un proceso de oxígeno y 2 de hidrógeno para poder formar una molécula de agua." << endl;
  cout << "\tCada uno de los procesos debe de poder ejecutar la función Union()" << endl;
  cout << "\tEn cada proceso existe un tipo de barrera para garantizar que hay un proceso de oxígeno y 2 de hidrógeno en esa barrera para poder pasarla y así ejecutar la función de Union()" << endl;
  cout << "\tPara que los procesos de oxígenos puedan ejecutar la función de Union() tienen que estar 2 procesos de hidrógeno esperando en la barrera." << endl;
  cout << "\tPara que los procesos de hidrógeno puedan ejecutar la función de Union() tiene que estar otro proceso de Hidrógeno y un proceso de Oxígeno en la barrera." << endl;
  cout << "\tHay n procesos de hidrógeno y n procesos de oxígeno" << endl;

  // correr problema H2O

  vector<thread> tH;
  vector<thread> tO;
  int iH, iO;

  /* Input dinamico de procesos */
  cout << "NOTA: Para que se terminen de ejecutar todos los procesos exitosamente se deben generar el DOBLE de Hidrogenos que de Oxigenos." << endl;
  cout << "Cuantos Hidrogenos?: " << endl;
  cin >> iH;
  cout << "Cuantos Oxigenos?: " << endl;
  cin >> iO;

  /* Creacion de procesos de Hidrogeno*/
  for (int i = 0; i < iH; i++)
  {
    tH.emplace_back(Hidrogeno);
  }

  /* Creacion de procesos de Oxigeno*/
  for (int i = 0; i < iO; i++)
  {
    tO.emplace_back(Oxigeno);
  }

  /* Se termina la ejecucion de los threads y se unen al main */
  for (auto &t : tH)
  {
    t.join();
  }

  for (auto &t : tO)
  {
    t.join();
  }

  cout << "Moléculas H20 creadas: " << h2o << endl;

  // Input manual de hidrogenos y oxigenos
  /*
  thread t1(Hidrogeno);
  // thread t2(Oxigeno);
  thread t3(Hidrogeno);
  thread t5(Hidrogeno);
  thread t6(Hidrogeno);
  thread t4(Oxigeno);

  t1.join();
  // t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  */
}

/* Problema 11 */

// Variables que llevan el conteo de hombres y mujeres, con sus semaforos
// para protefer el acceso a la variabke
int nH = 0;
int nM = 0;
Semaphore snH(1); //1 indica que la variable nH esta disponible para ser modificada
Semaphore snM(1); //1 indica que la variable nM esta disponible para ser modificada.
// Semaforos para llevar el conteo de mujeres y hombres dentro del baño
Semaphore sH(0); //Empieza con 0 hombres en el baño
Semaphore sM(0); //Empieza con 0 mujeres en el baño
// Semaforos que bloquean la entrada de un genero si el baño esta ocupado por el otro genero.
Semaphore sBH(1); //0 indica que no pueden pasar hombres
Semaphore sBM(1); //0 indica que no pueden pasar mujeres
//Semaforo que indica si el baño esta vacio, para regular casos donde una mujer y un hombre
// entran al mismo tiempo
Semaphore sV(1);

void hombreEntra()
{
  sBH.P(); //Revisa si esta bloqueado el paso para hombres
  if (nH == 0)
  {         //Si el baño esta vacio
    sV.P(); //Recurso "baño vacio" en competencia por si llegan hombre y mujer al mismo tiempo
  }
  /* Seccion critica - Entrar */
  snH.P(); //Protege el acceso de la variable nH (numero de hombres)
  nH++;
  cout << "+1 H - Un hombre entra \t H: " << nH << endl;
  snH.V(); //Libera el acceso al contador de hombres
  sH.V();  //Aumenta el semaforo de conteo de hombres
  sBH.V(); //Libera el bloque de hombres, deja pasar mas hombres.
}

void mujerEntra()
{
  sBM.P(); //Revisa si esta bloqueado el paso para mujeres
  if (nM == 0)
  {         //Si el baño esta vacio
    sV.P(); //Recurso "baño vacio" en competencia por si llegan hombre y mujer al mismo tiempo
  }
  /* Seccion critica - Entrar */
  snM.P(); //Protege el acceso de la variable nM (numero de mujeres)
  nM++;
  cout << "+1 M - Una mujer entra \t M: " << nM << endl;
  snM.V(); //Libera el acceso al contador de mujeres
  sM.V();  //Aumenta el semaforo de conteo de mujeres
  sBM.V(); //Libera el bloque de mujeres, deja pasar mas mujeres.
}

void hombreSale()
{
  sH.P(); //Revisa que haya hombres adentro, evitando la salida sin ninguno adentro
  /* Seccion critica: Salir */
  snH.P(); //Proteger el acceso de la variable nH (numero de hombres)
  nH--;
  cout << "-1 H - Un hombre sale \t H: " << nH << endl;
  snH.V(); //Liberar contador de hombres
  if (nH == 0)
  {
    sV.V(); //Marcar como vacio el cuarto
  }
}

void mujerSale()
{
  sM.P(); //Revisa que haya mujeres adentro, evitando la salida sin ninguna adentro
  /* Seccion critica: Salir */
  snM.P(); //Proteger el acceso de la variable nH (numero de mujeres)
  nM--;
  cout << "-1 M - Una mujer sale \t M: " << nM << endl;
  snM.V(); //Liberar contador de mujeres
  if (nM == 0)
  {
    sV.V(); //Marcar como vacio el cuarto
  }
}

void correrProblema11()
{
  cout << "\nEl campus Monterrey está considerando implementar una política para ponerle fin a la práctica de tener baños separados por género, conservando la regla de que solo puedan ser usados por personas del mismo género al mismo tiempo. Las nuevas reglas indican lo siguiente: \n";
  cout << "\tEl baño puede estar en tres estados: vació, con mujeres o con hombres.\n";
  cout << "\tCuando lo estén usando las mujeres, solo otras mujeres pueden entrar al baño y los hombres no, y viceversa.\n";
  cout << "\tPuedes asumir que los baños tienen capacidad infinita, es decir, cualquier persona que quiera entrar al baño lo va a poder hacer siempre y cuando este vació u ocupado por personas del mismo género y que la puerta no la esté usando nadie.\n";

  // correr problema de los baños

  // Input manual de hombres y mujeres, con sintaxis --> thread nombre(Proceso); y su nombre.join() al final.
  thread t1(hombreEntra);
  thread t2(mujerSale);
  thread t3(hombreEntra);
  thread t4(mujerEntra);
  thread t5(mujerEntra);
  thread t6(hombreSale);
  thread t7(mujerEntra);
  thread t8(hombreSale);
  thread t9(mujerSale);
  thread t10(mujerSale);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();
  t9.join();
  t10.join();
}

// MENUS

void desplegarOpcionesSimulacion()
{
  cout << "\nOprima un número para elegir alguna de las siguientes opciones: " << endl;
  cout << "1. Ejercicio Libre - Problema de la peluquería" << endl;
  cout << "2. Ejercicio 4 - Problema del estacionamiento" << endl;
  cout << "3. Ejercicio 7 - Problema Productor/Consumidor" << endl;
  cout << "4. Ejercicio 9 - Problema H2O" << endl;
  cout << "5. Ejercicio 11 - Problema de los baños" << endl;
  cout << "6. Regresar al menu principal" << endl;
}

void desplegarMenuPrincipal()
{
  cout << "Proyecto Final TC2008 - Sistemas Operativos" << endl;
  cout << "SIMULADOR DE PROBLEMAS CON SEMÁFOROS" << endl;
  cout << "Oprima un número para elegir alguna de las siguientes opciones: " << endl;
  cout << "1. Simulaciones de los problemas" << endl;
  cout << "2. ¿Qué es un semáforo?" << endl;
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
          correrProblemaL();
        }
        else if (opcionSimulaciones == 2)
        {
          correrProblema4();
        }
        else if (opcionSimulaciones == 3)
        {
          correrProblema7();
        }
        else if (opcionSimulaciones == 4)
        {
          correrProblema9();
        }
        else if (opcionSimulaciones == 5)
        {
          correrProblema11();
        }
        else if (opcionSimulaciones == 6)
        {
          break;
        }
        else
        {
          cout << "Opción no reconocida, inténtelo de nuevo.";
        }
      }
      cout << endl;
      break;
    case 2:
      cout << "\nSEMÁFORO: Variable especial protegida que solo puede tomar valores enteros y nos ayuda en la sincronización de procesos." << endl;
      cout << "Únicamente puede ser modificada por sus 3 operaciones atómicas:" << endl;
      cout << "\tWait --> Bloquea al proceso si no se puede acceder al recurso crítico" << endl;
      cout << "\tSignal --> Señaliza que el recurso crítico dejó de utilizarse por el proceso que da la señal" << endl;
      cout << "\tInitSemaphore --> Da valor inicial al semáforo." << endl;
      cout << endl;
      cout << endl;
      break;
    case 3:
      cout << "\nProyecto para la materia TC2008 - Sistemas Operativos en el Instituto Tecnológico y de Estudios Superiores de Monterrey" << endl;
      cout << "Profesor David Alonso Cantú Delgado" << endl;
      cout << "Integrantes del equipo: " << endl;
      cout << "\tLorena Ang Alcorta" << endl;
      cout << "\tJorge Besnier Benavides" << endl;
      cout << "\tJose Daniel Hernandez Rios" << endl;
      cout << "\tSebastian Andres Saldana Cardenas" << endl;
      cout << "\tJazmin Yolistli Santibanez de la Rosa" << endl;
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
