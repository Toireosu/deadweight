#pragma once

#include <list>
#include <memory>
#include "systems/player_vessel_moved_listener.hpp"

class Job;
class JobHandler : public PlayerVesselMovedListener {
private:
    std::list<std::shared_ptr<Job>> _currentJobs;
public:
    void addJob(std::shared_ptr<Job> job) {
        _currentJobs.push_back(job);
    }

    std::list<std::shared_ptr<Job>> getJobs() {
        return _currentJobs;
    }

    void handleMessage(SpaceCoords msg);

    void onPlayerMoved(SpaceCoords coords); 
};