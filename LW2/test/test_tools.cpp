#include <gtest/gtest.h> 

#include <exceptions.h>
#include <tools.h>

TEST(get_hex_numeric, test)
{
    auto correct_numeric = 15;
    auto expected_result = 'F';
    auto incorrect_numeric = 333;
    auto result = get_hex_numeric(correct_numeric);

    ASSERT_EQ(result, expected_result);
    ASSERT_THROW(get_hex_numeric(incorrect_numeric), NoHexNumericException);
}

TEST(get_decimal_numeric, test)
{
    auto correct_numeric = 'A';
    auto expected_result = 10;
    auto incorrect_numeric = 'S';
    auto result = get_decimal_numeric(correct_numeric);

    ASSERT_EQ(result, expected_result);
    ASSERT_THROW(get_decimal_numeric(incorrect_numeric), NoHexNumericException);
}

TEST(get_numeric, test)
{
    auto correct_numeric = 'b';
    auto expected_result = 'B';
    auto incorrect_numeric = 'l';
    auto result = get_numeric(correct_numeric);

    ASSERT_EQ(result, expected_result);
    ASSERT_THROW(get_decimal_numeric(incorrect_numeric), NoHexNumericException);
}

int main(int argc, char **argv) { 
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}