#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>
#include <RmlUi_Backend.h>
#include "RmlShell.h"
#include "UIMain.h"
#include "Logger.h"

namespace UI
{
    HWND hParentWindow = nullptr;
    Rml::Context* context = nullptr;
    bool running = true;

    void Init()
    {
        Logger::WriteMessage(L"Core UI Start init");

        //Find main window
        Logger::WriteMessage(L"Core UI Find MainWindow to inject");
        hParentWindow = FindWindowA("Rangers MainClassName", "Rangers");

        Logger::WriteMessage(L"Core UI Init backend");
        // Constructs the system and render interfaces, creates a window, and attaches the renderer.
        if (!RmlBackend::Initialize(hParentWindow))
        {
            Logger::WriteMessageError(L"Failed Init backend");
            return;
        }

        
        // Install the custom interfaces constructed by the backend before initializing RmlUi.
        Logger::WriteMessage(L"Core UI Init set system interface");
        Rml::SetSystemInterface(RmlBackend::GetSystemInterface());
        Logger::WriteMessage(L"Core UI Init set render interface");
        Rml::SetRenderInterface(RmlBackend::GetRenderInterface());

        Logger::WriteMessage(L"Core UI Initialize");
        // RmlUi initialisation.
        Rml::Initialise();


        Logger::WriteMessage(L"Core UI Init resolution");
        RECT rect;
        GetWindowRect(hParentWindow, &rect);
        int window_width = 444;
        int window_height = 444;


        Logger::WriteMessage(L"Core UI Init context");
        // Create the main RmlUi context.
        context = Rml::CreateContext("main", Rml::Vector2i(window_width, window_height));
        if (!context)
        {
            Logger::WriteMessageError(L"Failed Init context");
            Rml::Shutdown();
            RmlBackend::Shutdown();
            return;
        }

        Logger::WriteMessage(L"Core UI Init debugger");
        // The RmlUi debugger is optional but very useful. Try it by pressing 'F8' after starting this sample.
        Rml::Debugger::Initialise(context);
        
        Logger::WriteMessage(L"Core UI Load default fonts");
        // Fonts should be loaded before any documents are loaded.
        RmlShell::LoadDefaultFonts();

        Logger::WriteMessage(L"Core UI Load demo document");
        // Load and show the demo document.
        if (Rml::ElementDocument* document = context->LoadDocument("assets/demo.rml")) document->Show();
        else Logger::WriteMessageError(L"Core UI Failed Load Document");

        while (running)
        {
            // Handle input and window events.
            running = RmlBackend::ProcessEvents(context, &RmlShell::ProcessKeyDownShortcuts, true);

            // This is a good place to update your game or application.

            // Always update the context before rendering.
            context->Update();

            // Prepare the backend for taking rendering commands from RmlUi and then render the context.
            RmlBackend::BeginFrame();
            context->Render();
            RmlBackend::PresentFrame();
        }
        
    }
    void Shutdown()
    {
        Logger::WriteMessage(L"Core UI Shutdown");
        running = false;
        Rml::Shutdown();

        RmlBackend::Shutdown();
    }
    void Render()
    {
    }
}