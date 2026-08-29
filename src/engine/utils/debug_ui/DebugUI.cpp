#include "DebugUI.h"
#include <map>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>

#include "engine/entities/EntityManager.h"
#include "engine/components/CTransform.h"

DebugUI::DebugUI() {}

void DebugUI::Init(sf::RenderWindow& window)
{
    
    Window = &window;
    
    if (!ImGui::SFML::Init(*Window)) {
        std::cerr << "Failed to initialize ImGui-SFML!\n";
        return;
    }
    
    ImGuiIO& io = ImGui::GetIO();
   	ImFont* pFont = io.Fonts->AddFontFromFileTTF("game/assets/fonts/fonts/arial.ttf", 14.0f);

    if (pFont) {
        ImGui::PushFont(pFont);
    } else {
        std::cerr << "Warning: Failed to load fonts/arial.ttf\n";
    }
    
    ImGui::GetStyle().ScaleAllSizes(1.0f);
}

void DebugUI::Update(sf::Clock& deltaClock, const EntityVec& entities)
{
    ImGui::SFML::Update(*Window, deltaClock.restart());

    // Group entities by tag locally for the first section
    std::map<std::string, EntityVec> entitiesByTag;
    for (auto& e : entities) {
        entitiesByTag[e->getTag()].push_back(e);
    }

    ImGui::Begin("Entity Debug Panel");

    if (ImGui::CollapsingHeader("Entities by Tags", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Indent();
        for (auto& pair : entitiesByTag)
        {
            std::string name = pair.first + " Entities (" + std::to_string(pair.second.size()) + ")";
            
            if (ImGui::CollapsingHeader(name.c_str()))
            {
                if (!pair.second.empty()) {
                    if (ImGui::BeginTable(pair.first.c_str(), 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
                    {
                        ImGui::TableSetupColumn("ID");
                        ImGui::TableSetupColumn("Tag");
                        ImGui::TableSetupColumn("Position");
                        ImGui::TableHeadersRow();

                        for (size_t i = 0; i < pair.second.size(); i++)
                        {
                            ImGui::TableNextRow();

                            ImGui::TableSetColumnIndex(0);
                            ImGui::Text("%d", (int)pair.second[i]->getId());

                            ImGui::TableSetColumnIndex(1);
                            ImGui::Text("%s", pair.first.c_str());

                            auto& transform = pair.second[i]->getComponent<CTransform>();

                            ImGui::TableSetColumnIndex(2);
                            ImGui::Text("(%.1f, %.1f)", transform.position.x, transform.position.y);
                        }

                        ImGui::EndTable();
                    }
                }
            }
        }
        ImGui::Unindent();
    }
    
    if (ImGui::CollapsingHeader("All Entities", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::BeginTable("all_entities_table", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
        {
            ImGui::TableSetupColumn("Action", ImGuiTableColumnFlags_WidthFixed, 50);
            ImGui::TableSetupColumn("ID");
            ImGui::TableSetupColumn("Tag");
            ImGui::TableSetupColumn("Position");
            ImGui::TableHeadersRow();

            for (size_t i = 0; i < entities.size(); i++)
            {
                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex(0);
                std::string btnName = "D##" + std::to_string(entities[i]->getId());
                if (ImGui::Button(btnName.c_str(), ImVec2(40, 0))) {
                    entities[i]->destroy();
                }

                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%d", (int)entities[i]->getId());

                ImGui::TableSetColumnIndex(2);
                ImGui::Text("%s", entities[i]->getTag().c_str());

                auto& transform = entities[i]->getComponent<CTransform>();

                ImGui::TableSetColumnIndex(3);
                ImGui::Text("(%.1f, %.1f)", transform.position.x, transform.position.y);
            }
            ImGui::EndTable();
        }
    }

    ImGui::End();
}

void DebugUI::Render()
{
    ImGui::SFML::Render(*Window);
}

void DebugUI::ProcessEvent(sf::Event& event)
{
    ImGui::SFML::ProcessEvent(*Window, event);
}

bool DebugUI::GetAnyItemHovered()
{
    return ImGui::IsAnyItemHovered();
}