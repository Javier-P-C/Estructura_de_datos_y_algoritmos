#include <iostream>
using namespace std;

template <class T>
class Par 
{
  private:
    T a,b;
  public:
    Par(T generico1, T generico2) {a = generico1;b=generico2;};
    T getmax();
};

template <class T>
T Par<T>::getmax()
{
  T retval;
  if (a>b)
    retval= a;
  else
   retval = b;
  return retval;
}

int main() {
  Par <int> objectConInts (23,45);
  cout<<objectConInts.getmax();
}