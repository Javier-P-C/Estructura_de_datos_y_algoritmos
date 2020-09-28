Análisis de complejidad
void clear():
  Como tiene que recorrer todo la lista para borrar los elementos siempre es de complejidad lineal O(n)

void add(T):
  Al agregar un elemento al final de la lista tiene que recorrer toda las lista por lo que es de complejidad lineal O(n)
     
int find(T):
  En el peor de los casos el valor buscado se encuentra al final de la lista por lo que lo vuelve O(n)
    
void update(int,T):
  En el peor de los casos el índice recibido es el último. Al tener que recorrer la lista completa la complejidad es O(n)

T remove(int):
  En el peor de los casos el índice recibido es el último. Al tener que recorrer la lista completa la complejidad es O(n)

T removeFirst():
  Como elimina el primer elemento siempre se repite una sola vez. Su complejidad es constante O(1)