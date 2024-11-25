#include <fstream>
#include <filesystem>
#include <gtest/gtest.h>

#include <npc.h>

TEST(constructors_and_gettings, test)
{
    auto expected_alive = true;
    auto type = "werewolf";
    auto name = "Mihail";
    auto x = 100.;
    auto y = 200.1;

    auto npc = NPC(type, name, x, y);
    auto new_npc = NPC(npc);
    auto another_npc = NPC(NPC(type, name, x, y));
    auto copied_npc = NPC(npc);
    copied_npc = npc;
    auto moved_npc = NPC(npc);
    moved_npc = NPC(npc);

    ASSERT_EQ(npc.get_type(), type);
    ASSERT_EQ(new_npc.get_type(), type);
    ASSERT_EQ(another_npc.get_type(), type);
    ASSERT_EQ(copied_npc.get_type(), type);
    ASSERT_EQ(moved_npc.get_type(), type);

    ASSERT_EQ(npc.get_name(), name);
    ASSERT_EQ(new_npc.get_name(), name);
    ASSERT_EQ(another_npc.get_name(), name);
    ASSERT_EQ(copied_npc.get_name(), name);
    ASSERT_EQ(moved_npc.get_name(), name);

    ASSERT_EQ(npc.get_crds().x, x);
    ASSERT_EQ(new_npc.get_crds().x, x);
    ASSERT_EQ(another_npc.get_crds().x, x);
    ASSERT_EQ(copied_npc.get_crds().x, x);
    ASSERT_EQ(moved_npc.get_crds().x, x);

    ASSERT_EQ(npc.get_crds().y, y);
    ASSERT_EQ(new_npc.get_crds().y, y);
    ASSERT_EQ(another_npc.get_crds().y, y);
    ASSERT_EQ(copied_npc.get_crds().y, y);
    ASSERT_EQ(moved_npc.get_crds().y, y);

    ASSERT_EQ(npc.alive, expected_alive);
    ASSERT_EQ(new_npc.alive, expected_alive);
    ASSERT_EQ(another_npc.alive, expected_alive);
    ASSERT_EQ(copied_npc.alive, expected_alive);
    ASSERT_EQ(moved_npc.alive, expected_alive);
}

TEST(save, test)
{
    auto expected = "werewolf Mihail 100.2 200.1";
    auto type = "werewolf";
    auto name = "Mihail";
    auto x = 100.2;
    auto y = 200.1;

    auto npc = NPC(type, name, x, y);

    auto filename = "input.txt";
    auto _input = std::ofstream(filename);
    ASSERT_TRUE(_input.good());

    npc.save(_input);
    _input.close();

    std::ifstream input(filename);
    ASSERT_TRUE(input.good());

    std::string result;
    std::getline(input, result);

    ASSERT_EQ(expected, result);

    input.close();

    if (std::filesystem::exists(filename))
        std::filesystem::remove(filename);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}