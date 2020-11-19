cmake_minimum_required(VERSION 3.10)

project(rp4k_gameengine)

set(SOURCES
        src/main.cc
)

set(HEADERS)

set(BUILD_DYNAMIC_LIBS OFF)

add_subdirectory(deps)

add_executable(rp4k_gameengine ${SOURCES} ${HEADERS})
target_link_libraries(rp4k_gameengine box2d rapidjson sfml)

