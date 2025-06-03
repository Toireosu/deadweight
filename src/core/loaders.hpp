#pragma once

#include "core/loader_base.hpp"
#include "core/texture_loader.hpp"
#include "core/audio_loaders.hpp"
#include "core/font_loader.hpp"

class Loaders {
public:
    static inline TextureLoader Texture;
    static inline SoundLoader Sound;
    static inline MusicLoader Music;
    static inline FontLoader Font;
};