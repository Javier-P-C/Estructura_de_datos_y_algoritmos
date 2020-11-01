#ifndef AVL_H_
#define AVL_H_

#include <string>
#include <sstream>
#include <iostream>

template <class T> class AVL;

template <class T>
class TreeNode {
private:
	T value;
	TreeNode *left, *right;
  int level, balance;
	TreeNode<T> *predecessor();

public:
	TreeNode(T);
	TreeNode(T, TreeNode<T>*, TreeNode<T>*, int, int);
	void add(T);
	bool find(T);
	void remove(T);
	void removeChilds();
	void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;
  int max_depth();
  TreeNode<T>* check_tree(T*, TreeNode<T>*, bool*);
  TreeNode<T>* balance_tree();
  TreeNode<T>* rot_left(TreeNode<T>*);
  TreeNode<T>* rot_right(TreeNode<T>*);
  TreeNode<T>* rot_left_right(TreeNode<T>*);
  TreeNode<T>* rot_right_left(TreeNode<T>*);

	friend class AVL<T>;
};

template <class T>
TreeNode<T>::TreeNode(T val):value(val),left(0),right(0),level(0),balance(0) {}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri, int lev, int bal):value(val),left(le),right(ri),level(lev),balance(bal) {}

template <class T>
void TreeNode<T>::add(T val) {
  if(val<value)
  {
    if(left != 0)
      left->add(val);
    else
      left = new TreeNode<T> (val);
  }
  else
  {
    if(right != 0)
      right->add(val);
    else
      right = new TreeNode<T> (val);
  }
}

template <class T>
bool TreeNode<T>::find(T val) {
  if(val == value)
    return true;
  else if(val < value)
    return(left!=0 && left->find(val));
  else if(val > value)
    return (right!=0 && right->find(val));
	return false;
}

template <class T>
TreeNode<T>* TreeNode<T>::predecessor() {
  TreeNode<T> *le, *ri;

	le = left;
	ri = right;

	if (left == 0) {
		if (right != 0) {
			right = 0;
		}
		return ri;
	}

	if (left->right == 0) {
		left = left->left;
		le->left = 0;
		return le;
	}

	TreeNode<T> *parent, *child;
	parent = left;
	child = left->right;
	while (child->right != 0) {
		parent = child;
		child = child->right;
	}
	parent->right = child->left;
	child->left = 0;
	return child;
}

template <class T>
void TreeNode<T>::remove(T val) {
  TreeNode<T> *succ, *old;
  if(val < value)
  {
    if(left!=0)
    {
      if(val == left->value)
      {
        TreeNode<T> *old;
        old = left;
        succ = left->predecessor();
        if(succ != 0)
        {
          succ->left = old->left;
          succ->right = old->right;
        }
        left = succ;
        delete old;
      }
      else
        left->remove(val);
    }
  }
  else if(val > value)
  {
    if(right!=0)
    {
      if(val == right->value)
      {
        old = right;
        succ = right->predecessor();
        if(succ != 0)
        {
          succ->right = old->right;
          succ->left = old->left;
        }
        right = succ;
        delete old;
      }
      else
        right->remove(val);
    }
  }
}

template <class T>
void TreeNode<T>::removeChilds() {
  if(right != 0)
  {
    right->removeChilds(); 
    delete right;
    right = 0;
  }
  if(left != 0)
  {
    left->removeChilds(); 
    delete left;
    left = 0;
  }
}

template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
int TreeNode<T>::max_depth()
{
  int le=0, ri=0;
  if(left!=0)
    le = left->max_depth() + 1;
  if(right!=0)
    ri = right->max_depth()+1;
  if(le>ri)
    level = le;
  else 
    level = ri;
  balance = le - ri;
  return level;
}

//Checa si hay o no irregularidad
//a es el nodo balanceado
template <class T>
TreeNode<T>* TreeNode<T>::check_tree(T *check_val,TreeNode<T> *parent, bool *checked)
{
  std::cout<<"node value "<<value<<" "<<level<<" "<<balance<<std::endl;
  TreeNode<T> *le=0, *ri=0, *a=0;
  if(left != 0)
    le = left->check_tree(check_val,this,checked);
  if(right!=0)
    ri = right->check_tree(check_val,this,checked);
  if(*checked == false)
  {
    if(balance > 1)
    {
      a = balance_tree();
      *check_val = value;
      *checked = true;
      if(parent!=0)
      {
        std::cout<<"parent "<<parent->value<<" parent->left "<<parent->left->value<<std::endl;
        parent->left = a;
      }
    }
    else if(balance < -1)
    {
      a = balance_tree();
      *check_val = value;
      *checked = true;
      if(parent!=0)
      {
        std::cout<<"parent "<<parent->value<<" parent->right "<<parent->right->value<<std::endl;
        parent->right = a;
      }
    }
  }
  return a;
}

template <class T>
TreeNode<T>* TreeNode<T>::balance_tree()
{
  TreeNode<T> *a = this, *le = left, *ri=right;
  int old_value=value;
  std::cout<<"a: "<<a->value<<" ";
  if(balance>0)
  {
    if(le->balance>0)
    {
      std::cout<<"rot_right "<<a->balance<<" left "<<le->balance<<std::endl;
      a=rot_right(a);
    }
    else
    {
      std::cout<<"rot_left_right "<<a->balance<<"left: "<<le->balance<<std::endl;
      a = rot_left_right(a);
    }
  }
  else
  {
    if(ri->balance<0)
    {
      std::cout<<"rot_left "<<a->balance<<"right: "<<ri->balance<<std::endl;
      a=rot_left(a);
    }
    else
    {
      std::cout<<"rot_right_left "<<a->balance<<"right: "<<ri->balance<<std::endl;
      a=rot_right_left(a);
    }
  }
  std::cout<<"a value is "<<a->value<<std::endl;
  return a;
}

template <class T>
TreeNode<T>* TreeNode<T>::rot_left(TreeNode<T>* a)
{
  TreeNode<T> *b, *temp=0;
  if(a->right!=0)
  {
    b=a->right;
    if(b->left!=0)
      temp=b->left;
    b->left=a;
    if(temp!=0)
      a->right=temp;
    else
      a->right=0;
  }
  return b;
}

template <class T>
TreeNode<T>* TreeNode<T>::rot_right(TreeNode<T>* a)
{
  TreeNode<T> *b, *temp=0;
  if(a->left!=0)
  {
    b=a->left;
    if(b->right!=0)
      temp=b->right;
    b->right=a;
    if(temp!=0)
      a->left=temp;
    else
      a->left=0;
  }
  return b;
}

template <class T>
TreeNode<T>* TreeNode<T>::rot_left_right(TreeNode<T>* a)
{
  a->left=rot_left(a->left);
  a = rot_right(a);
  return a;
}

template <class T>
TreeNode<T>* TreeNode<T>::rot_right_left(TreeNode<T>* a)
{
  a->right=rot_right(a->right);
  a = rot_left(a);
  return a;
}

template <class T>
class AVL {
private:
	TreeNode<T> *root;

public:
	AVL();
	~AVL();
	bool empty() const;
	void add(T);
	bool find(T) const;
	void remove(T);
	void removeAll();
	std::string inorder() const;
	std::string preorder() const;
};

template <class T>
AVL<T>::AVL() : root(0) {}

template <class T>
AVL<T>::~AVL() {
	removeAll();
}

template <class T>
bool AVL<T>::empty() const {
	return (root == 0);
}

template<class T>
void AVL<T>::add(T val) {
  if(!empty())
  {
    if(!root->find(val))
    {
      TreeNode<T> *temp;
      T check_val;
      bool aux;
      root->add(val);
      root->max_depth();
      temp=root->check_tree(&check_val,0,&aux);
      std::cout<<"check values "<<check_val<<" vs "<<root->value<<std::endl;
      if(check_val==root->value)
        root=temp;
      root->max_depth();
    }
  }
  else
    root= new TreeNode<T>(val);
}

template <class T>
void AVL<T>::remove(T val) {
  if(root!=0)
  {
    if(val==root->value)
    {
      TreeNode<T> *pred=root->predecessor();
      if(pred!=0)
      {
        pred->left = root->left;
        pred->right=root->right;
      }
      delete root;
      root=pred;
    }
    else
      root->remove(val);
    root->max_depth();
    root = root->chexk_tree();
    root->max_depth();
  }
}

template <class T>
void AVL<T>::removeAll() {
  if(root!=0)
    root->removeChilds();
  delete root;
  root = 0;
}

template <class T>
bool AVL<T>::find(T val) const {
  if(root!=0)
    return root->find(val);
  return false;
}

template <class T>
std::string AVL<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string AVL<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

#endif 
