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
#include "LadderCollider.h"
#include "PhysicsHandler.h"
#include "PlayerCamera.h"
#include "PlayerCollider.h"
#include "LadderCollider.h"
#include "ProjectilePool.h"
#include "Texture.h"
#include "TextureCache.h"
#include "Transform.h"
#include "Zombie.h"
#include "ZombieCollider.h"



void LevelScene::InitializeScene()
{
	std::cout << "Controls:\nArrows keys: move\nJ: jump\nK: shoot";


	TextureCache *tCache = GetTextureCache();
	// Mac
	tCache->SetTextureDirectory("../");
	// Linux
	tCache->SetTextureDirectory("");

	m_pProjectilePool = new ProjectilePool(this);

	CreatePlayer();

	m_pCamera = new PlayerCamera(m_pPlayer->GetComponent<Transform>());
	// Center camera at start
	m_pCamera->MovePosition(Vector2f(-450, -300));

	//for(int i=0; i<50; i++)
		CreateEnemy();

	CreateLevel();
}


LevelScene::~LevelScene()
{
	delete m_pProjectilePool;
}

void LevelScene::UpdateScene(float deltaTime)
{
	// Parallax the background
	const float newXPos{ (m_pCamera->GetPosition().x * 0.2f) };
	m_pBackgroundTransform->SetPosition(Vector2f(newXPos, 0));

	// Debug for enemy spawn
	if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_SPACE] && !m_pEnemy->GetParent()->IsActive())
	{
		m_pEnemy->GetParent()->SetActive(true);

		m_pEnemy->Reset();
		m_pEnemy->GetParent()->GetComponent<Transform>()->SetPosition(Vector2f(150, 55));
	}
}

void LevelScene::DrawScene() const
{
	m_pPhysicsHandler->DrawDebugColliders();
}

ProjectilePool* LevelScene::GetProjectilePool() const
{
	return m_pProjectilePool;
}

Entity* LevelScene::GetPlayer() const
{
	return m_pPlayer;
}

void LevelScene::CreatePlayer()
{
	m_pTextureCache->LoadTexture("player", "Resources/player.png");

	m_pPlayer = m_pEntityKeeper->CreateEntity(100, "Player");
	m_pPlayer->AddComponent(new Transform(m_pPlayer, Vector2f(80, 40)));

	// RENDERING
	const float spriteWidth{ 22.f };
	const float spriteHeight{ 25.f };

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
	{ "climb", new AnimatorState(new Animation(std::vector<AnimationFrame*>{
			new AnimationFrame(0.15f, Rectf(spriteWidth * 0, spriteHeight * 3, spriteWidth, spriteHeight)),
			new AnimationFrame(0.15f, Rectf(spriteWidth * 1, spriteHeight * 3, spriteWidth, spriteHeight)),
		}))},
	{ "hurt", new AnimatorState(new Animation(std::vector<AnimationFrame*>{	
			new AnimationFrame(1.f, Rectf(spriteWidth * 0, spriteHeight * 5, spriteWidth, spriteHeight)),
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

		new ConditionalAnimatorTransition("idle", "climb", "isClimbing", true),
		new ConditionalAnimatorTransition("crouch", "climb", "isClimbing", true),
		new ConditionalAnimatorTransition("jump", "climb", "isClimbing", true),
		new ConditionalAnimatorTransition("walk", "climb", "isClimbing", true),

		new ConditionalAnimatorTransition("climb", "idle", "isClimbing", false),

		new ConditionalAnimatorTransition("idle", "hurt", "isHurt", true),
		new ConditionalAnimatorTransition("crouch", "hurt", "isHurt", true),
		new ConditionalAnimatorTransition("shoot", "hurt", "isHurt", true),
		new ConditionalAnimatorTransition("shootCrouched", "hurt", "isHurt", true),
		new ConditionalAnimatorTransition("jump", "hurt", "isHurt", true),
		new ConditionalAnimatorTransition("walk", "hurt", "isHurt", true),

		new ConditionalAnimatorTransition("hurt", "idle", "isHurt", false),
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

void LevelScene::CreateEnemy()
{
	Texture* pTexture = GetTextureCache()->GetTexture("zombie");

	if(!pTexture)
		pTexture = GetTextureCache()->LoadTexture("zombie", "Resources/zombie.png");

	Entity* pEnemy = m_pEntityKeeper->CreateEntity(5, "Enemy");

	printf("pTexture = %p, pEnemy = %p\n", pTexture, pEnemy);

	// FIXME: Hardcoded with of 2500
	Vector2f pos{ (float)(rand() % 2500), 55 };
	//Vector2f(150, 55)
	pEnemy->AddComponent(new Transform(pEnemy, pos));

	// RENDERING
	const float spriteWidth{ 22.f };
	const float spriteHeight{ 30.f };

	const std::unordered_map<std::string, AnimatorState*> enemyStates
	{
	{ "spawn", new AnimatorState(new Animation(std::vector<AnimationFrame*>{
			new AnimationFrame(0.25f, Rectf(spriteWidth * 0, spriteHeight * 1, spriteWidth, spriteHeight)),
			new AnimationFrame(0.25f, Rectf(spriteWidth * 1, spriteHeight * 1, spriteWidth, spriteHeight)),
			new AnimationFrame(0.25f, Rectf(spriteWidth * 2, spriteHeight * 1, spriteWidth, spriteHeight)),
			new AnimationFrame(0.25f, Rectf(spriteWidth * 3, spriteHeight * 1, spriteWidth, spriteHeight)),
			new AnimationFrame(0.25f, Rectf(spriteWidth * 4, spriteHeight * 1, spriteWidth, spriteHeight)),
		}))},
	{ "walk", new AnimatorState(new Animation(std::vector<AnimationFrame*>{
			new AnimationFrame(0.25f, Rectf(spriteWidth * 5, spriteHeight * 1, spriteWidth, spriteHeight)),
			new AnimationFrame(0.25f, Rectf(spriteWidth * 6, spriteHeight * 1, spriteWidth, spriteHeight)),
		}))},
	{ "death", new AnimatorState(new Animation(std::vector<AnimationFrame*>{
			new AnimationFrame(0.1f, Rectf(spriteWidth * 7, spriteHeight * 1, spriteWidth, spriteHeight)),
			new AnimationFrame(0.1f, Rectf(spriteWidth * 8, spriteHeight * 1, spriteWidth, spriteHeight)),
			new AnimationFrame(0.1f, Rectf(spriteWidth * 9, spriteHeight * 1, spriteWidth, spriteHeight)),
		}))},
	};

	const std::list<AnimatorTransition*> enemyTransitions
	{
		new ConditionalAnimatorTransition("walk", "death", "isDead", true),
	};

	pEnemy->AddComponent(new AnimatorRenderer(
		pEnemy,
		pTexture, 
		enemyStates, 
		enemyTransitions, 
"walk"
	));

	// LOGIC
	pEnemy->AddComponent(new ZombieCollider(pEnemy, std::vector<Vector2f>{
		Vector2f(-spriteWidth / 2, -spriteHeight / 2),
		Vector2f(-spriteWidth / 2, spriteHeight / 2),
		Vector2f(spriteWidth / 2, spriteHeight / 2),
		Vector2f(spriteWidth / 2, -spriteHeight / 2),
	}));

	pEnemy->AddComponent(new PhysicsBody(pEnemy));

	m_pEnemy = new Zombie(pEnemy, this);
	pEnemy->AddComponent(m_pEnemy);

	pEnemy->Initialize();
}

void LevelScene::CreateLevel()
{
	Texture* foreground{ m_pTextureCache->LoadTexture("level1Foreground", "Resources/level1Foreground.png") };
	Texture* background{ m_pTextureCache->LoadTexture("level1Background", "Resources/level1Background.png") };

	m_LevelSize = Vector2f(foreground->GetWidth(), foreground->GetHeight());

	Entity* pBackground{ GetEntityKeeper()->CreateEntity(-10) };

	m_pBackgroundTransform = new Transform(pBackground, Vector2f(m_LevelSize.x / 2, 0));
	pBackground->AddComponent(m_pBackgroundTransform);
	pBackground->AddComponent(new Renderer(pBackground, background));

	pBackground->Initialize();


    // Ground
	Entity* pForeground{ GetEntityKeeper()->CreateEntity(0) };

	pForeground->AddComponent(new Transform(pForeground, Vector2f(0, 0)));
	pForeground->AddComponent(new Renderer(pForeground, foreground));

	// Hardcoded values for map collision TODO: json-ify
	pForeground->AddComponent(new Collider(pForeground, std::vector<Vector2f>{
		Vector2f(0, 0),
		Vector2f(0, 40),
		Vector2f(2000, 40),
		Vector2f(2000, 0),
	}));
    // Elevated Ground
	pForeground->AddComponent(new Collider(pForeground, std::vector<Vector2f>{
		Vector2f(610 + 492, 110),
		Vector2f(610 + 492, 110 + 10),
		Vector2f(610, 110 + 10),
		Vector2f(610, 110),
	}));
	// Level wall Left
	pForeground->AddComponent(new Collider(pForeground, std::vector<Vector2f>{
		Vector2f(-5, 0),
		Vector2f(-5, 200),
		Vector2f(0, 200),
		Vector2f(0, 0),
	}));
    pForeground->SetTag("foreground");

	pForeground->Initialize();

	CreateLadder(727);
	CreateLadder(919);
	CreateLadder(1078);

    // Deathzone - area below the screen where the player dies
	Entity* pDeath{ GetEntityKeeper()->CreateEntity(-10) };
	pDeath->AddComponent(new Transform(pDeath, Vector2f(0, 0)));
	pDeath->AddComponent(new Collider(pDeath, std::vector<Vector2f>{
                Vector2f(0, -10),
                Vector2f(foreground->GetWidth(), -10),
                Vector2f(foreground->GetWidth(), 10),
                Vector2f(0, 10),
    }));
    pDeath->SetTag("deathzone");
	pDeath->Initialize();

    // Gravestones
	CreateGrave(Vector2f{ 54, 40});
	CreateGrave(Vector2f{ 245, 40});
	CreateGrave(Vector2f{ 420, 40});
	CreateGrave(Vector2f{ 532, 40});
	CreateGrave(Vector2f{ 756, 40});
	CreateGrave(Vector2f{ 772, 120});
	CreateGrave(Vector2f{ 868, 120});
	CreateGrave(Vector2f{ 965, 120});
	CreateGrave(Vector2f{ 965, 40});
	CreateGrave(Vector2f{ 1108, 40});
	CreateGrave(Vector2f{ 1268, 40});
	CreateGrave(Vector2f{ 1524, 40});

}

void LevelScene::CreateLadder(float xCoord) const
{
	Entity* pLadder1{ m_pEntityKeeper->CreateEntity(0, "Ladder") };

	const float ladderWidth{ 15.f };
	const float ladderHeight{ 104.f };

	pLadder1->AddComponent(new Transform(pLadder1, Vector2f(xCoord, 92)));
	pLadder1->AddComponent(new LadderCollider(pLadder1, std::vector<Vector2f>{
		Vector2f(-ladderWidth / 2, -ladderHeight / 2),
			Vector2f(-ladderWidth / 2, ladderHeight / 2),
			Vector2f(ladderWidth / 2, ladderHeight / 2),
			Vector2f(ladderWidth / 2, -ladderHeight / 2),
	}));

	pLadder1->Initialize();
}

void LevelScene::CreateGrave(Vector2f coord) const
{
    // Gravestone
    std::vector<Vector2f> stoneVector{
                Vector2f(0, 0),
                Vector2f(0, 12),
                Vector2f(6, 12),
                Vector2f(6, 0),
    };
	Entity* pStone{ GetEntityKeeper()->CreateEntity(0) };
	pStone->AddComponent(new Transform(pStone, coord)); 
	pStone->AddComponent(new Collider(pStone, stoneVector));
    pStone->SetTag("gravestone");
	pStone->Initialize();
}

