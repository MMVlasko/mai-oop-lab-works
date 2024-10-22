#pragma once

#include <cstddef>
#include <initializer_list>
#include <ostream>

#include "exceptions.h"

template <class T> class Array {
    private:
        T* *_elements;
        size_t _capacity;
    
    private:
        void _expand(size_t capacity);

    public:
        size_t size;

    public:
        Array();

        Array(std::initializer_list<T*> t);

        Array(const Array &other);

        Array(Array &&other) noexcept;

        Array &operator=(const Array &other);

        Array &operator=(Array &&other) noexcept;

        T* operator[](int index);

        virtual ~Array() noexcept;

        void free_elements();

        T* remove();

        void add(T* element);

        bool operator==(Array &other);

        bool operator!=(Array &other);

        void insert(T* element, size_t index);

        T* pop(size_t index);

        template <class U>
        friend std::ostream& operator<<(std::ostream &os, Array<U> &number);
};


template <class T>
Array<T>::Array() : _elements{nullptr}, _capacity{0}, size{0} {} 

template <class T>
Array<T>::Array(std::initializer_list<T*> t) {
    _capacity = size = t.size();
    _elements = new T*[_capacity];

    int i = 0;
    for (T* elem : t) {
        _elements[i] = elem;
        ++i;
    }
}
 
template <class T>
Array<T>::Array(const Array &other) {
    _capacity = other._capacity; 
    size = other.size;
    _elements = new T*[_capacity]; 
    for (int i = 0; i < size; ++i)
        _elements[i] = new T(*other._elements[i]);
} 
 
template <class T>
Array<T>::Array(Array &&other) noexcept : _elements{nullptr}, _capacity{0} {
    _elements = other._elements; 
    _capacity = other._capacity; 
    size = other.size;
    other._elements = nullptr; 
    other._capacity = other.size = 0; 
} 

template <class T>
Array<T>& Array<T>::operator=(const Array &other) {
    if (this != &other) { 
        delete[] _elements;

        _capacity = other._capacity; 
        size = other.size;
        _elements = new T*[_capacity]; 
        for (int i = 0; i < size; ++i)
            _elements[i] = new T(*other._elements[i]);
    } 
    return *this; 
} 

template <class T>
Array<T>& Array<T>::operator=(Array &&other) noexcept {
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
T* Array<T>::operator[] (int index) {
    if (index < -static_cast<int>(size) || index >= static_cast<int>(size))
        throw IndexOutOfRangeException("Index out of range");

    if (index < 0)
        return _elements[index + static_cast<int>(size)];
    return _elements[index];
}

template <class T>
Array<T>::~Array() noexcept {
    delete[] _elements;
}

template <class T>
void Array<T>::free_elements() {
    for (int i = 0; i < size; ++i)
        delete _elements[i];
}

template <class T>
T* Array<T>::remove() {
    if (size == 0)
        throw ArrayIsEmptyException("Array is now empty");
        
    --size;
    return _elements[size];
}

template <class T>
void Array<T>::_expand(const size_t capacity) {
    _capacity = capacity;
    T* *temp = new T*[_capacity];

    for (int i = 0; i < size; ++i)
        temp[i] = _elements[i];

    _elements = temp;
}

template <class T>
void Array<T>::add(T* element) {
    if(_capacity == size)
        _expand(_capacity * 2 + 1);

    _elements[size] = element;
    ++size;
}

template <class T>
bool Array<T>::operator==(Array &other) {
    if (other.size == size) {
        for (int i = 0; i < size; ++i) {
            T *first = _elements[i];
            T *second = other[i];
            if (*first != *second)
                return false;
        }
        return true;
    }
    return false;
}

template <class T>
bool Array<T>::operator!=(Array &other) {
    if (other.size == size) {
        for (int i = 0; i < size; ++i) {
            T *first = _elements[i];
            T *second = other[i];
            if (*first != *second)
                return true;
        }
        return false;
    }
    return true;
}

template <class T>
void Array<T>::insert(T* element, size_t index) {
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
T* Array<T>::pop(size_t index) {
    if (index >= size)
        throw IndexOutOfRangeException("Index out of range");

    T *temp = _elements[index];

    for (size_t i = index + 1; i < size; ++i)
        _elements[i - 1] = _elements[i];
    
    --size;
    return temp;
}

template <class T>
std::ostream& operator<<(std::ostream& os, Array<T> &array) {
    os << '[';    
    if (array.size) {
        for (int i = 0; i + 1 < array.size; ++i)
            os << *array._elements[i] << ", ";
        os << *array._elements[array.size - 1];
    }
    os << ']';
    return os;
}