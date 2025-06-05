#pragma once

#include "core/renderable_3D.hpp"
#include "systems/player_vessel_moved_listener.hpp"
#include "data/world_map.hpp"

class WorldRenderer : public Renderable3D, public PlayerVesselMovedListener {
private:
    Color _color;
    Vector3 _worldPosition;
    Texture* _texture;
public:
    WorldRenderer() : Renderable3D(nullptr) 
    { }

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
        _worldPosition = { distance, 0, -distance * 3 };
        _texture = planet->getTexture();
        _model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *_texture;
    }

    void render() override {
        if (_model) {
            DrawModelEx(*_model, _worldPosition, {0, 1, 0},  GetTime() * 0.05f, {1, 1, 1}, _color);
        }
    }
};