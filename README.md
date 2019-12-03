# Grafos

Algoritmos y Estructuras de Datos 1  
(Curso 2018 - 2019)

Grado en Ingeniería Informática  
Universidad de Murcia

Por: Juan Francisco Carrión Molina

Profesor: Norberto Marín Pérez

## Memoria de las prácticas

### 1. Resolución de problemas: análisis, diseño y eficiencia

#### 401

Implementación del algoritmo de búsqueda primero en profundidad (BPP) con almacenamiento del grafo mediante matriz de adyacencia y una tabla de nodos visitados.

La representación mediante matriz de adyacencia guarda las aristas entre dos nodos. Es el mejor método de almacenamiento para casos en los que hay muchas aristas entre los nodos. En el caso contrario, se desaprovecha mucha memoria. Las operaciones de acceso y modificación de aristas son de tiempo constante, mientras que los recorridos son proporcionales al número total de nodos del grafo.

El algoritmo de BPP utiliza un primer bucle para lanzar la búsqueda por todos los nodos y un segundo que recorre los adyacentes a los primeros. Así, la eficiencia del algoritmo BPP de cada caso con matrices de adyacencia es del orden del número total de nodos del grafo al cuadrado **O(n<sup>2</sup>)**.

#### 402

Implementación del algoritmo de búsqueda primero en anchura (BPA) y ajuste de las operaciones de lectura y escritura con respecto al problema anterior. Se utiliza la misma estructura de datos (matriz de adyacencia y tabla de nodos visitados) para almacenar el grafo y lanzar el algoritmo, por lo que la eficiencia del modo de almacenamiento es la misma.

La eficiencia del algoritmo de BPA es, debido a su construcción con bucles, es del orden del número total de nodos del grafo al cuadrado **O(n<sup>2</sup>)**.

#### 403

Ajuste de la operación de lectura `leer()` a la entrada proporcionada. Cada sitio se representa mediante un nodo en un grafo y las uniones directas mediante sus aristas. El grafo se representa utilizando una variable global `G` de tipo tabla de listas de enteros (representación con listas de adyacencia). Esta variable se inicializa vacía en la operación de lectura.

Además se utilizan una tabla de booleanos `visitado` para indicar los nodos que ya han sido visitados (se inicializa vacía al lanzar el recorrido), una cola de enteros `camino` para representar el camino seguido en un lanzamiento y varios booleanos de control.

La operación `todosvisitados()` devuelve true si todos los nodos han sido visitados o si la variable de control `todosvisitadosv` se utiliza. Esta operación se utilizará para saber si, en un lanzamiento, es necesario retroceder en el camino o ya se han visitado todos los nodos. La variable de control `todosvisitadosv` se inicializa a false en el lanzamiento y se utiliza poniéndose a `true` cuando hemos llegado al sitio de salida del laberinto (similar al `break` en un `for`).

La operación `lanzar()` inicializa distintas variables, lanza la búsqueda sobre el primer sitio (nodo 0) e imprime los resultados.

La operación de búsqueda `buscar()`, parte más relevante del algoritmo, marca como visitado el nodo sobre el que está buscando, lo inserta en el camino y, para cada nodo adyacente al actual, realiza una serie de comprobaciones para llamarse a sí misma de forma iterativa continuando el recorrido o añadiendo al camino un nodo (lo que en el laberinto es volver al sitio anterior).

Dado que estamos utilizando listas de adyacencia, la eficiencia de esta operación es proporcional al número total de nodos y al número de nodos adyacentes a cada nodo de media **O(n + a)**.

#### 409

Este ha sido sin duda el más difícil de implementar. Tras desarrollar mi propio algoritmo que solo fallaba insertando dos páginas simples iguales de vez en cuando, decidí utilizar el algoritmo de Warshall.

El algoritmo de Warshall calcula si existe un camino entre dos nodos para todos los pares de nodos de un grafo. Así, el planteamiento de que dos páginas originales pueden agruparse en una simple si ambas apuntan a la otra, es equivalente a utilizar el algoritmo de manera que si dos nodos apuntan cada uno al otro, tenemos una página simple.

Almacenamos el grafo compuesto por las páginas originales y las referencias a otras páginas en una matriz de adyacencia `M`.

La operación `leer()` inicializa las matrices, la lista de páginas simples y el resto de variables para cada caso y, después, lee las páginas originales y sus referencias.

A continuación se aplica `warshall()` para calcular en `A` las conexiones entre nodos de `M`.

La clave del código está en `lanzar().` En esta operación, se recorren todos los pares de nodos y se comprueba si hay caminos entre el primero y el segundo y viceversa. En caso de haberlos, `procesarOriginales()` se encarga de averiguar si alguna de las páginas originales ya está en una simple (mediante el array `V`, que indica un entero con dicha página simple), en cuyo caso se añaden a la misma, y en caso contrario, (`V` indica `-1` en este caso) se crea una nueva página simple.

Destacar que las páginas simples se listan en un tipo `vector` para habilitar el acceso aleatorio y dinámico.

Una vez terminado de procesar, `acabarSimples()` hace un barrido y crea páginas simples para los nodos restantes. También ordena cada página simple y elimina las originales repetidas. Por último se ordena la lista de páginas simples y se escribe.

Las operaciones de acceso y modificación de cada par de nodos son directas al utilizar matriz de adyacencia. El algoritmo de Warshall utiliza tres bucles que recorren todos los nodos, por lo que su eficiencia es proporcional al número de páginas originales al cubo **O(n<sup>3</sup>)**. La operación `lanzar()` tiene una eficiencia proporcional también a este número pero al cuadrado al tener dos bucles **O(n<sup>2</sup>)**.

### 2. Conclusiones

Utilizar el lenguaje C++ y sus diferencias con respecto a otros lenguajes, así como desarrollar soluciones a problemas de la teoría de Grafos, ha sido un reto muy interesante.

Aunque no he podido realizar más ejercicios del mínimo por el tiempo, esta actividad me ha llevado a utilizar también procesos de desarrollo de programas como especificación de la idea de los algoritmos, sus estructuras de datos, etc.

En muchas ocasiones la clave está en transformar lo visto en clase a lo que pide el problema, por lo que se requiere desarrollar un nivel de abstracción bastante amplio.

Trabajar en este nivel puede ser más sencillo o más complicado de la cuenta según qué casos. Normalmente, usamos programación estructurada, hacemos uso de variables, de bucles, de funciones complejas, etc. y así solucionamos cualquier necesidad, lo que es viable gracias al amplio abanico de posibilidades de C++.

También es necesario destacar que ha habido momentos de desesperación con respuestas erróneas e incluso respuestas que parecían correctas pero eran incorrectas a los ojos de Mooshak.

En general, mi opinión de la actividad es que en muchos casos se destina mucho esfuerzo a comprender cómo está construido el problema y la historia ficticia, y esto resta tiempo del trabajo práctico en programación y en teoría de Grafos. Por otro lado, me ha generado momentos constructivos y en los que he tenido que abstraerme e idear soluciones, conociendo situaciones en las que no había estado antes, por lo que ha sido también muy enriquecedor.
