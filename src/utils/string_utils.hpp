#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

namespace StringUtilites {
    std::string upperCase(std::string input) {
        std::string upper = input;
        std::transform(upper.begin(), upper.end(), upper.begin(),
                       [](unsigned char c) { return std::toupper(c); });

        return upper;
    }

    std::vector<std::string> split(std::string input, char delimiter) {
        auto segs = std::vector<std::string>(10);
        std::stringstream stringStream(input);
        std::string seg;
        while (getline(stringStream, seg, delimiter))
            segs.push_back(seg);

        return segs;
    }
};