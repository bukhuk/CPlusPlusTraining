add_library(static_string INTERFACE)

target_include_directories(static_string INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(static_string_bench main.cpp)
target_link_libraries(static_string_bench PRIVATE static_string)
