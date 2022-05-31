#include <bits/stdc++.h>
#include <gmpxx.h>
#include "FqBig.h"
using namespace std;

// Function to find a random
// number between 0 or 1
int findRandom()
{
    // Generate the random number
    int num = ((int)rand() % 2);

    // Return the generated number
    return num;
}

// Function to generate a random
// binary string of length N
string generateBinaryString(int N)
{
//    srand(time(nullptr));

    // Stores the empty string
    string S;

    // Iterate over the range [0, N - 1]
    for (int i = 0; i < N; i++) {

        // Store the random number
        int x = findRandom();

        // Append it to the string
        S += to_string(x);
    }

    // Print the resulting string
    cout << S << endl;

    return S;
}

// Driver Code
int main()
{
//    int N = 7;
//    string hmm = generateBinaryString(N);
//    string hmm2 = generateBinaryString(N);
//    BigInt bigNumber = BigInt(hmm);
//    BigInt bigNumber2 = BigInt(hmm);
//    BigInt res = bigNumber + bigNumber2;
//    cout << bitset<20>(hmm)<< endl;
//    mpz_t sum;
//    mpz_init(sum);
//    mpz_set_str(sum, "100", 10);
//    gmp_printf ("%s is an mpz %Zd\n", "here", sum);
//    mpz_t sum2;
//    mpz_init(sum2);
//    mpz_set_str(sum2, "100", 10);
//    mpz_add(sum, sum, sum2);
//    gmp_printf ("%s is an mpz %Zd\n", "here", sum);
//    gmp_printf ("%s is an mpz %Zd\n", "here", sum2);

    mpz_t a_big, b_big, res;
    mpz_init(a_big);
    mpz_init(b_big);
    mpz_init(res);
    mpz_set_str(a_big, "100", 10);
    mpz_set_str(b_big, "100", 10);
    Fq a = Fq(a_big);
    Fq b = Fq(b_big);
    gmp_printf ("%s is an mpz %Zd\n", "here", a.value);
    mpz_add(res, a_big, b_big);
//    gmp_randstate_t rstate;
//    mpz_t randomNumber;
//    mpz_init(randomNumber);
//    auto size = mp_bitcnt_t(2);
//    gmp_randinit_default (rstate);
//    mpz_rrandomb(randomNumber, rstate, 2);
////    mpz_random(randomNumber, 1L);
//    gmp_printf ("%s is an mpz %Zd\n", "here", randomNumber);
    return 0;
}