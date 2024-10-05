#pragma once
#include <iostream>

extern ZeroEngine::Application* ZeroEngine::CreateApplication(int argc, char** argv);
bool g_ApplicationRunning = true;

namespace ZeroEngine
{
    int Main(int argc, char** argv)
    {
        // Your application loop
        while (g_ApplicationRunning)
        {
            ZeroEngine::Application* app = ZeroEngine::CreateApplication(argc, argv);
            app->Run();
            delete app;
        }
        return 0;
    }

}

#if defined(WL_PLATFORM_WINDOWS) && !defined(WL_HEADLESS) && defined(WL_DIST)
#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    return ZeroEngine::Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
    return ZeroEngine::Main(argc, argv);
}

#endif // defined(WL_PLATFORM_WINDOWS) && defined(WL_DIST)