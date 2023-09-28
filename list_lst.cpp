#include <iostream> // на базі списків
template <typename T>
struct Node
{
    T data;
    Node* prev=nullptr;
    Node* next=nullptr;
};

template <typename T>
class List //двобічно зв'язаний список
{
    Node<T>* head=nullptr;
    Node<T>* tail=nullptr;
public:
    List();
    ~List();
    bool isEmpty();
    int getSize();
    void addtostart(T data);//додає новий елемент з даними data на початок списку.
    void addtoend(T data);
    void print();
    void addafter(Node<T>* after, T data);//додає новий елемент з даними data після вказаного вузла after
    void addbefore(Node<T>* before, T data);
    void del(Node<T>* el);
    Node<T>* byindex(int i);
    Node<T>* getmin();
    List(const List<T>& other); //конструктор копіювання, який створює копію іншого списку.
    List<T>& operator=(const List<T>& other);
    void insertinsorted(T data);
    void info(){std::cout<<"\nlist\n";}
};

template <typename T>
int List<T>::getSize()
{
    int sz=0;
    Node<T>* p=head;
    while(p!=nullptr)
    {
        sz++;
        p=p->next;
    }
    return sz;
}


template <typename T>
bool List<T>::isEmpty(){return head==nullptr;}

template <typename T>
List<T>::List(const List<T>& other)
{
    head = nullptr;
    tail = nullptr;

    Node<T>* current = other.head;

    while (current != nullptr)
    {
        addtoend(current->data);
        current = current->next;
    }
}


template <typename T>
List<T>& List<T>::operator=(const List<T>& other)
{
    if (this == &other)
        return *this;

    while (head != nullptr)
    {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }

    Node<T>* current = other.head;

    while (current != nullptr)
    {
        addtoend(current->data);
        current = current->next;
    }

    return *this;
}






template <typename T>List<T>::List(){}

template <typename T>List<T>::~List()
{
    Node<T>* todel, *p;

    while(p!=nullptr)
    {
        todel=head;
        head=head->next;
        delete todel;
    }
    tail=nullptr;
}

template <typename T>void List<T>::addtostart(T data)
{
    Node<T>* newnode= new Node<T>;
    newnode->data=data;
    newnode->next=head;
    newnode->prev=nullptr;
    if(head!=nullptr)
    {
        head->prev=newnode;
    }
    else
    {
        tail=newnode;
    }
    head=newnode;
}

template <typename T>  void List<T>::addtoend(T data)
{
    Node<T>* newnode= new Node<T>;
    newnode->data=data;
    newnode->next=nullptr;
    newnode->prev=tail;
    if(tail!=nullptr)
    {
        tail->next=newnode;
    }
    else
    {
        head=newnode;
    }
    tail=newnode;
}

template <typename T>void List<T>::print()
{
    Node<T>* p=head;
    while(p!=nullptr)
    {
        std::cout<<p->data<<" , ";
        p=p->next;
    }
}
template <typename T>  void List<T>::addafter(Node<T>* after, T data)
{
    if(after==tail)
        addtoend(data);
    else
    {
        Node<T>* newnode= new Node<T>;
        newnode->next=after->next;
        newnode->prev=after;
        after->next=newnode;
        newnode->next->prev=newnode;
    }
}

template <typename T>void List<T>::addbefore(Node<T>* before, T data)
{
    if(before==head)
        addtostart(data);
    else
    {
        Node<T>* newnode= new Node<T>;
        newnode->data=data;
        newnode->next=before;
        newnode->prev=before->prev;
        before->prev=newnode;
        newnode->prev->next=newnode;
    }
}

template <typename T>  void List<T>::del(Node<T>* el)
{
    if(el==nullptr)
        return;
    if(el==head)
    {
        head=el->next;
        if(head)
            head->prev=nullptr;
        else
            tail=nullptr;
    }
    else
    if(el==tail)
    {
        tail=el->prev;
        tail->next=nullptr;
    }
    else
    {
        el->prev->next=el->next;
        el->next->prev=el->prev;
    }
    delete el;
}

template <typename T>  Node<T>* List<T>::byindex(int i)
{
    Node<T>* p=head;
    while(p!=nullptr && i)
    {
        i--;
        p=p->next;
    }
    return p;
}

template <typename T>void List<T>::insertinsorted(T data)
{ //вставка у відпов позицию
    Node<T>* p=head; // початок з голови

    while(p!=nullptr && data > p->data)
        p=p->next;
    if(p==nullptr)
    {
        addtoend(data);
        return;
    }
    addbefore(p, data);
}

template <typename T>Node<T>* List<T>::getmin()
{
    Node<T>* p=head, *min;
    if(p==nullptr)
        return p;

    min=p;
    while(p!=nullptr)
    {
        if(p->data < min->data)
            min=p;
        p=p->next;
    }
    return min;
}
/*
void insertion_sort()
{
//це метод, його потрібно переробити в окрему ф-цію

  if(head==nullptr || head->next==nullptr)
    return;

  List<int> sortd;

  Node<T> *p;
  T min;

  while(head!=nullptr)
  {
    p=getmin();
    sortd.insertinsorted(p->data);
    del(p);
  }

  //sortd.print();
  do
  {
    p=sortd.byindex(0);
    if(p==nullptr)
      break;
    addtoend(p->data);
    sortd.del(p);
  }while(1);

}
*/
