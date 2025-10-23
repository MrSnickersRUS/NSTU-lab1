package containers

import (
	"fmt"
)

// ArrayNode представляет узел массива
type ArrayNode struct {
	Data string
	Next *ArrayNode
}

// Array представляет динамический массив на основе связного списка
type Array struct {
	Head *ArrayNode
	Size int
}

// NewArray создает новый массив
func NewArray() *Array {
	return &Array{
		Head: nil,
		Size: 0,
	}
}

// Add добавляет элемент в конец массива
func (a *Array) Add(value string) {
	newNode := &ArrayNode{Data: value, Next: nil}
	
	if a.Head == nil {
		a.Head = newNode
	} else {
		current := a.Head
		for current.Next != nil {
			current = current.Next
		}
		current.Next = newNode
	}
	a.Size++
}

// AddAt добавляет элемент по указанному индексу
func (a *Array) AddAt(value string, index int) error {
	if index < 0 || index > a.Size {
		return fmt.Errorf("Ошибка: индекс выходит за границы массива")
	}

	newNode := &ArrayNode{Data: value, Next: nil}

	if index == 0 {
		newNode.Next = a.Head
		a.Head = newNode
	} else {
		current := a.Head
		for i := 0; i < index-1; i++ {
			current = current.Next
		}
		newNode.Next = current.Next
		current.Next = newNode
	}
	a.Size++
	return nil
}

// Get возвращает элемент по индексу
func (a *Array) Get(index int) (string, error) {
	if index < 0 || index >= a.Size {
		return "", fmt.Errorf("Ошибка: индекс выходит за границы массива")
	}

	current := a.Head
	for i := 0; i < index; i++ {
		current = current.Next
	}
	return current.Data, nil
}

// Remove удаляет элемент по индексу
func (a *Array) Remove(index int) error {
	if index < 0 || index >= a.Size {
		return fmt.Errorf("Ошибка: индекс выходит за границы массива")
	}

	if index == 0 {
		a.Head = a.Head.Next
	} else {
		current := a.Head
		for i := 0; i < index-1; i++ {
			current = current.Next
		}
		current.Next = current.Next.Next
	}
	a.Size--
	return nil
}

// Replace заменяет элемент по индексу
func (a *Array) Replace(index int, value string) error {
	if index < 0 || index >= a.Size {
		return fmt.Errorf("Ошибка: индекс выходит за границы массива")
	}

	current := a.Head
	for i := 0; i < index; i++ {
		current = current.Next
	}
	current.Data = value
	return nil
}

// Length возвращает длину массива
func (a *Array) Length() int {
	return a.Size
}

// Read выводит все элементы массива
func (a *Array) Read() {
	current := a.Head
	for current != nil {
		fmt.Print(current.Data, " ")
		current = current.Next
	}
	fmt.Println()
}

// ToSlice преобразует массив в срез строк
func (a *Array) ToSlice() []string {
	result := make([]string, 0, a.Size)
	current := a.Head
	for current != nil {
		result = append(result, current.Data)
		current = current.Next
	}
	return result
}

// Clear очищает массив
func (a *Array) Clear() {
	a.Head = nil
	a.Size = 0
}
