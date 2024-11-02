/**
 * @file maxstack.cpp
 * @brief  Archivo de implementación del TDA MaxStack
 * @author
 */
#include "maxstack.h"
#include <iostream>
#include <queue>

using namespace std;

bool element::operator <(const element& elem2) const {
    return this->maximum < elem2.maximum;
}

ostream& operator<<(ostream& flujo, const Element& elem) {
    flujo << "{value: " << elem.value << ", maximum: " << elem.maximum << "}" << endl;
    return flujo;
}

void MaxStack::push(int valor){
    element almacenar;
    almacenar.value = valor;
    
    if(pila.empty()){
        cola.push(valor);
        almacenar.maximum = valor;
    }else{
        if(almacenar.value < cola.top()){
            almacenar.maximum = cola.top();
        }else{
            almacenar.maximum = almacenar.value;
        }
    }

    pila.push(almacenar); 
    cola.push(almacenar.maximum);
}

void MaxStack::pop(){
    if(!pila.empty()){
        pila.pop();
        if(!cola.empty()){
            cola.pop();
        }
    }
}

element MaxStack::top(){
    if(!pila.empty()){
        return pila.top();
    }else{
        cout << "Error";
    }
}

bool MaxStack::empty(){
    return pila.empty();
}

size_t MaxStack::size(){
    return pila.size();
}


