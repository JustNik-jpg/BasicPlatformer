cmake_minimum_required(VERSION 3.21)
project(BasicPlatformer)

set(CMAKE_CXX_STANDARD 23)

set(SDL2_INCLUDE_DIR includes/SDL2/include)
set(SDL2_LIB_DIR includes/SDL2/lib/x64)

set(SDL2_IMAGE_INCLUDE_DIR includes/SDL_Image/include)
set(SDL2_IMAGE_LIB_DIR includes/SDL_Image/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

include_directories(${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_IMAGE_LIB_DIR})

add_executable(BasicPlatformer main.cpp core/Game.cpp core/Game.h core/TextureHelper.cpp core/TextureHelper.h core/ecs/ECS.h core/ecs/ECS.cpp core/ecs/components/Component.h core/ecs/Types.h core/ecs/EntityManager.cpp core/ecs/EntityManager.h core/ecs/IComponentArray.cpp core/ecs/IComponentArray.h core/ecs/ComponentManager.cpp core/ecs/ComponentManager.h core/ecs/systems/System.h core/ecs/SystemManager.cpp core/ecs/SystemManager.h core/ecs/systems/MovementSystem.cpp core/ecs/systems/MovementSystem.h core/ecs/systems/RenderSystem.cpp core/ecs/systems/RenderSystem.h core/ecs/EntityHelper.cpp core/ecs/EntityHelper.h core/events/EventController.cpp core/events/EventController.h core/events/handlers/IEventHandler.h core/events/handlers/PlayerControlHandler.cpp core/events/handlers/PlayerControlHandler.h core/Engine.h core/tilemap/Tile.h core/tilemap/RoomController.cpp core/tilemap/RoomController.h core/ecs/systems/PhysicsSystem.cpp core/ecs/systems/PhysicsSystem.h core/utility/Vector2D.h core/collision/Collision.h core/ecs/systems/ControlSystem.cpp core/ecs/systems/ControlSystem.h core/ecs/systems/LifetimeSystem.cpp core/ecs/systems/LifetimeSystem.h core/ecs/systems/AttackSystem.cpp core/ecs/systems/AttackSystem.h core/ecs/systems/FollowSystem.cpp core/ecs/systems/FollowSystem.h core/ecs/systems/CollisionSystem.cpp core/ecs/systems/CollisionSystem.h core/ecs/systems/DeathSystem.cpp core/ecs/systems/DeathSystem.h core/ecs/Constants.h core/ecs/systems/EnemyAISystem.cpp core/ecs/systems/EnemyAISystem.h core/collision/Collision.cpp core/ecs/systems/AnimationSystem.cpp core/ecs/systems/AnimationSystem.h core/visuals/AnimationHelper.cpp core/visuals/AnimationHelper.h core/tilemap/Tile.cpp core/ecs/systems/HealthDisplaySystem.cpp core/ecs/systems/HealthDisplaySystem.h core/world/WorldTimer.cpp core/world/WorldTimer.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
target_link_libraries(${PROJECT_NAME} SDL2_image )
