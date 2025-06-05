#pragma once

#include "data/criteria.hpp"

#include <string>
#include <list>

class Job {
private:
    std::string _name;
    std::string _description;
    void* _owner; // TODO: pointer to npc
    std::string _questTag;
    std::list<Criteria> _criteria;
public:
    Job(std::string name, std::string description) {
        _name = name;
        _description = description;
    }

    std::string getName() { return _name; }

    std::string getDescription() { return _description; }

    void* getOwner() { return _owner; }

    bool completed() { 
        // When completed
        // Tell listeners
        return false;
    }

    std::list<Criteria> getCriteria() { return _criteria; }
};