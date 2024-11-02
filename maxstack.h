/**
 * @file maxstack.h
 * @brief  Archivo de especificación del TDA MaxStack
 * @author
 */

#ifndef MAXSTACK_H  // Guarda de inclusión
#define MAXSTACK_H

#include <iostream>
#include <queue>
#include <stack> // Necesario para utilizar stack

using namespace std;

// Estructura para almacenar el valor y el máximo
struct element {
    int value;   // Valor actual a almacenar
    int maximum; // Valor máximo actual en la estructura

    bool operator <(const element& elem2) const; // Declaración del operador <
};

// Sobrecarga del operador << para imprimir elementos
ostream& operator<<(ostream& flujo, const element& elem);

// Clase MaxStack que implementa una pila que puede devolver el máximo
class MaxStack {
private:
    stack<element> pila;            // Pila para almacenar elementos
    priority_queue<int> cola;      // Cola de prioridad para almacenar máximos

public:
    void push(int valor);           // Método para insertar un valor en la pila
    void pop();                     // Método para eliminar el elemento en la parte superior de la pila
    element top();                  // Método para obtener el elemento en la parte superior de la pila
    bool empty();                   // Método para verificar si la pila está vacía
    size_t size();                  // Método para obtener el tamaño de la pila
};

#endif // MAXSTACK_H
