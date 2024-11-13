/**
@file maxstack.cpp
@brief fichero con funciones primitivas de la clase MaxStack
*/
#include "../include/maxstackYeray.h"

MaxStack::MaxStack(){}

void MaxStack::push(int elemento){
    element dato;
    dato.value = elemento;
    pair<element,int> almacenar; 

    if(cola.empty()){
        dato.maximum = elemento;
        almacenar.first = dato;
        almacenar.second = 1;
        cola.push(almacenar);
    }
    else{
        if(elemento >= cola.top().first.maximum){
            dato.maximum = elemento;
            
        }
        else{
            dato.maximum = cola.top().first.maximum;
        }

        almacenar.first = dato;
        almacenar.second = (cola.top().second + 1);
        cola.push(almacenar);
    }
}

const element& MaxStack::top(){
    return cola.top().first;
}

void MaxStack::pop(){
    cola.pop();
}

bool MaxStack::empty(){
    return cola.empty(); 
}

int MaxStack::size(){
    return cola.size();
}
