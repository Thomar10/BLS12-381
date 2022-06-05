//
// Created by Thomas Luxhøj on 30-05-2022.
//

#include <bitset>
#include <gmpxx.h>
#include "Fq.h"

mpz_class PRIME_BIG(
		"4002409555221667393417789825735904156556882819939007885332058136124031650490837864442687629129015664037894272559787",
		10);

const unsigned long PRIME[] = {13402431016077863595UL, 2210141511517208575UL, 7435674573564081700UL,
							   7239337960414712511UL, 5412103778470702295UL, 1873798617647539866UL};

Fq::Fq(const mpz_t& bigint)
{
	if (mpz_cmp(bigint, PRIME_BIG.get_mpz_t())>=0) {
		mpz_t valueToSet;
		mpz_init(valueToSet);
		mpz_mod(valueToSet, bigint, PRIME_BIG.get_mpz_t());
	}
	void* outRaw = malloc(FQ_BYTES);
	mpz_export(outRaw, nullptr,
			-1, 6*8,
			-1, 0, bigint);
	this->value = static_cast<u_int64_t*>(outRaw);
}

unsigned long* add(unsigned long* result, const unsigned long* left, const unsigned long* right)
{
	unsigned long difference = 0;
	for (int i = 0; i<FQ_NUMBER_OF_LIMBS; i++) {
		unsigned long sum = left[i]+right[i]+difference;
		difference = sum<left[i] ? 1 : 0;
		result[i] = sum;
	}
	return result;
}

int sub(unsigned long* result, const unsigned long* left, const unsigned long* right)
{
	unsigned long borrow = 0;
	unsigned long diff;
	for (int i = 0; i<FQ_NUMBER_OF_LIMBS; i++) {
		diff = left[i]-right[i]-borrow;
		borrow = ((~left[i] & right[i]) | (~(left[i] ^ right[i]) & diff)) >> 63;
		result[i] = diff;
	}
	return (int)borrow;
}

Fq Fq::operator+(const Fq& rhs)
{
	auto* result = (unsigned long*)malloc(FQ_BYTES);
	add(result, this->value, rhs.value);
	if (compareValues(result, PRIME)>=0) {
		sub(result, result, PRIME);
	}
	return Fq(result);
}

Fq Fq::operator-(const Fq& rhs)
{
	auto* diff = (unsigned long*)malloc(FQ_BYTES);
	int borrow = sub(diff, this->value, rhs.value);
	if (borrow!=0) {
		add(diff, diff, PRIME);
	}
	return Fq(diff);
}

Fq Fq::operator*(const Fq& rhs)
{
	return Fq(this->value);
}

bool Fq::operator==(const Fq& rhs) const
{
	return compareValues(this->value, rhs.value)==0;
}

Fq::Fq(const unsigned long* limbs)
		:value(const_cast<unsigned long*>(limbs)) { }

std::string Fq::toString() const
{
	// Simply converting the limbs back into mpz_t as toString
	// is only used for debugging.
	mpz_t toString;
	mpz_init(toString);
	mpz_import(toString, 1, -1, FQ_BYTES, -1, 0, this->value);
	//auto* stringPointer = static_cast<char*>(malloc(FQ_BYTES));
	auto* stringPointer = mpz_get_str(nullptr, 10, toString);
	//mpz_clear(toString);
	return stringPointer;
}

/**
 *	Returns a byte array with most least word first.
 *
 * @return
 */
unsigned char* Fq::serialize() const
{
	auto* arr = (unsigned char*)malloc(FQ_BYTES);
	for (int j = 0; j<FQ_NUMBER_OF_LIMBS; j++) {
		for (int i = 0; i<8; i++) {
			arr[i+(j*8)] = (((unsigned long)this->value[j]) >> (56-(8*i))) & 0xFFu;
		}
	}
	return arr;
}
int Fq::compareValues(const unsigned long* left, const unsigned long* right)
{
	for (int i = FQ_NUMBER_OF_LIMBS-1; i>=0; i--) {
		auto diff = left[i]-right[i];
		auto borrow = ((~left[i] & right[i]) | (~(left[i] ^ right[i]) & diff)) >> 63;
		if (borrow!=0) {
			return -1;
		}
		else if (diff>0) {
			return 1;
		}
	}
	return 0;
}
