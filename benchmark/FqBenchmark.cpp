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

static void FqAddSmart(benchmark::State &state) {
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
        aa.addSmart(bb);
    }
}
static void FqAddSmart3(benchmark::State &state) {
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
        aa.addSmart3(bb);
    }
}

static void FqAddSmart4(benchmark::State &state) {
    // Perform setup here
    fq a, b, c;
    fq_new(a);
    fq_new(b);
    fq_new(c);
    fq_random(a);
    fq_random(b);
    for (auto _: state) {
        add_something(c, a, b);
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
BENCHMARK(FqAddSmart)->Iterations(100);
BENCHMARK(FqAddSmart3)->Iterations(100);
BENCHMARK(FqAddSmart4)->Iterations(100);
BENCHMARK(FqAddBig)->Iterations(100);
//BENCHMARK(FqSub)->Iterations(100);
//BENCHMARK(FqSubBig)->Iterations(100);
//BENCHMARK(FqMul)->Iterations(100);
//BENCHMARK(FqMulComba)->Iterations(100);
//BENCHMARK(FqMulBig)->Iterations(100);
BENCHMARK_MAIN();