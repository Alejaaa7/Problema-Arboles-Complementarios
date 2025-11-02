#include <iostream>
#include <vector>
using namespace std;

template <typename T>

// EL NODO DEL ÁRBOL:
class BTreeNode {
    public:
        BTreeNode<T>* left;
        BTreeNode<T>* right;
        T data;

        BTreeNode(T d) {
            data = d;
            left = NULL;
            right = NULL;
        };
};

// Se crea una estructura para almacenar una poda
template <typename T>
struct Pruning {
    vector<T> leaves; // las hojas resultantes
    string description; // descripción de la poda

    Pruning(vector<T> l, string desc) {
        leaves = l;
        description = desc;
    } 
};

// AHORA LA CLASE DEL ÁRBOL BINARIO
template <typename T>
class BTree {
    protected:
        BTreeNode<T>* root;

        // método para obtner las hojas recursivamente
        void getLeaves(BTreeNode<T>* r, vector<T>& leaves) {
            if(r == NULL) {
                return;
            }

            // si es solo hoja (no tiene hijos)
            if (r->left == NULL && r->right == NULL) {
                leaves.push_back(r->data); // agrega el valor al final del vector leaves
                return;
            }

            // recorrer los subárboles recursivamente
            getLeaves(r->left, leaves);
            getLeaves(r->right, leaves);
        }

        // Generar podas recursivamente
        void generatePrunings(BTreeNode<T>* node, vector<Pruning<T>>& prunings, string path) {
            // podar subárbol izquierdo
            if (node->left != NULL) {
                BTreeNode<T>* temp = node->left;
                node->left = NULL;

                vector<T> leaves = getLeaves();
                prunings.push_back(Pruning<T>(leaves, "Podar izq. de " + path));

                node->left = temp;

                // recursión en subárbol izquierdo
                generatePrunings(node->left, prunings, path + "->izq");
            }

            // podar subárbol derecho
            if (node->right != NULL) {
                BTreeNode<T>*temp = node->right;
                node->right = NULL;

                vector<T> leaves = getLeaves();
                prunings.push_back(Pruning<T>(leaves, "Podar der. de " + path));

                node->right = temp;

                // recursión en subárbol derecho
                generatePrunings(node->right, prunings, path + "->right");
            }

            // podar ambos subárboles
            if (node->left != NULL && node->right != NULL) {
                BTreeNode<T>* tempL = node->left;
                BTreeNode<T>* tempR = node->right;

                node->left = NULL;
                node->right = NULL;

                vector<T> leaves = getLeaves();
                prunings.push_back(Pruning<T>(leaves, "Podar ambos de " + path));

                node->left = tempL;
                node->right = tempR;
            }

            // Probar podar la izquierda y luego seguir podando la derecha
            if (node->left != NULL && node->right != NULL) {
                BTreeNode<T>*temp = node->left;
                node->left = NULL;

                generatePrunings(node->right, prunings, path + "->der (con izq. ya podado)");

                node->left = temp;
            }

            // Probar podar derecha y luego seguir podando en la izquierda
            if (node->left != NULL && node->right != NULL) {
                BTreeNode<T>* temp = node->right;
                node->right = NULL;

                // Ahora generar más podas en el subárbol izquierdo
                generatePrunings(node->left, prunings, path + "->izq (con der. ya podado)");

                node->right = temp;
            }
        }

        public:
            BTree() {
                this->root = NULL;
            }

            // obtener hojas públicamente
            vector<T> getLeaves() {
                vector<T> leaves;
                getLeaves(this->root, leaves);
                return leaves;
            }

            // generar todas las podas posibles
            vector<Pruning<T>> generateAllPrunings() {
                vector<Pruning<T>> prunings;

                if (this-> root == NULL) {
                    return prunings;
                }

                // primera poda: sin podar (se tiene el árbol completo)
                vector<T> originalLeaves = getLeaves();
                prunings.push_back(Pruning<T>(originalLeaves, "Sin poda"));

                // Podar solo el hijo izquiero de la raíz
                if (this->root->left != NULL) {
                    BTreeNode<T>* temp = this->root->left;
                    this->root->left = NULL;

                    vector<T> leaves = getLeaves();
                    prunings.push_back(Pruning<T>(leaves, "Podar hijo izq. de la raíz"));

                    this->root->left = temp;
                }

                // Podar solo hijo derecho de la raíz
                if (this->root->right != NULL) {
                    BTreeNode<T>* temp = this->root->right;
                    this->root->right = NULL;

                    vector<T> leaves = getLeaves();
                    prunings.push_back(Pruning<T>(leaves, "Podar hijo der. de la raíz"));

                    this->root->right = temp;
                }

                // Podar ambos hijos de la raíz, la raíz se vuelve hoja
                if (this->root->left != NULL && this->root->right != NULL) {
                    BTreeNode<T>* tempL = this->root->left;
                    BTreeNode<T>* tempR = this->root->right;
                    this->root->left = NULL;
                    this->root->right = NULL;

                    vector<T> leaves = getLeaves();
                    prunings.push_back(Pruning<T>(leaves, "POdar ambos hijos de la raíz, o sea convertirla en hoja"));

                    this->root->left = tempL;
                    this->root->right = tempR;                    
                }

                // generar todas las demás podas
                generatePrunings(this->root, prunings, "raíz");

                return prunings;
            }

            BTreeNode<T>* getRoot() {
                return this->root;
            }

            void setRoot(BTreeNode<T>* r) {
                this->root = r;
            }
};

// FUNCIONES AUXILIARES

template <typename T>
void printVector(vector<T> v) {
    cout << "[";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i < v.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]";
}

template <typename T>
bool areEqual(vector<T> v1, vector<T> v2) {
    if (v1.size() != v2.size()) {
        return false;
    }

    for(int i = 0; i < v1.size(); i++) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }
    return true;
}

// CONSTRUCCIÓN DE LOS ÁRBOLES
BTree<int>* buildTree1() {
    BTree<int>* tree = new BTree<int>();
    BTreeNode<int>* root = new BTreeNode<int>(5);

    root->left = new BTreeNode<int>(7);
    root->right = new BTreeNode<int>(4);

    root->left->left = new BTreeNode<int>(3);
    root->left->right = new BTreeNode<int>(-13);
    root->right->left = new BTreeNode<int>(-20);
    root->right->right = new BTreeNode<int>(-1);

    root->left->left->left = new BTreeNode<int>(8);
    root->left->right->right = new BTreeNode<int>(12);
    root->right->left->left = new BTreeNode<int>(10);
    root->right->left->right = new BTreeNode<int>(6);

    root->right->left->right->left = new BTreeNode<int>(1);
    root->right->left->right->right = new BTreeNode<int>(2);

    tree->setRoot(root);
    return tree;
}

BTree<int>* buildTree2() {
    BTree<int>* tree = new BTree<int>();
    BTreeNode<int>* root = new BTreeNode<int>(6);

    root->left = new BTreeNode<int>(2);
    root->right = new BTreeNode<int>(4);

    root->right->left = new BTreeNode<int>(-1);
    root->right->right = new BTreeNode<int>(5);

    tree->setRoot(root);
    return tree;
}

// ALGORITMO PRINCIPAL

struct Result {
    vector<int> leaves;
    int numLeaves;
    string pruning1;
    string pruning2;
};

Result findOptimalPruning(BTree<int>* tree1, BTree<int>* tree2) {
    cout << "GENERANDO LAS PODAS POSIBLES" << endl;

    // General las podas del árbol 1
    cout << "Podas del árbol 1: " << endl;
    vector<Pruning<int>> prunings1 = tree1->generateAllPrunings();
    cout << "Total de podas generadas: " << prunings1.size() << endl;

    // Generar las podas del árbol 2
    cout << "Podas del árbol 2: " << endl;
    vector<Pruning<int>> prunings2 = tree2->generateAllPrunings();
    cout << "Total de podas generadas: " << prunings2.size() << endl;

    // Buscar la mejor combinación:
    Result best;
    best.numLeaves = 0;
    int totalCombinations = prunings1.size() * prunings2.size();
    cout << "COMPARANDO LAS COMBINACIONES" << endl;
    cout << "Total de combinaciones a evaluar: " << totalCombinations << endl;

    int found = 0;
    for(int i = 0; i < prunings1.size(); i++) {
        for (int j = 0; j < prunings2.size(); j++) {
            // si las hojas son iguales
            if (areEqual(prunings1[i].leaves, prunings2[j].leaves)) {
                int numLeaves = prunings1[i].leaves.size();
                found++;

                // Mostrar todas las soluciones encontradas
                cout << "\n Solución " << found << ", con " << numLeaves << " hojas: ";
                printVector(prunings1[i].leaves);
                cout << endl;
                cout << "Árbol 1: " << prunings1[i].description << endl;
                cout << "Árbol 2: " << prunings2[j].description << endl;

                // Guardar solo si es mejor (más hojas)
                if (numLeaves > best.numLeaves) {
                    best.leaves = prunings1[i].leaves;
                    best.numLeaves = numLeaves;
                    best.pruning1 = prunings1[i].description;
                    best.pruning2 = prunings2[j].description;

                    cout << "Solución encontrada con " << numLeaves << " hojas: ";
                    printVector(best.leaves);
                    cout << endl;
                    cout << "Árbol 1: " << best.pruning1 << endl;
                    cout << "Árbol 2: " << best.pruning2 << endl;
                }
            }
        }
    }

    cout << "Total de soluciones complementarias encontradas: " << found << endl;
    if (found > 0) {
        cout << "La óptima, es decir la de más hojas, tiene " << best.numLeaves << " hojas" << endl;
    }

    return best;
}

// EL MAIN

int main() {
    cout << "SOLUCIÓN PROBLEMA ÁRBOLES COMPLEMENTARIOS CON PODA ÓPTIMA" << endl;

    // Construir árboles
    cout << "Se construyen los árboles de la foto del tablero" << endl;
    BTree<int>* tree1 = buildTree1();
    BTree<int>* tree2 = buildTree2();
    
    // Mostrar las hojas ORIGINALES
    cout << "Hojas originales, sin poda: " << endl;
    vector<int> leaves1 = tree1->getLeaves();
    vector<int> leaves2 = tree2->getLeaves();

    cout << "Árbol 1: ";
    printVector(leaves1);
    cout << " (con " << leaves1.size() << " hojas)" << endl;

    cout << "Árbol 2: ";
    printVector(leaves2);
    cout << " (con " << leaves2.size() << " hojas)" << endl;

    if (areEqual(leaves1, leaves2)) {
        cout << "Los árboles YA son complementarios sin podar! :)" << endl;
    }
    else{
        cout << "Los árboles NO son complementarios, se requiere poda." << endl;
    }

    // Entonces se tiene que buscar una poda óptima
    cout << "Buscando poda óptima" << endl;
    Result result = findOptimalPruning(tree1, tree2);

    // Mostrar el resultado final
    cout << "RESULTADO FINAL: " << endl;

    if (result.numLeaves > 0) {
        cout << "Solución Óptima encontrada :)" << endl;
        cout << "Máximo número de hojas complementarias: " << result.numLeaves << endl;
        cout << "Hojas resultantes: ";
        printVector(result.leaves);
        cout << endl;

        cout << "Podas necesarias: " << endl;
        cout << "Árbol 1: " << result.pruning1 << endl;
        cout << "Árbol 2: " << result.pruning2 << endl;
    }
    else{
        cout << "No se encontró ninguna combinación de podas complementarias :(" << endl;
    }

    return 0;
}
