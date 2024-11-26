#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>

#include <observer.h>

TEST(console_handle_event, test)
{
    auto observer = ConsoleObserver();
    auto message = "hello";
    auto expected = "hello\n";

    testing::internal::CaptureStdout();
    observer.handle_event(message);
    auto output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, expected);
}

TEST(file_handle_event, test)
{
    auto filename = "log.txt";
    auto observer = FileObserver(filename);
    auto message = "hello";

    observer.handle_event(message);

    std::ifstream input(filename);
    ASSERT_TRUE(input.good());

    std::string result;
    input >> result;

    ASSERT_EQ(result, message);
    input.close();
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}