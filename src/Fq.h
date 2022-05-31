//
// Created by Thomas Luxhøj on 30-05-2022.
//

#ifndef BLS12_381_FQ_H
#define BLS12_381_FQ_H

#include <gmp.h>
#include "FiniteField.h"
#include "iostream"

class Fq : FiniteField<Fq> {
	explicit Fq(const mpz_t& big_int);

	Fq operator+(const Fq& rhs) override;

	Fq operator-(const Fq& rhs) override;

	Fq operator*(const Fq& rhs) override;

	bool operator==(const Fq& rhs) const override;

//private:
	unsigned char
			value[];
};


#endif //BLS12_381_FQ_H
