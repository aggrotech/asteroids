#pragma once

#include "RenderableMesh.h"
#include "WindowsIncludes.h"

namespace Aggrotech
{
    class Window;

    class Renderer
    {
    public:

        Renderer(Window *window);

        ~Renderer();

        void Initialize();

        void Render();

        void Render(RenderableMesh mesh);

    private:

        void InitializeDevice();
    };
}