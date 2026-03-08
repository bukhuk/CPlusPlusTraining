add_library(arena INTERFACE)

target_include_directories(arena INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(arena_bench main.cpp)
target_link_libraries(arena_bench PRIVATE arena)
