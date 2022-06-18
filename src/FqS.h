//
// Created by tlux- on 18-06-2022.
//

#ifndef BLS12_381_FQS_H
#define BLS12_381_FQS_H
#define some_align
#define FQ_NUMBER_OF_LIMBS 6
#define fq_new(A)            /* empty */
#define fp_free(A)            /* empty */
typedef some_align unsigned long fq[FQ_NUMBER_OF_LIMBS * 2];
const fq PRIME_FQ = {13402431016077863595UL, 2210141511517208575UL, 7435674573564081700UL,
                    7239337960414712511UL, 5412103778470702295UL, 1873798617647539866UL};
void add(fq result, fq a, fq b);
void sub(fq result, fq a, fq b);
void mul(fq result, fq a, fq b);
int cmp(const fq left, const fq right);
void fq_random(fq a);
#endif //BLS12_381_FQS_H
