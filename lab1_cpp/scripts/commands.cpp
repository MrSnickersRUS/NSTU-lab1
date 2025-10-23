#include "commands.h"
#include "containers.h"
#include <iostream>
#include <sstream>
#include <map>
#include <fstream>
#include <functional>

using namespace std;

map<string, Container> conts = {
    {"M", ARRAY},
    {"F", SINGLE_LIST},
    {"L", DOUBLE_LIST},
    {"Q", QUEUE},
    {"S", STACK},
    {"T", TREE}
};

map<string, Operation> operations = {
    {"PUSH", PUSH},
    {"DEL", DEL},
    {"GET", GET},
    {"POP", POP},
    {"INS", INS},
    {"ISMEMBER", ISMEMBER},
    {"REP", REP},
    {"LEN", LEN},
    {"ADDHEAD", ADDHEAD},
    {"ADDTAIL", ADDTAIL},
    {"ADDBEFORE", ADDBEFORE},
    {"ADDAFTER", ADDAFTER},
    {"READ", READ}
};

// Глобальные хранилища для именованных структур данных
map<string, Array> arrays;
map<string, SingleList> singleLists;
map<string, DoubleList> doubleLists;
map<string, Stack> stacks;
map<string, Queue> queues;
map<string, AVLTree> trees;

// Функция для сохранения всех контейнеров в файл
void saveAllContainers(const string& filePath) {
    ofstream outFile(filePath);
    if (!outFile) {
        throw runtime_error("Ошибка: невозможно открыть файл для записи");
    }
    
    // Сохраняем массивы
    for (const auto& pair : arrays) {
        outFile << "[ARRAY:" << pair.first << "]" << endl;
        ArrayNode* current = pair.second.head;
        while (current != nullptr) {
            outFile << current->data << endl;
            current = current->next;
        }
    }
    
    // Сохраняем односвязные списки
    for (const auto& pair : singleLists) {
        outFile << "[SINGLE_LIST:" << pair.first << "]" << endl;
        SingleListNode* current = pair.second.head;
        while (current != nullptr) {
            outFile << current->data << endl;
            current = current->next;
        }
    }
    
    // Сохраняем двусвязные списки
    for (const auto& pair : doubleLists) {
        outFile << "[DOUBLE_LIST:" << pair.first << "]" << endl;
        DoubleListNode* current = pair.second.head;
        while (current != nullptr) {
            outFile << current->data << endl;
            current = current->next;
        }
    }
    
    // Сохраняем стеки
    for (const auto& pair : stacks) {
        outFile << "[STACK:" << pair.first << "]" << endl;
        StackNode* current = pair.second.top;
        while (current != nullptr) {
            outFile << current->data << endl;
            current = current->next;
        }
    }
    
    // Сохраняем очереди
    for (const auto& pair : queues) {
        outFile << "[QUEUE:" << pair.first << "]" << endl;
        QueueNode* current = pair.second.front;
        while (current != nullptr) {
            outFile << current->data << endl;
            current = current->next;
        }
    }
    
    // Сохраняем АВЛ-деревья
    for (const auto& pair : trees) {
        outFile << "[TREE:" << pair.first << "]" << endl;
        function<void(AVLNode*)> saveTree = [&](AVLNode* node) {
            if (!node) return;
            saveTree(node->left);
            outFile << node->data << endl;
            saveTree(node->right);
        };
        saveTree(pair.second.root);
    }
    
    outFile.close();
}

// Функция для загрузки всех контейнеров из файла
void loadAllContainers(const string& filePath) {
    ifstream inFile(filePath);
    if (!inFile) {
        // Файл не существует - это нормально для первого запуска
        return;
    }
    
    // Создаем временные хранилища для загрузки из файла
    map<string, Array> tempArrays;
    map<string, SingleList> tempSingleLists;
    map<string, DoubleList> tempDoubleLists;
    map<string, Stack> tempStacks;
    map<string, Queue> tempQueues;
    map<string, AVLTree> tempTrees;
    
    string line;
    string currentSection = "";
    string currentName = "";
    
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        
        // Проверяем, является ли строка заголовком секции
        if (line[0] == '[' && line[line.length()-1] == ']') {
            string header = line.substr(1, line.length()-2);
            size_t colonPos = header.find(':');
            
            if (colonPos != string::npos) {
                currentSection = header.substr(0, colonPos);
                currentName = header.substr(colonPos + 1);
                
                // Создаем пустой контейнер в соответствующем map
                if (currentSection == "ARRAY") {
                    tempArrays[currentName];
                } else if (currentSection == "SINGLE_LIST") {
                    tempSingleLists[currentName];
                } else if (currentSection == "DOUBLE_LIST") {
                    tempDoubleLists[currentName];
                } else if (currentSection == "STACK") {
                    tempStacks[currentName];
                } else if (currentSection == "QUEUE") {
                    tempQueues[currentName];
                } else if (currentSection == "TREE") {
                    tempTrees[currentName];
                }
            } else {
                // Старый формат без имени
                currentSection = header;
                currentName = "default";
            }
        } else {
            // Загружаем данные во временные контейнеры
            if (currentSection == "ARRAY") {
                addToArray(tempArrays[currentName], line);
            } else if (currentSection == "SINGLE_LIST") {
                addToList(tempSingleLists[currentName], line);
            } else if (currentSection == "DOUBLE_LIST") {
                addToTail(tempDoubleLists[currentName], line);
            } else if (currentSection == "STACK") {
                stackPush(tempStacks[currentName], line);
            } else if (currentSection == "QUEUE") {
                enqueue(tempQueues[currentName], line);
            } else if (currentSection == "TREE") {
                insertToAVL(tempTrees[currentName], line);
            }
        }
    }
    
    inFile.close();
    
    // Очищаем все старые данные перед загрузкой новых
    for (auto& pair : arrays) {
        clearArray(pair.second);
    }
    for (auto& pair : singleLists) {
        clearList(pair.second);
    }
    for (auto& pair : doubleLists) {
        clearList(pair.second);
    }
    for (auto& pair : stacks) {
        clearStack(pair.second);
    }
    for (auto& pair : queues) {
        clearQueue(pair.second);
    }
    for (auto& pair : trees) {
        clearTree(pair.second);
    }
    
    // Очищаем глобальные map'ы и переносим данные из временных контейнеров
    arrays.clear();
    singleLists.clear();
    doubleLists.clear();
    stacks.clear();
    queues.clear();
    trees.clear();
    
    for (auto& pair : tempArrays) {
        arrays[pair.first].head = pair.second.head;
        arrays[pair.first].size = pair.second.size;
        pair.second.head = nullptr;
        pair.second.size = 0;
    }
    for (auto& pair : tempSingleLists) {
        singleLists[pair.first].head = pair.second.head;
        pair.second.head = nullptr;
    }
    for (auto& pair : tempDoubleLists) {
        doubleLists[pair.first].head = pair.second.head;
        doubleLists[pair.first].tail = pair.second.tail;
        pair.second.head = nullptr;
        pair.second.tail = nullptr;
    }
    for (auto& pair : tempStacks) {
        stacks[pair.first].top = pair.second.top;
        pair.second.top = nullptr;
    }
    for (auto& pair : tempQueues) {
        queues[pair.first].front = pair.second.front;
        queues[pair.first].rear = pair.second.rear;
        pair.second.front = nullptr;
        pair.second.rear = nullptr;
    }
    for (auto& pair : tempTrees) {
        trees[pair.first].root = pair.second.root;
        pair.second.root = nullptr;
    }
}

void processQuery(const string& query, const string& filePath) {
    // Загружаем все контейнеры из файлов
    loadAllContainers(filePath);
    
    stringstream ss(query);
    string command;
    ss >> command;

    char structureKey = command[0];
    string operationKey = command.substr(1);
    
    if (command == "PRINT") {
        string containerName;
        ss >> containerName;

        // Ищем контейнер в map'ах
        if (arrays.find(containerName) != arrays.end()) {
            readArray(arrays[containerName]);
        } else if (singleLists.find(containerName) != singleLists.end()) {
            readSingleList(singleLists[containerName]);
        } else if (doubleLists.find(containerName) != doubleLists.end()) {
            readList(doubleLists[containerName]);
        } else if (stacks.find(containerName) != stacks.end()) {
            StackNode* current = stacks[containerName].top;
            while (current != nullptr) {
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;
        } else if (queues.find(containerName) != queues.end()) {
            QueueNode* current = queues[containerName].front;
            while (current != nullptr) {
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;
        } else if (trees.find(containerName) != trees.end()) {
            readAVL(trees[containerName]);
        } else {
            throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
        }
        return;
    }
    else if (command == "ISMEMBER") {
        string containerName, value;
        ss >> containerName >> value;

        // Определяем тип контейнера по первой букве его имени или ищем в map
        bool found = false;
        
        // Проверяем в массивах
        if (arrays.find(containerName) != arrays.end()) {
            for (size_t i = 0; i < arrays[containerName].size; i++) {
                if (getFromArray(arrays[containerName], i) == value) {
                    found = true;
                    break;
                }
            }
        }
        // Проверяем в односвязных списках
        else if (singleLists.find(containerName) != singleLists.end()) {
            found = isInList(singleLists[containerName], value);
        }
        // Проверяем в двусвязных списках
        else if (doubleLists.find(containerName) != doubleLists.end()) {
            found = isInList(doubleLists[containerName], value);
        }
        // Проверяем в деревьях
        else if (trees.find(containerName) != trees.end()) {
            found = searchInAVL(trees[containerName], value);
        }
        else {
            throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
        }
        
        cout << (found ? "TRUE" : "FALSE") << endl;
        return;
    }
    else if (conts.find(string(1, structureKey)) == conts.end()) {
        throw runtime_error("Неизвестная структура: " + string(1, structureKey));
    }
    else if (operations.find(operationKey) == operations.end()) {
        throw runtime_error("Неизвестная операция: " + operationKey);
    }

    Container structure = conts[string(1, structureKey)];
    Operation operation = operations[operationKey];
    
    // Читаем имя контейнера
    string containerName;
    ss >> containerName;
    
    bool isNeedSave = false; // Нужно ли сохранять данные

    switch (structure) {
        case ARRAY:
            if (operation == PUSH) {
                string value;
                ss >> value;
                // Если значение пустое, создаем контейнер, но не добавляем элемент
                if (!value.empty()) {
                    addToArray(arrays[containerName], value);
                } else {
                    // Просто создаем контейнер в map (если его нет)
                    arrays[containerName];
                }
                isNeedSave = true;
            } else if (operation == INS) {
                size_t index;
                string value;
                ss >> index >> value;
                if (arrays.find(containerName) != arrays.end()) {
                    addToArrayAt(arrays[containerName], value, index);
                    isNeedSave = true;
                } else {
                    // Если контейнера не существует, создаем его
                    addToArrayAt(arrays[containerName], value, index);
                    isNeedSave = true;
                }
            } else if (operation == DEL) {
                size_t index;
                ss >> index;
                if (arrays.find(containerName) != arrays.end() && index < arrays[containerName].size) {
                    removeFromArray(arrays[containerName], index);
                    // Удаляем контейнер, если он стал пустым
                    if (arrays[containerName].size == 0) {
                        arrays.erase(containerName);
                    }
                    isNeedSave = true;
                } else {
                    throw runtime_error("Ошибка: индекс выходит за границы или контейнер не найден");
                }
            } else if (operation == GET) {
                size_t index;
                ss >> index;
                if (arrays.find(containerName) != arrays.end()) {
                    cout << getFromArray(arrays[containerName], index) << endl;
                } else {
                    throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
                }
            } else if (operation == REP) {
                size_t index;
                string value;
                ss >> index >> value;
                if (arrays.find(containerName) != arrays.end()) {
                    replaceInArray(arrays[containerName], index, value);
                    isNeedSave = true;
                } else {
                    throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
                }
            } else if (operation == LEN) {
                if (arrays.find(containerName) != arrays.end()) {
                    cout << getArrayLength(arrays[containerName]) << endl;
                } else {
                    throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
                }
            } else if (operation == READ) {
                if (arrays.find(containerName) != arrays.end()) {
                    readArray(arrays[containerName]);
                } else {
                    throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
                }
            }
            break;
        case SINGLE_LIST:
            if (operation == PUSH) {
                string value;
                ss >> value;
                if (!value.empty()) {
                    addToList(singleLists[containerName], value);
                } else {
                    singleLists[containerName];
                }
                isNeedSave = true;
            } else if (operation == ADDHEAD) {
                string value;
                ss >> value;
                if (!value.empty()) {
                    addToHead(singleLists[containerName], value);
                } else {
                    singleLists[containerName];
                }
                isNeedSave = true;
            } else if (operation == ADDTAIL) {
                string value;
                ss >> value;
                if (!value.empty()) {
                    addToTail(singleLists[containerName], value);
                } else {
                    singleLists[containerName];
                }
                isNeedSave = true;
            } else if (operation == ADDBEFORE) {
                string target, value;
                ss >> target >> value;
                if (singleLists.find(containerName) != singleLists.end()) {
                    if (addBefore(singleLists[containerName], target, value)) {
                        isNeedSave = true;
                    } else {
                        throw runtime_error("Ошибка: элемент '" + target + "' не найден");
                    }
                } else {
                    throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
                }
            } else if (operation == ADDAFTER) {
                string target, value;
                ss >> target >> value;
                if (singleLists.find(containerName) != singleLists.end()) {
                    if (addAfter(singleLists[containerName], target, value)) {
                        isNeedSave = true;
                    } else {
                        throw runtime_error("Ошибка: элемент '" + target + "' не найден");
                    }
                } else {
                    throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
                }
            } else if (operation == DEL) {
                string value;
                ss >> value;
                if (singleLists.find(containerName) != singleLists.end() && 
                    isInList(singleLists[containerName], value)) {
                    removeFromList(singleLists[containerName], value);
                    // Удаляем контейнер, если он стал пустым
                    if (singleLists[containerName].head == nullptr) {
                        singleLists.erase(containerName);
                    }
                    isNeedSave = true;
                } else {
                    throw runtime_error("Ошибка: элемент '" + value + "' не найден в списке");
                }
            } else if (operation == GET) {
                string value;
                ss >> value;
                if (singleLists.find(containerName) != singleLists.end()) {
                    cout << (isInList(singleLists[containerName], value) ? "Найдено" : "Не найдено") << endl;
                } else {
                    throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
                }
            } else if (operation == READ) {
                if (singleLists.find(containerName) != singleLists.end()) {
                    readSingleList(singleLists[containerName]);
                } else {
                    throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
                }
            }
            break;
        case DOUBLE_LIST:
            if (operation == PUSH) {
                string value;
                ss >> value;
                // Если значение пустое, создаем контейнер, но не добавляем элемент
                if (!value.empty()) {
                    addToTail(doubleLists[containerName], value);
                } else {
                    // Просто создаем контейнер в map (если его нет)
                    doubleLists[containerName];
                }
                isNeedSave = true;
            } else if (operation == ADDHEAD) {
                string value;
                ss >> value;
                if (!value.empty()) {
                    addToHead(doubleLists[containerName], value);
                } else {
                    doubleLists[containerName];
                }
                isNeedSave = true;
            } else if (operation == ADDTAIL) {
                string value;
                ss >> value;
                if (!value.empty()) {
                    addToTail(doubleLists[containerName], value);
                } else {
                    doubleLists[containerName];
                }
                isNeedSave = true;
            } else if (operation == ADDBEFORE) {
                string target, value;
                ss >> target >> value;
                if (doubleLists.find(containerName) != doubleLists.end()) {
                    if (addBefore(doubleLists[containerName], target, value)) {
                        isNeedSave = true;
                    } else {
                        throw runtime_error("Ошибка: элемент '" + target + "' не найден");
                    }
                } else {
                    throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
                }
            } else if (operation == ADDAFTER) {
                string target, value;
                ss >> target >> value;
                if (doubleLists.find(containerName) != doubleLists.end()) {
                    if (addAfter(doubleLists[containerName], target, value)) {
                        isNeedSave = true;
                    } else {
                        throw runtime_error("Ошибка: элемент '" + target + "' не найден");
                    }
                } else {
                    throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
                }
            } else if (operation == DEL) {
                string value;
                ss >> value;
                if (doubleLists.find(containerName) != doubleLists.end() && 
                    isInList(doubleLists[containerName], value)) {
                    removeFromList(doubleLists[containerName], value);
                    // Удаляем контейнер, если он стал пустым
                    if (doubleLists[containerName].head == nullptr) {
                        doubleLists.erase(containerName);
                    }
                    isNeedSave = true;
                } else {
                    throw runtime_error("Ошибка: элемент '" + value + "' не найден в списке");
                }
            } else if (operation == GET) {
                string value;
                ss >> value;
                if (doubleLists.find(containerName) != doubleLists.end()) {
                    cout << (isInList(doubleLists[containerName], value) ? "Найдено" : "Не найдено") << endl;
                } else {
                    throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
                }
            } else if (operation == READ) {
                if (doubleLists.find(containerName) != doubleLists.end()) {
                    readList(doubleLists[containerName]);
                } else {
                    throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
                }
            }
            break;
        case QUEUE:
            if (operation == PUSH) {
                string value;
                if (ss >> value) {
                    // Если значение указано, добавляем его
                    enqueue(queues[containerName], value);
                } else {
                    // Если значение не указано, просто создаем пустую очередь
                    if (queues.find(containerName) == queues.end()) {
                        queues[containerName] = Queue();
                    }
                }
                isNeedSave = true;
            } else if (operation == POP) {
                if (queues.find(containerName) != queues.end()) {
                    cout << dequeue(queues[containerName]) << endl;
                    // Удаляем контейнер, если он стал пустым
                    if (queues[containerName].front == nullptr) {
                        queues.erase(containerName);
                    }
                    isNeedSave = true;
                } else {
                    throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
                }
            } else if (operation == READ) {
                if (queues.find(containerName) != queues.end()) {
                    QueueNode* current = queues[containerName].front;
                    while (current != nullptr) {
                        cout << current->data << " ";
                        current = current->next;
                    }
                    cout << endl;
                } else {
                    throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
                }
            }
            break;
        case STACK:
            if (operation == PUSH) {
                string value;
                if (ss >> value) {
                    // Если значение указано, добавляем его
                    stackPush(stacks[containerName], value);
                } else {
                    // Если значение не указано, просто создаем пустой стек
                    if (stacks.find(containerName) == stacks.end()) {
                        stacks[containerName] = Stack();
                    }
                }
                isNeedSave = true;
            } else if (operation == POP) {
                if (stacks.find(containerName) != stacks.end()) {
                    cout << stackPop(stacks[containerName]) << endl;
                    // Удаляем контейнер, если он стал пустым
                    if (stacks[containerName].top == nullptr) {
                        stacks.erase(containerName);
                    }
                    isNeedSave = true;
                } else {
                    throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
                }
            } else if (operation == READ) {
                if (stacks.find(containerName) != stacks.end()) {
                    StackNode* current = stacks[containerName].top;
                    while (current != nullptr) {
                        cout << current->data << " ";
                        current = current->next;
                    }
                    cout << endl;
                } else {
                    throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
                }
            }
            break;
        case TREE:
            if (operation == PUSH) {
                string value;
                if (ss >> value) {
                    // Если значение указано, добавляем его
                    insertToAVL(trees[containerName], value);
                } else {
                    // Если значение не указано, просто создаем пустое дерево
                    if (trees.find(containerName) == trees.end()) {
                        trees[containerName] = AVLTree();
                    }
                }
                isNeedSave = true;
            } else if (operation == INS) {
                string value;
                ss >> value;
                insertToAVL(trees[containerName], value);
                isNeedSave = true;
            } else if (operation == DEL) {
                string value;
                ss >> value;
                if (trees.find(containerName) != trees.end() && 
                    searchInAVL(trees[containerName], value)) {
                    deleteFromAVL(trees[containerName], value);
                    // Удаляем контейнер, если он стал пустым
                    if (trees[containerName].root == nullptr) {
                        trees.erase(containerName);
                    }
                    isNeedSave = true;
                } else {
                    throw runtime_error("Ошибка: элемент '" + value + "' не найден в дереве");
                }
            } else if (operation == GET) {
                string value;
                ss >> value;
                if (trees.find(containerName) != trees.end()) {
                    cout << (searchInAVL(trees[containerName], value) ? "Найдено" : "Не найдено") << endl;
                } else {
                    throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
                }
            } else if (operation == READ) {
                if (trees.find(containerName) != trees.end()) {
                    readAVL(trees[containerName]);
                } else {
                    throw runtime_error("Ошибка: контейнер '" + containerName + "' не найден");
                }
            }
            break;
        default:
            throw runtime_error("Неизвестная структура или операция.");
    }
    
    // Сохраняем данные в файл, если были изменения
    if (isNeedSave) {
        saveAllContainers(filePath);
    }
}
