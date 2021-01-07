cmake_minimum_required(VERSION 3.10)

project(rp4k_game_engine)

include_directories(include deps/box2d/include deps/rapidjson/include deps/sfml/include)

set(ENGINE_SOURCES
	src/engine.cc

	src/systems/animation.cc
	src/systems/render.cc
)

set(ENGINE_HEADERS
	include/component.h
	include/engine.h

	include/systems/animation.h
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
