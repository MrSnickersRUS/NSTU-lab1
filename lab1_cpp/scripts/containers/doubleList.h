#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include <string>

using namespace std;

// Структура для узла двусвязного списка
struct DoubleListNode {
    string data;
    DoubleListNode* prev;
    DoubleListNode* next;
};

// Структура для двусвязного списка
struct DoubleList {
    DoubleListNode* head = nullptr;
    DoubleListNode* tail = nullptr;
    
    // Конструктор
    DoubleList();
    // Деструктор
    ~DoubleList();
};

void addToHead(DoubleList& list, const string& value);
void addToTail(DoubleList& list, const string& value);
bool addBefore(DoubleList& list, const string& target, const string& value);
bool addAfter(DoubleList& list, const string& target, const string& value);
bool removeFromList(DoubleList& list, const string& value);
bool removeFromHead(DoubleList& list);
bool removeFromTail(DoubleList& list);
bool removeBefore(DoubleList& list, const string& target);
bool removeAfter(DoubleList& list, const string& target);
bool isInList(const DoubleList& list, const string& value);
int findIndex(const DoubleList& list, const string& value);
void readList(const DoubleList& list);
void readListReverse(const DoubleList& list);
string getElement(const DoubleList& list, int index);
string getHead(const DoubleList& list);
string getTail(const DoubleList& list);
int getSize(const DoubleList& list);
bool isEmpty(const DoubleList& list);
void clearList(DoubleList& list);
void loadDoubleListFromFile(DoubleList& list, const string& filename);
void saveListToFile(const DoubleList& list, const string& filename);

#endif
