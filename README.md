# ÁRBOLES COMPLEMENTARIOS CON PODA ÓPTIMA

**Problema:** Determinar cómo podar dos árboles binarios para hacerlos complementarios maximizando el número de hojas.

## Definición del Problema

Como se ha visto en clase, dos árboles binarios son complementarios si sus hojas leídas de izquierda a derecha son las mismas.

## Árboles de Ejemplo

![Árboles del tablero](foto_arboles.jpg)

- En el árbol de la izquierda, las hojas originales son: [8, 12, 10, 1, 2, -1]
- En el árbol de la derecha, las hojas originales son: [2, -1, 5]

## Solución encontrada

En este caso, el programa encuentra 9 combinaciones de podas que hacen los árboles complementarios. Donde también se encuentra la solución óptima pedida, obtenerlos con el mayor número de hojas:

### Mejor Solución:
- Hojas resultantes: [2, -1] (2 hojas)
- Poda Árbol 1: Podar: root->left, luego root->right->left->left y finalmente root->right->left->right->left.
- Poda Árbol 2: Podar el "hijo" derecho del "hijo" derecho de la raíz.

## Estructuras de Datos Utilizadas

Se implementaron bases vistas y programadas en clase, para:

### 1. Clase `BTreeNode<T>`
```cpp
template
class BTreeNode {
    T data;
    BTreeNode* left;
    BTreeNode* right;
};
```
- Representa un nodo del árbol binario.
- Contiene el dato y punteros a hijos izquierdo y derecho.
- Usa templates para ser genérico.

### 2. Clase `BTree<T>`
```cpp
template
class BTree {
    protected:
        BTreeNode* root;
        void getLeaves(BTreeNode* r, vector& leaves);
        voudgeneratePrunings(BTreeNode* node, ...);
    public:
        vector getLeaves();
        vector<Pruning> generateAllPrunings();
};
```
- Árbol binario completo con métdoos públicos y protegidos.
- Métodos protegidos: funciones recursivas auxiliares.
- Métodos públicos: para obtener hojas y generar podas.

### 3. Struct `Pruning<T>`
```cpp
template
struct Pruning {
    vector leaves;
    string description;
};
```
- Almacena cada configuración de poda posible.
- Facilita la comparación entre podas.

### 4. Struct `Result`
```cpp
struct Result {
    vector leaves;
    int numLeaves;
    string pruning1;
    string pruning2;
};
```
- Empaqueta la solución final.
- Almacena la mejor combinación encontrada.

### 5. Vector (STL)
- `vector<T> para almacenar hojas en orden.
- `vector<Pruning<T>>` para listar todas las podas posbiles
- Permite el manejo dinámico del tamaño.

### 6. Recursión (Pila implícita)
- Recorrido para obtener hoajs de izquierda a derecha.
- Generación exhaustiva de podas explorando todos los niveles.
- Combinaciones de podas múltiples.

## Resumen Algoritmo

### 1. Paso 1: Generar todas las podas posibles
Para cada árbol, explora:
1. Sin podar, es decir, el árbol completo.
2. Podar "hijo" de la izquierda de cada nodo.
3. Podar "hijo" de la derecha de cada nodo.
4. Podar ambos hijos de cada nodo.
5. Combinaciones, es decir, podar un lado y seguir podando en el otro.
```cpp
void generatePrunings(BTreeNode* node, vector<Pruning>& prunings, string path) {
    // Probar: podar izquierda
    //         podar derecha
    //         podar ambos
    // Recursión en subárboles
    // Combinaciones
}
```

### Paso 2: Comparar todas las combinaciones
Algo de la forma:

Para cada poda P1 del árbol 1:
    Para cada poda P2 del árbol 2:
        Si hojas(P1) == hojas(P2):
            Es una solución válida
            Si tiene más hojas que la mejor actual:
                Actualizar la mejor solución

Complejidad: 0(p1 x p2, x h)
- p1, p2 = número de podas de cada árbol.
- h = longitud de las hojas (para comparación)

### Paso 3: Retornar la Solución Óptima
- Se selecciona la combinación con MÁS HOJAS.
- Se retorna con una breve descripción de cómo podar.
- Se indica el número total de podas generadas por cada árbol.
- Se indica el número de combinaciones evaluadas.

Soluciones complementarias encontradas: 9
Solución Óptima: 2 hojas [2, -1]

## Compilación y Ejecución
Para compilar:
```bash
g++ -o arboles problema_arboles.cpp
```
Para ejecutar:
```bash
./arboles
```

En Windows:
```bash
g++ -o problema_arboles.exe problema_arboles.cpp
problema_arboles.exe
```

