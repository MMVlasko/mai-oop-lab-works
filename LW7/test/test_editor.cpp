#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>

#include <editor.h>

static auto properties = std::map({
    std::pair<std::string, std::pair<int, int>> {"werewolf", {400, 50}},
    std::pair<std::string, std::pair<int, int>> {"robber", {100, 100}},
    std::pair<std::string, std::pair<int, int>> {"bear", {50, 100}}
});

static auto rules = std::map({
    std::pair<std::string, std::string> {"werewolf", "robber"},
    std::pair<std::string, std::string> {"robber", "bear"},
    std::pair<std::string, std::string> {"bear", "werewolf"}
});

TEST(constructors_and_get_npcs, test)
{
    auto size = 500;
    auto expected_size = 0;

    auto editor = Editor(rules, properties, size, false);
    auto new_editor = Editor(editor);
    auto another_editor = Editor(Editor(rules, properties, size, false));
    auto copied_editor = Editor(rules, properties, size, false);
    copied_editor = editor;
    auto moved_editor = Editor(rules, properties, size, false);
    moved_editor = Editor(rules, properties, size, false);

    auto editor_npcs = editor.get_npcs();
    auto new_editor_npcs = new_editor.get_npcs();
    auto another_editor_npcs = another_editor.get_npcs();
    auto copied_editor_npcs = copied_editor.get_npcs();
    auto moved_editor_npcs = moved_editor.get_npcs();

    ASSERT_EQ(editor_npcs->size, expected_size);
    ASSERT_EQ(new_editor_npcs->size, expected_size);
    ASSERT_EQ(another_editor_npcs->size, expected_size);
    ASSERT_EQ(copied_editor_npcs->size, expected_size);
    ASSERT_EQ(moved_editor_npcs->size, expected_size);
}

TEST(create_and_add_npc, test)
{
    auto fight_size = 500;
    auto size = 1;
    auto type = "werewolf";
    auto name = "Mihail";
    auto x = 100.;
    auto y = 200.1;

    auto editor = Editor(rules, properties, fight_size, false);
    editor.add_npc(type, name, x, y);
    auto npcs = editor.get_npcs();

    ASSERT_EQ(npcs->size, size);

    ASSERT_EQ((*npcs)[0]->get_type(), type);
    ASSERT_EQ((*npcs)[0]->get_name(), name);
    ASSERT_EQ((*npcs)[0]->get_crds().x, x);
    ASSERT_EQ((*npcs)[0]->get_crds().y, y);
}

TEST(load_npc, test)
{
    auto fight_size = 500;
    auto size = 3;
    auto type = "werewolf";
    auto name = "Mihail";
    auto x = 100.1;
    auto y = 200.3;

    auto filename = "input.txt";
    auto _input = std::ofstream(filename);
    ASSERT_TRUE(_input.good());
    auto npc_data = "werewolf Mihail 100.1 200.3\nwerewolf Mihail 100.1 200.3\nwerewolf Mihail 100.1 200.3";

    _input << npc_data;
    _input.close();

    auto editor = Editor(rules, properties, fight_size, false);
    editor.load(filename);
    auto npcs = editor.get_npcs();

    ASSERT_EQ(npcs->size, size);

    for (int i = 0; i < size; ++i) {
        ASSERT_EQ((*npcs)[i]->get_type(), type);
        ASSERT_EQ((*npcs)[i]->get_name(), name);
        ASSERT_EQ((*npcs)[i]->get_crds().x, x);
        ASSERT_EQ((*npcs)[i]->get_crds().y, y);
    }

    if (std::filesystem::exists(filename))
        std::filesystem::remove(filename);
}

TEST(save_npc, test)
{
    auto fight_size = 500;
    auto size = 3;
    auto type = "werewolf";
    auto name = "Mihail";
    auto x = 100.1;
    auto y = 200.3;

    auto filename = "output.txt";
    auto npc_data = "werewolf Mihail 100.1 200.3";

    auto editor = Editor(rules, properties, fight_size, false);

    editor.add_npc(type, name, x, y);
    editor.add_npc(type, name, x, y);
    editor.add_npc(type, name, x, y);

    editor.save(filename);

    std::ifstream input(filename);

    ASSERT_TRUE(input.good());

    std::string result;
    for (int i = 0; i < size; ++i) {
        std::getline(input, result);
        ASSERT_EQ(result, npc_data);
    }

    input.close();

    if (std::filesystem::exists(filename))
        std::filesystem::remove(filename);
}

TEST(fight, test)
{
    auto fight_size = 500;
    auto not_expected = "";

    auto type_1 = "werewolf";
    auto name_1 = "Mihail";
    auto x_1 = 100.;
    auto y_1 = 200.1;

    auto type_2 = "bear";
    auto name_2 = "Alex";
    auto x_2 = 100.;
    auto y_2 = 201.1;

    auto editor = Editor(rules, properties, fight_size, false);
    auto console_observer = std::make_shared<ConsoleObserver>(ConsoleObserver());
    editor.add_observer<ConsoleObserver>(console_observer);

    editor.add_npc(type_1, name_1, x_1, y_1);
    editor.add_npc(type_2, name_2, x_2, y_2);

    auto npcs = editor.get_npcs();

    testing::internal::CaptureStdout();
    Editor::fight((*npcs)[1], (*npcs)[0], true);
    auto output = testing::internal::GetCapturedStdout();

    ASSERT_NE(output, not_expected);
}

TEST(print, test)
{
    auto fight_size = 500;
    auto expected = "werewolf Mihail X = 100 Y = 200.1\nbear Alex X = 150 Y = 250.1\n-----------------\n";

    auto type_1 = "werewolf";
    auto name_1 = "Mihail";
    auto x_1 = 100.;
    auto y_1 = 200.1;

    auto type_2 = "bear";
    auto name_2 = "Alex";
    auto x_2 = 150.;
    auto y_2 = 250.1;

    auto editor = Editor(rules, properties, fight_size, false);

    editor.add_npc(type_1, name_1, x_1, y_1);
    editor.add_npc(type_2, name_2, x_2, y_2);

    testing::internal::CaptureStdout();
    editor.print();
    auto output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, expected);
}

TEST(process_and_move_and_analysis, test)
{
    auto fight_size = 3000;

    auto editor = Editor(rules, properties, fight_size);

    auto file_observer = std::make_shared<FileObserver>(FileObserver("log.txt"));
    editor.add_observer<FileObserver>(file_observer);

    editor.process();
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}