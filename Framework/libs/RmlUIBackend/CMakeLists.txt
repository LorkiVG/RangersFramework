find_package(RmlUi REQUIRED)
message(STATUS "RmlUI finded")

target_link_libraries(VGFramework PRIVATE RmlCore RmlDebugger)

file(GLOB RMLUIVULCAN_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/Backends/RmlUi_Vulkan/*.h)
file(GLOB RMLUIBACKENDS_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/Backends/*.h)
file(GLOB RMLUIBACKENDS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Backends/*.cpp)

add_library(RmlUIBackend ${RMLUIBACKENDS_SOURCES})
target_sources(VGFramework PRIVATE ${RMLUIVULCAN_INCLUDES} ${RMLUIBACKENDS_INCLUDES} ${RMLUIBACKENDS_SOURCES})

target_link_libraries(RmlUIBackend PRIVATE RmlCore RmlDebugger)
target_link_libraries(RmlUIBackend PRIVATE ${CMAKE_DL_LIBS})
target_include_directories(RmlUIBackend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Backends/RmlUi_Vulkan)