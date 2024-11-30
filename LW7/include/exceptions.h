#pragma once

#include <exception>
#include <string>

class UnknownNPCTypeException : public std::exception {
    std::string _msg;

    public:
        UnknownNPCTypeException(std::string msg);

        const char* what() const noexcept override;
};

class InvalidCoordinatesExceptions : public std::exception {
    std::string _msg;

public:
    InvalidCoordinatesExceptions(std::string msg);

    const char* what() const noexcept override;
};

class FileNotExistsException : public std::exception {
    std::string _msg;

public:
    FileNotExistsException(std::string msg);

    const char* what() const noexcept override;
};

class IndexOutOfRangeException : public std::exception {
    std::string _msg;

    public:
        IndexOutOfRangeException(std::string msg);

        const char* what() const noexcept override;
};

class ArrayIsEmptyException : public std::exception {
    std::string _msg;

    public:
        ArrayIsEmptyException(std::string msg);

        const char* what() const noexcept override;
};