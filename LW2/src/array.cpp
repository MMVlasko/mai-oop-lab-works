#include <cstring> 
#include <iostream>

#include <exceptions.h>
#include <array.h>
 
Array::Array() : _elements{nullptr}, _capacity{0}, size{0} {} 
 
Array::Array(const std::string &t) { 
    _capacity = size = t.size();

    if (size != 0) {
        _elements = new unsigned char[_capacity]; 
        std::memcpy(_elements, t.data(), _capacity);  
    } else _elements = nullptr;
} 
 
Array::Array(const Array &other) { 
    _capacity = other._capacity; 
    size = other.size;
    _elements = new unsigned char[_capacity]; 
    std::memcpy(_elements, other._elements, size);
} 
 
Array::Array(Array &&other) noexcept : _elements{nullptr}, _capacity{0} { 
    _elements = other._elements; 
    _capacity = other._capacity; 
    size = other.size;
    other._elements = nullptr; 
    other._capacity = other.size = 0; 
} 

Array& Array::operator=(const Array &other) { 
    if (this != &other) { 
        delete[] _elements;

        _capacity = other._capacity; 
        size = other.size;
        _elements = new unsigned char[_capacity]; 
        std::memcpy(_elements, other._elements, size);
    } 
    return *this; 
} 

Array& Array::operator=(Array &&other) noexcept { 
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

unsigned char Array::operator[] (int index) {
    if (index < -static_cast<int>(size) || index >= static_cast<int>(size))
        throw IndexOutOfRangeException("Index out of range");

    if (index < 0)
        return _elements[index + static_cast<int>(size)];

    else return _elements[index];
}

Array::~Array() noexcept { 
    if (_elements != nullptr)
        delete[] _elements;
}

unsigned char Array::remove() {
    if (size == 0)
        throw ArrayIsEmptyException("Array is now empty");
        
    --size;
    return _elements[size];
}

void Array::_expand(size_t capacity) {
    _capacity = capacity;
    unsigned char *temp = new unsigned char[_capacity];
    std::memcpy(temp, _elements, size);
    delete[] _elements;
    _elements = temp;
}

void Array::add(unsigned char element) {
    if(_capacity == size)
        _expand(_capacity * 2 + 1);

    _elements[size] = element;
    ++size;
}

bool Array::operator==(Array &other) {
    if (other.size == size) {
        for (int i = 0; i < size; ++i) {
            if (_elements[i] != other[i])
                return false;
        }
        return true;
    }
    return false;
}

bool Array::operator!=(Array &other) {
    if (other.size == size) {
        for (int i = 0; i < size; ++i) {
            if (_elements[i] != other[i])
                return true;
        }
        return false;
    }
    return true;
}

void Array::insert(unsigned char element, size_t index) {
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

unsigned char Array::pop(size_t index) {
    if (index >= size)
        throw IndexOutOfRangeException("Index out of range");

    unsigned char temp = _elements[index];

    for (int i = index + 1; i < size; ++i) 
        _elements[i - 1] = _elements[i];
    
    --size;
    return temp;
}

std::string Array::to_string() {
    std::string result = "";

    for (int i = 0; i < size; ++i)
        result += _elements[i];

    return result;
}

std::ostream& operator<<(std::ostream& os, Array& array) {
    os << '[';

    for (int i = 0; i + 1 < array.size; ++i)
        os << array._elements[i] << ", ";

    os << array._elements[array.size - 1] << ']' << std::endl;
    return os;
}