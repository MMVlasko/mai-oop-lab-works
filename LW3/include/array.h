#pragma once

#include <stddef.h>


template <class T> class Array {
    private:
        T *_elements;
        size_t _capacity;
    
    private:
        void _expand(size_t capacity);

    public:
        size_t size;

    public:
        Array();

        Array(const Array<T> &other);

        Array(Array<T> &&other) noexcept;

        Array<T> &operator=(const Array<T> &other);

        Array<T> &operator=(Array<T> &&other) noexcept;

        T operator[](int index);

        virtual ~Array() noexcept;

        T remove();

        void add(T element);

        bool operator==(Array<T> &other);

        bool operator!=(Array<T> &other);

        void insert(T element, size_t index);

        T pop(size_t index);

        friend std::ostream& operator<<<T>(std::ostream &os, Array<T> &number);
};