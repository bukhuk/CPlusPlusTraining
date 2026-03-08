add_library(string_pool INTERFACE)

target_include_directories(string_pool INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(string_pool_bench main.cpp)
target_link_libraries(string_pool_bench PRIVATE string_pool)
