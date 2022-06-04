//
// Created by Thomas Luxhøj on 30-05-2022.
//

#include <cstring>
#include <bitset>
#include <tuple>
#include "Fq.h"
Fq::Fq(const mpz_t& bigint)
{
	void* outRaw = malloc(BYTES);
	mpz_export(outRaw, nullptr,
			-1, 6*8,
			-1, 0, bigint);
	this->value = static_cast<u_int64_t*>(outRaw);
}

std::tuple<unsigned long long, int> add(unsigned long left, unsigned long right, int carry)
{
	auto sum = left+right+carry;
	int carryOut = ((left & right) | ((left | right) ^ sum)) >> 63;
	return std::make_tuple(sum, carryOut);
}

Fq Fq::operator+(const Fq& rhs)
{
	auto size = sizeof(unsigned long)*6;
	auto* result = (unsigned long*)malloc(size);
	int difference = 0;
	unsigned long sum;
	for (int i = 0; i<6; ++i) {
		std::tie(sum, difference) =
				add(this->value[i],
						rhs.value[i],
						difference);
		result[i] = sum;
	}
	std::cout << "result " << std::endl;
	for (int i = 0; i<6; i++) {
		std::cout << std::bitset<64>(result[i]).to_string() << std::endl;
	}
	return Fq(result);
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
		:value(const_cast<unsigned long*>(limbs)) { }
std::string Fq::toString() const
{
	// Simply converting the limbs back into mpz_t as toString
	// is only used for debugging.
	mpz_t toString;
	mpz_init(toString);
	mpz_import(toString, 1, -1, BYTES, -1, 0, this->value);
	auto* stringPointer = static_cast<char*>(malloc(BYTES));
	mpz_get_str(stringPointer, 10, toString);
	mpz_clear(toString);
	return stringPointer;
}


/**
 *	Returns a byte array with most least word first.
 *
 * @return
 */
unsigned char* Fq::serialize() const
{
	auto* arr = (unsigned char*)malloc(BYTES);
	for (int j = 0; j<6; j++) {
		for (int i = 0; i<8; i++) {
			arr[i+(j*8)] = (((unsigned long)this->value[j]) >> (56-(8*i))) & 0xFFu;
		}
	}
	return arr;
}