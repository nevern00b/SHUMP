#include "Item.h"

#include <Box2d/Box2D.h>
#include "Globals.h"
#include "DataManager.h"
#include "Physics/PhysicsComponent.h"
#include "Rendering/RenderComponent.h"
#include "UIManager.h"

Item::Item(float vx, float vy) : Entity(0)
{
	// Create spinner thing
	Mesh* mesh = Globals::m_dataManager->getMesh("sphere");
	Material* material = Globals::m_dataManager->getMaterial(COLOR::RED);

	b2PolygonShape shape;
	shape.SetAsBox(0.3f, 0.3f);
	PhysicsData physicsData(shape);
	PhysicsComponent* physics = new PhysicsComponent(this, physicsData);
	RenderComponent* render = new RenderComponent(this, mesh, material);
	m_transform->setScale(0.3f);

	
	m_rotator = new Entity(this);

	m_atom1 = new Entity(m_rotator);
	RenderComponent* atomRender1 = new RenderComponent(m_atom1, mesh, material);
	m_atom1->m_transform->setTranslation(glm::vec3(1, 0, 0));
	m_atom1->m_transform->setScale(0.5f);

	m_atom2 = new Entity(m_rotator);
	RenderComponent* atomRender2 = new RenderComponent(m_atom2, mesh, material);
	m_atom2->m_transform->setTranslation(glm::vec3(-1, 0, 0));
	m_atom2->m_transform->setScale(0.5f);

	m_physics->setVelocity(vx, vy);
}

Item::~Item()
{

}

bool Item::update()
{
	if (!Entity::update()) return false;

	float rotateAmount = Globals::m_uiManager->getFramerateAdjust(10.0f);
	m_rotator->m_transform->rotate(rotateAmount, glm::vec3(0, 1, 0));
	
	return true;
}


// Immunity

ImmunityItem::ImmunityItem(COLOR color, float vx, float vy) : Item(vx, vy),
	m_color(color)
{
	Material* material = Globals::m_dataManager->getMaterial(m_color);
	m_atom1->m_render->m_materials[0] = material;
	m_atom2->m_render->m_materials[0] = material;
	m_render->m_materials[0] = material;
}

ImmunityItem::~ImmunityItem()
{

}

// Life
LifeItem::LifeItem(float vx, float vy) : Item(vx, vy)
{
	Material* material = Globals::m_dataManager->getMaterial("pink");
	m_atom1->m_render->m_materials[0] = material;
	m_atom2->m_render->m_materials[0] = material;
	m_render->m_materials[0] = material;
}

LifeItem::~LifeItem()
{

}