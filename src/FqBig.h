//
// Created by tlux- on 30-05-2022.
//

#ifndef BLS12_381_FQBIG_H
#define BLS12_381_FQBIG_H

#include "FiniteField.h"
#include <gmpxx.h>

class FqBig : FiniteField<FqBig>{

public:
    explicit FqBig(const mpz_t &value);

    FqBig operator+(const FqBig &rhs) override;

    FqBig operator-(const FqBig &rhs) override;

    FqBig operator*(const FqBig &rhs) override;

    bool operator==(const FqBig &rhs) const override;

    [[nodiscard]] std::string toString() const;
//private:
    mpz_t value{};
};

#endif //BLS12_381_FQBIG_H
