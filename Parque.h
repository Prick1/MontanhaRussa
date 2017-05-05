#ifndef PARQUE_H_
#define PARQUE_H_

class Parque{
public:
    Parque(const unsigned int& totalVoltas_): totalVoltas(totalVoltas_){}
    unsigned int totalVoltas;
    unsigned int Voltas = 0;
    void IncrementarVoltas();
    bool fechouParque = false;
};

#endif // PARQUE_H_