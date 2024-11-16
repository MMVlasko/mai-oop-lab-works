#pragma once

#include "array.h"
#include "observer.h"

class NPC;

class Visitor {
    std::shared_ptr<Array<NPC>> _npcs;
    std::shared_ptr<Array<std::shared_ptr<Observer>>> _observers;
    double _max_distance;
    int _now = 0;

    void _log(const std::string &message) const;

    public:
        Visitor(std::shared_ptr<Array<NPC>>& npcs, double max_distance,
            const std::shared_ptr<Array<std::shared_ptr<Observer>>>& observers);

        Visitor(const Visitor &other) = default;

        Visitor(Visitor &&other) = default;

        Visitor &operator=(const Visitor &other);

        Visitor &operator=(Visitor &&other) noexcept;

        void fight();

        void visit(const NPC &npc);
};