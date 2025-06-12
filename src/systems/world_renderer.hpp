#pragma once

#include "core/renderable_3D.hpp"
#include "systems/player_vessel_moved_listener.hpp"
#include "data/world_map.hpp"
#include "core/loaders.hpp"
#include <stdexcept>

class WorldRenderer : public Renderable3D, public PlayerVesselMovedListener {
private:
    Color _color;
    Vector3 _worldPosition;
    Texture* _texture;
    Model* _sky;
    Music* _cockpitSounds;
    Shader _planetShader;
public:
    WorldRenderer() : Renderable3D(nullptr) 
    { 
        _sky = new Model(LoadModelFromMesh(GenMeshPlane(854.0f, 640.0f, 1, 1)));
        _sky->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *Loaders::Texture.get("assets/textures/world_background.png");
        _cockpitSounds = Loaders::Music.get("assets/audio/music/cockpit_interior.wav");
        PlayMusicStream(*_cockpitSounds); 

        _planetShader = LoadShader("assets/shaders/light.vs", "assets/shaders/light.fs");
    }

    void update() override {
        UpdateMusicStream(*_cockpitSounds);
    }

    void onPlayerMoved(SpaceCoords coords) override {
        delete _model;
        _model = nullptr;
        
        auto world = WorldMap::getWorldByCoords(coords);

        auto planet = dynamic_cast<Planet*>(world);

        if (planet == nullptr)
            return;
        
        float distance = 100.0f;
        auto size = planet->getDiameter() / 2 * 10.0f;
        _model = new Model(LoadModelFromMesh(GenMeshSphere(size, 16, 16)));
        _color = planet->getColor();
        _worldPosition = { distance, -distance * 3, 0 };
        _texture = planet->getTexture();
        _model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *_texture;
        _model->materials[0].shader = _planetShader;
    }

    void render() override {
        DrawModelEx(*_sky, {0, -500, 0}, {0, 0, 0}, 0.0f, {1, 1, 1}, WHITE);
        if (_model) {
            DrawModelEx(*_model, _worldPosition, {0, 1, 0},  GetTime() * 0.05f, {1, 1, 1}, _color);
        }
    }
};