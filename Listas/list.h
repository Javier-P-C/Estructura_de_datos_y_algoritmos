#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <sstream>
#include "exception.h"

template <T> class List;
template <T> class ListIterator;

//La clase Link son los elementos que se van a guardar en la lista. Cada objeto se une a otro por medio de un apuntador
template <T>
class Link
{
  private:
    Link(T);
    Link(T,Link<T>*);
    Link(const &Link);
    
    T value;
    Link* next;

    //Indica cuales clases pueden tener acceso a los atributos y métodos privados de Link
    friend class List<T>;
    friend class ListIterator<T>;
};

template <T> class Link<T>::Link(T val): value(T),next(0) {}
template <T> class Link<T>::Link(T val, Link* nxt): value(val), next(nxt) {}
template <T> class Link<T>::Link(const Link &source):value(source.value),next(source.next) {}

//List es la lista pero solo tiene un apuntador al primer elemento y accede al resto de los elementos por medio de sus apuntadores
template <T>
class List
{
  private:
    Link* head;
    int size;

  public:
    List(Link<T>*);
    List(const List<T>&);
    ~List();

    
};

