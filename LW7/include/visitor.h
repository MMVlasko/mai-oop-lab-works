#pragma once

#include "array.h"

class BaseNPC;

class NPC;

class Visitor {
    public:
        virtual ~Visitor() = default;

        virtual void visit() = 0;
};

class FightVisitor : public Visitor {
    std::shared_ptr<NPC> _attacker;
    std::shared_ptr<NPC> _defender;

    public:
        FightVisitor(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender);

        FightVisitor(const FightVisitor &other) = default;

        FightVisitor(FightVisitor &&other) = default;

        FightVisitor &operator=(const FightVisitor &other);

        FightVisitor &operator=(FightVisitor &&other) noexcept;

        void fight(bool test = false);

        void visit() override;
};