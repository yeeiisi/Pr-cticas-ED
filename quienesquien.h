/**
 * @file quienesquien.h
 * @brief Fichero cabecera del QuienEsQuien.
 *
 * Almacena el �rbol de preguntas para jugar al �Qui�n es qui�n?.
 */

#ifndef _QUIENESQUIEN_H_
#define _QUIENESQUIEN_H_

#define DEBUG_QUIENESQUIEN 0

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <cassert>
#include <set>
#include <sstream>
#include "pregunta.h"
#include "bintree.h"
#include "ventana.h"
#include "consola.h"
#include "tablerografico.h"
using namespace std;

/**
 * @brief T.D.A. QuienEsQuien
 *
 * Conjunto de personajes con sus atributos.
 */
class QuienEsQuien{
private:
	/**
	  * @brief Almacena el nombre de los personajes. Su �ndice en
	  *        este vector corresponde con el �ndice de su
	  *        descripci�n en el tablero.
	  */
	vector<string> personajes;

	 /**
      * @brief Almacena el nombre de las imagenes en disco de los  personajes. Su �ndice en
      *        este vector corresponde con el �ndice de su
      *        descripci�n en el tablero.
      */
    vector<string> personajes_images;


	/**
	  * @brief Almacena los atributos.  Su �ndice en este vector
	  *        corresponde con el �ndice correspondiente de cada
	  *        vector del tablero.
	  */
	vector<string> atributos;

	/**
	  * @brief Matriz que almacena para cada personaje su valor para
	  *        cada atributo.
	  */
	vector<vector<bool>> tablero;

	/**
	  * @brief Arbol de preguntas para adivinar personajes.
	  */
	bintree<Pregunta> arbol;

	/**
	  * @brief Nodo del arbol de preguntas correspondiente a la jugada
	  *        actual.
	  */
	bintree<Pregunta>::node jugada_actual;

	 /**
     * @brief tg es el tablero grafico donde se muestra los personajes
     */
    TableroGrafico *tg;

    /**
     * @brief con consola para interactuar con el usuario
     */
    Consola *con;

    /**
     * @brief imagen_ocultar nombre de la imagen en disco para ocultar el personaje
     */
    string imagen_ocultar;

    /**
     * @brief modo_graph flag que indica si se usa el modelo grafico o solo texto
     */
    bool modo_graph;

    /**
     * @brief arbol_mejorado flag que indica si se deber�a llamar al m�todo crear_arbol (si vale false) o si se deber�a llamar al m�todo crear_arbol_mejorado (si vale true)
    */
    bool arbol_mejorado;


	/**
	  * @brief Esta es una propuesta de cabecera de la funci�n para crear el arbol.
	  * 	   Este m�todo debe crear el �rbol eligiendo las preguntas en orden.
	  */
	 bintree<Pregunta> crear_arbol(vector<string> atributos,
                                    int indice_atributo,
                                    vector<string> personajes,
                                    vector<bool> personajes_restantes,
                                    vector<vector<bool>> tablero);

	 /**
	  * @brief Esta es una propuesta de cabecera de la funci�n para crear el arbol.
	  *        Este m�todo implementa la mejora de creaci�n del �rbol donde las preguntas se escogen maximizando la entrop�a
	  *        (es decir, intentando que el �rbol est� balanceado).
	  */
	 bintree<Pregunta> crear_arbol_mejorado(vector<string> atributos,
                                    int indice_atributo,
                                    vector<string> personajes,
                                    vector<bool> personajes_restantes,
                                    vector<vector<bool>> tablero);

	 double calcular_entropia(int indice_atributo, vector<vector<bool>> tablero, vector<bool> personajes_restantes);

	 int selecion_mejor_atrib(vector<string> atributos, vector<bool> personajes_restantes, vector<vector<bool>> tablero);


public:
	/**
	  * @brief Constructor b�sico de la clase
	  */
	QuienEsQuien();
	/**
	  * @brief Constructor de copia.
	  * @param quienEsQuien QuienEsQuien a copiar.
	  */
	QuienEsQuien(const QuienEsQuien &quienEsQuien);
	/**
	  * @brief Destructor del pregunta.
	  */
	~QuienEsQuien();
	/**
	  * @brief Vacia todos los datos del QuienEsQuien receptor.
	  */
	void limpiar();
	/**
	* @brief Sobrecarga del operador de asignaci�n.
	* @param quienEsQuien objeto a copiar.
	* @return Referencia al objeto copiado.
	*/
	QuienEsQuien& operator = (const QuienEsQuien &quienEsQuien);

	/**
	  * @brief Operador de extracci�n de flujo.
	  * @param is Stream de entrada
          * @param quienEsQuien Quien es quien a leer.
	  * @return Referencia al stream de entrada.
	  *
	  * Lee de @e is un quien es quien y lo almacena en @e
	  * quienEsQuien. El formato aceptado para la lectura es un TSV
	  * (tab-separated values) en el que las columnas tienen cabecera y
	  * son las preguntas. La �ltima columna corresponde al nombre del
	  * personaje. Tras la cabecera se especifica en cada l�nea un
	  * personaje, teniendo el valor 1 o 0 si tiene/no tiene el
	  * atributo de la columna. En la �ltima columna se da el
	  * nombre del personaje.
	  */
	friend istream& operator >> (istream& is, QuienEsQuien &quienEsQuien);

	/**
	  * @brief Operador de inserci�n de flujo.
	  * @param os Stream de salida
	  * @param quienEsQuien Quien es quien a escribir.
	  * @return Referencia al stream de salida.
	  *
	  * Escribe en @e is un quien es quien.
	  * El formato usado para la escritura es un TSV
	  * (tab-separated values) en el que las columnas tienen cabecera y
	  * son las preguntas. La �ltima columna corresponde al nombre del
	  * personaje. Tras la cabecera se especifica en cada l�nea un
	  * personaje, teniendo el valor 1 o 0 si tiene/no tiene el
	  * atributo de la columna. En la �ltima columna se da el
	  * nombre del personaje.
	  */
	friend ostream& operator << (ostream& os, const QuienEsQuien &quienEsQuien);

	/**
	  * @brief Escribe en la salida estandard las estructuras atributos, personajes y tablero.
	  */
	void mostrar_estructuras_leidas();

	/**
	  * @brief Este m�todo construye el �rbol de preguntas para todos los personajes del tablero.
	  */
	bintree<Pregunta> crear_arbol();

	/**
	  * @brief Sustituye el �rbol actual por el �rbol pasado por par�metro.
	  *
	  * @param arbol_nuevo Arbol de preguntas que sustituye al actual.
	  *
	  */
	void usar_arbol(bintree<Pregunta> arbol_nuevo);

	/**
	  * @brief Escribe el arbol generado en la salida estandard.
	  */
	void escribir_arbol_completo() const;

	/**
	  * @brief M�todo que modifica el �rbol de preguntas para que haya
	  *        preguntas redundantes.
	  * @post El �rbol de preguntas se modifica.
	  */
	void eliminar_nodos_redundantes();

	//Función auxiliar que permite eliminar los nodos con un solo hijo de manera recursiva.
	//Va recorriendo nodos hasta que se encuentre con un nodo nulo. (es decir, se ha llamado desde una hoja)
	void elimina_nodos_recursivos(bintree<Pregunta>::node nodo);

	void preguntas_formuladas(bintree<Pregunta>::node jugada);

	/**
	  * @brief Inicializa el juego.
	  * @post  Si la partida anterior no hab�a terminado se
	  *        pierde el progreso.
	  */
	void iniciar_juego();

	/**
	  * @brief Dado un estado del tablero devuelve los nombres de
	  *        los personajes que a�n no han sido tumbados en el
	  *        tablero.
	  *
	  * @param jugada_actual Nodo del estado del tablero.
	  *
	  * @return Conjunto de personajes que no han sido tumbados en el tablero.
	  *
	  * @pre El arbol del QuienEsQuien receptor debe haber sido construido previamente.
	  * @pre El nodo indicado debe ser un nodo del arbol del QuienEsQuien receptor.
	  */
	set<string> informacion_jugada(bintree<Pregunta>::node jugada_actual);

	/**
	  * @brief Este m�todo permite calcular la media de la profundidad de las hojas del �rbol.
	  * Este valor representa el n�mero (promedio) de preguntas necesarias para adivinar cada personaje.
	  * A menor profundidad promedio, mejor soluci�n. Esta m�trica es un indicador para evaluar la calidad de vuestra soluci�n.
	  *
	  * @return Profundidad media del arbol de preguntas.
	  *
	  * @pre El arbol de preguntas debe haber sido construido previamente.
	  */
	float profundidad_promedio_hojas();

	/**
	  * @brief Rellena los datos del QuienEsQuien con un tablero calculado aleatoriamente.
	  *
	  * @param numero_de_personajes N�mero de personajes que tiene el tablero a crear.
	  */
	void tablero_aleatorio(int numero_de_personajes);

    /**
     * @brief setImagenOcultar Modifica el nombre de la imagen en disco para ocultar los personajes en modo
     * grafico
     * @param n:nombre del fichero en disco
     */
    void setImagenOcultar(const char * n);

    /**
     * @brief setModoGraph Modifica el modelo grafico
     * @param m: True si se desea modo grafico false solo texto
     */
    void setModoGraph(bool m);

    /**
     * @brief setArbolMejorado Modifica el atributo arbol_mejorado
     * @param m: True si se desea crear el �rbol de manera mejorada, false en caso contrario
     */
    void setArbolMejorado(bool m);

     /**
     * @brief Oculta en el tablero grafico los personajes que no estan activos
     * @param personajes_activos: personajes que est�n activos
     */
    void ocultar_personajes_graph(const set<string> &personajes_activos);


};

#endif

