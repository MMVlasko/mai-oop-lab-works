#include <gtest/gtest.h> 

#include <exceptions.h>
#include <array.h>
#include <complex>

TEST(empty_constructor, test) {
    auto expected_size = 0;
    auto array = Array<int>();

    ASSERT_EQ(array.size, expected_size);
}

TEST(init_list_constructor, test)
{
    auto expected_size = 4;
    auto init_list = {1, 1, 1, 1};
    auto array = Array(init_list);

    ASSERT_EQ(array.size, expected_size);

    int i = 0;
    for (const auto& elem : init_list) {
        ASSERT_EQ(*array[i], elem);
        ++i;
    }
}

TEST(index_operator, test_simple_array)
{
    auto init_list = {1};
    auto array = Array(init_list);

    ASSERT_EQ(*array[0], *init_list.begin());
    ASSERT_EQ(*array[-1], *init_list.begin());
    ASSERT_THROW(array[1], IndexOutOfRangeException);
}

TEST(index_operator, test_empty_array)
{
    auto array = Array<int>();
    ASSERT_THROW(array[0], IndexOutOfRangeException);
}

TEST(copy_constructor, test)
{
    auto init_list = {1, 2, 3, 4};
    auto array = Array(init_list);
    auto other_array = Array(array);

    ASSERT_EQ(other_array.size, array.size);

    for (int i = 0; i < array.size; ++i)
        ASSERT_EQ(*array[i], *other_array[i]);
}

TEST(move_constructor, test)
{
    auto expected_size = 4;
    auto init_list = {1, 2, 3, 4};
    auto array = Array(Array(init_list));

    ASSERT_EQ(array.size, expected_size);

    int i = 0;
    for (const auto& elem : init_list) {
        ASSERT_EQ(*array[i], elem);
        ++i;
    }
}

TEST(assignment_operator, test)
{
    auto first_init_list = {1, 2, 3, 4};
    auto first_array = Array(first_init_list);
    auto second_init_list = {5, 6, 7, 8, 9};
    auto second_array = Array(second_init_list);
    first_array = second_array;

    ASSERT_EQ(first_array.size, second_array.size);
    for (int i = 0; i < first_array.size; ++i)
        ASSERT_EQ(*first_array[i], *second_array[i]);
}

TEST(move_assignment_operator, test)
{
    auto first_init_list = {1, 2, 3, 4};
    auto second_init_list = {5, 6, 7, 8, 9};
    auto expected_size = 5;
    
    auto array = Array(first_init_list);
    array = Array(second_init_list);

    ASSERT_EQ(array.size, expected_size);
    
    int i = 0;
    for (const auto& elem : second_init_list) {
        ASSERT_EQ(*array[i], elem);
        ++i;
    }
}

TEST(remove, test_empty_array)
{
    auto array = Array<int>(); 

    ASSERT_THROW(array.remove(), ArrayIsEmptyException);
}
 
TEST(remove, test_simple_array)
{
    auto expected_size = 3;
    auto expected_number = 4;
    auto init_list = {1, 2, 3, expected_number};

    auto array = Array(init_list);
    auto element = array.remove();

    ASSERT_EQ(*element, expected_number);
    ASSERT_EQ(array.size, expected_size);
}

TEST(add, test) 
{
    auto expected_size = 1;
    auto element = 333;

    auto array = Array<int>();
    array.add(element);

    ASSERT_EQ(array.size, expected_size);
    ASSERT_EQ(*array[0], element);
}

TEST(equal_operator, test)
{
    auto init_list = {1, 2, 3, 4};

    auto first_array = Array(init_list);
    auto sec_array = Array(init_list);

    ASSERT_TRUE(first_array == sec_array);

    sec_array.remove();

    ASSERT_FALSE(first_array == sec_array);
}

TEST(not_equal_operator, test)
{
    auto init_list = {1, 2, 3, 4};

    auto first_array = Array(init_list);
    auto sec_array = Array(init_list);

    ASSERT_FALSE(first_array != sec_array);

    sec_array.remove();

    ASSERT_TRUE(first_array != sec_array);
}

TEST(insert, test_simple_array)
{
    auto insert_index = 1;
    auto first = 1;
    auto insert_number = 333;
    auto second = 2;

    auto first_init_list = {first, second};
    auto second_init_list = {first, insert_number, second};

    auto array = Array(first_init_list);
    auto new_array = Array(second_init_list);

    array.insert(insert_number, insert_index);

    ASSERT_TRUE(array == new_array);
}

TEST(insert, test_empty_array)
{
    auto insert_index = 0;
    auto insert_number = 1;
    auto init_list = {1};

    auto array = Array<int>();
    auto new_array = Array(init_list);

    array.insert(insert_number, insert_index);

    ASSERT_TRUE(array == new_array);
}

TEST(pop, test)
{
    auto expected_number = 2;
    auto init_list = {1, expected_number, 3, 4};
    auto expected_size = 3;
    
    auto array = Array(init_list);

    auto result = array.pop(1);

    ASSERT_EQ(array.size, expected_size);
    ASSERT_EQ(expected_number, *result);
    ASSERT_THROW(array.pop(3), IndexOutOfRangeException);
}

TEST(print, test)
{
    auto init_list = {1, 2, 3, 4};
    auto result = "[1, 2, 3, 4]";
    auto array = Array(init_list);

    testing::internal::CaptureStdout();
    std::cout << array;
    auto output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, result);
}
 
int main(int argc, char **argv) { 
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}