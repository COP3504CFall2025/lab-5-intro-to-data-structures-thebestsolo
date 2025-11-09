#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
public:
	struct Node {
		T data;
		Node* prev;
		Node* next;
	};
	// Behaviors
	void printForward() const
	{
		Node* current = head;
		while(current != nullptr)
		{
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}
	void printReverse() const
	{
		Node* current = tail;
		while(current != nullptr)
		{
			cout << current->data << " ";
			current = current->prev;
		}
		cout << endl;
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const
	{
		return count;
	}
	Node* getHead()
	{
		return head;
	}
	const Node* getHead() const
	{
		return head;
	}
	Node* getTail()
	{
		return tail;
	}
	const Node* getTail() const
	{
		return tail;
	}

	// Insertion
	void addHead(const T& data)
	{
		Node* temp = new Node();
		temp.data = data;
		temp.next = head;
		head = temp;
	}
	void addTail(const T& data)
	{
		Node* temp = new Node();
		temp.data = data;
		temp.prev = tail;
		tail = temp;
	}

	// Removal
	bool removeHead()
	{
		if(count == 0)
		{
			return false;
		}
		count--;
		if(count == 0)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
			return true;
		}
		Node* temp = head;
		head = head->next;
		head->prev = nullptr;
		delete temp;
		return true;
	}
	bool removeTail()
	{
		if(count == 0)
		{
			return false;
		}
		count--;
		if(count == 0)
		{
			delete tail;
			tail = nullptr;
			head = nullptr;
			return true;
		}
		Node* temp = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete temp;
		return true;
	}
	void Clear()
	{
		while(removeHead());
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept
	{

	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList()
	{
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	LinkedList(const LinkedList<T>& list)
	{
		head = nullptr;
		tail = nullptr;
		count = 0;
		Node* current = list.head;
		while(current != nullptr)
		{
			addTail(current->data);
			current = current->next;
		}
	}
	LinkedList(LinkedList<T>&& other) noexcept
	{
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList()
	{
		Clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};


