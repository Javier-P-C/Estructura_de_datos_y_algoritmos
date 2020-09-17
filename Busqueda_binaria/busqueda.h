#ifndef BUSQUEDA_H_
#define BUSQUEDA_H_

//Devuelve la posición donde se encuentra el número que se busca en su defecto manda la posición donde debería estar


//Demanera secuencial
int busquedaBin_sec(int arr[],int size,int valor)
{
  int mid;
  int low = 0;
  int high = size-1;

  while (low < high) //low<=high
  {
    mid = (high+low)/2;
    if (valor==arr[mid])
    {
      return mid;
    }
    else if (valor<arr[mid])
    {
      high=mid-1;
    }
    else if (valor>arr[mid])
    {
      low=mid+1;
    }
  }
  return low;
}

//De manera recursiva
int busqueda_aux(int arr[],int valor,int low,int high)
 {
   int mid;
   mid=(low+high)/2;
   if (low<=high) //low<high
   {
      if (valor == arr[mid])
      {
        return mid;
      }
      else if(valor<arr[mid])
      {
        return busqueda_aux(arr,valor,low,mid-1);
      }
      else if(valor>arr[mid])
      {
        return busqueda_aux(arr,valor,mid+1,high);
      }
   }
   return low;
 }

 int busquedaBin_rec(int arr[],int size,int valor)
 {
   return busqueda_aux(arr,valor,0,size-1);
 }

#endif