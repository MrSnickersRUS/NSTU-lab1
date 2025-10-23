#include "array.h"
#include <iostream>
#include <fstream>

using namespace std;

// Конструктор массива
Array::Array() : head(nullptr), size(0) {}

// Деструктор массива
Array::~Array() {
    clearArray(*this);
}

// Очищает массив
void clearArray(Array& array) {
    while (array.head != nullptr) {
        ArrayNode* temp = array.head;
        array.head = array.head->next;
        delete temp;
    }
    array.size = 0;
}

// Добавляет элемент в конец массива
void addToArray(Array& array, const string& value) {
    ArrayNode* newNode = new ArrayNode{value, nullptr};
    
    if (array.head == nullptr) {
        array.head = newNode;
    } else {
        ArrayNode* current = array.head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    array.size++;
}

// Добавляет элемент по индексу
void addToArrayAt(Array& array, const string& value, size_t index) {
    if (index > array.size) {
        throw out_of_range("Индекс выходит за границы массива");
    }
    
    ArrayNode* newNode = new ArrayNode{value, nullptr};
    
    if (index == 0) {
        newNode->next = array.head;
        array.head = newNode;
    } else {
        ArrayNode* current = array.head;
        for (size_t i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    array.size++;
}

// Получает элемент по индексу
string getFromArray(const Array& array, size_t index) {
    if (index >= array.size) {
        throw out_of_range("Индекс выходит за границы массива");
    }
    
    ArrayNode* current = array.head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

// Удаляет элемент по индексу
void removeFromArray(Array& array, size_t index) {
    if (index >= array.size) {
        throw out_of_range("Индекс выходит за границы массива");
    }
    
    ArrayNode* temp;
    
    if (index == 0) {
        temp = array.head;
        array.head = array.head->next;
        delete temp;
    } else {
        ArrayNode* current = array.head;
        for (size_t i = 0; i < index - 1; i++) {
            current = current->next;
        }
        temp = current->next;
        current->next = temp->next;
        delete temp;
    }
    array.size--;
}

// Заменяет элемент по индексу
void replaceInArray(Array& array, size_t index, const string& value) {
    if (index >= array.size) {
        throw out_of_range("Индекс выходит за границы массива");
    }
    
    ArrayNode* current = array.head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    current->data = value;
}

// Возвращает длину массива
size_t getArrayLength(const Array& array) {
    return array.size;
}

// Читает массив
void readArray(const Array& array) {
    ArrayNode* current = array.head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Сохраняет массив в файл
void saveArrayToFile(const Array& array, const string& filePath) {
    ofstream outFile(filePath);
    if (!outFile) {
        throw runtime_error("Ошибка: невозможно открыть файл для записи");
    }
    ArrayNode* current = array.head;
    while (current != nullptr) {
        outFile << current->data << endl;
        current = current->next;
    }
    outFile.close();
}

// Загружает массив из файла
void loadArrayFromFile(Array& array, const string& filePath) {
    ifstream inFile(filePath);
    if (!inFile) {
        throw runtime_error("Ошибка: невозможно открыть файл для чтения");
    }
    clearArray(array);
    string value;
    while (getline(inFile, value)) {
        addToArray(array, value);
    }
    inFile.close();
}