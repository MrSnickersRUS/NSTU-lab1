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

// Удаляет элемент из списка по значению
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

// Удаляет элемент с головы списка
bool removeFromHead(SingleList& list) {
    if (list.head == nullptr) {
        return false;
    }
    SingleListNode* temp = list.head;
    list.head = list.head->next;
    delete temp;
    return true;
}

// Удаляет элемент с хвоста списка
bool removeFromTail(SingleList& list) {
    if (list.head == nullptr) {
        return false;
    }
    if (list.head->next == nullptr) {
        delete list.head;
        list.head = nullptr;
        return true;
    }
    SingleListNode* current = list.head;
    while (current->next->next != nullptr) {
        current = current->next;
    }
    delete current->next;
    current->next = nullptr;
    return true;
}

// Удаляет элемент перед указанным значением
bool removeBefore(SingleList& list, const string& target) {
    if (list.head == nullptr || list.head->next == nullptr) {
        return false;
    }
    // Если второй элемент - это target, удаляем первый
    if (list.head->next->data == target) {
        SingleListNode* temp = list.head;
        list.head = list.head->next;
        delete temp;
        return true;
    }
    
    SingleListNode* current = list.head->next;
    SingleListNode* prevPrev = list.head;
    
    while (current->next != nullptr) {
        if (current->next->data == target) {
            SingleListNode* temp = current;
            prevPrev->next = current->next;
            delete temp;
            return true;
        }
        prevPrev = current;
        current = current->next;
    }
    return false;
}

// Удаляет элемент после указанного значения
bool removeAfter(SingleList& list, const string& target) {
    SingleListNode* current = list.head;
    
    while (current != nullptr && current->next != nullptr) {
        if (current->data == target) {
            SingleListNode* temp = current->next;
            current->next = temp->next;
            delete temp;
            return true;
        }
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

// Находит индекс элемента в списке
int findIndex(const SingleList& list, const string& value) {
    SingleListNode* current = list.head;
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

// Получает элемент по индексу
string getElement(const SingleList& list, int index) {
    if (index < 0) {
        throw out_of_range("Индекс не может быть отрицательным");
    }
    SingleListNode* current = list.head;
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
string getHead(const SingleList& list) {
    if (list.head == nullptr) {
        throw runtime_error("Список пуст");
    }
    return list.head->data;
}

// Получает последний элемент (хвост)
string getTail(const SingleList& list) {
    if (list.head == nullptr) {
        throw runtime_error("Список пуст");
    }
    SingleListNode* current = list.head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current->data;
}

// Получает размер списка
int getSize(const SingleList& list) {
    int size = 0;
    SingleListNode* current = list.head;
    while (current != nullptr) {
        size++;
        current = current->next;
    }
    return size;
}

// Проверяет, пуст ли список
bool isEmpty(const SingleList& list) {
    return list.head == nullptr;
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