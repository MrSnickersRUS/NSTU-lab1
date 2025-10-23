#include "doubleList.h"
#include <iostream>
#include <fstream>

using namespace std;

// Конструктор двусвязного списка
DoubleList::DoubleList() : head(nullptr), tail(nullptr) {}

// Деструктор двусвязного списка
DoubleList::~DoubleList() {
    clearList(*this);
}

// Добавляет элемент в голову списка
void addToHead(DoubleList& list, const string& value) {
    DoubleListNode* newNode = new DoubleListNode{value, nullptr, list.head};
    if (list.head != nullptr) {
        list.head->prev = newNode;
    } else {
        list.tail = newNode;
    }
    list.head = newNode;
}

// Добавляет элемент в хвост списка
void addToTail(DoubleList& list, const string& value) {
    DoubleListNode* newNode = new DoubleListNode{value, list.tail, nullptr};
    if (list.tail != nullptr) {
        list.tail->next = newNode;
    } else {
        list.head = newNode;
    }
    list.tail = newNode;
}

// Добавляет элемент перед указанным значением
bool addBefore(DoubleList& list, const string& target, const string& value) {
    DoubleListNode* current = list.head;

    while (current != nullptr) {
        if (current->data == target) {
            DoubleListNode* newNode = new DoubleListNode{value, current->prev, current};
            if (current->prev != nullptr) {
                current->prev->next = newNode;
            } else {
                list.head = newNode;
            }
            current->prev = newNode;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Добавляет элемент после указанного значения
bool addAfter(DoubleList& list, const string& target, const string& value) {
    DoubleListNode* current = list.head;

    while (current != nullptr) {
        if (current->data == target) {
            DoubleListNode* newNode = new DoubleListNode{value, current, current->next};
            if (current->next != nullptr) {
                current->next->prev = newNode;
            } else {
                list.tail = newNode;
            }
            current->next = newNode;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Удаляет элемент из списка
bool removeFromList(DoubleList& list, const string& value) {
    DoubleListNode* current = list.head;

    while (current != nullptr) {
        if (current->data == value) {
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                list.head = current->next;
            }
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            } else {
                list.tail = current->prev;
            }
            // освобождаем узел и корректно уменьшаем память
            delete current;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Проверяет, содержится ли элемент в списке
bool isInList(const DoubleList& list, const string& value) {
    DoubleListNode* current = list.head;
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Читает список
void readList(const DoubleList& list) {
    DoubleListNode* current = list.head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Очищает список
void clearList(DoubleList& list) {
    while (list.head != nullptr) {
        DoubleListNode* temp = list.head;
        list.head = list.head->next;
        delete temp;
    }
    list.tail = nullptr;
}

// Сохраняет двусвязный список в файл
void saveListToFile(const DoubleList& list, const string& filePath) {
    ofstream outFile(filePath);
    if (!outFile) {
        throw runtime_error("Невозможно открыть файл для записи");
    }
    DoubleListNode* current = list.head;
    while (current != nullptr) {
        outFile << current->data << endl;
        current = current->next;
    }
    outFile.close();
}

// Загружает двусвязный список из файла
void loadDoubleListFromFile(DoubleList& list, const string& filePath) {
    ifstream inFile(filePath);
    if (!inFile) {
        throw runtime_error("Ошибка: невозможно открыть файл для чтения");
    }
    clearList(list);
    string value;
    while (getline(inFile, value)) {
        addToTail(list, value);
    }
    inFile.close();
}