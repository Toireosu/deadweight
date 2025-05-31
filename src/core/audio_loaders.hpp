#pragma once

#include "core/loader_base.hpp"
#include <raylib.h>

class SoundLoader : public LoaderBase<Sound> {
protected:
    Sound* load(const std::string& path) override {
        Sound* sound = new Sound();
        *sound = LoadSound(path.c_str());
        return sound;
    }
};

class MusicLoader : public LoaderBase<Music> {
protected:
    Music* load(const std::string& path) override {
        Music* music = new Music();
        *music = LoadMusicStream(path.c_str());
        return music;
    }
};