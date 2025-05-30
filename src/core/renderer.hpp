#pragma once

#include <raylib.h>

class RenderStack;
class Renderer {
private:
    static Camera* _camera;
    static int _width; 
    static int _height;
    static RenderTexture _renderTexture;
    static float _ratio;
    static Vector2 _pos;
public:
    static void init(int width, int height);
    static void calculateRatio(int width, int height);
    static Camera* getCamera() { return _camera; }
    static void setCamera(Camera* camera) { _camera = camera; }
    static void render(RenderStack&);
};