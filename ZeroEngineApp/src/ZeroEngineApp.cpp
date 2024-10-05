#include "ZeroEngine/Application.h"
#include "ZeroEngine/EntryPoint.h"
#include "ZeroEngine/Image.h"
#include <ZeroEngine/UI/UI.h>

class ZeroEngineLayer : public ZeroEngine::Layer
{
public:
    // OnUIRender is where you want to render your ImGui stuff. Change this as you wish!
    virtual void OnUIRender() override
    {
        // This makes your ImGui window "become" your window. Use this if you want.
        /*
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 windowPos = viewport->Pos;
        windowPos.y += m_TopOffset;
        ImVec2 windowSize = ImVec2(viewport->Size.x, viewport->Size.y - m_TopOffset - m_BottomOffset);
        ImGui::SetNextWindowPos(windowPos);
        ImGui::SetNextWindowSize(windowSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNavFocus;
        */
        ImGui::Begin("ZeroEngine", nullptr /* ,window_flags */);
        ImGui::Text("Some Text!");
        ImGui::End();

        UI_DrawAboutModal();
    }

    void UI_DrawAboutModal()
    {
        if (m_AboutModalOpen)
        {
            ImGui::OpenPopup("About");
            m_AboutModalOpen = false;
        }

        if (ImGui::BeginPopupModal("About", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            auto image = ZeroEngine::Application::Get().GetApplicationIcon();
            if (image != nullptr)
            {
                ImGui::Image(image->GetDescriptorSet(), { 48, 48 });
                ImGui::SameLine();
                ZeroEngine::UI::ShiftCursorX(20.0f);
            }

            ImGui::BeginGroup();
            ImGui::Text("ZeroEngine Template");
            ImGui::Text("by Fako.");
            ImGui::Text("Built on top of [Studio Cherno] Walnut application framework.");
            ImGui::EndGroup();
            if (ZeroEngine::UI::ButtonCentered("Close"))
            {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
    }

    void ShowAboutModal()
    {
        m_AboutModalOpen = true;
    }

private:
    bool m_AboutModalOpen = false;
};

ZeroEngine::Application* ZeroEngine::CreateApplication(int argc, char** argv)
{
    ZeroEngine::ApplicationSpecification spec;
    spec.Name = "Example Template";
    spec.CustomTitlebar = true;
    ZeroEngine::Application* app = new ZeroEngine::Application(spec);
    std::shared_ptr<ZeroEngineLayer> exampleLayer = std::make_shared<ZeroEngineLayer>();
    app->PushLayer(exampleLayer);
    app->SetMenubarCallback([app, exampleLayer]()
    {
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About"))
            {
                exampleLayer->ShowAboutModal(); 
            }
            ImGui::EndMenu();
        }
    });
    return app;
}