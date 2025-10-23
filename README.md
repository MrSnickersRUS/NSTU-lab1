# 🚀 Проект Lab1 Go

Добро пожаловать в первую лабораторную работу по программированию! Этот репозиторий содержит реализации различных структур данных и алгоритмов, написанных на Go и C++. Проект создан для изучения и освоения АТД. 🌟

## 📂 Структура проекта

```
lab1_go/
├── commands.go       # Логика обработки команд
├── dbms              # Система управления базами данных
├── go.mod            # Файл модуля Go
├── main.go           # Главная точка входа в приложение
├── Makefile          # Команды для сборки и запуска
├── test_data.txt     # Пример тестовых данных
└── containers/       # Реализации структур данных
    ├── array.go
    ├── doublelist.go
    ├── queue.go
    ├── singlelist.go
    └── stack.go

lab1_cpp/
├── scripts/          # Исходный код на C++
│   ├── commands.cpp
│   ├── commands.h
│   ├── containers.h
│   ├── main.cpp
│   ├── dbms          # Система управления базами данных
│   └── containers/   # Реализации структур данных на C++
│       ├── array.cpp
│       ├── doubleList.cpp
│       ├── queue.cpp
│       ├── stack.cpp
│       └── tree.cpp
└── source/           # Дополнительные исходники
```

## 📜 Возможности

- **Очередь (Queue)**: Простая реализация очереди с методами добавления, удаления и утилитами.
- **Стек (Stack)**: Реализация стека для операций LIFO.
- **Связные списки (Linked Lists)**: Односвязные и двусвязные списки.
- **Массив (Array)**: Утилиты для работы с массивами.
- **Деревья (Trees)**: Реализация бинарных деревьев и AVL-деревьев на C++.

## 🛠️ Начало работы

### Предварительные требования

Убедитесь, что у вас установлено:

- [Go](https://golang.org/dl/) (версия 1.16 или выше)
- Компилятор C++ (например, g++)

### Установка

1. Клонируйте репозиторий:
   ```bash
   git clone https://github.com/your-username/lab1-go-project.git
   cd lab1-go-project
   ```

2. Инициализируйте модуль Go:
   ```bash
   go mod tidy
   ```

### Запуск проекта

Для запуска основного приложения на Go:
```bash
make run
```

Для запуска тестов:
```bash
make test
```

Для компиляции и запуска C++ кода:
```bash
cd labs/lab1/scripts
make
./dbms --file data.txt --query 'TREAD myTree'
```

# 📖 Документация по командам DBMS

## Общий формат
```
./dbms --file <путь_к_файлу> --query '<КОМАНДА> <контейнер> [параметры]'
```

## Массив (Array) - префикс M

### Операции:
- **MPUSH** `<имя> <значение>` - добавление элемента в конец массива
- **MINS** `<имя> <индекс> <значение>` - добавление элемента по индексу
- **MDEL** `<имя> <индекс>` - удаление элемента по индексу
- **MGET** `<имя> <индекс>` - получение элемента по индексу
- **MREP** `<имя> <индекс> <значение>` - замена элемента по индексу
- **MLEN** `<имя>` - получение длины массива
- **MREAD** `<имя>` - чтение всего массива

### Примеры:
```bash
./dbms --file ../source/file.data --query 'MPUSH myArray'
./dbms --file ../source/file.data --query 'MINS myArray 0 first'
./dbms --file ../source/file.data --query 'MGET myArray 0'
./dbms --file ../source/file.data --query 'MREP myArray 1 newValue'
./dbms --file ../source/file.data --query 'MLEN myArray'
./dbms --file ../source/file.data --query 'MREAD myArray'
./dbms --file ../source/file.data --query 'MDEL myArray 0'
```

---

## Односвязный список (Single List) - префикс F

### Операции:
- **FPUSH** `<имя> <значение>` - добавление элемента (общий метод)
- **FADDHEAD** `<имя> <значение>` - добавление элемента в голову списка
- **FADDTAIL** `<имя> <значение>` - добавление элемента в хвост списка
- **FADDBEFORE** `<имя> <целевой_элемент> <значение>` - добавление элемента перед указанным
- **FADDAFTER** `<имя> <целевой_элемент> <значение>` - добавление элемента после указанного
- **FDEL** `<имя> <значение>` - удаление элемента по значению
- **FGET** `<имя> <значение>` - поиск элемента по значению (Found/Not Found)
- **FREAD** `<имя>` - чтение всего списка

### Примеры:
```bash
./dbms --file ../source/file.data --query 'FADDHEAD myList head'
./dbms --file ../source/file.data --query 'FADDTAIL myList tail'
./dbms --file ../source/file.data --query 'FADDBEFORE myList tail middle'
./dbms --file ../source/file.data --query 'FADDAFTER myList head after-head'
./dbms --file ../source/file.data --query 'FDEL myList middle'
./dbms --file ../source/file.data --query 'FGET myList head'
./dbms --file ../source/file.data --query 'FREAD myList'
./dbms --file ../source/file.data --query 'FPUSH myList head'
```

---

## Двусвязный список (Double List) - префикс L

### Операции:
- **LPUSH** `<имя> <значение>` - добавление элемента в хвост списка
- **LADDHEAD** `<имя> <значение>` - добавление элемента в голову списка
- **LADDTAIL** `<имя> <значение>` - добавление элемента в хвост списка
- **LADDBEFORE** `<имя> <целевой_элемент> <значение>` - добавление элемента перед указанным
- **LADDAFTER** `<имя> <целевой_элемент> <значение>` - добавление элемента после указанного
- **LDEL** `<имя> <значение>` - удаление элемента по значению
- **LGET** `<имя> <значение>` - поиск элемента по значению (Found/Not Found)
- **LREAD** `<имя>` - чтение всего списка

### Примеры:
```bash
./dbms --file ../source/file.data --query 'LADDHEAD myDList head'
./dbms --file ../source/file.data --query 'LADDTAIL myDList tail'
./dbms --file ../source/file.data --query 'LADDBEFORE myDList tail middle'
./dbms --file ../source/file.data --query 'LADDAFTER myDList head after-head'
./dbms --file ../source/file.data --query 'LDEL myDList middle'
./dbms --file ../source/file.data --query 'LREAD myDList'
```

---

## Стек (Stack) - префикс S

### Операции:
- **SPUSH** `<имя> <значение>` - добавление элемента в стек (push)
- **SPOP** `<имя>` - извлечение элемента из стека (pop)
- **SREAD** `<имя>` - чтение всего стека

### Примеры:
```bash
./dbms --file ../source/file.data --query 'SPUSH myStack item1'
./dbms --file ../source/file.data --query 'SPUSH myStack item2'
./dbms --file ../source/file.data --query 'SREAD myStack'
./dbms --file ../source/file.data --query 'SPOP myStack'
```

---

## Очередь (Queue) - префикс Q

### Операции:
- **QPUSH** `<имя> <значение>` - добавление элемента в очередь (enqueue)
- **QPOP** `<имя>` - извлечение элемента из очереди (dequeue)
- **QREAD** `<имя>` - чтение всей очереди

### Примеры:
```bash
./dbms --file ../source/file.data --query 'QPUSH myQueue q1'
./dbms --file ../source/file.data --query 'QPUSH myQueue q2'
./dbms --file ../source/file.data --query 'QREAD myQueue'
./dbms --file ../source/file.data --query 'QPOP myQueue'
```

---

## АВЛ-дерево (AVL Tree) - префикс T

### Операции:
- **TINS** `<имя> <значение>` - вставка элемента в дерево
- **TDEL** `<имя> <значение>` - удаление элемента из дерева
- **TGET** `<имя> <значение>` - поиск элемента в дереве (Found/Not Found)
- **TREAD** `<имя>` - чтение дерева (in-order обход)

### Примеры:
```bash
./dbms --file ../source/file.data --query 'TINS myTree 50'
./dbms --file ../source/file.data --query 'TINS myTree 30'
./dbms --file ../source/file.data --query 'TINS myTree 70'
./dbms --file ../source/file.data --query 'TREAD myTree'
./dbms --file ../source/file.data --query 'TGET myTree 50'
./dbms --file ../source/file.data --query 'TDEL myTree 30'
```

---

## Универсальные команды

### PRINT
Выводит содержимое контейнера (альтернатива READ, работает с любым типом).
```bash
./dbms --file ../source/file.data --query 'PRINT myArray'
./dbms --file ../source/file.data --query 'PRINT myList'
```

### ISMEMBER
Проверяет наличие элемента в контейнере (TRUE/FALSE).
```bash
./dbms --file ../source/file.data --query 'ISMEMBER myArray value'
./dbms --file ../source/file.data --query 'ISMEMBER myList item'
./dbms --file ../source/file.data --query 'ISMEMBER myTree 50'
```

---

## Примечания

1. **Именование контейнеров**: Каждый контейнер имеет уникальное имя. Можно создавать несколько контейнеров одного типа с разными именами.

2. **Автоматическое создание**: Если контейнер не существует, он будет создан при первом добавлении элемента.

3. **Автоматическое удаление**: Если из контейнера удаляется последний элемент, контейнер полностью удаляется из файла.

4. **Персистентность**: Все изменения автоматически сохраняются в указанный файл.

5. **Формат файла**: Данные хранятся в текстовом формате с секциями вида `[TYPE:name]`, где TYPE - тип контейнера, name - его имя.

---

## Соответствие требованиям задания

### a. Массив ✅
- ✅ Создание (автоматическое при первом добавлении)
- ✅ Добавление элемента по индексу (MINS)
- ✅ Добавление элемента в конец массива (MPUSH)
- ✅ Получение элемента по индексу (MGET)
- ✅ Удаление элемента по индексу (MDEL)
- ✅ Замена элемента по индексу (MREP)
- ✅ Длина массива (MLEN)
- ✅ Чтение (MREAD)

### b. Односвязный список ✅
- ✅ Добавление в голову (FADDHEAD)
- ✅ Добавление в хвост (FADDTAIL)
- ✅ Добавление до элемента (FADDBEFORE)
- ✅ Добавление после элемента (FADDAFTER)
- ✅ Удаление элемента по значению (FDEL)
- ✅ Поиск элемента по значению (FGET)
- ✅ Чтение (FREAD)

### c. Двусвязный список ✅
- ✅ Добавление в голову (LADDHEAD)
- ✅ Добавление в хвост (LADDTAIL)
- ✅ Добавление до элемента (LADDBEFORE)
- ✅ Добавление после элемента (LADDAFTER)
- ✅ Удаление элемента по значению (LDEL)
- ✅ Поиск элемента по значению (LGET)
- ✅ Чтение (LREAD)

### d. Стек ✅
- ✅ Добавление элемента (SPUSH - push)
- ✅ Удаление элемента (SPOP - pop)
- ✅ Чтение (SREAD)

### e. Очередь ✅
- ✅ Добавление элемента (QPUSH - enqueue)
- ✅ Удаление элемента (QPOP - dequeue)
- ✅ Чтение (QREAD)

### f. АВЛ-дерево (вариант 2) ✅
- ✅ Добавление элемента (TINS)
- ✅ Поиск элемента (TGET)
- ✅ Удаление элемента с сохранением структуры (TDEL)
- ✅ Чтение (TREAD - in-order обход)

