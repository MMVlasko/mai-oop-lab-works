#pragma once

#include <exception>
#include <string>

class EmptyStackException : public std::exception {
    private:
        std::string _msg;
    
    public:
        EmptyStackException(std::string msg);
        
        const char* what() const noexcept override;
};

class OutOfMemoryException : public std::exception {
    private:
        std::string _msg;

    public:
        OutOfMemoryException(std::string msg);

        const char* what() const noexcept override;
};