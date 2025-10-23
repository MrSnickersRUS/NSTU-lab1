#ifndef ARRAY_H
#define ARRAY_H

#include <string>

using namespace std;

// Структура для узла массива
struct ArrayNode {
    string data;
    ArrayNode* next;
};

// Структура для динамического массива на основе связного списка
struct Array {
    ArrayNode* head = nullptr;
    size_t size = 0;
    
    // Конструктор
    Array();
    // Деструктор
    ~Array();
};

void addToArray(Array& array, const string& value);
void addToArrayAt(Array& array, const string& value, size_t index);
string getFromArray(const Array& array, size_t index);
void removeFromArray(Array& array, size_t index);
void replaceInArray(Array& array, size_t index, const string& value);
size_t getArrayLength(const Array& array);
void readArray(const Array& array);
void loadArrayFromFile(Array& array, const string& filename);
void saveArrayToFile(const Array& array, const string& filename);
void clearArray(Array& array);

#endif
