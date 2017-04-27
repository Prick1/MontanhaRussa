#include "Parque.h"

void Parque::IncrementarVoltas(){
    Voltas++;
    if(Voltas == totalVoltas)
        fechouParque = true;
}