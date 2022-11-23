template <class T> class DList;
template <class T> class DListIterator;

#pragma once
#include "DListNode.h"
#include "DListIterator.h"

template <class T>
class DList
{
public:
	DListNode<T>* head, * tail;
	int count;

	DList();
	DList(DList<T>& list);
	void append(T item);
	void prepend(T item);
	void removeHead();
	void removeTail();
	DListIterator<T> getIterator();
	void insert(DListIterator<T>& iter, T item);
	DListIterator<T> remove(DListIterator<T>& iter);
	int size();
	~DList();
};

template <class T>
DList<T>::DList(DList<T>& list)
{
	head = nullptr;
	tail = nullptr;
	DListNode<T>* current, * next, * previous;
	current = list.head;
	while (current != nullptr)
	{
		this->append(current->data);
		current = current->next;
	}
}
template <class T>
int DList<T>::size()
{
	return count;
}
template <class T>
DList<T>::DList()
{
	count = 0;
	head = tail = nullptr;
}
template <class T>
void DList<T>::append(T item)
{
	if (head == nullptr)
	{
		head = tail = new DListNode<T>(item);
	}
	else
	{
		tail->insertAfter(item);
		tail = tail->next;
	}
	count++;
}

template <class T>
void DList<T>::prepend(T item)
{
	if (head == nullptr)
	{
		head = tail = new DListNode<T>(item);
	}
	else
	{
		head->insertBefore(item);
		head = head->previous;
	}
	count++;
}

template <class T>
void DList<T>::removeHead()
{
	if (head == nullptr)
	{
		return;
	}
	else if (head == tail)
	{
		delete head;
		head = tail = nullptr;
		count--;
	}
	else
	{
		DListNode<T>* temp = head;
		head = head->next;
		head->previous = nullptr;
		delete temp;
		temp = nullptr;
		count--;
	}
}

template <class T>
void DList<T>::removeTail()
{
	if (head == nullptr)
	{
		return;
	}
	else if (head == tail)
	{
		delete head;
		head = tail = nullptr;
		count--;
	}
	else
	{
		DListNode<T>* temp = tail;
		tail = tail->previous;
		tail->next = nullptr;
		delete temp;
		temp = nullptr;
		count--;
	}
}
template <class T>
DListIterator<T> DList<T>::getIterator()
{
	return DListIterator<T>(this, head);
}
template <class T>
void DList<T>::insert(DListIterator<T>& iter, T item)
{
	if (iter.list != this || !iter.isValid())
	{
		return;
	}
	else if (iter.currentNode == head)
	{
		prepend(item);
	}
	else
	{
		iter.currentNode->insertBefore(item);
		count++;
	}
}

template <class T>
DListIterator<T> DList<T>::remove(DListIterator<T>& iter)
{
	if (iter.list != this || !iter.isValid())
	{
		return  iter;
	}
	else if (iter.currentNode == head)
	{
		iter.advance();
		removeHead();
		return iter;
	}
	else
	{
		DListNode<T>* temp = iter.currentNode->previous;
		if (iter.currentNode == tail)
		{
			tail = temp;
		}
		temp->next = iter.currentNode->next;
		if (temp->next != nullptr)
		{
			temp->next->previous = temp;
		}
		delete iter.currentNode;
		count--;
		return DListIterator<T>(this, temp->next);
	}
	return iter;
}

template <class T>
DList<T>::~DList()
{
	DListNode<T>* iter, * next = nullptr;
	iter = head;
	while (iter != nullptr)
	{
		next = iter->next;
		delete iter;
		iter = next;
	}
	head = nullptr;
	tail = nullptr;
}