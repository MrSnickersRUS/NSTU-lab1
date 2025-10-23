#include "tree.h"
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

// Конструктор АВЛ-дерева
AVLTree::AVLTree() : root(nullptr) {}

// Деструктор АВЛ-дерева
AVLTree::~AVLTree() {
    clearTree(*this);
}

// Вспомогательная функция для рекурсивного удаления узлов
void clearTreeHelper(AVLNode* node) {
    if (node == nullptr) return;
    clearTreeHelper(node->left);
    clearTreeHelper(node->right);
    delete node;
}

// Очищает дерево
void clearTree(AVLTree& tree) {
    clearTreeHelper(tree.root);
    tree.root = nullptr;
}

// Возвращает высоту узла
int getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

// Вычисляет баланс узла
int getBalance(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Поворот вправо
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Поворот влево
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Универсальная функция балансировки АВЛ-дерева
// Работает для любых операций (вставка, удаление)
AVLNode* rebalance(AVLNode* node) {
    int balance = getBalance(node);

    // Левый перевес
    if (balance > 1) {
        // Левый-Правый случай (LR): требуется двойной поворот
        if (getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        // Левый-Левый случай (LL): один правый поворот
        return rotateRight(node);
    }

    // Правый перевес
    if (balance < -1) {
        // Правый-Левый случай (RL): требуется двойной поворот
        if (getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        // Правый-Правый случай (RR): один левый поворот
        return rotateLeft(node);
    }

    return node;
}

// Вставка элемента в АВЛ-дерево
AVLNode* insert(AVLNode* node, const string& value) {
    if (!node) {
        return new AVLNode{value, 1, nullptr, nullptr};
    }

    if (value < node->data) {
        node->left = insert(node->left, value);
    } else if (value > node->data) {
        node->right = insert(node->right, value);
    } else {
        return node; // Дубликаты не допускаются
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Балансировка после вставки
    return rebalance(node);
}

// Вставка в дерево
void insertToAVL(AVLTree& tree, const string& value) {
    tree.root = insert(tree.root, value);
}

// Поиск элемента в дереве
bool search(AVLNode* node, const string& value) {
    if (!node) {
        return false;
    }
    if (value == node->data) {
        return true;
    }
    if (value < node->data) {
        return search(node->left, value);
    }
    return search(node->right, value);
}

bool searchInAVL(const AVLTree& tree, const string& value) {
    return search(tree.root, value);
}

// Обход дерева (в порядке возрастания)
void inorderTraversal(AVLNode* node) {
    if (!node) {
        return;
    }
    inorderTraversal(node->left);
    cout << node->data << " ";
    inorderTraversal(node->right);
}

void readAVL(const AVLTree& tree) {
    inorderTraversal(tree.root);
    cout << endl;
}

// Сохраняет АВЛ-дерево в файл (обход в порядке возрастания)
void saveAVLToFileHelper(AVLNode* node, ofstream& outFile) {
    if (!node) return;
    saveAVLToFileHelper(node->left, outFile);
    outFile << node->data << endl;
    saveAVLToFileHelper(node->right, outFile);
}

void saveAVLToFile(const AVLTree& tree, const string& filePath) {
    ofstream outFile(filePath);
    if (!outFile) {
        throw runtime_error("Ошибка: невозможно открыть файл для записи");
    }
    saveAVLToFileHelper(tree.root, outFile);
    outFile.close();
}

// Загружает АВЛ-дерево из файла
void loadAVLFromFile(AVLTree& tree, const string& filePath) {
    ifstream inFile(filePath);
    if (!inFile) {
        throw runtime_error("Ошибка: невозможно открыть файл для чтения");
    }
    clearTree(tree); // Правильно очищаем дерево перед загрузкой
    string value;
    while (getline(inFile, value)) {
        insertToAVL(tree, value);
    }
    inFile.close();
}

// Удаляет узел из дерева
AVLNode* deleteNode(AVLNode* root, const string& value) {
    if (!root) {
        return root;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            AVLNode* temp = root->right;
            while (temp->left) {
                temp = temp->left;
            }
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (!root) {
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Балансировка после удаления
    return rebalance(root);
}

// Удаляет элемент из дерева
void deleteFromAVL(AVLTree& tree, const string& value) {
    tree.root = deleteNode(tree.root, value);
}