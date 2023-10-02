#ifndef __DICEH__
#define __DICEH__

class Dice
{
    // int - БУДЕ масив ск на і-й грані очок
    //       зараз на ій грані і+1 очок
    // масив граней "кубика" для фіксації очок на кожній грані
    int *face=nullptr;

    //масив ймовірностей випадіння кожної грані
    float *probability=nullptr;

    //к-ть граней
    int side=0;
public:

    Dice();
    //конструктор для кубика з сумами на гранях від 1 до size

    Dice(int size);

    //конструктор для кубика з сумами на гранях від sz1 до sz2
    Dice(int sz1, int sz2);

    void Init(int s1, int s2,float=1.0);

    // Оператор присвоювання
    Dice& operator=(const Dice& other);

    // Конструктор копіювання
    Dice(const Dice& other);

    //void setprobability(int i, int percent){}
    //скільки очок на певній грані
    int CostBySide(int i);
    float ProbBySide(int i);
    void setRNDprobability();

    //викидає випадкову грань згідно з ймовірностями
    int Throw();
    void print();
    ~Dice();
    int sides();
};
#endif