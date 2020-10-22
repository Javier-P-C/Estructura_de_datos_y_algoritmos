#ifndef SPLAY_H
#define SPLAY_H

#include <iostream>
#include <sstream>

template <class T> class SplayTree;

template <class T>
class Node
{
  private:
    T value;
    Node<T> *left, *right, *parent;

    Node<T>* succesor();
    Node<T>* rot_right(Node<T>*);
    Node<T>* rot_left(Node<T>*);

    friend class SplayTree<T>;

  public:
    Node(T);
    Node(T, Node<T>*,Node<T>*,Node<T>*);

    Node<T>* add(T);
    Node<T>* remove(T);
    Node<T>* find(T);
    void inorder(std::stringstream &aux) const;
    int size();
    Node<T>* splay(Node<T>*,Node<T>*);

    void print_tree(std::stringstream &aux) const;
    void preorder(std::stringstream &aux) const;
};

template <class T>
Node<T>::Node(T val)
{
  value = val;
  left = 0;
  right = 0;
  parent = 0;
}

template <class T>
Node<T>::Node(T val, Node<T> *le,Node<T> *ri,Node<T> *prnt)
{
  value = val;
  right = ri;
  left = le;
  parent = prnt;
}

template <class T>
Node<T>* Node<T>::succesor()
{
  Node<T> *le, *ri;
  le =left;
  ri = right;

  if(right == 0)
  {
    if(left!=0)
      left = 0;
    if(le)
      le->parent = 0;
    return le;
  }
  
  if(right->left==0)
  {
    right=right->right;
    if(right!=0)
      right->parent=parent;
    ri->right=0;
    ri->parent=0;
    return ri;
  }

  Node<T> *navigator,*next;
  navigator = right;
  next=right->left;
  while(next->left!=0)
  {
    navigator=next;
    next=next->left;
  }
  navigator->left = next->right;
  if(navigator->left)
    navigator->left->parent=navigator;
  next->right=0;
  return next;
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T> *pointer)
{
  Node<T> *pointer_son = pointer->left;

  pointer->left=pointer_son->right;
  if(pointer_son->right!=0)
    pointer_son->right->parent=pointer;

  pointer_son->right=pointer;
  pointer_son->parent=pointer->parent;
  pointer->parent=pointer_son;

  if(pointer_son->parent)
  {
    if(pointer_son->parent->left && pointer_son->parent->left->value==pointer->value)
      pointer_son->parent->left=pointer_son;
    else
      pointer_son->parent->right=pointer_son;
  }
  
  return pointer_son; 
}

template <class T>
Node<T>* Node<T>::rot_left(Node<T> *pointer)
{
  Node<T> *pointer_son = pointer->right;

  pointer->right=pointer_son->left;
  if(pointer_son->left!=0)
    pointer_son->left->parent=pointer;

  pointer_son->left=pointer;
  pointer_son->parent=pointer->parent;
  pointer->parent=pointer_son;

  if(pointer_son->parent)
  {
    if(pointer_son->parent->left && pointer_son->parent->left->value==pointer->value)
      pointer_son->parent->left=pointer_son;
    else
      pointer_son->parent->right=pointer_son;
  }
  
  return pointer_son; 
}

template <class T>
Node<T>* Node<T>::add(T val)
{
	if(val<value)
  {
		if(left!=0)
			return left->add(val);
		else
    {
			left = new Node<T>(val);
			left->parent=this;
			return left;
		}
	}
  else
  {
		if(right!=0)
			return right->add(val);
		else
    {
			right = new Node<T>(val);
			right->parent=this;
			return right;
		}
	}
}

template <class T>
Node<T>* Node<T>::remove(T val)
{
  Node<T> *old,*succ;
  if(val<value)
  {
    if(left!=0)
    {
      if(left->value==val)
      {
        old=left;
				succ=left->succesor();
				if(succ !=0)
        {
					succ->left=old->left;
					succ->right=old->right;
					succ->parent=old->parent;
					if(succ->left)
						succ->left->parent=succ;
					if(succ->right)
						succ->right->parent=succ;
        }
        left=succ;
				delete old;
				return this;
      }
			else
				return left->remove(val);
    }
  }
  else if(val>value)
  {
    if(right!=0)
    {
      if(right->value==val)
      {
        old=right;
				succ=right->succesor();
				if(succ !=0)
        {
					succ->right=old->right;
					succ->left=old->left;
					succ->parent=old->parent;
					if(succ->right)
						succ->right->parent=succ;
					if(succ->left)
						succ->left->parent=succ;
        }
        right=succ;
				delete old;
				return this;
      }
			else
				return right->remove(val);
    }
  } 
  return 0;
}

template <class T>
Node<T>* Node<T>::find(T val)
{
  if(val==value)
		return this;
	else if (val<value)
  {
		if(left!=0)
			return left->find(val);
		else
			return this;
	}
  else if (val>value)
  {
		if(right!=0)
			return right->find(val);
		else
			return this;
	}
	return 0;
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const
{
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
int Node<T>::size()
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
Node<T>* Node<T>::splay(Node<T> *root,Node<T> *pointer)
{
  while(pointer->parent!=0){
		
		if(pointer->parent->value==root->value)
    {
			if(pointer->parent->left && pointer->parent->left->value==pointer->value)
      {
				rot_right(pointer->parent);
			}
      else
				rot_left(pointer->parent);
		}
    else
    {
			Node<T>*p = pointer->parent;
			Node<T>*g = p->parent;
			if(p->left && g->left && pointer->value == p->left->value && p->value==g->left->value)
      {
				rot_right(g);
				rot_right(p);
			}
      else if(p->right && g->right && pointer->value==p->right->value && p->value==g->right->value)
      {
				rot_left(g);
				rot_left(p);
			}
      else if(p->left && g->right && pointer->value==p->left->value && p->value == g->right->value)
      {
				rot_right(p);
				rot_left(g);
			}
      else
      {
				rot_left(p);
				rot_right(g);
			}
		}
	}
	
  return pointer;
}

template <class T>
void Node<T>::print_tree(std::stringstream &aux) const {
	if (parent != 0){
		aux << "\n node " << value;
		aux << " parent " << parent->value;
	}else
		aux << "\n root " << value;
	if (left != 0)
		aux << " left " << left->value;
	if (right != 0)
		aux << " right " << right->value;
	aux << "\n";
	if (left != 0) {
		left->print_tree(aux);
	}
	if (right != 0) {
		right->print_tree(aux);
	}
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
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

template<class T>
class SplayTree
{
  private:
    Node<T> *root;

  public:
    SplayTree();

    void add(T);
    void remove(T);
    bool find(T);
    std::string inorder() const;
    int size();
    bool empty() const;

    std::string print_tree() const;
    std::string preorder() const;
};

template <class T>
SplayTree<T>::SplayTree()
{
  root=0;
}

template <class T>
void SplayTree<T>::add(T val)
{
  if(root==0)
    root=new Node<T>(val);
  else
  {
    Node<T> *change;
    change = root->add(val);
		root = root->splay(root,change);
  }
}

template <class T>
void SplayTree<T>::remove(T val)
{
  if(root!=0)
  {
    if(val==root->value)
    {
			Node<T> *succ = root->succesor();
			if(succ!=0)
      {
				succ->left = root->left;
				succ->right=root->right;
				succ->parent=0;
				if(succ->left)
					succ->left->parent=succ;
				if(succ->right)
					succ->right->parent=succ;
			}
			delete root;
			root=succ;
		}
    else 
    {
			Node<T> *pointer = root->remove(val);
			if (pointer!=0)
				root=root->splay(root,pointer);
		}
  }
}

template<class T>
bool SplayTree<T>::find(T val)
{
	if(root!=0)
  {
		Node<T>* found=root->find(val);
		if (found == 0) 
      return false;
		root=root->splay(root,found);

		return(root->value==val);
	}
  else
		return false;
}

template <class T>
std::string SplayTree<T>::inorder() const
{
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
int SplayTree<T>::size()
{
  return root->size();
}

template <class T>
std::string SplayTree<T>::print_tree() const
{
  std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->print_tree(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string SplayTree<T>::preorder() const
{
  std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
bool SplayTree<T>::empty() const { return (root==0); }

#endif