cmake_minimum_required(VERSION 3.0)
project(AStartAlgorithm)

#Add the executable
add_executable(main src/main.cpp src/astar.cpp)

#Add include directories
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Include SFML headers
target_include_directories(main PRIVATE ${SFML_INCLUDE_DIR})

# Link SFML libraries
target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-system)