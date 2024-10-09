#include <gtest/gtest.h> 

#include <exceptions.h>
#include <array.h>
#include <figure.h>
#include <point.h>

TEST(destructor, test)
{
    auto *first_point = new Point(1.0, 1.0);
    auto *second_point = new Point(1.0, 2.0);

    auto expected_result = Array({first_point, second_point});
    auto *figure = new Figure({first_point, second_point});

    auto *result = figure->get_crds_array();
    ASSERT_TRUE(*result == expected_result);

    delete figure;
    result->free_elements();
    delete result;
}

TEST(init_list_constructor, test)
{
    auto *first_point = new Point(1.0, 1.0);
    auto *second_point = new Point(1.0, 2.0);
    auto *third_point = new Point(2.0, 1.0);

    auto expected_result = Array({first_point, second_point, third_point});
    auto figure = Figure({first_point, second_point, third_point});

    auto *result = figure.get_crds_array();
    ASSERT_TRUE(*result == expected_result);

    result->free_elements();
    delete result;
}

TEST(copy_constructor, test)
{
    auto *first_point = new Point(1.0, 1.0);
    auto *second_point = new Point(1.0, 2.0);
    auto *third_point = new Point(2.0, 1.0);
    auto *first_figure = new Figure({first_point, second_point, third_point});
    auto *second_figure = new Figure(*first_figure);

    ASSERT_TRUE(*first_figure == *second_figure);

    delete first_figure;
    delete second_figure;
}

TEST(print, test)
{
    auto expected_output = "[(1.1, 1), (1, 2), (2, 1)]";
    auto *first_point = new Point(1.1, 1.0);
    auto *second_point = new Point(1.0, 2.0);
    auto *third_point = new Point(2.0, 1.0);

    auto *figure = new Figure({first_point, second_point, third_point});

    testing::internal::CaptureStdout();
    std::cout << *figure;
    auto output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, expected_output);

    delete figure;
}
 
int main(int argc, char **argv) { 
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}