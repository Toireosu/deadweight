#pragma once

class SpaceCoords {
protected:
    unsigned short _x;
    unsigned short _y;
public:
    SpaceCoords(unsigned short x, unsigned short y) {
        _x = x;
        _y = y;
    }

    unsigned short getX() { return _x; }
    unsigned short getY() { return _y; }

    bool operator==(SpaceCoords& other) const {
        return _x == other.getX() && _y == other.getY();
    }

    bool operator!=(SpaceCoords& other) const {
        return !(*this == other);
    }
};