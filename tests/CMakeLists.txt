# Download and configure Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable Google Test
enable_testing()
include(GoogleTest)

# Test executable
add_executable(ptusa_engineer_tests
    draw_info_test.cpp
    action_test.cpp
)

# Link against the library and Google Test
target_link_libraries(ptusa_engineer_tests
    ptusa_engineer_lib
    gtest_main
    gtest
)

# Discover tests
gtest_discover_tests(ptusa_engineer_tests)
