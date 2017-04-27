#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_

#include "Carro.h"


class Passageiro{
public:
    unsigned int ID;
    Carro* pCarro;
    std::thread* thread = NULL;
    unsigned int tempoDePasseio = rand()%2000;
    void Start();
    void Rotina();
    Passageiro(int ID_,Carro* pCarro_);
    ~Passageiro();
};

#endif // PASSAGEIRO_H_