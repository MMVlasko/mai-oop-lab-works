#include "../include/hex.h"
#include "../include/tools.h"
#include "../include/exceptions.h"

#include <cmath>

Hex::Hex() : _number {new Array("0")} {}

Hex::Hex(const std::string &t) : _number {new Array(t)} {}

Hex::Hex(unsigned int number) {
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

unsigned int Hex::to_decimal() {
    unsigned int result = 0;
    for (int i = 0; i < _number->size; i++)
        result += get_decimal_numeric((*_number)[i]) * static_cast<unsigned int>(pow(16, i));
    return result;
}

Hex Hex::operator+(Hex &other) {
    return Hex(to_decimal() + other.to_decimal());
}

Hex Hex::operator-(Hex &other) {
    auto result = to_decimal() - other.to_decimal();

    if (result < 0)
        throw ResultIsNegativeException("Result shouldn't be negative");

    return Hex(to_decimal() + other.to_decimal());
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
    os << (number._number)->to_string();
    return os;
}