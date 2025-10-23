#include "stack.h"
#include <iostream>
#include <fstream>

using namespace std;

// Конструктор стека
Stack::Stack() : top(nullptr) {}

// Деструктор стека
Stack::~Stack() {
    clearStack(*this);
}

// Добавляет элемент в стек
void stackPush(Stack& stackk, const string& value) {
    StackNode* newNode = new StackNode{value, stackk.top};
    stackk.top = newNode;
}

// Извлекает элемент из стека
string stackPop(Stack& stackk) {
    if (isStackEmpty(stackk)) {
        throw runtime_error("Ошибка: стек пуст");
    }

    StackNode* temp = stackk.top;
    string value = temp->data;
    stackk.top = temp->next;
    delete temp;
    return value;
}

// Проверяет, пуст ли стек
bool isStackEmpty(const Stack& stackk) {
    return stackk.top == nullptr;
}

// Очищает стек
void clearStack(Stack& stackk) {
    while (!isStackEmpty(stackk)) {
        stackPop(stackk);
    }
}

// Сохраняет стек в файл
void saveStackToFile(const Stack& stackk, const string& filePath) {
    ofstream outFile(filePath);
    if (!outFile) {
        throw runtime_error("Ошибка: невозможно открыть файл для записи");
    }
    StackNode* current = stackk.top;
    while (current != nullptr) {
        outFile << current->data << endl;
        current = current->next;
    }
    outFile.close();
}

// Загружает стек из файла
void loadStackFromFile(Stack& stackk, const string& filePath) {
    ifstream inFile(filePath);
    if (!inFile) {
        throw runtime_error("Ошибка: невозможно открыть файл для чтения");
        return;
    }
    clearStack(stackk);
    string value;
    while (getline(inFile, value)) {
        stackPush(stackk, value);
    }
    inFile.close();
}
