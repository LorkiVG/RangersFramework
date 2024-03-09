#VGFramework

message(STATUS "Started configure VGFramework")

set(GAME_VERSION "2424" CACHE STRING "Version of the game")

message(STATUS "Selected Game version: 2.1.${GAME_VERSION}")

add_library(VGFramework SHARED)

find_package(RmlUi REQUIRED)
message(STATUS "RmlUI finded")

target_link_libraries(VGFramework PRIVATE RmlCore RmlDebugger)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/RmlUIBackend)

target_include_directories(VGFramework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/RmlUIBackend/Backends)
target_link_libraries(VGFramework PRIVATE RmlUIBackend)

message(STATUS "RmlUI connected")

enable_language(ASM_MASM)

#Include VGFramework library files
file(GLOB CORE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/core/inc/*.h)
file(GLOB CORE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/core/src/*.cpp)

file(GLOB MODULES_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/modules/inc/*.h)
file(GLOB MODULES_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/modules/src/*.cpp)

file(GLOB GAMEOBJECTS_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/game-objects/${GAME_VERSION}/inc/*.h)
file(GLOB GAMEOBJECTS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/game-objects/${GAME_VERSION}/src/*.cpp)

set(GAMEOBJECTS_ASM
    game-objects/${GAME_VERSION}/src/TGalaxyAsm.asm
)

target_sources(VGFramework PRIVATE main.cpp)

target_sources(VGFramework PRIVATE ${CORE_INCLUDES} ${CORE_SOURCES})

target_sources(VGFramework PRIVATE ${MODULES_INCLUDES} ${MODULES_SOURCES})

target_sources(VGFramework PRIVATE ${GAMEOBJECTS_INCLUDES} ${GAMEOBJECTS_SOURCES})
target_sources(VGFramework PRIVATE ${GAMEOBJECTS_ASM})

source_group("core\\inc" FILES ${CORE_INCLUDES})
source_group("core\\src" FILES ${CORE_SOURCES})

source_group("core\\ui\\inc" FILES ${COREUI_INCLUDES})
source_group("core\\ui\\src" FILES ${COREUI_SOURCES})

source_group("core\\inc" FILES ${SCRIPTS_INCLUDES})
source_group("core\\src" FILES ${SCRIPTS_SOURCES})

source_group("modules\\inc" FILES ${MODULES_INCLUDES})
source_group("modules\\src" FILES ${MODULES_SOURCES})

source_group("game-objects\\inc" FILES ${SOURCES_INCLUDES})
source_group("game-objects\\src" FILES ${SOURCES_SOURCES})
source_group("game-objects\\asm" FILES ${SOURCES_SOURCES_ASM})


target_include_directories(VGFramework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core/inc)
target_include_directories(VGFramework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core/ui/inc)
target_include_directories(VGFramework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/scripts/inc)
target_include_directories(VGFramework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/modules/inc)
target_include_directories(VGFramework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/game-objects/${GAME_VERSION}/inc)
target_link_options(VGFramework PUBLIC "$<$<C_COMPILER_ID:MSVC>:-SAFESEH:NO>")

message(STATUS "Finished configure VGFramework")