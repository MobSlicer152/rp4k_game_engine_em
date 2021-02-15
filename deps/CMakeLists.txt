cmake_minimum_required(VERSION 3.10)

# Disable the Box2D unit tests and testbed, we have no use whatsoever for them and they cause build errors.
set(BOX2D_BUILD_TESTBED OFF)
set(BOX2D_BUILD_UNIT_TESTS OFF)

add_subdirectory(box2d)
add_subdirectory(sfml)
