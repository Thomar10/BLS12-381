//
// Created by tlux- on 18-06-2022.
//
#include <random>
#include "FqS.h"

unsigned long sub_limbs(unsigned long *result, const unsigned long *left, const unsigned long *right) {
    int i;
    unsigned long carry, r0, diff;

    carry = 0;
    for (i = 0; i < FQ_NUMBER_OF_LIMBS; i++, left++, right++, result++) {
        diff = (*left) - (*right);
        r0 = diff - carry;
        carry = ((*left) < (*right)) || (carry && !diff);
        (*result) = r0;
    }
    return carry;
}

void add_limbs(unsigned long *result, const unsigned long *left, const unsigned long *right) {
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


void add(fq result, fq left, fq right) {
    add_limbs(result, left, right);
    if (cmp(result, PRIME_FQ) > 0) {
        sub_limbs(result, left, right);
    }
}

void sub(fq result, fq left, fq right) {
    unsigned long borrow = sub_limbs(result, left, right);
    if (borrow != 0) {
        add_limbs(result, result, PRIME_FQ);
    }
}

void mul(fq result, fq left, fq right) {

}

void fq_random(fq a) {
    std::random_device rd;     //Get a random seed from the OS entropy device, or whatever
    std::mt19937_64 eng(rd()); //Use the 64-bit Mersenne Twister 19937 generator
    //and seed it with entropy.

    //Define the distribution, by default it goes from 0 to MAX(unsigned long long)
    //or what have you.
    std::uniform_int_distribution<unsigned long long> distr;

    //Generate random numbers
    for(int n=0; n<FQ_NUMBER_OF_LIMBS; a++, n++) {
        *a =  distr(eng);
    }
}

int cmp(const fq left, const unsigned long* right) {
    for (int i = FQ_NUMBER_OF_LIMBS - 1; i >= 0; i--) {
        if (left[i] < right[i]) {
            return -1;
        } else if (left[i] > right[i]) {
            return 1;
        }
    }
    return 0;
}