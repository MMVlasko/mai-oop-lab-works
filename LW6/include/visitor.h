#pragma once

#include <map>

#include "array.h"

class BaseNPC;

class NPC;

class Visitor {
    public:
        virtual ~Visitor() = default;

        virtual void visit(BaseNPC& npc) = 0;
};

class FightVisitor : public Visitor {
    const std::shared_ptr<std::map<std::string, std::string>>& _rules;
    std::shared_ptr<Array<NPC>> _npcs;
    double _max_distance;
    int _now = 0;

    public:
        FightVisitor(std::shared_ptr<Array<NPC>>& npcs, double max_distance,
            const std::shared_ptr<std::map<std::string, std::string>>& rules);

        FightVisitor(const FightVisitor &other) = default;

        FightVisitor(FightVisitor &&other) = default;

        FightVisitor &operator=(const FightVisitor &other);

        FightVisitor &operator=(FightVisitor &&other) noexcept;

        void fight();

        void visit(BaseNPC &npc) override;
};