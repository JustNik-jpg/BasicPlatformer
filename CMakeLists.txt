cmake_minimum_required(VERSION 3.21)
project(BasicPlatformer)

set(CMAKE_CXX_STANDARD 23)

set(SDL2_INCLUDE_DIR E:/Files/Prog/cpp/libs/SDL2-2.0.20/include)
set(SDL2_LIB_DIR E:/Files/Prog/cpp/libs/SDL2-2.0.20/lib/x64)

set(SDL2_IMAGE_INCLUDE_DIR E:/Files/Prog/cpp/libs/SDL2_image-2.0.5/include)
set(SDL2_IMAGE_LIB_DIR E:/Files/Prog/cpp/libs/SDL2_image-2.0.5/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

include_directories(${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_IMAGE_LIB_DIR})

add_executable(BasicPlatformer main.cpp core/Game.cpp core/Game.h core/TextureManager.cpp core/TextureManager.h core/ecs/ECS.h core/ecs/ECS.cpp core/ecs/components/Component.h core/ecs/Types.h core/ecs/EntityManager.cpp core/ecs/EntityManager.h core/ecs/IComponentArray.cpp core/ecs/IComponentArray.h core/ecs/ComponentManager.cpp core/ecs/ComponentManager.h core/ecs/systems/System.h core/ecs/SystemManager.cpp core/ecs/SystemManager.h core/ecs/systems/MovementSystem.cpp core/ecs/systems/MovementSystem.h core/ecs/systems/RenderSystem.cpp core/ecs/systems/RenderSystem.h core/ecs/EntityHelper.cpp core/ecs/EntityHelper.h core/events/EventController.cpp core/events/EventController.h core/events/handlers/IEventHandler.h core/events/handlers/PlayerControlHandler.cpp core/events/handlers/PlayerControlHandler.h core/Engine.h core/tilemap/Tile.h core/tilemap/RoomController.cpp core/tilemap/RoomController.h core/ecs/systems/PhysicsSystem.cpp core/ecs/systems/PhysicsSystem.h core/utility/Vector2D.h core/collision/Collision.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
target_link_libraries(${PROJECT_NAME} SDL2_image )
