#ifndef TREE_H
#define TREE_H

#include <string>

using namespace std;

// Структура для узла АВЛ-дерева
struct AVLNode {
    string data;
    int height;
    AVLNode* left;
    AVLNode* right;
};

// Структура для АВЛ-дерева
struct AVLTree {
    AVLNode* root = nullptr;
    
    // Конструктор
    AVLTree();
    // Деструктор
    ~AVLTree();
};

void insertToAVL(AVLTree& tree, const string& value);
void clearTree(AVLTree& tree);
bool searchInAVL(const AVLTree& tree, const string& value);
void deleteFromAVL(AVLTree& tree, const string& value);
void readAVL(const AVLTree& tree);
void loadAVLFromFile(AVLTree& tree, const string& filename);
void saveAVLToFile(const AVLTree& tree, const string& filename);

#endif
