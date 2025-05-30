#pragma once

#include <string>
#include <map>

template <typename T>
class LoaderBase {
private:
    std::map<std::string, T*> _cache;
protected: 
    virtual T* load(const std::string& path) = 0;
public:
    T* get(const std::string& path) {
        if (_cache.count(path))
            return _cache[path];

        auto t = load(path);
        _cache[path] = t;
        return t;
    }
};