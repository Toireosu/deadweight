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
    std::list<Criteria*> _criteria;
public:
    Job(std::string name, std::string description) {
        _name = name;
        _description = description;
    }

    Job(std::string name, std::string description, Criteria* criteria) 
        : Job(name, description) {
        _criteria.push_front(criteria);
    }

    ~Job() {
        for (auto criteria : _criteria)
            delete criteria;
    }


    std::string getName() { return _name; }

    std::string getDescription() { return _description; }

    void* getOwner() { return _owner; }

    bool completed(SpaceCoords msg) {
        for (auto criteria : _criteria) {
            if (!criteria->completed(msg))
                return false;
        }

        return true;
    }

    std::list<Criteria*> getCriteria() { return _criteria; }
};