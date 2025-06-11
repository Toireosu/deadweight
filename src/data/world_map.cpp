#include "data/world_map.hpp"

#include <memory>
#include "data/job.hpp"
#include "data/criteria_deliver.hpp"

void WorldMap::populateJobs() {
    getWorldByName("Valesh")->addJob(std::make_shared<Job>(
        "Vera Delivery", 
        "Deliver some goods from Valesh to Vera.", 
        new CriteriaDeliver(getWorldByName("Vera"))));

    getWorldByName("Sarakiel")->addJob(std::make_shared<Job>(
        "Peronie Mule", 
        "Smuggle some merchandize from Sarakiel to Peronie.", 
        new CriteriaDeliver(getWorldByName("Peronie"))));
}