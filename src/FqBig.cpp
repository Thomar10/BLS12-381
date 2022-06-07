#include "FqBig.h"


mpz_class PRIME("1A0111EA397FE69A4B1BA7B6434BACD764774B84F38512BF6730D2A0F6B0F6241EABFFFEB153FFFFB9FEFFFFFFFFAAAB", 16);

mpz_class REDUCER_RECIPROCAL_BIG("14fec701e8fb0ce9ed5e64273c4f538b1797ab1458a88de9343ea97914956dc87fe11274d898fafbf4d38259380b4820", 16);

mpz_class MASK("39402006196394479212279040100143613805079739270465446667948293404245721771497210611414266254884915640806627990306815", 10);

mpz_class FACTOR_BIG("31812345668571394200522959936182890292651532161468729907319195075155855129916747767697203739041175453056836858347517", 10);


const int REDUCER_BITS = 384;

void convertIntoMontgomery(mpz_t& value) {
	mpz_mul_2exp(value, value, REDUCER_BITS);
	mpz_mod(value, value, PRIME.get_mpz_t());
}

void convertOutMontgomery(mpz_t& value) {
	mpz_mul(value, value, REDUCER_RECIPROCAL_BIG.get_mpz_t());
	mpz_mod(value, value, PRIME.get_mpz_t());
}

FqBig::FqBig(const mpz_t &value) {
	mpz_t valueToSet;
	mpz_init(valueToSet);
	mpz_set(valueToSet, value);
	convertIntoMontgomery(valueToSet);
    mpz_set(this->value, valueToSet);
}

FqBig FqBig::operator+(const FqBig &rhs) {
    mpz_t c;
    mpz_init(c);
    mpz_add(c, this->value, rhs.value);
	if (mpz_cmp(c, PRIME.get_mpz_t()) >= 0) {
		mpz_mod(c, c, PRIME.get_mpz_t());
	}
    return FqBig{c};
}

FqBig FqBig::operator-(const FqBig &rhs) {
	mpz_t c;
	mpz_init(c);
	if (mpz_cmp(this->value, rhs.value) < 0) {
		mpz_add(c, this->value, PRIME.get_mpz_t());
		mpz_sub(c, c, rhs.value);
	} else {
		mpz_sub(c, this->value, rhs.value);
	}
    return FqBig{c};
}

FqBig FqBig::operator*(const FqBig &rhs) {
	mpz_t c, temp;
	mpz_inits(c, temp, nullptr);
    mpz_mul(c, this->value, rhs.value);
	mpz_and(temp, c, MASK.get_mpz_t());
	mpz_mul(temp, temp, FACTOR_BIG.get_mpz_t());
	mpz_and(temp, temp, MASK.get_mpz_t());
	mpz_mul(temp, temp, PRIME.get_mpz_t());
	mpz_add(c, c, temp);
	mpz_div_2exp(c, c, REDUCER_BITS);
	int cmp = mpz_cmp(c, PRIME.get_mpz_t());
	if (cmp < 0) {
		return FqBig{c};
	} else {
		mpz_sub(c, c, PRIME.get_mpz_t());
		return FqBig{c};
	}
}

bool FqBig::operator==(const FqBig &rhs) const {
    int result = mpz_cmp(this->value, rhs.value);
    return result == 0;
}
