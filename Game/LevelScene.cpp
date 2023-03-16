#include "pch.h"
#include "LevelScene.h"

#include "Camera.h"
#include "Collider.h"
#include "Entity.h"

#include "EntityKeeper.h"
#include "PhysicsBody.h"
#include "PlayerController.h"
#include "Renderer.h"
#include "TextureCache.h"
#include "Transform.h"

LevelScene::LevelScene()
	: Scene(new Camera(5.f))
{
}

void LevelScene::InitializeScene()
{
	m_pTextureCache->LoadTexture("pengo", "pengo.png");

	m_pPlayer = m_pEntityKeeper->CreateEntity();

	m_pPlayer->AddComponent(new Transform(m_pPlayer, Vector2f(10, 40)));
	m_pPlayer->AddComponent(new Renderer(m_pPlayer, m_pTextureCache->GetTexture("pengo")));
	m_pPlayer->AddComponent(new PhysicsBody(m_pPlayer));

	const float colliderWidth{ 16.f };
	const float colliderHeight{ 16.f };
	m_pPlayer->AddComponent(new Collider(m_pPlayer, std::vector<Vector2f>{
		Vector2f(0.f, 0.f),
		Vector2f(0.f, colliderHeight),
		Vector2f(colliderWidth, colliderHeight),
		Vector2f(colliderWidth, 0.f)
	}));

	m_pPlayer->AddComponent(new PlayerController(m_pPlayer));

	m_pPlayer->Initialize();


	m_pObstacle = m_pEntityKeeper->CreateEntity(1);

	m_pObstacle->AddComponent(new Transform(m_pObstacle, Vector2f(0, 5)));
	m_pObstacle->AddComponent(new Collider(m_pObstacle, std::vector<Vector2f>{ Vector2f(0, 0), Vector2f(0, 5), Vector2f(50, 5), Vector2f(50, 0) }));

	m_pObstacle->Initialize();
}

void LevelScene::UpdateScene(float deltaTime)
{
	if(SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_SPACE])
	{
		m_pPlayer->GetComponent<PhysicsBody>()->SetYVelocity(0);
		m_pPlayer->GetComponent<Transform>()->MovePosition(Vector2f(0, 80 * deltaTime));
	}
}

void LevelScene::DrawScene() const
{
}
