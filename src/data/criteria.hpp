#pragma once

class Criteria {
public:
    virtual bool completed(SpaceCoords msg) = 0;
};