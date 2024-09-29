#include <tools.h>
#include <exceptions.h>


unsigned char get_hex_numeric(unsigned int numeric) {
    auto symbols = "0123456789ABCDEF";

    if (numeric <= 15 && numeric >= 0)
        return symbols[numeric];
        
    throw NoHexNumericException("Received no hex numeric");
}

unsigned int get_decimal_numeric(unsigned char numeric) {
    auto symbols = "0123456789ABCDEF";

    for (int i = 0; i < 16; ++i)
        if (symbols[i] == numeric)
            return i;

    throw NoHexNumericException("Received no hex numeric");
}

unsigned char get_numeric(unsigned char numeric) {
    auto symbols = "0123456789ABCDEF";
    numeric = toupper(numeric);
    
    for (int i = 0; i < 16; ++i)
        if (symbols[i] == numeric)
            return symbols[i];
            
    throw NoHexNumericException("Received no hex numeric");
}