#include <gtest/gtest.h> 

#include <exceptions.h>
#include <array.h>

TEST(empty_constructor, test)
{
    auto array = Array();

    ASSERT_EQ(array.size, 0);
}

TEST(string_constructor, test_empty_string)
{
    auto str = "";
    auto array = Array(str);

    ASSERT_EQ(array.size, 0);
}

TEST(string_constructor, test_simple_string)
{
    auto str = "abcd";
    auto array = Array(str);

    ASSERT_EQ(array.size, 4);

    for (int i = 0; i < 4; ++i)
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
    auto str = "abcd";
    auto array = Array(Array(str));

    ASSERT_EQ(array.size, 4);

    for (int i = 0; i < 4; ++i)
        ASSERT_EQ(array[i], str[i]);
}

TEST(equal_operator, test)
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

TEST(move_equal_operator, test)
{
    auto first_str = "abcd";
    auto sec_str = "efghij";
    auto first_array = Array(first_str);
    first_array = Array(sec_str);

    ASSERT_TRUE(first_array.size == 6);
    for (int i = 0; i < 6; ++i)
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
    auto str = "abcd";
    auto array = Array(str); 

    auto element = array.remove();

    ASSERT_EQ(element, 'd');
    ASSERT_EQ(array.size, 3);
}

TEST(add, test) 
{
    auto array = Array();
    unsigned char element = 'f';

    array.add(element);

    ASSERT_EQ(array.size, 1);
    ASSERT_EQ(array[0], element);
}

TEST(eq_operator, test)
{
    auto str = "abcd";
    auto first_array = Array(str);
    auto sec_array = Array(str);

    ASSERT_TRUE(first_array == sec_array);

    sec_array.remove();

    ASSERT_FALSE(first_array == sec_array);
}

TEST(insert, test_simple_array)
{
    auto first_str = "ac";
    auto sec_str = "abc";
    auto array = Array(first_str);
    auto new_array = Array(sec_str);

    array.insert('b', 1);

    ASSERT_TRUE(array == new_array);
}

TEST(insert, test_empty_array)
{
    auto str = "a";
    auto array = Array();
    auto new_array = Array(str);

    array.insert('a', 0);

    ASSERT_TRUE(array == new_array);
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