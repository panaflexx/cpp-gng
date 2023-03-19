#include "pch.h"
#include "LevelScene.h"

#include "Animation.h"
#include "AnimationFrame.h"
#include "AnimatorAnimationEndTransition.h"
#include "AnimatorRenderer.h"
#include "AnimatorState.h"
#include "Camera.h"
#include "Collider.h"
#include "ConditionalAnimatorTransition.h"
#include "Entity.h"

#include "EntityKeeper.h"
#include "PhysicsBody.h"
#include "PlayerController.h"
#include "Game.h"
#include "Renderer.h"
#include "TextureCache.h"
#include "Transform.h"

LevelScene::LevelScene()
	: Scene(new Camera(5.f))
{
}

void LevelScene::InitializeScene()
{
	CreatePlayer();

	m_pObstacle = m_pEntityKeeper->CreateEntity(1, "Obstacle");

	m_pObstacle->AddComponent(new Transform(m_pObstacle, Vector2f(0, 5)));
	m_pObstacle->AddComponent(new Collider(m_pObstacle, std::vector<Vector2f>{
		Vector2f(0, 0),
			Vector2f(0, 5),
			Vector2f(150, 5),
			Vector2f(150, 0),
	}));

	m_pObstacle->Initialize();
}

void LevelScene::UpdateScene(float deltaTime)
{
}

void LevelScene::DrawScene() const
{
}

void LevelScene::CreatePlayer()
{
	m_pTextureCache->LoadTexture("player", "player.png");

	m_pPlayer = m_pEntityKeeper->CreateEntity(100, "Player");
	m_pPlayer->AddComponent(new Transform(m_pPlayer, Vector2f(10, 40)));

	// RENDERING
	const float spriteWidth{ 22.f };
	const float spriteHeight{ 25.f };
	const std::unordered_map<std::string, AnimatorState*> playerStates
	{
	{ "idle", new AnimatorState(new Animation(std::vector<AnimationFrame*>{
			new AnimationFrame(1.f, Rectf(spriteWidth * 1, spriteHeight * 1, spriteWidth, spriteHeight)),
		}))},
	{ "crouch", new AnimatorState(new Animation(std::vector<AnimationFrame*>{
			new AnimationFrame(1.f, Rectf(spriteWidth * 2, spriteHeight * 1, spriteWidth, spriteHeight)),
		}))},
	{ "walk", new AnimatorState(new Animation(std::vector<AnimationFrame*>{
			new AnimationFrame(0.2f,  Rectf(spriteWidth * 0, spriteHeight * 2, spriteWidth, spriteHeight)),
			new AnimationFrame(0.2f,  Rectf(spriteWidth * 1, spriteHeight * 2, spriteWidth, spriteHeight)),
		}))}
	};

	const std::list<AnimatorTransition*> playerTransitions
	{
		new ConditionalAnimatorTransition("idle", "crouch", "isCrouched", true),
		new ConditionalAnimatorTransition("crouch", "idle", "isCrouched", false),
	};

	m_pPlayer->AddComponent(new AnimatorRenderer(
		m_pPlayer,
		m_pTextureCache->GetTexture("player"),
		playerStates,
		playerTransitions,
		"idle"
	));


	// PHYSICS
	m_pPlayer->AddComponent(new PhysicsBody(m_pPlayer));

	const float colliderWidth{ 8.f };
	const float colliderHeight{ 8.f };
	m_pPlayer->AddComponent(new Collider(m_pPlayer, std::vector<Vector2f>{
		Vector2f(0.f, 0.f),
		Vector2f(0.f, colliderHeight),
		Vector2f(colliderWidth, colliderHeight),
		Vector2f(colliderWidth, 0.f)
	}));


	// LOGIC
	m_pPlayer->AddComponent(new PlayerController(m_pPlayer));

	m_pPlayer->Initialize();
}
