#include "display/program_window.hpp"

int main() {
    // Create the game window with the specified size and title
    ProgramWindow pw = ProgramWindow{ 1920, 1080, "OpenGL-IMGui-Docking-CMake-Template by @InverseDerivative" };
    return pw.Run();
}