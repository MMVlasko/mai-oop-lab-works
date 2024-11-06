#include <gtest/gtest.h>

#include <stack_memory_resource.h>

TEST(destructor, test)
{
    auto *mr = new StackMemoryResource();
    delete mr;
}

TEST(allocate_and_deallocate, test)
{
    auto element = 333;
    StackMemoryResource mr;

    auto *number = static_cast<int*>(mr.allocate(sizeof(int), 0));
    *number = element;

    auto *enough_number = static_cast<int*>(mr.allocate(sizeof(int), 0));
    *enough_number = element;

    ASSERT_EQ(*number, element);
    ASSERT_EQ(*enough_number, element);

    mr.deallocate(number, sizeof(int), 0);
    mr.deallocate(enough_number, sizeof(int), 0);

    ASSERT_THROW(mr.deallocate(number, sizeof(long), 0), std::logic_error);
}

TEST(do_is_equal, test_complex)
{
    StackMemoryResource mr1;
    const StackMemoryResource& mr2 = mr1;
    StackMemoryResource mr3;

    ASSERT_TRUE(mr1 == mr2);
    ASSERT_FALSE(mr1 == mr3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}