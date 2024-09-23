#include <gtest/gtest.h> 

#include "../include/exceptions.h"
#include "../include/hex.h" 


TEST(empty_constructor, test)
{
    auto number = Hex();
    auto result = number.to_decimal();

    ASSERT_EQ(result, 0);
}

 
int main(int argc, char **argv) { 
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}