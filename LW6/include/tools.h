#pragma once

#include <map>
#include <memory>
#include <string>

#include <npc.h>

bool correct_npc_type(const std::string &type, const std::shared_ptr<std::map<std::string, std::string>>& rules);

bool can_kill(const std::string &attacker, const std::string &defender,
    const std::shared_ptr<std::map<std::string, std::string>>& rules);

double distance(Pair first, Pair second);
