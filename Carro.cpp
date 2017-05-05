#include "Carro.h"

Carro::Carro(const unsigned int& vagas_, const unsigned int& totalPassageiros_, Parque* pParque_){
    vagas = vagas_;
    totalPassageiros = totalPassageiros_;
    pParque = pParque_;
    filaDePassageiros = new unsigned int[totalPassageiros];
    
    for(unsigned int i = 0; i < totalPassageiros; i++)
        filaDePassageiros[i] = 0;
}

Carro::~Carro(){
    delete[] filaDePassageiros;
    if(thread != NULL)
        delete thread;
}

void Carro::Start(){
    thread = new std::thread(&Carro::Rotina, this);
}

void Carro::Rotina(){
    while(totalPassageiros != 0){
        estado = EsperandoEntrar; // espera os passageiros embarcarem no carro
        while(estado != DandoAVolta){
             if(totalPassageiros == 0)
                return;
             //std::cerr <<"Numero de Passageiros1: "<< nPassageiros << std::endl;
             std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        std::cerr << "A Volta começou" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cerr << "A volta acabou" << std::endl;
        pParque->IncrementarVoltas();//incrementa o numero de voltas e verifica se é suficiente para fechar o parque
        estado = EsperandoSair;//termina a volta


        while(nPassageiros > 0){//espera os passageiros sairem
            //std::cerr <<"Numero de Passageiros2: "<< nPassageiros << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

    }
}