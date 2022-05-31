//
// Created by tlux- on 30-05-2022.
//

#ifndef BLS12_381_FQ2_H
#define BLS12_381_FQ2_H

#include "FqBig.h"

class Fq2 : FiniteField<Fq2> {

public:
    Fq2 operator+(const Fq2 &rhs) override;

    Fq2 operator-(const Fq2 &rhs) override;

    Fq2 operator*(const Fq2 &rhs) override;

    bool operator==(const Fq2 &rhs) const override;

    Fq2(const FqBig &a0, const FqBig &a1);

private:
    FqBig a0;
    FqBig a1;
};


#endif //BLS12_381_FQ2_H
