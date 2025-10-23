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
		return fmt.Errorf("Ошибка: список пуст")
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
		return fmt.Errorf("Ошибка: элемент '%s' не найден", target)
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
		return fmt.Errorf("Ошибка: элемент '%s' не найден", target)
	}

	newNode := &SingleListNode{Data: value, Next: current.Next}
	current.Next = newNode
	return nil
}

// Remove удаляет элемент из списка
func (sl *SingleList) Remove(value string) error {
	if sl.Head == nil {
		return fmt.Errorf("Ошибка: список пуст")
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
		return fmt.Errorf("Ошибка: элемент '%s' не найден в списке", value)
	}

	current.Next = current.Next.Next
	return nil
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
