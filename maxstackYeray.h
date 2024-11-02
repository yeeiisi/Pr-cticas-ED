#ifndef PRACTICA4_MAXSTACK
#define PRACTICA4_MAXSTACK
#include <iostream>
#include <stack>
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

class MaxStack{
private:
stack<element> pila;
std::priority_queue<int> cola;
public:

MaxStack();

void push(int elemento);

element& top();

void pop();

bool empty();

int size();
};
#endif //PRACTICA4_MAXSTACK