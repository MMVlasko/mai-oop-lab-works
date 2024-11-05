#pragma once

#include <memory>

template <class T>
class Stack {
    private:
        struct Node {
            T value;
            Node* next;
        };
    public:
        using allocator_type = std::pmr::polymorphic_allocator<Node>;

    private:
        Node* _head = nullptr;
        allocator_type _alloc;
        size_t _size;

    private:
        void _clear();

    public:
        explicit Stack(const allocator_type& alloc = {});

        Stack(const Stack &other, std::pmr::memory_resource* resource = nullptr);

        Stack(Stack &&other) noexcept;

        virtual ~Stack() noexcept;

        Stack &operator=(const Stack &other);

        Stack &operator=(Stack &&other) noexcept;

        void push(T element);

        std::shared_ptr<T> pop();

        [[nodiscard]] size_t size() const;

        [[nodiscard]] bool empty() const;

        void clear();

        template <class U>
        friend std::ostream& operator<<(std::ostream &os, const Stack<U> &stack);

};


template <class T>
Stack<T>::Stack(const allocator_type& alloc) : _alloc(alloc), _size(0) {}

template <class T>
Stack<T>::Stack(const Stack &other, std::pmr::memory_resource* resource)
    : _alloc(resource ? resource : other._alloc.resource()) {

    if (other._head == nullptr)
        _head = nullptr;
    else {
        _head = _alloc.allocate(1);
        std::allocator_traits<allocator_type>::construct(_alloc, _head, Node{other._head->value, nullptr});

        Node* current = _head;
        Node* other_current = other._head->next;

        while (other_current != nullptr) {
            Node* new_node = _alloc.allocate(1);
            std::allocator_traits<allocator_type>::construct(_alloc, new_node, Node{other_current->value,
                nullptr});

            current->next = new_node;
            current = new_node;
            other_current = other_current->next;
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
            _head = _alloc.allocate(1);
            std::allocator_traits<allocator_type>::construct(_alloc, _head, Node{other._head->value,
                nullptr});

            Node* current = _head;
            Node* other_current = other._head->next;

            while (other_current != nullptr) {
                Node* new_node = _alloc.allocate(1);
                std::allocator_traits<allocator_type>::construct(_alloc, new_node, Node{other_current->value,
                    nullptr});

                current->next = new_node;
                current = new_node;
                other_current = other_current->next;
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
void Stack<T>::push(T element) {
    Node* node = _alloc.allocate(1);
    std::allocator_traits<allocator_type>::construct(_alloc, node, Node{element, _head});
    _head = node;
    ++_size;
}

template <class T>
std::shared_ptr<T> Stack<T>::pop() {
    if (_head == nullptr)
        throw std::out_of_range("Stack is empty");

    Node* temp = _head;
    std::shared_ptr<T> result = std::make_shared<T>(_head->value);
    _head = _head->next;

    std::allocator_traits<allocator_type>::destroy(_alloc, temp);
    _alloc.deallocate(temp, 1);
    --_size;

    return result;
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
        std::allocator_traits<allocator_type>::destroy(_alloc, temp);
        _alloc.deallocate(temp, 1);
        --_size;
    }
}

template <class T>
std::ostream& operator<<(std::ostream &os, const Stack<T> &stack) {
    os << ']';
    auto *elem = stack._head;
    while (elem->next) {
        os << elem->value << ", ";
        elem = elem->next;
    }
    os << elem->value << ']';
    return os;
}