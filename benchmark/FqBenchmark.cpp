//
// Created by tlux- on 30-05-2022.
//
#include <benchmark/benchmark.h>
#include <iostream>
#include "../src/FqBig.h"
#include "../src/Fq.h"
#include "../src/FqS.h"

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

static void FqAddHeap(benchmark::State &state) {
    // Perform setup here
    fq a, b, c;
    fq_new(a);
    fq_new(b);
    fq_new(c);
    fq_random(a);
    fq_random(b);
    for (auto _: state) {
        add(c, a, b);
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

static void FqSubHeap(benchmark::State &state) {
    // Perform setup here
    fq a, b, c;
    fq_new(a);
    fq_new(b);
    fq_new(c);
    fq_random(a);
    fq_random(b);
    for (auto _: state) {
        sub(c, a, b);
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

static void FqMulHeap(benchmark::State &state) {
    // Perform setup here
    fq a, b, c;
    fq_new(a);
    fq_new(b);
    fq_new(c);
    fq_random(a);
    fq_random(b);
    for (auto _: state) {
        mul(c, a, b);
    }
}

static void FqMulComba(benchmark::State &state) {
    mpz_t a, b;
    mpz_inits(a, b, nullptr);
    gmp_randstate_t rstate;
    gmp_randinit_default(rstate);
    mpz_rrandomb(a, rstate, 380);
    mpz_rrandomb(b, rstate, 380);
    auto aa = Fq(a);
    auto bb = Fq(b);
    for (auto _: state) {
        aa.multiplyComba(bb);
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
BENCHMARK(FqAdd)->Iterations(100);
BENCHMARK(FqAddHeap)->Iterations(100);
BENCHMARK(FqAddBig)->Iterations(100);
BENCHMARK(FqSub)->Iterations(100);
BENCHMARK(FqSubHeap)->Iterations(100);
BENCHMARK(FqSubBig)->Iterations(100);
BENCHMARK(FqMul)->Iterations(100);
BENCHMARK(FqMulHeap)->Iterations(100);
//BENCHMARK(FqMulComba)->Iterations(100);
BENCHMARK(FqMulBig)->Iterations(100);
BENCHMARK_MAIN();