#include "Item.h"

#include <Box2d/Box2D.h>
#include "Globals.h"
#include "DataManager.h"
#include "Physics/PhysicsComponent.h"
#include "Rendering/RenderComponent.h"

Item::Item() : Entity(0)
{
	b2PolygonShape shape;
	shape.SetAsBox(0.3f, 0.3f);
	PhysicsData physicsData(shape);
	PhysicsComponent* physics = new PhysicsComponent(this, physicsData);
	m_transform->setScale(0.3f);

	// The visual portion rotates, while the main entity does physics
	m_visual = new Entity(this);
}

Item::~Item()
{

}

bool Item::update()
{
	if (!Entity::update()) return false;

	m_physics->setVelocity(0, -1.0f);

	m_visual->m_transform->rotate(3.0f, glm::vec3(1, 1, 0));
	
	return true;
}


// Immunity

ImmunityItem::ImmunityItem(COLOR color) : Item(),
	m_color(color)
{
	Mesh* mesh = Globals::m_dataManager->getMesh("cube");
	Material* material = Globals::m_dataManager->getMaterial(m_color);
	RenderComponent* render = new RenderComponent(m_visual, mesh, material);
}

ImmunityItem::~ImmunityItem()
{

}