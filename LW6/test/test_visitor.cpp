#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>

#include <visitor.h>
#include <npcs.h>

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

    auto visitor = Visitor(npcs, max_distance, nullptr);
    auto new_visitor = Visitor(visitor);
    auto another_visitor = Visitor(Visitor(npcs, max_distance, nullptr));
    auto copied_visitor = Visitor(npcs, max_distance, nullptr);
    copied_visitor = visitor;
    auto moved_visitor = Visitor(npcs, max_distance, nullptr);
    moved_visitor = Visitor(npcs, max_distance, nullptr);
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

    auto visitor = Visitor(npcs, max_distance, nullptr);
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
    auto observers = std::make_shared<Array<std::shared_ptr<Observer>>>(Array<std::shared_ptr<Observer>>());
    observers->add(std::make_shared<ConsoleObserver>(observer));

    auto visitor = Visitor(npcs, max_distance, observers);

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