#ifndef MyVector_H
#define MyVector_H

#include <initializer_list>
#include <iostream>

#include "VectorException.h"

template <typename T> class MyVector {
private:
    T *internalArray;
    int internalArrayLength;

    // проверяет индекс на соответствие границам массива
    void checkBounds(int index);
public:
    class Iterator
    {
    private:
        MyVector<T> vector;
        int currentIndex = -1;
    public:
        // конструктор, принимающий объект контейнерного класса, который необходимо обойти с помощью
        // данного итератора
        Iterator(MyVector<T> vector);

        // перейти к следующему объекту в контейнере
        Iterator next();

        // получить значение текущего объекта в контейнере
        T value();

        // указывает ли итератор на конечный фиктивный элемент контейнера, следующий за последним
        // реальным. Нужен для определения конца итерирования
        bool is_end();

        // префиксный инкремент, эквивалентен next()
        Iterator &operator++();

        // оператор разыменования, эквивалентен value()
        T &operator*();

        // оператор сравнения на равенство
        bool operator == (Iterator &b);

        // оператор сравнения на неравенство
        bool operator != (Iterator &b);
    };


    // конструктор с указанием размерности
    MyVector(int length);

    // конструктор копирования
    MyVector(const MyVector<T> &vector);

    // конструктор перемещения
    MyVector (MyVector <T> &&vector);

    // конструктор со списком инициализации
    explicit MyVector(std::initializer_list<T> list);

    // деструктор
    ~MyVector();

    // перегрузка оператора присваивания
    MyVector<T>& operator =(const MyVector<T>& srcVector);

    // получить текущий размер
    int get_length() const;

    // изменить элемент вектора по индексу
    void set_elem(int index,const T &element);

    // получить элемент списка по индексу
    T& get_elem(int index);

    // создать новый массив, в который необходимо записать все элементы вектора
    T* to_array();

    // доступ к элементу, аналогично массиву
    T& operator [](int index);

    // перегрузка оператора << для вывода класса в поток (cout к примеру)
    template <class X> friend std::ostream &operator <<(std::ostream &os, const MyVector<X> &list);

    // перегрузка оператора +=, к this добавлется vect
    MyVector<T>& operator +=(const MyVector<T>& vect);

    // перегрузка оператора -=, из this вычитается vect
    MyVector<T>& operator -=(const MyVector<T>& vect);

    // перегрузка оператора *=, каждый элемент this домножается на val
    MyVector<T>& operator *=(const T& value);

    // перегрузка оператора /=, каждый элемент this делится на val
    MyVector<T>& operator /=(const T& value);

    // перегрузка оператора += к v1 добавлется v2
    template<typename _T> friend MyVector<_T> operator +(const MyVector<_T> &v1, const MyVector<_T> &v2);

    // перегрузка оператора -, из v1 вычитается v2
    template<typename _T> friend MyVector<_T> operator -(const MyVector<_T> &v1, const MyVector<_T> &v2);

    // перегрузка оператора *, каждый элемент v1 домножается на val
    template<typename _T, typename __T> friend MyVector<_T> operator * (const MyVector<_T> &v1, const __T &value);

    // перегрузка оператора /, каждый элемент v1 делится на val
    template<typename _T, typename __T> friend MyVector<_T> operator / (const MyVector<_T> &v1, const __T &value);

    // метод получения итератора на начало вектора (первый элемент)
    Iterator iterator_begin();

    // метод получения итератора на конец списка (фиктивный элемент, следующий за последним в векторе)
    Iterator iterator_end();
};

// проверяет индекс на соответствие границам массива
template<typename T> void MyVector<T>::checkBounds(int index) {
    if (index < 0)
        throw VectorException("Index must be greater than zero");

    if (internalArrayLength <= index)
        throw VectorException("Index out of range");
}


// конструктор с указанием размерности
template<typename T> MyVector<T>::MyVector(int length)
{
    if(length < 0)
        throw VectorException("Length of vector must be greater or equal zero");

    internalArrayLength = length;
    internalArray = new T[internalArrayLength]{};
}

// конструктор копирования
template<typename T> MyVector<T>::MyVector(const MyVector<T> &vector)
{
    internalArrayLength = vector.internalArrayLength;
    internalArray = new T[internalArrayLength];
    for(int i = 0; i < internalArrayLength; i++)
        internalArray[i] = vector.internalArray[i];
}

// конструктор перемещения
template<typename T> MyVector<T>::MyVector(MyVector<T> &&vector)
{
    internalArray = vector.internalArray;
    internalArrayLength = vector.internalArrayLength;
    vector.internalArrayLength = 0;
    vector.internalArray = nullptr;
}

// конструктор со списком инициализации
template<typename T> MyVector<T>::MyVector(std::initializer_list<T> list)
{
    if(list.size() < 0)
        throw VectorException("Vector length must be greater or equal zero");

    internalArrayLength = list.size();
    internalArray = new T[list.size()]{};

    int i = 0;
    for(T item : list) {
        internalArray[i++] = item;
    }
}

// деструктор
template<typename T> MyVector<T>::~MyVector()
{
    internalArrayLength = 0;

    delete[] internalArray;
    internalArray = nullptr;
}

// перегрузка оператора присваивания
template<typename T> MyVector<T> &MyVector<T>::operator=(const MyVector<T> &srcVector)
{
    internalArray = new T[srcVector.internalArrayLength]{};
    internalArrayLength = srcVector.internalArrayLength;
    for(int i = 0; i < srcVector.internalArrayLength; i++)
        internalArray[i] = srcVector.m_vec[i];

    return *this;
}

// получить текущий размер
template<typename T> int MyVector<T>::get_length() const
{
    return internalArrayLength;
}

// изменить элемент вектора по индексу
template<typename T> void MyVector<T>::set_elem(int index, const T &element)
{
    checkBounds(index);
    internalArray[index] = element;
}

// получить элемент списка по индексу
template<typename T> T &MyVector<T>::get_elem(int index)
{
    checkBounds(index);
    return internalArray[index];
}

// создать новый массив, в который необходимо записать все элементы вектора
template<typename T> T *MyVector<T>::to_array()
{
    T *array = new T[internalArrayLength];

    for(int i =0; i < internalArrayLength; i++)
        array[i] = internalArray[i];

    return array;
}

// доступ к элементу, аналогично массиву
template<typename T> T &MyVector<T>::operator [](int index)
{
    checkBounds(index);
    return *(internalArray + index);
}

// перегрузка оператора << для вывода класса в поток (cout к примеру)
template<typename T> std::ostream &operator <<(std::ostream& os, const MyVector<T> &list)
{
    std::string container = "MyVector{length: " + std::to_string(list.internalArrayLength) + ", array: [";

    for(int i = 0; i < list.internalArrayLength; i++) {
        container += std::to_string(list.internalArray[i]);

        if (i < list.internalArrayLength - 1) {
            container += ", ";
        }
    }

    container += "]}";

    return os << container;
}

// перегрузка оператора +=, к this добавлется vect
template<typename T> MyVector<T> &MyVector<T>::operator += (const MyVector<T> &vector)
{
    MyVector<T> me = *this;

    if (internalArrayLength > 0)
        delete[] internalArray;

    internalArrayLength = me.internalArrayLength + vector.internalArrayLength;

    internalArray = new T[internalArrayLength]{};

    for(int i = 0; i < me.internalArrayLength; i++)
        internalArray[i] = me.internalArray[i];

    for(int i = 0; i < vector.internalArrayLength; i++)
        internalArray[me.internalArrayLength + i] = vector.internalArray[i];

    return me;
}

// перегрузка оператора -=, из this вычитается vect
template<typename T> MyVector<T> &MyVector<T>::operator -= (const MyVector<T> &vector)
{
    MyVector<T> me = *this;

    if (internalArrayLength > 0)
        delete[] internalArray;

    internalArrayLength = std::max(me.internalArrayLength, vector.internalArrayLength);

    internalArray = new T[internalArrayLength]{};
    for(int i = 0; i < internalArrayLength; i++)
        internalArray[i] = ((i < me.internalArrayLength) ? me.internalArray[i] : 0) -
                           ((i < vector.internalArrayLength) ? vector.internalArray[i] : 0);
    return me;
}

// перегрузка оператора *=, каждый элемент this домножается на val
template<typename T> MyVector<T> &MyVector<T>::operator *= (const T &value)
{
    for(int i = 0; i < internalArrayLength; i++)
        internalArray[i] *= value;
    return *this;
}

// перегрузка оператора /=, каждый элемент this делится на val
template<typename T> MyVector<T> &MyVector<T>::operator /= (const T &value)
{
    if(value == 0)
        return *this;

    for(int i = 0; i < internalArrayLength; i++)
        internalArray[i] /= value;

    return *this;
}

// перегрузка оператора + к v1 добавлется v2
template<typename _T> MyVector<_T> operator + (const MyVector<_T> &v1, const MyVector<_T> &v2)
{
    MyVector<_T> result(v1.internalArrayLength + v2.internalArrayLength);

    for(int i = 0; i < v1.internalArrayLength; i++)
        result[i] = v1.internalArray[i];

    for(int i = 0; i < v2.internalArrayLength; i++)
        result[v1.internalArrayLength + i] = v2.internalArray[i];

    return result;
}

// перегрузка оператора -, из v1 вычитается v2
template<typename _T> MyVector<_T> operator - (const MyVector<_T> &v1, const MyVector<_T> &v2)
{
    MyVector<_T> result(std::max(v1.internalArrayLength, v2.internalArrayLength));

    for(int i = 0; i < result.internalArrayLength; i++)
        result[i] = ((i < v1.internalArrayLength) ? v1.internalArray[i] : 0) -
                    ((i < v2.internalArrayLength) ? v2.internalArray[i] : 0);

    return result;
}

// перегрузка оператора *, каждый элемент v1 домножается на val
template<typename _T, typename __T> MyVector<_T> operator * (const MyVector<_T> &v1, const __T &value)
{
    for(int i = 0; i < v1.internalArrayLength; i++)
        v1.internalArray[i] *= value;

    return v1;
}

// перегрузка оператора /, каждый элемент v1 делится на val
template<typename _T, typename __T> MyVector<_T> operator / (const MyVector<_T> &v1, const __T &value)
{
    if(value == 0)
        throw VectorException("division by zero");

    for(int i = 0; i < v1.internalArrayLength; i++)
        v1.internalArray[i] /= value;

    return v1;
}

// метод получения итератора на начало вектора (первый элемент)
template<typename T> typename MyVector<T>::Iterator MyVector<T>::iterator_begin()
{
    return MyVector<T>::Iterator(*this);
}

// метод получения итератора на конец списка (фиктивный элемент, следующий за последним в векторе)
template<typename T> typename MyVector<T>::Iterator MyVector<T>::iterator_end()
{
    MyVector<T>::Iterator iterator = MyVector<T>::Iterator(*this);
    while(!iterator.is_end())
        iterator.next();

    return iterator;
}


// конструктор, принимающий объект контейнерного класса, который необходимо обойти с помощью
// данного итератора
template <typename T> MyVector<T>::Iterator::Iterator(MyVector<T> vector) :
    vector(vector), currentIndex(0)
{
}

// перейти к следующему объекту в контейнере
template <typename T> typename MyVector<T>::Iterator MyVector<T>::Iterator::next()
{
    if(!this->is_end())
        currentIndex += 1;

    return *this;
}

// получить значение текущего объекта в контейнере
template <typename T> T MyVector<T>::Iterator::value()
{
    return vector[currentIndex];
}

// указывает ли итератор на конечный фиктивный элемент контейнера, следующий за последним
// реальным. Нужен для определения конца итерирования
template <typename T> bool MyVector<T>::Iterator::is_end()
{
    if (vector.get_length() == 0)
        return true;

    else if (currentIndex == vector.get_length() - 1)
        return true;

    else
        return false;
}

// префиксный инкремент, эквивалентен next()
template <typename T> typename MyVector<T>::Iterator &MyVector<T>::Iterator::operator++()
{
    MyVector<T>::Iterator::next();
    return *this;
}

// оператор сравнения на равенство
template <typename T> bool MyVector<T>::Iterator::operator == (Iterator &b)
{
    if (currentIndex != b.currentIndex)
        return false;

    if (is_end() != b.is_end())
        return false;

    if (is_end() && b.is_end() && is_end() == true)
        return true;

    return vector[currentIndex] == b.vector[b.currentIndex];
}

// оператор сравнения на неравенство
template <typename T> bool MyVector<T>::Iterator::operator != (Iterator &b)
{
    if (currentIndex == b.currentIndex)
        return false;

    if (is_end() != b.is_end())
        return true;

    if (is_end() && b.is_end() && is_end() == true)
        return false;

    return vector[currentIndex] != b.vector[b.currentIndex];
}


#endif // MyVector_H
