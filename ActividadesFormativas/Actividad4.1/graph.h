#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <fstream>
#include <list>
#include <cmath>

class Graph
{
  private:
    int nodes;
    std::list<int> *adjList;
    std::vector<int> adjMat;

  public:
    Graph();
    ~Graph();

    void loadGraphMat(std::string,int,int);
    void loadGraphList(std::string,int,int);
    std::string DFS(int,int);
    std::string BFS(int,int);
    std::string printAdjList();
    std::string printAdjMat();
};

Graph::Graph() 
{
  nodes = 0;
}

Graph::~Graph() 
{
  nodes = 0;
  delete [] adjList;
  adjMat.~vector();
}

void Graph::loadGraphList(std::string doc_name,int vert,int arc)
{
  //Se dan valores los atributos del objeto
  nodes = vert;
  adjList = new std::list<int>[nodes];

  //Se lee el documento y se sacan los nodos de él
  std::ifstream reader(doc_name);
  if(reader.is_open())
  {
    std::string line;
    while(reader.good())
    {
      getline(reader,line,')');
      
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
        a+=(line[i]-'0')*pow(10,count);
        index++;
        count--;
      } while(line[index]!=',');
      //Se saca el segundo entero 
      index+=2;
      aux_i = index;
      count = -1;
      for(;aux_i<line.size();aux_i++)
      {
        count++;
      }
      for(;index<line.size();index++)
      {
        b+=(line[i]-'0')*pow(10,count);
        count--;
      } 

      adjList[a].push_back(b);
      adjList[b].push_back(a);
    }
    reader.close();
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
  for(int i=0;i<(nodes*nodes);i++)
  {
    adjMat.insert(0);
  }

  std::ifstream reader(doc_name);
  if(reader.is_open())
  {
    std::string line;
    while(reader.good())
    {
      getline(reader,line,')');

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
        m+=(line[i]-'0')*pow(10,count);
        index++;
        count--;
      } while(line[index]!=',');
      //Se saca el segundo entero 
      index+=2;
      aux_i = index;
      count = -1;
      for(;aux_i<line.size();aux_i++)
      {
        count++;
      }
      for(;index<line.size();index++)
      {
        n+=(line[i]-'0')*pow(10,count);
        count--;
      } 

      adjMat[nodes*m+n] = 1;
      adjMat[nodes*n+m] = 1;
    }
    reader.close();
  }
  else
  {
    std::cout<<"ERROR: No se pudo abrir el archivo"<<std::endl;
  }
}

std::string DFS(int,int);

std::string BFS(int,int);

std::string printAdjList();

std::string printAdjMat();

#endif
