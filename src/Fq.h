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

class Fq : FiniteField<Fq> {
public:
	/**
	 * Initialize a Fq from a mpz_t.
	 * If the value is above PRIME the value will be big_int % PRIME.
	 * Note it does not free the memory for the mpz_t.
	 * @param big_int mpz_t to be made into a fq.
	 */
	explicit Fq(const mpz_t& big_int);

	/**
	 * Adds this with rhs.
	 * @param rhs the Fq to add.
	 * @return this + rhs.
	 */
	Fq operator+(const Fq& rhs) override;

	/**
	 * Subtracts this with rhs.
	 * @param rhs the Fq to subtract.
	 * @return this - rhs;
	 */
	Fq operator-(const Fq& rhs) override;

	/**
	 * Multiplies this with rhs
	 * @param rhs the Fq to multiply with.
	 * @return  this * rhs;
	 */
	Fq operator*(const Fq& rhs) override;

	/**
	 * Checks if two Fq are equal
	 * @param rhs the Fq to check equality with.
	 * @return this == rhs;
	 */
	bool operator==(const Fq& rhs) const override;

	/**
	 * Returns the string value of this Fq.
	 * @return String value of this Fq.
	 */
	[[nodiscard]] std::string toString() const;

	/**
	 * Serialize this Fq into a byte array with least significant first.
	 * @return byte array in little endian.
	 */
	[[nodiscard]] unsigned char* serialize() const;

	unsigned long* value;
private:
	explicit Fq(const unsigned long* limbs);

};

#endif //BLS12_381_FQ_H
