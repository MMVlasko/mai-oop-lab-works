#include <cmath>
#include <algorithm>

#include <hex.h>
#include <tools.h>
#include <exceptions.h>

Hex::Hex() : _number {new Array("0")} {}

Hex::Hex(const std::string &t) {
    if (t == "")
        throw NoHexNumericException("Received empty string");

    _number = new Array();

    for (int i = t.size() - 1; i >= 0; --i)
        _number->add(get_numeric(t[i]));
}

Hex::Hex(unsigned long long int number) {
    _number = new Array();

    while (number > 0) {
        _number->add(get_hex_numeric(number % 16));
        number /= 16;
    }
}

Hex::Hex(const Hex &other) : _number {new Array(*other._number)} {}
 
Hex::Hex(Hex &&other) noexcept : _number {new Array(*other._number)} {} 

Hex& Hex::operator=(const Hex &other) { 
    if (this != &other)
        _number = new Array(*other._number);

    return *this; 
} 

Hex& Hex::operator=(Hex &&other) noexcept { 
    if (this != &other)
        _number = new Array(*other._number);

    return *this; 
} 

Hex::~Hex() noexcept {
    delete _number;
}

unsigned long long int Hex::to_decimal() {
    unsigned long long int result = 0;

    for (int i = 0; i < _number->size; i++) {
        unsigned long long int digit = get_decimal_numeric((*_number)[i]) * static_cast<unsigned long long int>(pow(16, i));

        // если очередное слагоемое вышло за границу lli
        if (digit == 0 && get_decimal_numeric((*_number)[i]) != 0)
            throw TooBigNumberException("The decimal representation is too big");

        result += digit;
    }

    // если итоговая сумма вышла за границу lli
    if (result == 0 && to_string() != "0")
        throw TooBigNumberException("The decimal representation is too big");

    return result;
}

std::string Hex::to_string() {
    std::string result = _number->to_string();
    std::reverse(result.begin(), result.end());

    return result;
}

Hex Hex::operator+(Hex &other) {
    return Hex(to_decimal() + other.to_decimal());
}

Hex Hex::operator-(Hex &other) {
    int result = to_decimal() - other.to_decimal();

    if (result < 0)
        throw ResultIsNegativeException("Result shouldn't be negative");

    return Hex(to_decimal() - other.to_decimal());
}

bool Hex::operator>(Hex &other) {
    return to_decimal() > other.to_decimal();
}

bool Hex::operator<(Hex &other) {
    return to_decimal() < other.to_decimal();
}

bool Hex::operator>=(Hex &other) {
    return to_decimal() >= other.to_decimal();
}

bool Hex::operator<=(Hex &other) {
    return to_decimal() <= other.to_decimal();
}

bool Hex::operator==(Hex &other) {
    return to_decimal() == other.to_decimal();
}

bool Hex::operator!=(Hex &other) {
    return to_decimal() != other.to_decimal();
}

std::ostream& operator<<(std::ostream& os, Hex& number) {
    os << number.to_string();
    
    return os;
}