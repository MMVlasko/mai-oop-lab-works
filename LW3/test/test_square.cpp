#include <gtest/gtest.h> 

#include <exceptions.h>
#include <array.h>
#include <square.h>
#include <point.h>

TEST(init_list_constructor, test)
{
    auto *first_point = new Point(1.0, 1.0);
    auto *second_point = new Point(2.0, 2.0);
    auto *third_point = new Point(1.0, 2.0);
    auto *fourth_point = new Point(2.0, 1.0);

    auto expected_result = Array({first_point, fourth_point, second_point, third_point});
    auto square = Square({first_point, second_point, third_point, fourth_point});

    auto *result = square.get_crds_array();
    ASSERT_TRUE(*result == expected_result);

    result->free_elements();
    delete result;
}
 
int main(int argc, char **argv) { 
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}