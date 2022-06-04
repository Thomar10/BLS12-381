//
// Created by Thomas Luxhøj on 30-05-2022.
//

#ifndef BLS12_381_FQ_H
#define BLS12_381_FQ_H

#include <gmp.h>
#include "FiniteField.h"
#include "iostream"

#define FQ_BYTES 48
#define FQ_NUMBER_OF_LIMBS 6
const unsigned long PRIME[] = {13402431016077863595UL, 2210141511517208575UL, 7435674573564081700UL,
							   7239337960414712511UL, 5412103778470702295UL, 1873798617647539866UL};
class Fq : FiniteField<Fq> {
public:
	explicit Fq(const mpz_t& big_int);

	Fq operator+(const Fq& rhs) override;

	Fq operator-(const Fq& rhs) override;

	Fq operator*(const Fq& rhs) override;

	bool operator==(const Fq& rhs) const override;

	[[nodiscard]] std::string toString() const;

	[[nodiscard]] unsigned char* serialize() const;

	unsigned long* value;
private:
	[[nodiscard]] static int compareValues(const unsigned long* left, const unsigned long* right);
	explicit Fq(const unsigned long* limbs);
};

#endif //BLS12_381_FQ_H
