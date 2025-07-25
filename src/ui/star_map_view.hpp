#pragma once

#include "core/renderable_UI.hpp"
#include "data/world_map.hpp"
#include "core/loaders.hpp"
#include "data/player_vessel.hpp"
#include "ui/star_map_world.hpp"

class StarMapView : public RenderableUI {
private:
    std::vector<StarMapWorld> _worlds; 
    World* _hoveredWorld = nullptr;
    RenderTexture _preRenderTexture;
    Font* _font;
    const float _worldLabelspacing = 0.8f;
    const float _worldLabelFontSize = 15;
    const float _labelMargin = 1;
    int _sideSize = 0;
    PlayerVessel* _vessel;

    int _height;

    Vector2 spaceCoordsToVector(SpaceCoords coords) {
        float x = _height * coords.getX() / SpaceCoords::bounds();
        float y = _height * coords.getY() / SpaceCoords::bounds();

        return { x, y };
    }

    struct ColorScheme { Color world, label, text; };
public:
    StarMapView(int height, PlayerVessel* vessel) {
        _font = Loaders::Font.get("assets/fonts/VT323-Regular.ttf");
        _vessel = vessel;
        _height = height;

        auto worlds = WorldMap::getAll();
        _worlds.resize(worlds.size());
        std::transform(worlds.begin(), worlds.end(), _worlds.begin(), 
            [height, this](World* world) { 
                Vector2 worldSpace = spaceCoordsToVector(world->getCoords());

                float x = worldSpace.x;
                float y = worldSpace.y;

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

        _sideSize = height;
    }
    
    ~StarMapView() {
        UnloadRenderTexture(_preRenderTexture);
    }

    virtual bool handleMouse(Vector2 coords, bool left, bool right) {
        for (auto world : _worlds) {
            if (Vector2Distance(coords, world.getPosition()) < world.getRadius()) {
                _hoveredWorld = world.getWorld();
                return true;
            }
        }
        
        _hoveredWorld = nullptr;

        return true;
    }
    
    ColorScheme getColorScheme(Color worldColor, bool hovered) {
        return hovered ? ColorScheme(WHITE, WHITE, BLACK) : ColorScheme(worldColor, GRAY, GREEN);
    }

    virtual void render() override {
        // DrawTexturePro(*_texture, _textureRect, {0, 0, _textureRect.width * _scale, _textureRect.height * _scale }, {0.0f, 0.0f}, 0.0f, WHITE);
        // renderOne(_texture, _textureRect, {0, 0, _textureRect.width * _scale, _textureRect.height * _scale });
        
        RenderableUI::render();

        for (auto world : _worlds) {
            Planet* planet = dynamic_cast<Planet*>(world.getWorld());

            bool isHovered = (world.getWorld() == _hoveredWorld);
            auto colorScheme = getColorScheme(planet->getColor(), isHovered);

            // Rendering planet
            float radius = planet->getDiameter() / 2.0f;
            Vector2 position = world.getPosition(); 
            DrawSphere({ position.x, position.y + radius , 0}, radius, BLACK);
            DrawSphere({ position.x, position.y, 0}, radius, colorScheme.world);

            // Rendering arrow
            auto labelAnchor = world.getLabelAnchorPoint();
            DrawLine(labelAnchor.x, labelAnchor.y, position.x, position.y, colorScheme.text);

            // Rendering label
            auto labelPosition = world.getLabelPosition();
            auto labelSize = world.getLabelSize();
            DrawRectangle(labelPosition.x, labelPosition.y, labelSize.x, labelSize.y, colorScheme.label);
            DrawTextEx(*_font, planet->getName().c_str(), world.getTextPosition(), _worldLabelFontSize, _worldLabelspacing, colorScheme.text);
        }

        if (_hoveredWorld != nullptr) {
            int tabSize = 100;
            float yDiff = 30;
            DrawTextEx(*_font, _hoveredWorld->getName().c_str(), { 1.0f * _sideSize, 0 }, _worldLabelFontSize, _worldLabelspacing, GREEN);
            DrawTextEx(*_font, "FACTION: ", { 1.0f * _sideSize, yDiff }, _worldLabelFontSize, _worldLabelspacing, GREEN);
            DrawTextEx(*_font, _hoveredWorld->getFaction()->getAcronym().c_str(), { 1.0f * _sideSize + tabSize, yDiff }, _worldLabelFontSize, _worldLabelspacing, GREEN);
        }

        Vector2 playerPos = spaceCoordsToVector(_vessel->getCoords());

        DrawRectangle(playerPos.x, playerPos.y, 10, 10, GREEN);
    }
};