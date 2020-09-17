#include <iostream>
#include <fstream>

int main()
{
  //Escribir en archivo
  std::ofstream myFilein("example.txt");
  if (myFilein.is_open())
  {
    myFilein<<"Línea ingresada";
    myFilein<<" Seguimos aquí?\n";
    myFilein<<"Nueva línea ingresada";
    myFilein.close();
  }
  else
  {
    std::cout<<"No se puede abrir el archivo"<<std::endl;
  }

  //Leer archivo
  std::ifstream myFileout("example.txt");
  std::string line;
  if(myFileout.is_open())
  {
    while(getline(myFileout,line))
    {
      std::cout<<line<<std::endl;
    }
  }
  else
  {
    std::cout<<"No se puede abrir el archivo";
  }

  return 0;
}