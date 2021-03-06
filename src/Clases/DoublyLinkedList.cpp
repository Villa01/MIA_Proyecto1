#include "DoublyLInkedList.h"

template <typename T>
void double_linked<T>::push_back(T data)
{
    tail = new node(data, tail, NULL);
    if( tail->prev )
        tail->prev->next = tail;

    if( empty() )
        head = tail;
}

template <typename T>
void double_linked<T>::push_front(T data)
{
    head = new node(data, NULL, head);
    if( head->next )
        head->next->prev = head;

    if( empty() )
        tail = head;
}

template<typename T>T double_linked<T>::pop_back()
{
    if( empty() )
        throw("La lista está vacía.");
    node* temp(tail);
    T data( tail->data );
    tail = tail->prev ;

    if( tail )
        tail->next = NULL;
    else
        head = NULL ;

    delete temp;
    return data;
}

template<typename T>T double_linked<T>::pop_front()
{
    if( empty() )
        throw("double_linked : list empty");
    node* temp(head);
    T data( head->data );
    head = head->next ;

    if( head )
        head->prev = NULL;
    else
        tail = NULL;

    delete temp;
    return data;
}