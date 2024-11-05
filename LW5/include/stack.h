#pragma once

#include <memory>
#include <iterator>

#include <exceptions.h>

template <class T>
class Stack {
    private:
        struct Node {
            T value;
            Node* next;
        };

        class const_iterator {
            public:
                using iterator_category = std::forward_iterator_tag;

            private:
                const Node* _current;

            public:
                explicit const_iterator(const Node *node);

                const T& operator*() const;

                const T *operator->() const;

                const_iterator &operator++();

                const_iterator operator++(int);

                bool operator==(const const_iterator &other) const;

                bool operator!=(const const_iterator &other) const;
        };

    public:
        using AT = std::pmr::polymorphic_allocator<Node>;

    private:
        Node* _head = nullptr;
        AT _alloc;
        size_t _size;

    private:
        void _clear();

    public:
        explicit Stack(const AT& alloc = {});

        Stack(const Stack &other, std::pmr::memory_resource* resource = nullptr);

        Stack(Stack &&other) noexcept;

        virtual ~Stack() noexcept;

        Stack &operator=(const Stack &other);

        Stack &operator=(Stack &&other) noexcept;

        bool operator==(const Stack &other) const;

        bool operator!=(const Stack &other) const;

        void push(T element);

        std::shared_ptr<T> pop();

        std::shared_ptr<T> top() const;

        [[nodiscard]] size_t size() const;

        [[nodiscard]] bool empty() const;

        void clear();

        template <class U>
        friend std::ostream& operator<<(std::ostream &os, const Stack<U> &stack);

        const_iterator begin() const;

        const_iterator end() const;
};


template <class T>
Stack<T>::Stack(const AT& alloc) : _alloc(alloc), _size(0) {}

template <class T>
Stack<T>::Stack(const Stack &other, std::pmr::memory_resource* resource)
    : _alloc(resource ? resource : other._alloc.resource()) {

    if (other._head == nullptr)
        _head = nullptr;
    else {
        try {
            _head = _alloc.allocate(1);
        } catch (std::bad_alloc&) {
            throw OutOfMemoryException("Buffer was overflowed");
        }
        std::allocator_traits<AT>::construct(_alloc, _head, Node{other._head->value, nullptr});

        Node* current = _head;
        Node* other_current = other._head->next;

        while (other_current != nullptr) {
            try {
                Node *new_node = _alloc.allocate(1);
                std::allocator_traits<AT>::construct(_alloc, new_node, Node{other_current->value,
                nullptr});

                current->next = new_node;
                current = new_node;
                other_current = other_current->next;
            } catch (std::bad_alloc&) {
                throw OutOfMemoryException("Buffer was overflowed");
            }
        }
    }
    _size = other._size;
}

template <class T>
Stack<T>::Stack(Stack &&other) noexcept : _alloc(other._alloc) {
    if (other._head == nullptr)
        _head = nullptr;
    else {
        while (other._head->next != nullptr) {
            _head = other._head;
            other._head = other._head->next;
        }
    }
    _size = other._size;
}

template<class T>
Stack<T>::~Stack() noexcept {
    _clear();
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack &other) {
    if (this != &other) {
        _clear();

        if (other._head == nullptr)
            _head = nullptr;
        else {
            try {
                _head = _alloc.allocate(1);
            } catch (std::bad_alloc&) {
                throw OutOfMemoryException("Buffer was overflowed");
            }
            std::allocator_traits<AT>::construct(_alloc, _head, Node{other._head->value,
                nullptr});

            Node* current = _head;
            Node* other_current = other._head->next;

            while (other_current != nullptr) {
                try {
                    Node *new_node = _alloc.allocate(1);
                    std::allocator_traits<AT>::construct(_alloc, new_node, Node{other_current->value,
                    nullptr});
                    current->next = new_node;
                    current = new_node;
                    other_current = other_current->next;
                } catch (std::bad_alloc&) {
                    throw OutOfMemoryException("Buffer was overflowed");
                }
            }
        }
        _size = other._size;
    }
    return *this;
}

template <class T>
Stack<T>& Stack<T>::operator=(Stack &&other) noexcept {
    if (this != &other) {
        _clear();
        if (other._head == nullptr)
            _head = nullptr;
        else {
            while (other._head->next != nullptr) {
                _head = other._head;
                other._head = other._head->next;
            }
        }
        _size = other._size;
    }
    return *this;
}

template <class T>
bool Stack<T>::operator==(const Stack &other) const {
    if (_size == other._size) {
        auto *first_head = _head;
        auto *second_head = other._head;

        while (first_head) {
            if (first_head->value != second_head->value)
                return false;

            first_head = first_head->next;
            second_head = second_head->next;
        }
        return true;
    }
    return false;
}

template <class T>
bool Stack<T>::operator!=(const Stack &other) const {
    if (_size == other._size) {
        auto *first_head = _head;
        auto *second_head = other._head;

        while (first_head) {
            if (first_head->value != second_head->value)
                return true;

            first_head = first_head->next;
            second_head = second_head->next;
        }
        return false;
    }
    return true;
}

template <class T>
void Stack<T>::push(T element) {
    try {
        Node *node = _alloc.allocate(1);
        std::allocator_traits<AT>::construct(_alloc, node, Node{element, _head});
        _head = node;
        ++_size;
    } catch (std::bad_alloc&) {
        throw OutOfMemoryException("Buffer was overflowed");
    }
}

template <class T>
std::shared_ptr<T> Stack<T>::pop() {
    if (_head == nullptr)
        throw EmptyStackException("Stack is empty");

    Node* temp = _head;
    std::shared_ptr<T> result = std::make_shared<T>(_head->value);
    _head = _head->next;

    std::allocator_traits<AT>::destroy(_alloc, temp);
    _alloc.deallocate(temp, 1);
    --_size;

    return result;
}

template <class T>
std::shared_ptr<T> Stack<T>::top() const {
    if (_head == nullptr)
        throw EmptyStackException("Stack is empty");

    return std::make_shared<T>(_head->value);
}

template <class T>
size_t Stack<T>::size() const {
    return _size;
}

template <class T>
bool Stack<T>::empty() const {
    return _size == 0;
}

template <class T>
void Stack<T>::clear() {
    _clear();
}

template <class T>
void Stack<T>::_clear() {
    while (_head) {
        Node* temp = _head;
        _head = _head->next;
        std::allocator_traits<AT>::destroy(_alloc, temp);
        _alloc.deallocate(temp, 1);
        --_size;
    }
}

template <class T>
std::ostream& operator<<(std::ostream &os, const Stack<T> &stack) {
    os << ']';
    if (stack._size) {
        auto *elem = stack._head;
        while (elem->next) {
            os << elem->value << ", ";
            elem = elem->next;
        }
        os << elem->value;
    }
    os << ']';
    return os;
}

template <class T>
Stack<T>::const_iterator::const_iterator(const Node* node) : _current(node) {}

template <class T>
const T& Stack<T>::const_iterator::operator*() const {
    return _current->value;
}

template <class T>
const T* Stack<T>::const_iterator::operator->() const {
    return &(_current->value);
}

template <class T>
typename Stack<T>::const_iterator& Stack<T>::const_iterator::operator++() {
    _current = _current->next;
    return *this;
}

template <class T>
typename Stack<T>::const_iterator Stack<T>::const_iterator::operator++(int) {
    const_iterator temp = *this;
    ++(*this);
    return temp;
}

template <class T>
bool Stack<T>::const_iterator::operator==(const const_iterator& other) const {
    return _current == other._current;
}

template <class T>
bool Stack<T>::const_iterator::operator!=(const const_iterator& other) const {
    return _current != other._current;
}

template <class T>
typename Stack<T>::const_iterator Stack<T>::begin() const {
    return const_iterator(_head);
}

template <class T>
typename Stack<T>::const_iterator Stack<T>::end() const {
    return const_iterator(nullptr);
}