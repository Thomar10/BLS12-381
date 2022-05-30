//
// Created by tlux- on 30-05-2022.
//

#ifndef BLS12_381_FQ2_H
#define BLS12_381_FQ2_H

#include "Fq.h"

class Fq2 : FiniteField<Fq2> {

public:
    Fq2 operator+(const Fq2 &rhs) override;

    Fq2 operator-(const Fq2 &rhs) override;

    Fq2 operator*(const Fq2 &rhs) override;

    bool operator==(const Fq2 &rhs) const override;

    Fq2(const Fq &a0, const Fq &a1);

private:
    Fq a0;
    Fq a1;
};


#endif //BLS12_381_FQ2_H
