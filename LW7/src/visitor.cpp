#include <random>

#include <mutex.h>
#include <npc.h>
#include <tools.h>
#include <visitor.h>

FightVisitor::FightVisitor(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender) :
    _attacker(attacker), _defender(defender) {}

FightVisitor &FightVisitor::operator=(const FightVisitor &other) {
    if (this != &other) {
        _attacker = other._attacker;
        _defender = other._defender;
    }
    return *this;
}

FightVisitor &FightVisitor::operator=(FightVisitor &&other) noexcept {
    if (this != &other) {
        _attacker = other._attacker;
        _defender = other._defender;
    }
    return *this;
}

void FightVisitor::fight(bool test) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);

    auto attacker_force = dist(gen);
    auto defender_force = dist(gen);

    std::lock_guard lock(fight_mutex);
    if (attacker_force > defender_force || test)
        _attacker->accept(*this);
    else {
        _attacker->status = ALIVE;
        _defender->status = ALIVE;
    }
}

void FightVisitor::visit() {
    _attacker->status = ALIVE;
    _defender->status = KILLED;
    _attacker->notify(*_defender);
}