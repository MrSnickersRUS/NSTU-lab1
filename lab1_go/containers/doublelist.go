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
		return fmt.Errorf("Ошибка: элемент '%s' не найден", target)
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
		return fmt.Errorf("Ошибка: элемент '%s' не найден", target)
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

// Remove удаляет элемент из списка
func (dl *DoubleList) Remove(value string) error {
	current := dl.Head
	for current != nil && current.Data != value {
		current = current.Next
	}

	if current == nil {
		return fmt.Errorf("Ошибка: элемент '%s' не найден в списке", value)
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

// Read выводит все элементы списка
func (dl *DoubleList) Read() {
	current := dl.Head
	for current != nil {
		fmt.Print(current.Data, " ")
		current = current.Next
	}
	fmt.Println()
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
