cmake_minimum_required(VERSION 3.14)
project(tests)

add_executable(${PROJECT_NAME} test_base64Converter.cpp test_resizeImage.cpp)

set(CMAKE_CXX_STANDARD 17)

target_link_libraries(${PROJECT_NAME} PUBLIC
                                    calculations
                                    gtest
                                    gtest_main
                                    )