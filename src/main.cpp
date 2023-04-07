#include "Application/Application.h"
#include "Drawers/Colors.h"

int main() {

    Application::Init(800, 800);
    Scene scene;
//    scene.camera = Camera(0.1f, 1000.0f, 90.0f, {0.0f, 0.0f, 0.0f});
    scene = Scene(Camera(0.1f, 1000.0f, 90.0f, {0.0f, 0.0f, 0.0f}));
    Application::scene = &scene;
    scene.Init();

    Mesh triangle = {
            {
                    {{0.0f, 1.0f, 0.0f}, {0.5f, 1.5f, 0.5f}, {1.0f, 1.0f, 0.0f}},
                    {{1.0f, 1.0f, 1.0f}, {0.5f, 1.5f, 0.5f}, {0.0f, 1.0f, 1.0f}},
                    {{1.0f, 1.0f, 0.0f}, {0.5f, 1.5f, 0.5f}, {1.0f, 1.0f, 1.0f}},
                    {{0.0f, 1.0f, 1.0f}, {0.5f, 1.5f, 0.5f}, {0.0f, 1.0f, 0.0f}}
            }

    };
//    Application::scene->meshes.push_back(triangle);

    Application::Main();

    Application::Quit();

    return 0;
}
