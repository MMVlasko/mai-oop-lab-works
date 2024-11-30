#include <fstream>
#include <iostream>
#include <thread>

#include <editor.h>
#include <factory.h>
#include <visitor.h>
#include <tools.h>
#include <mutex.h>

Editor::Editor(std::map<std::string, std::string> &rules, std::map<std::string, std::pair<int, int>> &properties,
    double size, bool gen) : _size(size), _stop(false) {
    _rules = std::make_shared<std::map<std::string, std::string>>(rules);
    _observers = std::make_shared<Array<std::shared_ptr<Observer>>>(Array<std::shared_ptr<Observer>>());
    _properties = std::make_shared<std::map<std::string, std::pair<int, int>>>(properties);
    if (gen)
        _npcs = make_npcs(_rules, _observers, _size);
    else
        _npcs = std::make_shared<Array<NPC>>(Array<NPC>());
}

Editor::Editor(const Editor &other) {
    _rules = std::make_shared<std::map<std::string, std::string>>(std::map(*other._rules));
    _npcs = std::make_shared<Array<NPC>>(Array(*other._npcs));
    _observers = std::make_shared<Array<std::shared_ptr<Observer>>>(Array(*other._observers));
    _properties = std::make_shared<std::map<std::string, std::pair<int, int>>>(*other._properties);
    _size = other._size;
}

Editor::Editor(Editor &&other) noexcept {
    _rules = other._rules;
    _npcs = other._npcs;
    _observers = other._observers;
    _size = other._size;
    _properties = other._properties;
}

Editor& Editor::operator=(const Editor &other) {
    if (this != &other) {
        _rules = std::make_shared<std::map<std::string, std::string>>(std::map(*other._rules));
        _npcs = std::make_shared<Array<NPC>>(Array(*other._npcs));
        _observers = std::make_shared<Array<std::shared_ptr<Observer>>>(Array(*other._observers));
        _size = other._size;
        _properties = std::make_shared<std::map<std::string, std::pair<int, int>>>(*other._properties);
    }
    return *this;
}

Editor& Editor::operator=(Editor &&other) noexcept {
    if (this != &other) {
        _rules = other._rules;
        _npcs = other._npcs;
        _observers = other._observers;
        _size = other._size;
        _properties = other._properties;
    }
    return *this;
}

void Editor::add_npc(const std::string& type, const std::string& name, double x, double y) {
    auto npc = Factory::create_npc(type, name, x, y, _rules, _size);
    for (int i = 0; i < _observers->size; ++i)
        npc->add_observer(*(*_observers)[i]);
    _npcs->add(*npc);
}

void Editor::save(const std::string &filename) {
    std::ofstream output(filename);
    if (!output)
        throw FileNotExistsException("Error with open output file");

    for (int i = 0; i < _npcs->size - 1; ++i)
        (*_npcs)[i]->save(output);
    (*_npcs)[-1]->save(output, false);

    output.close();
}

void Editor::load(const std::string &filename) {
    std::ifstream input(filename);
    if (!input)
        throw FileNotExistsException("Input file is not exist");

    while (input.good()) {
        auto npc = Factory::load_npc(input, _rules, _size);
        for (int i = 0; i < _observers->size; ++i)
            npc->add_observer(*(*_observers)[i]);
        _npcs->add(*npc);
    }

    input.close();
}

void Editor::fight(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool test) {
    auto visitor = FightVisitor(attacker, defender);
    visitor.fight(test);
}

void Editor::print() const {
    std::lock_guard lock(stdout_mtx);
    for (int i = 0; i < _npcs->size; ++i)
        if ((*_npcs)[i]->status == ALIVE)
            std::cout << (*_npcs)[i]->get_type() << " " << (*_npcs)[i]->get_name() <<
                " X = " << (*_npcs)[i]->get_crds().x << " Y = " << (*_npcs)[i]->get_crds().y << std::endl;
    std::cout << "-----------------" << std::endl;
}

std::shared_ptr<Array<NPC>> Editor::get_npcs() {
    return std::make_shared<Array<NPC>>(Array(*_npcs));
}

bool Editor::empty() const {
    return _npcs->size == 0;
}

void Editor::move_and_analysis(int timeout) {
    while (!_stop) {
        for (int i = 0; i < _npcs->size; ++i) {
            auto now = (*_npcs)[i]->get_crds();
            auto distance = (*_properties)[(*_npcs)[i]->get_type()].first;

            if (now.x - distance > 0)
                (*_npcs)[i]->set_coords(Pair{now.x - distance, now.y});
            else if (now.x + distance < 0)
                (*_npcs)[i]->set_coords(Pair{now.x + distance, now.y});
            else if (now.y - distance > 0)
                (*_npcs)[i]->set_coords(Pair{now.x, now.y - distance});
            else if (now.y + distance > 0)
                (*_npcs)[i]->set_coords(Pair{now.x, now.y + distance});
        }

        for (int i = 0; i < _npcs->size; ++i) {
            if ((*_npcs)[i]->status == ALIVE) {
                auto now = (*_npcs)[i]->get_crds();
                auto type = (*_npcs)[i]->get_type();
                auto kill_distance = (*_properties)[(*_npcs)[i]->get_type()].first;

                for (int j = 0; j < _npcs->size; ++j)
                    if ((*_npcs)[j]->status == ALIVE && can_kill(type, (*_npcs)[j]->get_type(), _rules))
                        if (distance(now, (*_npcs)[j]->get_crds()) <= kill_distance) {
                            (*_npcs)[i]->status = BATTLER;
                            (*_npcs)[j]->status = BATTLER;
                            fight((*_npcs)[i], (*_npcs)[j]);
                            std::thread fight_thread(fight, (*_npcs)[i], (*_npcs)[j], false);
                            fight_thread.detach();
                            break;
                        }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
    }
}

void Editor::process(int timeout) {
    const auto start = std::time(nullptr);
    std::thread move_thread([this, timeout] { move_and_analysis(timeout); });
    while (true) {
        print();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (std::time(nullptr) - start >= 30)
            break;
    }
    _stop.store(true);
    move_thread.join();
}
