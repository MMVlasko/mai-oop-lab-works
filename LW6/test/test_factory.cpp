#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>

#include <exceptions.h>
#include <factory.h>

TEST(create_npc, test)
{
    auto type = "werewolf";
    auto incorrect_type = "aaa";
    auto name = "Mihail";
    auto x = 100.;
    auto y = 200.1;

    auto npc = Factory::create_npc(type, name, x, y);

    ASSERT_EQ(npc->get_type(), type);
    ASSERT_EQ(npc->get_name(), name);
    ASSERT_EQ(npc->get_crds().x, x);
    ASSERT_EQ(npc->get_crds().y, y);

    ASSERT_THROW(Factory::create_npc(incorrect_type, name, x, y), UnknownNPCTypeException);
}

TEST(load_npc, test)
{
    auto type = "werewolf";
    auto name = "Mihail";
    auto x = 100.1;
    auto y = 200.3;

    auto filename = "input.txt";
    auto _input = std::ofstream(filename);
    ASSERT_TRUE(_input.good());
    auto npc_data = "werewolf Mihail 100.1 200.3\naaa mmm 11.1 12.1\nwerewolf mmm hj kfk\nwerewolf mmm 1.0 501.1";

    _input << npc_data;
    _input.close();

    std::ifstream input(filename);
    ASSERT_TRUE(input.good());

    auto npc = Factory::load_npc(input);

    ASSERT_EQ(npc->get_type(), type);
    ASSERT_EQ(npc->get_name(), name);
    ASSERT_EQ(npc->get_crds().x, x);
    ASSERT_EQ(npc->get_crds().y, y);

    ASSERT_THROW(Factory::load_npc(input), UnknownNPCTypeException);
    ASSERT_THROW(Factory::load_npc(input), InvalidCoordinatesExceptions);
    ASSERT_THROW(Factory::load_npc(input), InvalidCoordinatesExceptions);

    input.close();

    if (std::filesystem::exists(filename))
        std::filesystem::remove(filename);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}