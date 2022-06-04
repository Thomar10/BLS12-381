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
			"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111",
			2);

	Fq someFq = Fq(aa);
	unsigned char* serialized = someFq.serialize();
	std::cout << sizeof(unsigned long) * 6 << std::endl;
	std::cout << "Fq limbs" << std::endl;
	//std::cout << std::bitset<64>(someFq.value[0]).to_string() << std::endl;
	for (int i = 0; i < 6; i++) {
		std::cout << std::bitset<64>(someFq.value[i]).to_string() << std::endl;
	}
	std::cout << "from bytes" << std::endl;
	for (int j = 0; j < 6; j++) {
		for (int i = 0; i<8; ++i) {
			std::cout << std::bitset<8>(serialized[i+(j*8)]).to_string();
		}
		std::cout << std::endl;
	}

	mpz_t aaback;
	mpz_init(aaback);
	mpz_import(aaback, 1, -1, 48, -1, 0, serialized);
	gmp_printf ("%s is an mpz %Zd\n", "here", aa);
	gmp_printf ("%s is an mpz %Zd\n", "here", aaback);
	Fq someFqBack = Fq(aaback);

	std::cout << someFq.toString() << std::endl;
	std::cout << someFqBack.toString() << std::endl;


	//ASSERT_EQ(-1.0, squareRoot(-0.0));
	//ASSERT_EQ(-1.0, squareRoot(-0.2));
}

TEST(FqTest, hej)  {
	mpz_t a, b, c, a2, b2;
	mpz_init(a);
	mpz_set_str(a, "1111111111111111111111111111111111111111111111111111111111111111111111111", 2);
	void* outRaw = malloc(sizeof(unsigned long)*6);
	mpz_export(outRaw, nullptr,
			-1, sizeof(unsigned long) * 6,
			-1, 0, a);
	auto* hej = static_cast<u_int64_t*>(outRaw);
	for (int i = 0; i<6; i++) {
		std::cout << std::bitset<64>(hej[i]).to_string() << std::endl;
	}
}

TEST(FqTest, AddSome) {
	mpz_t a, b, c, a2, b2;
	mpz_init(a);
	mpz_init(a2);
	mpz_init(b);
	mpz_init(b2);
	mpz_init(c);
	mpz_set_str(a,
			"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111",
			2);
	mpz_set_str(b,
			"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111",
			2);
	mpz_set_str(a2,
			"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111",
			2);
	mpz_set_str(b2,
			"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111",
			2);
	Fq aa = Fq(a);
	Fq bb = Fq(b);

	Fq cc = aa + bb;
	mpz_add(c, a2, b2);
	Fq ccc = Fq(c);
	std::cout << "true res " << std::endl;
	for (int i = 0; i < 6; i++) {
		std::cout << std::bitset<64>(ccc.value[i]).to_string() << std::endl;
	}
	std::cout << "my " << cc.toString() << std::endl;
	std::cout << "true " << Fq(c).toString() << std::endl;
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}