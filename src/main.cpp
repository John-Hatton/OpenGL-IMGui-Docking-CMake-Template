#include "display/game_window.hpp"

int main() {
    // Create the game window with the specified size and title
    GameWindow gw = GameWindow{ 1920, 1080, "OpenGL-IMGui-Docking-CMake-Template by @InverseDerivative" };
    return gw.Run();
}