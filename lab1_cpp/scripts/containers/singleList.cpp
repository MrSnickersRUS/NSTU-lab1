#include "singleList.h"
#include <iostream>
#include <fstream>

using namespace std;

// Конструктор односвязного списка
SingleList::SingleList() : head(nullptr) {}

// Деструктор односвязного списка
SingleList::~SingleList() {
    clearList(*this);
}

// Добавляет элемент в голову списка
void addToHead(SingleList& list, const string& value) {
    SingleListNode* newNode = new SingleListNode{value, list.head};
    list.head = newNode;
}

// Добавляет элемент в хвост списка
void addToTail(SingleList& list, const string& value) {
    SingleListNode* newNode = new SingleListNode{value, nullptr};
    if (list.head == nullptr) {
        list.head = newNode;
        return;
    }
    SingleListNode* current = list.head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
}

// Добавляет элемент перед указанным значением
bool addBefore(SingleList& list, const string& target, const string& value) {
    SingleListNode* current = list.head;
    SingleListNode* prev = nullptr;

    while (current != nullptr) {
        if (current->data == target) {
            SingleListNode* newNode = new SingleListNode{value, current};
            if (prev == nullptr) {
                list.head = newNode;
            } else {
                prev->next = newNode;
            }
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

// Добавляет элемент после указанного значения
bool addAfter(SingleList& list, const string& target, const string& value) {
    SingleListNode* current = list.head;

    while (current != nullptr) {
        if (current->data == target) {
            SingleListNode* newNode = new SingleListNode{value, current->next};
            current->next = newNode;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Удаляет элемент из списка
bool removeFromList(SingleList& list, const string& value) {
    SingleListNode* current = list.head;
    SingleListNode* prev = nullptr;

    while (current != nullptr) {
        if (current->data == value) {
            if (prev == nullptr) {
                list.head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

// Проверяет, содержится ли элемент в списке
bool isInList(const SingleList& list, const string& value) {
    SingleListNode* current = list.head;
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Читает список
void readList(const SingleList& list) {
    SingleListNode* current = list.head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Очищает список
void clearList(SingleList& list) {
    while (list.head != nullptr) {
        SingleListNode* temp = list.head;
        list.head = list.head->next;
        delete temp;
    }
}

// Сохраняет односвязный список в файл
void saveListToFile(const SingleList& list, const string& filePath) {
    ofstream outFile(filePath);
    if (!outFile) {
        throw runtime_error("Ошибка: невозможно открыть файл для записи");
    }
    SingleListNode* current = list.head;
    while (current != nullptr) {
        outFile << current->data << endl;
        current = current->next;
    }
    outFile.close();
}

// Загружает односвязный список из файла
void loadListFromFile(SingleList& list, const string& filePath) {
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

// Получает значения из списка
void readSingleList(const SingleList& list) {
    SingleListNode* current = list.head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Добавляет значение в список
void addToList(SingleList& list, const string& value) {
    SingleListNode* newNode = new SingleListNode{value, nullptr};
    if (list.head == nullptr) {
        list.head = newNode;
    } else {
        SingleListNode* current = list.head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}