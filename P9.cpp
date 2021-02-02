#include <iostream>
#include <thread>
#include <vector>
#include "semaphore.h"

using namespace std;

Semaphore sHidrogenos(0); // Semaforo que controla la cantidad de semaforos disponibles
Semaphore sPaso(0);       //Semaforo que indica si hay un oxigeno y 2 hidrogenos.

int h20 = 0;

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
    cout << " > +1 H2O" << endl;
    //h20++; // Necesitaria semaforo para proteger variable
    //cout << " ** Moleculas de H2O totales: " << h20 << endl;
}

int RunPH2O()
{
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
    return 0;
}