#include <iostream>
#include <math.h>
#include "list_lst.cpp"
#include <Windows.h>

/*(**) Список. Реалізації на основі зв’язних списків, масивів, бібліотечних засобів.
  Алгоритми сортування: insertion sort, quicksort, merge sort.*/

template <typename T>
void inserting_sort(List<T>& a)
{
    List<T> sorted;
    Node<T>*p;

    while(!a.isEmpty())
    {
        p=a.getmin();
        sorted.insertinsorted(p->data);
        a.del(p);
    }
    a=sorted;
}
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    List<int> t;
    t.info();
    int nn=155;
    t.addtostart(11);

    for(int i=1; i<nn; i++)
    {
        switch(rand()%3)
        {
            case 0: t.addtostart(rand()%200);break;
            case 1: t.addtoend(rand()%200); break;
            case 2: t.addafter(t.byindex(rand()%(t.getSize())), rand()%300);break;
        }
    }
    std::cout<<"\nстворюємо масив(додавання на початок, в кінець, після певного елементу)'\n";
    std::cout<<"\nМасив на "<<nn<< " елементів\n";
    t.print(); std::cout<<"\n";
    std::cout<<"\nСортуємо....";
    inserting_sort(t);
    t.print(); std::cout<<"\n";

    nn+=50000;
    for(int i=1; i<nn; i++)
    {
        switch(rand()%3)
        {
            case 0: t.addtostart(rand()%200);break;
            case 1: t.addtoend(rand()%200); break;
            case 2: t.addafter(t.byindex(rand()%(t.getSize())), rand()%300);break;
        }
    }
    std::cout<<"\nдоповнюємо масив(додавання на початок, в кінець, після певного елементу)'\n";
    std::cout<<"\nМасив до "<<nn<< " елементів\n";

    std::cout<<"\nСортуємо....";
    inserting_sort(t);
    std::cout<<"\nОК";

}





