#include <exceptions.h>

IndexOutOfRangeException::IndexOutOfRangeException(std::string msg) : _msg {msg} {}

const char* IndexOutOfRangeException::what() const noexcept {
    return _msg.c_str();
}

ArrayIsEmptyException::ArrayIsEmptyException(std::string msg) : _msg {msg} {}

const char* ArrayIsEmptyException::what() const noexcept {
    return _msg.c_str();
}

NotImplementedException::NotImplementedException(std::string msg) : _msg {msg} {}

const char* NotImplementedException::what() const noexcept {
    return _msg.c_str();
}

UninitializedException::UninitializedException(std::string msg) : _msg {msg} {}

const char* UninitializedException::what() const noexcept {
    return _msg.c_str();
}

BadInputDataException::BadInputDataException(std::string msg) : _msg {msg} {}

const char* BadInputDataException::what() const noexcept {
    return _msg.c_str();
}