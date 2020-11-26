cmake_minimum_required(VERSION 3.10)

project(rp4k_gameengine)

include_directories(include deps/box2d/include deps/rapidjson/include deps/sfml/include)

set(SOURCES
	src/main.cc
	src/engine.cc

	src/systems/render.cc
)

set(HEADERS
	include/component.h
	include/engine.h

	include/systems/render.h
)

set(BUILD_DYNAMIC_LIBS OFF)

add_subdirectory(deps)

add_executable(rp4k_gameengine ${SOURCES} ${HEADERS})
target_link_libraries(rp4k_gameengine box2d sfml-graphics sfml-system sfml-window)

