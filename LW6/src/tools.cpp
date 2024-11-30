#include <cmath>

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
