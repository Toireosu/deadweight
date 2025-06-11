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
        _internal.push_back(world);
    }

    static void populateJobs();

    static void init() {
        add(new Planet("Peronie", Factions::Union, SpaceCoords(100, 120), "Capital of the Union.", 12000000000U, 23.0f, BLUE));
        add(new Planet("Valesh", Factions::Confederacy, SpaceCoords(800, 600), "Home planet of the Confederacy.", 700000000U, 46.0f, RED));
        add(new Planet("Vera", Factions::Confederacy, SpaceCoords(750, 700), "Moon of Valesh", 8000U, 9.0f, GRAY));
        add(new Planet("Sarakiel", Factions::Syndicates, SpaceCoords(700, 230), "Mining planet.", 8000000U, 17.0f, ORANGE));

        populateJobs();
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

    static const std::list<World*>& getAll() { return _internal; }
};