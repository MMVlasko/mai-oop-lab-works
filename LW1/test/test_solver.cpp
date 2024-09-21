#include <gtest/gtest.h> 
#include "../include/solver.h" 
 
TEST(test_01, basic_test_set) 
{ 
    bool result = solver("понедельник", 12);
    ASSERT_TRUE(result == 1); 
} 

TEST(test_02, basic_test_set) 
{ 
    bool result = solver("вторник", 96);
    ASSERT_TRUE(result == 1); 
} 

TEST(test_03, basic_test_set) 
{ 
    bool result = solver("вторник", 95);
    ASSERT_TRUE(result == 0); 
} 

TEST(test_04, basic_test_set) 
{ 
    bool result = solver("среда", 34);
    ASSERT_TRUE(result == 1); 
} 

TEST(test_05, basic_test_set) 
{ 
    bool result = solver("четверг", 0); 
    ASSERT_TRUE(result == 1); 
} 

TEST(test_06, basic_test_set) 
{ 
    bool result = solver("пятница", 888);
    ASSERT_TRUE(result == 1); 
} 

TEST(test_07, basic_test_set) 
{ 
    bool result = solver("пятница", 889);
    ASSERT_TRUE(result == 0); 
} 

TEST(test_08, basic_test_set) 
{ 
    bool result = solver("суббота", 56); 
    ASSERT_TRUE(result == 1); 
} 

TEST(test_09, basic_test_set) 
{ 
    bool result = solver("воскресенье", 666);
    ASSERT_TRUE(result == 1); 
} 

TEST(test_10, basic_test_set) 
{ 
    bool result = solver("воскресенье", -666);
    ASSERT_TRUE(result == 1); 
}

TEST(test_11, basic_test_set) 
{ 
    bool result = solver("абвгде", 777);
    ASSERT_TRUE(result == 0); 
} 
 
int main(int argc, char **argv) { 
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}