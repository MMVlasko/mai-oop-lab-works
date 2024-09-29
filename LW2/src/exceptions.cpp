#include <exceptions.h>

IndexOutOfRangeException::IndexOutOfRangeException(std::string msg) : _msg {msg} {}

const char* IndexOutOfRangeException::what() const noexcept {
    return _msg.c_str();
}

ArrayIsEmptyException::ArrayIsEmptyException(std::string msg) : _msg {msg} {}

const char* ArrayIsEmptyException::what() const noexcept {
    return _msg.c_str();
}

ResultIsNegativeException::ResultIsNegativeException(std::string msg) : _msg {msg} {}

const char* ResultIsNegativeException::what() const noexcept {
    return _msg.c_str();
}

NoHexNumericException::NoHexNumericException(std::string msg) : _msg {msg} {}

const char* NoHexNumericException::what() const noexcept {
    return _msg.c_str();
}

TooBigNumberException::TooBigNumberException(std::string msg) : _msg {msg} {}

const char* TooBigNumberException::what() const noexcept {
    return _msg.c_str();
}