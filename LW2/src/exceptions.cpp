#include "../include/exceptions.h"

IndexOutOfRangeException::IndexOutOfRangeException(std::string msg) : _msg {msg} {}

const char* IndexOutOfRangeException::what() const noexcept {
    return _msg.c_str();
}

ArrayIsEmptyException::ArrayIsEmptyException(std::string msg) : _msg {msg} {}

const char* ArrayIsEmptyException::what() const noexcept {
    return _msg.c_str();
}