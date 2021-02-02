#include <mutex>
#include <condition_variable>

class Semaphore
{
public:
  Semaphore(int count_ = 0)
      : count(count_)
  {
  }

  //Funcion para aumentar semaforo/liberar un recurso
  inline void V()
  {
    std::unique_lock<std::mutex> lock(mtx);
    count++;
    cv.notify_one(); //Avisa que se libero +1 en el semaforo
  }

  //Funcion para checar si hay disponibilidad y bloquear si no
  inline void P()
  {
    std::unique_lock<std::mutex> lock(mtx);
    while (count == 0)
    {
      //Esperar hasta que haya una V/el semaforo este en 1 o mas
      cv.wait(lock);
    }
    count--; //Resta un recurso
  }

private:
  std::mutex mtx;             //Ayuda a bloquear el proceso
  std::condition_variable cv; //Ayuda a avisar que se libera un recurso
  int count;                  //Contador del semaforo
};