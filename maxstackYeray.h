#ifndef PRACTICA4_MAXSTACK
#define PRACTICA4_MAXSTACK
#include <iostream>
#include <queue>
using namespace std;

/**
 * @file maxstack.h
 * @brief  Archivo de especificación del TDA MaxStack
 * @author José Carlos y Yeray
 */

struct element {
int value; // Current value to store
int maximum; // Current max value in the structure
};

/**
 * @brief Struct con un functor que usará la cola con prioridad para ordenar los elementos en su interior.
 * Compara los int de los pairs, los cuales representan el orden de inserción en la cola.
 * @param primero: Pair que contiene un element y un int
 * @param segundo: Pair de element e int para comparar con el primero
 * @return TRUE si el second del primero es menor, FALSE si es mayor
 */
struct Comparar{
    bool operator()(pair<element,int> primero, pair<element,int> segundo){
        if(primero.second < segundo.second)
            return true;
        else
            return false;
    }
};

/**
  @brief T.D.A. MaxStack

  Una instancia del tipo de dato abstracto MaxStack nos permite almacenar datos de tipo element, comportándose como una pila y diciendo cuál es el máximo de los introducidos en cada momento

  El TDA ofrece los mismos métodos que una pila, pudiendo añadir, consultar el último añadido, quitar un elemento y consultar si está vacía y su tamaño

  El formato de los elementos introducidos es: elemento,máximo
  Para poder usar el TDA MaxStack se debe incluir el fichero

  \#include <maxstack.h>

  @author José Carlos y Yeray
  @date Noviembre 2024

**/

class MaxStack{
/**
      @page repMaxStack Representación del TDA MaxStack .

      @section invMaxStack Invariante de la representación.

      Un objeto válido 1 del TDA MaxStack debe cumplir
        -cola.top().first.element = int
        -cola contiene un pair<element,int> 

      @section faMaxStack Función de abstracción

      Un objeto válido 1 del TDA MaxStack representa una pila que contiene datos de tipo element

    **/
private:
/**
 * @brief cola con prioridad que almacena pares de element e int y que usa el struct Comparar para su prioridad
 */
std::priority_queue<pair<element,int>,vector<pair<element,int>>,Comparar> cola;

public:

/**
 * @brief Constructor sin parámetros que genera una cola con prioridad vacía
 * @return MaxStack, el objeto MaxStack creado
 */
MaxStack();

/**
 * @brief Compara el elemento a insertar con el máximo hasta ese momento e inserta un element en la pila
 * @param elemento Entero a introducir en la pila
 */
void push(int elemento);

/**
 * @brief Método para consultar el tope de la pila
 * @return Referencia constante al element en el tope de la pila
 */
const element& top();

/**
 * @brief Elimina el elemento en el tope de la pila
 */
void pop();

/**
 * @brief Método para consultar si la pila está vacía
 * @return Bool que nos indica si la pila está vacía, true en caso afirmativo y false en el contrario.
 */
bool empty();

/**
 * @brief Método para consultar el tamaño de la pila
 * @return Entero que nos indica cuántos elementos hay introducidos en la pila
 */
int size();
};
#endif //PRACTICA4_MAXSTACK