#pragma once

#include "core/loader_base.hpp"
#include "core/texture_loader.hpp"
#include "core/audio_loaders.hpp"
#include "core/font_loader.hpp"

namespace Loaders {
    TextureLoader Texture;
    SoundLoader Sound;
    MusicLoader Music;
    FontLoader Font;
}