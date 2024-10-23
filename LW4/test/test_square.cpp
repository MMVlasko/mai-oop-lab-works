#include <gtest/gtest.h> 
#include <iostream>
#include <sstream>

#include <exceptions.h>
#include <array.h>
#include <square.h>
#include <point.h>

TEST(init_list_constructor, test)
{
    auto first_point = Point(1.0, 1.0);
    auto second_point = Point(2.0, 2.0);
    auto third_point = Point(1.0, 2.0);
    auto fourth_point = Point(2.0, 1.0);

    auto bad_point = Point(1000.0, 1000.0);

    auto expected_result = Array({first_point, fourth_point, second_point, third_point});
    auto square = Square({first_point, second_point, third_point, fourth_point});

    auto result = square.get_crds_array();
    ASSERT_TRUE(*result == expected_result);
    ASSERT_THROW(Square({first_point, second_point, third_point, bad_point}), BadInputDataException);
}

TEST(input, test)
{
    auto first_point = Point(1.0, 1.0);
    auto second_point = Point(2.0, 2.0);
    auto third_point = Point(1.0, 2.0);
    auto fourth_point = Point(2.0, 1.0);

    std::istringstream input("1.0 1.0\n2.0 2.0\n1.0 2.0\n2.0 1.0\n1.0 1.0\n5.0 1.0\n4.0 3.0\n1000.0 1000.0");
    std::streambuf* original_cin = std::cin.rdbuf();

    std::cin.rdbuf(input.rdbuf());

    Square<double> square;
    std::cin >> square;
    
    auto expected_result = Array({first_point, fourth_point, second_point, third_point});
    auto result = square.get_crds_array();
    ASSERT_TRUE(*result == expected_result);
    
    Square<double> bad;
    ASSERT_THROW(std::cin >> bad, BadInputDataException);

    std::cin.rdbuf(original_cin); 
}
 
int main(int argc, char **argv) { 
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}