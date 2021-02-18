cmake_minimum_required(VERSION 3.10)

project(rp4k_game_engine)

include_directories(include deps/box2d/include deps/rapidjson/include deps/sfml/include)
set_property(GLOBAL PROPERTY CXX_STANDARD 11)

set(ENGINE_SOURCES
	src/engine.cc

	src/interface/button_map.cc
	src/interface/button.cc
	src/interface/main_camera.cc
	src/interface/pause_menu.cc
	src/interface/states.cc
	src/interface/tile.cc

	src/systems/animation.cc
	src/systems/input.cc
	src/systems/movement.cc
	src/systems/physics.cc
	src/systems/render.cc
)

set(ENGINE_HEADERS
	include/component.h
	include/engine.h

	include/interface/button_map.h
	include/interface/button.h
	include/interface/main_camera.h
	include/interface/pause_menu.h
	include/interface/states.h
	include/interface/tile.h

	include/systems/animation.h
	include/systems/input.h
	include/systems/movement.h
	include/systems/physics.h
	include/systems/render.h
)

set(BUILD_DYNAMIC_LIBS OFF)

add_subdirectory(deps)

add_library(rp4k_game_engine STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS})
add_executable(rp4k_game src/main.cc)

add_custom_command(
	TARGET rp4k_game POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E remove -f $<TARGET_FILE_DIR:rp4k_game>/res
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:rp4k_game>
)

target_link_libraries(rp4k_game_engine box2d sfml-graphics sfml-system sfml-window)
target_link_libraries(rp4k_game rp4k_game_engine)
