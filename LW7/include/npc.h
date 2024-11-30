#pragma once

#include <string>

#include "visitor.h"
#include "observer.h"
#include "array.h"

typedef enum {
    ALIVE,
    BATTLER,
    KILLED
} Status;

struct Pair {
    double x;
    double y;
};

class BaseNPC {
    protected:
        std::shared_ptr<Array<std::shared_ptr<Observer>>> _observers;

    public:
        virtual void accept(Visitor &visitor) = 0;

        virtual void notify(BaseNPC&) = 0;

        [[nodiscard]] virtual std::string get_type() const = 0;

        [[nodiscard]] virtual std::string get_name() const = 0;

        [[nodiscard]] virtual Pair get_crds() const = 0;

        virtual ~BaseNPC() = default;
};

class NPC : public BaseNPC {
    std::string _type, _name;
    double _x, _y;

    public:
        Status status;

        NPC(std::string type, std::string name, double x, double y);

        NPC(const NPC &other) = default;

        NPC(NPC &&other) = default;

        NPC &operator=(const NPC &other);

        NPC &operator=(NPC &&other) noexcept;

        template <class ObserverT>
        void add_observer(std::shared_ptr<ObserverT> observer);

        void accept(Visitor &visitor) override;

        void notify(BaseNPC &other) override;

        void save(std::ofstream &os, bool nl = true) const;

        [[nodiscard]] std::string get_type() const override;

        [[nodiscard]] std::string get_name() const override;

        [[nodiscard]] Pair get_crds() const override;

        void set_coords(const Pair &crds);
};

template <class ObserverT>
void NPC::add_observer(std::shared_ptr<ObserverT> observer) {
    _observers->add(observer);
}