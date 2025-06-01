#pragma once

#include "data/world.hpp"
#include "data/planet.hpp"
#include "data/factions.hpp"
#include <list>
#include <string>

#include "utils/string_utils.hpp"

class WorldMap {
private:
    static inline std::list<World*> _internal; 
public:

    static void add(World* world) {
        // Make sure name and coordinates are unique
    }

    static void init() {
        _internal.push_back(new Planet("Peronie", Factions::Union, SpaceCoords(100, 120), "Capital of the Union.", 12000000000U, 23.0f, BLUE));
        _internal.push_back(new Planet("Valesh", Factions::Confederacy, SpaceCoords(230, 120), "Home planet of the Confederacy.", 700000000U, 46.0f, RED));
    }

    static World* getWorldByName(std::string name) {
        for (auto world : _internal) {
            if (StringUtilites::equalsCaseInsensitve(world->getName(), name))
                return world;
        }

        return nullptr;
    } 

    static World* getWorldByCoords(SpaceCoords coords) {
        for (auto world : _internal) {
            if (world->getCoords() == coords)
                return world;
        }

        return nullptr;
    }
};