#include "Item.h"

#include <Box2d/Box2D.h>
#include "Globals.h"
#include "DataManager.h"
#include "Physics/PhysicsComponent.h"
#include "Rendering/RenderComponent.h"
#include "UIManager.h"

Item::Item(float vx, float vy) : Entity(0),
	m_scaleDir(1.0f)
{
	b2PolygonShape shape;
	shape.SetAsBox(0.3f, 0.3f);
	PhysicsData physicsData(shape);
	PhysicsComponent* physics = new PhysicsComponent(this, physicsData);
	m_transform->setScale(0.3f);

	// The visual portion rotates, while the main entity does physics
	m_visual = new Entity(this);

	m_physics->setVelocity(vx, vy);


}

Item::~Item()
{

}

bool Item::update()
{
	if (!Entity::update()) return false;

	float rotateAmount = Globals::m_uiManager->getFramerateAdjust(3.0f);
	m_visual->m_transform->rotate(rotateAmount, glm::vec3(1, 1, 0));

	float scaleAmount = Globals::m_uiManager->getFramerateAdjust(0.01f);
	float scale = m_transform->m_scale.x + scaleAmount * m_scaleDir;
	if (scale >= 0.4f)
	{
		m_scaleDir = -1.0f;
	}
	else if (scale <= 0.2f)
	{
		m_scaleDir = 1.0f;
	}

	m_transform->setScale(scale);
	
	return true;
}


// Immunity

ImmunityItem::ImmunityItem(COLOR color, float vx, float vy) : Item(vx, vy),
	m_color(color)
{
	Mesh* mesh = Globals::m_dataManager->getMesh("cube");
	Material* material = Globals::m_dataManager->getMaterial(m_color);
	RenderComponent* render = new RenderComponent(m_visual, mesh, material);
}

ImmunityItem::~ImmunityItem()
{

}

// Life
LifeItem::LifeItem(float vx, float vy) : Item(vx, vy)
{
	Mesh* mesh = Globals::m_dataManager->getMesh("cube");
	Material* material = Globals::m_dataManager->getMaterial("pink");
	RenderComponent* render = new RenderComponent(m_visual, mesh, material);
}

LifeItem::~LifeItem()
{

}