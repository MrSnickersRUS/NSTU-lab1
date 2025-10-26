#include "array.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// Размер массива по умолчанию
const size_t INITIAL_CAPACITY = 4;

// Конструктор массива
Array::Array() : data(nullptr), size(0), capacity(0) {}

// Деструктор массива
Array::~Array() {
    clearArray(*this);
}

// Вспомогательная функция для увеличения емкости массива
void resizeArray(Array& array, size_t newCapacity) {
    string* newData = new string[newCapacity];
    for (size_t i = 0; i < array.size; i++) {
        newData[i] = array.data[i];
    }
    delete[] array.data;
    array.data = newData;
    array.capacity = newCapacity;
}

// Очищает массив
void clearArray(Array& array) {
    delete[] array.data;
    array.data = nullptr;
    array.size = 0;
    array.capacity = 0;
}

// Добавляет элемент в конец массива
void addToArray(Array& array, const string& value) {
    if (array.size >= array.capacity) {
        size_t newCapacity = (array.capacity == 0) ? INITIAL_CAPACITY : array.capacity * 2;
        resizeArray(array, newCapacity);
    }
    array.data[array.size++] = value;
}

// Добавляет элемент по индексу
void addToArrayAt(Array& array, const string& value, size_t index) {
    if (index > array.size) {
        throw out_of_range("Индекс выходит за границы массива");
    }
    
    if (array.size >= array.capacity) {
        size_t newCapacity = (array.capacity == 0) ? INITIAL_CAPACITY : array.capacity * 2;
        resizeArray(array, newCapacity);
    }
    
    // Сдвигаем элементы вправо
    for (size_t i = array.size; i > index; i--) {
        array.data[i] = array.data[i - 1];
    }
    
    array.data[index] = value;
    array.size++;
}

// Получает элемент по индексу
string getFromArray(const Array& array, size_t index) {
    if (index >= array.size) {
        throw out_of_range("Индекс выходит за границы массива");
    }
    return array.data[index];
}

// Удаляет элемент по индексу
void removeFromArray(Array& array, size_t index) {
    if (index >= array.size) {
        throw out_of_range("Индекс выходит за границы массива");
    }
    
    // Сдвигаем элементы влево
    for (size_t i = index; i < array.size - 1; i++) {
        array.data[i] = array.data[i + 1];
    }
    
    array.size--;
}

// Заменяет элемент по индексу
void replaceInArray(Array& array, size_t index, const string& value) {
    if (index >= array.size) {
        throw out_of_range("Индекс выходит за границы массива");
    }
    array.data[index] = value;
}

// Возвращает длину массива
size_t getArrayLength(const Array& array) {
    return array.size;
}

// Читает массив
void readArray(const Array& array) {
    for (size_t i = 0; i < array.size; i++) {
        cout << array.data[i] << " ";
    }
    cout << endl;
}

// Сохраняет массив в файл
void saveArrayToFile(const Array& array, const string& filePath) {
    ofstream outFile(filePath);
    if (!outFile) {
        throw runtime_error("Ошибка: невозможно открыть файл для записи");
    }
    for (size_t i = 0; i < array.size; i++) {
        outFile << array.data[i] << endl;
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