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

// Удаляет элемент из списка по значению
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
            delete current;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Удаляет элемент с головы списка
bool removeFromHead(DoubleList& list) {
    if (list.head == nullptr) {
        return false;
    }
    DoubleListNode* temp = list.head;
    list.head = list.head->next;
    if (list.head != nullptr) {
        list.head->prev = nullptr;
    } else {
        list.tail = nullptr;
    }
    delete temp;
    return true;
}

// Удаляет элемент с хвоста списка
bool removeFromTail(DoubleList& list) {
    if (list.tail == nullptr) {
        return false;
    }
    DoubleListNode* temp = list.tail;
    list.tail = list.tail->prev;
    if (list.tail != nullptr) {
        list.tail->next = nullptr;
    } else {
        list.head = nullptr;
    }
    delete temp;
    return true;
}

// Удаляет элемент перед указанным значением
bool removeBefore(DoubleList& list, const string& target) {
    DoubleListNode* current = list.head;
    
    while (current != nullptr) {
        if (current->data == target && current->prev != nullptr) {
            DoubleListNode* toDelete = current->prev;
            if (toDelete->prev != nullptr) {
                toDelete->prev->next = current;
            } else {
                list.head = current;
            }
            current->prev = toDelete->prev;
            delete toDelete;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Удаляет элемент после указанного значения
bool removeAfter(DoubleList& list, const string& target) {
    DoubleListNode* current = list.head;
    
    while (current != nullptr) {
        if (current->data == target && current->next != nullptr) {
            DoubleListNode* toDelete = current->next;
            if (toDelete->next != nullptr) {
                toDelete->next->prev = current;
            } else {
                list.tail = current;
            }
            current->next = toDelete->next;
            delete toDelete;
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

// Находит индекс элемента в списке
int findIndex(const DoubleList& list, const string& value) {
    DoubleListNode* current = list.head;
    int index = 0;
    while (current != nullptr) {
        if (current->data == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;  // элемент не найден
}

// Читает список от головы к хвосту
void readList(const DoubleList& list) {
    DoubleListNode* current = list.head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Читает список от хвоста к голове (обратный порядок)
void readListReverse(const DoubleList& list) {
    DoubleListNode* current = list.tail;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->prev;
    }
    cout << endl;
}

// Получает элемент по индексу
string getElement(const DoubleList& list, int index) {
    if (index < 0) {
        throw out_of_range("Индекс не может быть отрицательным");
    }
    DoubleListNode* current = list.head;
    int currentIndex = 0;
    while (current != nullptr) {
        if (currentIndex == index) {
            return current->data;
        }
        current = current->next;
        currentIndex++;
    }
    throw out_of_range("Индекс выходит за границы списка");
}

// Получает первый элемент (голову)
string getHead(const DoubleList& list) {
    if (list.head == nullptr) {
        throw runtime_error("Список пуст");
    }
    return list.head->data;
}

// Получает последний элемент (хвост)
string getTail(const DoubleList& list) {
    if (list.tail == nullptr) {
        throw runtime_error("Список пуст");
    }
    return list.tail->data;
}

// Получает размер списка
int getSize(const DoubleList& list) {
    int size = 0;
    DoubleListNode* current = list.head;
    while (current != nullptr) {
        size++;
        current = current->next;
    }
    return size;
}

// Проверяет, пуст ли список
bool isEmpty(const DoubleList& list) {
    return list.head == nullptr;
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