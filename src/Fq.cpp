#include "Fq.h"

const BigInt PRIME = BigInt(
        "4002409555221667393417789825735904156556882819939007885332058136124031650490837864442687629129015664037894272559787");

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