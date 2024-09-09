#include <gtest/gtest.h> 
#include "../include/solver.h" 
 
TEST(test_01, basic_test_set) 
{ 
ASSERT_TRUE(solver("Понедельник", 12) == 1); 
} 
 
int main(int argc, char **argv) { 
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}