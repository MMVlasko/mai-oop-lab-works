#include <gtest/gtest.h> 

#include <point.h>

TEST(empty_constructor, test)
{
    auto exp = 0.;
    auto point = Point();

    ASSERT_EQ(point.x, exp);
    ASSERT_EQ(point.y, exp);
}

TEST(arg_constructor, test) 
{
    auto x = 1.1;
    auto y = 2.2;

    auto point = Point(x, y);

    ASSERT_EQ(point.x, x);
    ASSERT_EQ(point.y, y);
}

TEST(copy_constructor, test)
{
    auto x = 1.1;
    auto y = 2.2;

    auto first_point = Point(x, y);
    auto second_point = Point(first_point);

    ASSERT_EQ(first_point.x, second_point.x);
    ASSERT_EQ(first_point.y, second_point.y);
}

TEST(move_constructor, test)
{
    auto x = 1.1;
    auto y = 2.2;

    auto point = Point(Point(x, y));

    ASSERT_EQ(point.x, x);
    ASSERT_EQ(point.y, y);
}

TEST(assignment_operator, test)
{
    auto x = 1.1;
    auto y = 2.2;

    auto first_point = Point(x, y);
    auto second_point = Point();
    second_point = first_point;

    ASSERT_EQ(first_point.x, second_point.x);
    ASSERT_EQ(first_point.y, second_point.y);
}

TEST(move_assignment_operator, test)
{
    auto x = 1.1;
    auto y = 2.2;

    auto point = Point();
    point = Point(x, y);

    ASSERT_EQ(point.x, x);
    ASSERT_EQ(point.y, y);
}

TEST(destructor, test) 
{
    auto x = 1.1;
    auto y = 2.2;

    auto *point = new Point(x, y);

    ASSERT_EQ(point->x, x);
    ASSERT_EQ(point->y, y);

    delete point;
}

TEST(print, test)
{
    auto result = "(1.1, 2.2)";
    auto x = 1.1;
    auto y = 2.2;

    auto point = Point(x, y);

    testing::internal::CaptureStdout();
    std::cout << point;
    auto output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, result);
}

TEST(equal_operator, test)
{
    auto x = 1.1;
    auto y = 2.2;

    auto first_point = Point(x, y);
    auto second_point = Point(x, y);

    ASSERT_TRUE(first_point == second_point);
    first_point.x = 11.2;
    ASSERT_FALSE(first_point == second_point);
}

TEST(not_equal_operator, test)
{
    auto x = 1.1;
    auto y = 2.2;

    auto first_point = Point(x, y);
    auto second_point = Point(x, y);

    ASSERT_FALSE(first_point != second_point);
    first_point.x = 11.2;
    ASSERT_TRUE(first_point != second_point);
}

TEST(distance, test)
{
    auto first = Point(1, 1);
    auto second = Point(4, 5);
    auto expected_result = 5.;

    auto first_result = first.distance(second);
    auto second_result = second.distance(first);

    ASSERT_EQ(first_result, expected_result);
    ASSERT_EQ(second_result, expected_result);
}

int main(int argc, char **argv) { 
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}