#include "systems/job_handler.hpp"
#include "data/job.hpp"


void JobHandler::handleMessage(SpaceCoords msg) {
    for (auto job : std::list<std::shared_ptr<Job>>(_currentJobs)) {
        if (job->completed(msg)) {
            // TODO: Get payed, get items, get reputation
            _currentJobs.remove(job);
        }
    }

}

void JobHandler::onPlayerMoved(SpaceCoords coords) {
    handleMessage(coords);
}