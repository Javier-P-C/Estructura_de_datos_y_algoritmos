#ifndef BST_H
#define BST_H

#include <string>
#include <sstream>

template <class T> class BST;

template <class T>
class Node
{
  private:
    T value;
    Node<T> *left, *right;

    friend class BST<T>;

  public:
    Node(T);
    Node(Node<T>*,Node<T>*,T);

    void add(T);
    void visit(std::stringstream&);
    int height();
    void ancestors(T,std::stringstream&);
    int whatlevelamI(T);
    bool find(T);

    void preorder(std::stringstream&);
    void inorder(std::stringstream&);
    void postorder(std::stringstream&);
    void levelByLevel(std::stringstream&);

    void stringLevel(std::stringstream&,int);

    void removeChilds();
};

template <class T>
Node<T>::Node(T val):value(val),left(0),right(0) {}

template <class T>
Node<T>::Node(Node<T> *le,Node<T> *ri,T val):left(le),right(ri),value(val) {}

template <class T>
void Node<T>::add(T val)
{
  if(val > value)
  {
    if (right != 0)
      right->add(val);   
    else
      right = new Node<T>(val);
  }
  else if(val < value)
  {
    if(left != 0)
      left->add(val);
    else
      left = new Node<T>(val);
  }
}

template <class T>
void Node<T>::visit(std::stringstream &aux)
{
  std::stringstream aux1,aux2,aux3,aux4;
  aux1<<"[";
  preorder(aux1);
  aux1<<"]\n";

  aux2<<"[";
  inorder(aux2);
  aux2<<"]\n";

  aux3<<"[";
  postorder(aux3);
  aux3<<"]\n";

  aux4<<"[";
  levelByLevel(aux4);
  aux4<<"]";

  aux<<aux1.str()<<aux2.str()<<aux3.str()<<aux4.str();
}

template <class T>
int Node<T>::height()
{
  int right_lvl = 0; 
  int left_lvl = 0;
  int level;

  if(right != 0)
    right_lvl += right->height() + 1;
  if(left != 0)
    left_lvl += left->height() + 1;
  if(left==0 && right==0)
    return 1;

  if(left_lvl > right_lvl)
    level = left_lvl;
  else
    level = right_lvl;

  return level;
}

template <class T>
void Node<T>::ancestors(T val,std::stringstream &aux)
{
  if(val == value)
    return;
  if(val<value)
  {
    if(aux.tellp()!=1)
      aux<<" ";
    aux<<value;
    left->ancestors(val,aux);
  }
  if(val>value)
  {
    if(aux.tellp()!=1)
      aux<<" ";
    aux<<value;
    right->ancestors(val,aux);
  }
}

template <class T>
int Node<T>::whatlevelamI(T val)
{
  if(val<value)
    return left->whatlevelamI(val) +1;
  if(val>value)
    return right->whatlevelamI(val) +1;
  return 1;
}

template <class T>
void Node<T>::preorder(std::stringstream &aux)
{
  aux<<value;
  if(left != 0)
  {
    aux<<" ";
    left->preorder(aux);
  }
  if(right != 0)
  {
    aux<<" ";
    right->preorder(aux);
  }
}

template <class T>
void Node<T>::inorder(std::stringstream &aux)
{
  if(left != 0)
    left->inorder(aux);
  if(aux.tellp() != 1)
    aux<<" ";
  aux<<value;
  if(right != 0)
    right->inorder(aux);
}

template <class T>
void Node<T>::postorder(std::stringstream &aux)
{
  if(left != 0)
    {
      left->postorder(aux);
      aux<<" ";
    }
  if(right)
    {
      right->postorder(aux);
      aux<<" ";
    }
  aux<<value;
}

template <class T>
void Node<T>::levelByLevel(std::stringstream &aux)
{
  int levels = height();

  for(int i=0; i<levels; i++)
  {
    stringLevel(aux,i);
  }
}

template <class T>
void Node<T>::stringLevel(std::stringstream &aux,int levels)
{
  if(levels==0)
  {
    if (aux.tellp() != 1) 
    {
			aux << " ";
		}
    aux<<value;
    return; //Checar por si no funciona------------------------------------------------------
  }
  if(left!=0)
    left->stringLevel(aux,levels-1);
  if(right!=0)
    right->stringLevel(aux,levels-1);
}

template <class T>
bool Node<T>::find(T val)
{
  if(val == value)
    return true;
  else if(val < value)
  {
    if(left!=0)
    {
      return left->find(val);
    }
  }
  else if(val > value)
  {
    if(right!=0)
    {
      return right->find(val);
    }
  }
    
  return false;
}

template <class T>
void Node<T>::removeChilds()
{
  if(left!=0)
  {
    left->removeChilds();
    delete left;
    left = 0;
  }
  if(right!=0)
  {
    left->removeChilds();
    delete right;
    right = 0;
  }
}


template <class T>
class BST
{
  private:
    Node<T> *root;

  public:
    BST();
    ~BST();

    void add(T);
    std::string visit();
    int height();
    std::string ancestors(T);
    int whatlevelamI(T);
    bool empty();
};

template <class T>
BST<T>::BST():root(0) {}

template <class T>
BST<T>::~BST()
{
  if((root->left==0) || (root->right==0))
    root->removeChilds();
  delete root;
}

template <class T>
void BST<T>::add(T val)
{
  if(root == 0)
    root = new Node<T>(val);
  else
    root->add(val);
}

template <class T>
std::string BST<T>::visit()
{
  std::stringstream aux;
  if(empty())
    return "[]\n[]\n[]\n[]";
  root->visit(aux);
  //std::cout<<aux.str();
  return aux.str();
}

template <class T>
int BST<T>::height()
{
  if(root==0)
    return 0;
  return root->height();
}

template <class T>
std::string BST<T>::ancestors(T val)
{
  std::stringstream aux;
  aux<<"[";
  if(!empty())
  {
    if(root->find(val))
    {
      root->ancestors(val,aux);
    }
  }
  aux<<"]";
  return aux.str();
}

template <class T>
int BST<T>::whatlevelamI(T val)
{
  if(root->find(val))
    return root->whatlevelamI(val);
  return -1;
}

template <class T>
bool BST<T>::empty()
{
  return (root == 0);
}



#endif