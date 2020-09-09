#ordenaSeleccion
Tiene un for loop anidado en otro for. Al ser ambos dependientes de i se toma como una complejidad O(n^2)

#ordenaBurbuja
La función se repite n veces teniendo un ciclo anidado que se repite n veces menos el número de iteración. Teniendo en cuenta el peor caso ambos ciclos son equivalentes a n haciendo del algoritmo uno con complejidad O(n^2)

#ordenaMerge
En el ordenamiento con Merge Sort se tres procesos principales. El primero divide el arreglo y tarda un tiempo constante pues solo calcula low, high y mid. El segundo ordena los subgrupos en cada nivel del arbol O(1). El proceso se hace cada vez más corto conforme bajamos en el nivel del árbol, dandonos una complejidad de logn. Por último se mezclan los subgrupos, lo que hace que el algoritmo recorra todo el arreglo; O(n). Juntando estas complejidades nos da que la complejidad del Merge sort es de O(n*log(n)

#busqSecuencial
La busqueda secuencial recorre el vector aumentando la posición a uno por vez. En el peor de los casos tendría que recorrer todo el arreglo por lo que es O(n).

#busqBinaria
En cada repetición el rango donde puede estar el elemento se divide mínimo a la mitad lo que reduce la cantidad de iteraciones necesarias. Por eso es una complejidad de O(log(n)).