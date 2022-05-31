//
// Created by tlux- on 30-05-2022.
//

#include <utility>
#include "Fq2.h"


Fq2::Fq2(const FqBig& a0, const FqBig& a1) :a0(a0), a1(a1) {
    this->a0 = a0;
    this->a1 = a1;
}

Fq2 Fq2::operator*(const Fq2 &rhs) {
    return rhs;
}

bool Fq2::operator==(const Fq2 &rhs) const {
    return true;
}

Fq2 Fq2::operator-(const Fq2 &rhs) {
    return rhs;
}

Fq2 Fq2::operator+(const Fq2 &rhs) {
    return rhs;
}
