#include <iostream>
#include "busqueda.h"

//La busqueda binaria sirve con arreglos ordenados

int main()
{
  int arr[] = {1,3,5,23,66,67,99};

  //iterativa
  std::cout<<busquedaBin_sec(arr,7,67);
  //Recursiva
  std::cout<<"\n"<<busquedaBin_rec(arr,7,5);
}
