ANÁLISIS DE COMPLEJIDAD

bool isTree(); 
  Usa un for anidado dentro de otro for para determinar la existencia de una raíz. El primer for depende del número de nodos del grafo, el segundo del número de nodos adyacentes. En el peor de los casos es de complejidad O(n^2)

std::string topologicalSort();
  Este metodo usa recursividad para navegar entre las ramas. En casos normlaes su complejidad es O(logn) porque cada rama acorta el recorrido. En el peor de los casos el grafo es una sola línea y se recorre con complejidad O(n).

bool bipartiteGraph();
  Utiliza un for que llama recursivamente a la función. El for depende del número de nodos, n y la recursividad de los nodos adyacentes. La recursividad acorta el recorrido pero el for hace que se repita n veces. Por eso la complejidad es de O(nlogn)