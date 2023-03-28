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
#include "PhysicsHandler.h"
#include "PlayerCollider.h"
#include "TextureCache.h"
#include "Transform.h"

LevelScene::LevelScene()
	: Scene(new Camera(2.f))
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


	m_pTestEnemy = m_pEntityKeeper->CreateEntity(2, "Enemy");

	m_pTestEnemy->AddComponent(new Transform(m_pTestEnemy, Vector2f(50, 10)));
	m_pTestEnemy->AddComponent(new Collider(m_pTestEnemy, std::vector<Vector2f>{
		Vector2f(0, 0),
		Vector2f(0, 20),
		Vector2f(20, 20),
		Vector2f(20, 0),
	}, true));

	m_pTestEnemy->Initialize();


	m_pTestLadder = m_pEntityKeeper->CreateEntity(0, "Ladder");

	m_pTestLadder->AddComponent(new Transform(m_pTestLadder, Vector2f(80, 10)));
	m_pTestLadder->AddComponent(new Collider(m_pTestLadder, std::vector<Vector2f>{
		Vector2f(0, 0),
		Vector2f(0, 50),
		Vector2f(10, 50),
		Vector2f(10, 0),
	}, true));

	m_pTestLadder->Initialize();
}

void LevelScene::UpdateScene(float deltaTime)
{
}

void LevelScene::DrawScene() const
{
	m_pPhysicsHandler->DrawDebugColliders();
}

void LevelScene::CreatePlayer()
{
	m_pTextureCache->LoadTexture("player", "player.png");

	m_pPlayer = m_pEntityKeeper->CreateEntity(100, "Player");
	m_pPlayer->AddComponent(new Transform(m_pPlayer, Vector2f(10, 40)));

	// RENDERING
	const float spriteWidth{ 22.f };
	const float spriteHeight{ 25.f };
	//new AnimationFrame(1.f, Rectf(spriteWidth * 1, spriteHeight * 1, spriteWidth, spriteHeight)),
	const std::unordered_map<std::string, AnimatorState*> playerStates
	{
	{ "idle", new AnimatorState(new Animation(std::vector<AnimationFrame*>{
			new AnimationFrame(1.f, Rectf(spriteWidth * 1, spriteHeight * 1, spriteWidth, spriteHeight)),
		}))},
	{ "walk", new AnimatorState(new Animation(std::vector<AnimationFrame*>{
			new AnimationFrame(0.15f, Rectf(spriteWidth * 0, spriteHeight * 2, spriteWidth, spriteHeight)),
			new AnimationFrame(0.15f, Rectf(spriteWidth * 1, spriteHeight * 2, spriteWidth, spriteHeight)),
		}))},
	{ "crouch", new AnimatorState(new Animation(std::vector<AnimationFrame*>{
			new AnimationFrame(1.f, Rectf(spriteWidth * 2, spriteHeight * 1, spriteWidth, spriteHeight)),
		}))},
	{ "jump", new AnimatorState(new Animation(std::vector<AnimationFrame*>{
			new AnimationFrame(1.f, Rectf(spriteWidth * 3, spriteHeight * 1, spriteWidth, spriteHeight)),
		}))},
	{ "shoot", new AnimatorState(new Animation(std::vector<AnimationFrame*>{
			new AnimationFrame(0.15f, Rectf(spriteWidth * 0, spriteHeight * 4, spriteWidth, spriteHeight)),
			new AnimationFrame(0.15f, Rectf(spriteWidth * 1, spriteHeight * 4, spriteWidth, spriteHeight)),
		}))},
	{ "shootCrouched", new AnimatorState(new Animation(std::vector<AnimationFrame*>{
			new AnimationFrame(0.15f, Rectf(spriteWidth * 2, spriteHeight * 4, spriteWidth, spriteHeight)),
			new AnimationFrame(0.15f, Rectf(spriteWidth * 3, spriteHeight * 4, spriteWidth, spriteHeight)),
		}))},
	};

	const std::list<AnimatorTransition*> playerTransitions
	{
		new ConditionalAnimatorTransition("idle", "crouch", "isCrouched", true),
		new ConditionalAnimatorTransition("idle", "shoot", "isShooting", true),
		new ConditionalAnimatorTransition("idle", "jump", "isGrounded", false),
		new ConditionalAnimatorTransition("idle", "walk", "isWalking", true),

		new ConditionalAnimatorTransition("crouch", "idle", "isCrouched", false),
		new ConditionalAnimatorTransition("crouch", "shootCrouched", "isShooting", true),

		new AnimatorAnimationEndTransition("shoot", "idle"),

		new AnimatorAnimationEndTransition("shootCrouched", "crouch"),

		new ConditionalAnimatorTransition("jump", "idle", "isGrounded", true),
		new ConditionalAnimatorTransition("jump", "shoot", "isShooting", true),

		new ConditionalAnimatorTransition("walk", "idle", "isWalking", false),
		new ConditionalAnimatorTransition("walk", "crouch", "isCrouched", true),
		new ConditionalAnimatorTransition("walk", "jump", "isGrounded", false),
		new ConditionalAnimatorTransition("walk", "shoot", "isShooting", true),

	};

	m_pPlayer->AddComponent(new AnimatorRenderer(
		m_pPlayer,
		m_pTextureCache->GetTexture("player"),
		playerStates,
		playerTransitions,
		"idle"
	));


	// PHYSICS
	m_pPlayer->AddComponent(new PlayerCollider(m_pPlayer));
	m_pPlayer->AddComponent(new PhysicsBody(m_pPlayer));

	// LOGIC
	m_pPlayer->AddComponent(new PlayerController(m_pPlayer));

	m_pPlayer->Initialize();
}
