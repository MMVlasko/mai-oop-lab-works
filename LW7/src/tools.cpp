#include <array>
#include <cmath>
#include <list>
#include <random>

#include <factory.h>
#include <tools.h>

bool correct_npc_type(const std::string &type, const std::shared_ptr<std::map<std::string, std::string>> &rules) {
    for (auto &elem : *rules)
        if (elem.first == type)
            return true;
    return false;
}

bool can_kill(const std::string &attacker, const std::string &defender,
        const std::shared_ptr<std::map<std::string, std::string>> &rules) {
    for (auto& [at, def] : *rules)
        if (at == attacker && def == defender)
            return true;
    return false;
}

double distance(const Pair first, const Pair second) {
    return std::pow(std::pow(second.x - first.x, 2) + std::pow(second.y - first.y, 2), 0.5);
}

std::shared_ptr<Array<NPC>> make_npcs(const std::shared_ptr<std::map<std::string, std::string>>& rules,
        const std::shared_ptr<Array<std::shared_ptr<Observer>>>& observers, double size) {
    auto names = {
        "Michael", "Henry", "Ethan", "Avery", "Dylan", "James", "Olivia",
        "Zoe", "Ryan", "Nathan", "Scarlett", "Logan", "Madison", "Charlotte",
        "Isabella", "Jack", "Emily", "Benjamin", "Mia", "Addison", "Chloe",
        "Abigail", "Joshua", "Hannah", "Ella", "Matthew", "Eleanor", "Boris",
        "John", "Jacob", "Sophia", "Alice", "Amelia", "Lucas", "Thomas", "William",
        "Lily", "Sofia", "Emma", "David", "Joseph", "Ava", "Andrew", "Daniel",
        "Victoria", "Harper", "Caleb", "Liam", "Samuel", "Grace"
    };

    auto npcs = std::make_shared<Array<NPC>>(Array<NPC>());
    auto types = std::array<std::string, 3>{"werewolf", "bear", "robber"};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0., size);

    int i = 0;
    for (auto name : names) {
        double x = dist(gen);
        double y = dist(gen);
        auto npc = Factory::create_npc(types[i % 3], name, x, y, rules, size);
        if (observers != nullptr)
            for (int j = 0; j < observers->size; ++j)
                npc->add_observer(*(*observers)[j]);
        npcs->add(*npc);
        ++i;
    }

    return npcs;
}
