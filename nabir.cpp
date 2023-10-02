#include "dice.h"
#include "nabir.h"
#include <math.h>
#include <iostream>
#include <iomanip>

//математичне очікування
float Nabir::GetExp()
{
    return expect;
}

//ф-ції порівняння
bool Nabir::operator>(const Nabir& other) const
{
    return  expect>other.expect;
}

bool Nabir::operator<(const Nabir& other) const
{
    return  expect<other.expect;
}

bool Nabir::operator==(const Nabir& other) const
{
    return fabs(expect-other.expect)<Nabir::EPS;
}

bool Nabir::operator!=(const Nabir& other) const
{
    return  fabs(expect-other.expect)>=Nabir::EPS;
}

void Nabir::print()
{
    std::cout<<std::endl<<"Nabir "<<numcubes<<" dices";
    for(int i=0; i<numcubes; i++)
    {
        std::cout<<std::endl<<i+1<<"\t";
        dices[i].print();
    }
    Summ(1);

}

//додавання +1 кубика
void Nabir::Add(Dice& kub)
{
    Dice *temp=new Dice[numcubes+1];
    for(int i=0; i<numcubes; i++)
    {
        temp[i]=dices[i];
    }
    temp[numcubes]=kub;
    numcubes++;
    delete[] dices;
    dices=temp;
    //після додавання ще одного кубика до набору- треба перерахувати
    //ймовірності
    Summ();
}

//show>0 то буде виводитися min інформація про набір,
//show>1 то буде виводитися інформація про набір
//show<=0  не буде ніякого виводу
void Nabir::Summ(int show)
{
    int max=0;//сума максимумів на всих гранях
    int min=0;//сума мінімумів на всих гранях
    // необх для розміру масиву сум
    int *m=new int[numcubes];//тимч масив для перебору всих варіантів ІНДЕКСИ
    for(int i=0; i<numcubes; i++)
    {
        max+=dices[i].CostBySide(dices[i].sides()-1);
        min+=dices[i].CostBySide(0);
        m[i]=0;//почнемо з нулевих індексів
    }

    //масив кількостей сум: від мінсуми....до макссуми
    int numofsums=max-min+1;

    delete[] sums;
    delete[] probability;

    sums=new int[numofsums];
    probability=new float[numofsums];

    for(int i=0; i<numofsums; i++)
    {
        sums[i]=0;
        probability[i]=0;
    }

    int carry=0;
    //наприклад кубики такі: { 3 4 5} та {2 3 4}
    // min=3+2  max=5+4   тобто суми від 5 до 9
    // в масиві М зараз мінімальеа конфігурація 32
    // в циклі додаємо по 1
    // хм...якщо на гранях к-ть сум росте не рівномірно((
    // додавати слід не 1(( і carry теж не завжди 1!!!!!
    //отже поки на гранях суми лиш з кроком 1!!, від а до в
    // m +1
    //щоб на гранях був крок не строго +1 а довільний
    // перевіряти чи реальна конфіг гранй в масиві М
    //  !!!! ВАУ в масив писати не грані а індекси!!!! граней
    // і тепер суми на гранях можут бути навіть FLOAT
    //----тепер в М індекси
    do
    {
        int s=0;
        float f=1;
        {
            for(int i=0; i<numcubes; i++)
            {
                s+=dices[i].CostBySide(m[i]);  //сума ряду
                f*=dices[i].ProbBySide(m[i]);  //ймовірність
            }
            sums[s-min]++;     //к-ть сум
            probability[s-min]+=f; // ймов сум
        }

        if(show>1)
        {
            std::cout<<"\n";
            for(int i=0; i<numcubes; i++)
            {
                std::cout<<dices[i].CostBySide(m[i])<<" ";
            }
            std::cout<<"\t = "<<s;
        }

        m[numcubes-1]++;//збільшити останн індекс
        carry=0;
        for(int i=numcubes-1; i>=0; i--)//по розрядах
        {
            m[i]+=carry;
            carry=0;
            if(m[i]>dices[i].sides()-1)
            {
                m[i]=0;
                carry=1;
            }
        }

        // bool finish=true;
        // for(int i=0; i<k; i++)
        // {
        //   if(m[i]!=1)
        //   {
        //     finish=false;break;
        //   }
        // }
    }while(!carry);

    if(show>0)
    {
        std::cout<<"\nSUMS: \n";
        for(int i=min; i<=max; i++)
            std::cout<<i<<"\t";
        std::cout<<"\n";

        for(int i=0; i<numofsums; i++)
        {
            std::cout<<sums[i]<<"\t";
        }
        float tt=0;
        std::cout<<"\n";
        std::cout<< std::fixed << std::setprecision(3);
        for(int i=0; i<numofsums; i++)
        {
            //tt+=probability[i];
            std::cout<<probability[i]<<"\t";
        }

        //std::cout<<"\n"<<tt;///якщо сума 1 - ОК!!!
    }

    expect=0;
    for (int i = 0; i < numofsums; i++) {
        expect += sums[i] * probability[i];
    }

    delete[] m;
}