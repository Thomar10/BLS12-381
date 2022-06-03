//
// Created by Thomas Luxhøj on 30-05-2022.
//

#include <cstring>
#include "Fq.h"
Fq::Fq(const mpz_t& bigint)
{
	void* outRaw = malloc(sizeof(unsigned long)*6);
	mpz_export(outRaw, nullptr,
			1, 6*8,
			0, 0, bigint);
	this->value = static_cast<u_int64_t*>(outRaw);
}

Fq Fq::operator+(const Fq& rhs)
{
	return Fq(this->value);
}

Fq Fq::operator-(const Fq& rhs)
{
	return Fq(this->value);
}

Fq Fq::operator*(const Fq& rhs)
{
	return Fq(this->value);
}

bool Fq::operator==(const Fq& rhs) const
{
	return false;
}

Fq::Fq(const unsigned long* limbs)
{
	//this->value = limbs;
	auto* valueToAssign = static_cast<unsigned long*>(malloc(sizeof(unsigned long)*6));
	std::memcpy(valueToAssign, limbs, 6);
	this->value = valueToAssign;
}
std::string Fq::toString() const
{
	// Simply converting the limbs back into mpz_t as toString
	// is only used for debugging.
	mpz_t toString;
	mpz_init(toString);
	mpz_import(toString, 1, 0, sizeof(unsigned long)*6, 0, 0, this->value);
	auto* stringPointer = static_cast<char*>(malloc(sizeof(unsigned long)*6));
	mpz_get_str(stringPointer, 10, toString);
	mpz_clear(toString);
	return stringPointer;
}