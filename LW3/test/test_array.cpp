#include <gtest/gtest.h> 

#include <exceptions.h>
#include <array.h>

TEST(empty_constructor, test)
{
    auto expected_size = 0;
    auto array = Array();

    ASSERT_EQ(array.size, expected_size);
}

TEST(string_constructor, test_empty_string)
{
    auto expected_size = 0;
    auto str = "";
    auto array = Array(str);

    ASSERT_EQ(array.size, expected_size);
}

TEST(string_constructor, test_simple_string)
{
    auto expected_size = 4;
    auto str = "abcd";
    auto array = Array(str);

    ASSERT_EQ(array.size, expected_size);

    for (int i = 0; i < array.size; ++i)
        ASSERT_EQ(array[i], str[i]);
}

TEST(index_operator, test_simple_array)
{
    auto str = "a";
    auto array = Array(str);

    ASSERT_EQ(array[0], str[0]);
    ASSERT_EQ(array[-1], str[0]);
    ASSERT_THROW(array[1], IndexOutOfRangeException);
}

TEST(index_operator, test_empty_array)
{
    auto str = "";
    auto array = Array(str);
    ASSERT_THROW(array[0], IndexOutOfRangeException);
}

TEST(copy_constructor, test)
{
    auto str = "abcd";
    auto array = Array(str);
    auto other_array = Array(array);

    ASSERT_EQ(other_array.size, array.size);

    for (int i = 0; i < array.size; ++i)
        ASSERT_EQ(array[i], other_array[i]);
}

TEST(move_constructor, test)
{
    auto expected_size = 4;
    auto str = "abcd";
    auto array = Array(Array(str));

    ASSERT_EQ(array.size, expected_size);

    for (int i = 0; i < array.size; ++i)
        ASSERT_EQ(array[i], str[i]);
}

TEST(assignment_operator, test)
{
    auto first_str = "abcd";
    auto sec_str = "efghij";
    auto first_array = Array(first_str);
    auto sec_array = Array(sec_str);

    first_array = sec_array;

    ASSERT_EQ(first_array.size, sec_array.size);
    for (int i = 0; i < first_array.size; ++i)
        ASSERT_EQ(first_array[i], sec_array[i]);
}

TEST(move_assignment_operator, test)
{
    auto expected_size = 6;
    auto first_str = "abcd";
    auto sec_str = "efghij";
    auto first_array = Array(first_str);
    first_array = Array(sec_str);

    ASSERT_TRUE(first_array.size == expected_size);
    for (int i = 0; i < first_array.size; ++i)
        ASSERT_EQ(first_array[i], sec_str[i]);
}

TEST(destructor, test) 
{
    auto str = "a";
    auto *array = new Array(str);

    ASSERT_EQ((*array)[0], str[0]);

    delete array;
}

TEST(remove, test_empty_array)
{
    auto array = Array(); 

    ASSERT_THROW(array.remove(), ArrayIsEmptyException);
}
 
TEST(remove, test_simple_array)
{
    auto expected_size = 3;
    auto expected_symbol = 'd';
    auto str = "abcd";

    auto array = Array(str); 
    auto element = array.remove();

    ASSERT_EQ(element, expected_symbol);
    ASSERT_EQ(array.size, expected_size);
}

TEST(add, test) 
{
    auto expected_size = 1;
    unsigned char element = 'f';

    auto array = Array();
    array.add(element);

    ASSERT_EQ(array.size, expected_size);
    ASSERT_EQ(array[0], element);
}

TEST(equal_operator, test)
{
    auto str = "abcd";

    auto first_array = Array(str);
    auto sec_array = Array(str);

    ASSERT_TRUE(first_array == sec_array);

    sec_array.remove();

    ASSERT_FALSE(first_array == sec_array);
}

TEST(not_equal_operator, test)
{
    auto str = "abcd";

    auto first_array = Array(str);
    auto sec_array = Array(str);

    ASSERT_FALSE(first_array != sec_array);

    sec_array.remove();

    ASSERT_TRUE(first_array != sec_array);
}

TEST(insert, test_simple_array)
{
    auto insert_index = 1;
    auto insert_symbol = 'b';
    auto first_str = "ac";
    auto sec_str = "abc";

    auto array = Array(first_str);
    auto new_array = Array(sec_str);

    array.insert(insert_symbol, insert_index);

    ASSERT_TRUE(array == new_array);
}

TEST(insert, test_empty_array)
{
    auto str = "a";
    auto insert_index = 0;
    auto insert_symbol = 'a';

    auto array = Array();
    auto new_array = Array(str);

    array.insert(insert_symbol, insert_index);

    ASSERT_TRUE(array == new_array);
}

TEST(pop, test)
{
    auto str = "abcd";
    auto expected_symbol = 'b';
    auto expected_size = 3;
    
    auto array = Array(str);

    auto result = array.pop(1);

    ASSERT_EQ(array.size, expected_size);
    ASSERT_EQ(expected_symbol, result);
    ASSERT_THROW(array.pop(3), IndexOutOfRangeException);
}

TEST(to_string, test)
{
    auto str = "abcde";
    auto array = Array(str);
    
    auto result = array.to_string();

    ASSERT_EQ(str, result);
}

TEST(print, test)
{
    auto str = "abcde";
    auto result = "[a, b, c, d, e]\n";
    auto array = Array(str);

    testing::internal::CaptureStdout();
    std::cout << array;
    auto output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, result);
}
 
int main(int argc, char **argv) { 
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}