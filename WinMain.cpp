#include "Window.h"
#include "Renderer.h"
#include "WindowsIncludes.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Aggrotech::Window window("aggrotech::asteroids", 0, 0, 640, 480, lpCmdLine, nCmdShow);
    Aggrotech::Renderer renderer(&window);

    return window.Run();
}
