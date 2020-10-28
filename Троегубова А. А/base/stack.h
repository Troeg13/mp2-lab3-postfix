#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
	T *pMem;
	int size;
	int top;
public:

	TStack(int _size);
	~TStack();
	bool IsEmpty();
	bool IsFull();
	void Put(T elem);
	T Get();
	int Cardinality();
	int GetSize();
	T Head();
};

template <class T>
TStack<T>::TStack(int _size) : size(_size), top(-1)
{
	if ((size < 1) || (size > MaxStackSize))
		throw size;
	pMem = new T[size];
}

template <class T>
TStack<T>::~TStack()
{
	delete[] pMem;
	pMem = nullptr;
}

template <class T>
bool TStack<T>::IsEmpty()
{
	if (top == -1) return 1;
	return 0;
}

template <class T>
bool TStack<T>::IsFull()
{
	if (top == (size - 1)) return 1;
	return 0;
}


template <class T>
void TStack<T>::Put(T elem)
{
	if (IsFull())
		throw -1;
	pMem[++top] = elem;
}

template <class T>
T TStack<T>::Get()
{
	if (IsEmpty()) 
		throw -1;
	return pMem[top--];
}

template <class T>
int TStack<T>::Cardinality()
{
	return top + 1;
}

template <class T>
int TStack<T>::GetSize()
{
	return size;
}

template <class T>
T TStack<T>::Head()
{
	if (IsEmpty()) throw;
	return pMem[top];
}

#endif