#include <bitset>
#include "TestDependencies.h"
#include "../src/Fq.h"

mpz_class PRIME_TEST(
		"4002409555221667393417789825735904156556882819939007885332058136124031650490837864442687629129015664037894272559787",
		10);
#define LOOP_COUNT 1000

TEST(FqTest, PositiveNos)
{
//    gmp_printf ("%s is an mpz %Zd\n", "here", this->value);
// std::cout << std::bitset<64>(someFqBack.value[i]).to_string() << std::endl;

	mpz_t a_big, aa, b_big, res;
	mpz_init(a_big);
	mpz_init(b_big);
	mpz_init(res);
	mpz_init(aa);
	mpz_set_str(aa, "100", 10);
	mpz_set_str(a_big, "100", 10);
	mpz_set_str(b_big, "100", 10);
	auto a = Fq(aa);
	auto b = Fq(b_big);
	mpz_add(res, a_big, b_big);
	mpz_mod(res, res, PRIME_TEST.get_mpz_t());
	ASSERT_EQ(a+b, Fq(res));
}

TEST(FqTest, limbMaker9000)
{
	mpz_t prime;
	mpz_init(prime);
	mpz_set_str(prime,
			"31812345668571394200522959936182890292651532161468729907319195075155855129916747767697203739041175453056836858347517",
			10);
	Fq fqPrime = Fq(prime);
	std::cout << "WOOOO" << std::endl;
	for (int i = 0; i<FQ_NUMBER_OF_LIMBS; i++) {
		std::cout << (unsigned long)(fqPrime.value[i]) << std::endl;
	}
}
TEST(FqTest, multiplyComba) {
    mpz_t a, b, c;
    mpz_inits(a, b, c, nullptr);
    gmp_randstate_t rstate;
    gmp_randinit_mt(rstate);
    for (int i = 0; i<LOOP_COUNT; i++) {
        mpz_urandomb(a, rstate, 380);
        mpz_urandomb(b, rstate, 380);
        Fq fqA = Fq(a);
        Fq fqB = Fq(b);
        mpz_mul(c, a, b);
        mpz_mod(c, c, PRIME_TEST.get_mpz_t());
        Fq cc = fqA.multiplyComba(fqB);
        ASSERT_EQ(cc, Fq(c));
    }
}


TEST(FqTest, multiply) {
	mpz_t a, b, c;
	mpz_inits(a, b, c, nullptr);
	gmp_randstate_t rstate;
	gmp_randinit_mt(rstate);
	for (int i = 0; i<LOOP_COUNT; i++) {
		mpz_urandomb(a, rstate, 380);
		mpz_urandomb(b, rstate, 380);
		Fq fqA = Fq(a);
		Fq fqB = Fq(b);
		mpz_mul(c, a, b);
		mpz_mod(c, c, PRIME_TEST.get_mpz_t());
		Fq cc = fqA*fqB;
		ASSERT_EQ(cc, Fq(c));
	}
}

TEST(FqTest, Add)
{
	mpz_t a, b, c;
	mpz_inits(a, b, c, nullptr);
	gmp_randstate_t rstate;
	gmp_randinit_mt(rstate);
	for (int i = 0; i<LOOP_COUNT; i++) {
		mpz_urandomb(a, rstate, 380);
		mpz_urandomb(b, rstate, 380);
		Fq fqA = Fq(a);
		Fq fqB = Fq(b);
		mpz_add(c, a, b);
		mpz_mod(c, c, PRIME_TEST.get_mpz_t());
		Fq cc = fqA+fqB;
		Fq ccc = Fq(c);
		ASSERT_EQ(cc, ccc);
	}
}

TEST(FqTest, SubNegative)
{
	mpz_t a, b, c;
	mpz_inits(a, b, c, nullptr);
	gmp_randstate_t rstate;
	gmp_randinit_mt(rstate);
	for (int i = 0; i<LOOP_COUNT; i++) {
		mpz_rrandomb(a, rstate, 370);
		mpz_rrandomb(b, rstate, 380);
		Fq fqA = Fq(a);
		Fq fqB = Fq(b);
		mpz_sub(c, a, b);
		mpz_add(c, c, PRIME_TEST.get_mpz_t());
		Fq cc = fqA-fqB;
		Fq ccc = Fq(c);
		ASSERT_EQ(cc, ccc);
	}
}
TEST(FqTest, SubEqual)
{
	mpz_t a, b, c;
	mpz_inits(a, b, c, nullptr);
	gmp_randstate_t rstate;
	gmp_randinit_mt(rstate);
	for (int i = 0; i<LOOP_COUNT; i++) {
		mpz_rrandomb(a, rstate, 380);
		mpz_rrandomb(b, rstate, 380);
		Fq fqA = Fq(a);
		Fq fqB = Fq(b);
		mpz_sub(c, a, b);
		if (mpz_cmp(a, b) < 0) {
			mpz_add(c, c, PRIME_TEST.get_mpz_t());
		}
		Fq cc = fqA-fqB;
		Fq ccc = Fq(c);
		ASSERT_EQ(cc, ccc);
	}
}
TEST(FqTest, SubNormal)
{
	mpz_t a, b, c;
	mpz_inits(a, b, c, nullptr);
	gmp_randstate_t rstate;
	gmp_randinit_mt(rstate);
	for (int i = 0; i<LOOP_COUNT; i++) {
		mpz_rrandomb(a, rstate, 380);
		mpz_rrandomb(b, rstate, 370);
		Fq fqA = Fq(a);
		Fq fqB = Fq(b);
		mpz_sub(c, a, b);
		Fq cc = fqA-fqB;
		Fq ccc = Fq(c);
		ASSERT_EQ(cc, ccc);
	}
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}