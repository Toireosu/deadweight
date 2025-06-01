#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

class StringUtilites {
public:
    static std::string upperCase(std::string input) {
        std::string upper = input;
        std::transform(upper.begin(), upper.end(), upper.begin(),
                       [](unsigned char c) { return std::toupper(c); });

        return upper;
    }

    static std::string lowerCase(std::string input) {
        std::string lower = input;
        std::transform(lower.begin(), lower.end(), lower.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        return lower;
    }

    static std::vector<std::string> split(std::string input, char delimiter) {
        auto segs = std::vector<std::string>(10);
        std::stringstream stringStream(input);
        std::string seg;
        while (getline(stringStream, seg, delimiter))
            segs.push_back(seg);

        return segs;
    }

    static bool equalsCaseInsensitve(std::string s0, std::string s1) {
        return upperCase(s0) == upperCase(s1);
    }
};