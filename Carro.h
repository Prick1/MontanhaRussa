#ifndef CARRO_H_
#define CARRO_H_
#include <cstdlib>
#include <thread>
#include <algorithm>
#include <chrono>
#include <atomic>
#include <iostream>
#include "Parque.h"

typedef enum Estado{
    DandoAVolta, EsperandoEntrar, EsperandoSair
}tEstado;

class Carro{
public:
    unsigned int *filaDePassageiros;
    unsigned int vagas;
    unsigned int totalPassageiros;
    tEstado estado;
    std::thread *thread = NULL;
    Parque *pParque;
    void Start();
    void Rotina();
    unsigned int nPassageiros{0};
    std::atomic_flag lock = ATOMIC_FLAG_INIT;
    std::atomic_flag lock2 = ATOMIC_FLAG_INIT;
    Carro(unsigned int vagas_, unsigned int totalPassageiros_, Parque* pParque_);
    Carro(){}
    ~Carro();
};


#endif // CARRO_H_