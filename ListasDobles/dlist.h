#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>
#include "exception.h"

template <class T> class DList;
template <class T> class DListIterator;

template <class T>
class DLink 
{
  private:
    Dlink(T);
    Dlink(T,Dlink<T>*,Dlink<T>*);
    Dlink(const Dlink<T>&);

    T value;
    Dlink<T> *next, *previous;

    friend class DList<T>;
    friend class DListIterator<T>;
};

Dlink<T>::Dlink(T val):value(val),next(0),previous(0) {}
Dlink<T>::Dlink(T val,Dlink<T> *_next,Dlink<T> *_previous):value(val),next(_next),previous(_previous) {}
Dlink<T>::Dlink(const Dlink<T> &source):value(source.value),next(source.next),previous(source.previous) {}

template <class T>
class DList
{
  private:
    int size;
    Dlink<T> *head, *tail;
    
    friend class DListIterator<T>;

  public:
    DList();
    DList(const DList<T>&) throw (OutOfMemory);
    ~DList();

    void addFirst(T) throw (OutOfMemory);
    void add(T) throw (OutOfMemory);

    T removeFirst() throw (NoSuchElement);

    int indexOf(T) const;
    bool set(int,T) throw (OutOfBounds);
    T remove(int) throw (OutOfBounds);
};

DList<T>::DList():size(0),head(0),tail(0) {}

DList<T>::DList(const DList<T> &source):size(source.size)
{

}

DList<T>::~DList()
{
  DList<T>
  size = 0;

}

#endif /* DLIST_H_ */
