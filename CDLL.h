#pragma once
#include <assert.h>
#include <iostream>
//#include <vld.h>


template <class T>
class CircularDoublyLinkedList {

private:

	class Node {
	public:
		Node(T v, Node *n, Node *p) : value(v), next(n), prev(p) {}
		T value;
		Node *next;
		Node *prev;
	};

	Node *m_head;
	Node *m_tail;
	unsigned int m_size;

public:
	CircularDoublyLinkedList();
	~CircularDoublyLinkedList();
	unsigned int size() const;
	bool isEmpty() const;
	void addHead(T item);
	void addTail(T item);
	T retrieveHead() const;
	T retrieveTail() const;
	T retrieve(unsigned int n) const;
	T removeHead();
	T removeTail();
	void add(unsigned int n, T item);
	T remove(unsigned int n);
	T replace(unsigned int n, T item);
	


	void shiftLeft();
	void shiftRight();
	void shiftLeftParameter(int x);


	class Iterator {
	private:
		Node* m_ptr;    // an iterator hides a pointer to node
	public:
		Iterator() {}
		Iterator(Node* ptr) { m_ptr = ptr; }
		void operator++ () { m_ptr = m_ptr->next; } // for forward traversing, e,g, Iterator i=begin(); ... ++i;
		bool operator != (const Iterator& b) { return m_ptr != b.m_ptr; }
		void operator-- () { m_ptr = m_ptr->prev; }	//for backwards traversing
		T operator *() { return m_ptr->value; }
		T getValue() { return m_ptr->value; }
		void setValue(T val) { m_ptr->value = val; }
	};

	// linked list objects create forward-traversal iterators using the two functions below
	Iterator begin() { return Iterator(m_head); }
	Iterator end() { return Iterator(m_tail); }



};


template <class T>
void CircularDoublyLinkedList<T>::shiftLeft()
{
	int answer;
	std::cout << "How many spaces? ";
	std::cin >> answer;
	for (auto i = 0; i < answer; i++) {
		m_head = m_head->next;
		m_tail = m_tail->next;
	}
}

template <class T>
void CircularDoublyLinkedList<T>::shiftLeftParameter(int x)
{

	for (auto i = 0; i < x; i++) {
		m_head = m_head->next;
		m_tail = m_tail->next;
	}
}
template <class T>
void CircularDoublyLinkedList<T>::shiftRight()
{
	int answer;
	std::cout << "How many spaces? ";
	std::cin >> answer;
	for (auto i = 0; i < answer; i++) {
		m_head = m_head->prev;
		m_tail = m_tail->prev;
	}
}



template <class T>
CircularDoublyLinkedList<T> ::CircularDoublyLinkedList() : m_head(nullptr),
m_tail(nullptr), m_size(0) {

}

template <class T>
CircularDoublyLinkedList <T> :: ~CircularDoublyLinkedList() {
	Node * here = m_head, *nextNode;
	while (here != m_tail) {
		nextNode = here->next;
		delete here;
		here = nextNode;

	}
	delete here;

}
template <class T>
unsigned int CircularDoublyLinkedList<T> ::size() const {
	return m_size;
}

template <class T>
void CircularDoublyLinkedList<T> ::addHead(T item) {

	Node* cur = new Node(item, nullptr, nullptr);

	if (m_head == nullptr)
	{
		m_tail = m_head = cur;
	}
	else
	{
		m_head->prev = cur;
		cur->next = m_head;
		cur->prev = m_tail;
		m_head = cur;
	}
	m_tail->next = m_head;
	m_size++;
}
template <class T>
void CircularDoublyLinkedList<T> ::addTail(T item)
{
	if (isEmpty()) addHead(item);
	else
	{
		Node * curr = new Node(item, m_head, m_tail);
		m_tail->next = curr;
		m_tail = curr;
		m_head->prev = m_tail;
		m_size++;
	}
}


template<class T>
T CircularDoublyLinkedList<T>::retrieveHead() const
{
	//	 PRECONDITION: list is not already empty
	assert((!isEmpty() && "LinkedList is Empty (in retrieveHead)"));
	return m_head->value;
}

template <class T>
T CircularDoublyLinkedList<T> ::retrieveTail() const {
	//	 PRECONDITION: list is not already empty
	assert((!isEmpty() && "LinkedList is Empty (in retrieveTail)"));
	return m_tail->value;
}

template <class T>
T CircularDoublyLinkedList<T> ::retrieve(unsigned int n) const
{
	//	 PRECONDITION: n must be a valid current list position
	assert(((n >= 1) && (n <= size()) && "LinkedList index is out of bounds (in retrieve)"));
	if (n == 1) { return retrieveHead(); }
	if (n == size()) return retrieveTail();

	Node * here = m_head;
	for (unsigned int k = 1; k < n; k++)
		here = here->next;
	return here->value;

}

template <class T>
bool CircularDoublyLinkedList<T> ::isEmpty() const {
	return (m_size == 0);
}

template <class T>
CircularDoublyLinkedList<T> Iterator(CircularDoublyLinkedList<T> &a) {
	CircularDoublyLinkedList<T> returnLL;
	for (CircularDoublyLinkedList<int>::Iterator it = a.begin(); it != a.end(); ++it) {
		returnLL.addHead(it.getValue());
	}
	return returnLL;
}

template <class T>
T CircularDoublyLinkedList<T> ::removeHead()
{
	// PRECONDITION: list is not already empty
	assert((!isEmpty() && "LinkedList is Empty (in removeHead)"));
	Node * oldNode = m_tail->next;
	T returnVal = m_head->value;
	m_tail->next = oldNode->next;
	m_head = m_head->next;
	if (oldNode == m_tail) { m_head = m_tail = nullptr; }

	delete oldNode;
	m_size--;
	return returnVal;
}

template <class T>
T CircularDoublyLinkedList<T> ::removeTail()
{
	// PRECONDITION: list is not already empty
	assert((!isEmpty() && "LinkedList is Empty (in removeTail)"));
	if (m_head == m_tail) return removeHead();
	T returnVal = m_tail->value;
	Node * preTail = m_head;
	while (preTail->next != m_tail)
		preTail = preTail->next;
	preTail->next = nullptr;
	delete m_tail;
	m_tail = preTail;
	m_size--;
	return returnVal;
}

template <class T>
void CircularDoublyLinkedList<T> ::add(unsigned int n, T item)
{
	// PRECONDITION: n should be a valid position in the list
	assert(((n >= 1) && (n <= size() + 1) && "LinkedList index is out of bounds (in add)"));
	if (n == 1)          addHead(item);
	else if (n == (size() + 1)) addTail(item);
	else {
		Node * here = m_head;
		for (unsigned int k = 1; k < n - 1; k++)
			here = here->next;
		here->next = new Node(item, here->next, here->prev);
		m_size++;
	}
}

template <class T>
T CircularDoublyLinkedList<T> ::replace(unsigned int n, T item)
{
	// PRECONDITION: n must be a valid current list position
	assert(((n >= 1) && (n <= size()) && "LinkedList index is out of bounds (in replace)"));
	T returnValue;
	Node * here = m_head;
	for (unsigned int k = 1; k < n; k++)
		here = here->next;
	returnValue = here->value;
	here->value = item;
	return returnValue;
}

template <class T>
T CircularDoublyLinkedList<T> ::remove(unsigned int n)
{
	// PRECONDITION: n must be a valid current list position
	assert(((n >= 1) && (n <= size()) && "LinkedList index is out of bounds (in remove)"));
	if (n == 1) return removeHead();
	if (n == size()) return removeTail();

	Node * here = m_head;
	for (unsigned int k = 1; k < n - 1; k++)
		here = here->next;
	Node * kill = here->next;
	T returnVal = kill->value;
	here->next = kill->next;
	here->prev = kill->prev;
	delete kill;
	m_size--;
	return returnVal;
}

