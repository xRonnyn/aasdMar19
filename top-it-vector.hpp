#ifndef TOPITVECTOR_HPP
#define TOPITVECTOR_HPP
#include <cstddef>
namespace topit
{
    template< class T >
    struct Vector {
        Vector();
        Vector(const Vector< T >&) = delete;
        Vector < T >& operator=(const Vector< T >&) = delete;
        ~Vector();

        void swap(Vector< T >& rhs) noexcept;

        bool isEmpty() const noexcept;
        size_t getSize() const noexcept;
        size_t getCapacity() const noexcept;

        T& operator[](size_t id) noexcept;
        const T& operator[](size_t id) const noexcept;

        void pushBack(const T&);
        void pushFront(const T&);
        void popBack();

    private:
        T* data_;
        size_t size_, capacity_;

        explicit Vector(size_t k);
    };
}
template < class T >
size_t topit::Vector< T >::getCapacity() const noexcept{
  return capacity_;
}

template < class T >
void topit::Vector < T >::pushFront(const T &val) // сложный момент : в дефолт библиотеке вектор не реализовано
{
  Vector< T > cpy(val.getSize() + 1);
  cpy[0] = val;
  for (size_t i = 1; i < cpy.getSize(); i++){
    cpy[i] = (*this)[i - 1];
  }
  swap(cpy);
}
template< class T >
void topit::Vector< T > ::swap(Vector< T >& rhs) noexcept // обязательно noexcept (идиома copy-swap)
{
    std::swap(cpy.data_, data_); //не может быть исключение ( все встроенные типы )
    std::swap(cpy.size_, size_);
    std::swap(cpy.capacity_, capacity_);
}
template < class T >
topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T >& rhs)
{
  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}
template <class T>
topit::Vector<T>::Vector(size_t k)
{
    data_(new T[k.size()]),
    size_(k.getSize()),
    capacity_(k.getSize())
}
template< class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
    return !size_;
}
template< class T >
size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}

template< class T >
topit::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize()); //ЗДесь мы пишем таким образом так как иначе надо будет писать catch (если создавать через поля просто) а так мы вызываем конструктор и деструктор вызовится
{
  for (size_t i = 0; i < getSize(); ++i){
    data_[i] = rhs[i];
  }
}
template< class T >
topit::Vector< T >::~Vector()
{
    delete[] data_;
}
template< class T >
T& topit::Vector< T >::operator[](size_t id) noexcept
{
  assert(id < getSize());
  return data_[0];
}

template< class T >
const T& topit::Vector< T >::operator[](size_t id) const noexcept
{
  assert(id < getSize());
  return data_[0];
}

template< class T >
void topit::Vector< T >::pushBack(const T&)
{
  if (size_ == capacity_){
    size_t newCap *= 2;
    T* new_data = new T[newCap];
    try{
      for (size_t i = 0; i < getSize(); ++i){
        new_data[i] = data_[i];
      }
    catch(){
      delete[] new_data;
      throw;
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = newCap;
  }
  data_[size_++] = T;
}

#endif