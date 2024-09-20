#include <gtest/gtest.h> 
#include "../include/solver.h" 
 
TEST(test_01, basic_test_set) 
{ 
ASSERT_TRUE(solver("понедельник", 12) == 1); 
} 

TEST(test_02, basic_test_set) 
{ 
ASSERT_TRUE(solver("вторник", 96) == 1); 
} 

TEST(test_03, basic_test_set) 
{ 
ASSERT_TRUE(solver("вторник", 95) == 0); 
} 

TEST(test_04, basic_test_set) 
{ 
ASSERT_TRUE(solver("среда", 34) == 1); 
} 

TEST(test_05, basic_test_set) 
{ 
ASSERT_TRUE(solver("четверг", 0) == 1); 
} 

TEST(test_06, basic_test_set) 
{ 
ASSERT_TRUE(solver("пятница", 888) == 1); 
} 

TEST(test_07, basic_test_set) 
{ 
ASSERT_TRUE(solver("пятница", 889) == 0); 
} 

TEST(test_08, basic_test_set) 
{ 
ASSERT_TRUE(solver("суббота", 56) == 1); 
} 

TEST(test_09, basic_test_set) 
{ 
ASSERT_TRUE(solver("воскресенье", 666) == 1); 
} 

TEST(test_10, basic_test_set) 
{ 
ASSERT_TRUE(solver("воскресенье", -666) == 1); 
}

TEST(test_11, basic_test_set) 
{ 
ASSERT_TRUE(solver("абвгде", 777) == 0); 
} 
 
int main(int argc, char **argv) { 
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}