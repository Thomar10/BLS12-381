#include "TestDependencies.h"


mpz_class PRIME_TEST("4002409555221667393417789825735904156556882819939007885332058136124031650490837864442687629129015664037894272559787");

TEST(FqTest, PositiveNos)
{
//    gmp_printf ("%s is an mpz %Zd\n", "here", this->value);

    mpz_class hej = 10;
    mpz_t a_big, aa, b_big, res;
    mpz_init(a_big);
    mpz_init(b_big);
    mpz_init(res);
    mpz_init(aa);
    mpz_set_str(aa, "100", 10);
    mpz_set_str(a_big, "100", 10);
    mpz_set_str(b_big, "100", 10);
    Fq a = Fq(aa);
    Fq b = Fq(b_big);
    mpz_add(res, a_big, b_big);
    mpz_mod(res, res, PRIME_TEST.get_mpz_t());
    ASSERT_EQ(a + b, Fq(res));

}

TEST(FqTest, NegativeNos)
{
    //ASSERT_EQ(-1.0, squareRoot(-0.0));
    //ASSERT_EQ(-1.0, squareRoot(-0.2));
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}