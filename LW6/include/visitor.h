#pragma once

#include "array.h"
#include "observer.h"

class NPC;

class Visitor {
    public:
        virtual ~Visitor() = default;

        virtual void visit(const NPC& npc) = 0;
};

class FightVisitor : Visitor {
    std::shared_ptr<Array<NPC>> _npcs;
    std::shared_ptr<Array<std::shared_ptr<Observer>>> _observers;
    double _max_distance;
    int _now = 0;

    void _log(const std::string &message) const;

    public:
        FightVisitor(std::shared_ptr<Array<NPC>>& npcs, double max_distance,
            const std::shared_ptr<Array<std::shared_ptr<Observer>>>& observers);

        FightVisitor(const FightVisitor &other) = default;

        FightVisitor(FightVisitor &&other) = default;

        FightVisitor &operator=(const FightVisitor &other);

        FightVisitor &operator=(FightVisitor &&other) noexcept;

        void fight();

        void visit(const NPC &npc) override;
};