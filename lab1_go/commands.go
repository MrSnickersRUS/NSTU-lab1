package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"

	"lab1_go/containers"
)

// Глобальные хранилища для именованных структур данных
var (
	arrays      = make(map[string]*containers.Array)
	singleLists = make(map[string]*containers.SingleList)
	doubleLists = make(map[string]*containers.DoubleList)
	stacks      = make(map[string]*containers.Stack)
	queues      = make(map[string]*containers.Queue)
)

// SaveAllContainers сохраняет все контейнеры в файл
func SaveAllContainers(filePath string) error {
	file, err := os.Create(filePath)
	if err != nil {
		return fmt.Errorf("Ошибка: невозможно открыть файл для записи")
	}
	defer file.Close()

	writer := bufio.NewWriter(file)

	// Сохраняем массивы
	for name, arr := range arrays {
		fmt.Fprintf(writer, "[ARRAY:%s]\n", name)
		for _, value := range arr.ToSlice() {
			fmt.Fprintln(writer, value)
		}
	}

	// Сохраняем односвязные списки
	for name, list := range singleLists {
		fmt.Fprintf(writer, "[SINGLE_LIST:%s]\n", name)
		for _, value := range list.ToSlice() {
			fmt.Fprintln(writer, value)
		}
	}

	// Сохраняем двусвязные списки
	for name, list := range doubleLists {
		fmt.Fprintf(writer, "[DOUBLE_LIST:%s]\n", name)
		for _, value := range list.ToSlice() {
			fmt.Fprintln(writer, value)
		}
	}

	// Сохраняем стеки
	for name, stack := range stacks {
		fmt.Fprintf(writer, "[STACK:%s]\n", name)
		for _, value := range stack.ToSlice() {
			fmt.Fprintln(writer, value)
		}
	}

	// Сохраняем очереди
	for name, queue := range queues {
		fmt.Fprintf(writer, "[QUEUE:%s]\n", name)
		for _, value := range queue.ToSlice() {
			fmt.Fprintln(writer, value)
		}
	}

	return writer.Flush()
}

// LoadAllContainers загружает все контейнеры из файла
func LoadAllContainers(filePath string) error {
	file, err := os.Open(filePath)
	if err != nil {
		// Файл не существует - это нормально при первом запуске
		if os.IsNotExist(err) {
			return nil
		}
		return err
	}
	defer file.Close()

	// Очищаем все контейнеры перед загрузкой
	arrays = make(map[string]*containers.Array)
	singleLists = make(map[string]*containers.SingleList)
	doubleLists = make(map[string]*containers.DoubleList)
	stacks = make(map[string]*containers.Stack)
	queues = make(map[string]*containers.Queue)

	scanner := bufio.NewScanner(file)
	currentSection := ""
	currentName := ""

	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			continue
		}

		// Проверяем, является ли строка заголовком секции
		if strings.HasPrefix(line, "[") && strings.HasSuffix(line, "]") {
			header := line[1 : len(line)-1]
			parts := strings.Split(header, ":")

			if len(parts) == 2 {
				currentSection = parts[0]
				currentName = parts[1]
			} else {
				currentSection = header
				currentName = "default"
			}

			// Инициализируем контейнеры
			switch currentSection {
			case "ARRAY":
				if _, exists := arrays[currentName]; !exists {
					arrays[currentName] = containers.NewArray()
				}
			case "SINGLE_LIST":
				if _, exists := singleLists[currentName]; !exists {
					singleLists[currentName] = containers.NewSingleList()
				}
			case "DOUBLE_LIST":
				if _, exists := doubleLists[currentName]; !exists {
					doubleLists[currentName] = containers.NewDoubleList()
				}
			case "STACK":
				if _, exists := stacks[currentName]; !exists {
					stacks[currentName] = containers.NewStack()
				}
			case "QUEUE":
				if _, exists := queues[currentName]; !exists {
					queues[currentName] = containers.NewQueue()
				}
			}
		} else {
			// Загружаем данные в соответствующий контейнер
			switch currentSection {
			case "ARRAY":
				arrays[currentName].Add(line)
			case "SINGLE_LIST":
				singleLists[currentName].Add(line)
			case "DOUBLE_LIST":
				doubleLists[currentName].AddTail(line)
			case "STACK":
				stacks[currentName].Push(line)
			case "QUEUE":
				queues[currentName].Enqueue(line)
			}
		}
	}

	return scanner.Err()
}

// ProcessQuery обрабатывает команду
func ProcessQuery(query, filePath string) error {
	// Загружаем все контейнеры из файла
	if err := LoadAllContainers(filePath); err != nil {
		return err
	}

	parts := strings.Fields(query)
	if len(parts) == 0 {
		return fmt.Errorf("Ошибка: пустая команда")
	}

	command := parts[0]
	isNeedSave := false

	// Обработка команды PRINT
	if command == "PRINT" {
		if len(parts) < 2 {
			return fmt.Errorf("Ошибка: недостаточно аргументов для команды PRINT")
		}
		containerName := parts[1]

		if arr, exists := arrays[containerName]; exists {
			arr.Read()
		} else if list, exists := singleLists[containerName]; exists {
			list.Read()
		} else if list, exists := doubleLists[containerName]; exists {
			list.Read()
		} else if stack, exists := stacks[containerName]; exists {
			stack.Read()
		} else if queue, exists := queues[containerName]; exists {
			queue.Read()
		} else {
			return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
		}
		return nil
	}

	// Обработка команды ISMEMBER
	if command == "ISMEMBER" {
		if len(parts) < 3 {
			return fmt.Errorf("Ошибка: недостаточно аргументов для команды ISMEMBER")
		}
		containerName := parts[1]
		value := parts[2]
		found := false

		if arr, exists := arrays[containerName]; exists {
			for i := 0; i < arr.Length(); i++ {
				if val, _ := arr.Get(i); val == value {
					found = true
					break
				}
			}
		} else if list, exists := singleLists[containerName]; exists {
			found = list.IsIn(value)
		} else if list, exists := doubleLists[containerName]; exists {
			found = list.IsIn(value)
		} else {
			return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
		}

		if found {
			fmt.Println("TRUE")
		} else {
			fmt.Println("FALSE")
		}
		return nil
	}

	// Парсим команду формата XOPER
	if len(command) < 2 {
		return fmt.Errorf("Неизвестная команда: %s", command)
	}

	structureKey := string(command[0])
	operationKey := command[1:]

	if len(parts) < 2 {
		return fmt.Errorf("Ошибка: недостаточно аргументов")
	}

	containerName := parts[1]

	// Обработка команд для массива (M)
	if structureKey == "M" {
		switch operationKey {
		case "PUSH":
			if len(parts) < 3 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			if _, exists := arrays[containerName]; !exists {
				arrays[containerName] = containers.NewArray()
			}
			arrays[containerName].Add(parts[2])
			isNeedSave = true

		case "INS":
			if len(parts) < 4 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			index, err := strconv.Atoi(parts[2])
			if err != nil {
				return fmt.Errorf("Ошибка: неверный индекс")
			}
			if _, exists := arrays[containerName]; !exists {
				arrays[containerName] = containers.NewArray()
			}
			if err := arrays[containerName].AddAt(parts[3], index); err != nil {
				return err
			}
			isNeedSave = true

		case "DEL":
			if len(parts) < 3 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			index, err := strconv.Atoi(parts[2])
			if err != nil {
				return fmt.Errorf("Ошибка: неверный индекс")
			}
			arr, exists := arrays[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			if err := arr.Remove(index); err != nil {
				return err
			}
			if arr.Length() == 0 {
				delete(arrays, containerName)
			}
			isNeedSave = true

		case "GET":
			if len(parts) < 3 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			index, err := strconv.Atoi(parts[2])
			if err != nil {
				return fmt.Errorf("Ошибка: неверный индекс")
			}
			arr, exists := arrays[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			value, err := arr.Get(index)
			if err != nil {
				return err
			}
			fmt.Println(value)

		case "REP":
			if len(parts) < 4 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			index, err := strconv.Atoi(parts[2])
			if err != nil {
				return fmt.Errorf("Ошибка: неверный индекс")
			}
			arr, exists := arrays[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			if err := arr.Replace(index, parts[3]); err != nil {
				return err
			}
			isNeedSave = true

		case "LEN":
			arr, exists := arrays[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			fmt.Println(arr.Length())

		case "READ":
			arr, exists := arrays[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			arr.Read()

		default:
			return fmt.Errorf("Неизвестная операция: %s", operationKey)
		}
	}

	// Обработка команд для односвязного списка (F)
	if structureKey == "F" {
		switch operationKey {
		case "PUSH":
			if len(parts) < 3 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			if _, exists := singleLists[containerName]; !exists {
				singleLists[containerName] = containers.NewSingleList()
			}
			singleLists[containerName].Add(parts[2])
			isNeedSave = true

		case "ADDHEAD":
			if len(parts) < 3 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			if _, exists := singleLists[containerName]; !exists {
				singleLists[containerName] = containers.NewSingleList()
			}
			singleLists[containerName].AddHead(parts[2])
			isNeedSave = true

		case "ADDTAIL":
			if len(parts) < 3 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			if _, exists := singleLists[containerName]; !exists {
				singleLists[containerName] = containers.NewSingleList()
			}
			singleLists[containerName].AddTail(parts[2])
			isNeedSave = true

		case "ADDBEFORE":
			if len(parts) < 4 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			list, exists := singleLists[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			if err := list.AddBefore(parts[2], parts[3]); err != nil {
				return err
			}
			fmt.Printf("Элемент '%s' добавлен перед '%s'\n", parts[3], parts[2])
			isNeedSave = true

		case "ADDAFTER":
			if len(parts) < 4 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			list, exists := singleLists[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			if err := list.AddAfter(parts[2], parts[3]); err != nil {
				return err
			}
			fmt.Printf("Элемент '%s' добавлен после '%s'\n", parts[3], parts[2])
			isNeedSave = true

		case "DEL":
			if len(parts) < 3 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			list, exists := singleLists[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			if err := list.Remove(parts[2]); err != nil {
				return err
			}
			if list.IsEmpty() {
				delete(singleLists, containerName)
			}
			fmt.Printf("Элемент '%s' успешно удален\n", parts[2])
			isNeedSave = true

		case "GET":
			if len(parts) < 3 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			list, exists := singleLists[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			if list.IsIn(parts[2]) {
				fmt.Println("Найдено")
			} else {
				fmt.Println("Не найдено")
			}

		case "READ":
			list, exists := singleLists[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			list.Read()

		default:
			return fmt.Errorf("Неизвестная операция: %s", operationKey)
		}
	}

	// Обработка команд для двусвязного списка (L)
	if structureKey == "L" {
		switch operationKey {
		case "PUSH":
			if len(parts) < 3 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			if _, exists := doubleLists[containerName]; !exists {
				doubleLists[containerName] = containers.NewDoubleList()
			}
			doubleLists[containerName].AddTail(parts[2])
			isNeedSave = true

		case "ADDHEAD":
			if len(parts) < 3 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			if _, exists := doubleLists[containerName]; !exists {
				doubleLists[containerName] = containers.NewDoubleList()
			}
			doubleLists[containerName].AddHead(parts[2])
			isNeedSave = true

		case "ADDTAIL":
			if len(parts) < 3 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			if _, exists := doubleLists[containerName]; !exists {
				doubleLists[containerName] = containers.NewDoubleList()
			}
			doubleLists[containerName].AddTail(parts[2])
			isNeedSave = true

		case "ADDBEFORE":
			if len(parts) < 4 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			list, exists := doubleLists[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			if err := list.AddBefore(parts[2], parts[3]); err != nil {
				return err
			}
			fmt.Printf("Элемент '%s' добавлен перед '%s'\n", parts[3], parts[2])
			isNeedSave = true

		case "ADDAFTER":
			if len(parts) < 4 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			list, exists := doubleLists[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			if err := list.AddAfter(parts[2], parts[3]); err != nil {
				return err
			}
			fmt.Printf("Элемент '%s' добавлен после '%s'\n", parts[3], parts[2])
			isNeedSave = true

		case "DEL":
			if len(parts) < 3 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			list, exists := doubleLists[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			if err := list.Remove(parts[2]); err != nil {
				return err
			}
			if list.IsEmpty() {
				delete(doubleLists, containerName)
			}
			fmt.Printf("Элемент '%s' успешно удален\n", parts[2])
			isNeedSave = true

		case "GET":
			if len(parts) < 3 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			list, exists := doubleLists[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			if list.IsIn(parts[2]) {
				fmt.Println("Найдено")
			} else {
				fmt.Println("Не найдено")
			}

		case "READ":
			list, exists := doubleLists[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			list.Read()

		default:
			return fmt.Errorf("Неизвестная операция: %s", operationKey)
		}
	}

	// Обработка команд для очереди (Q)
	if structureKey == "Q" {
		switch operationKey {
		case "PUSH":
			if len(parts) < 3 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			if _, exists := queues[containerName]; !exists {
				queues[containerName] = containers.NewQueue()
			}
			queues[containerName].Enqueue(parts[2])
			isNeedSave = true

		case "POP":
			queue, exists := queues[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			value, err := queue.Dequeue()
			if err != nil {
				return err
			}
			fmt.Println(value)
			if queue.IsEmpty() {
				delete(queues, containerName)
			}
			isNeedSave = true

		case "READ":
			queue, exists := queues[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			queue.Read()

		default:
			return fmt.Errorf("Неизвестная операция: %s", operationKey)
		}
	}

	// Обработка команд для стека (S)
	if structureKey == "S" {
		switch operationKey {
		case "PUSH":
			if len(parts) < 3 {
				return fmt.Errorf("Ошибка: недостаточно аргументов")
			}
			if _, exists := stacks[containerName]; !exists {
				stacks[containerName] = containers.NewStack()
			}
			stacks[containerName].Push(parts[2])
			isNeedSave = true

		case "POP":
			stack, exists := stacks[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			value, err := stack.Pop()
			if err != nil {
				return err
			}
			fmt.Println(value)
			if stack.IsEmpty() {
				delete(stacks, containerName)
			}
			isNeedSave = true

		case "READ":
			stack, exists := stacks[containerName]
			if !exists {
				return fmt.Errorf("Ошибка: контейнер '%s' не найден", containerName)
			}
			stack.Read()

		default:
			return fmt.Errorf("Неизвестная операция: %s", operationKey)
		}
	}

	// Сохраняем данные в файл, если были изменения
	if isNeedSave {
		return SaveAllContainers(filePath)
	}

	return nil
}
