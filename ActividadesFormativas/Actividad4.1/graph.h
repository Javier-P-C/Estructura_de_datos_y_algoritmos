#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <fstream>
#include <list>
#include <cmath>
#include <iostream>
#include <sstream>

class Graph
{
  private:
    int nodes;
    std::vector<std::vector<int>> adjList;
    int *adjMat;

  public:
    Graph();
    ~Graph();

    void loadGraphMat(std::string,int,int);
    void loadGraphList(std::string,int,int);
    std::string DFS(int,int);
    std::string BFS(int,int);
    std::string printAdjList();
    std::string printAdjMat();

    void swap(std::vector<int>&,int,int);
};

Graph::Graph() 
{
  nodes = 0;
}

Graph::~Graph() 
{
  nodes = 0;
  //delete [] adjList;
  //adjMat.~vector();
}

void Graph::swap(std::vector<int> &v,int i,int j)
{
  int aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

void Graph::loadGraphList(std::string doc_name,int vert,int arc)
{
  //Se dan valores los atributos del objeto
  nodes = vert;
  for(int i=0;i<nodes;i++)
  {
    std::vector<int> lista;
    adjList.push_back(lista);
  }

  //Se lee el documento y se sacan los nodos de él
  std::ifstream reader(doc_name);
  if(reader.is_open())
  {
    std::string line;
    while(reader.good())
    {
      getline(reader,line,'\n');
      //Se saca el primer entero 
      int index = 1, aux_i = index;
      int a = 0,b = 0,count = -1;
      do
      {
        count ++;
        aux_i++;
      }while(line[aux_i]!=',');
      do
      {
        a+=(line[index]-'0')*pow(10,count);
        index++;
        count--;
      } while(line[index]!=',');
      //Se saca el segundo entero 
      index+=2;
      aux_i = index;
      count = -1;
      for(;aux_i<line.size()-1;aux_i++)
      {
        count++;
      }
      for(;index<line.size()-1;index++)
      {
        b+=(line[index]-'0')*pow(10,count);
        count--;
      } 

      adjList[a].push_back(b);
      adjList[b].push_back(a);
    }
    reader.close();

    //Insertion Sort
    for(int x=0;x<nodes;x++)
    {
      for (int i=1;i<=adjList[x].size()-1;i++)
      {
        for (int j=i;j>0 && adjList[x][j]<adjList[x][j-1];j--)
        {
          swap(adjList[x],j,j-1);
        }
      }
    }

  }
  else
  {
    std::cout<<"ERROR: No se pudo abrir el archivo"<<std::endl;
  }
}

void Graph::loadGraphMat(std::string doc_name,int vert,int arc)
{
  //Se dan valores los atributos del objeto
  nodes = vert;
  adjMat = new int[nodes*nodes];

  for(int i=0;i<(nodes*nodes);i++)
  {
    adjMat[i]=0;
  }
  std::ifstream reader(doc_name);
  
  if(reader.is_open())
  {
    
    std::string line;
    
    while(reader.good())
    {
      getline(reader,line,'\n');
      //Se saca el primer entero 
      int index = 1, aux_i = index;
      int m = 0,n = 0,count = -1;
      do
      {
        count ++;
        aux_i++;
      }while(line[aux_i]!=',');
      do
      {
        m+=(line[index]-'0')*pow(10,count);
        index++;
        count--;
      } while(line[index]!=',');
      //Se saca el segundo entero 
      index+=2;
      aux_i = index;
      count = -1;
      for(;aux_i<line.size()-1;aux_i++)
      {
        count++;
      }
      for(;index<line.size()-1;index++)
      {
        n+=(line[index]-'0')*pow(10,count);
        count--;
      } 

      adjMat[nodes*m+n] = 1;
      adjMat[nodes*n+m] = 1;

    }
    reader.close();
    printAdjMat();
  }
  else
  {
    std::cout<<"ERROR: No se pudo abrir el archivo"<<std::endl;
  }
  
}

//std::string DFS(int,int); //Depth-First Search

std::string BFS(int,int); //Breadth-First Search

std::string Graph::printAdjList()
{
  std::stringstream str;
  for(int i=0;i<nodes;i++)
  {
    str<<"vertex "<<i<<" : ";
    for(int j=0;j<adjList[i].size();j++)
    {
      str<<adjList[i][j];
      str<<" ";
    }
  }
  return str.str();
}

std::string Graph::printAdjMat()
{
  std::stringstream str;
  for(int i=0;i<nodes*nodes;i++)
  {
    str<<adjMat[i];
    str<<" ";
  }
  return str.str();
}

#endif
