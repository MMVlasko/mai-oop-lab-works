#include <gtest/gtest.h> 
#include <iostream>
#include <sstream>

#include <exceptions.h>
#include <array.h>
#include <trapeze.h>
#include <point.h>

TEST(init_list_constructor, test_1)
{
    auto first_point = Point(1.0, 1.0);
    auto second_point = Point(5.0, 1.0);
    auto third_point = Point(4.0, 3.0);
    auto fourth_point = Point(2.0, 3.0);

    auto bad_point = Point(1000.0, 1000.0);

    auto expected_result = Array({first_point, second_point, third_point, fourth_point});
    auto trapeze = Trapeze({first_point, second_point, third_point, fourth_point});

    auto result = trapeze.get_crds_array();
    ASSERT_TRUE(*result == expected_result);
}

TEST(init_list_constructor, test_2)
{
    auto first_point = Point(0.0, 0.0);
    auto second_point = Point(4.0, 5.0);
    auto third_point = Point(4.0, 100.0);
    auto fourth_point = Point(0.0, 300.0);

    auto expected_result = Array({first_point, second_point, third_point, fourth_point});
    auto trapeze = Trapeze({first_point, second_point, third_point, fourth_point});

    auto result = trapeze.get_crds_array();
    ASSERT_TRUE(*result == expected_result);
}

TEST(init_list_constructor, test_3)
{
    auto first_point = Point(1.0, 1.0);
    auto second_point = Point(501.0, 1.0);
    auto third_point = Point(444.0, 30.0);
    auto fourth_point = Point(11.0, 30.0);

    auto expected_result = Array({first_point, second_point, third_point, fourth_point});
    auto trapeze = Trapeze({first_point, second_point, third_point, fourth_point});

    auto result = trapeze.get_crds_array();
    ASSERT_TRUE(*result == expected_result);
}

TEST(input, test)
{
    auto first_point = Point(1.0, 1.0);
    auto second_point = Point(5.0, 1.0);
    auto third_point = Point(4.0, 3.0);
    auto fourth_point = Point(2.0, 3.0);

    std::istringstream input("1.0 1.0\n5.0 1.0\n4.0 3.0\n2.0 3.0\n1.0 1.0\n5.0 1.0\n4.0 3.0\n1000.0 1000.0");
    std::streambuf* original_cin = std::cin.rdbuf();

    std::cin.rdbuf(input.rdbuf());

    Trapeze<double> trapeze;
    std::cin >> trapeze;
    
    auto expected_result = Array({first_point, second_point, third_point, fourth_point});
    auto result = trapeze.get_crds_array();
    ASSERT_TRUE(*result == expected_result);

    Trapeze<double> bad;
    ASSERT_THROW(std::cin >> bad, BadInputDataException);

    std::cin.rdbuf(original_cin); 
}
 
int main(int argc, char **argv) { 
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}