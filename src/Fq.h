//
// Created by Thomas Luxhøj on 30-05-2022.
//

#ifndef BLS12_381_FQ_H
#define BLS12_381_FQ_H

#include <gmp.h>
#include "FiniteField.h"
#include "iostream"

class Fq : FiniteField<Fq> {
public:
	explicit Fq(const mpz_t& big_int);

	Fq operator+(const Fq& rhs) override;

	Fq operator-(const Fq& rhs) override;

	Fq operator*(const Fq& rhs) override;

	bool operator==(const Fq& rhs) const override;

	[[nodiscard]] std::string toString() const;

//private:
	unsigned long* value;

private:
	explicit Fq(const unsigned long* limbs);
};

#endif //BLS12_381_FQ_H
