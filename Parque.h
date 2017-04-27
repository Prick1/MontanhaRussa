#ifndef PARQUE_H_
#define PARQUE_H_

class Parque{
public:
    unsigned int totalVoltas = 5;
    unsigned int Voltas = 0;
    void IncrementarVoltas();
    bool fechouParque = false;
};

#endif // PARQUE_H_