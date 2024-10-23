#include <gtest/gtest.h> 

#include <tools.h>

TEST(sort_points, test)
{
    auto first_point = Point(1.0, 1.0);
    auto second_point = Point(2.0, 2.0);
    auto third_point = Point(1.0, 2.0);
    auto fourth_point = Point(2.0, 1.0);

    auto array = Array({first_point, second_point, third_point, fourth_point});
    auto expected_result = Array({first_point, fourth_point, second_point, third_point});
    
    auto result = sort_points(array);
    
    ASSERT_TRUE(*result == expected_result);
}

TEST(get_square, test)
{
    auto first_point = Point(1.0, 3.0);
    auto second_point = Point(1.0, 1.0);
    auto third_point = Point(5.0, 1.0);
    auto fourth_point = Point(5.0, 3.0);

    auto expected_result = 8.;
    auto array = Array({second_point, third_point, fourth_point, first_point});
    
    auto result = get_square(array);
    
    ASSERT_EQ(result, expected_result);
}

TEST(input, test)
{
    std::istringstream input("abcde");
    std::streambuf* original_cin = std::cin.rdbuf();

    std::cin.rdbuf(input.rdbuf());

    double value;
    std::cin >> value;
    ASSERT_THROW(check_cin(), BadInputDataException);

    std::cin.rdbuf(original_cin); 
}

int main(int argc, char **argv) { 
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}