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
    string key; 
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
        for (int i = 0; i < (int)expressao.length(); i++) {
            if (expressao[i] == '(') nivelParenteses++;
            else if (expressao[i] == ')') nivelParenteses--;
            if (nivelParenteses == 0 && i < (int)expressao.length() - 1)
                return expressao; 
        }
        return expressao.substr(1, expressao.length() - 2);
    }
    return expressao;
}

void montar_string(const string& expressao, Node*& node) {
    string expr = removerParentesesExternos(expressao);
    cout << expr << endl;
    if (expr.empty()) return;

    int pos = encontrarOperadorPrincipal(expr);
    node = new Node();
    node->left = nullptr;
    node->right = nullptr;

    if (pos != -1) {
        node->key = string(1, expr[pos]);
        node->tipo = OPERADOR;

        string esquerda = expr.substr(0, pos);
        string direita  = expr.substr(pos + 1);

        montar_string(esquerda,  node->left);
        montar_string(direita,   node->right);
    } else {
        node->tipo = OPERANDO;
        node->key = expr;  
    }
}

void printPreOrder(Node* node) {
    if (!node) return;
    cout << node->key << " ";
    printPreOrder(node->left);
    printPreOrder(node->right);
}

bool isNumero(const string& s) {
    if (s.empty()) return false;

    bool temPonto = false;
    bool temDigito = false;
    int sinal = 0;

    if (s[0] == '-' || s[0] == '+') {
        sinal = 1;
    }

    for (int i = sinal; i < s.length(); i++) {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            temDigito = true;
        } else if (c == '.') {
            if (temPonto) return false;
            temPonto = true;
        } else {
            return false;
        }
    }

    return temDigito;
}

double executar_arvore(Node* node) {
    if (node == NULL) return 0;

    if (node->tipo == OPERANDO) {
        if (isNumero(node->key)) {
            return stod(node->key); // converte string para double
        } else {
            return 0;
        }
    }

    double a = executar_arvore(node->left);
    double b = executar_arvore(node->right);

    if (node->key == "+") return a + b;
    if (node->key == "-") return a - b;
    if (node->key == "*") return a * b;
    if (node->key == "/") return b != 0 ? a / b : 0;

    return 0;
}



#endif
