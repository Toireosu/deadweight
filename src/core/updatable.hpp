#pragma once

class Updatable {
protected:
    bool _shouldUpdate = true;
public:
    void setShouldUpdate(bool shouldUpdate) { _shouldUpdate = shouldUpdate; }
    bool getShouldUpdate() { return _shouldUpdate; }

    void runUpdate() { 
        if (_shouldUpdate)
            update();
    }
    virtual void update() { }
};