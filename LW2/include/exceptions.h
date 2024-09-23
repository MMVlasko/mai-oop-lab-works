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