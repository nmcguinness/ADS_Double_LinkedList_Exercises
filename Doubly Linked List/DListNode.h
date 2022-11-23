#pragma once

template <class T>
class DListNode
{
public:
	T data;
	DListNode<T>* next;
	DListNode<T>* previous;

	DListNode(T item);
	DListNode(DListNode<T>& item);
	void insertBefore(T item);
	void insertAfter(T item);

	~DListNode()
	{
		//next = nullptr;
		//previous = nullptr;
	}
};

template <class T>
DListNode<T>::DListNode(DListNode<T>& node)
{
	this->data = new DListNode(node->data);
}

template <class T>
DListNode<T>::DListNode(T item)
{
	data = item;
	next = previous = nullptr;
}

template <class T>
void DListNode<T>::insertAfter(T item)
{
}

template <class T>
void DListNode<T>::insertBefore(T item) //inserting "Oslo" between "Paris" and "Munich"
{
	//"new" returns address of a new object in RAM - the node
	DListNode<T>* pNew = new DListNode<T>(item); //Oslo
	DListNode<T>* pLeft = this->previous;        //Paris
	DListNode<T>* pRight = this;				 //Munich

	//lets create the "next" (going right) connections
	pLeft->next = pNew; //Paris -> Oslo
	pNew->next = pRight; //Oslo -> Munich

	//lets create the "previous" (going left) connections
	pRight->previous = pNew; //Munich -> Oslo
	pNew->previous = pLeft;  //Oslo -> Paris

	//TODO - consider edge cases?
}
