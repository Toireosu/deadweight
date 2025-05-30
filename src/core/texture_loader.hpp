#pragma once

#include "core/loader_base.hpp"
#include <raylib.h>


class TextureLoader : public LoaderBase<Texture> {
protected:
    Texture* load(const std::string& path) override {
        Texture* texture = new Texture();
        *texture = LoadTexture(path.c_str());
        return texture;
    }
};