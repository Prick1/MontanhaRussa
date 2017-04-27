#include "Passageiro.h"


Passageiro::Passageiro(int ID_, Carro* pCarro_): ID(ID_), pCarro(pCarro_){}

void Passageiro::Rotina(){
    while(1){

        while(pCarro->lock.test_and_set());//ve a ficha dos outros e pega uma maior
        pCarro->filaDePassageiros[ID] = 1;
        pCarro->filaDePassageiros[ID] = *std::max_element(pCarro->filaDePassageiros, pCarro->filaDePassageiros + pCarro->totalPassageiros) + 1;
        std::cerr << "Passageiro " << ID << " Pegou a ficha " << pCarro->filaDePassageiros[ID] << std::endl; 
        pCarro->lock.clear();

        for(unsigned int i = 0; i < pCarro->totalPassageiros; i++){//espera a vez de entrar no carro
            while(pCarro->filaDePassageiros[ID] > pCarro->filaDePassageiros[i] && pCarro->filaDePassageiros[i] != 0){
                //std::cerr << "Passageiro "<< ID << " Travado por Passageiro " << i << " Com Ficha " << pCarro->filaDePassageiros[i] << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                
            }
        }


            
        while(pCarro->estado != EsperandoEntrar || pCarro->nPassageiros >= pCarro->vagas){//espera a volta acabar e ser liberado para entrar
            /*std::cerr << "Passageiro " << ID << " Esperando a Volta Acabar" << std::endl;
            std::cerr << "Estado: ";
            if(pCarro->estado == EsperandoEntrar)
                std::cerr << "EsperandoEntrar";
            else if(pCarro->estado == EsperandoSair)
                std::cerr << "EsperandoSair";
            else
                std::cerr << "DandoAVolta";
            std::cerr << std::endl;
            std::cerr << "nPassageiros :" << pCarro->nPassageiros << std::endl;*/
            std::this_thread::sleep_for(std::chrono::milliseconds(1));

        } // espera a volta acabar
        if(pCarro->pParque->fechouParque){//Se o parque fechou, sai dele
            std::cerr << "Passageiro " << ID << " Saiu do Parque" << std::endl;
            pCarro->totalPassageiros--;//diminui o numero de passageiros
            pCarro->filaDePassageiros[ID] = 0;//libera a vez na padaria
            break;
        }

        std::cerr << "Passageiro " << ID << " Entrou no carro" << std::endl;
        pCarro->nPassageiros++;//entra no carro
        
        pCarro->filaDePassageiros[ID] = 0;

        while(pCarro->estado != EsperandoSair){//espera a volta acabar pra sair do carro
            /*std::cerr << "Passageiro " << ID <<" Travado" << std::endl;
            std::cerr  << "Estado2: ";
             if(pCarro->estado == EsperandoEntrar)
                std::cerr << "EsperandoEntrar";
            else if(pCarro->estado == EsperandoSair)
                std::cerr << "EsperandoSair";
            else
                std::cerr << "DandoAVolta";
            std::cerr << std::endl;*/
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        while(pCarro->lock.test_and_set());//sair do carro
        (pCarro->nPassageiros)--;
        std::cerr << "Passageiro " << ID << " Saiu do Carro" << std::endl;
        pCarro->lock.clear();

        std::this_thread::sleep_for(std::chrono::milliseconds(rand()%5000));//passear pelo parque
    }

}

void Passageiro::Start(){
    thread = new std::thread(&Passageiro::Rotina, this);
}

Passageiro::~Passageiro(){
    if(thread != NULL)
        delete thread;
}