Análisis de complejidad:
void add(T):
  La función debe recorrer una rama del árbol hasta llegar a una hoja. En teoría el árbol no se va a degenerar debido a las continuas rotaciones. En la práctica se puede dar el caso de un árbol degenerado de una sola rama. Esto le da una complejidad linel en el peor de los casos, O(n). Pero en la mayoría de los casos se mantiene en complejidad logaritmíca porque recorre una sola rama, O(log(n))

void remove(T):
  Remove tiene la misma situación que add(). En la mayoría de los casos la complejidad será O(log(n)) porque va recorriendo solo la rama que conduce al elemento. Sin embargo, en el caso extremo de ser un árbol degenerado sería O(n).

bool find(T):
  Ocurre lo mismo que con las anteriores porque tiene que buscar un elemento siguiendo una sola rama. Normalmente es O(log(n)) en el peor de los casos O(n).

std::string inorder() const:
  Apesar de que recorre todo el árbol es O(log(n)) normalmente debido a que lo hace por medio de recursividad, por lo que visita dos varias ramas a la vez en una misma iteración. Aunque en el caso de un árbol degenerado es de complejidad lineal O(n).

int size():
  Al igual que inorder(), size() aprovecha la recursividad para visitar varias ramas en una iteración. Es por tanto O(log(n)) generalmente y O(n) en el peor de los casos.