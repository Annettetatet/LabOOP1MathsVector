#include <QCoreApplication>
#include "TestException.h"
#include "VectorException.h"
#include "MyVector.h"
#include <iostream>
#include <sstream>

void testStart(const char *message) {
    std::cout << "Test " << message << "... ";
}

void testOk() {
    std::cout << "OK" << std::endl;
}

void testFailed(const char *message)
{
    std::cout << "FAILED " << message << std::endl;
}

void fail(const char *message) {
    throw TestException(message);
}

// конструктор с указанием размерности
void testLengthConstructor() {
    testStart("testLengthConstructor");

    // проверка нулевой длины
    MyVector<int> vector1(0);

    // проверка ненулевой длины
    MyVector<int> vector2(7);
    if (vector2.get_length() != 7)
        fail("invalid length");

    // проверка отрицательной длины
    try {
        MyVector<int> vector3(-1);
        fail("negative length");
    } catch(VectorException &e2) { }

    testOk();
}

// конструктор копирования
void testCopyConstructor() {
    testStart("testCopyConstructor");

    MyVector<int> vector1{1, 2, 3};
    MyVector<int> vector2(vector1);

    if (vector1.get_length() != vector2.get_length())
        fail("invalid size");

    for(int i=0; i<vector1.get_length(); i++)
        if (vector1[i] != vector2[i])
            fail("elements differs");

    testOk();
}

// конструктор перемещения
void testMoveConstructor() {
    testStart("testMoveConstructor");

    MyVector<int> *vector1 = new MyVector<int>{1, 2, 3};
    MyVector<int> vector2(*vector1);

    if (vector1->get_length() != 3)
        fail("invalid initial vector size");

    if (vector2.get_length() != 3)
        fail("invalid destination vector size");

    if (vector2[0] != 1 || vector2[1] != 2 || vector2[2] != 3)
        fail("elements differs");

    testOk();
}

// конструктор со списком инициализации
void testListContructor() {
    testStart("testListContructor");

    MyVector<int> vector1{};
    if (vector1.get_length() != 0)
        fail("invalid length");

    MyVector<int> vector2{1};
    if (vector2.get_length() != 1)
        fail("invalid length");
    if (vector2[0] != 1)
        fail("invalid value");

    MyVector<int> vector3{1, 2, 3};
    if (vector3.get_length() != 3)
        fail("invalid length");
    if (vector3[0] != 1 || vector3[1] != 2 || vector3[2] != 3)
        fail("invalid value");

    testOk();
}

// перегрузка оператора присваивания
void testEqualOperator() {
    testStart("testEqualOperator");

    MyVector<int> vector1{};
    MyVector<int> vector2 = vector1;

    if (vector2.get_length() != 0)
        fail("invalid length");

    MyVector<int> vector3{1, 2, 3};
    MyVector<int> vector4 = vector3;

    if (vector4.get_length() != 3)
        fail("invalid length");
    if (vector4[0] != 1 || vector4[1] != 2 || vector4[2] != 3)
        fail("invalid value");

    testOk();
}

// получить текущий размер
void testGetLength() {
    testStart("testGetLength");

    MyVector<int> vector1{};
    if (vector1.get_length() != 0)
        fail("invalid length");

    MyVector<int> vector2{1, 2, 3};
    if (vector2.get_length() != 3)
        fail("invalid length");

    testOk();
}

// изменить элемент вектора по индексу
void testSetElement() {
    testStart("testSetElement");

    MyVector<int> vector1{};
    try {
        vector1[1] = 2;
        fail("no exception");
    } catch(VectorException &e2) { }

    MyVector<int> vector2{1, 2, 3};
    vector2[0] = 3;
    vector2[1] = 2;
    vector2[2] = 1;
    if (vector2[0] != 3 || vector2[1] != 2 || vector2[2] != 1)
        fail("invalid value");

    MyVector<int> vector3{1, 2, 3};
    try {
        vector1[3] = 4;
        fail("no exception");
    } catch(VectorException &e2) { }

    testOk();
}

// получить элемент списка по индексу
void testGetElement() {
    testStart("testGetElement");

    MyVector<int> vector1{};
    try {
        vector1.get_elem(0);
        fail("no exception");
    } catch(VectorException &e2) { }

    MyVector<int> vector2{1, 2, 3};
    if (vector2.get_elem(0) != 1 || vector2.get_elem(1) != 2 || vector2.get_elem(2) != 3)
        fail("invalid value");

    MyVector<int> vector3{1, 2, 3};
    try {
        vector1.get_elem(3);
        fail("no exception");
    } catch(VectorException &e2) { }

    testOk();
}

// создать новый массив, в который необходимо записать все элементы вектора
void testToArray() {
    testStart("testToArray");

    MyVector<int> vector1{};
    vector1.to_array();

    MyVector<int> vector2{1, 2, 3};
    int* array2 = vector2.to_array();
    if (array2[0] != 1 || array2[1] != 2 || array2[2] != 3)
        fail("invalid value");

    testOk();
}

// доступ к элементу, аналогично массиву
void testArrayOperator() {
    testStart("testArrayOperator");

    MyVector<int> vector1{};
    try {
        vector1[0];
        fail("no exception");
    } catch(VectorException &e2) { }

    MyVector<int> vector2{1, 2, 3};
    if (vector2[0] != 1 || vector2[1] != 2 || vector2[2] != 3)
        fail("invalid value");

    MyVector<int> vector3{1, 2, 3};
    try {
        vector1[3];
        fail("no exception");
    } catch(VectorException &e2) { }

    testOk();
}

// перегрузка оператора << для вывода класса в поток (cout к примеру)
void testStreamOperator() {
    testStart("testStreamOperator");

    std::stringstream ss1, ss2;

    MyVector vector{1, 2, 3};
    ss1 << vector;
    ss2 << "MyVector{length: 3, array: [1, 2, 3]}";

    if (ss1.str() != ss2.str()) {
        fail("string are not equal");
    }

    testOk();
}

// перегрузка оператора +=, к this добавлется vect
void testAddOperator() {
    testStart("testAddOperator");

    MyVector vector1{1};
    MyVector vector2{2, 3};

    vector1 += vector2;

    if (vector1.get_length() != 3)
        fail("invalid length");

    if (vector1[0] != 1 || vector1[1] != 2 || vector1[2] != 3)
        fail("invalid value");

    testOk();
}

// перегрузка оператора -=, из this вычитается vect
void testMinusOperator() {
    testStart("testMinusOperator");

    MyVector vector1{10, 10};
    MyVector vector2{1, 2, 3};

    vector1 -= vector2;

    if (vector1.get_length() != 3)
        fail("invalid length");

    if (vector1[0] != 9 || vector1[1] != 8 || vector1[2] != -3)
        fail("invalid value");

    testOk();
}

// перегрузка оператора *=, каждый элемент this домножается на val
void testMultiplyOperator() {
    testStart("testMultiplyOperator");

    MyVector vector1{1, 2, 3};

    vector1 *= 2;

    if (vector1.get_length() != 3)
        fail("invalid length");

    if (vector1[0] != 2 || vector1[1] != 4 || vector1[2] != 6)
        fail("invalid value");

    testOk();
}

// перегрузка оператора /=, каждый элемент this делится на val
void testDivisionOperator() {
    testStart("testDivisionOperator");

    MyVector vector1{8, 16, 32};

    vector1 /= 2;

    if (vector1.get_length() != 3)
        fail("invalid length");

    if (vector1[0] != 4 || vector1[1] != 8 || vector1[2] != 16)
        fail("invalid value");

    MyVector<int> vector2{1, 2, 3};
    vector2 /= 0;
    if (vector2[0] != 1 || vector2[1] != 2 || vector2[2] != 3)
        fail("invalid value");

    testOk();
}

// перегрузка оператора + к v1 добавлется v2
void testTwoArgumentsAddOperator() {
    testStart("testTwoArgumentsAddOperator");

    MyVector vector1{1};
    MyVector vector2{2, 3};
    MyVector vector = vector1 + vector2;

    if (vector.get_length() != 3)
        fail("invalid length");

    if (vector[0] != 1 || vector[1] != 2 || vector[2] != 3)
        fail("invalid value");

    testOk();
}

// перегрузка оператора -, из v1 вычитается v2
void testTwoArgumentsMinusOperator() {
    testStart("testTwoArgumentsMinusOperator");

    MyVector vector1{10, 10};
    MyVector vector2{1, 2, 3};
    MyVector vector = vector1 - vector2;

    if (vector.get_length() != 3)
        fail("invalid length");

    if (vector[0] != 9 || vector[1] != 8 || vector[2] != -3)
        fail("invalid value");

    testOk();
}

// перегрузка оператора *, каждый элемент v1 домножается на val
void testTwoArgumentsMultiplyOperator() {
    testStart("testTwoArgumentsMultiplyOperator");

    MyVector<int> vector1{1, 2, 3};
    MyVector<int> vector2 = vector1 * 2;

    if (vector1.get_length() != 3)
        fail("invalid length");

    if (vector1[0] != 2 || vector1[1] != 4 || vector1[2] != 6)
        fail("invalid value");

    testOk();
}

// перегрузка оператора /, каждый элемент v1 делится на val
void testTwoArgumentsDivisionOperator() {
    testStart("testTwoArgumentsDivisionOperator");

    MyVector<int> vector1{8, 16, 32};

    MyVector<int> vector2 = vector1 / 2;

    if (vector2.get_length() != 3)
        fail("invalid length");

    if (vector2[0] != 4 || vector2[1] != 8 || vector2[2] != 16)
        fail("invalid value");

    MyVector<int> vector3{1, 2, 3};
    try {
        MyVector<int> vector4 = vector3 / 0;
        fail("no exception");
    } catch(VectorException &e2) { }

    testOk();
}

// метод получения итератора на начало вектора (первый элемент)
void testIterator() {
    testStart("testIterator");

    MyVector<int>* vector1= new MyVector<int>{};
    if (vector1->iterator_begin().is_end() != true)
        fail("end mark is invalid");

    MyVector<int>::Iterator vector1it1 = vector1->iterator_begin();
    MyVector<int>::Iterator vector1it2 = vector1->iterator_begin().next();
    if (vector1it1 != vector1it2)
        fail("end mark is invalid");

    if (vector1it1 == vector1it2)
    { } else fail("equals error");

    MyVector vector2{1, 2, 3};
    MyVector<int>::Iterator vector2it = vector2.iterator_begin();
    if (vector2it.is_end())
        fail("invalid end mark");
    if (vector2it.value() != 1)
        fail("invalid value");

    vector2it.next();
    if (vector2it.is_end())
        fail("invalid end mark");
    if (vector2it.value() != 2)
        fail("invalid value");

    ++vector2it;
    if (!vector2it.is_end())
        fail("invalid end mark");
    if (vector2it.value() != 3)
        fail("invalid value");

    testOk();
}

int main(int argc, char *argv[])
{
    try {
        // конструктор с указанием размерности
        testLengthConstructor();

        // конструктор копирования
        testCopyConstructor();

        // конструктор перемещения
        testMoveConstructor();

        // конструктор со списком инициализации
        testListContructor();

        // перегрузка оператора присваивания
        testEqualOperator();

        // получить текущий размер
        testGetLength();

        // изменить элемент вектора по индексу
        testSetElement();

        // получить элемент списка по индексу
        testGetElement();

        // создать новый массив, в который необходимо записать все элементы вектора
        testToArray();

        // доступ к элементу, аналогично массиву
        testArrayOperator();

        // перегрузка оператора << для вывода класса в поток (cout к примеру)
        testStreamOperator();

        // перегрузка оператора +=, к this добавлется vect
        testAddOperator();

        // перегрузка оператора -=, из this вычитается vect
        testMinusOperator();

        // перегрузка оператора *=, каждый элемент this домножается на val
        testMultiplyOperator();

        // перегрузка оператора /=, каждый элемент this делится на val
        testDivisionOperator();

        // перегрузка оператора += к v1 добавлется v2
        testTwoArgumentsAddOperator();

        // перегрузка оператора -, из v1 вычитается v2
        testTwoArgumentsMinusOperator();

        // перегрузка оператора *, каждый элемент v1 домножается на val
        testTwoArgumentsMultiplyOperator();

        // перегрузка оператора /, каждый элемент v1 делится на val
        testTwoArgumentsDivisionOperator();

        // метод получения итератора на начало вектора (первый элемент)
        testIterator();
    } catch(std::exception &e) {
        testFailed(e.what());
    }
}
