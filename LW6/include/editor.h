#pragma once

#include "array.h"
#include "npcs.h"

class Editor {
    std::shared_ptr<Array<NPC>> _npcs;
    std::shared_ptr<Array<std::shared_ptr<Observer>>> _observers;

    public:
        Editor();

        Editor(const Editor &other);

        Editor(Editor &&other) noexcept;

        Editor &operator=(const Editor &other);

        Editor &operator=(Editor &&other) noexcept;

        void add_npc(const std::string& type, const std::string& name, double x, double y);

        template <class ObserverT>
        void add_observer(std::shared_ptr<ObserverT> &observer);

        void save(const std::string &filename);

        void load(const std::string &filename);

        void fight(double max_distance);

        void print() const;

        std::shared_ptr<Array<NPC>> get_npcs();

        bool empty() const;
};

template <class ObserverT>
void Editor::add_observer(std::shared_ptr<ObserverT> &observer) {
    _observers->add(observer);
}