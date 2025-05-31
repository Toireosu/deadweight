#pragma once

#include "core/loader_base.hpp"
#include <raylib.h>

class FontLoader : public LoaderBase<Font> {
    Font* load(const std::string& path) override {
        Font* font = new Font();
        *font = LoadFontEx(path.c_str(), 200, nullptr, 0);
        return font;
    }
};