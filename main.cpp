#include "biblioteca.h"

int main() {
    Node *raiz = new Node();
    string expressao = "((-53+1)*1)/2";

    montar_string(expressao, raiz);

    cout << "Árvore:\n";
    
    print(raiz);

    cout << "\n\nResultado: " << executar_arvore(raiz) << endl;


    return 0;
}
