#include "queue.h"
#include <iostream>
#include <fstream>

using namespace std;

// Конструктор очереди
Queue::Queue() : front(nullptr), rear(nullptr) {}

// Деструктор очереди
Queue::~Queue() {
    clearQueue(*this);
}

// Добавляет элемент в очередь
void enqueue(Queue& queue, const string& value) {
    QueueNode* newNode = new QueueNode{value, nullptr};
    if (queue.rear == nullptr) {
        queue.front = queue.rear = newNode;
    } else {
        queue.rear->next = newNode;
        queue.rear = newNode;
    }
}

// Извлекает элемент из очереди
string dequeue(Queue& queue) {
    if (isQueueEmpty(queue)) {
        throw runtime_error("Ошибка: очередь пуста");
    }

    QueueNode* temp = queue.front;
    string value = temp->data;
    queue.front = temp->next;

    if (queue.front == nullptr) {
        queue.rear = nullptr;
    }

    delete temp;
    return value;
}

// Проверяет, пуста ли очередь
bool isQueueEmpty(const Queue& queue) {
    return queue.front == nullptr;
}

// Очищает очередь
void clearQueue(Queue& queue) {
    while (!isQueueEmpty(queue)) {
        dequeue(queue);
    }
}

// Сохраняет очередь в файл
void saveQueueToFile(const Queue& queue, const string& filePath) {
    ofstream outFile(filePath);
    if (!outFile) {
        throw runtime_error("Ошибка: невозможно открыть файл для записи");
    }
    QueueNode* current = queue.front;
    while (current != nullptr) {
        outFile << current->data << endl;
        current = current->next;
    }
    outFile.close();
}

// Загружает очередь из файла
void loadQueueFromFile(Queue& queue, const string& filePath) {
    ifstream inFile(filePath);
    if (!inFile) {
        throw runtime_error("Ошибка: невозможно открыть файл для чтения");
    }
    clearQueue(queue);
    string value;
    while (getline(inFile, value)) {
        enqueue(queue, value);
    }
    inFile.close();
}