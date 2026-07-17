cmake_minimum_required(VERSION 3.20)

project(tuple_util VERSION 1.0 LANGUAGES CXX)

add_library(tuple_util INTERFACE)

target_compile_features(tuple_util INTERFACE cxx_std_23)

target_include_directories(tuple_util INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp") 
	set(CMAKE_CXX_STANDARD 23)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

	add_executable(util ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

	target_link_libraries(util PRIVATE tuple_util)
endif()