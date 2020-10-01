#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>

template <class T> class DList;

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

  public:
    DList();
    ~DList();

    void addFirst(T);
    void add(T);
    void removeFirst();
    int find(T) const;
    void update(int,T);
    void remove(int);
    std::string toStringForward() const;
    std::string toStringBackward() const;
};

template <class T>
DList<T>::DList():size(0),head(0),tail(0) {}

template <class T>
DList<T>::~DList()
{
  DLink<T> *p;
  p=head;

  while(p->next!=0)
  {
    p = p->next;
    delete p->previous;
  }
  delete p;

  head = 0;
  tail = 0;
  size = 0;
}

template <class T>
void DList<T>::addFirst(T val)
{
  head = new DLink<T>(val);

  size++;
}

template <class T>
void DList<T>::add(T val)
{
  if (size == 0)
  {
    addFirst(val);
    tail = head;
    return;
  }
  else
  {
    tail->next = new DLink<T>(val);
    tail->next->previous = tail;
    tail = tail->next;
  }

  size++;
}

template <class T>
void DList<T>::removeFirst()
{
  DLink<T> *p;
  p = head;
  p->next->previous = 0;
  head = p->next;
  delete p;
  size--;
}

template <class T>
void DList<T>::remove(int index)
{
  DLink<T> *p,*q;
  p=head;
  q=0;

  if(index == 0)
  {
    removeFirst();
    return;
  }
  else
  {
    for(int i=0;i<size;i++)
    {
      if(index==i)
      {
        if(p->next!=0)
        {
          p->previous->next = p->next;
          p->next->previous = p->previous;
        }
        else
        {
          p->previous->next = 0;
        }
        break;
      }
      p = p->next;
    }
  }
  delete p;

  size--;
}

template <class T>
int DList<T>::find(T val) const
{
  DLink<T> *p;
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

template <class T>
void DList<T>::update(int index,T val)
{
  DLink<T> *p;
  p = head;

  for(int i=0;i<size;i++)
  {
    if(index==i)
    {
      p->value = val;
      break;
    }
    p = p->next;
  }
}

template <class T>
	std::string DList<T>::toStringForward() const {
		std::stringstream aux;
		DLink<T> *p;
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
	template <class T>
	std::string DList<T>::toStringBackward() const {
		std::stringstream aux;
		DLink<T> *p;
		p = tail;
		aux << "[";
		while (p != 0) {
			aux << p->value;
			if (p->previous != 0) {
				aux << ", ";
			}
			p = p->previous;
		}
		aux << "]";
		return aux.str();
	}

#endif /* DLIST_H_ */