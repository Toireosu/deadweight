#pragma once

#include <cctype>
#include <stdexcept>

class SpaceCoords {
protected:
    unsigned short _x;
    unsigned short _y;
public:
    SpaceCoords(unsigned short x, unsigned short y) {
        if (x > bounds() || y > bounds()) {
            throw new std::invalid_argument("Coordinate is outside of star system!");
        }

        _x = x;
        _y = y;
    }

    SpaceCoords() {
        _x = 0;
        _y = 0;
    }


    unsigned short getX() { return _x; }
    unsigned short getY() { return _y; }

    static unsigned short bounds() { return 1000; }

    bool operator==(SpaceCoords& other) const {
        return _x == other.getX() && _y == other.getY();
    }

    bool operator!=(SpaceCoords& other) const {
        return !(*this == other);
    }
};