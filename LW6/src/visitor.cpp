#include <npc.h>
#include <tools.h>
#include <visitor.h>

FightVisitor::FightVisitor(std::shared_ptr<Array<NPC>> &npcs, double max_distance,
        const std::shared_ptr<std::map<std::string, std::string>>& rules) : _npcs(npcs),
    _max_distance(max_distance), _rules(rules) {}

FightVisitor &FightVisitor::operator=(const FightVisitor &other) {
    if (this != &other) {
        _npcs = other._npcs;
        _max_distance = other._max_distance;
    }
    return *this;
}

FightVisitor &FightVisitor::operator=(FightVisitor &&other) noexcept {
    if (this != &other) {
        _npcs = other._npcs;
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

void FightVisitor::visit(BaseNPC &npc) {
    auto att_t = npc.get_type();
    auto def_t = (*_npcs)[_now]->get_type();
    auto att_crds = npc.get_crds();
    auto def_crds = (*_npcs)[_now]->get_crds();

    if (can_kill(att_t, def_t, _rules) && distance(att_crds, def_crds) <= _max_distance) {
        (*_npcs)[_now]->alive = false;
        npc.notify(*(*_npcs)[_now]);
    }
}