#include <gtest/gtest.h>

#include <exceptions.h>
#include <stack_memory_resource.h>
#include <stack.h>

TEST(default_constructor, test)
{
    StackMemoryResource mr;

    auto stack = Stack<int>(&mr);

    auto expected_size = 0;
    auto size = stack.size();
    ASSERT_EQ(size, expected_size);
}

TEST(push_and_pop, test)
{
    StackMemoryResource mr;
    auto stack = Stack<int>(&mr);

    ASSERT_THROW(stack.pop(), EmptyStackException);

    auto element = 333;
    auto expected_size = 1;
    auto final_expected_size = 0;

    stack.push(element);
    ASSERT_EQ(stack.size(), expected_size);

    auto result = stack.pop();

    ASSERT_EQ(*result, element);
    ASSERT_EQ(stack.size(), final_expected_size);
}

TEST(push_and_pop, test_complex)
{
    struct Complex {
        int A;
        int B;
    };

    StackMemoryResource mr;
    auto stack = Stack<Complex>(&mr);

    auto element = Complex{12, 13};
    auto expected_size = 1;
    auto final_expected_size = 0;

    stack.push(element);
    ASSERT_EQ(stack.size(), expected_size);

    auto result = stack.pop();

    ASSERT_EQ(result->A, element.A);
    ASSERT_EQ(result->B, element.B);
    ASSERT_EQ(stack.size(), final_expected_size);
}

TEST(top, test)
{
    StackMemoryResource mr;
    auto stack = Stack<int>(&mr);

    ASSERT_THROW(stack.top(), EmptyStackException);

    auto element = 333;

    stack.push(333);

    auto result = stack.top();

    ASSERT_EQ(*result, element);
}

TEST(size, test)
{
    StackMemoryResource mr;
    auto stack = Stack<int>(&mr);

    auto first_expected_size = 0;
    auto sec_expected_size = 6;

    ASSERT_EQ(stack.size(), first_expected_size);

    for (int i = 0; i < 6; ++i)
        stack.push(i);

    ASSERT_EQ(stack.size(), sec_expected_size);
}

TEST(empty, stack)
{
    StackMemoryResource mr;
    auto stack = Stack<int>(&mr);
    auto element = 1;

    ASSERT_TRUE(stack.empty());

    stack.push(element);

    ASSERT_FALSE(stack.empty());
}

TEST(clear_and_destructor, test)
{
    StackMemoryResource mr;
    auto stack = Stack<int>(&mr);

    auto sec_expected_size = 0;
    auto first_expected_size = 6;

    for (int i = 0; i < 6; ++i)
        stack.push(i);

    ASSERT_EQ(stack.size(), first_expected_size);

    stack.clear();

    ASSERT_EQ(stack.size(), sec_expected_size);
}

TEST(copy_constructor, test)
{
    StackMemoryResource mr;
    StackMemoryResource mr1;
    auto stack = Stack<int>(&mr);

    for (int i = 0; i < 6; ++i)
        stack.push(i);

    auto new_stack = Stack(stack, &mr1);

    ASSERT_EQ(stack.size(), new_stack.size());
    for (int i = 0; i < stack.size(); ++i)
        ASSERT_EQ(*stack.pop(), *new_stack.pop());
}

TEST(move_constructor, test)
{
    StackMemoryResource mr;
    auto stack = Stack(Stack<int>(&mr));
    auto element = 333;
    auto expected_size = 1;

    stack.push(element);


    ASSERT_EQ(stack.size(), expected_size);
    ASSERT_EQ(*stack.pop(), element);
}

TEST(assignment_operator, test)
{
    StackMemoryResource mr;
    auto stack = Stack<int>(&mr);

    for (int i = 0; i < 6; ++i)
        stack.push(i);

    StackMemoryResource mr1;
    auto new_stack = Stack<int>(&mr1);

    new_stack.push(333);

    new_stack = stack;

    ASSERT_EQ(stack.size(), new_stack.size());
    for (int i = 0; i < stack.size(); ++i)
        ASSERT_EQ(*stack.pop(), *new_stack.pop());
}

TEST(move_assignment_operator, test)
{
    StackMemoryResource mr;
    auto stack = Stack<int>(&mr);
    auto expected_size = 0;

    for (int i = 0; i < 6; ++i)
        stack.push(i);

    StackMemoryResource mr1;
    stack = Stack<int>(&mr1);

    ASSERT_EQ(stack.size(), expected_size);
}

TEST(equal_operator, test)
{
    StackMemoryResource mr;
    auto stack = Stack<int>(&mr);

    for (int i = 0; i < 6; ++i)
        stack.push(i);

    StackMemoryResource mr1;
    auto new_stack = Stack<int>(&mr1);

    for (int i = 0; i < 6; ++i)
        new_stack.push(i);

    ASSERT_TRUE(stack == new_stack);

    new_stack.pop();

    ASSERT_FALSE(stack == new_stack);
}

TEST(not_equal_operator, test)
{
    StackMemoryResource mr;
    auto stack = Stack<int>(&mr);

    for (int i = 0; i < 6; ++i)
        stack.push(i);

    StackMemoryResource mr1;
    auto new_stack = Stack<int>(&mr1);

    for (int i = 0; i < 6; ++i)
        new_stack.push(i);

    ASSERT_FALSE(stack != new_stack);

    new_stack.pop();

    ASSERT_TRUE(stack != new_stack);
}

TEST(print, test)
{
    StackMemoryResource mr;
    auto result = "]5, 4, 3, 2, 1, 0]";
    auto stack = Stack<int>(&mr);

    for (int i = 0; i < 6; ++i)
        stack.push(i);

    testing::internal::CaptureStdout();
    std::cout << stack;
    auto output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, result);
}

TEST(print, test_empty)
{
    StackMemoryResource mr;
    auto result = "]]";
    auto stack = Stack<int>(&mr);

    testing::internal::CaptureStdout();
    std::cout << stack;
    auto output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, result);
}

TEST(iteration, tests)
{
    StackMemoryResource mr;
    auto stack = Stack<int>(&mr);
    auto count = 15;
    auto expected = count;

    for (int i = 0; i < count + 1; ++i)
        stack.push(i);

    auto iter = stack.begin();
    auto end = stack.end();
    auto  begin = stack.begin();

    ASSERT_TRUE(iter == begin);
    ASSERT_TRUE(iter != end);

    ASSERT_EQ(*iter, expected);

    iter++;
    --expected;
    ASSERT_EQ(*(iter.operator->()), expected);

    ++iter;
    --expected;
    ASSERT_EQ(*iter, expected);

    for (int elem : stack) {
        ASSERT_EQ(elem, count);
        --count;
    }
}

TEST(owerflow_error, test)
{
    StackMemoryResource mr;
    auto stack = Stack<int>(&mr);

    ASSERT_THROW(for (int i = 0; i < 5000; ++i) stack.push(i), OutOfMemoryException);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}