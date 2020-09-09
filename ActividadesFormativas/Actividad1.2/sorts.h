/*
 * sorts.h
 *
 *  Created on: 09/09/2020
 *      Author: Javier Piña Camacho
 */
#ifndef SORTS_H_
#define SORTS_H_

#include <iostream>

template <class T>
class Sorts
{
  public:
  void ordenaSeleccion(std::vector<T> &v);
  void ordenaBurbuja(std::vector<T> &v);
  void ordenaMerge(std::vector<T> &v);
  void mergeSplit(std::vector<T> &A,std::vector<T> &B,int low,int high);
  void mergeArray(std::vector<T> &A,std::vector<T> &B,int low,int mid,int high);
  void copyArray(std::vector<T> &A,std::vector<T> &B,int low, int high);
  int busqSecuencial(std::vector<T> &v,T valor);
  int busqBinaria(std::vector<T> &v,T valor);
  int busqBinAux(std::vector<T> &v,int low,int high,T valor);
  void swap(std::vector<T> &v,int i,int j);
};

//Intercambio de dos valores en un vector
template <class T>
void Sorts<T>::swap(std::vector<T> &v,int i,int j)
{
  T aux;
  aux=v[i];
  v[i]=v[j];
  v[j]=aux;
}

//selection Sort
template <class T>
void Sorts<T>::ordenaSeleccion(std::vector<T> &v)
{
  int pos;
  int aux;
  for(int i=0;i<v.size();i++)
  {
    pos=i;
    for(int j=i;j<v.size();j++)
    {
      if (v[j]<v[pos])
      {
        pos=j;
      }
    }
    if (pos!=i)
    {
      swap(v,pos,i);
    }
  }
}

//Bubble Sort
template <class T>
void Sorts<T>::ordenaBurbuja(std::vector<T> &v)
{
  for (int i=0;i<v.size()-1;i++)
  {
    for (int j=0;j<v.size()-1-i;j++)
    {
      if (v[j]>v[j+1])
      {
        swap(v,j,j+1);
      }
    }
  }
}

//Merge Sort
template <class T>
void Sorts<T>::copyArray(std::vector<T> &A,std::vector<T> &B,int low, int high)
{
  for(int i=low;i<=high;i++)
  {
    A[i]=B[i];
  }
}

template <class T>
void Sorts<T>::mergeArray(std::vector<T> &A,std::vector<T> &B,int low,int mid,int high)
{
  int i=low;
  int j=mid+1;
  int k=low;

  while(i<=mid && j<=high)
  {
    if (A[i]<A[j])
    {
      B[k]=A[i];
      i++;
    }
    else
    {
      B[k]=A[j];
      j++;
    }
    k++;
  }

  if(i<=mid)
  {
    for(;i<=mid;i++)
    {
      B[k]=A[i];
      k++;
    }
  }
  else
  {
    for(;j<=high;j++)
    {
      B[k]=A[j];
      k++;
    }
  }
}

template <class T>
void Sorts<T>::mergeSplit(std::vector<T> &A,std::vector<T> &B,int low,int high)
{
  int mid;
  if ((high-low)<1)
  {
    return;
  }
  mid = (high+low)/2;
  mergeSplit(A,B,low,mid);
  mergeSplit(A,B,mid+1,high);
  mergeArray(A,B,low,mid,high);
  copyArray(A,B,low,high);
}

template <class T>
void Sorts<T>::ordenaMerge(std::vector<T> &v)
{
  int low = 0;
  int high = v.size()-1;
  std::vector<T> temporal(v.size());
  mergeSplit(v,temporal,low,high);
}

//Sequential search
template <class T>
int Sorts<T>::busqSecuencial(std::vector<T> &v,T valor)
{
  for(int i=0;i<=v.size()-1;i++)
  {
    if(v[i]==valor)
    {
      return i;
    }
  }
  return -1;
}

//Binary search
template <class T>
int Sorts<T>::busqBinAux(std::vector<T> &v,int low,int high,T valor)
{
  int mid = (low+high)/2;
  if(low<high)
  {
    if(valor==v[mid])
    {
      return mid;
    }
    if (valor<v[mid])
    {
      return busqBinAux(v,low,mid-1,valor);
    }
    else if (valor>v[mid])
    {
      return busqBinAux(v,mid+1,high,valor);
    }
  }
  return low;
}

template <class T>
int Sorts<T>::busqBinaria(std::vector<T> &v,T valor)
{
  int low = 0;
  int high = v.size()-1;
  return busqBinAux(v,low,high,valor);
}

#endif