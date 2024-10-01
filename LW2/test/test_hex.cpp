#include <gtest/gtest.h> 

#include <exceptions.h>
#include <hex.h>


TEST(empty_constructor, test)
{
    auto number = Hex();
    auto result = number.to_decimal();

    ASSERT_EQ(result, 0);
}

TEST(string_constructor, test_empty_string)
{
    auto str = "";

    ASSERT_THROW(auto number = Hex(str), NoHexNumericException);
}

TEST(string_constructor, test_incorrect_string)
{
    auto str = "abclkjgedcs";

    ASSERT_THROW(auto number = Hex(str), NoHexNumericException);
}

TEST(string_constructor, test_simple_string)
{
    auto str = "102345";

    auto number = Hex(str);
    auto expected_result = 1057605;
    auto result = number.to_decimal();

    ASSERT_EQ(result, expected_result);
}

TEST(int_constructor, test)
{
    auto num = 123456789;

    auto number = Hex(num);
    auto result = number.to_decimal();

    ASSERT_EQ(result, num);
}

TEST(copy_constructor, test)
{
    auto num = 123456789;

    auto first_number = Hex(num);
    auto second_number = Hex(first_number);

    auto result = second_number.to_decimal();

    ASSERT_EQ(num, result);
}

TEST(move_constructor, test)
{
    auto num = 123456789;

    auto number = Hex(Hex(num));
    auto result = number.to_decimal();

    ASSERT_EQ(num, result);
}

TEST(assignment_operator, test)
{
    auto num = 123456789;

    auto first_number = Hex();
    auto second_number = Hex(num);

    first_number = second_number;
    auto result = first_number.to_decimal();

    ASSERT_EQ(num, result);
}

TEST(move_assignment_operator, test)
{
    auto num = 123456789;

    auto number = Hex();
    number = Hex(num);
    auto result = number.to_decimal();

    ASSERT_EQ(num, result);
}

TEST(destructor, test) 
{
    auto num = 123456789;
    
    auto *number = new Hex(num);
    auto result = number->to_decimal();

    ASSERT_EQ(result, num);

    delete number;
}

TEST(to_decimal, test_simple_number) 
{
    auto num = "62737ad";
    auto expected_result = 103233453;

    auto number = Hex(num);
    auto result = number.to_decimal();

    ASSERT_EQ(result, expected_result);
}

TEST(to_decimal, test_too_big_number) 
{
    auto num = "abcdefabcdefabcdef2634758";

    auto number = Hex(num);

    ASSERT_THROW(number.to_decimal(), TooBigNumberException);
}

TEST(to_string, test_too_big_number) 
{
    auto num = "123456789ABC";

    auto number = Hex(num);

    auto result = number.to_string();
    
    ASSERT_EQ(result, num);
}

TEST(plus_operator, test) 
{
    auto first_num = 123;
    auto second_num = 321;
    auto expected_result = 444;

    auto first_number = Hex(first_num);
    auto second_number = Hex(second_num);

    auto result_number = first_number + second_number;
    auto result = result_number.to_decimal();

    ASSERT_EQ(result, expected_result);
}

TEST(minus_operator, test) 
{
    auto first_num = 123;
    auto second_num = 321;
    auto expected_result = 198;

    auto first_number = Hex(first_num);
    auto second_number = Hex(second_num);

    auto result_number = second_number - first_number;
    auto result = result_number.to_decimal();

    ASSERT_EQ(result, expected_result);
    ASSERT_THROW(first_number - second_number, ResultIsNegativeException);
}

TEST(more_operator, test) 
{
    auto first_num = 123;
    auto second_num = 321;

    auto first_number = Hex(first_num);
    auto second_number = Hex(second_num);

    ASSERT_TRUE(second_number > first_number);
    ASSERT_FALSE(first_number > second_number);
}

TEST(less_operator, test) 
{
    auto first_num = 123;
    auto second_num = 321;

    auto first_number = Hex(first_num);
    auto second_number = Hex(second_num);

    ASSERT_FALSE(second_number < first_number);
    ASSERT_TRUE(first_number < second_number);
}


TEST(more_equal_operator, test) 
{
    auto first_num = 123;
    auto first_num_1 = 123;
    auto second_num = 321;

    auto first_number = Hex(first_num);
    auto first_number_1 = Hex(first_num_1);
    auto second_number = Hex(second_num);

    ASSERT_TRUE(second_number >= first_number);
    ASSERT_FALSE(first_number >= second_number);
    ASSERT_TRUE(first_number >= first_number_1);
}
 
TEST(less_equal_operator, test) 
{
    auto first_num = 123;
    auto first_num_1 = 123;
    auto second_num = 321;

    auto first_number = Hex(first_num);
    auto first_number_1 = Hex(first_num_1);
    auto second_number = Hex(second_num);

    ASSERT_FALSE(second_number <= first_number);
    ASSERT_TRUE(first_number <= second_number);
    ASSERT_TRUE(first_number <= first_number_1);
}


TEST(equal_operator, test) 
{
    auto first_num = 123;
    auto first_num_1 = 123;
    auto second_num = 321;

    auto first_number = Hex(first_num);
    auto first_number_1 = Hex(first_num_1);
    auto second_number = Hex(second_num);

    ASSERT_FALSE(second_number == first_number);
    ASSERT_FALSE(first_number == second_number);
    ASSERT_TRUE(first_number == first_number_1);
}

TEST(not_equal_operator, test) 
{
    auto first_num = 123;
    auto first_num_1 = 123;
    auto second_num = 321;

    auto first_number = Hex(first_num);
    auto first_number_1 = Hex(first_num_1);
    auto second_number = Hex(second_num);

    ASSERT_TRUE(second_number != first_number);
    ASSERT_TRUE(first_number != second_number);
    ASSERT_FALSE(first_number != first_number_1);
}

TEST(print, test)
{
    auto str = "ABCDE";
    auto number = Hex(str);

    testing::internal::CaptureStdout();
    std::cout << number;
    auto output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(str, output);
}

int main(int argc, char **argv) { 
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}