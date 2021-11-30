//============================================================================
// Name        : lesson_03_CPP_DM.cpp
// Author      : andry antonenko
// IDE         : Qt Creator 4.14.2 based on Qt 5.15.2
// Description : lesson 03 of the C++: difficult moments course
//============================================================================
#include <QCoreApplication>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>
#include <tuple>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>
#include <codecvt>
#include <list>
#include <functional>

//#include "timer.h"

//using namespace std;
//----------------------------------------------------------------------------
int getRandomNum(int min, int max)
{
  const static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::mt19937_64 generator(seed);
  std::uniform_int_distribution<int> dis(min, max);
  return dis(generator);
}
//----------------------------------------------------------------------------
/*
1. Написать функцию, добавляющую в конец списка вещественных чисел элемент,
значение которого равно среднему арифметическому всех его элементов.
//*/

void addElementOfMiddleValue(std::list<double>& l)
{
  double sum{0};
  size_t cnt{0};
  for(const auto& d: l)
  {
    sum += d;
    ++cnt;
  }
  sum /= static_cast<double>(cnt);
  l.push_back(sum);
}

template<typename T>
void printList(const std::list<T>& l)
{
  for(const auto& a: l)
    std::cout << a << " ";
  std::cout << std::endl;
}

void task_1()
{
  std::cout << "Task 1\n" << std::endl;

  const size_t NUMBER_OF_ELEMENTS = 10;
  const size_t MIN = 0;
  const size_t MAX = 100;

  std::list<double> listDouble;

  for(size_t i{0}; i < NUMBER_OF_ELEMENTS; ++i)
  {
    listDouble.push_back(
          static_cast<double>(getRandomNum(MIN,MAX)) / 10.0);
  }

  std::cout << "Source list:" << std::endl;
  printList(listDouble);

  addElementOfMiddleValue(listDouble);

  std::cout << "Resultant list:" << std::endl;
  printList(listDouble);

  std::cout << std::endl;
}
//----------------------------------------------------------------------------
/*
2. Создать класс, представляющий матрицу.
Реализовать в нем метод, вычисляющий определитель матрицы.
//*/

template<typename T>
class Matrix
{
private:
  size_t size;
  T** matrix;

  T determinantMatrixSizeTwo();
  T determinantMatrixSizeThree();
public:
  Matrix(const size_t aSize = 3)
    :size(aSize > 3 ? 3 : aSize)//restriction on the size of the matrix
  {
    matrix = new T*[size];
    for(size_t i {0}; i < size; ++i)
      matrix[i] = new T[size];
  }
  ~Matrix()
  {
    for(size_t i {0}; i < size; ++i)
      delete[] matrix[i];
    delete []  matrix;
  }

  void generateValues(int min, int max)
  {
    for(size_t i {0}; i < size; ++i)
      for(size_t j {0}; j < size; ++j)
        matrix[i][j] = (T)getRandomNum(min, max);
  }

  void print();
  T determinant();
};

template<typename T>
void Matrix<T>::print()
{
  for(size_t i {0}; i < size; ++i)
  {
    for(size_t j {0}; j < size; ++j)
      std::cout << matrix[i][j] << " ";
    std::cout << std::endl;
  }
}

template<typename T>
T Matrix<T>::determinant()
{
  switch(size)
  {
    case 1:
      return matrix[0][0];
    break;
    case 2:
      return determinantMatrixSizeTwo();
    break;
    case 3:
      return determinantMatrixSizeThree();
    break;
  }
  return 0;
}

template<typename T>
T Matrix<T>::determinantMatrixSizeTwo()
{
  if(size != 2) return 0;
  return matrix[0][0] * matrix[1][1] -
      matrix[0][1] * matrix[1][0];
}

template<typename T>
T Matrix<T>::determinantMatrixSizeThree()
{
  if(size != 3) return 0;
  return matrix[0][0] * matrix[1][1] * matrix[2][2] +
      matrix[0][1] * matrix[1][2] * matrix[2][0] +
      matrix[1][0] * matrix[2][1] * matrix[0][2] -
      matrix[2][0] * matrix[1][1] * matrix[0][2] -
      matrix[0][0] * matrix[1][2] * matrix[2][1] -
      matrix[0][1] * matrix[1][0] * matrix[2][2];
}

void task_2()
{
  std::cout << "Task 2\n" << std::endl;

  const size_t NUMBER_OF_ELEMENTS = 3;
  const size_t MIN = 0;
  const size_t MAX = 100;

  Matrix<double> matrix(NUMBER_OF_ELEMENTS);

  matrix.generateValues(MIN,MAX);
  std::cout << "Print of the matrix:" << std::endl;
  matrix.print();

  std::cout << "Determinant of the matrix: ";
  std::cout << matrix.determinant();

  std::cout << std::endl;
}

//----------------------------------------------------------------------------
/*
3. Реализовать собственный класс итератора,
с помощью которого можно будет проитерироваться
по диапазону целых чисел в цикле for-range-based.
//*/

template<typename T>
class cIterator
{
private:
  T* p;
public:
  cIterator(T* aP)
      :p(aP)
  {}

  cIterator(T& aP)
      :p(&aP)
  {}


  T operator*()
  {
      return *p;
  }

  void operator++()
  {
      ++p;
  }

  bool operator!=(T *aP)
  {
      return p != aP;
  }
};

void task_3()
{
  std::cout << "\nTask 3\n" << std::endl;

  const size_t NUMBER_OF_ELEMENTS = 10;
  const size_t MIN = 0;
  const size_t MAX = 1000;

  std::cout << "Massive of interger numbers:" << std::endl;

  int mI[NUMBER_OF_ELEMENTS];

  for(size_t i {0}; i < NUMBER_OF_ELEMENTS; ++i)
  {
    mI[i] = getRandomNum(MIN,MAX);
  }

  for(cIterator<int> it {std::begin(mI)}; it != std::end(mI); ++it)
  {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  std::cout << "Massive of double float numbers:" << std::endl;

  double mD[NUMBER_OF_ELEMENTS];

  for(cIterator<double> it : mD)
  {
    std::cout << *it << " ";
  }

  std::cout << std::endl;
}
//----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  //--------------------------------------------------------------------------
  // Task 1
  //*
  task_1();
  //*/
  //--------------------------------------------------------------------------
  // Task 2
  //*
  task_2();
  //*/
  //--------------------------------------------------------------------------
  // Task 3
  //*
  task_3();
  //*/
  //--------------------------------------------------------------------------
  return a.exec();
}
