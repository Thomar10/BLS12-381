#include <bitset>
#include "TestDependencies.h"
#include "../src/Fq.h"

mpz_class PRIME_TEST(
		"4002409555221667393417789825735904156556882819939007885332058136124031650490837864442687629129015664037894272559787");

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
	auto a = FqBig(aa);
	auto b = FqBig(b_big);
	mpz_add(res, a_big, b_big);
	mpz_mod(res, res, PRIME_TEST.get_mpz_t());
	ASSERT_EQ(a+b, FqBig(res));

}

TEST(FqTest, CanCreateFq)
{
	mpz_t aa;
	mpz_init(aa);
	//mpz_set_str(aa, "1111111111111111111111111111111111111111111111111111111111111111", 2);
	mpz_set_str(aa,
			"111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111",
			2);

	Fq someFq = Fq(aa);
	std::cout << "Fq limbs" << std::endl;
	//std::cout << std::bitset<64>(someFq.value[0]).to_string() << std::endl;
	//for (int i = 0; i < 6; i++) {
	//	std::cout << std::bitset<64>(someFq.value[i]).to_string() << std::endl;
	//}
	mpz_t aaback;
	mpz_init(aaback);
	//mpz_set_str(aaback, "1", 10);
	//import - rop, count, order, size, endian, nails, op
	mpz_import(aaback, 1, 0, sizeof(unsigned long) * 6, 0, 0, someFq.value);
	gmp_printf ("%s is an mpz %Zd\n", "here", aa);
	gmp_printf ("%s is an mpz %Zd\n", "here", aaback);
	Fq someFqBack = Fq(aaback);

	std::cout << someFq.toString() << std::endl;
	std::cout << someFqBack.toString() << std::endl;


	//ASSERT_EQ(-1.0, squareRoot(-0.0));
	//ASSERT_EQ(-1.0, squareRoot(-0.2));
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}