cmake_minimum_required(VERSION 3.7)

project(gng)

set(OpenGL_GL_PREFERENCE GLVND)
if (!APPLE)
#	find_package(SDL2 REQUIRED)
#	find_package(SDL2_ttf REQUIRED)
#	find_package(SDL2_image REQUIRED)
#	find_package(SDL2_mixer REQUIRED)
endif()
find_package(OpenGL REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "-std=gnu++1z")

# Compile main enginelib library
add_library(enginelib STATIC
    Engine/Animation.h Engine/Animation.cpp
    Engine/AnimationFrame.h Engine/AnimationFrame.cpp
    Engine/AnimatorAnimationEndTransition.h Engine/AnimatorAnimationEndTransition.cpp
    Engine/AnimatorRenderer.h Engine/AnimatorRenderer.cpp
    Engine/AnimatorState.h Engine/AnimatorState.cpp
    Engine/AnimatorTransition.h Engine/AnimatorTransition.cpp
    Engine/base.h Engine/base.cpp
    Engine/Camera.h Engine/Camera.cpp
    Engine/Collider.h Engine/Collider.cpp
    Engine/collisions.h Engine/collisions.cpp
    Engine/Component.h Engine/Component.cpp
    Engine/ConditionalAnimatorTransition.h Engine/ConditionalAnimatorTransition.cpp
    Engine/Entity.h Engine/Entity.cpp
    Engine/EntityKeeper.h Engine/EntityKeeper.cpp
    Engine/Game.h Engine/Game.cpp
    Engine/InputHandler.h Engine/InputHandler.cpp
    Engine/Matrix2x3.h Engine/Matrix2x3.cpp
    Engine/PartialRenderer.h Engine/PartialRenderer.cpp
    Engine/PhysicsBody.h Engine/PhysicsBody.cpp
    Engine/PhysicsHandler.h Engine/PhysicsHandler.cpp
    Engine/Renderer.h Engine/Renderer.cpp
    Engine/Scene.cpp Engine/Scene.h
    Engine/SoundEffect.h Engine/SoundEffect.cpp
    Engine/SoundStream.h Engine/SoundStream.cpp
    Engine/structs.h Engine/structs.cpp
    Engine/SVGParser.h Engine/SVGParser.cpp
    Engine/TextureCache.h Engine/TextureCache.cpp
    Engine/Texture.h Engine/Texture.cpp
    Engine/Transform.h Engine/Transform.cpp
    Engine/utils.h Engine/utils.cpp
    Engine/Vector2f.h Engine/Vector2f.cpp

    # Game files
    Game/Zombie.h Game/Zombie.cpp
    Game/ZombieCollider.h Game/ZombieCollider.cpp
    Game/ProjectilePool.h Game/ProjectilePool.cpp
    Game/Projectile.h Game/Projectile.cpp
    Game/PlayerController.h Game/PlayerController.cpp
    Game/PlayerCollider.h Game/PlayerCollider.cpp
    Game/PlayerCamera.h Game/PlayerCamera.cpp
    Game/pch.h Game/pch.cpp
    Game/LevelScene.h Game/LevelScene.cpp
    Game/LadderCollider.h Game/LadderCollider.cpp
    Game/GhostsAndGoblins.h Game/GhostsAndGoblins.cpp
    Game/constants.h
)

if(APPLE)
	target_include_directories(enginelib PUBLIC "Engine"
		"/Library/Frameworks/SDL2.framework/Headers/"
		"/Library/Frameworks/SDL2_ttf.framework/Headers/"
		"/Library/Frameworks/SDL2_image.framework/Headers/"
		"/Library/Frameworks/SDL2_mixer.framework/Headers/"
	)
endif()

set(MY_SRC "Game/main.cpp")

add_executable(gng ${MY_SRC})
target_link_libraries(gng 
    enginelib
#	${SDL2_LIBRARIES}
#    ${SDL2mixer_INCLUDE_DIRS}
#    ${SDL2ttf_INCLUDE_DIRS}
#    ${SDL2image_INCLUDE_DIRS}
#    ${OPENGL_LIBRARIES}
#    "-lSDL2_image"
#    "-lSDL2_mixer"
#    "-lSDL2_ttf"
)
if(APPLE)
	target_link_libraries(gng
		"-framework OpenGL"
		"-framework SDL2"
		"-framework SDL2_image"
		"-framework SDL2_mixer"
		"-framework SDL2_ttf"
	)
endif()

if(APPLE)
set(CUR_TARGET gng-osx)
add_executable(${CUR_TARGET} MACOSX_BUNDLE ${MY_SRC})
target_link_libraries(${CUR_TARGET}
    enginelib
	"-framework OpenGL"
	"-framework SDL2"
	"-framework SDL2_image"
	"-framework SDL2_mixer"
	"-framework SDL2_ttf"
	)
file(COPY "Resources/level1Background.png" DESTINATION "${CUR_TARGET}.app/Contents/Resources")
file(COPY "Resources/level1Foreground.png" DESTINATION "${CUR_TARGET}.app/Contents/Resources")
file(COPY "Resources/player.png" DESTINATION "${CUR_TARGET}.app/Contents/Resources")
file(COPY "Resources/playerDebug.png" DESTINATION "${CUR_TARGET}.app/Contents/Resources")
file(COPY "Resources/projectiles.png" DESTINATION "${CUR_TARGET}.app/Contents/Resources")
file(COPY "Resources/zombie.png" DESTINATION "${CUR_TARGET}.app/Contents/Resources")
set_target_properties(${CUR_TARGET} PROPERTIES
    BUNDLE True
    MACOSX_BUNDLE_GUI_IDENTIFIER org.panaflexx.game.${CUR_TARGET}
    MACOSX_BUNDLE_BUNDLE_NAME ${CUR_TARGET}
    MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
)
endif()

# Dump all variables
if(DUMP_ALL_VARS)
	get_cmake_property(_variableNames VARIABLES)
	list (SORT _variableNames)
	foreach (_variableName ${_variableNames})
		message(STATUS "${_variableName}=${${_variableName}}")
	endforeach()
endif()
