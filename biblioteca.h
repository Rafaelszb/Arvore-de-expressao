#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <iostream>
#include <vector>

using namespace std;

enum TipoNode {
    OPERANDO,
    OPERADOR
};

struct Node {
    char key;
    Node* left;
    Node* right;
    TipoNode tipo;
};

int encontrarOperadorPrincipal(const string& expressao) {
    int nivelParenteses = 0;

    for (int i = expressao.length() - 1; i >= 0; i--) {
        char c = expressao[i];

        if (c == ')') nivelParenteses++;
        else if (c == '(') nivelParenteses--;
        else if (nivelParenteses == 0 && (c == '+' || c == '-')) {
            return i;
        }
    }
    nivelParenteses = 0;
    for (int i = expressao.length() - 1; i >= 0; i--) {
        char c = expressao[i];

        if (c == ')') nivelParenteses++;
        else if (c == '(') nivelParenteses--;
        else if (nivelParenteses == 0 && (c == '*' || c == '/')) {
            return i;
        }
    }

    return -1;
}

string removerParentesesExternos(const string& expressao) {
    if (expressao.empty()) return expressao;
    if (expressao.front() == '(' && expressao.back() == ')') {
        int nivelParenteses = 0;
        for (int i = 0; i < expressao.length(); i++) {
            if (expressao[i] == '(') nivelParenteses++;
            if (expressao[i] == ')') nivelParenteses--;

            if (nivelParenteses == 0 && i < expressao.length() - 1)
                return expressao; // Tem algo fora dos parênteses
        }
        return expressao.substr(1, expressao.length() - 2); // Retorna a expressao sem o primeiro e o ultimo caractere "(" e ")"
    }
    return expressao;
}

void montar_string(const string& expressao, Node*& node) {
    string expr = removerParentesesExternos(expressao);
    cout<<expr<<endl;
    if (expr.empty()) return;

    int pos = encontrarOperadorPrincipal(expr);

    node = new Node();
    node->left = nullptr;
    node->right = nullptr;

    if (pos != -1) {
        node->key = expr[pos]; "+";
        node->tipo = TipoNode::OPERADOR;

        string esquerda = expr.substr(0, pos);
        string direita = expr.substr(pos + 1);

        montar_string(esquerda, node->left);
        montar_string(direita, node->right);
    }
    else {
        node->tipo = TipoNode::OPERANDO;
        node->key = expr[0];
    }
}


void printPreOrder(Node* node) {
    if (!node) return;
    cout << node->key << " ";
    printPreOrder(node->left);
    printPreOrder(node->right);
}


#endif
