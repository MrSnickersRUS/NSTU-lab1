package containers

import "fmt"

// QueueNode представляет узел очереди
type QueueNode struct {
	Data string
	Next *QueueNode
}

// Queue представляет очередь
type Queue struct {
	Front *QueueNode
	Rear  *QueueNode
}

// NewQueue создает новую очередь
func NewQueue() *Queue {
	return &Queue{Front: nil, Rear: nil}
}

// Enqueue добавляет элемент в конец очереди
func (q *Queue) Enqueue(value string) {
	newNode := &QueueNode{Data: value, Next: nil}
	
	if q.Rear == nil {
		q.Front = newNode
		q.Rear = newNode
	} else {
		q.Rear.Next = newNode
		q.Rear = newNode
	}
}

// Dequeue удаляет и возвращает элемент из начала очереди
func (q *Queue) Dequeue() (string, error) {
	if q.IsEmpty() {
		return "", fmt.Errorf("Ошибка: очередь пуста")
	}

	value := q.Front.Data
	q.Front = q.Front.Next
	
	if q.Front == nil {
		q.Rear = nil
	}
	
	return value, nil
}

// IsEmpty проверяет, пуста ли очередь
func (q *Queue) IsEmpty() bool {
	return q.Front == nil
}

// Read выводит все элементы очереди
func (q *Queue) Read() {
	current := q.Front
	for current != nil {
		fmt.Print(current.Data, " ")
		current = current.Next
	}
	fmt.Println()
}

// ToSlice преобразует очередь в срез строк
func (q *Queue) ToSlice() []string {
	result := []string{}
	current := q.Front
	for current != nil {
		result = append(result, current.Data)
		current = current.Next
	}
	return result
}

// Clear очищает очередь
func (q *Queue) Clear() {
	q.Front = nil
	q.Rear = nil
}
