/*
 * sorts.h
 *
 *  Created on: 05/08/2015
 *      Author: pperezm
 */

#ifndef SORTS_H_
#define SORTS_H_

#include "exception.h"
#include <vector>
#include <list>

template <class T>
class Sorts {
private:
	void swap(std::vector<T>&, int, int);
	int partition(std::vector<T>&, int, int);
	void quickHelper(std::vector<T>&, int, int);

public:
	std::vector<T> quickSort(const std::vector<T> &source);
};

template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

template <class T>
int Sorts<T>::partition(std::vector<T> &v, int low, int high)
{
  int pivot = v[high];
  int i = low;
  for(int j=low;j<high;j++)
  {
    if(v[j]<=pivot)
    {
      swap(v,j,i);
      i++;
    }
  }
  swap(v,i,high); //(i+1)
  return i;
}

template <class T>
void Sorts<T>::quickHelper(std::vector<T> &v, int low, int high)
{
  if(low<high)
  {
    int pivot = partition(v,low,high);
    quickHelper(v,low,pivot-1);
    quickHelper(v,pivot+1,high);
  }
}

template <class T>
std::vector<T> Sorts<T>::quickSort(const std::vector<T> &source) {
  std::vector<T> v(source);
	quickHelper(v,0,v.size()-1);
  /*for(int i=0;i<v.size();i++)
  {
    std::cout<<v[i]<<std::endl;
  }*/
  return v;
}

#endif /* SORTS_H_ */