
#include <gtest/gtest.h>
#include "../src/Belts.h"

Belts belts[MAX_BELTS];
// bool function1(float a) {
//     return a > 5;
// }

// Test for function1
TEST(Function1Test, Test1) {
    belts[0].set_luggege(4242);
    //belts[0].get_luggege(4242);

    EXPECT_FALSE(true);
}

// TEST(Function2Test, Test2) {

//     EXPECT_FALSE(function1(6.77));

// }

// TEST(Function3Test, Test3) {

//     EXPECT_FALSE(function1(5.55f));

// }
// TEST(Function4Test, Test4) {

//     EXPECT_FALSE(function1(4.9999f));

// }
// TEST(Function5Test, Test5) {
//     EXPECT_TRUE(function1(10));
// }
// TEST(Function6Test, Test5) {
//     EXPECT_TRUE(function1(10866));
// }
// TEST(Function7Test, Test6) {
//     EXPECT_FALSE(function1(4.9999f));

// }


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}




// #include "myclass.h"

// // Test fixture for MyClass
// class MyClassTest : public ::testing::Test {
// protected:
//     MyClass obj;
// };

// // Test for MyClass::myFunction
// TEST_F(MyClassTest, Test1) {
//     EXPECT_EQ(obj.myFunction(0), 0);
//     EXPECT_EQ(obj.myFunction(5), 5);
//     EXPECT_EQ(obj.myFunction(10), 10);
// }
