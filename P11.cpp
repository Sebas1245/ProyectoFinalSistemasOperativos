#include <iostream>
#include <thread>
#include <vector>
#include "semaphore.h"

using namespace std;

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
    {           //Si el baño esta vacio
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
    {           //Si el baño esta vacio
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

int main()
{
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
    return 0;
}