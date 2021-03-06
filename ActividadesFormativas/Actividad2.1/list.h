#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>
#include <string>
#include <sstream>

template <class T> class List;

template <class T>
class Link
{
  private:
    Link(T);
    Link(T,Link<T>*);
    Link(const Link<T>&);
    //~Link();

    Link<T> *next;
    T value;

    friend class List<T>;
};

//Cuando recibe solo el valor
template <class T> 
Link<T>::Link(T val):value(val),next(0) {}
//Cuando recibe el valor y el siguiente elemento de la Lista
template <class T> 
Link<T>::Link(T val,Link<T> *_next):value(val),next(_next) {}
//Para copiar un elemento
template <class T> 
Link<T>::Link(const Link<T> &source):value(source.value),next(source.next) {}


template <class T>
class List
{
  private:
    Link<T> *head;
    int size;

  public:
    List();
    List(const List<T>&);
    ~List();

    void clear();
    void add(T);
    int find(T);
    void update(int,T);
    T remove(int);
    T removeFirst();

    std::string toString() const; 
};

//Cuando se crea la lista sin nada
template <class T>
List<T>::List()
{
  head = 0;
  size = 0;
}

//Cuando se quiere hacer una copia de otra lista
template <class T>
List<T>::List(const List<T> &source):size(source.size)
{
  Link<T> *p,*q;

  head = new Link<T>(source.head);
  p = head;
  q = source.head;

  while(p != 0)
  {
    p->next = new Link<T>(q->next);
    p = p->next;
    q = q->next;
  }
}

//Borra la Lista
template <class T>
List<T>::~List()
{
  clear();
}

//Libera el espacio en memoria
template <class T>
void List<T>::clear()
{
  Link<T> *p,*q;
  p = head;
  q = 0;

  while(p != 0)
  {
    q = p->next;
    delete p;
    p = q;
  }

  size = 0;
  head = 0;
}

//Añade un elemento al final de la lista
template <class T>
void List<T>::add(T val)
{
  Link<T> *newLink,*p;
  newLink = new Link<T>(val);
  p = head;
  
  if(size==0)
  {
    head = newLink;
    size++;
    return;
  }

  while(p->next != 0)
  {
    p = p->next;
  }
  newLink->next=0;
  p->next = newLink;

  size++;
}

//Devuelve el índice donde se encuentra el valor recibido
template <class T>
int List<T>::find(T val)
{
  Link<T> *p,*q;
  p = head;

  for(int i=0;i<size;i++)
  {
    if(p->value == val)
    {
      return i;
    }
    p = p->next;
  }

  return -1;
}

//Cambia el valor de un índice
template <class T>
void List<T>::update(int index,T val)
{
  Link<T> *p;
  p = head;
  
  for(int i=0;i<size;i++)
  {
    if(i == index)
    {
      p->value = val;
      break;
    }
    p = p->next;
  }
}

//Borra el elemento del índice
template <class T>
T List<T>::remove(int index)
{
  T val;
  Link<T> *p,*q;
  p = head;
  q = 0;

  if(index == 0)
  {
    return removeFirst();
  }
  else
  {
    for (int i=0;i<size;i++)
    {
      if(i==index)
      {
        q->next = p->next;
        val = p->value;
        delete p;
        break;
      }
      q = p;
      p = p->next;
    }
  }
  size--;

  return val;
}

//Remueve el primer elemento de la lista
template <class T>
T List<T>::removeFirst()
{
  T val;
  Link<T> *p;

  val = head->value;

  p = head->next;
  delete head;
  head = p;

  size--;

  return val;
}


template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;
	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

#endif