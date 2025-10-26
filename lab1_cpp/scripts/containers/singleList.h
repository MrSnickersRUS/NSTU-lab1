#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

#include <string>

using namespace std;

// Структура для узла односвязного списка
struct SingleListNode {
    string data;
    SingleListNode* next;
};

// Структура для односвязного списка
struct SingleList {
    SingleListNode* head = nullptr;
    
    // Конструктор
    SingleList();
    // Деструктор
    ~SingleList();
};
void addToList(SingleList& list, const string& value);
void addToHead(SingleList& list, const string& value);
void addToTail(SingleList& list, const string& value);
bool addBefore(SingleList& list, const string& target, const string& value);
bool addAfter(SingleList& list, const string& target, const string& value);
bool removeFromList(SingleList& list, const string& value);
bool removeFromHead(SingleList& list);
bool removeFromTail(SingleList& list);
bool removeBefore(SingleList& list, const string& target);
bool removeAfter(SingleList& list, const string& target);
bool isInList(const SingleList& list, const string& value);
int findIndex(const SingleList& list, const string& value);
void readSingleList(const SingleList& list);
string getElement(const SingleList& list, int index);
string getHead(const SingleList& list);
string getTail(const SingleList& list);
int getSize(const SingleList& list);
bool isEmpty(const SingleList& list);
void clearList(SingleList& list);
void loadListFromFile(SingleList& list, const string& filename);
void saveListToFile(const SingleList& list, const string& filename);

#endif
