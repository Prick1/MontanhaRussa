#include "Passageiro.h"

bool TesteDaPadaria(unsigned int fichaP1, unsigned int idP1, unsigned int fichaP2,unsigned int idP2){
    if(fichaP1 >= fichaP2 && idP1 > idP2){
        return true;
    }
    return false;
}

Passageiro::Passageiro(const int& ID_,Carro* pCarro_): ID(ID_), pCarro(pCarro_){}

void Passageiro::Rotina(){
    while(1){

        
        pCarro->filaDePassageiros[ID] = 1;
        pCarro->filaDePassageiros[ID] = *std::max_element(pCarro->filaDePassageiros, pCarro->filaDePassageiros + pCarro->totalPassageiros) + 1;//ve a ficha dos outros e pega uma maior
        

        for(unsigned int i = 0; i < pCarro->totalPassageiros; i++){//espera a vez de entrar no carro
            while(pCarro->filaDePassageiros[i] != 0 && pCarro->filaDePassageiros[ID] >= pCarro->filaDePassageiros[i]){
                if(pCarro->filaDePassageiros[ID] == pCarro->filaDePassageiros[i] && ID <= i)
                    break;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                
            }
        }


            
        while(pCarro->estado != EsperandoEntrar){//espera a volta acabar e ser liberado para entrar
         
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if(pCarro->pParque->fechouParque){//Se o parque fechou, sai dele
                while(pCarro->lock.test_and_set());
                std::cerr << "Passageiro [" << ID << "] , Que Andou ["<< voltasDadas <<"] Voltas, Saiu do Parque" << std::endl;
                pCarro->totalPassageiros--;//diminui o numero de passageiros
                pCarro->filaDePassageiros[ID] = 0;//libera a vez na padaria
                pCarro->lock.clear();
                return;
            }
        } 
        if(pCarro->pParque->Voltas == pCarro->pParque->totalVoltas){//Se o parque fechou, sai dele
            while(pCarro->lock.test_and_set());
            std::cerr << "Passageiro [" << ID << "] , Que Andou ["<< voltasDadas <<"] Voltas, Saiu do Parque" << std::endl;
            pCarro->totalPassageiros--;//diminui o numero de passageiros
            pCarro->filaDePassageiros[ID] = 0;//libera a vez na padaria
            pCarro->lock.clear();
            return;
        }

        std::cerr << "Passageiro [" << ID << "] Com ficha ["<< pCarro->filaDePassageiros[ID] << "] Entrou no carro" << std::endl;
        pCarro->nPassageiros++;//entra no carro
        if(pCarro->nPassageiros == pCarro->vagas)
            pCarro->estado = DandoAVolta;
        
        pCarro->filaDePassageiros[ID] = 0;

        while(pCarro->estado != EsperandoSair){//espera a volta acabar pra sair do carro
    
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            
        }

        while(pCarro->lock.test_and_set());//sair do carro
        std::cerr << "Passageiro [" << ID << "] Saiu do Carro" << std::endl;
        (pCarro->nPassageiros)--;
        tempoDePasseio = rand()%5000;//define o tempo que vai passear
        voltasDadas++;
        if(pCarro->pParque->Voltas == pCarro->pParque->totalVoltas){//Se o parque fechou, sai dele
            std::cerr << "Passageiro [" << ID << "] , Que Andou ["<< voltasDadas <<"] Voltas, Saiu do Parque" << std::endl;
            pCarro->totalPassageiros--;//diminui o numero de passageiros
            pCarro->lock.clear();
            break;
        }
        pCarro->lock.clear();
        std::this_thread::sleep_for(std::chrono::milliseconds(tempoDePasseio));//passear pelo parque
        
    }

}

void Passageiro::Start(){
    thread = new std::thread(&Passageiro::Rotina, this);
}

Passageiro::~Passageiro(){}