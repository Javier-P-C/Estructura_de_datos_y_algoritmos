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
    DLink(T);
    DLink(T,DLink<T>*,DLink<T>*);
    DLink(const DLink<T>&);

    T value;
    DLink<T> *next, *previous;

    friend class DList<T>;
    friend class DListIterator<T>;
};

template <class T>
DLink<T>::DLink(T val):value(val),next(0),previous(0) {}

template <class T>
DLink<T>::DLink(T val,DLink<T> *_next,DLink<T> *_previous):value(val),next(_next),previous(_previous) {}

template <class T>
DLink<T>::DLink(const DLink<T> &source):value(source.value),next(source.next),previous(source.previous) {}

template <class T>
class DList
{
  private:
    int size;
    DLink<T> *head, *tail;
    
    friend class DListIterator<T>;

  public:
    DList();
    DList(const DList<T>&) throw (OutOfMemory);
    ~DList();

    void addFirst(T) throw (OutOfMemory);
    void add(T) throw (OutOfMemory);
    T    getFirst() const throw (NoSuchElement);
    T    removeFirst() throw (NoSuchElement);
    T	 getLast() const throw (NoSuchElement);
    T    removeLast() throw (NoSuchElement);
    int  length() const;
    T    get(int) const throw (IndexOutOfBounds);
    bool contains(T) const;
    bool empty() const;
    void clear();
    std::string toString() const;

    void addBefore(DListIterator<T>&, T) throw (IllegalAction, OutOfMemory);
    void addAfter(DListIterator<T>&, T) throw (IllegalAction, OutOfMemory);
    T    removeCurrent(DListIterator<T>&) throw (IllegalAction);

    bool set(int, T) throw (IndexOutOfBounds);
    int  indexOf(T) const;
    int  lastIndexOf(T) const;
    T    remove(int) throw (IndexOutOfBounds);
    bool removeFirstOcurrence(T);
    bool removeLastOcurrence(T);
};

template <class T>
DList<T>::DList():size(0),head(0),tail(0) {}

template <class T>
DList<T>::DList(const DList<T> &source) throw (OutOfMemory):size(source.size)
{
  DLink<T> *p,*q;

  if (source.empty()) 
  {
		size = 0;
		head = 0;
		tail = 0;
	} 
  else 
  {
    head = new DLink<T>(source.head);
    if (head == 0) 
    {
			throw OutOfMemory();
		}
    p = head;
    q = source.head;
    
    while(q == 0)
    {
      p->next = new DLink<T>(q->next);
      p->next->previous = p;
      p = p->next;
      q = q->next;
    }
  }
}

template <class T>
DList<T>::~DList()
{
  clear();
}

template <class T>
void DList<T>::addFirst(T val) throw (OutOfMemory)
{
  DLink<T> *newLink;
  newLink = new DLink<T>(val);
  if(newLink == 0)
  {
    throw OutOfMemory();
  }
  else
  {
    if(size == 0)
    {
      head = newLink;
      tail = newLink;
    }
    else
    {
      head->previous = newLink;
      newLink->next = head;
      head = newLink;
    }
  }
  size++;
}

template <class T>
void DList<T>::add(T val) throw (OutOfMemory)
{
  DLink<T> *newLink = new DLink<T>(val);
  if(newLink == 0)
  {
    throw OutOfMemory();
  }
  else
  {
    tail->next = newLink;
    newLink->previous = tail;
    tail = newLink;
  }
  size++;
}

template <class T>
void DList<T>::clear()
{
  DLink<T> *p,*q;
  if(size == 0)
  {
  }
  else
  {
    p = head->next;
  
    while(p->next!=0)
    {
      delete p->previous;
      p = p->next;
    }
    delete p;
  }
  size = 0;
  head = 0;
  tail = 0;
}

template <class T>
bool DList<T>::empty() const
{
  return (size == 0);
}

template <class T>
T DList<T>::getFirst() const throw (NoSuchElement)
{
  return head->value;
}

template <class T>
T DList<T>::removeFirst() throw (NoSuchElement)
{
  T val;
  if(empty())
  {
    throw NoSuchElement();
  }
  else
  {
    val = head->value;
    if(head == tail)
    {
      delete head;
      head = 0;
      tail = 0;
    }
    else
    {
      head = head->next;
      delete head->previous;
      head->previous = 0;
    }
  }
  size--;
  return val;
}

template <class T>
T	 DList<T>::getLast() const throw (NoSuchElement)
{
  return tail->value;
}

template <class T>
T DList<T>::removeLast() throw (NoSuchElement)
{
  T val;
  if (empty())
  {
    throw NoSuchElement();
  }
  else
  {
    val = tail->value;
    if(head == tail)
    {
      delete tail;
      head = 0;
      tail = 0;
    }
    else
    {
      tail = tail->previous;
      delete tail->next;
      tail->next = 0;
    }
  }
  size--;
  return val;
}

template <class T>
int  DList<T>::length() const
{
  return size;
}

template <class T>
T DList<T>::get(int index) const throw (IndexOutOfBounds)
{
  T val;
  DLink<T> *p;
  p = head;

  if((index >= size)||(index < 0))
  {
    throw IndexOutOfBounds();
  }
  for(int i=0;i<size;i++)
  {
    if(i == index)
    {
      val = p->value;
      break;
    }
    p = p->next;
  }
  return val;
}

template <class T>
bool DList<T>::contains(T val) const
{
  DLink<T> *p;
  p = head;
  while(p!=0)
  {
    if(p->value == val)
    {
      return true;
    }
    p = p->next;
  }
  return false;
}

template <class T>
std::string DList<T>::toString() const
{
  std::stringstream aux;

  DLink<T> *p;
  p = head;

  aux<<"[";
  while (p != 0)
  {
    aux<<p->value;
    if(p->next != 0)
    {
      aux<<",";
    }
    p = p->next;
  }
  aux<<"]";
  return aux.str();
}

template <class T>
bool DList<T>::set(int index, T val) throw (IndexOutOfBounds)
{
  DLink<T> *p;
  p = head;

  if((index < 0)||(index >= size))
  {
    throw IndexOutOfBounds();
  }
  else
  {
    for(int i=0;i<=size;i++)
    {
      if(i == index)
      {
        p->value = val;
        break;
      }
      p = p->next;
    }
  }
  return true;
}

template <class T>
int DList<T>::indexOf(T val) const
{
  DLink<T> *p;
  p = head;

  for(int i=0;i<size;i++)
  {
    if(p->value == val)
    {
      return i;
    }
  }

  return -1;
}

template <class T>
int DList<T>::lastIndexOf(T val) const
{
  DLink<T> *p;
  p = head;
  int index = -1;

  for(int i=0;i<size;i++)
  {
    if(p->value == val)
    {
      index = i;
    }
  }

  return index;
}

template <class T>
T DList<T>::remove(int index) throw (IndexOutOfBounds)
{
  T val;
  DLink<T> *p;
  p = head;

  if((index < 0)||(index >= size))
  {
    throw IndexOutOfBounds();
  }

  if(index == 0)
  {
    return removeFirst();
  }
  else
  {
    for(int i=0;i<size;i++)
    {
      if(index == i)
      {
        val = p->value;
        p->previous->next = p->next;
        p->next->previous = p->previous;
        delete p;
      }
    }
  }
  size--;
  return val;
}

template <class T>
bool DList<T>::removeFirstOcurrence(T val)
{
  DLink<T> *p;
  p = head;

  while (p!=0)
  {
    if(p->value == val)
    {
      p->previous->next = p->next;
      p->next->previous = p->previous;
      size--;
      return true;
    }
    p = p->next;
  }
  return false;
}

template <class T>
bool DList<T>::removeLastOcurrence(T val)
{
  DLink<T> *p,*ocurrence;
  p = head;
  ocurrence = 0;

  while (p!=0)
  {
    if(p->value == val)
    {
      ocurrence = p;
    }
    p = p->next;
  }
  if(ocurrence == 0)
  {
    return false;
  }
  return true;
}

#endif /* DLIST_H_ */
