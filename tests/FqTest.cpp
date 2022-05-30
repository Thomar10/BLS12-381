#include "TestDependencies.h"

const BigInt PRIME = BigInt(
        "4002409555221667393417789825735904156556882819939007885332058136124031650490837864442687629129015664037894272559787");

TEST(FqTest, PositiveNos)
{
    BigInt a_big = BigInt(10);
    Fq a = Fq(a_big);
    BigInt b_big = BigInt(20);
    Fq b = Fq(b_big);
    ASSERT_EQ(a + b, Fq((a_big + b_big) % PRIME));
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