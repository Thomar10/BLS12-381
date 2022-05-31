#include <bitset>
#include "TestDependencies.h"

mpz_class PRIME_TEST(
		"4002409555221667393417789825735904156556882819939007885332058136124031650490837864442687629129015664037894272559787");

TEST(FqTest, PositiveNos)
{
//    gmp_printf ("%s is an mpz %Zd\n", "here", this->value);


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
	mpz_set_str(aa, "2", 10);
	char *buff;
	char size = 8;
	int numb = 8 * size - 0;
	auto count = (mpz_sizeinbase(aa, 2) + numb - 1) / numb;
	void* p = malloc(count * size);
	int big_size = mpz_sizeinbase(aa, 2);
	buff = static_cast<char*>(calloc(1, big_size));
	//https://machinecognitis.github.io/Math.Gmp.Native/html/c9d371c8-8c16-77a3-2c47-8edae05276c5.htm
	mpz_export(buff, nullptr, 1, big_size, 1, 0, aa);
	mpz_export(p, nullptr, 1, big_size, 0, 0, aa);
	char* hmm;
	hmm = static_cast<char*>(p);
	std::cout << big_size << std::endl;
	auto hej = std::bitset<8>(buff[0]).to_string();
	auto hej1 = std::bitset<8>(buff[1]).to_string();
	std::cout << hej << std::endl;
	std::cout << hej1 << std::endl;
	std::cout << hmm << std::endl;
	std::cout << p << std::endl;
	int i = 0;
	free(buff);
	//ASSERT_EQ(-1.0, squareRoot(-0.0));
	//ASSERT_EQ(-1.0, squareRoot(-0.2));
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}