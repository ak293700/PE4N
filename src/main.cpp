#include "MainManager/MainManager.h"
#include "Drawers/Colors.h"

int main()
{
    MainManager::Init(600, 600);

    // Define the 12 triangles of the cube
    Mesh cube = {
            {
                    // South
                    {{0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}},
                    {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},

                    // East
                    {{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
                    {{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},

                    // North
                    {{1.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
                    {{1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},

                    // West
                    {{0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
                    {{0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},

                    // Top
                    {{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
                    {{0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 0.0f}},

                    // Bottom
                    {{1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}},
                    {{1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}
            }
    };
    MainManager::scene.meshes.push_back(cube);

    Mesh triangle = {
            {

                    {{0.0f, 1.0f, 0.0f}, {0.5f, 1.5f, 0.5f}, {1.0f, 1.0f, 0.0f}},
                    {{1.0f, 1.0f, 1.0f}, {0.5f, 1.5f, 0.5f}, {0.0f, 1.0f, 1.0f}},
                    {{1.0f, 1.0f, 0.0f}, {0.5f, 1.5f, 0.5f}, {1.0f, 1.0f, 1.0f}},
                    {{0.0f, 1.0f, 1.0f}, {0.5f, 1.5f, 0.5f}, {0.0f, 1.0f, 0.0f}}
            }

    };
    MainManager::scene.meshes.push_back(triangle);

    MainManager::Main();

    MainManager::Quit();

    return 0;
}
