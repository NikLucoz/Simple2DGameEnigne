#include "DebugUI.h"
#include <map>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>

#include "engine/systems/EnemySpawnSystem.h"
#include "engine/systems/LifeSpanSystem.h"
#include "engine/systems/CollisionSystem.h"
#include "engine/systems/MovementSystem.h"
#include "engine/systems/RenderSystem.h"
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

    ImGui::GetStyle().ScaleAllSizes(1.0f);
}

void DebugUI::Update(sf::Clock& deltaClock, const EntityVec& entities)
{
    ImGui::SFML::Update(*Window, deltaClock.restart());

    ImGui::Begin("Debug Panel");

    // Creazione della barra delle schede (TabBar)
    if (ImGui::BeginTabBar("DebugTabBar"))
    {
        // --------------------------------------------------
        // TAB 1: SYSTEM
        // --------------------------------------------------
        if (ImGui::BeginTabItem("System"))
        {
            bool isMovementActive = MovementSystem::getInstance().bIsActive_;
            if (ImGui::Checkbox("Movement System", &isMovementActive)) {
                MovementSystem::getInstance().bIsActive_ = isMovementActive;
            }

            bool isCollisionActive = CollisionSystem::getInstance().bIsActive_;
            if (ImGui::Checkbox("Collision System", &isCollisionActive)) {
                CollisionSystem::getInstance().bIsActive_ = isCollisionActive;
            }

            if (ImGui::CollapsingHeader("Render", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Indent();
                bool isRenderActive = RenderSystem::getInstance().bIsActive_;
                if (ImGui::Checkbox("Render System", &isRenderActive)) {
                    RenderSystem::getInstance().bIsActive_ = isRenderActive;
                }

                bool shouldRenderDebug = RenderSystem::getInstance().bDrawDebug_;
                if (ImGui::Checkbox("Show debug", &shouldRenderDebug)) {
                    RenderSystem::getInstance().bDrawDebug_ = shouldRenderDebug;
                }
                ImGui::Unindent();
            }

            bool isLifespanActive = LifeSpanSystem::getInstance().bIsActive_;
            if (ImGui::Checkbox("LifeSpanSystem System", &isLifespanActive)) {
                LifeSpanSystem::getInstance().bIsActive_ = isLifespanActive;
            }

            bool isEnemySpawnActive = EnemySpawnSystem::getInstance().bIsActive_;
            if (ImGui::Checkbox("EnemySpawn System", &isEnemySpawnActive)) {
                EnemySpawnSystem::getInstance().bIsActive_ = isEnemySpawnActive;
            }

            ImGui::EndTabItem();
        }

        // --------------------------------------------------
        // TAB 2: ENTITIES
        // --------------------------------------------------
        if (ImGui::BeginTabItem("Entities"))
        {
            // Raggruppa le entità per tag
            std::map<std::string, EntityVec> entitiesByTag;
            for (auto& e : entities) {
                entitiesByTag[e->getTag()].push_back(e);
            }

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
                if (ImGui::BeginTable("all_entities_table", 6, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
                {
                    ImGui::TableSetupColumn("Action", ImGuiTableColumnFlags_WidthFixed, 50);
                    ImGui::TableSetupColumn("ID");
                    ImGui::TableSetupColumn("Tag");
                    ImGui::TableSetupColumn("Position");
                    ImGui::TableSetupColumn("Velocity");
                    ImGui::TableSetupColumn("Rotation");
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
                        ImGui::TableSetColumnIndex(4);
                        ImGui::Text("(%.1f, %.1f)", transform.velocity.x, transform.velocity.y);
                        ImGui::TableSetColumnIndex(5);
                        ImGui::Text("%.1f", transform.rotation);
                    }
                    ImGui::EndTable();
                }
            }

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
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