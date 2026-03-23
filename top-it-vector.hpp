#ifndef TOPITVECTOR_HPP
#define TOPITVECTOR_HPP
#include <cassert>
#include <stdexcept>
#include <cstddef>
#include <utility>
namespace topit
{
  template < class T > struct Vector
  {
    Vector();
    Vector(const Vector< T > &);
    Vector< T > &operator=(const Vector< T > &);
    ~Vector();

    void swap(Vector< T > &rhs) noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    T &operator[](size_t id) noexcept;
    const T &operator[](size_t id) const noexcept;

    void pushBack(const T &);
    void pushFront(const T &);
    void popBack();

  private:
    T *data_;
    size_t size_, capacity_;

    explicit Vector(size_t k);
  };
}
template < class T > void topit::Vector< T >::popBack()
{
  if (size_ == 0) {
    throw std::out_of_range("Vector is empty");
  }
  size_--;
  data_[size_].~T();
}
template < class T > size_t topit::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}

template < class T >
void topit::Vector< T >::pushFront(const T &val) // сложный момент : в дефолт библиотеке вектор не реализовано
{
  Vector< T > cpy(size_ + 1);
  cpy[0] = val;
  for (size_t i = 1; i < cpy.getSize(); i++) {
    cpy[i] = (*this)[i - 1];
  }
  swap(cpy);
}
template < class T > void topit::Vector< T >::swap(Vector< T > &rhs) noexcept // обязательно noexcept (идиома copy-swap)
{
  std::swap(rhs.data_, data_); // не может быть исключение ( все встроенные типы )
  std::swap(rhs.size_, size_);
  std::swap(rhs.capacity_, capacity_);
}
template < class T > topit::Vector< T > &topit::Vector< T >::operator=(const Vector< T > &rhs)
{
  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}
template < class T > topit::Vector< T >::Vector(size_t k)
{
  data_(new T[k.size()]), size_(k.getSize()), capacity_(k.getSize())
}
template < class T > bool topit::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}
template < class T > size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}

template < class T >
topit::Vector< T >::Vector(const Vector< T > &rhs):
  Vector(rhs.getSize()) // ЗДесь мы пишем таким образом так как иначе надо будет писать catch (если создавать через поля
                        // просто) а так мы вызываем конструктор и деструктор вызовится
{
  for (size_t i = 0; i < getSize(); ++i) {
    data_[i] = rhs[i];
  }
}
template < class T > topit::Vector< T >::~Vector()
{
  delete[] data_;
}
template < class T > T &topit::Vector< T >::operator[](size_t id) noexcept
{
  assert(id < getSize());
  return data_[id];
}

template < class T > const T &topit::Vector< T >::operator[](size_t id) const noexcept
{
  assert(id < getSize());
  return data_[id];
}

template < class T > void topit::Vector< T >::pushBack(const T &val)
{
  if (size_ == capacity_) {
    size_t newCap = (capacity_ == 0 ? 1 : capacity_ * 2);
    T *new_data = new T[newCap];
    try {
      for (size_t i = 0; i < getSize(); ++i) {
        new_data[i] = data_[i];
      }
    } catch (...) {
      delete[] new_data;
      throw;
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = newCap;
  }
  data_[size_++] = val;
}

#endif