# Ctests
include(FetchContent)
SET(PROJ_TEST_NAME "luggage_belts_test")
# PROJECT(${PROJ_TEST_NAME} CXX C)
enable_testing()

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(${PROJ_TEST_NAME} luggage_belts_test.cpp)

target_link_libraries(${PROJ_TEST_NAME}
 PRIVATE
  GTest::GTest
  luggage_belts_test)

add_test(luggage_belts_gtest luggage_belts_test)
