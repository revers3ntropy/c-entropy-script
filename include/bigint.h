#pragma once

#define ull unsigned long long int;

// Single class BigNumber, all contained in this header file

namespace es {
    class BigNumber {
        ull numerator;
        ull denominator;

    public:
        bool invalid;

        BigNumber (std::string number): invalid(false) {
            std::vector<std::string>* parts = split(number, '.');
            if (parts)
        }
    };
}