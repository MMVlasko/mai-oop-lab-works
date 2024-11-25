#include <fstream>
#include <iostream>

#include <editor.h>
#include <factory.h>
#include <visitor.h>

Editor::Editor() {
    _npcs = std::make_shared<Array<NPC>>(Array<NPC>());
    _observers = std::make_shared<Array<std::shared_ptr<Observer>>>(Array<std::shared_ptr<Observer>>());
}

Editor::Editor(const Editor &other) {
    _npcs = std::make_shared<Array<NPC>>(Array(*other._npcs));
    _observers = std::make_shared<Array<std::shared_ptr<Observer>>>(Array(*other._observers));
}

Editor::Editor(Editor &&other) noexcept {
    _npcs = other._npcs;
    _observers = other._observers;
}

Editor& Editor::operator=(const Editor &other) {
    if (this != &other) {
        _npcs = std::make_shared<Array<NPC>>(Array(*other._npcs));
        _observers = std::make_shared<Array<std::shared_ptr<Observer>>>(Array(*other._observers));
    }
    return *this;
}

Editor& Editor::operator=(Editor &&other) noexcept {
    if (this != &other) {
        _npcs = other._npcs;
        _observers = other._observers;
    }
    return *this;
}

void Editor::add_npc(const std::string& type, const std::string& name, double x, double y) {
    _npcs->add(*Factory::create_npc(type, name, x, y));
}

void Editor::save(const std::string &filename) {
    std::ofstream input(filename);
    if (!input)
        throw FileNotExistsException("Error with open output file");

    for (int i = 0; i < _npcs->size - 1; ++i)
        (*_npcs)[i]->save(input);
    (*_npcs)[-1]->save(input, false);

    input.close();
}

void Editor::load(const std::string &filename) {
    std::ifstream input(filename);
    if (!input)
        throw FileNotExistsException("Input file is not exist");

    while (input.good())
        _npcs->add(*Factory::load_npc(input));

    input.close();
}

void Editor::fight(double max_distance) {
    auto visitor = FightVisitor(_npcs, max_distance, _observers);
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