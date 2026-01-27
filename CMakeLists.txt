cmake_minimum_required(VERSION 3.10)
project(ptusa_engineer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

# Source files
set(EDITOR_SOURCES
    src/editor/draw_info.cpp
    src/editor/tree_view_item.cpp
)

set(TECHOBJECT_SOURCES
    src/techobject/action.cpp
)

# Create library
add_library(ptusa_engineer_lib STATIC
    ${EDITOR_SOURCES}
    ${TECHOBJECT_SOURCES}
)

# Enable testing
enable_testing()

# Add test subdirectory
add_subdirectory(tests)

# Add example executable
add_executable(visualization_example
    examples/visualization_example.cpp
)

target_link_libraries(visualization_example
    ptusa_engineer_lib
)
