#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>
#include <sstream>
#include <queue>
#include <stack>
#include <string>

class Graph
{
  private:
    int nodes;
    std::vector<std::vector<int>> adjList;
    int *adjMat;

  public:
    Graph(); 
    ~Graph();

    void loadGraphMat(std::string,int,int); //Mete los nodos a adjMat
    void loadGraphList(std::string,int,int); //Mete los nodos a adjList
    std::string DFS(int,int); //El recorrido de DFS junto con el camino más corto
    std::string BFS(int,int); //El recorrido de BFS junto con el camino más corto
    std::string printAdjList(); //Imprime AdjList
    std::string printAdjMat(); //Imprime AdMat
    void pathBFS(int,int,std::queue<int>&,std::stringstream&); //apoya a BFS a sacar el camino más corto
    bool aux_DFS(int,int,std::stack<int>&,bool[],std::stringstream&,bool&);
    void pathDFS(std::stringstream&,std::stack<int>&);//apoya a DFS a sacar el camino más corto
    void swap(std::vector<int>&,int,int); //Apoya con intercambios de valores en arreglos
};

Graph::Graph() 
{
  nodes = 0;
}

Graph::~Graph() 
{
  nodes = 0;
  delete [] adjMat;
  adjList.~vector();
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

std::string Graph::BFS(int start,int end) //Breadth-First Search
{
  std::queue<int> path_helper;
  bool check[nodes];
  std::stringstream visit;

  visit<<"visited: ";

  for(int i=0;i<nodes;i++)
  {
    check[i]=false;
  }

  check[start] = true;
  path_helper.push(start);
  visit<<start<<" ";
  if(start==end)
    goto next;

  for(int i=start;i<nodes;i++)
  {
    for(int j=0;j<adjList[i].size();j++)
    {
      if(check[adjList[i][j]]==false)
      {
        visit<<adjList[i][j]<<" ";
        check[adjList[i][j]]=true;
        path_helper.push(adjList[i][j]);
        if(adjList[i][j]==end)
          goto next;
      }
    }
  }
  next: pathBFS(start,end,path_helper,visit);
  //std::cout<<visit.str()<<std::endl;
  return visit.str();
}

void Graph::pathBFS(int start,int end,std::queue<int> &q,std::stringstream &visit)
{
  bool check[nodes];
  int prev[nodes];

  visit<<"path:";
  for(int i=0;i<nodes;i++)
  {
    check[i]=false;
    prev[i]=-1;
  }

  check[q.front()] = true;
  prev[q.front()] = start;  
  while(!q.empty())
  {
    for(int i=0;i<adjList[q.front()].size();i++)
    {
      if(check[adjList[q.front()][i]]==false)
      {
        check[adjList[q.front()][i]] = true;
        prev[adjList[q.front()][i]] = q.front();
      }      
    }
    q.pop();
  }

  int path_finder = end;
  std::vector<int> path_holder;
  while (true)
  {
    if(path_finder == prev[path_finder])
    {
      path_holder.push_back(path_finder);
      break;
    }
    path_holder.push_back(path_finder);
    path_finder=prev[path_finder];
  }

  for(int i=path_holder.size()-1;i>=0;i--)
  {
    visit<<" "<<path_holder[i];
  }
}

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

std::string Graph::DFS(int start,int end) //Depth-First Search
{
  std::stringstream visit;
  std::stack<int> DFS_stack;
  bool check[nodes];
  bool stop = false;

  for(int i=0;i<nodes;i++)
  {
    check[i]=false;
  }

  visit<<"visited: ";
  aux_DFS(start,end,DFS_stack,check,visit,stop);
  pathDFS(visit,DFS_stack);
  //std::cout<<visit.str()<<std::endl;
  return visit.str();
}

bool Graph::aux_DFS(int start,int end,std::stack<int> &stack,bool check[],std::stringstream &visit,bool &stop)
{
  bool found = false;
  check[start]=true;
  visit<<start<<" ";
  if (start == end)
  {
    stop = true;
    stack.push(start);
    return true;
  }

  for(int i=0;(i<adjList[start].size())&&(stop==false);i++)
  {
    if(check[adjList[start][i]]==false)
    {
      found = aux_DFS(adjList[start][i],end,stack,check,visit,stop);
      if(found)
      {
        stack.push(start);
      }
    }
  }
  return found;
}

void Graph::pathDFS(std::stringstream &visit,std::stack<int> &stack)
{
  visit<<"path:";
  while(!stack.empty())
  {
    visit<<" "<<stack.top();
    stack.pop();
  }
}

#endif