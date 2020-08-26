/*
 * recursion.h
 *
 *  Created on: 10/09/2015
 *      Author: pperezm
 */

#ifndef RECURSION_H_
#define RECURSION_H_

#include "exception.h"
#include <iostream>

long sum_seq(int n) { //lineal O(n)
  int sum = 0;
  for(int i=n;i!=0;i--)
  {
    sum+=i;
  }
  return sum;
}

long sum_rec(int n) { //O(n)
  int aument=0;
  if (n>=1)
    {
      aument+=n+sum_seq(n-1);
    }
  else
    {
      return 0;
    }
  return aument;
}

long fact_seq(int n) { //O(n)
	int factorial = 1;
  for(int i=n;i!=0;i--)
  {
    factorial*=i;
  }
  return factorial;
}

long fact_rec(int n) { //O(n)
  int fact = n;
  if(n==0) {return 0;}
  else if(n==1) {return 1;}
  fact *= fact_rec(n-1);
	return fact;
}

long fib_seq(int n) { //O(n)
  if (n<2)
  {
    return 0;
  }
  int i=3, a=1, b=1, aux;
  while (i<=n)
  {
    aux=a;
    a+=b;
    b=aux;
    i++;
  }
	return a;
}

long fib_rec(int n) { //O(2^n/2)
  if (n==1) {return 1;}
  if (n==0) {return 0;}
	return fib_rec(n-1)+fib_rec(n-2);
}

long gcd_seq(long a, long b) { //mayor común divisor O(log(n))
	long aux;
  while (b!=0)
  {
    aux = b;
    b=a%b;
    a = aux;
  }
  return a;
}

long gcd_rec(long a, long b) { //log(n)
  if (b==0) {return a;}
	long aux=gcd_rec(b, a%b);
  return aux;
}

bool find_seq(int arr[], int size, int val) {//
	return false;
}

bool find_rec(int arr[], int low, int high, int val) {
	return false;
}

int max_seq(int arr[], int size) { //elemento más grande del arreglo
  long aux=arr[0];
  for (int i=0;i<size;i++)
  {
    if (aux<arr[i]) {aux=arr[i];}
  }
	return aux;
}

int max_rec(int arr[], int low, int high) //O(2^n)
{
  
	return 0;
}

int unimodal_seq(int arr[], int size) {
	return 0;
}

int unimodal_rec(int arr[], int low, int high) {
	return 0;
}

int unimodal_rec(int arr[], int size) {
	return 0;
}

int bs_seq(int arr[], int size, int val) {
	return 0;
}

int bs_aux(int arr[], int low, int high, int val) //log(n)
{
  int mid;

  if (low <= high) {
    mid = (high+low)/2;
    if (val == arr[mid]) {
      return mid;
    }
    else if (val < arr[mid]) {
      return bs_aux(arr, low, mid - 1, val);
    }
    else if (val>arr[mid]) {
      return bs_aux(arr, mid +1, high, val);
    }
    return low;
  }
	return 0;
}

int bs_rec(int arr[], int size, int val) {
	return bs_aux(arr,0,size-1, val);
}
#endif /* RECURSION_H_ */
