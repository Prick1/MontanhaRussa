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
    unsigned int voltasDadas = 0;
    Passageiro(const int& ID_,Carro* pCarro_);
    ~Passageiro();
};

#endif // PASSAGEIRO_H_