#include "biblioteca.h"

int main() {
    Node *root = new Node();
    montar_string("((5+5)+(5+5))*1", root);

    // + + 5 5 + 5 5
    printPreOrder(root);


    return 0;
}