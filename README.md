# Proyecto Final Sistemas Operativos
Proyecto final para la clase de Sistemas Operativos del Tecnológico de Monterrey con el profesor David Cantú .

# Colaboradores
| Nombre              | Matricula        |
| -----------         | -----------      |
| Jorge Besnier       | A01039882        |
| Lorena Ang          | A01039980        |
| Daniel Hernández    | A00825596        |
| Sebastián Saldaña   | A01570274        |
| Jazmín Santibáñez   | A01234029        |

# Objetivo

Fortalecer el aprendizaje sobre la sincronización de procesos en un aplicación creada en un lenguaje de programación que soporte el uso de programación en paralelo.


# Contenido
* Instrucciones
* Componentes del código
  * Lenguaje de Programación	
  * Menú del Programa
  * Programa 1: Problema de la peluquería
  * Programa 2: Ejercicio 7 - Problema Productor/Consumidor
  * Programa 3:	Ejercicio 9 - Problema H2O
* Video de demostración
* Breve descripción	
* Setup para utilizar el proyecto

# Instrucciones

Crear una aplicación que haga uso de threads y locks (semáforos)
1. El programa deberá de contener un menú con 3 opciones, 2 de las cuales serán para simular cualquiera de los problemas vistos en clases desde el problema de productor consumidor, ejercicio 7 en adelante, y otro para simular cualquiera problema de sincronización de procesos que ustedes deseen, solo que sean retadores los problemas
2. Puede utilizar el lenguaje de programación que gustes, solo que soporte el uso de múltiples threads y programación en paralelo.
3. Deberán de grabar un video donde deberán de mostrar lo siguiente:
    *   El programa funcionará en cada una de las opciones del menú.
    *   Una breve descripción del código, donde muestren cómo fue que resolvieron la sincronización de los procesos.
4. Generen un manual de instalación y explicación explicación del código y sobre uso de la aplicación en el readme de tu repositorio (Usa lenguaje de Markdown)

# Componentes del Código


## Lenguaje de programación
Se eligió utilizar `C++` para utilizar la librería de `<threads>` que fue introducida a partir de `C++11`. Asimismo, se utiliza una implementación de semáforos que se puede encontrar en el archivo llamado `semaforo.h`, el cual está en el directorio raíz de este repositorio. 

## Menú del Programa
El menú principal del programa presenta cuatro opciones: 
1. Simulaciones de los problemas
   * Lleva al menú donde se puede elegir ejecutar cualquiera de los tres problemas que se eligieron simular para este proyecto. 
2. ¿Qué es un semaforo?
   * Provee al usuario una corta descripción de lo que es un semáforo, ya que fue concepto clave para la realización de este proyecto. 
3. Créditos
   * Despliega los responsables de la realización del proyecto. 
4. Salir
   * Termina la ejecución de la aplicación principal del proyecto.

## Programa 1:


## Programa 2:


## Programa 3:


# Video de Demostración


# Breve descripción


# Setup para utilizar el proyecto
Clona este repositorio a tu directorio local de preferencia. Este proyecto fue desarollado con una librería especializada de `C++` llamada `<thread>` por lo que requiere compilarse con `C++11` o superior. Una vez clonado, compila el proyecto con el siguiente comando:
~~~
`g++ -pthread -std=c++17 main.cpp -o main`
~~~
Es importante notar que si se pretende utilizar este proyecto en **Windows** se debe de contar con un compilador que soporte un entorno multithreading, por ejemplo **MinGW-w64**. Ciertamente, la bandera `-pthread` tiene el propósito de hacerle saber al compilador que se pretende utilizar multithreading, pero aún así se pueden generar errores con ciertos compiladores. 
