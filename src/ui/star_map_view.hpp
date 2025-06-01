#pragma once

#include "core/renderable_UI.hpp"
#include "data/world_map.hpp"

class StarMapWorld {
private:
    World* _world;
    Vector2 _position;
public:
    World* getWorld() { return _world; }
    Vector2 getPosition() { return _position; }
    StarMapWorld() { }
    StarMapWorld(World* world, Vector2 position) { _world = world; _position = position; }
};

class StarMapView : public RenderableUI {
private:
    std::vector<StarMapWorld> _worlds; 
    RenderTexture _preRenderTexture;
public:
    StarMapView(int height) {
        auto worlds = WorldMap::getAll();
        _worlds.resize(worlds.size());
        std::transform(worlds.begin(), worlds.end(), _worlds.begin(), 
            [height](World* world) { 
                float x =  height * world->getCoords().getX() / SpaceCoords::bounds();
                float y =  height * world->getCoords().getY() / SpaceCoords::bounds();

                return StarMapWorld(world, { x, y }); 
            });

        auto tileTexture = Loaders::Texture.get("assets/textures/star_map.png");

        _preRenderTexture = LoadRenderTexture(height, height);
        BeginTextureMode(_preRenderTexture);

        int iHeight = height / 16;
        for (int y = 0; y < iHeight; y++) {
            for (int x = 0; x < iHeight; x++) {
                Rectangle rect = {16, 16, 16, 16};

                rect.x = ((x == iHeight - 1) ? 32 : ((x == 0) ? 0 : 16));
                rect.y = ((y == iHeight - 1) ? 32 : ((y == 0) ? 0 : 16));

                DrawTextureRec(*tileTexture, rect, {16.0f * x, 16.0f * y}, WHITE);
            }
        }
        EndTextureMode();
        
        _texture = new Texture();
        *_texture = _preRenderTexture.texture;
        _textureRect = { 0, 0, 1.0f * height, -1.0f * height };
    }
    
    ~StarMapView() {
        UnloadRenderTexture(_preRenderTexture);
    }

    virtual void render() override {
        // DrawTexturePro(*_texture, _textureRect, {0, 0, _textureRect.width * _scale, _textureRect.height * _scale }, {0.0f, 0.0f}, 0.0f, WHITE);
        // renderOne(_texture, _textureRect, {0, 0, _textureRect.width * _scale, _textureRect.height * _scale });
        
        RenderableUI::render();

        for (auto world : _worlds) {
            Planet* planet = dynamic_cast<Planet*>(world.getWorld());
            float radius = planet->getDiameter() / 2.0f;
            DrawSphere({ world.getPosition().x, world.getPosition().y + radius , 0}, radius, BLACK);
            DrawSphere({ world.getPosition().x, world.getPosition().y, 0}, radius, planet->getColor());
        }
    }
};