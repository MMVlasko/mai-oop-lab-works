#include <exceptions.h>

EmptyStackException::EmptyStackException(std::string msg) : _msg {msg} {}

const char* EmptyStackException::what() const noexcept {
    return _msg.c_str();
}

OutOfMemoryException::OutOfMemoryException(std::string msg) : _msg {msg} {}

const char* OutOfMemoryException::what() const noexcept {
    return _msg.c_str();
}