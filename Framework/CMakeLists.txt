#VGFramework

message(STATUS "Started configure VGFramework")

set(GAME_VERSION "2424" CACHE STRING "Version of the game")

message(STATUS "Selected Game version: 2.1.${GAME_VERSION}")

add_library(VGFramework SHARED)

find_package(RmlUi REQUIRED)
message(STATUS "RmlUI finded")

target_link_libraries(VGFramework PRIVATE RmlCore RmlDebugger)
message(STATUS "RmlUI connected")

enable_language(ASM_MASM)

#Include VGFramework library files
file(GLOB MODULES_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/modules/inc/*.h)
file(GLOB MODULES_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/modules/src/*.cpp)

file(GLOB GAMEOBJECTS_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/game-objects/${GAME_VERSION}/inc/*.h)
file(GLOB GAMEOBJECTS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/game-objects/${GAME_VERSION}/src/*.cpp)

set(GAMEOBJECTS_ASM
    game-objects/${GAME_VERSION}/src/TGalaxyAsm.asm
)

target_sources(VGFramework PRIVATE main.cpp)
target_sources(VGFramework PRIVATE ${MODULES_INCLUDES} ${MODULES_SOURCES})
target_sources(VGFramework PRIVATE ${GAMEOBJECTS_INCLUDES} ${GAMEOBJECTS_SOURCES})
target_sources(VGFramework PRIVATE ${GAMEOBJECTS_ASM})

source_group("modules\\Header Files" FILES ${MODULES_INCLUDES})
source_group("modules\\Source Files" FILES ${MODULES_SOURCES})

source_group("game-objects\\Header Files" FILES ${SOURCES_INCLUDES})
source_group("game-objects\\Source Files" FILES ${SOURCES_SOURCES})
source_group("game-objects\\Asm Files" FILES ${SOURCES_SOURCES_ASM})


target_include_directories(VGFramework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/modules/inc)
target_include_directories(VGFramework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/game-objects/${GAME_VERSION}/inc)
target_link_options(VGFramework PUBLIC "$<$<C_COMPILER_ID:MSVC>:-SAFESEH:NO>")

message(STATUS "Finished configure VGFramework")