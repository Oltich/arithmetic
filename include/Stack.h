#pragma once

#include <iostream>
#include <stdexcept>

const int MaxMemSize = 255;

template <class T>
class TStack {
protected:
  T* pMem;
  int MemSize;
  int Hi;
  int DataCount;

  int GetNextIndex(int index) { return index + 1; }

public:
  TStack(int size = MaxMemSize);
  TStack(const TStack& other);
  ~TStack();

  bool IsEmpty() const;
  bool IsFull() const;
  void Push(const T& val);
  T Pop();
  T Top() const;

  TStack& operator=(const TStack& other);
};

template <class T>
TStack<T>::TStack(int size) : MemSize(size), Hi(-1), DataCount(0) {
  if (size <= 0) throw std::invalid_argument("Stack size must be positive");
  pMem = new T[MemSize];
}

template <class T>
TStack<T>::TStack(const TStack& other) : MemSize(other.MemSize), Hi(other.Hi), DataCount(other.DataCount) {
  pMem = new T[MemSize];
  for (int i = 0; i <= Hi; i++)
    pMem[i] = other.pMem[i];
}

template <class T>
TStack<T>::~TStack() {
  delete[] pMem;
}

template <class T>
bool TStack<T>::IsEmpty() const {
  return Hi == -1;
}

template <class T>
bool TStack<T>::IsFull() const {
  return Hi == MemSize - 1;
}

template <class T>
void TStack<T>::Push(const T& val) {
  if (IsFull()) throw std::overflow_error("Stack overflow");
  pMem[++Hi] = val;
  DataCount++;
}

template <class T>
T TStack<T>::Pop() {
  if (IsEmpty()) throw std::underflow_error("Stack underflow");
  DataCount--;
  return pMem[Hi--];
}

template <class T>
T TStack<T>::Top() const {
  if (IsEmpty()) throw std::underflow_error("Stack is empty");
  return pMem[Hi];
}

template <class T>
TStack<T>& TStack<T>::operator=(const TStack& other) {
  if (this != &other) {
    delete[] pMem;
    MemSize = other.MemSize;
    Hi = other.Hi;
    DataCount = other.DataCount;
    pMem = new T[MemSize];
    for (int i = 0; i <= Hi; i++)
      pMem[i] = other.pMem[i];
  }
  return *this;
}
