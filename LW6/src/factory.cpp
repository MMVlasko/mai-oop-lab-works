#include <map>

#include <exceptions.h>
#include <factory.h>
#include <tools.h>
#include <npc.h>

std::shared_ptr<NPC> Factory::create_npc(const std::string &type, const std::string &name, double x, double y,
        const std::shared_ptr<std::map<std::string, std::string>>& rules) {
    if (correct_npc_type(type, rules)) {
        if (x >= 0 && x <= 500 && y >= 0 && y <= 500)
            return std::make_shared<NPC>(type, name, x, y);
        throw InvalidCoordinatesExceptions("Coordinates must be between 0 and 500");
    }
    throw UnknownNPCTypeException("Incorrect NPC type");
}

std::shared_ptr<NPC> Factory::load_npc(std::istream &is,
        const std::shared_ptr<std::map<std::string, std::string>>& rules) {
    std::string type, name, x, y;
    is >> type >> name >> x >> y;
    try {
        if (correct_npc_type(type, rules)) {
            if (stod(x) >= 0 && stod(x) <= 500 && stod(y) >= 0 && stod(y) <= 500)
                return std::make_shared<NPC>(type, name, stod(x), stod(y));
            throw InvalidCoordinatesExceptions("Coordinates must be between 0 and 500");
        }
        throw UnknownNPCTypeException("Incorrect NPC type");
    } catch (std::invalid_argument&) {
        throw InvalidCoordinatesExceptions("Coordinates must be double");
    }
}