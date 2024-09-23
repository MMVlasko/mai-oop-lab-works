#include <gtest/gtest.h> 
#include "../include/solver.h" 
 
TEST(test_01, basic_test_set) 
{
    std::string day = "понедельник";
    int number = 12;
    bool result = solver(day, number);
    ASSERT_TRUE(result == 1); 
} 

TEST(test_02, basic_test_set) 
{ 
    std::string day = "вторник";
    int number = 96;
    bool result = solver(day, number);
    ASSERT_TRUE(result == 1); 
} 

TEST(test_03, basic_test_set) 
{ 
    std::string day = "вторник";
    int number = 95;
    bool result = solver(day, number);
    ASSERT_TRUE(result == 0); 
} 

TEST(test_04, basic_test_set) 
{ 
    std::string day = "среда";
    int number = 34;
    bool result = solver(day, number);
    ASSERT_TRUE(result == 1); 
} 

TEST(test_05, basic_test_set) 
{ 
    std::string day = "четверг";
    int number = 0;
    bool result = solver(day, number);
    ASSERT_TRUE(result == 1); 
} 

TEST(test_06, basic_test_set) 
{ 
    std::string day = "пятница";
    int number = 888;
    bool result = solver(day, number);
    ASSERT_TRUE(result == 1); 
} 

TEST(test_07, basic_test_set) 
{ 
    std::string day = "пятница";
    int number = 889;
    bool result = solver(day, number);
    ASSERT_TRUE(result == 0); 
} 

TEST(test_08, basic_test_set) 
{ 
    std::string day = "суббота";
    int number = 56;
    bool result = solver(day, number);
    ASSERT_TRUE(result == 1); 
} 

TEST(test_09, basic_test_set) 
{ 
    std::string day = "воскресенье";
    int number = 666;
    bool result = solver(day, number);
    ASSERT_TRUE(result == 1); 
} 

TEST(test_10, basic_test_set) 
{ 
    std::string day = "воскресенье";
    int number = -666;
    bool result = solver(day, number);
    ASSERT_TRUE(result == 1); 
}

TEST(test_11, basic_test_set) 
{ 
    std::string day = "абвгде";
    int number = 777;
    bool result = solver(day, number);
    ASSERT_TRUE(result == 0); 
} 
 
int main(int argc, char **argv) { 
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}