package containers

import "fmt"

// SingleListNode представляет узел односвязного списка
type SingleListNode struct {
	Data string
	Next *SingleListNode
}

// SingleList представляет односвязный список
type SingleList struct {
	Head *SingleListNode
}

// NewSingleList создает новый односвязный список
func NewSingleList() *SingleList {
	return &SingleList{Head: nil}
}

// Add добавляет элемент в конец списка
func (sl *SingleList) Add(value string) {
	newNode := &SingleListNode{Data: value, Next: nil}

	if sl.Head == nil {
		sl.Head = newNode
		return
	}

	current := sl.Head
	for current.Next != nil {
		current = current.Next
	}
	current.Next = newNode
}

// AddHead добавляет элемент в начало списка
func (sl *SingleList) AddHead(value string) {
	newNode := &SingleListNode{Data: value, Next: sl.Head}
	sl.Head = newNode
}

// AddTail добавляет элемент в конец списка
func (sl *SingleList) AddTail(value string) {
	sl.Add(value)
}

// AddBefore добавляет элемент перед указанным значением
func (sl *SingleList) AddBefore(target, value string) error {
	if sl.Head == nil {
		return fmt.Errorf("список пуст")
	}

	if sl.Head.Data == target {
		sl.AddHead(value)
		return nil
	}

	current := sl.Head
	for current.Next != nil && current.Next.Data != target {
		current = current.Next
	}

	if current.Next == nil {
		return fmt.Errorf("элемент '%s' не найден", target)
	}

	newNode := &SingleListNode{Data: value, Next: current.Next}
	current.Next = newNode
	return nil
}

// AddAfter добавляет элемент после указанного значения
func (sl *SingleList) AddAfter(target, value string) error {
	current := sl.Head
	for current != nil && current.Data != target {
		current = current.Next
	}

	if current == nil {
		return fmt.Errorf("элемент '%s' не найден", target)
	}

	newNode := &SingleListNode{Data: value, Next: current.Next}
	current.Next = newNode
	return nil
}

// Remove удаляет элемент из списка по значению
func (sl *SingleList) Remove(value string) error {
	if sl.Head == nil {
		return fmt.Errorf("список пуст")
	}

	if sl.Head.Data == value {
		sl.Head = sl.Head.Next
		return nil
	}

	current := sl.Head
	for current.Next != nil && current.Next.Data != value {
		current = current.Next
	}

	if current.Next == nil {
		return fmt.Errorf("элемент '%s' не найден в списке", value)
	}

	current.Next = current.Next.Next
	return nil
}

// RemoveHead удаляет элемент с головы списка
func (sl *SingleList) RemoveHead() error {
	if sl.Head == nil {
		return fmt.Errorf("список пуст")
	}
	sl.Head = sl.Head.Next
	return nil
}

// RemoveTail удаляет элемент с хвоста списка
func (sl *SingleList) RemoveTail() error {
	if sl.Head == nil {
		return fmt.Errorf("список пуст")
	}

	if sl.Head.Next == nil {
		sl.Head = nil
		return nil
	}

	current := sl.Head
	for current.Next.Next != nil {
		current = current.Next
	}
	current.Next = nil
	return nil
}

// RemoveBefore удаляет элемент перед указанным значением
func (sl *SingleList) RemoveBefore(target string) error {
	if sl.Head == nil {
		return fmt.Errorf("список пуст")
	}

	if sl.Head.Data == target || sl.Head.Next == nil {
		return fmt.Errorf("недостаточно элементов в списке")
	}

	if sl.Head.Next.Data == target {
		sl.Head = sl.Head.Next
		return nil
	}

	prev := sl.Head
	current := prev.Next

	for current.Next != nil {
		if current.Next.Data == target {
			prev.Next = current.Next
			return nil
		}
		prev = current
		current = current.Next
	}
	return fmt.Errorf("элемент '%s' не найден или перед ним нет элемента", target)
}

// RemoveAfter удаляет элемент после указанного значения
func (sl *SingleList) RemoveAfter(target string) error {
	if sl.Head == nil {
		return fmt.Errorf("список пуст")
	}

	current := sl.Head
	for current != nil && current.Next != nil {
		if current.Data == target {
			current.Next = current.Next.Next
			return nil
		}
		current = current.Next
	}

	return fmt.Errorf("элемент '%s' не найден или после него нет элемента", target)
}

// IsIn проверяет наличие элемента в списке
func (sl *SingleList) IsIn(value string) bool {
	current := sl.Head
	for current != nil {
		if current.Data == value {
			return true
		}
		current = current.Next
	}
	return false
}

// FindIndex возвращает индекс элемента в списке (-1 если не найден)
func (sl *SingleList) FindIndex(value string) int {
	current := sl.Head
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

// GetElement возвращает элемент по индексу
func (sl *SingleList) GetElement(index int) (string, error) {
	if index < 0 {
		return "", fmt.Errorf("индекс не может быть отрицательным")
	}

	current := sl.Head
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
func (sl *SingleList) GetHead() (string, error) {
	if sl.Head == nil {
		return "", fmt.Errorf("список пуст")
	}
	return sl.Head.Data, nil
}

// GetTail возвращает последний элемент (хвост)
func (sl *SingleList) GetTail() (string, error) {
	if sl.Head == nil {
		return "", fmt.Errorf("список пуст")
	}

	current := sl.Head
	for current.Next != nil {
		current = current.Next
	}
	return current.Data, nil
}

// Size возвращает размер списка
func (sl *SingleList) Size() int {
	size := 0
	current := sl.Head
	for current != nil {
		size++
		current = current.Next
	}
	return size
}

// Read выводит все элементы списка
func (sl *SingleList) Read() {
	current := sl.Head
	for current != nil {
		fmt.Print(current.Data, " ")
		current = current.Next
	}
	fmt.Println()
}

// ToSlice преобразует список в срез строк
func (sl *SingleList) ToSlice() []string {
	result := []string{}
	current := sl.Head
	for current != nil {
		result = append(result, current.Data)
		current = current.Next
	}
	return result
}

// Clear очищает список
func (sl *SingleList) Clear() {
	sl.Head = nil
}

// IsEmpty проверяет, пуст ли список
func (sl *SingleList) IsEmpty() bool {
	return sl.Head == nil
}
