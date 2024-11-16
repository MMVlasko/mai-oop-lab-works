#include <exceptions.h>
#include <factory.h>
#include <npcs.h>

std::shared_ptr<NPC> Factory::create_npc(const std::string &type, const std::string &name, double x, double y) {
    if (type == "bear" || type == "werewolf" || type == "robber") {
        if (x >= 0 && x <= 500 && y >= 0 && y <= 500)
            return std::make_shared<NPC>(type, name, x, y);
        throw InvalidCoordinatesExceptions("Coordinates must be between 0 and 500");
    }
    throw UnknownNPCTypeException("Must be 'bear', 'werewolf' or 'robber'");
}

std::shared_ptr<NPC> Factory::load_npc(std::istream &is) {

    std::string type, name, x, y;
    is >> type >> name >> x >> y;
    try {
        if (type == "bear" || type == "werewolf" || type == "robber") {
            if (stod(x) >= 0 && stod(x) <= 500 && stod(y) >= 0 && stod(y) <= 500)
                return std::make_shared<NPC>(type, name, stod(x), stod(y));
            throw InvalidCoordinatesExceptions("Coordinates must be between 0 and 500");
        }
        throw UnknownNPCTypeException("Must be 'bear', 'werewolf' or 'robber'");
    } catch (std::invalid_argument&) {
        throw InvalidCoordinatesExceptions("Coordinates must be double");
    }
}
