#include <iostream>
template <typename T>
struct Node
{
    T data;
};

template <typename T>
class List
{
    Node<T>* arr=nullptr;
    int size; // реальн розм
    int cap;  //місткість-фіз розмір
public:
    bool isEmpty();
    void Resize();
    List();
    ~List();
    // Конструктор копіювання
    List(const List& other);
    List& operator=(const List& other);
    void addtostart(T data);
    void addtoend(T data);
    void print();
    void addafter(Node<T>* after, T data);
    Node<T>* byindex(int i);
    void addbefore(Node<T>* before, T data);
    void del(Node<T>* el);
    Node<T>* getmin();
    void insertinsorted(T data);
    int getSize();
    void info(){std::cout<<"\narray\n";}
/*
void insertion_sort(); */
//split()
//merge(l1, l2)    
};

template <typename T>
bool List<T>::isEmpty(){return size==0;}

template <typename T>
int List<T>::getSize(){return size;}


template <typename T>
void List<T>::Resize()
{//збільш фіз розмфру
    cap+=50;
    Node<T>* newarr=new Node<T>[cap];
    for(int i=0; i<size; i++)
        newarr[i]=arr[i];
    delete[] arr;
    arr=newarr;
}
// List(int n)
// {
//   arr=new Node<T>[n];
//   cap=n;
//   size=0;
// }
template <typename T>
List<T>::List()
{
    arr=new Node<T>[50];
    cap=50;
    size=0;
}

template <typename T>
List<T>::~List()
{
    delete[] arr;
}
// Конструктор копіювання
template <typename T>
List<T>::List(const List& other)
{
    cap = other.cap;
    size = other.size;

    arr = new Node<T>[cap];

    for (int i = 0; i < size; i++)
    {
        arr[i] = other.arr[i];
    }
}

template <typename T>
List<T>&  List<T>::operator=(const List& other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] arr;

    cap = other.cap;
    size = other.size;

    arr = new Node<T>[cap];

    for (int i = 0; i < size; i++)
    {
        arr[i] = other.arr[i];
    }

    return *this;
}

template <typename T>
void  List<T>::addtostart(T data)
{
    if(size==cap)
        Resize();
    size++;
    for(int i=size-1; i>=0; i--)
        arr[i]=arr[i-1]; //Переміщення масиву вправо, для звільнення місця для першого елементу
    arr[0].data=data;
}

template <typename T>
void  List<T>::addtoend(T data)
{
    if(size==cap)
        Resize();
    size++;
    arr[size-1].data=data;
}

template <typename T>
void  List<T>::print()
{
    for(int i=0; i<size; i++)
        std::cout<<arr[i].data<<", ";
}

template <typename T>
void  List<T>::addafter(Node<T>* after, T data)
{
    int k=after-arr;
    if(k<0||k>=size)
    {
        std::cout<<"\nERRORafter\n";
        return;
    }
    if(size==cap)
        Resize();
    int i;
    for(i=size; i>k+1;i--)
        arr[i]=arr[i-1];
    arr[i].data=data;

    size++;


}

template <typename T>
Node<T>*  List<T>::byindex(int i)
{
    if(i>=0&&i<size)
        return &arr[i];
    else return nullptr;
}

template <typename T>
void  List<T>::addbefore(Node<T>* before, T data)
{
    if(before==nullptr)
        return;
    if(size==cap)
        Resize();
    size++;
    Node<T>*p;
    for(p=arr+size-1; p>before; p--)///+1прибрати буде before
        p->data=p[-1].data;
    p->data=data;
}


template <typename T>
void  List<T>::del(Node<T>* el)
{
    if(el)
    {
        Node<T>*p=arr;
        while(p<el)
            p++;
        while(p<arr+size)
        {
            p[0].data=p[1].data;
            p++;
        }
        size--;
    }
}

template <typename T>
Node<T>*  List<T>::getmin()
{
    Node<T>*mn=nullptr;
    if(size>0)
    {
        mn=&arr[0];
        for(int i=1; i<size; i++)
            if(arr[i].data < mn->data)
                mn=&arr[i];
    }
    return mn;
}


template <typename T>
void  List<T>::insertinsorted(T data)
{
    for(int i=0; i<size; i++)
    {
        if(data < arr[i].data)
        {
            addbefore(&arr[i], data);
            return;
        }
    }
    addtoend(data);
}





/* Функція для сортування списку за допомогою quicksort
template <typename T>
void quicksort(List<T>& a, Node<T>* low, Node<T>* high)
{
    if (low && high && low != high && low != high+1)
    {
        Node<T>* pivot = partition(a, low, high);
        quicksort(a, low, pivot);
        quicksort(a, pivot+1, high);
    }
}

template <typename T>
void quicksort(List<T>& a)
{
    quicksort(a, a.byindex(0), a.byindex(a.getSize() - 1));
}*/

