#pragma once

#include <stddef.h>
#include <string>


class Array {
    private:
        unsigned char *_elements;
        size_t _capacity;
    
    private:
        void _expand(size_t capacity);

    public:
        size_t size;

    public:
        Array();

        Array(const std::string &t);

        Array(const Array &other);

        Array(Array &&other) noexcept;

        Array &operator=(const Array &other);

        Array &operator=(Array &&other) noexcept;

        unsigned char operator[](int index);

        virtual ~Array() noexcept;

        unsigned char remove();

        void add(unsigned char element);

        bool operator==(Array &other);

        bool operator!=(Array &other);

        void insert(unsigned char element, size_t index);

        unsigned char pop(size_t index);

        std::string to_string();

        friend std::ostream& operator<<(std::ostream& os, Array& number);
};