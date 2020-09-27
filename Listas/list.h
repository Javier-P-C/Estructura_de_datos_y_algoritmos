#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <sstream>
#include "exception.h"

template <class T> class List;
template <class T> class ListIterator;

//La clase Link son los elementos que se van a guardar en la lista. Cada objeto se une a otro por medio de un apuntador
template <class T>
class Link
{
  private:
    Link(T);
    Link(T,Link<T>*);
    Link(const Link<T>&);
    
    T value;
    Link* next;

    //Indica cuales clases pueden tener acceso a los atributos y métodos privados de Link
    friend class List<T>;
    friend class ListIterator<T>;
};

//Cuando recibe solo el valor
template <class T> 
Link<T>::Link(T val): value(val),next(0) {}
//Cuando recibe el valor y el siguiente elemento de la Lista
template <class T> 
Link<T>::Link(T val, Link* nxt): value(val), next(nxt) {}
//Para copiar un elemento
template <class T> 
Link<T>::Link(const Link &source):value(source.value),next(source.next) {}



//List es la lista pero solo tiene un apuntador al primer elemento y accede al resto de los elementos por medio de sus apuntadores
template <class T>
class List
{
  private:
    Link<T>* head;
    int size;

    friend class ListIterator<T>;

  public:
    List();
    List(const List<T>&) throw (OutOfMemory);
    ~List();

    void addFirst(T) throw (OutOfMemory);
    void add(T) throw (OutOfMemory);
    T    getFirst() const throw (NoSuchElement);
    T    removeFirst() throw (NoSuchElement);
    void clear();
    bool empty() const;
  	int  length() const;
    T    get(int) const throw (IndexOutOfBounds, NoSuchElement);
    bool contains(T) const;
    //std::string toString() const;
	  //void operator= (const List&) throw (OutOfMemory);
};

//Cuando se crea la lista sin nada
template <class T> 
List<T>::List():head(0),size(0){}

//Cuando se quiere hacer una copia de otra lista
template <class T> 
List<T>::List(const List<T> &source) throw (OutOfMemory)
{
  Link<T> *p,*q; //p se encargará de apuntar a source y q a los elementos de la nueva lista

  if (source.empty())
  {
    size=0;
    head=0;
  }
  else
  {
    p=source.head; //Está apuntando al head de la lista source
    head = new Link<T>(p->head); //Le envía el head de la lista source para crear un nuevo objeto
    if(head==0)
    {
      throw OutOfMemory();
    }

    q=head; //Se apunta al nuevo objeto
    p = p->next; //Se pasa al siguiente elemento de la lista

    p=source.head;
    q=p->next;
    while(p!=0)
    {
      q->next = new Link<T> (p->value);
      if (q->next == 0)
      {
        throw OutOfMemory();
      }

      p=p->next;
      q=q->next;
    }
    size = source.size;
  }

  size = source.size;
}

//Borra la Lista
template <class T>
List<T>::~List()
{
  clear();
}

//Recibe el valor para un nuevo Link y lo vuelve el primero de la lista
template <class T> 
void List<T>::addFirst(T val) throw (OutOfMemory)
{
  Link<T> *newLink;
  newLink = new Link<T>(val);
  if (newLink==0)
  {
    throw OutOfMemory();
  }

  newLink->next = head;
  head=newLink;

  size++;
}

//Aañade un elemento al final de la lista
template <class T>
void List<T>::add(T val) throw (OutOfMemory) 
{
	Link<T> *newLink, *p;

	newLink = new Link<T>(val);
	if (newLink == 0) 
  {
		throw OutOfMemory();
  }

  if (empty()) {
		addFirst(val);
		return;
	}

	p = head;
	while (p->next != 0) {
		p = p->next;
	}
	newLink->next = 0;
	p->next = newLink;

	size++;
}

//Devuelve el valor del primer elemento en la lista
template <class T>
T List<T>::getFirst() const throw (NoSuchElement) 
{
	if (empty()) 
  {
		throw NoSuchElement();
	}
	return head->value;
}

//Remueve el primer elemento de la lista
template <class T>
T List<T>::removeFirst() throw (NoSuchElement) 
{
  Link<T> *p;
	T val;

	if (empty()) 
  {
		throw NoSuchElement();
	}

	p = head;

	head = p->next;
	val = p->value;
	delete p;
	size--;

	return val;
}

//Comprueba que haya elementos en la lista
template <class T>
bool List<T>::empty() const 
{
	return (head == 0);
}

//Elimina todos los objetos Link de la lista
template <class T>
void List<T>::clear() 
{
	Link<T> *p, *q;

	p = head;
	while (p != 0) 
  {
		q = p->next;
		delete p;
		p = q;
	}

	head = 0;
	size = 0;
}

//Devuelve el número de elementos de la listatemplate <class T>
template <class T>
int List<T>::length() const 
{
	return size;
}

//Devuelve el valor contenido en el índice recibido
template <class T>
T List<T>::get(int index) const throw (IndexOutOfBounds, NoSuchElement) 
{
	int pos;
	Link<T> *p;

	if (index < 0 || index >= size) 
  {
		throw IndexOutOfBounds();
	}

	if (index == 0) 
  {
		return getFirst();
	}

	p = head;
	pos = 0;
	while (pos != index) 
  {
		p = p->next;
		pos++;
	}

	return p->value;
}

//Comprueba que exita el valor en la lista
template <class T>
bool List<T>::contains(T val) const 
{
	Link<T> *p;

	p = head;
	while (p != 0) 
  {
		if (p->value == val) 
    {
			return true;
		}
		p = p->next;
	}
	return false;
}

#endif
