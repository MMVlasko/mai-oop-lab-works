#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>

#include <visitor.h>
#include <npc.h>

TEST(constructors_and_get_npcs, test)
{
    auto type = "werewolf";
    auto name = "Mihail";
    auto x = 100.;
    auto y = 200.1;

    auto npc_1 = std::make_shared<NPC>(NPC(type, name, x, y));
    auto npc_2 = std::make_shared<NPC>(NPC(type, name, x, y));

    auto visitor = FightVisitor(npc_1, npc_2);
    auto new_visitor = FightVisitor(visitor);
    auto another_visitor = FightVisitor(FightVisitor(npc_1, npc_2));
    auto copied_visitor = FightVisitor(npc_1, npc_2);
    copied_visitor = visitor;
    auto moved_visitor = FightVisitor(npc_1, npc_2);
    moved_visitor = FightVisitor(npc_1, npc_2);
}

TEST(fight, test)
{
    auto type_1 = "werewolf";
    auto name_1 = "Mihail";
    auto x_1 = 100.;
    auto y_1 = 200.1;

    auto type_2 = "bear";
    auto name_2 = "Alex";
    auto x_2 = 100.;
    auto y_2 = 201.1;

    auto npc_1 = std::make_shared<NPC>(NPC(type_1, name_1, x_1, y_1));
    auto npc_2 = std::make_shared<NPC>(NPC(type_2, name_2, x_2, y_2));

    auto visitor = FightVisitor(npc_2, npc_1);
    visitor.fight(true);

    ASSERT_TRUE(npc_1->status == KILLED);
    ASSERT_TRUE(npc_2->status == ALIVE);
}

TEST(visit, test)
{
    auto type_1 = "werewolf";
    auto name_1 = "Mihail";
    auto x_1 = 100.;
    auto y_1 = 200.1;

    auto type_2 = "bear";
    auto name_2 = "Alex";
    auto x_2 = 150.;
    auto y_2 = 250.1;

    auto npc_1 = std::make_shared<NPC>(NPC(type_1, name_1, x_1, y_1));
    auto npc_2 = std::make_shared<NPC>(NPC(type_2, name_2, x_2, y_2));

    auto observer = ConsoleObserver();
    npc_1->add_observer(std::make_shared<ConsoleObserver>(observer));
    npc_2->add_observer(std::make_shared<ConsoleObserver>(observer));

    auto visitor = FightVisitor(npc_2, npc_1);

    testing::internal::CaptureStdout();
    visitor.visit();
    auto output = testing::internal::GetCapturedStdout();

    ASSERT_TRUE(npc_1->status == KILLED);
    ASSERT_TRUE(npc_2->status == ALIVE);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}