ANÁLISIS DE COMPLEJIDAD:

loadGraphMat:
  Para cargar la matriz se lee un archivo. Del archivo se lee línea por línea para marcar donde se encuentran las uniones. Esta parte del código es de complejidad O(n) porque se leen n líneas. Por otro lado antes de meter 1's en la matriz se llena con ceros. Para eso se recorre toda la matriz, la cual tiene n*n cantidad de elementos. loadGraphMat es de complejidad 0(n^2) si se cuenta el algoritmo más complejo. Si queremos ser más exactos, juntando ambas complejidades, la complejidad es de O((n^2)+n).

loadGraphList:
  Al igual que en el anterior load se leen n cantidad de líneas. Para ello un loop se repite n veces. Aparte de eso, se tienen que ordenar los vectores de cada índice. Como se usa un insertion sort, el cual es de complejidad O(n^2) y se tiene que hacer para los n índices la complejidad es de O(n^3). Si sumamos la complejidad de la lectura nos quedamos con un O(n^3+n).

DFS:
  La función es recursiva y cuenta con un for para checar todos los nodos adyacentes. La recursión se realiza la cantidad de vértices que tiene el grafo y el for se realiza en total el mismo número de veces que el número de arcos. Por lo tanto se dice que el DFS es O(V+E); siendo v los vértices y e los arcos. Se puede decir también que es O(2n) En este caso se hace otro loop para sacar el camino más corto que se guarda en el stack, el camino en el peor de los casos es O(n). En total se tiene una complejidad de O(3n).

BFS:
  En primera, se recorre un arreglo de valores booleanos de n dimensiones, O(n). Después se tiene un for anidado a otro for,estos se utilizan para comprobar si ya se ha visitado cada vértice adyacente (Edges) de cada vértice (vértices); O(V+E). Después se llama a otra función para sacar el camino más corto por medio de un queue. Los valores del queue son metidos en un arreglo por un proceso O(n). Este arreglo es recorrido para encontrar el camino más corto, el cual en el peor de los casos es O(n). En total se tiene una complejidad de O(6n), o solo O(2n) si se simplifica.