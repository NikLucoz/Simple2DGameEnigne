#include "Scene.h"
#include "engine/GameEngine.h"
#include "engine/actions/Action.h"
#include "engine/entities/EntityManager.h"
#include <SFML/Window/Keyboard.hpp>

Scene::Scene(GameEngine* gameEngine) : gameEngine_(gameEngine)
{
	registerAction(InputDevice::Keyboard, static_cast<int>(sf::Keyboard::Key::F3), "Toggle_Debug_UI");
}

void Scene::doAction(const Action &action)
{
    if (action.name() == "Toggle_Debug_UI" && action.type() == "pressed")
    {
        gameEngine_->getDebugOptions().showDebugUI = !gameEngine_->getDebugOptions().showDebugUI;
    }

    sDoAction(action);
}

void Scene::registerAction(InputDevice device, int code, const std::string& actionName)
{
    actionMap_[{ device, code }] = actionName;
}

ActionMap& Scene::getActionMap()
{
    return actionMap_;
}

void Scene::defaultEntityRender(float dt) {
    for (std::shared_ptr<Entity>& ePtr : EntityManager::getInstance().getEntities())
    {
        Entity& e = *ePtr;
        if (!e.hasComponent<CTransform>()) continue;
        CTransform& transform = e.getComponent<CTransform>();
        Vec2f pos = transform.getPosition();
        
        if (e.hasComponent<CShape>())
        {
            CShape& cShape = e.getComponent<CShape>();
            cShape.getShape()->setPointCount(cShape.point_count_);
            cShape.getShape()->setPosition(sf::Vector2f(pos.x, pos.y));
            cShape.getShape()->setRotation(sf::degrees(transform.getRotation()));
            cShape.getShape()->setOrigin({cShape.radius_, cShape.radius_});
            cShape.getShape()->setFillColor(cShape.fillColor_);
            cShape.getShape()->setOutlineColor(cShape.outlineColor_);
            cShape.getShape()->setOutlineThickness(cShape.outlineThickness_);
            cShape.getShape()->setScale(transform.getScale().toSFVector2());
            gameEngine_->getWindow().draw(*cShape.getShape());
        }

        if (e.hasComponent<CAnimatedSprite>()) {
            CAnimatedSprite& cAnimatedSprite = e.getComponent<CAnimatedSprite>();
            sf::Sprite& sprite = cAnimatedSprite.animation->getSprite();
            sprite.setPosition(sf::Vector2f(transform.getPosition().x, transform.getPosition().y));
            sprite.setRotation(sf::degrees(transform.getRotation()));
            sprite.setScale(transform.getScale().toSFVector2());
            gameEngine_->getWindow().draw(sprite);
        }
        
        if (e.hasComponent<CSprite>())
        {
            CSprite& sprite = e.getComponent<CSprite>();
            auto& sfSprite = sprite.getSprite();
            sf::Vector2u textureSize = sprite.getTexture().getSize();
            Vec2f desiredSize = sprite.getSize();
            
            Vec2f calculatedScale(
                desiredSize.x / textureSize.x,
                desiredSize.y / textureSize.y
            );
    
            sf::Vector2f finalScale = (calculatedScale * sprite.getScale()).toSFVector2();
            sfSprite.setScale(finalScale);
    
            sf::Vector2f spriteOrigin(
                textureSize.x / 2.0f,
                textureSize.y / 2.0f
            );

            sfSprite.setOrigin(spriteOrigin);
            sfSprite.setPosition(sf::Vector2f(transform.getPosition().x, transform.getPosition().y));
            sfSprite.setRotation(sf::degrees(transform.getRotation()));
            gameEngine_->getWindow().draw(sfSprite);
        }
        
        if (gameEngine_->getDebugOptions().showEntityIds)
        {
            sf::Text entityIdText(
                gameEngine_->getAssets().getFont("fontArial"),
                std::to_string(e.getId()),
                14
            );
            entityIdText.setOrigin({7.0f, 14.0f});
            entityIdText.setPosition({pos.x, pos.y - 40.0f});
            entityIdText.setFillColor(sf::Color::White);
            entityIdText.setOutlineColor(sf::Color::Black);
            entityIdText.setOutlineThickness(1.0f);
            gameEngine_->getWindow().draw(entityIdText);
        }
    }
    
    if (gameEngine_->getDebugOptions().showCollisionGeometry) sDebug();
}
