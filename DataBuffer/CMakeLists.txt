add_library(data_buffer INTERFACE)

target_include_directories(data_buffer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(data_buffer_bench main.cpp)
target_link_libraries(data_buffer_bench PRIVATE data_buffer)
 
