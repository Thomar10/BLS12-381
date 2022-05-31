#include "FqBig.h"


mpz_class PRIME("1A0111EA397FE69A4B1BA7B6434BACD764774B84F38512BF6730D2A0F6B0F6241EABFFFEB153FFFFB9FEFFFFFFFFAAAB", 16);


FqBig::FqBig(const mpz_t &value) {
    mpz_set(this->value, value);
//    this->value = value;
}

FqBig FqBig::operator+(const FqBig &rhs) {
    mpz_t c;
    mpz_init(c);
    mpz_add(c, this->value, rhs.value);
    mpz_mod(c, c, PRIME.get_mpz_t());
    return FqBig{c};
}

FqBig FqBig::operator-(const FqBig &rhs) {
    mpz_sub(this->value, this->value, rhs.value);
    return FqBig{this->value};// % PRIME};
}

FqBig FqBig::operator*(const FqBig &rhs) {
    mpz_mul(this->value, this->value, rhs.value);
    return FqBig{this->value};// % PRIME};
}

bool FqBig::operator==(const FqBig &rhs) const {
    int result = mpz_cmp(this->value, rhs.value);
    return result == 0;
}
