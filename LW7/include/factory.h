#pragma once

#include <memory>
#include <map>

#include "npc.h"

class Factory {
    public:
        static std::shared_ptr<NPC> create_npc(const std::string &type, const std::string &name, double x, double y,
            const std::shared_ptr<std::map<std::string, std::string>>& rules, double size);

        static std::shared_ptr<NPC> load_npc(std::istream &is,
            const std::shared_ptr<std::map<std::string, std::string>>& rules, double size);
};