Análisis de Complejidad

void addFirst(T)
  Es constante porque no tiene que iterar para encontrar el índice. Se trabaja con el apuntador head y realiza una vez el proceso, O(1).

void add(T)
  Es constante porque no tiene que iterar para encontrar el índice. Solo se trabaja con el apuntador tail por lo que se realiza una vez el proceso, O(1).

void removeFirst()
  Es constante porque no tiene que iterar para encontrar el ínidce. Se trabaja con el apuntador head y realiza una vez el proceso, O(1).

int find(T) const
  En el peor de los casos el valor se encuentra al en la última posición de la lista. Com no hay manera de saberlo sino hasta recorrer todos los nodos la complejidad es lineal, O(n);

void update(int,T)
  En el peor de los casos se tiene que recorrer toda la lista para llegar al índice por lo que es lineal, O(n)
  
void remove(int)
  Para llegar al índice en el peor de los casos se recorre toda la lista por lo que es lineal O(n)