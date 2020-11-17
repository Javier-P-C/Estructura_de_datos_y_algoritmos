#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <fstream>
#include <cmath>
#include <stack>
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

    void loadGraphMat(std::string,int,int); //Mete los nodos a adjMat
    void loadGraphList(std::string,int,int); //Mete los nodos a adjList
    void swap(std::vector<int>&,int,int); //Apoya con intercambios de valores en arreglos
    bool isTree(); //Determina si el grafo es un arbol
    std::string topologicalSort(); //Devuelve un string con el oreden topológico
    bool bipartiteGraph(); //Determina si es bipartite
    void auxTopologicalSort(int,std::stack<int>&,bool[],bool[]); //Ayuda a determinar el orden topológico
    void auxBipartiteGraph(int,int,int,bool&,int[],bool[]); //Ayuda a determinar si es bipartite
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
  }
  else
  {
    std::cout<<"ERROR: No se pudo abrir el archivo"<<std::endl;
  }
}

bool Graph::isTree()
{
  

  bool check[nodes];

  for(int i=0;i<nodes;i++)
  {
    int check_count = 0;

    for(int j=0;j<nodes;j++)
    {
      check[i]=false;
    }

    for(int x=0;x<nodes;x++)
    {
      for(int z=0;z<adjList[x].size();z++)
      {
        if(check[adjList[x][z]]==false)
        {
          check[adjList[x][z]]==true;
          check_count++;
        }
      }
    }

    if((check[i]==false)&&(check_count==nodes-1))
      return true;
  }

  return false;
}
    
std::string Graph::topologicalSort()
{
  std::stringstream visit;
  std::stack<int> toplogic_stack;
  bool check[nodes];
  bool check2[nodes];
  bool stop = false;

  for(int i=0;i<nodes;i++)
  {
    check[i]=false;
    check2[i]=false;
  }

  check[0]=true;
  auxTopologicalSort(0,toplogic_stack,check,check2);

  visit<<toplogic_stack.top();
  toplogic_stack.pop();
  while(!toplogic_stack.empty())
  {
    visit<<" "<<toplogic_stack.top();
    toplogic_stack.pop();
  }
  //std::cout<<visit.str()<<std::endl;
  return visit.str();
}
    
void Graph::auxTopologicalSort(int start,std::stack<int> &toplogic_stack,bool check[],bool check2[])
{  
  for(int i=0;i<adjList[start].size();i++)
  {
    if(check[start]==false) //Marca que se ha pasado por este nodo
    {
      check[start]=true;
    }
    if(check[adjList[start][i]]==false) //Recusividad si el nodo vecino no ha sido visitado
    {
      auxTopologicalSort(adjList[start][i],toplogic_stack,check,check2);
    }
  }
  if(check2[start]==false)//Mete al stack el para ordenar los nodos
  {
    toplogic_stack.push(start);
    check2[start]=true;
  }
}

bool Graph::bipartiteGraph()
{
  int color =0; //0=rojo, 1=azul
  bool aux = true;

  int check[nodes];
  bool visit[nodes];
  for(int i=0;i<nodes;i++)
  {
    check[i]=-1;
    visit[i]=false;
  }

  auxBipartiteGraph(0,-1,color,aux,check,visit);
  return aux;
}

void Graph::auxBipartiteGraph(int start,int prev,int color,bool &aux,int check[],bool visit[])
{

  //Checa si hay inconsistencias en los colores
  if(check[start]==-1)
  {
    check[start]=color;
  }
  else
  {
    if(check[start]!=color)
    {
      aux=false;
    }
  }

  //Determina si ya se ha pasado por este nodo
  if (visit[start]==true)
    return;
  else
    visit[start]=true;

  //Recorre los nodos vecinos
  int color_aux=color;
  if(color_aux == 0)
    color_aux = 1;
  else
    color_aux=0;
  for(int i=0;i<adjList[start].size();i++)
  {
    if(adjList[start][i]!=prev)
    {
      auxBipartiteGraph(adjList[start][i],start,color_aux,aux,check,visit);
    }
  }
}

#endif