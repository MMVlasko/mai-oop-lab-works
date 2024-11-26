#pragma once

#include "array.h"

class NPC;

class Visitor {
    public:
        virtual ~Visitor() = default;

        virtual void visit(NPC& npc) = 0;
};

class FightVisitor : Visitor {
    std::shared_ptr<Array<NPC>> _npcs;
    double _max_distance;
    int _now = 0;

    public:
        FightVisitor(std::shared_ptr<Array<NPC>>& npcs, double max_distance);

        FightVisitor(const FightVisitor &other) = default;

        FightVisitor(FightVisitor &&other) = default;

        FightVisitor &operator=(const FightVisitor &other);

        FightVisitor &operator=(FightVisitor &&other) noexcept;

        void fight();

        void visit(NPC &npc) override;
};