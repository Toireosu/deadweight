#pragma once

#include "data/space_coords.hpp"
#include "systems/player_vessel_moved_listener.hpp"
#include "data/storable.hpp"
#include <list>

class PlayerVessel {
    SpaceCoords _coords;
    std::list<Storable*> _storage; 
    std::list<PlayerVesselMovedListener*> _listeners;
public: 
    PlayerVessel(SpaceCoords coords) {
        _coords = coords;
    }

    void hasMovedCoords() {
        for (auto listener : _listeners) {
            listener->onPlayerMoved(_coords);
        }
    }

    void jump(SpaceCoords coords) {
        _coords = coords;
        hasMovedCoords();
    }

    SpaceCoords getCoords() { return _coords; }
    void addListener(PlayerVesselMovedListener* listener) {
        _listeners.push_front(listener);
    }
    
    std::list<Storable*> getStorage() { return _storage; }
    void addStorable(Storable* storable) {
        _storage.push_front(storable);
    }

};