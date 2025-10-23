package containers

import "fmt"

// StackNode представляет узел стека
type StackNode struct {
	Data string
	Next *StackNode
}

// Stack представляет стек
type Stack struct {
	Top *StackNode
}

// NewStack создает новый стек
func NewStack() *Stack {
	return &Stack{Top: nil}
}

// Push добавляет элемент на вершину стека
func (s *Stack) Push(value string) {
	newNode := &StackNode{Data: value, Next: s.Top}
	s.Top = newNode
}

// Pop удаляет и возвращает элемент с вершины стека
func (s *Stack) Pop() (string, error) {
	if s.IsEmpty() {
		return "", fmt.Errorf("Ошибка: стек пуст")
	}

	value := s.Top.Data
	s.Top = s.Top.Next
	return value, nil
}

// IsEmpty проверяет, пуст ли стек
func (s *Stack) IsEmpty() bool {
	return s.Top == nil
}

// Read выводит все элементы стека
func (s *Stack) Read() {
	current := s.Top
	for current != nil {
		fmt.Print(current.Data, " ")
		current = current.Next
	}
	fmt.Println()
}

// ToSlice преобразует стек в срез строк
func (s *Stack) ToSlice() []string {
	result := []string{}
	current := s.Top
	for current != nil {
		result = append(result, current.Data)
		current = current.Next
	}
	return result
}

// Clear очищает стек
func (s *Stack) Clear() {
	s.Top = nil
}
