/*
 * funciones.h
 *
 *  Created on: 25/08/2020
 *      Author: Javier Piña Camacho
 */
#include <iostream> 

class Funciones
{
  public:
  int sumaIterativa(int n);
  int sumaRecursiva(int n);
  int sumaDirecta(int n);
};

//Suma de 1 a n de manera Iterativa
int Funciones::sumaIterativa(int n)
{
  int suma=0;
  for (int i=0;i<n;i++)
  {
    suma+=n-(i);
  }
  return suma;
}

//Suma de 1 a n de manera Recursiva
int Funciones::sumaRecursiva(int n)
{
  int suma=n;
  if (n<1)
  {
    return 0;
  }
  else
  {
    suma+=sumaRecursiva(n-1);
    return suma;
  }
}

//Suma de 1 a n por medio de una ecuación
int Funciones::sumaDirecta(int n)
{
  int suma=0;
  suma = n*(n+1)/2;
  return suma;
}
