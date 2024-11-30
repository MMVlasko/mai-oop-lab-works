#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>

#include <visitor.h>
#include <npc.h>

static auto rules = std::make_shared<std::map<std::string, std::string>>(
    std::map({
        std::pair<std::string, std::string> {"werewolf", "robber"},
        std::pair<std::string, std::string> {"robber", "bear"},
        std::pair<std::string, std::string> {"bear", "werewolf"}
    })
);

TEST(constructors_and_get_npcs, test)
{
    auto max_distance = 100.;
    auto type = "werewolf";
    auto name = "Mihail";
    auto x = 100.;
    auto y = 200.1;

    auto npc = NPC(type, name, x, y);
    auto npcs = std::make_shared<Array<NPC>>(Array<NPC>());
    npcs->add(npc);

    auto visitor = FightVisitor(npcs, max_distance, rules);
    auto new_visitor = FightVisitor(visitor);
    auto another_visitor = FightVisitor(FightVisitor(npcs, max_distance, rules));
    auto copied_visitor = FightVisitor(npcs, max_distance, rules);
    copied_visitor = visitor;
    auto moved_visitor = FightVisitor(npcs, max_distance, rules);
    moved_visitor = FightVisitor(npcs, max_distance, rules);
}

TEST(fight, test)
{
    auto expected_size = 1;
    auto max_distance = 100.;

    auto type_1 = "werewolf";
    auto name_1 = "Mihail";
    auto x_1 = 100.;
    auto y_1 = 200.1;

    auto type_2 = "bear";
    auto name_2 = "Alex";
    auto x_2 = 150.;
    auto y_2 = 250.1;

    auto npc_1 = NPC(type_1, name_1, x_1, y_1);
    auto npc_2 = NPC(type_2, name_2, x_2, y_2);

    auto npcs = std::make_shared<Array<NPC>>(Array<NPC>());
    npcs->add(npc_1);
    npcs->add(npc_2);

    auto visitor = FightVisitor(npcs, max_distance, rules);
    visitor.fight();

    ASSERT_EQ(npcs->size, expected_size);
    ASSERT_EQ((*npcs)[0]->get_name(), name_2);
}

TEST(visit, test)
{
    auto expected = "NPC Mihail (werewolf) was killed by NPC Alex (bear)\n";
    auto max_distance = 100.;

    auto type_1 = "werewolf";
    auto name_1 = "Mihail";
    auto x_1 = 100.;
    auto y_1 = 200.1;

    auto type_2 = "bear";
    auto name_2 = "Alex";
    auto x_2 = 150.;
    auto y_2 = 250.1;

    auto npc_1 = NPC(type_1, name_1, x_1, y_1);
    auto npc_2 = NPC(type_2, name_2, x_2, y_2);

    auto npcs = std::make_shared<Array<NPC>>(Array<NPC>());
    npcs->add(npc_1);

    auto observer = ConsoleObserver();
    npc_1.add_observer(std::make_shared<ConsoleObserver>(observer));
    npc_2.add_observer(std::make_shared<ConsoleObserver>(observer));

    auto visitor = FightVisitor(npcs, max_distance, rules);

    testing::internal::CaptureStdout();
    visitor.visit(npc_2);
    auto output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, expected);
    ASSERT_FALSE((*npcs)[0]->alive);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}