
#include <iostream>
#include <thread>
#include "Passageiro.h"

int main(){
    unsigned int numeroDePassageiros, vagas, voltas;
    std::cout << "Defina o número de passageiros da montanha russa: ";
    std::cin >> numeroDePassageiros;
    std::cout << "Defina o número de voltas da montanha russa: " ;
    std::cin >> voltas;
    while(1){
        std::cout << "Defina o número de vagas no carro da montanha russa: ";
        std::cin >> vagas;
        if(vagas <= numeroDePassageiros)
            break;
        std::cout << "O número de vagas no carro deve ser menor ou igual ao número de passageiros" << std::endl;
    }
    
    Parque parque1(voltas);

    Carro carro1(vagas, numeroDePassageiros, &parque1);
    
    Passageiro *passageiros[numeroDePassageiros];
    
    for(int i = 0; i < numeroDePassageiros; i++){
        passageiros[i] = new Passageiro(i, &carro1);
    }
    
    

    carro1.Start();
    for(int i = 0; i < numeroDePassageiros; i++){
        passageiros[i]->Start();
    }

    carro1.thread->join();
    
    for(int i = 0; i < numeroDePassageiros; i++){
        delete passageiros[i];
    }
    return 0;
}