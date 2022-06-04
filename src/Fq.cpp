//
// Created by Thomas Luxhøj on 30-05-2022.
//

#include <bitset>
#include <tuple>
#include <cstring>
#include "Fq.h"

Fq::Fq(const mpz_t& bigint)
{
	void* outRaw = malloc(FQ_BYTES);
	mpz_export(outRaw, nullptr,
			-1, 6*8,
			-1, 0, bigint);
	this->value = static_cast<u_int64_t*>(outRaw);
	//mpz_clear(const_cast<mpz_ptr>(bigint));
}

unsigned long* add(const unsigned long* left, const unsigned long* right) {
	auto* result = (unsigned long*)malloc(FQ_BYTES);
	unsigned long difference = 0;
	for (int i = 0; i<FQ_NUMBER_OF_LIMBS; ++i) {
		unsigned long leftVal = left[i];
		unsigned long sum = leftVal + right[i] + difference;
		difference = sum < leftVal ? 1 : 0;
		result[i] = sum;
	}
	return result;
}

std::tuple<unsigned long long, int> subLongs(unsigned long left, unsigned long right, int borrow)
{
	auto difference = left-right-borrow;
	auto newBorrow = left >= (difference - right) ? 0 : 1;
	return std::make_tuple(difference, newBorrow);
}

std::tuple<unsigned long*, int> sub(unsigned long* left, unsigned long* right) {
	auto* result = (unsigned long*)malloc(FQ_BYTES);
	int borrow = 0;
	unsigned long diff;
	for (int i = 0; i<FQ_NUMBER_OF_LIMBS; ++i) {
		std::tie(diff, borrow) =
				subLongs(left[i],
						right[i],
						borrow);
		result[i] = diff;
	}
	return std::make_tuple(result, borrow);
}

Fq Fq::operator+(const Fq& rhs)
{
	unsigned long* result = add(this->value, rhs.value);
	if (compareValues(result, PRIME) >= 0) {
		int borrow = 0;
		unsigned long diff;
		for (int i = 0; i<FQ_NUMBER_OF_LIMBS; ++i) {
			diff = result[i]-PRIME[i]-borrow;
			borrow = result[i] >= (diff - PRIME[i]) ? 0 : 1;
			result[i] = diff;
		}
		return Fq(result);
	}
	return Fq(result);
}

Fq Fq::operator-(const Fq& rhs)
{
	unsigned long* diff;
	int borrow;
	std::tie(diff, borrow) = sub(this->value, rhs.value);
	if (borrow != 0) {
		unsigned long* newRes = add(diff, const_cast<unsigned long*>(PRIME));
		free(diff);
		return Fq(newRes);
	}
	return Fq(diff);
}

Fq Fq::operator*(const Fq& rhs)
{
	return Fq(this->value);
}

bool Fq::operator==(const Fq& rhs) const
{
	return compareValues(this->value, rhs.value) == 0;
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
	for (int j = 0; j<6; j++) {
		for (int i = 0; i<8; i++) {
			arr[i+(j*8)] = (((unsigned long)this->value[j]) >> (56-(8*i))) & 0xFFu;
		}
	}
	return arr;
}
int Fq::compareValues(const unsigned long* left, const unsigned long* right)
{
	for (int i = FQ_NUMBER_OF_LIMBS - 1; i >= 0; i--) {
		auto intermediate = (signed long)(left[i] - right[i]);
		if (intermediate < 0) {
			return -1;
		} else if (intermediate > 0) {
			return 1;
		}
	}
	return 0;
}
