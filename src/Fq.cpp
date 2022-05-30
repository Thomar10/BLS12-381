#include "Fq.h"

Fq::Fq(const BigInt &value) {
    this->value = value;
}

Fq Fq::operator+(const Fq &rhs) {
    return Fq{(this->value + rhs.value) % PRIME};
}

Fq Fq::operator-(const Fq &rhs) {
    return Fq{(this->value - rhs.value) % PRIME};
}

Fq Fq::operator*(const Fq &rhs) {
    return Fq{(this->value * rhs.value) % PRIME};
}

bool Fq::operator==(const Fq &rhs) const {
    return this->value == rhs.value;
}