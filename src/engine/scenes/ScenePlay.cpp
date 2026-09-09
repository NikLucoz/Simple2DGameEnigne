#include "ScenePlay.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include "engine/actions/Action.h"
#include "engine/entities/EntityManager.h"
#include "engine/entities/EPlayer.h"
#include "engine/utils/physics/CollisionUtils.h"

ScenePlay::ScenePlay(GameEngine* gameEngine, float enemySpawnTime) : Scene(gameEngine), enemySpawnMaxTime(enemySpawnTime)
{
    elapsedTimeSinceLastEnemySpawn_ = enemySpawnTime;
        
    player_ = EntityManager::getInstance().addEntity<EPlayer>("player");
    Vec2f startPos = Vec2f(gameEngine_->getWindow().getSize().x / 2, gameEngine_->getWindow().getSize().y / 2);
    player_->getComponent<CTransform>().position = startPos;
    player_->startPosition = startPos;
}

void ScenePlay::update(float dt)
{
    sMovement(dt);
    sCollision();
    sLifespan(dt);
    sEnemySpawner(dt);
    sAnimation();
    if (bShouldShowDebug_) sDebug();
}

void ScenePlay::sRender(float dt)
{
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
            gameEngine_->getWindow().draw(*cShape.getShape());
        }
        
        /*
        * if (e.hasComponent<CSprite>())
        {
            CSprite& sprite = e.getComponent<CSprite>();
            if (sprite.m_filepath.empty()) return;
    
            sf::Sprite sfSprite(sprite.getTexture());
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
         */
    }
    sDebug();
}

void ScenePlay::sDoAction(const Action& action)
{
}

void ScenePlay::sAnimation()
{
}

void ScenePlay::sMovement(float dt)
{
    //if (!bIsActive_) return;
    
    if (player_ == nullptr) return;
   
    auto& input = player_->getComponent<CInput>();
    if (input.hasMovementInput())
    {
        auto& transform = player_->getComponent<CTransform>();
        Vector2<int> movementDirection = input.getMovementDirection();
        transform.position.x += transform.velocity.x * movementDirection.x * dt;
        transform.position.y += transform.velocity.y * movementDirection.y * dt;
    }
    
    
    std::vector<std::string> tags{"bullet", "enemy"};
    auto movable_entities = EntityManager::getInstance().getEntities(tags);
    for (auto& e : movable_entities)
    {
        if (!e->hasComponent<CTransform>()) continue;
        auto& transform = e->getComponent<CTransform>();
        transform.position.y += transform.velocity.y * dt;
        transform.position.x += transform.velocity.x * dt;
    }
    
    tags = {"specialBullet"};
    auto specialBullets = EntityManager::getInstance().getEntities(tags);
    for (auto& sb : specialBullets)
    {
        if (!sb->hasComponent<CTransform>()) continue;
        
        if (!sb->hasComponent<CSpecialBullet>())
            sb->addComponent<CSpecialBullet>();
    
        auto& bulletData = sb->getComponent<CSpecialBullet>();
        bulletData.oscillationTime += dt;
        float oscillationAmplitude = 15.0f;
        
        float sinValue = std::sin(bulletData.oscillationTime * 8.0f);
        
        auto& transform = sb->getComponent<CTransform>();
        float velocityMagnitude = transform.velocity.magnitude();
    
        if (velocityMagnitude > 0.0f)
        {
            float dirX = transform.velocity.x / velocityMagnitude;
            float dirY = transform.velocity.y / velocityMagnitude;
            
            // per applicare l'oscillazione del sin devo ruotare di 90° in senso orario
            Vec2f rotatedDirection = Vec2f(dirY, -dirX);
            Vec2f oscillation = rotatedDirection * oscillationAmplitude * sinValue;
            
            transform.position.x += oscillation.x + transform.velocity.x * dt;
            transform.position.y += oscillation.y + transform.velocity.y * dt;
        }
    }
}

void ScenePlay::sEnemySpawner(float dt)
{
    elapsedTimeSinceLastEnemySpawn_ -= dt;
    if (elapsedTimeSinceLastEnemySpawn_ <= 0.0f) {
        srand(time(0)*dt);
        float randomX = static_cast<float>(rand() % gameEngine_->getWindow().getSize().x);
        float randomY = static_cast<float>(rand() %  gameEngine_->getWindow().getSize().y);
        float randomAngle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f * 3.14f;

        float speed = 300.0f;
        float velX = std::cos(randomAngle) * speed;
        float velY = std::sin(randomAngle) * speed;
        
        int randomPoints = 3 + rand() % (6 + 1);
        
        int r = rand() % 255;
        int g = rand() % 255;
        int b = rand() % 255;

        auto e = EntityManager::getInstance().addEntity("enemy");
        e->addComponent<CTransform>(Vec2f(randomX, randomY), Vec2f(velX, velY), 0);
        e->addComponent<CShape>(25, randomPoints, sf::Color(r, g, b), sf::Color::White, 4);
        e->addComponent<CBoundingBox>(Vector2<int>(50,50));

        elapsedTimeSinceLastEnemySpawn_ = enemySpawnMaxTime;
    }
}

void ScenePlay::sCollision()
{
    auto& enemies = EntityManager::getInstance().getEntities("enemy");
    
    std::vector<std::string> tags{"bullet", "specialBullet"};
    auto bullets = EntityManager::getInstance().getEntities(tags);
    
    if (player_ == nullptr) return;
    
    auto& pTransform = player_->getComponent<CTransform>();
    auto& pCollider = player_->getComponent<CBoundingBox>();
    
    for (auto& enemy : enemies)
    {
        
        auto& eTransform = enemy->getComponent<CTransform>();
        auto& eBoundingBox = enemy->getComponent<CBoundingBox>();
        if (!enemy->hasComponent<CBoundingBox>()) continue;
        if (IsColliding(player_.get(), enemy.get()))
        {
            spawnEnemyDeathParticles(enemy.get());
            enemy->destroy();
            pTransform.position = player_->startPosition;
            break;
        }
        
        if (eTransform.getPosition().x - eBoundingBox.size.x < 0 ||
            eTransform.getPosition().x + eBoundingBox.size.x > gameEngine_->getWindow().getSize().x)
        {
            eTransform.velocity = eTransform.velocity.reflectionVector({1.0f, 0.0f});
        }
        
        // Horizontal wall collision
        if (eTransform.getPosition().y - eBoundingBox.size.y < 0 ||
            eTransform.getPosition().y + eBoundingBox.size.y > gameEngine_->getWindow().getSize().y)
        {
            eTransform.velocity = eTransform.velocity.reflectionVector({0.0f, 1.0f});
        }
        
        /*
        if (!enemy->hasComponent<CCircleCollider>()) continue;
        auto& eTransform = enemy->getComponent<CTransform>();
        auto& eCollider = enemy->getComponent<CCircleCollider>();

        float distanceToPlayer = eTransform.getPosition().distanceToSquared(pTransform.getPosition());
        if (distanceToPlayer < (eCollider.radius_ + pCollider.radius_) * (eCollider.radius_ + pCollider.radius_))
        {
            spawnEnemyDeathParticles(enemy.get());
            enemy->destroy();
            // TODO: ScoreSystem::getInstance().addScore(-200);
            pTransform.position = player_->startPosition;
            break;
        }
        
        for (auto& bullet : bullets)
        {
            if (!bullet->hasComponent<CCircleCollider>()) continue;
            auto& bTransform = bullet->getComponent<CTransform>();
            auto& bCollider = bullet->getComponent<CCircleCollider>();
            
            float distanceToBullet = eTransform.getPosition().distanceToSquared(bTransform.getPosition());
            if (distanceToBullet < (eCollider.radius_ + bCollider.radius_) * eCollider.radius_)
            {
                spawnEnemyDeathParticles(enemy.get());
                enemy->destroy();
                bullet->destroy();
                // TODO: ScoreSystem::getInstance().addScore(50);
                break;
            }
        }
        
        // Vertical wall collision
        if (eTransform.getPosition().x - eCollider.radius_ < 0 ||
            eTransform.getPosition().x + eCollider.radius_ > gameEngine_->getWindow().getSize().x)
        {
            eTransform.velocity = eTransform.velocity.reflectionVector({1.0f, 0.0f});
        }
        
        // Horizontal wall collision
        if (eTransform.getPosition().y - eCollider.radius_ < 0 ||
            eTransform.getPosition().y + eCollider.radius_ > gameEngine_->getWindow().getSize().y)
        {
            eTransform.velocity = eTransform.velocity.reflectionVector({0.0f, 1.0f});
        }
        */
        
       
    }
}

void ScenePlay::sLifespan(float dt)
{
    auto& entities = EntityManager::getInstance().getEntities();
    
    for (auto& entity : entities)
    {
        if (!entity->hasComponent<CLifespan>()) continue;
        CLifespan& cLifespan = entity->getComponent<CLifespan>();
        cLifespan.remainingSeconds_ -= dt;
        if (cLifespan.remainingSeconds_ <= 0) {
            cLifespan.remainingSeconds_ = 0;
        }

        if (entity->hasComponent<CShape>()) {
            CShape& cShape = entity->getComponent<CShape>();
            uint8_t alpha = (cLifespan.remainingSeconds_ / cLifespan.lifespanSeconds_) * 255;
            cShape.fillColor_.a = alpha;
            cShape.outlineColor_.a = alpha;
            cShape.getShape()->setFillColor(cShape.fillColor_);
            cShape.getShape()->setOutlineColor(cShape.outlineColor_);
        }

        if (cLifespan.remainingSeconds_ <= 0)
        {
            entity->destroy();
        }
    }
}

void ScenePlay::sDebug()
{
    for (std::shared_ptr<Entity>& ePtr : EntityManager::getInstance().getEntities())
    {
        Entity& e = *ePtr;
        if (e.hasComponent<CTransform>())
        {
            CTransform& transform = e.getComponent<CTransform>();
            Vec2f pos = transform.getPosition();
            if (e.hasComponent<CCircleCollider>())
            {
                CCircleCollider& c = e.getComponent<CCircleCollider>();
                sf::CircleShape sfShape(c.radius_);
                sfShape.setPointCount(20);
                sfShape.setPosition(sf::Vector2f(pos.x, pos.y));
                sfShape.setOrigin({c.radius_, c.radius_});
                sfShape.setFillColor(sf::Color::Transparent);
                sfShape.setOutlineColor(sf::Color::Green);
                sfShape.setOutlineThickness(2);
                gameEngine_->getWindow().draw(sfShape);
            }
            
            if (e.hasComponent<CBoundingBox>())
            {
                CBoundingBox& b = e.getComponent<CBoundingBox>();
                sf::RectangleShape sfShape;
                sfShape.setOutlineColor(sf::Color::Green);
                sfShape.setOutlineThickness(2);
                sfShape.setFillColor(sf::Color::Transparent);
                sfShape.setPosition(sf::Vector2f(pos.x - b.size.x/2, pos.y - b.size.y/2));
                sfShape.setSize(sf::Vector2f(b.size.x, b.size.y));
                gameEngine_->getWindow().draw(sfShape);
            }
        }
    }
}

void ScenePlay::spawnEnemyDeathParticles(Entity* enemy)
{
    if (enemy->hasComponent<CShape>())
    {
        auto& cShape = enemy->getComponent<CShape>();
        auto& eTransform = enemy->getComponent<CTransform>();

        float angleStep = 360.0f / cShape.point_count_;
        for (int i = 0; i < cShape.point_count_; ++i)
        {
            float angle = i * angleStep;
            angle += angleStep/2;
            float radiandAngles = sf::degrees(angle).asRadians();
            auto velX = std::cosf(radiandAngles) * 300;
            auto velY = -1 * std::sinf(radiandAngles) * 300;

            std::shared_ptr<Entity> enemyParticle = EntityManager::getInstance().addEntity("enemy");
            enemyParticle->addComponent<CShape>(10, cShape.point_count_, cShape.fillColor_, cShape.outlineColor_, 2);
            enemyParticle->addComponent<CLifespan>(0.4);
            enemyParticle->addComponent<CTransform>(eTransform.getPosition(), Vec2f(velX, velY), eTransform.getRotation());
        }
    }
}