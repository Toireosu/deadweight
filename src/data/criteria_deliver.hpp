#pragma once

#include "data/criteria.hpp"
#include "data/world.hpp"
#include "data/world_map.hpp"

// Temp for now, should contain what items to deliver
class CriteriaDeliver : public Criteria {
private:
    World* _world;
public:
    CriteriaDeliver(World* world) {
        _world = world;
    }

    bool completed(SpaceCoords msg) override {
        if (WorldMap::getWorldByCoords(msg) == _world)
            return true;
        return false;
    }
};