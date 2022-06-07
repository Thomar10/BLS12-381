//
// Created by tlux- on 30-05-2022.
//
#include <benchmark/benchmark.h>
#include <iostream>
#include "../src/FqBig.h"
#include "../src/Fq.h"

static void FqAdd(benchmark::State &state) {
    // Perform setup here
	mpz_t a, b;
	mpz_inits(a, b, nullptr);
	gmp_randstate_t rstate;
	gmp_randinit_default(rstate);
	mpz_rrandomb(a, rstate, 380);
	mpz_rrandomb(b, rstate, 380);
	Fq aa = Fq(a);
	Fq bb = Fq(b);
    for (auto _: state) {
		aa + bb;
    }
}

static void FqAddBig(benchmark::State &state) {
	mpz_t a, b;
	mpz_inits(a, b, nullptr);
	gmp_randstate_t rstate;
	gmp_randinit_default(rstate);
	mpz_rrandomb(a, rstate, 380);
	mpz_rrandomb(b, rstate, 380);
	auto aa = FqBig(a);
	auto bb = FqBig(b);
    for (auto _: state) {
        aa + bb;
    }
}

static void FqSub(benchmark::State &state) {
	mpz_t a, b;
	mpz_inits(a, b, nullptr);
	gmp_randstate_t rstate;
	gmp_randinit_default(rstate);
	mpz_rrandomb(a, rstate, 380);
	mpz_rrandomb(b, rstate, 380);
	Fq aa = Fq(a);
	Fq bb = Fq(b);
	for (auto _: state) {
		aa - bb;
	}
}

static void FqSubBig(benchmark::State &state) {
	mpz_t a, b;
	mpz_inits(a, b, nullptr);
	gmp_randstate_t rstate;
	gmp_randinit_default(rstate);
	mpz_rrandomb(a, rstate, 380);
	mpz_rrandomb(b, rstate, 380);
	auto aa = FqBig(a);
	auto bb = FqBig(b);
	for (auto _: state) {
		aa - bb;
	}
}

static void FqMul(benchmark::State &state) {
	mpz_t a, b;
	mpz_inits(a, b, nullptr);
	gmp_randstate_t rstate;
	gmp_randinit_default(rstate);
	mpz_rrandomb(a, rstate, 380);
	mpz_rrandomb(b, rstate, 380);
	Fq aa = Fq(a);
	Fq bb = Fq(b);
	for (auto _: state) {
		aa * bb;
	}
}

static void FqMulBig(benchmark::State &state) {
	mpz_t a, b;
	mpz_inits(a, b, nullptr);
	gmp_randstate_t rstate;
	gmp_randinit_default(rstate);
	mpz_rrandomb(a, rstate, 380);
	mpz_rrandomb(b, rstate, 380);
	auto aa = FqBig(a);
	auto bb = FqBig(b);
	for (auto _: state) {
		aa * bb;
	}
}


// Register the function as a benchmark
BENCHMARK(FqAdd);
BENCHMARK(FqAddBig);
BENCHMARK(FqSub);
BENCHMARK(FqSubBig);
BENCHMARK(FqMul);
BENCHMARK(FqMulBig);
BENCHMARK_MAIN();