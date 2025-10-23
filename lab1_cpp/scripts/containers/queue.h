#ifndef QUEUE_H
#define QUEUE_H

#include <string>

using namespace std;

// Структура для узла очереди
struct QueueNode {
    string data;
    QueueNode* next;
};

// Структура для очереди
struct Queue {
    QueueNode* front = nullptr;
    QueueNode* rear = nullptr;
    
    // Конструктор
    Queue();
    // Деструктор
    ~Queue();
};

void enqueue(Queue& queue, const string& value);
string dequeue(Queue& queue);
bool isQueueEmpty(const Queue& queue);
void clearQueue(Queue& queue);
void loadQueueFromFile(Queue& queue, const string& filename);
void saveQueueToFile(const Queue& queue, const string& filename);

#endif
