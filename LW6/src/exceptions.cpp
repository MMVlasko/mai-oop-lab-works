#include <exceptions.h>

UnknownNPCTypeException::UnknownNPCTypeException(std::string msg) : _msg {msg} {}

const char* UnknownNPCTypeException::what() const noexcept {
    return _msg.c_str();
}

InvalidCoordinatesExceptions::InvalidCoordinatesExceptions(std::string msg) : _msg {msg} {}

const char* InvalidCoordinatesExceptions::what() const noexcept {
    return _msg.c_str();
}

FileNotExistsException::FileNotExistsException(std::string msg) : _msg {msg} {}

const char* FileNotExistsException::what() const noexcept {
    return _msg.c_str();
}

IndexOutOfRangeException::IndexOutOfRangeException(std::string msg) : _msg {msg} {}

const char* IndexOutOfRangeException::what() const noexcept {
    return _msg.c_str();
}

ArrayIsEmptyException::ArrayIsEmptyException(std::string msg) : _msg {msg} {}

const char* ArrayIsEmptyException::what() const noexcept {
    return _msg.c_str();
}