#ifndef STACK_H
#define STACK_H

#include <string>

using namespace std;

// Структура для узла стека
struct StackNode {
    string data;
    StackNode* next;
};

// Структура для хранения всех стеков
struct Stack {
    StackNode* top = nullptr;
    
    // Конструктор
    Stack();
    // Деструктор
    ~Stack();
};

void stackPush(Stack& stackk, const string& value);
string stackPop(Stack& stackk);
bool isStackEmpty(const Stack& stackk);
void clearStack(Stack& stackk);
void loadStackFromFile(Stack& stackk, const string& filename);
void saveStackToFile(const Stack& stackk, const string& filename);

#endif
