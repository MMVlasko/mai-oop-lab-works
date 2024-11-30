#include <map>

#include <exceptions.h>
#include <factory.h>
#include <tools.h>
#include <npc.h>

std::shared_ptr<NPC> Factory::create_npc(const std::string &type, const std::string &name, double x, double y,
        const std::shared_ptr<std::map<std::string, std::string>>& rules, double size) {
    if (correct_npc_type(type, rules)) {
        if (x >= 0 && x <= size && y >= 0 && y <= size)
            return std::make_shared<NPC>(type, name, x, y);
        throw InvalidCoordinatesExceptions("Coordinates must be between 0 and " + std::to_string(size));
    }
    throw UnknownNPCTypeException("Incorrect NPC type");
}

std::shared_ptr<NPC> Factory::load_npc(std::istream &is,
        const std::shared_ptr<std::map<std::string, std::string>>& rules, double size) {
    std::string type, name, x, y;
    is >> type >> name >> x >> y;
    try {
        if (correct_npc_type(type, rules)) {
            if (stod(x) >= 0 && stod(x) <= size && stod(y) >= 0 && stod(y) <= size)
                return std::make_shared<NPC>(type, name, stod(x), stod(y));
            throw InvalidCoordinatesExceptions("Coordinates must be between 0 and " + std::to_string(size));
        }
        throw UnknownNPCTypeException("Incorrect NPC type");
    } catch (std::invalid_argument&) {
        throw InvalidCoordinatesExceptions("Coordinates must be double");
    }
}