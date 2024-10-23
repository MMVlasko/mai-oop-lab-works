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

class NotImplementedException : public std::exception {
    private:
        std::string _msg;
    
    public:
        NotImplementedException(std::string msg);

        const char* what() const noexcept override;
};

class UninitializedException : public std::exception {
    private:
        std::string _msg;
    
    public:
        UninitializedException(std::string msg);

        const char* what() const noexcept override;
};

class BadInputDataException : public std::exception {
    private:
        std::string _msg;
    
    public:
        BadInputDataException(std::string msg);

        const char* what() const noexcept override;
};