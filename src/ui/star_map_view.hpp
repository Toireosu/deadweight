#pragma once

#include "core/renderable_UI.hpp"
#include "data/world_map.hpp"

class StarMapWorld {
private:
    World* _world;
    Vector2 _position;
    Vector2 _labelPosition;
    Vector2 _labelSize; 
    Vector2 _textPosition;
    Vector2 _labelAnchorPoint;
public:
    World* getWorld() { return _world; }
    Vector2 getPosition() { return _position; }
    Vector2 getLabelPosition() { return _labelPosition; }
    Vector2 getTextPosition() { return _textPosition; }
    Vector2 getLabelSize() { return _labelSize; }
    Vector2 getLabelAnchorPoint() { return _labelAnchorPoint; }
    StarMapWorld() { }
    StarMapWorld(World* world, Vector2 position, Vector2 labelPosition, Vector2 labelSize, Vector2 textPosition, Vector2 labelAnchorPoint) { 
        _world = world; 
        _position = position; 
        _labelPosition = labelPosition;
        _labelSize = labelSize;
        _textPosition = textPosition;
        _labelAnchorPoint = labelAnchorPoint;
    }
};

class StarMapView : public RenderableUI {
private:
    std::vector<StarMapWorld> _worlds; 
    RenderTexture _preRenderTexture;
    Font* _font;
    const float _worldLabelspacing = 0.8f;
    const float _worldLabelFontSize = 15;
    const float _labelMargin = 1;
public:
    StarMapView(int height) {
        _font = Loaders::Font.get("assets/fonts/VT323-Regular.ttf");

        auto worlds = WorldMap::getAll();
        _worlds.resize(worlds.size());
        std::transform(worlds.begin(), worlds.end(), _worlds.begin(), 
            [height, this](World* world) { 
                float x =  height * world->getCoords().getX() / SpaceCoords::bounds();
                float y =  height * world->getCoords().getY() / SpaceCoords::bounds();

                // Temp
                float worldRadius = ((Planet*)world)->getDiameter() / 2;
                auto textSize = MeasureTextEx(*_font, world->getName().c_str(), _worldLabelFontSize, _worldLabelspacing);
                // Label anchor setup
                Vector2 labelAnchor = { 0, 0};
                
                // Trying to calculate an appropriate placement for text
                // centering 
                float textX = x;
                float textY = y;
                // moving right and left
                if (x < height / 2) {
                    textX += worldRadius;
                    labelAnchor.x = 0;
                } else {
                    textX -= worldRadius + textSize.x;
                    labelAnchor.x = 1;
                }
                // moving up and down
                if (y < height / 2) {
                    textY += worldRadius;
                    labelAnchor.y = 0;
                } else {
                    textY -= worldRadius + textSize.y;
                    labelAnchor.y = 1;
                }

                Vector2 textPosition = { textX, textY };
                Vector2 labelPosition = Vector2Subtract(textPosition, { _labelMargin, _labelMargin });
                textSize = Vector2Add(textSize, { _labelMargin * 2, _labelMargin * 2 });

                labelAnchor = Vector2Add(labelPosition, Vector2Multiply(labelAnchor, textSize));

                return StarMapWorld(
                    world, 
                    { x, y },
                    labelPosition,
                    textSize,
                    textPosition,
                    labelAnchor
                ); 
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
            Vector2 position = world.getPosition(); 
            DrawSphere({ position.x, position.y + radius , 0}, radius, BLACK);
            DrawSphere({ position.x, position.y, 0}, radius, planet->getColor());

            auto labelAnchor = world.getLabelAnchorPoint();
            DrawLine(labelAnchor.x, labelAnchor.y, position.x, position.y, GREEN);

            auto labelPosition = world.getLabelPosition();
            auto labelSize = world.getLabelSize();
            DrawRectangle(labelPosition.x, labelPosition.y, labelSize.x, labelSize.y, GRAY);
            DrawTextEx(*_font, planet->getName().c_str(), world.getTextPosition(), _worldLabelFontSize, _worldLabelspacing, GREEN);
        }
    }
};