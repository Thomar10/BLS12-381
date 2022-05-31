#include "TestDependencies.h"

TEST(FqTest2, PositiveNos)
{
    BigInt a_big = BigInt(10);
    FqBig a0 = FqBig(a_big);
    BigInt b_big = BigInt(20);
    FqBig a1 = FqBig(b_big);
    Fq2 fq2 = Fq2(a0, a1);

    BigInt a_big2 = BigInt(20);
    FqBig a02 = FqBig(a_big);
    BigInt b_big2 = BigInt(30);
    FqBig a12 = FqBig(b_big);
    Fq2 fq22 = Fq2(a02, a12);
    ASSERT_EQ(fq2 + fq22, Fq2(FqBig(a_big + a_big2), FqBig(b_big + b_big2)));
}

TEST(FqTest2, NegativeNos)
{
    //ASSERT_EQ(-1.0, squareRoot(-0.0));
    //ASSERT_EQ(-1.0, squareRoot(-0.2));
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}