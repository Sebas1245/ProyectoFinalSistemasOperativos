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
Se eligió utilizar `C++` para utilizar la librería de `<thread>` que fue introducida a partir de `C++11`. Asimismo, se utiliza una implementación de semáforos que se puede encontrar en el archivo llamado `semaforo.h`, el cual está en el directorio raíz de este repositorio. 

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

## Programa 1: Barberia
La barbería esta regentada por un peluquero, tiene una silla para atender a los clientes y sillas para que esperen los clientes. Si no hay clientes, el peluquero espera durmiendo a que entren a la peluquería. Cuando llega un cliente, tiene que despertar al peluquero. Si llegan más clientes mientras el peluquero está atendiendo a un cliente se sientan si hay sillas libres, o se van si no pueden sentarse.

Mas informacion de este problema [aqui](https://lsi2.ugr.es/jagomez/sisopi_archivos/Sincronizacion.htm#ExPelu)

## Programa 2: Productor-Consumidor
Explicación del problema: Ejercicio 9 hecho en clase. Se tienen dos procesos concurrentes que cooperan como productor y consumidor con la siguiente restricción: El productor siempre produce un dato cada vez El consumidor debe tomar de dos datos a la vez. Suponiendo que el buffer común es de tamaño 2, plantee una solución al problema usando semáforos.

Explicación del código: 
* Se utilizan dos semáforos
	* un semáforo que controla los espacios disponibles
	* un semáforo que controla los espacios ocupados
	* adicionalmente se utiliza un contador para saber la cantidad de cooperaciones exitosas entre productor-consumidor.
* Por otra parte, cuenta con dos procesos
	* El proceso de productor produce mientras tenga espacios disponibles
	* El consumidor espera a que el productor haya producido dos unidades para poder consumir
	* Finalmente el contador nos indica cuantas operaciones exitosas se han realizado.

## Programa 3: H20
Explicación del problema: Ejercicio 9 hecho en clase. En este problema se tienen los procesos de Hidrógeno y Oxígeno, se busca que solo puedan ser procesados en grupos de 3, teniendo 2 hidrógenos y un oxígeno. De no cumplirse el grupo de 3, los procesos estarían en espera hasta completarse el grupo. 

Explicación del código:  
* Hay 2 semáforos: uno para llevar el conteo de los hidrógenos existentes y otro para controlar el paso de los hidrógenos, el cuál se "encendería" cuando se haya completado un grupo y así permitiría la completación de procesos. 
* Se manejan los procesos como funciones, una para hidrógeno y otra para oxígeno. 
	* El proceso de hidrógeno aumenta el semáforo de hidrógeno y espera al semáforo de paso. 
	* El proceso de oxígeno es el "detonante" para completar los proces. 
	* Primero hay dos esperas (P) para el semáforo de hidrógenos, asegurando la existencia de al menos 2 h's. 
* Una vez encontrados, se ejecuta la sección crítica(unión) y aumenta en 2 el semáforo de paso para dar luz verde a dos hidrógenos que se encuentran en espera. 

## (Extra) Programa 4: Estacionamiento
Explicación del problema: Se tiene un estacionamiento que tiene 1 puerta de entrada–salida y 50 lugares individuales. Se desea sincronizar la entrada y salida de carros del estacionamiento. Sólo se permite que un carro entre o salga del estacionamiento a la vez. Los carros siempre están tratando de entrar o salir del estacionamiento. Si el estacionamiento está lleno, los carros hacen fila fuera de él. Hay 2 procesos, carro entra, carro sale.

Explicación del código: 
* Se utilizan tres semáforos
	* un semáforo que controla los espacios disponibles
	* uno semáforo que controla los espacios ocupados
	* un semáforo binario para controlar la entrada y salida de los autos
	* adicionalmente se utiliza un contador para saber la cantidad de autos adentro del estacionamiento.

* Por otra parte, cuenta con tres procesos
	1. Entra al estacionamiento donde se verifica que el estacionamiento tenga lugar disponible y verifica que pueda entrar por la puerta.
	2. Sale de estacionamiento donde se verifica si hay autos disponibles adentro para poder sacar y verifica que pueda salir por la pueta.


## (Extra) Programa 5: Baños 
Explicación del problema: Ejercicio 9 hecho en clase.  El campus Monterrey está considerando implementar una política para ponerle fin a la práctica de tener baños separados por género, conservando la regla de que solo puedan ser usados por personas del mismo género al mismo tiempo.

Las nuevas reglas indican lo siguiente:
 1. El baño puede estar en tres estados: vació, con mujeres o con hombres.
 2. Cuando lo estén usando las mujeres, solo otras mujeres pueden entrar al baño y los hombres no, y viceversa.
 3. Cuando el baño este vació puede ser usado por un hombre o una mujer y se mantendrá dedicado al género que entró al baño, hasta que salga la última persona de ese género.
 4. Puedes asumir que los baños tienen capacidad infinita, es decir, cualquier persona que quiera entrar al baño lo va a poder hacer siempre y cuando este vació u ocupado por personas del mismo género y que la puerta no la esté usando nadie.
 5. procedimientos:
  * mujer_entra_baño (Pueden estar corriendo n procesos de este tipo)
  * hombre_entra_baño (Pueden estar corriendo n procesos de este tipo)
  * mujer_sale_baño (Pueden estar corriendo n procesos de este tipo)
  * hombre_sale_baño (Pueden estar corriendo n procesos de este tipo)
  * el procedimiento principal.

# Video de demostración
El video de demostración del proyecto se puede ver [aquí](https://drive.google.com/file/d/12r2J1lszhV_v4FrxgHSc85Mbr5Gif0-_/view?usp=sharing)

# Breve descripción
Para el funcionamiento correcto y más sencillo del proyecto se requiere de la versión más actualizada del software de repl.it, o bien existen otras opciones similares que pueden funcionar. Sin embargo, nosotros consideramos como mejor opción repl.it por su simplicidad y capacidad de colaboración.

Instrucciones para probar el código:
 * Opción 1: Acceder directamente al nuestro repl.it mediante este [link](https://repl.it/join/hdcwobzj-loreang98) y utilizar el botón de run en la parte superior para correr el programa. Posteriormente, seguir instrucciones del menú.
 * Opción 2: Descargar el archivo main.cpp y el archivo semaphore.h, enseguida crear su propio repositorio de repl.it o software que usted crea conveniente (no garantizamos funcionamiento en otro software).

Archivos que conforman el proyecto:
 * main.cpp: incluye el menú principal, descripción de los problemas y finalmente los problemas de sincronización.
 * Semaphore.h: funcionamiento básico para sincronizar procesos donde se incluye una clase publica para poder crear objectos en el main, por otra parte se incluye la función void V() que libera un recurso y p() para revisar la disponibilidad del recurso que se busca utilizar. 

# Otro Setup para utilizar el proyecto
Clona este repositorio a tu directorio local de preferencia. Este proyecto fue desarollado con una librería especializada de `C++` llamada `<thread>` por lo que requiere compilarse con `C++11` o superior. Una vez clonado, compila el proyecto con el siguiente comando:
~~~
g++ -pthread -std=c++17 main.cpp -o main
~~~
Es importante notar que si se pretende utilizar este proyecto en **Windows** se pueden generar algunos errores debido a que se debe de contar con un compilador que soporte un entorno multithreading, por ejemplo **MinGW-w64** con la opción de `posix` habilitada al momento de instalación. Para más información sobre este problema visita [este post de Stack Overflow](https://stackoverflow.com/questions/17242516/mingw-w64-threads-posix-vs-win32).
