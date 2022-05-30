//
// Created by tlux- on 30-05-2022.
//
#include "../BigInt.hpp"

#ifndef FQ_H
#define FQ_H

class Fq {
    const BigInt PRIME = BigInt(
            "40024095552216673934177898257359041565568828199390078853320"
            "58136124031650490837864442687629129015664037894272559787");
public:
    explicit Fq(const BigInt & value);

    Fq operator+(const Fq &rhs);

    Fq operator-(const Fq &rhs);

    Fq operator*(const Fq &rhs);

    bool operator==(const Fq &rhs) const;

private:
    BigInt value;
};

#endif //FQ_H
