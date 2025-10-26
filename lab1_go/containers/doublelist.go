package containers

import "fmt"

// DoubleListNode представляет узел двусвязного списка
type DoubleListNode struct {
	Data string
	Prev *DoubleListNode
	Next *DoubleListNode
}

// DoubleList представляет двусвязный список
type DoubleList struct {
	Head *DoubleListNode
	Tail *DoubleListNode
}

// NewDoubleList создает новый двусвязный список
func NewDoubleList() *DoubleList {
	return &DoubleList{Head: nil, Tail: nil}
}

// AddHead добавляет элемент в начало списка
func (dl *DoubleList) AddHead(value string) {
	newNode := &DoubleListNode{Data: value, Prev: nil, Next: dl.Head}

	if dl.Head == nil {
		dl.Head = newNode
		dl.Tail = newNode
	} else {
		dl.Head.Prev = newNode
		dl.Head = newNode
	}
}

// AddTail добавляет элемент в конец списка
func (dl *DoubleList) AddTail(value string) {
	newNode := &DoubleListNode{Data: value, Prev: dl.Tail, Next: nil}

	if dl.Tail == nil {
		dl.Head = newNode
		dl.Tail = newNode
	} else {
		dl.Tail.Next = newNode
		dl.Tail = newNode
	}
}

// AddBefore добавляет элемент перед указанным значением
func (dl *DoubleList) AddBefore(target, value string) error {
	current := dl.Head
	for current != nil && current.Data != target {
		current = current.Next
	}

	if current == nil {
		return fmt.Errorf("элемент '%s' не найден", target)
	}

	newNode := &DoubleListNode{Data: value, Prev: current.Prev, Next: current}

	if current.Prev != nil {
		current.Prev.Next = newNode
	} else {
		dl.Head = newNode
	}
	current.Prev = newNode
	return nil
}

// AddAfter добавляет элемент после указанного значения
func (dl *DoubleList) AddAfter(target, value string) error {
	current := dl.Head
	for current != nil && current.Data != target {
		current = current.Next
	}

	if current == nil {
		return fmt.Errorf("элемент '%s' не найден", target)
	}

	newNode := &DoubleListNode{Data: value, Prev: current, Next: current.Next}

	if current.Next != nil {
		current.Next.Prev = newNode
	} else {
		dl.Tail = newNode
	}
	current.Next = newNode
	return nil
}

// Remove удаляет элемент из списка по значению
func (dl *DoubleList) Remove(value string) error {
	current := dl.Head
	for current != nil && current.Data != value {
		current = current.Next
	}

	if current == nil {
		return fmt.Errorf("элемент '%s' не найден в списке", value)
	}

	if current.Prev != nil {
		current.Prev.Next = current.Next
	} else {
		dl.Head = current.Next
	}

	if current.Next != nil {
		current.Next.Prev = current.Prev
	} else {
		dl.Tail = current.Prev
	}

	return nil
}

// RemoveHead удаляет элемент с головы списка
func (dl *DoubleList) RemoveHead() error {
	if dl.Head == nil {
		return fmt.Errorf("список пуст")
	}

	dl.Head = dl.Head.Next
	if dl.Head != nil {
		dl.Head.Prev = nil
	} else {
		dl.Tail = nil
	}
	return nil
}

// RemoveTail удаляет элемент с хвоста списка
func (dl *DoubleList) RemoveTail() error {
	if dl.Tail == nil {
		return fmt.Errorf("список пуст")
	}

	dl.Tail = dl.Tail.Prev
	if dl.Tail != nil {
		dl.Tail.Next = nil
	} else {
		dl.Head = nil
	}
	return nil
}

// RemoveBefore удаляет элемент перед указанным значением
func (dl *DoubleList) RemoveBefore(target string) error {
	current := dl.Head

	for current != nil {
		if current.Data == target && current.Prev != nil {
			toDelete := current.Prev
			if toDelete.Prev != nil {
				toDelete.Prev.Next = current
			} else {
				dl.Head = current
			}
			current.Prev = toDelete.Prev
			return nil
		}
		current = current.Next
	}

	return fmt.Errorf("элемент '%s' не найден или перед ним нет элемента", target)
}

// RemoveAfter удаляет элемент после указанного значения
func (dl *DoubleList) RemoveAfter(target string) error {
	current := dl.Head

	for current != nil {
		if current.Data == target && current.Next != nil {
			toDelete := current.Next
			if toDelete.Next != nil {
				toDelete.Next.Prev = current
			} else {
				dl.Tail = current
			}
			current.Next = toDelete.Next
			return nil
		}
		current = current.Next
	}

	return fmt.Errorf("элемент '%s' не найден или после него нет элемента", target)
}

// IsIn проверяет наличие элемента в списке
func (dl *DoubleList) IsIn(value string) bool {
	current := dl.Head
	for current != nil {
		if current.Data == value {
			return true
		}
		current = current.Next
	}
	return false
}

// FindIndex возвращает индекс элемента в списке (-1 если не найден)
func (dl *DoubleList) FindIndex(value string) int {
	current := dl.Head
	index := 0
	for current != nil {
		if current.Data == value {
			return index
		}
		current = current.Next
		index++
	}
	return -1
}

// Read выводит все элементы списка (прямой порядок)
func (dl *DoubleList) Read() {
	current := dl.Head
	for current != nil {
		fmt.Print(current.Data, " ")
		current = current.Next
	}
	fmt.Println()
}

// ReadReverse выводит все элементы списка (обратный порядок)
func (dl *DoubleList) ReadReverse() {
	current := dl.Tail
	for current != nil {
		fmt.Print(current.Data, " ")
		current = current.Prev
	}
	fmt.Println()
}

// GetElement возвращает элемент по индексу
func (dl *DoubleList) GetElement(index int) (string, error) {
	if index < 0 {
		return "", fmt.Errorf("индекс не может быть отрицательным")
	}

	current := dl.Head
	currentIndex := 0
	for current != nil {
		if currentIndex == index {
			return current.Data, nil
		}
		current = current.Next
		currentIndex++
	}

	return "", fmt.Errorf("индекс %d выходит за границы списка", index)
}

// GetHead возвращает первый элемент (голову)
func (dl *DoubleList) GetHead() (string, error) {
	if dl.Head == nil {
		return "", fmt.Errorf("список пуст")
	}
	return dl.Head.Data, nil
}

// GetTail возвращает последний элемент (хвост)
func (dl *DoubleList) GetTail() (string, error) {
	if dl.Tail == nil {
		return "", fmt.Errorf("список пуст")
	}
	return dl.Tail.Data, nil
}

// Size возвращает размер списка
func (dl *DoubleList) Size() int {
	size := 0
	current := dl.Head
	for current != nil {
		size++
		current = current.Next
	}
	return size
}

// ToSlice преобразует список в срез строк
func (dl *DoubleList) ToSlice() []string {
	result := []string{}
	current := dl.Head
	for current != nil {
		result = append(result, current.Data)
		current = current.Next
	}
	return result
}

// Clear очищает список
func (dl *DoubleList) Clear() {
	dl.Head = nil
	dl.Tail = nil
}

// IsEmpty проверяет, пуст ли список
func (dl *DoubleList) IsEmpty() bool {
	return dl.Head == nil
}
