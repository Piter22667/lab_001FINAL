
#include <iostream>
#include "dice.h"
#include "nabir.h"

using namespace std;

int main()
{
    std::cout<<"\nDICE & NABIR class demo\n";
    Dice d;
    d.Init(3,8);
    d.print();
    for(int i=1; i<20; i++)
        std::cout<<d.Throw()<<" ";

    Nabir n1;
    n1.Add(d);
    n1.print();
    d.Init(5,8);
    n1.Add(d);
    n1.print();

    d.Init(-5,5);
    n1.Add(d);
    n1.print();

    d.Init(10,30,3);
    n1.Add(d);
    n1.print();


}
