#include "biblioteca.h"

int main() {
    Node *root = new Node();
    montar_string("((10*3)+(40/(-2)))*2", root);

    // + + 5 5 + 5 5
    printPreOrder(root);
cout << "Resultado: " << executar_arvore(root) << endl; // 19.8

    return 0;
}