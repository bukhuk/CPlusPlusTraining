if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

add_library(thread_safe_lookup_table INTERFACE)

target_include_directories(thread_safe_lookup_table INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set(Boost_NO_BOOST_CMAKE ON)
find_package(Boost REQUIRED COMPONENTS thread)

if(Boost_FOUND)
	add_executable(thread_safe_lookup_table_bench main.cpp)
	target_link_libraries(thread_safe_lookup_table_bench PRIVATE
		Boost::thread
		thread_safe_lookup_table
	)
endif()
