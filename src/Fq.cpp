//
// Created by Thomas Luxhøj on 30-05-2022.
//

#include <bitset>
#include <gmpxx.h>
#include "Fq.h"

mpz_class PRIME_BIG(
		"4002409555221667393417789825735904156556882819939007885332058136124031650490837864442687629129015664037894272559787",
		10);
mpz_class REDUCER_RECIPROCAL(
		"14fec701e8fb0ce9ed5e64273c4f538b1797ab1458a88de9343ea97914956dc87fe11274d898fafbf4d38259380b4820", 16);

const unsigned long PRIME[] = {13402431016077863595UL, 2210141511517208575UL, 7435674573564081700UL,
							   7239337960414712511UL, 5412103778470702295UL, 1873798617647539866UL};

const unsigned long FACTOR[] = {9940570264628428797UL, 2912381532814513128, 1652591199965612872,
								1868090109324352332, 7544399084751736664, 14893510650384546964UL};


const int REDUCER_BITS = 384;

int compareValues(const unsigned long* left, const unsigned long* right)
{
	for (int i = FQ_NUMBER_OF_LIMBS-1; i>=0; i--) {

		if (left[i]<right[i]) {
			return -1;
		}
		else if (left[i]>right[i]) {
			return 1;
		}
	}
	return 0;
}

void convertIntoMontgomery(mpz_t& value)
{
	mpz_mul_2exp(value, value, REDUCER_BITS);
	mpz_mod(value, value, PRIME_BIG.get_mpz_t());
}

void convertOutMontgomery(mpz_t& value)
{
	mpz_mul(value, value, REDUCER_RECIPROCAL.get_mpz_t());
	mpz_mod(value, value, PRIME_BIG.get_mpz_t());
}

Fq::Fq(const mpz_t& bigint)
{
	// ALSO FIND OUY WHY I CANNOT CLEAR valueToSet...
	mpz_t valueToSet;
	mpz_init(valueToSet);
	mpz_set(valueToSet, bigint);
	convertIntoMontgomery(valueToSet);
	void* outRaw = malloc(FQ_BYTES);
	mpz_export(outRaw, nullptr,
			-1, 6*8,
			-1, 0, valueToSet);
	this->value = static_cast<u_int64_t*>(outRaw);
	//mpz_clear(valueToSet);
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

unsigned long multiplyHigh(unsigned long x, unsigned long y)
{
	unsigned long x1 = x >> 32;
	unsigned long x2 = x & 0xFFFFFFFFL;
	unsigned long y1 = y >> 32;
	unsigned long y2 = y & 0xFFFFFFFFL;
	unsigned long z2 = x2*y2;
	unsigned long t = x1*y2+(z2 >> 32);
	unsigned long z1 = t & 0xFFFFFFFFL;
	unsigned long z0 = t >> 32;
	z1 += x2*y1;
	return x1*y1+z0+(z1 >> 32);
}

void multiplyUnsignedLongsAndAdd(
		unsigned long* result, unsigned long left,
		unsigned long right, unsigned long carry,
		unsigned long overflow)
{
	unsigned long lowerPart = left*right;
	unsigned long highPart = multiplyHigh(left, right);
	unsigned long add1 = lowerPart+overflow;
	unsigned long overflow1 = add1<lowerPart ? 1 : 0;
	unsigned long add2 = add1+carry;
	unsigned long overflow2 = add2<add1 ? 1 : 0;
	unsigned long highPart1 = highPart+overflow2+overflow1;
	result[0] = highPart1;
	result[1] = add2;
}

void mul(unsigned long* result, unsigned long* multiplyAndAdd, const unsigned long* left, const unsigned long* right)
{
	for (int i = 0; i<FQ_NUMBER_OF_LIMBS; i++) {
		unsigned long carry = 0;
		for (int j = 0; j<FQ_NUMBER_OF_LIMBS; j++) {
			multiplyUnsignedLongsAndAdd(multiplyAndAdd, left[i], right[j],
					carry, result[i+j]);
			carry = multiplyAndAdd[0];
			result[i+j] = multiplyAndAdd[1];
		}
		result[i+FQ_NUMBER_OF_LIMBS] = carry;
	}
}

void multiplyAndModReduce(unsigned long* result, unsigned long* multiplyAndAdd, const unsigned long* product, const unsigned long* factor)
{
	for (int i = 0; i<=FQ_NUMBER_OF_LIMBS-1; i++) {
		unsigned long carry = 0;
		for (int j = 0; j<FQ_NUMBER_OF_LIMBS-i; j++) {
			multiplyUnsignedLongsAndAdd(multiplyAndAdd, product[i], factor[j], carry, result[i+j]);
			carry = multiplyAndAdd[0];
			result[i+j] = multiplyAndAdd[1];
		}
	}
}

unsigned long* addLong(unsigned long* result, const unsigned long* left, const unsigned long* right)
{
	unsigned long difference = 0;
	for (int i = 0; i<FQ_NUMBER_OF_LIMBS*2; i++) {
		unsigned long sum = left[i]+right[i]+difference;
		difference = sum<left[i] ? 1 : 0;
		result[i] = sum;
	}
	return result;
}

unsigned long* reduce(unsigned long* product, unsigned long* multiplyAndAdd)
{
	auto* temp = static_cast<unsigned long*>(malloc(FQ_BYTES));
	multiplyAndModReduce(temp, multiplyAndAdd, product, FACTOR);
	auto* reduced1 = static_cast<unsigned long*>(malloc(FQ_BYTES*2));
	mul(reduced1,multiplyAndAdd, temp, PRIME);
	addLong(reduced1, product, reduced1);
	// Shift right 384 bits, here comes the advance of not our chosen reducer.
	// As the shift is simply the upper 6 limbs.
	std::copy(reduced1+6, reduced1+12, temp);
	if (compareValues(temp, PRIME)<0) {
		return temp;
	}
	else {
		sub(temp, temp, PRIME);
		return temp;
	}
}

Fq Fq::operator*(const Fq& rhs)
{
	auto* result = (unsigned long*)malloc(FQ_BYTES*2);
	auto* multiplyAndAdd = (unsigned long*)malloc(sizeof(unsigned long) * 2);
	mul(result, multiplyAndAdd, this->value, rhs.value);
    unsigned long *resultLimbs = reduce(result, multiplyAndAdd);
    free(multiplyAndAdd);
    return Fq(resultLimbs);
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
	convertOutMontgomery(toString);
	auto* stringPointer = mpz_get_str(nullptr, 10, toString);
	mpz_clear(toString);
	return stringPointer;
}

/**
 * 	****DOES NOT WORK****
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