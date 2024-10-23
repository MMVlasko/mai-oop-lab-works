#include <gtest/gtest.h> 

#include <exceptions.h>
#include <array.h>
#include <figure.h>
#include <point.h>
#include <tools.h>

TEST(empty_constructor, test)
{
    auto figure = Figure<int>();
    ASSERT_THROW(figure.get_crds_array(), UninitializedException);
}

TEST(init_list_constructor, test)
{
    auto first_point = Point(1.0, 1.0);
    auto second_point = Point(2.0, 1.0);
    auto third_point = Point(1.0, 2.0);

    auto expected_result = Array({first_point, second_point, third_point});
    auto figure = Figure({first_point, second_point, third_point});

    auto result = figure.get_crds_array();
    ASSERT_TRUE(*result == expected_result);
}

TEST(copy_constructor, test)
{
    auto first_point =Point(1.0, 1.0);
    auto second_point = Point(1.0, 2.0);
    auto third_point = Point(2.0, 1.0);
    auto first_figure = Figure({first_point, second_point, third_point});
    auto second_figure = Figure(first_figure);

    ASSERT_TRUE(first_figure == second_figure);
}

TEST(move_constructor, test)
{
    auto first_point = Point(1, 1);
    auto second_point = Point(2, 1);
    auto third_point = Point(1, 2);
    auto figure = Figure(Figure({first_point, second_point, third_point}));

    auto result = figure.get_crds_array();
    ASSERT_TRUE(first_point == *(*result)[0]);
    ASSERT_TRUE(second_point == *(*result)[1]);
    ASSERT_TRUE(third_point == *(*result)[2]);
}

TEST(destructor, test)
{
    auto first_point = Point(1.0, 1.0);
    auto second_point = Point(1.0, 2.0);

    auto expected_result = Array({first_point, second_point});
    auto figure = Figure({first_point, second_point});

    auto result = figure.get_crds_array();
    ASSERT_TRUE(*result == expected_result);
}

TEST(assignment_operator, test) 
{
    auto first_point = Point(1.0, 1.0);
    auto second_point = Point(1.0, 2.0);
    auto third_point = Point(2.0, 1.0);

    auto first_figure = Figure({first_point, second_point, third_point});
    auto second_figure = Figure({Point(first_point)});
    first_figure = second_figure;

    ASSERT_TRUE(first_figure == second_figure);
}

TEST(move_assignment_operator, test) 
{
    auto first_point = Point(1, 1);
    auto second_point = Point(1, 2);
    auto third_point = Point(2, 1);

    auto figure = Figure({Point(first_point), second_point, third_point});
    figure = Figure({Point(first_point)});;

    auto result = figure.get_crds_array();
    ASSERT_TRUE(result->size == 1);
    ASSERT_TRUE(first_point == *(*result)[0]);
}

TEST(equal_operator, test)
{
    auto first_point = Point(1, 1);
    auto second_point = Point(1, 2);
    auto third_point = Point(2, 1);
    auto first_figure = Figure({first_point, second_point, third_point});
    auto second_figure = Figure({Point(first_point), Point(third_point), Point(second_point)});
    auto third_figure = Figure({Point<int>(second_point)});
    
    ASSERT_TRUE(first_figure == second_figure);
    ASSERT_FALSE(first_figure == third_figure);
    ASSERT_FALSE(second_figure == third_figure);
}

TEST(not_equal_operator, test)
{
    auto first_point = Point(1, 1);
    auto second_point = Point(1, 2);
    auto third_point = Point(2, 1);
    auto first_figure = Figure({first_point, second_point, third_point});
    auto second_figure = Figure({Point(first_point), Point(third_point), Point(second_point)});
    auto third_figure = Figure({Point<int>(second_point)});
    
    ASSERT_FALSE(first_figure != second_figure);
    ASSERT_TRUE(first_figure != third_figure);
    ASSERT_TRUE(second_figure != third_figure);
}

TEST(print, test)
{
    auto expected_output = "Figure [(1.1, 1), (2, 1), (1, 2)]";
    auto first_point = Point(1.1, 1.0);
    auto second_point = Point(2.0, 1.0);
    auto third_point = Point(1.0, 2.0);

    auto figure = Figure({first_point, second_point, third_point});

    testing::internal::CaptureStdout();
    std::cout << figure;
    auto output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, expected_output);
}

TEST(get_crds_array, test)
{
    auto expected_output = "[(1.1, 1), (2, 1), (1, 2)]";
    auto first_point = Point(1.1, 1.0);
    auto second_point = Point(2.0, 1.0);
    auto third_point = Point(1.0, 2.0);

    auto figure = Figure({first_point, second_point, third_point});

    auto result = figure.get_crds_array();

    testing::internal::CaptureStdout();
    std::cout << *result;
    auto output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, expected_output);
}

TEST(get_name, test)
{
    auto expected_result = "Figure";
    auto first_point = Point(1.0, 1.0);

    auto figure = Figure({first_point});

    auto result = figure.get_name();

    ASSERT_EQ(result, expected_result);
}

TEST(get_center, test)
{
    auto first_point = Point(1.0, 3.0);
    auto second_point = Point(1.0, 1.0);
    auto third_point = Point(5.0, 1.0);
    auto fourth_point = Point(5.0, 3.0);

    auto expected_result = Point(3.0, 2.0);

    auto figure = Figure({first_point, second_point, third_point, fourth_point});
    auto result = figure.get_center();
    
    ASSERT_TRUE(*result == expected_result);
}

TEST(square, test)
{
    auto first_point = Point(1.0, 3.0);
    auto second_point = Point(1.0, 1.0);
    auto third_point = Point(5.0, 1.0);
    auto fourth_point = Point(5.0, 3.0);

    auto expected_result = 8.;

    auto figure = Figure({first_point, second_point, third_point, fourth_point});
    auto result = static_cast<double>(figure);
    
    ASSERT_EQ(result, expected_result);
}

TEST(input, test)
{
    Figure<double> figure;
    ASSERT_THROW(std::cin >> figure, NotImplementedException);
}
 
int main(int argc, char **argv) { 
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}