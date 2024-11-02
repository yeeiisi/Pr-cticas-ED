/**
@file maxstack.cpp
@brief fichero con funciones primitivas de la clase MaxStack
*/
#include "maxstack.h"

MaxStack::MaxStack(){}

void MaxStack::push(int elemento){
    element almacenar;
    almacenar.value = elemento;
    cola.push(elemento);

    if(pila.empty()){
        almacenar.maximum = elemento;
        pila.push(almacenar);
    }
    else{
        if(elemento >= cola.top()){
            almacenar.maximum = elemento;
        }
        else{
            almacenar.maximum = cola.top();
        }

        pila.push(almacenar);
    }
}

element& MaxStack::top(){
    return pila.top();
}

void MaxStack::pop(){
    if(pila.top().value == cola.top()){
        cola.pop();
    }
    else{
        stack<int> auxiliar;
        while(!cola.empty() && (pila.top().value != cola.top())){
            auxiliar.push(cola.top());
            cola.pop();
        }
        cola.pop();
        while(!auxiliar.empty()){
            cola.push(auxiliar.top());
            auxiliar.pop();
        }
    }
    pila.pop();
}

bool MaxStack::empty(){
    return pila.empty(); 
}

int MaxStack::size(){
    return cola.size();
}
