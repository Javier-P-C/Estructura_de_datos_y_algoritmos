#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>


template <class T> class BST;

template <class T>
class TreeNode {
private:
	T value;
	TreeNode *left, *right;

	TreeNode<T>* predecessor();

public:
	TreeNode(T);
	TreeNode(T, TreeNode<T>*, TreeNode<T>*);
	void add(T);
	bool find(T);
	void remove(T);
	void removeChilds();
	void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;

	friend class BST<T>;
};

template <class T>
TreeNode<T>::TreeNode(T val):value(val),left(0),right(0) {}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri):value(val),left(le),right(ri) {}

template <class T>
void TreeNode<T>::add(T val) {
  if(val<value)
  {
    if(left != 0)
    {
      left->add(val);
    }
    else
    {
      left = new TreeNode<T> (val);
    }
  }
  else if(val>value)
  {
    if(right != 0)
    {
      right->add(val);
    }
    else
    {
      right = new TreeNode<T> (val);
    }
  }
}

template <class T>
bool TreeNode<T>::find(T val) {
  if(val == value)
  {
    return true;
  }
  else if(val < value)
  {
    return(left!=0 && left->find(val));
  }
  else if(val > value)
  {
    return (right!=0 && right->find(val));
  }
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
  TreeNode<T> *succ;
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
      {
        return left->remove(val);
      }
    }
  }
  else if(val > value)
  {
    if(right!=0)
    {
      if(val == right->value)
      {
        TreeNode<T> *old;
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
      {
        return right->remove(val);
      }
    }
  }
}

template <class T>
void TreeNode<T>::removeChilds() {
  //std::cout<<"Llego"<<std::endl;
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
class BST {
private:
	TreeNode<T> *root;

public:
	BST();
	~BST();
	bool empty() const;
	void add(T);
	bool find(T) const;
	void remove(T);
	void removeAll();
	std::string inorder() const;
	std::string preorder() const;
};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
BST<T>::~BST() {
	removeAll();
}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

template<class T>
void BST<T>::add(T val) {
  if(empty())
  {
    root = new TreeNode<T> (val);
  }
  else
  {
    root->add(val);
  }
}

template <class T>
void BST<T>::remove(T val) {
  TreeNode<T> *succ;
  if(val == root->value)
  {
    succ = root->predecessor();
    if(succ != 0)
    {
      succ->left = root->left;
      succ->right = root->right;
    }
    delete root;
    root = succ;
  }
  else
  {
    root->remove(val);
  }
}

template <class T>
void BST<T>::removeAll() {
  root->removeChilds();
  delete root;
  root = 0;
}

template <class T>
bool BST<T>::find(T val) const {
  return root->find(val);
}

template <class T>
std::string BST<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

#endif /* BST_H_ */
