#include <cstring> 
#include <iostream>

#include <exceptions.h>
#include <array.h>
 
template <class T>
Array<T>::Array() : _elements{nullptr}, _capacity{0}, size{0} {} 
 
template <class T>
Array<T>::Array(const Array<T> &other) { 
    _capacity = other._capacity; 
    size = other.size;
    _elements = new T[_capacity]; 
    std::memcpy(_elements, other._elements, size);
} 
 
template <class T>
Array<T>::Array(Array<T> &&other) noexcept : _elements{nullptr}, _capacity{0} { 
    _elements = other._elements; 
    _capacity = other._capacity; 
    size = other.size;
    other._elements = nullptr; 
    other._capacity = other.size = 0; 
} 

template <class T>
Array<T>& Array<T>::operator=(const Array<T> &other) { 
    if (this != &other) { 
        delete[] _elements;

        _capacity = other._capacity; 
        size = other.size;
        _elements = new T[_capacity]; 
        std::memcpy(_elements, other._elements, size);
    } 
    return *this; 
} 

template <class T>
Array<T>& Array<T>::operator=(Array<T> &&other) noexcept { 
    if (this != &other) { 
        delete[] _elements;
        _elements = other._elements; 
        _capacity = other._capacity; 
        size = other.size;

        other._elements = nullptr; 
        other._capacity = other.size = 0; 
    } 
    return *this; 
} 

template <class T>
T Array<T>::operator[] (int index) {
    if (index < -static_cast<int>(size) || index >= static_cast<int>(size))
        throw IndexOutOfRangeException("Index out of range");

    if (index < 0)
        return _elements[index + static_cast<int>(size)];

    else return _elements[index];
}

template <class T>
Array<T>::~Array() noexcept { 
    if (_elements != nullptr)
        delete[] _elements;
}

template <class T>
T Array<T>::remove() {
    if (size == 0)
        throw ArrayIsEmptyException("Array is now empty");
        
    --size;
    return _elements[size];
}

template <class T>
void Array<T>::_expand(size_t capacity) {
    _capacity = capacity;
    T *temp = new T[_capacity];
    std::memcpy(temp, _elements, size);
    delete[] _elements;
    _elements = temp;
}

template <class T>
void Array<T>::add(T element) {
    if(_capacity == size)
        _expand(_capacity * 2 + 1);

    _elements[size] = element;
    ++size;
}

template <class T>
bool Array<T>::operator==(Array<T> &other) {
    if (other.size == size) {
        for (int i = 0; i < size; ++i) {
            if (_elements[i] != other[i])
                return false;
        }
        return true;
    }
    return false;
}

template <class T>
bool Array<T>::operator!=(Array<T> &other) {
    if (other.size == size) {
        for (int i = 0; i < size; ++i) {
            if (_elements[i] != other[i])
                return true;
        }
        return false;
    }
    return true;
}

template <class T>
void Array<T>::insert(T element, size_t index) {
    if (index > size)
        throw IndexOutOfRangeException("Index out of range");

    if (_capacity == size)
        _expand(_capacity * 2 + 1);
        
    if (index != size) {
        for (int i = size; i >= index; --i)
            _elements[i + 1] = _elements[i];
    }

    _elements[index] = element;
    ++size;
}

template <class T>
T Array<T>::pop(size_t index) {
    if (index >= size)
        throw IndexOutOfRangeException("Index out of range");

    T temp = _elements[index];

    for (int i = index + 1; i < size; ++i) 
        _elements[i - 1] = _elements[i];
    
    --size;
    return temp;
}

template <class T>
std::ostream& operator<<(std::ostream& os, Array<T> &array) {
    os << '[';

    for (int i = 0; i + 1 < array.size; ++i)
        os << array._elements[i] << ", ";

    os << array._elements[array.size - 1] << ']' << std::endl;
    return os;
}