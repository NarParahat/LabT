#ifndef _STACK_
#define _STACK_
#include <iostream>
#include <fstream>
using namespace std;

template <class T>
class TStack
{
protected:
  int length;
  T* x;
  int ind;
public:
  TStack(int size = 100);
  TStack(const TStack<T>& _v);
  ~TStack();
  
  void Push(T d); //Вставка элемента
  T Get(); //Получение элемента
  int IsEmpty(void) const; // контроль пустоты
  int IsFull(void) const; //контроль переполнения

  //Доп задания
  inline int min_elem(); //Поиск минимального элемента
  inline int max_elem(); //Поиск максимального элемента
  inline void file(); //Запись в файл

  TStack<T>& operator =(const TStack<T>& _v);

  template <class T1>
  friend ostream& operator<< (ostream& ostr, const TStack<T1> &A);
  template <class T1>
  friend istream& operator >> (istream& istr, TStack<T1> &A);

  int Length();
};

template <class T1>
ostream& operator<< (ostream& ostr, const TStack<T1> &A) {
  for (int i = 0; i < A.ind; i++) {
    ostr << A.x[i] << endl;
  }
  return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TStack<T1> &A) {
  int count;
  istr >> count;
  for (int i = 0; i < A.count; i++) {
    T1 d;
    istr >> d;
    A.Push(d);
  }
  return istr;
}

template<class T>
inline TStack<T>::TStack(int size)
{
  if (size > 0)
  {
    this->length = size;
    x = new T[length];
    for (int i = 0; i < length; i++)
    {
      x[i] = 0;
    }
    this->ind = 0;
  }
  else
  {
    throw "Error";
  }
}

template <class T>
TStack<T>::TStack(const TStack<T>& _v)
{
  length = _v.length;
  ind = _v.ind;
  x = new T [length];
  for (int i = 0; i < length;i = i + 1)
    x[i] = _v.x[i];
}

template <class T>
TStack<T>::~TStack()
{
  length = 0;
  if (x != 0)
    delete [] x;
  x = 0;
}

//ДОП
template<typename T>
inline int TStack<T>::max_elem()
{
  T res = x[0];
  for (int i = 1; i < length; i++)
  {
    if (x[i] > res)
    {
      res = x[i];
    }
  }
  return res;
}

template<typename T>
inline int TStack<T>::min_elem()
{
  T res = x[0];
  for (int i = 1; i < length; i++)
  {
    if (x[i] < res)
    {
      res = x[i];
    }
  }
  return res;
}

template<typename T>
inline void TStack<T>::file()
{
  ofstream outf("Data.txt");
  if (!outf)
  {
    throw "Error file";
  }
  for (int i = 0; i < length; i++)
  {
    outf << x[i] << endl;
  }
}

template <class T>
TStack<T>& TStack<T>::operator =(const TStack<T>& _v)
{
  if (this == &_v)
    return *this;

  this->length = _v.length;
  if (x != NULL)
  {
    delete[] x;
  }

  this->x = new T [length];
  for (int i = 0; i < length; i++)
    x[i] = _v.x[i];
  this->ind = _v.ind;
  return *this;
}

template<class T>
inline void TStack<T>::Push(T d)
{
  if (ind >= length || ind < 0)
  {
    throw "Error";
  }

  x[ind] = d;
  ind++;
}

template<class T>
inline T TStack<T>::Get()
{
  if (ind == 0)
  {
    throw "Error";
  }

  T d = x[ind-1];
  ind--;
  return d;
}

template<class T>
inline int TStack<T>::IsEmpty(void) const
{
  return ind == 0;
}

template<class T>
inline int TStack<T>::IsFull(void) const
{
  return ind == length;
}

template <class T>
int TStack<T>::Length()
{
  return length;
}
#endif