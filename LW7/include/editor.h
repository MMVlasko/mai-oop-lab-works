#pragma once

#include <map>
#include <atomic>

#include "array.h"
#include "npc.h"

class Editor {
    std::shared_ptr<Array<NPC>> _npcs;
    std::shared_ptr<Array<std::shared_ptr<Observer>>> _observers;
    std::shared_ptr<std::map<std::string, std::string>> _rules;
    std::shared_ptr<std::map<std::string, std::pair<int, int>>> _properties;
    double _size;
    std::atomic<bool> _stop;

    public:
        explicit Editor(std::map<std::string, std::string> &rules,
            std::map<std::string, std::pair<int, int>> &properties, double size, bool gen = true);

        Editor(const Editor &other);

        Editor(Editor &&other) noexcept;

        Editor &operator=(const Editor &other);

        Editor &operator=(Editor &&other) noexcept;

        void add_npc(const std::string& type, const std::string& name, double x, double y);

        template <class ObserverT>
        void add_observer(std::shared_ptr<ObserverT> &observer);

        void save(const std::string &filename);

        void load(const std::string &filename);

        static void fight(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender,
            bool test = false);

        void print() const;

        std::shared_ptr<Array<NPC>> get_npcs();

        [[nodiscard]] bool empty() const;

        void move_and_analysis(int timeout);

        void process(int timeout = 300);
};

template <class ObserverT>
void Editor::add_observer(std::shared_ptr<ObserverT> &observer) {
    _observers->add(observer);
    for (int i = 0; i < _npcs->size; ++i)
        (*_npcs)[i]->add_observer(observer);
}