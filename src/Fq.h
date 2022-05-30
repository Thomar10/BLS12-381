//
// Created by tlux- on 30-05-2022.
//

#ifndef BLS12_381_FQ_H
#define BLS12_381_FQ_H

#include "FiniteField.h"
#include <gmpxx.h>

class Fq : FiniteField<Fq>{

public:
    explicit Fq(const mpz_t &value);

    Fq operator+(const Fq &rhs) override;

    Fq operator-(const Fq &rhs) override;

    Fq operator*(const Fq &rhs) override;

    bool operator==(const Fq &rhs) const override;

//private:
    mpz_t value{};
};

#endif //BLS12_381_FQ_H
