#ifndef HEAP_H_
#define HEAP_H_

template <class T>
class Heap {
private:
	T *data;
	unsigned int size_;
	unsigned int count;
	
	unsigned int parent(unsigned int) const;
	unsigned int left(unsigned int) const;
	unsigned int right(unsigned int) const;
	void heapify(unsigned int);
	void swap(unsigned int, unsigned int);
	
public:
	Heap(unsigned int);
	~Heap();
  
  void push(T);
	void pop();
  T top();
  int size();

	bool empty() const;
	bool full() const;
	void clear();
	std::string toString() const;
};

//Constructor
template <class T>
Heap<T>::Heap(unsigned int sze)
{
  size_ = sze;
  data = new T [size_];
  count = 0;
}

//Destructor
template <class T>
Heap<T>::~Heap() {
  clear();
 }

//Checa si hay elementos en el heap
template <class T>
bool Heap<T>::empty() const {
  return (count == 0);
}

//Checa si está lleno el heap
template <class T>
bool Heap<T>::full() const {
	return (count == size_);
}

//Devuelve la poscición donde debe estar el padre
template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
	return ((pos-1)/2);
}

//Devuelve la posición donde debe ir el hijo izquierdo
template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
	return (pos*2+1);
}

//Devuelve el elemento donde debe ir el hijo derecho
template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
	return (pos*2+2);
}

//Cambia de posición dos elementos del heap
template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
	T aux = data[i];
	data[i] = data[j];
	data[j] = aux;
}

//Arregla inconsistencias del árbol
template <class T>
void Heap<T>::heapify(unsigned int pos) {
  unsigned int le = left(pos);
	unsigned int ri = right(pos);
	unsigned int min = pos;
	if (le < count && data[le] < data[min]) {
		min = le;
	}
	if (ri < count && data[ri] < data[min]) {
		min = ri;
	}
	if (min != pos) {
		swap(pos, min);
		heapify(min);
	}
}

//Añade un elemento al heap
template <class T>
void Heap<T>::push(T val)
{
  int pos = count;
  data[count++] = val;
  while(pos>0 && val<data[parent(pos)])
  {
    swap(pos,parent(pos));
    pos = parent(pos);
  }
}

//Elimina el primer el elemento del heap
template <class T>
void Heap<T>::pop()
{
  data[0] = data[--count];
  heapify(0);
}

//Deja libre la memoria utilizada
template <class T>
void Heap<T>::clear() {
  delete [] data;
  count = 0;
  size_ = 0;
}

//Devuelve el valor de la raíz
template <class T>
T Heap<T>::top()
{
  return data[0];
}

//Devuelve la cantidad de elementos en el heap
template <class T>
int Heap<T>::size()
{
  return count;
}

//Imprime los elementos del heap
template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}

#endif