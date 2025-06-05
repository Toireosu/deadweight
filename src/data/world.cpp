#include "data/world.hpp"
#include "data/job.hpp"

std::vector<std::shared_ptr<Job>> World::fetchJobs() {
    return std::vector<std::shared_ptr<Job>> {
        std::make_shared<Job>("Test Job", "Testing a job"),
    };
}