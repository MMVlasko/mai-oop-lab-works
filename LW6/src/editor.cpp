#include <fstream>
#include <iostream>

#include <editor.h>
#include <factory.h>
#include <visitor.h>

Editor::Editor(std::map<std::string, std::string> &rules) {
    _rules = std::make_shared<std::map<std::string, std::string>>(rules);
    _npcs = std::make_shared<Array<NPC>>(Array<NPC>());
    _observers = std::make_shared<Array<std::shared_ptr<Observer>>>(Array<std::shared_ptr<Observer>>());
}

Editor::Editor(const Editor &other) {
    _rules = std::make_shared<std::map<std::string, std::string>>(std::map(*other._rules));
    _npcs = std::make_shared<Array<NPC>>(Array(*other._npcs));
    _observers = std::make_shared<Array<std::shared_ptr<Observer>>>(Array(*other._observers));
}

Editor::Editor(Editor &&other) noexcept {
    _rules = other._rules;
    _npcs = other._npcs;
    _observers = other._observers;
}

Editor& Editor::operator=(const Editor &other) {
    if (this != &other) {
        _rules = std::make_shared<std::map<std::string, std::string>>(std::map(*other._rules));
        _npcs = std::make_shared<Array<NPC>>(Array(*other._npcs));
        _observers = std::make_shared<Array<std::shared_ptr<Observer>>>(Array(*other._observers));
    }
    return *this;
}

Editor& Editor::operator=(Editor &&other) noexcept {
    if (this != &other) {
        _rules = other._rules;
        _npcs = other._npcs;
        _observers = other._observers;
    }
    return *this;
}

void Editor::add_npc(const std::string& type, const std::string& name, double x, double y) {
    auto npc = Factory::create_npc(type, name, x, y, _rules);
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
        auto npc = Factory::load_npc(input, _rules);
        for (int i = 0; i < _observers->size; ++i)
            npc->add_observer(*(*_observers)[i]);
        _npcs->add(*npc);
    }

    input.close();
}

void Editor::fight(double max_distance) {
    auto visitor = FightVisitor(_npcs, max_distance, _rules);
    visitor.fight();
}

void Editor::print() const {
    for (int i = 0; i < _npcs->size; ++i) {
        std::cout << (*_npcs)[i]->get_type() << " " << (*_npcs)[i]->get_name() <<
            " X = " << (*_npcs)[i]->get_crds().x << " Y = " << (*_npcs)[i]->get_crds().y << std::endl;
    }
}

std::shared_ptr<Array<NPC>> Editor::get_npcs() {
    return std::make_shared<Array<NPC>>(Array(*_npcs));
}

bool Editor::empty() const {
    return _npcs->size == 0;
}