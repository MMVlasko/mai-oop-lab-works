#pragma once

#include <array.h>

class Hex {
    private:
        Array *_number;

    public:
        Hex();

        Hex(const std::string &t);

        Hex(unsigned long long int number);

        Hex(const Hex &other);

        Hex(Hex &&other) noexcept;

        Hex &operator=(const Hex &other);

        Hex &operator=(Hex &&other) noexcept;

        virtual ~Hex() noexcept;

        unsigned long long int to_decimal();

        std::string to_string();

        Hex operator+(Hex &other);

        Hex operator-(Hex &other);

        bool operator>(Hex &other);

        bool operator<(Hex &other);

        bool operator>=(Hex &other);

        bool operator<=(Hex &other);

        bool operator==(Hex &other);

        bool operator!=(Hex &other);

        friend std::ostream& operator<<(std::ostream& os, Hex& number);
};