#pragma once

#include <exception>
#include <string>

class IndexOutOfRangeException : public std::exception {
    private:
        std::string _msg;
    
    public:
        IndexOutOfRangeException(std::string msg);
        
        const char* what() const noexcept override;
};

class ArrayIsEmptyException : public std::exception {
    private:
        std::string _msg;
    
    public:
        ArrayIsEmptyException(std::string msg);

        const char* what() const noexcept override;
};

class ResultIsNegativeException : public std::exception {
    private:
        std::string _msg;
    
    public:
        ResultIsNegativeException(std::string msg);

        const char* what() const noexcept override;
};

class NoHexNumericException : public std::exception {
    private:
        std::string _msg;
    
    public:
        NoHexNumericException(std::string msg);

        const char* what() const noexcept override;
};

class TooBigNumberException : public std::exception {
    private:
        std::string _msg;
    
    public:
        TooBigNumberException(std::string msg);

        const char* what() const noexcept override;
};