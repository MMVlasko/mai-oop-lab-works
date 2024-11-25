#pragma once

#include <string>

#include "visitor.h"

struct Pair {
    double x;
    double y;
};

class NPC {
    std::string _type, _name;
    double _x, _y;

    public:
        bool alive;

        NPC(std::string type, std::string name, double x, double y);

        NPC(const NPC &other) = default;

        NPC(NPC &&other) = default;

        NPC &operator=(const NPC &other);

        NPC &operator=(NPC &&other) noexcept;

        void accept(FightVisitor &visitor) const;

        void save(std::ofstream &os, bool nl = true) const;

        [[nodiscard]] std::string get_type() const;

        [[nodiscard]] std::string get_name() const;

        [[nodiscard]] Pair get_crds() const;
};