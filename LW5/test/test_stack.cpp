#include <gtest/gtest.h>

#include <stack_memory_resource.h>
#include <stack.h>

TEST(default_constructor, test)
{
    StackMemoryResource mr;
    std::pmr::polymorphic_allocator<int> alloc(&mr);

    auto stack = Stack<int>(alloc);

    auto expected_size = 0;
    auto size = stack.size();
    ASSERT_EQ(size, expected_size);
}

TEST(push_and_pop, test)
{
    StackMemoryResource mr;
    std::pmr::polymorphic_allocator<int> alloc(&mr);
    auto stack = Stack<int>(alloc);

    auto element = 333;
    auto expected_size = 1;
    auto final_expected_size = 0;

    stack.push(333);
    ASSERT_EQ(stack.size(), expected_size);

    auto result = stack.pop();

    ASSERT_EQ(*result, element);
    ASSERT_EQ(stack.size(), final_expected_size);
}

TEST(size, test)
{
    StackMemoryResource mr;
    std::pmr::polymorphic_allocator<int> alloc(&mr);
    auto stack = Stack<int>(alloc);

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
    std::pmr::polymorphic_allocator<int> alloc(&mr);
    auto stack = Stack<int>(alloc);
    auto element = 1;

    ASSERT_TRUE(stack.empty());

    stack.push(element);

    ASSERT_FALSE(stack.empty());
}

TEST(clear_and_destructor, test)
{
    StackMemoryResource mr;
    std::pmr::polymorphic_allocator<int> alloc(&mr);
    auto stack = Stack<int>(alloc);

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
    std::pmr::polymorphic_allocator<int> alloc(&mr);
    auto stack = Stack<int>(alloc);

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
    std::pmr::polymorphic_allocator<int> alloc(&mr);
    auto stack = Stack(Stack<int>(alloc));
    auto element = 333;
    auto expected_size = 1;

    stack.push(element);


    ASSERT_EQ(stack.size(), expected_size);
    ASSERT_EQ(*stack.pop(), element);
}

TEST(assignment_operator, test)
{
    StackMemoryResource mr;
    std::pmr::polymorphic_allocator<int> alloc(&mr);
    auto stack = Stack<int>(alloc);

    for (int i = 0; i < 6; ++i)
        stack.push(i);

    StackMemoryResource mr1;
    std::pmr::polymorphic_allocator<int> alloc1(&mr1);
    auto new_stack = Stack<int>(alloc1);

    new_stack.push(333);

    new_stack = stack;

    ASSERT_EQ(stack.size(), new_stack.size());
    for (int i = 0; i < stack.size(); ++i)
        ASSERT_EQ(*stack.pop(), *new_stack.pop());
}

TEST(move_assignment_operator, test)
{
    StackMemoryResource mr;
    std::pmr::polymorphic_allocator<int> alloc(&mr);
    auto stack = Stack<int>(alloc);
    auto expected_size = 0;

    for (int i = 0; i < 6; ++i)
        stack.push(i);

    StackMemoryResource mr1;
    std::pmr::polymorphic_allocator<int> alloc1(&mr1);
    stack = Stack<int>(alloc1);

    ASSERT_EQ(stack.size(), expected_size);
}

TEST(print, test)
{
    StackMemoryResource mr;
    auto result = "]5, 4, 3, 2, 1, 0]";
    std::pmr::polymorphic_allocator<int> alloc(&mr);
    auto stack = Stack<int>(alloc);

    for (int i = 0; i < 6; ++i)
        stack.push(i);

    testing::internal::CaptureStdout();
    std::cout << stack;
    auto output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, result);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}