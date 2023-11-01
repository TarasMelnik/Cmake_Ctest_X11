# Ctests
include(FetchContent)
SET(PROJ_TEST "luggage_belts_test")
#PROJECT(${PROJ_TEST_NAME} CXX C)
#enable_testing()

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)
add_executable(${PROJ_TEST} luggage_belts_test.cpp)

# target_link_libraries(${PROJ_TEST}  l_b_library)

target_link_libraries(${PROJ_TEST}  
                                    PRIVATE
                                    
                                    GTest::GTest
                                    )
target_link_libraries(${PROJ_TEST}  
                                    PUBLIC
                                    l_b_library
                                    )
add_test(NAME MyTest COMMAND ${PROJ_TEST})

