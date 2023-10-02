#include "dice.h"
#include <math.h>
#include <iostream>
#include <iomanip>

Dice::Dice(){}
void Dice::Init(int s1,int s2,float step) //конструктор. Діапазони можливих значень від s1 до s2
{
    if(probability)
        delete[] probability;
    if(face)
        delete[] face;

    //side=s2-s1+1;
    if(step<1) step=1;
    side=0.5+(s2-s1+1)/step;
    step=(s2-s1+1.0)/side;

    probability = new float[side];
    face        = new int[side];

    for(int i=0; i<side; i++)
        face[i]=(int)(s1+i*step+0.0);

    //розпишемо на грані числа від sz1 ...sz2
    // можна і довільні числа на гранях, не обовязково послідовні АЛЕ ВПОРЯДКОВАНІ менш-більш
    //for(int i=0; i<side; i++)
    //    face[i]=s1+i;



    // випадкові ймовірності граням
    setRNDprobability();
}

// Конструктор копіювання
Dice::Dice(const Dice& other)
{
    // Копіюємо кількість граней
    side = other.side;

    // Виділяємо пам'ять для нового масиву граней і ймовірностей
    face = new int[side];
    probability = new float[side];

    // Копіюємо значення граней та ймовірностей з іншого об'єкта
    for (int i = 0; i < side; i++)
    {
        face[i] = other.face[i];
        probability[i] = other.probability[i];
    }
}

// Оператор присвоювання
Dice& Dice::operator=(const Dice& other)
{
    if (this == &other)
    {
        // Перевірка на самоприсвоєння
        return *this;
    }

    // Видаляємо старі дані
    delete[] face;
    delete[] probability;

    // Копіюємо кількість граней
    side = other.side;

    // Виділяємо пам'ять для нового масиву граней і ймовірностей
    face = new int[side];
    probability = new float[side];

    // Копіюємо значення граней та ймовірностей з іншого об'єкта
    for (int i = 0; i < side; i++)
    {
        face[i] = other.face[i];
        probability[i] = other.probability[i];
    }

    return *this;
}

//конструктор для кубика з сумами на гранях від 1 до size
Dice::Dice(int size) : Dice(1, size){}

//конструктор для кубика з сумами на гранях від sz1 до sz2
Dice::Dice(int sz1, int sz2)
{
    Init(sz1,sz2);
}
//void setprobability(int i, int percent){}

//скільки очок на певній грані
int Dice::CostBySide(int i){return face[i];}
float Dice::ProbBySide(int i){return probability[i];}

void Dice::setRNDprobability()
{
    //side-граней
    //в середньому на кожній грані(при рівномірному розподілу)
    float f=1.0/side;     // {0.25 0.25 0.25 0.25} =1
    for(int i=0; i<side; i++)
        probability[i]=f;

    int sd1, sd2;  // пара для перерозподілу ймов
    for(int k=1; k<30; k++)
    {
        f=rand()%100/100.0;// випадкова величина перерозподілу
        sd1=rand()%side;
        sd2=rand()%side;
        if(probability[sd1]-f>0 && probability[sd2]+f<1)
        {
            probability[sd1]-=f;//в одному місці віднімемо
            probability[sd2]+=f;//в інше те ж прибавимо
        }
    }
    // про всяк випадок перевіримо щоб сума була 1
    float s=0;
    for(int i=0; i<side; i++)
        s+=probability[i];   //0.98
    float correct=1-s;// те що заважає бути сумі рівним 1
    for(int i=0; i<side; i++)
        if(probability[i]+s<1 && probability[i]+s>0)
            //додамо до першої ж ймовірності яка попадеться
            probability[i]+=s;
}

//генерує випадкову грань згідно з ймовірностями
int Dice::Throw()
{
    int g;
    float cum=0.0;
    float rnd=rand()%100000/100000.0;

    for(int i=0; i<side; i++)
    {
        cum+=probability[i];
        if(rnd<=cum)
        {
            g=face[i];
            break;
        }
    }
    return g;
}

void Dice::print()
{   std::cout<< std::fixed << std::setprecision(2);
    std::cout<<side<<"-sided dice: {";
    for(int i=0; i<side; i++)
    {
        std::cout<<CostBySide(i)<<"(" << probability[i]<<")";
        if(i!=side-1)
            std::cout<<", ";
        else
            std::cout<<"}";
    }
}
Dice::~Dice(){delete[] probability;delete[]face;}
int Dice::sides(){return side;}

