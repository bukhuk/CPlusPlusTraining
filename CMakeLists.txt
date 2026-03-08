cmake_minimum_required(VERSION 3.15)
project(EngineSystems LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(USE_ASAN "Enable Address Sanitizer" OFF)
option(USE_TSAN "Enable Thread Sanitizer" OFF)

if(USE_ASAN)
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
endif()

if(USE_TSAN)
    add_compile_options(-fsanitize=thread)
    add_link_options(-fsanitize=thread)
endif()

add_subdirectory(Arena)
add_subdirectory(DataBuffer)
add_subdirectory(DataStructuresWithLocks/ThreadSafeStack)
add_subdirectory(DataStructuresWithLocks/TrreadSafeLookupTable)
add_subdirectory(StaticString)
add_subdirectory(StringPool)
