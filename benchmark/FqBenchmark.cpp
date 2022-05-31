//
// Created by tlux- on 30-05-2022.
//
#include <benchmark/benchmark.h>
#include <gmpxx.h>
#include <iostream>
#include "../src/FqBig.h"

static void FqAdd(benchmark::State &state) {
    // Perform setup here
    for (auto _: state) {
        // This code gets timed
        (2 + 2) % 100;
    }
}

static void FqAddBig(benchmark::State &state) {
    // Perform setup here
    mpz_t a, b;
    mpz_init_set_str(a, "2", 10);
    mpz_init_set_str(b, "2", 10);
    FqBig fqA = FqBig(a);
    FqBig fqB = FqBig(b);
    for (auto _: state) {
        // This code gets timed
        fqA + fqB;
    }
}
// Register the function as a benchmark
BENCHMARK(FqAdd);
BENCHMARK(FqAddBig);
BENCHMARK_MAIN();