#ifndef __NABIRH__
#define __NABIRH__

#include "dice.h"
class Nabir
{
    static constexpr float EPS=0.00001;
    Dice *dices=nullptr;   // масив кубиків
    int numcubes=0;//к-ть кубиків у наборі
    float *probability=nullptr;
    int *sums=nullptr;
    float expect=0.0;
public:
    float GetExp();
    bool operator>(const Nabir& other) const;
    bool operator<(const Nabir& other) const;
    bool operator==(const Nabir& other) const;
    bool operator!=(const Nabir& other) const;
    void Add(Dice& kub);
    void Summ(int show=0);
    void print();
};

#endif