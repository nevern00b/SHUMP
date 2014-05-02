#include "Floor.h"

#include "Common.h"
#include "Rendering/Mesh.h"
#include "Rendering/Material.h"
#include "Rendering/RenderComponent.h"
#include "Globals.h"
#include "Rendering/RenderManager.h"

Floor::Floor() : Entity(0)
{
	float vertexData[32] = { -50.0f, -100.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
							50.0f, -100.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
							50.0f, 100.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
							-50.0f, 100.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f };

	ushort elementArrayData[6] = { 0, 1, 2, 2, 3, 0 };

	Mesh* mesh = new Mesh(vertexData, elementArrayData, 32, 6);
	Material* material = new Material();

	RenderComponent* render = new RenderComponent(this, mesh, material);

	Globals::m_renderManager->setFloor(this);
}

Floor::~Floor()
{

}