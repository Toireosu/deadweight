#include "data/world.hpp"
#include "data/job.hpp"

std::vector<std::shared_ptr<Job>> World::fetchJobs() {
    return _jobs;
}

void World::addJob(std::shared_ptr<Job> job) {
    _jobs.push_back(job);
}