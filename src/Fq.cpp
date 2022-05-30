#include "Fq.h"


mpz_class PRIME("1A0111EA397FE69A4B1BA7B6434BACD764774B84F38512BF6730D2A0F6B0F6241EABFFFEB153FFFFB9FEFFFFFFFFAAAB", 16);


Fq::Fq(const mpz_t &value) {
    mpz_set(this->value, value);
//    this->value = value;
}

Fq Fq::operator+(const Fq &rhs) {
    mpz_t c;
    mpz_init(c);
    mpz_add(c, this->value, rhs.value);
    mpz_mod(c, c, PRIME.get_mpz_t());
    return Fq{c};
}

Fq Fq::operator-(const Fq &rhs) {
    mpz_sub(this->value, this->value, rhs.value);
    return Fq{this->value};// % PRIME};
}

Fq Fq::operator*(const Fq &rhs) {
    mpz_mul(this->value, this->value, rhs.value);
    return Fq{this->value};// % PRIME};
}

bool Fq::operator==(const Fq &rhs) const {
    int result = mpz_cmp(this->value, rhs.value);
    return result == 0;
}
