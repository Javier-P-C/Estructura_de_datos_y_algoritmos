Análisis de Complejidad:

void add(T):
  Para añadir un elemento nuevo al árbol se debe llegar a una hoja. Por lo que se recorre una rama del árbol hasta la punta. En el peor de los casos el árbol queda degenerado y todos los elementos quedan en una misma rama. Al tener que recorrer los n elementos su complejidad es linela O(n). 

std::string visit():
  Este método llama a cuatro métodos del nodo que tienen que recorrer todos los elementos para poder poner los valores en un stringstream: preorder(std::stringstream&), inorder(std::stringstream&) y postorder(std::stringstream&). Cada uno de estos métodos es de complejidad lineal, O(n). visit() tambien llama a levelByLevel(std::stringstream&) el cual recorre el árbol n veces para imprimir cada nivel, tiene complejidad de O(n^2) por eso. Juntando todas las complejidades vist() es de O(3n+n^2), si solo tomamos en cuenta la función recursiva más compleja entonces es de O(n^2).

int height():
  Igual que en add() si el árbol es degenerado tiene que recorrer todos los elementos en una rama. En el peor de los casos es lineal O(n).

std::string ancestors(T):
  En el peor de los casos recibe el valor de una hoja y el árbol queda degenerado. Se recorrerían todos los elementos, dando una complejidad de O(n).

int whatlevelamI(T):
  En el peor de los casos recibe el valor de una hoja y el árbol queda degenerado. Se recorrerían todos los elementos, dando una complejidad de O(n).

bool empty():
  Solo retorna el valor booleano de una condición. Siempre es O(1).
   
~BST():
  Llama al método removeChilds() de la clase Node. Este método recorre en el peor de los casos todos los elemetos en una sola rama para borrarlos. Es lineal O(n)


