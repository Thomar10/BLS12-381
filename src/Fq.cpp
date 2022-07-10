//
// Created by Thomas Luxhøj on 30-05-2022.
//

#include "Fq.h"
#include <bitset>
#include <gmpxx.h>

#define stack_helper
typedef __uint128_t bigNum;

typedef stack_helper unsigned long fq_mul_helper[2];
#define fq_helper_new(A)  /* empty */
#define fq_helper_free(A) /* empty */

mpz_class PRIME_BIG("4002409555221667393417789825735904156556882819939007885332"
                    "058136124031650490837864442687629129015664037894272559787",
                    10);
mpz_class REDUCER_RECIPROCAL("14fec701e8fb0ce9ed5e64273c4f538b1797ab1458a88de93"
                             "43ea97914956dc87fe11274d898fafbf4d38259380b4820",
                             16);

const unsigned long PRIME[] = {13402431016077863595UL, 2210141511517208575UL,
                               7435674573564081700UL,  7239337960414712511UL,
                               5412103778470702295UL,  1873798617647539866UL};

const unsigned long FACTOR[] = {9940570264628428797UL, 2912381532814513128,
                                1652591199965612872,   1868090109324352332,
                                7544399084751736664,   14893510650384546964UL};

const int REDUCER_BITS = 384;

static void initializePointerArray(unsigned long *pointerArray, int length) {
  for (int j = 0; j < length * FQ_NUMBER_OF_LIMBS; j++) {
    pointerArray[j] = 0;
  }
}

int compareValues(const unsigned long *left, const unsigned long *right) {
  for (int i = FQ_NUMBER_OF_LIMBS - 1; i >= 0; i--) {

    if (left[i] < right[i]) {
      return -1;
    } else if (left[i] > right[i]) {
      return 1;
    }
  }
  return 0;
}

static void convertIntoMontgomery(mpz_t &value) {
  mpz_mul_2exp(value, value, REDUCER_BITS);
  mpz_mod(value, value, PRIME_BIG.get_mpz_t());
}

static void convertOutMontgomery(mpz_t &value) {
  mpz_mul(value, value, REDUCER_RECIPROCAL.get_mpz_t());
  mpz_mod(value, value, PRIME_BIG.get_mpz_t());
}

Fq::Fq(__mpz_struct *bigint) {
  mpz_t valueToSet;
  mpz_init(valueToSet);
  mpz_set(valueToSet, bigint);
  convertIntoMontgomery(valueToSet);
  void *outRaw = malloc(FQ_BYTES);
  mpz_export(outRaw, nullptr, -1, 6 * 8, -1, 0, valueToSet);
  this->value = (unsigned long *)outRaw;
  mpz_clear(valueToSet);
}

void add(unsigned long *result, const unsigned long *left,
         const unsigned long *right) {
  int i;
  unsigned long carry, c0, c1, r0, r1;

  carry = 0;
  for (i = 0; i < FQ_NUMBER_OF_LIMBS; i++, left++, right++, result++) {
    r0 = (*left) + (*right);
    c0 = (r0 < (*left));
    r1 = r0 + carry;
    c1 = (r1 < r0);
    carry = c0 | c1;
    (*result) = r1;
  }
}

int sub(unsigned long *result, const unsigned long *left,
        const unsigned long *right) {
  unsigned long borrow = 0;
  unsigned long diff;
  for (int i = 0; i < FQ_NUMBER_OF_LIMBS; i++) {
    diff = left[i] - right[i] - borrow;
    borrow = ((~left[i] & right[i]) | (~(left[i] ^ right[i]) & diff)) >> 63;
    result[i] = diff;
  }
  return (int)borrow;
}

Fq Fq::operator+(const Fq &rhs) {
  auto *result = (unsigned long *)malloc(FQ_BYTES);
  add(result, this->value, rhs.value);
  if (compareValues(result, PRIME) >= 0) {
    sub(result, result, PRIME);
  }
  return Fq(result);
}

Fq Fq::operator-(const Fq &rhs) {
  auto *diff = (unsigned long *)malloc(FQ_BYTES);
  int borrow = sub(diff, this->value, rhs.value);
  if (borrow != 0) {
    add(diff, diff, PRIME);
  }
  return Fq(diff);
}

unsigned long multiplyHigh(unsigned long x, unsigned long y) {
  unsigned long high = ((bigNum)x * (bigNum)y) >> 64;
  return high;
  /*unsigned long x1 = x >> 32;
  unsigned long x2 = x & 0xFFFFFFFFL;
  unsigned long y1 = y >> 32;
  unsigned long y2 = y & 0xFFFFFFFFL;
  unsigned long z2 = x2 * y2;
  unsigned long t = x1 * y2 + (z2 >> 32);
  unsigned long z1 = t & 0xFFFFFFFFL;
  unsigned long z0 = t >> 32;
  z1 += x2 * y1;
  return x1 * y1 + z0 + (z1 >> 32);*/
}

void multiplyUnsignedLongsAndAdd(fq_mul_helper result, unsigned long left,
                                 unsigned long right, unsigned long carry,
                                 unsigned long overflow) {
  unsigned long lowerPart = left * right;
  unsigned long highPart = multiplyHigh(left, right);
  unsigned long add1 = lowerPart + overflow;
  unsigned long overflow1 = (add1 < lowerPart);
  unsigned long add2 = add1 + carry;
  unsigned long overflow2 = (add2 < add1);
  unsigned long highPart1 = highPart + overflow2; // + overflow1;
  unsigned long highPart2 = highPart1 + overflow1;

  result[0] = highPart2;
  result[1] = add2;
}

void mul(unsigned long *result, const unsigned long *left,
         const unsigned long *right, unsigned long *multiplyAndAdd) {
  for (int i = 0; i < FQ_NUMBER_OF_LIMBS; i++) {
    unsigned long carry = 0;
    for (int j = 0; j < FQ_NUMBER_OF_LIMBS; j++) {
      multiplyUnsignedLongsAndAdd(multiplyAndAdd, left[i], right[j], carry,
                                  result[i + j]);
      carry = multiplyAndAdd[0];
      result[i + j] = multiplyAndAdd[1];
    }
    result[i + FQ_NUMBER_OF_LIMBS] = carry;
  }
}

void multiplyAndModReduce(unsigned long *result, const unsigned long *product,
                          fq_mul_helper multiplyAndAdd) {
  for (int i = 0; i <= FQ_NUMBER_OF_LIMBS - 1; i++) {
    unsigned long carry = 0;
    for (int j = 0; j < FQ_NUMBER_OF_LIMBS - i; j++) {
      multiplyUnsignedLongsAndAdd(multiplyAndAdd, product[i], FACTOR[j], carry,
                                  result[i + j]);
      carry = multiplyAndAdd[0];
      result[i + j] = multiplyAndAdd[1];
    }
  }
}

void addLong(unsigned long *result, const unsigned long *left,
             const unsigned long *right) {
  unsigned long difference = 0;
  for (int i = 0; i < FQ_NUMBER_OF_LIMBS * 2; i++) {
    unsigned long sum = left[i] + right[i] + difference;
    difference = sum < left[i] ? 1 : 0;
    result[i] = sum;
  }
}

void reduce(unsigned long *result, unsigned long *product, unsigned long *temp,
            unsigned long *reduced1, fq_mul_helper mulAndAddHelper) {
  multiplyAndModReduce(temp, product, mulAndAddHelper);
  mul(reduced1, temp, PRIME, mulAndAddHelper);
  addLong(reduced1, product, reduced1);
  // Shift right 384 bits, here comes the advance of not our chosen reducer.
  // As the shift is simply the upper 6 limbs.
  for (int i = 6, j = 0; i < 2 * FQ_NUMBER_OF_LIMBS; i++, j++) {
    result[j] = reduced1[i];
  }
  // std::copy(reduced1 + 6, reduced1 + 12, result);
  if (compareValues(result, PRIME) >= 0) {
    sub(result, result, PRIME);
  }
  fq_helper_free(temp);
}

Fq Fq::operator*(const Fq &rhs) {
  auto *interRes = (unsigned long *)malloc(FQ_BYTES * 2);
  auto *temp = (unsigned long *)malloc(FQ_BYTES * 2);
  auto *reduced1 = (unsigned long *)malloc(FQ_BYTES * 2);
  auto *result = (unsigned long *)(malloc(FQ_BYTES));
  initializePointerArray(interRes, 2);
  initializePointerArray(temp, 2);
  initializePointerArray(reduced1, 2);
  initializePointerArray(result, 1);
  fq_mul_helper mulAndAddHelper;
  fq_helper_new(mulAndAddHelper);
  mul(interRes, this->value, rhs.value, mulAndAddHelper);
  reduce(result, interRes, temp, reduced1, mulAndAddHelper);
  std::free(interRes);
  std::free(reduced1);
  std::free(temp);
  fq_helper_free(mulAndAddHelper);
  return Fq(result);
}

bool Fq::operator==(const Fq &rhs) const {
  return compareValues(this->value, rhs.value) == 0;
}

Fq::Fq(const unsigned long *limbs)
    : value(const_cast<unsigned long *>(limbs)) {}

std::string Fq::toString() const {
  // Simply converting the limbs back into mpz_t as toString
  // is only used for debugging.
  mpz_t toString;
  mpz_init(toString);
  mpz_import(toString, 1, -1, FQ_BYTES, -1, 0, this->value);
  convertOutMontgomery(toString);
  auto *stringPointer = mpz_get_str(nullptr, 10, toString);
  mpz_clear(toString);
  return stringPointer;
}

/**
 * 	****DOES NOT WORK****
 *	Returns a byte array with most least word first.
 *
 * @return
 */
unsigned char *Fq::serialize() const {
  auto *arr = (unsigned char *)malloc(FQ_BYTES);
  for (int j = 0; j < FQ_NUMBER_OF_LIMBS; j++) {
    for (int i = 0; i < 8; i++) {
      arr[i + (j * 8)] =
          (((unsigned long)this->value[j]) >> (56 - (8 * i))) & 0xFFu;
    }
  }
  return arr;
}
Fq::~Fq() { std::free(this->value); }
