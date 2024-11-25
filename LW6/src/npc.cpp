#include <fstream>
#include <utility>

#include <npc.h>

NPC::NPC(std::string type, std::string name, double x, double y)  : _type(std::move(type)),
    _name(std::move(name)), _x(x), _y(y), alive(true) {}

NPC& NPC::operator=(const NPC &other) {
    if (this != &other) {
        _name = other._name;
        _x = other._x;
        _y = other._y;
        alive = other.alive;
    }
    return *this;
}

NPC& NPC::operator=(NPC &&other) noexcept {
    if (this != &other) {
        _name = other._name;
        _x = other._x;
        _y = other._y;
        alive = other.alive;
    }
    return *this;
}

void NPC::accept(FightVisitor &visitor) const {
    visitor.visit(*this);
}

void NPC::save(std::ofstream &os, const bool nl) const {
    if (os.is_open()) {
        os << _type << " " << _name << " " << _x << " " << _y;
        if (nl)
            os << std::endl;
    }
}

std::string NPC::get_type() const {
    return _type;
}

std::string NPC::get_name() const {
    return _name;
}

Pair NPC::get_crds() const {
    return Pair{_x, _y};
}