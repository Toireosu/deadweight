#pragma once 

#include "data/space_coords.hpp"

class PlayerVesselMovedListener {
public:
    virtual void onPlayerMoved(SpaceCoords coords) = 0;
};