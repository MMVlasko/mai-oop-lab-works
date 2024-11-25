#include <cmath>

#include <npc.h>
#include <visitor.h>

FightVisitor::FightVisitor(std::shared_ptr<Array<NPC>> &npcs, double max_distance,
    const std::shared_ptr<Array<std::shared_ptr<Observer>>> &observers) : _npcs(npcs), _observers(observers),
        _max_distance(max_distance) {}

FightVisitor &FightVisitor::operator=(const FightVisitor &other) {
    if (this != &other) {
        _npcs = other._npcs;
        _observers = other._observers;
        _max_distance = other._max_distance;
    }
    return *this;
}

FightVisitor &FightVisitor::operator=(FightVisitor &&other) noexcept {
    if (this != &other) {
        _npcs = other._npcs;
        _observers = other._observers;
        _max_distance = other._max_distance;
    }
    return *this;
}

void FightVisitor::fight() {
    for (int i = 0; i < _npcs->size; ++i) {
        for (int j = 0; j < _npcs->size; ++j) {
            if (i != j) {
                _now = j;
                (*_npcs)[i]->accept(*this);
            }
        }
    }

    bool exists = true;
    while (exists) {
        exists = false;
        for (int i = 0; i < _npcs->size; ++i) {
            if (!(*_npcs)[i]->alive) {
                _npcs->pop(i);
                exists = true;
                break;
            }
        }
    }
}

void FightVisitor::visit(const NPC &npc) {
    auto self_type = npc.get_type();
    auto other_type = (*_npcs)[_now]->get_type();
    auto self_crds = npc.get_crds();
    auto other_crds = (*_npcs)[_now]->get_crds();

    if ((self_type == "werewolf" && other_type == "robber" || self_type == "robber" && other_type == "bear" ||
        self_type == "bear" && other_type == "werewolf") && std::pow((self_crds.x - other_crds.x), 2) +
        std::pow((self_crds.y - other_crds.y), 2) <= std::pow(_max_distance, 2)) {
        (*_npcs)[_now]->alive = false;
        _log("NPC " + (*_npcs)[_now]->get_name() + " (" + other_type +
            ") was killed by NPC " + npc.get_name() + " (" + self_type + ")");
    }
}

void FightVisitor::_log(const std::string &message) const {
    if (_observers != nullptr)
        for (int i = 0; i < _observers->size; ++i)
            (*(*_observers)[i])->notify(message);
}
