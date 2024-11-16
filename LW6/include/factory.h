#pragma once

#include <memory>

#include "npcs.h"

class Factory {
    public:
        static std::shared_ptr<NPC> create_npc(const std::string &type, const std::string &name, double x, double y);
        static std::shared_ptr<NPC> load_npc(std::istream &is);
};
