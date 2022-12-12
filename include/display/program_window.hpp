#include "display/base_window.hpp"

/**
 * Class Description: The Program Window class serves as the entry point to our program. It extends from the
 * Base Window class, and has a lot of the features of the application refactored into a few simple function calls.
 */
class ProgramWindow : public BaseWindow {
    public:

    /**
     * Program Window Constructor takes a width and height as well as a title as parameter arguments.
     * This will set the state of the program, and setup the window as the user has described.
     * @param width An integer value, representing the width of the program window.
     * @param height An integer value, representing the height of the program window.
     * @param title a string value, representing the title of the application. This is displayed on the
     * program window, in the top left corner.
     */
    ProgramWindow(int width, int height, std::string title) : BaseWindow(width, height, title) {};

    /**
     * The Initialize function simply sets up the GLFW Hints. It is the first thing
     * that is run when starting the window. Not to beconfused with the Run function, in the Base Window class.
     */
    void Initialize();
    /**
     *
     */
    void LoadContent();
    /**
     *
     */
    void Update();
    /**
     *
     */
    void Render();
    /**
     *
     */
    void Unload();
};