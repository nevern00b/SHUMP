#include "Enemy.h"
#include <Box2D/Box2D.h>
#include <glm/gtc/random.hpp>
#include "Bullet.h"
#include "Globals.h"
#include "DataManager.h"
#include "Player.h"
#include "Physics/PhysicsManager.h"
#include "Physics/PhysicsComponent.h"
#include "Rendering/RenderComponent.h"
#include "ShmupGame.h"
#include "ShootComponent.h"
#include "UIManager.h"
#include "Rendering/ParticleSystem.h"
#include "Item.h"
#include "Rendering/Material.h"
#include "AnimationManager.h"
#include "Rendering/RenderManager.h"

Enemy::Enemy(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float pos_x) : Entity(0),
	m_color(color), 
	m_pattern(pattern), 
	m_type(type),
	m_x(pos_x),
	m_brightness(0.0f),
	m_intro(true)
{
	Mesh* mesh = Globals::m_dataManager->getMesh("sphere");

	b2PolygonShape shape;
	shape.SetAsBox(0.5f, 0.5f);
	PhysicsData physicsData(shape);
	physicsData.m_groupIndex = ShmupGame::ENEMY_GROUP;

	Material* material = Globals::m_dataManager->getEnemyMaterial(color);
	material->m_spawnTime = Globals::m_uiManager->getTime();
	material->m_specPower = 10.0f;
	material->m_specIntensity = 0.5f;

	PhysicsComponent* physics = new PhysicsComponent(this, physicsData);
	RenderComponent* render = new RenderComponent(this, mesh, material);

	if (m_color == COLOR::RED)
	{
		m_health = 2.0f;
		m_shootComponent = new ShootComponent(this, Globals::m_shmupGame->m_enemyRBulletPool);
	}
	else if (m_color == COLOR::BLUE)
	{
		m_health = 4.0f;
		m_shootComponent = new ShootComponent(this, Globals::m_shmupGame->m_enemyBBulletPool);
	}
	else if (m_color == COLOR::GREEN)
	{
		m_health = 6.0f;
		m_shootComponent = new ShootComponent(this, Globals::m_shmupGame->m_enemyGBulletPool);
	}
	else if (m_color == COLOR::YELLOW)
	{
		m_health = 10.0f;
		m_shootComponent = new ShootComponent(this, Globals::m_shmupGame->m_enemyYBulletPool);
	}	
	
	if (m_type == ENEMY_TYPE::EXPLOSIVE)
	{
		material->m_noiseStrength = 0.3f;
	}

	m_shootTimer = new Timer();
	m_shootTimer->start(0.3f, true);


	float introTime = 0.5f;

	// Rise from the floor
	auto endIntro = [&]() {m_intro = false; };
	float floorDepth = Globals::m_renderManager->m_floorDepth;
	Animation* introAnimation = new Animation(this, m_transform->m_translation.z, floorDepth - 1.0f, 0.0f, 0.5f, 0.0f, false);
	introAnimation->m_callback = endIntro;
}

Enemy::~Enemy()
{

}

bool Enemy::update()
{
	if(!Entity::update()) return false;
	if (m_intro) return true;

	if (m_shootTimer->checkInterval())
	{
		b2Vec2 pos = m_physics->m_body->GetPosition();

		if (m_pattern == ENEMY_PATTERN::HOVER)
		{
			if (pos.x < (m_x - 3)) m_enemyDirection.x = -m_enemyDirection.x;
			else if (pos.x > (m_x + 3)) m_enemyDirection.x = -m_enemyDirection.x;
		}

		float vx;
		float vy;

		if (m_color == COLOR::RED)
		{
			vx = glm::linearRand(-5.0f, 5.0f);
			vy = glm::linearRand(-5.0f, 5.0f);

			if (glm::abs(vx) < 0.1) vx = -1;
			if (glm::abs(vy) < 0.1) vy = -1;
		}
		else if (m_color == COLOR::GREEN)
		{
			vx = glm::linearRand(-5.0f, 5.0f);
			vy = glm::linearRand(-5.0f, 5.0f);
		}
		else if (m_color == COLOR::BLUE)
		{
			vx = -pos.x;// glm::linearRand(-5.0f, 5.0f);
			vy = -pos.y;// glm::linearRand(-5.0f, 5.0f);
		}
		else if (m_color == COLOR::YELLOW)
		{
			if (Globals::m_shmupGame->m_player != 0)
			{
				b2Vec2 playerpos = Globals::m_shmupGame->m_player->getPosition2d();
				b2Vec2 velocity = playerpos - pos;
				velocity.Normalize();
				vx = velocity.x * 5.0f;
				vy = velocity.y * 5.0f;
			}
			

			/*vx = glm::linearRand(-5.0f, 5.0f);
			vy = glm::linearRand(-5.0f, 5.0f);*/
		}
		
		if (glm::abs(vx) < 0.1) vx = -1.0f;
		if (glm::abs(vy) < 0.1) vy = -1.0f;
		m_shootComponent->shoot(pos.x, pos.y, vx, vy);

		if (pos.x < ShmupGame::WORLD_LOWER_BOUND_X || pos.x > ShmupGame::WORLD_UPPER_BOUND_X || pos.y < ShmupGame::WORLD_LOWER_BOUND_Y || pos.y > ShmupGame::WORLD_UPPER_BOUND_Y)
			destroy();
	}	

	m_physics->applyVelocity(m_enemyDirection.x, m_enemyDirection.y);

	glm::vec3 color = glm::vec3(Globals::m_dataManager->getMaterial(m_color)->m_diffuseColor);
	color += m_brightness;
	color = glm::min(color, glm::vec3(1.0));
	m_render->m_materials[0]->m_diffuseColor = glm::vec4(color, 1.0);

	return true;
}

void Enemy::onCollide(EventObject* collider)
{
	Bullet* bullet = dynamic_cast<Bullet*>(m_collider);
	if (bullet != 0)
	{
		bullet->destroy();
		if (bullet->m_color != m_color)
		{
			m_health -= bullet->m_damage;

			if (m_health <= 0.0f)
			{
				Globals::m_stateMachine->p_score = Globals::m_stateMachine->p_score + 500;

				b2Vec2 pos = m_physics->m_body->GetPosition();
				Globals::m_shmupGame->m_particleSystem->createRadial(pos.x, pos.y, 10);

				// Drop immunity item
				ImmunityItem* immunityItem = new ImmunityItem(m_color, 0.0f, -3.0f);
				immunityItem->m_transform->setTranslation(pos.x, pos.y);

				// Randomly drop life item
				if (glm::linearRand(0.0, 1.0) < 0.3f)
				{
					float vx = glm::linearRand(-5.0f, 5.0f);
					float vy = -3.0f;
					LifeItem* lifeItem = new LifeItem(vx, vy);
					lifeItem->m_transform->setTranslation(pos.x, pos.y);					
				}

				destroy();
			}
			else
			{
				new Animation(this, m_brightness, 1.0f, 0.0f, 0.1f, 0.0f, false);
			}
		}
	}
}
