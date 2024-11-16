#pragma once

#include <cstddef>
#include <initializer_list>
#include <cstring>
#include <memory>

#include "exceptions.h"

template <class T> class Array {
    private:
        std::shared_ptr<std::shared_ptr<T>[]> _elements;
        size_t _capacity;

    private:
        void _expand(size_t capacity);

    public:
        size_t size;

    public:
        Array();

        Array(std::initializer_list<T> t);

        Array(const Array &other);

        Array(Array &&other) noexcept;

        Array &operator=(const Array &other);

        Array &operator=(Array &&other) noexcept;

        std::shared_ptr<T> operator[](int index);

        std::shared_ptr<T> remove();

        void add(T element);

        bool operator==(Array &other);

        bool operator!=(Array &other);

        void insert(T element, size_t index);

        std::shared_ptr<T> pop(size_t index);

        template <class U>
        friend std::ostream& operator<<(std::ostream &os, Array<U> &number);
};


template <class T>
Array<T>::Array() : _elements{nullptr}, _capacity{0}, size{0} {}

template <class T>
Array<T>::Array(std::initializer_list<T> t) {
    _capacity = size = t.size();
    _elements = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[_capacity],
        std::default_delete<std::shared_ptr<T>[]>());

    int i = 0;
    for (auto elem : t) {
        _elements[i] = std::make_shared<T>(std::move(elem));
        ++i;
    }
}

template <class T>
Array<T>::Array(const Array &other) {
    _capacity = other._capacity;
    size = other.size;
    _elements = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[_capacity],
        std::default_delete<std::shared_ptr<T>[]>());
    for (int i = 0; i < size; ++i)
        _elements[i] = std::make_shared<T>(T(*other._elements[i]));
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
        _capacity = other._capacity;
        size = other.size;
        _elements = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[_capacity],
            std::default_delete<std::shared_ptr<T>[]>());
        for (int i = 0; i < size; ++i)
            _elements[i] = std::make_shared<T>(T(*other._elements[i]));
    }
    return *this;
}

template <class T>
Array<T>& Array<T>::operator=(Array &&other) noexcept {
    if (this != &other) {
        _elements = other._elements;
        _capacity = other._capacity;
        size = other.size;

        other._elements = nullptr;
        other._capacity = other.size = 0;
    }
    return *this;
}

template <class T>
std::shared_ptr<T> Array<T>::operator[] (int index) {
    if (index < -static_cast<int>(size) || index >= static_cast<int>(size))
        throw IndexOutOfRangeException("Index out of range");

    if (index < 0)
        return _elements[index + static_cast<int>(size)];
    return _elements[index];
}

template <class T>
std::shared_ptr<T> Array<T>::remove() {
    if (size == 0)
        throw ArrayIsEmptyException("Array is now empty");

    --size;
    return std::make_shared<T>(std::move(*_elements[size]));
}

template <class T>
void Array<T>::_expand(const size_t capacity) {
    _capacity = capacity;
    auto temp = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[_capacity],
        std::default_delete<std::shared_ptr<T>[]>());

    for (int i = 0; i < size; ++i)
        temp[i] = std::move(_elements[i]);

    _elements = temp;
}

template <class T>
void Array<T>::add(T element) {
    if(_capacity == size)
        _expand(_capacity * 2 + 1);

    _elements[size] = std::make_shared<T>(element);
    ++size;
}

template <class T>
bool Array<T>::operator==(Array &other) {
    if (other.size == size) {
        for (int i = 0; i < size; ++i) {
            if (*_elements[i] != *other[i])
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
            if (*_elements[i] != *other[i])
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
        for (int i = size; i > index; --i)
            _elements[i] = std::make_shared<T>(std::move(*_elements[i - 1]));
    }

    _elements[index] = std::make_shared<T>(std::move(element));
    ++size;
}

template <class T>
std::shared_ptr<T> Array<T>::pop(size_t index) {
    if (index >= size)
        throw IndexOutOfRangeException("Index out of range");

    auto temp = std::make_shared<T>(std::move(*_elements[index]));

    for (size_t i = index + 1; i < size; ++i)
        _elements[i - 1] = std::make_shared<T>(*_elements[i]);

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