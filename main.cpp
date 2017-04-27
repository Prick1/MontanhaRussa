
#include <iostream>
#include <thread>
#include "Passageiro.h"

int main(){
    Parque parque1;
    Carro carro1(5, 10, &parque1);
    
    Passageiro *passageiros[10];
    
    for(int i = 0; i < 10; i++){
        passageiros[i] = new Passageiro(i, &carro1);
    }
    
    

    carro1.Start();
    for(int i = 0; i < 10; i++){
        passageiros[i]->Start();
    }

    carro1.thread->join();
    return 0;
    for(int i = 0; i < 10; i++){
        delete passageiros[i];
    }
}