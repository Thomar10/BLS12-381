//
// Created by tlux- on 30-05-2022.
//

#ifndef BLS12_381_FQ_H
#define BLS12_381_FQ_H

#include "FiniteField.h"
#include "../BigInt.hpp"

//#define BigInt PRIME = BigInt("4002409555221667393417789825735904156556882819939007885332058136124031650490837864442687629129015664037894272559787");
class Fq : FiniteField<Fq>{

public:
    explicit Fq(const BigInt &value);

    Fq operator+(const Fq &rhs) override;

    Fq operator-(const Fq &rhs) override;

    Fq operator*(const Fq &rhs) override;

    bool operator==(const Fq &rhs) const override;

private:
    BigInt value;
};

#endif //BLS12_381_FQ_H
