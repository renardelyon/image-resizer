cmake_minimum_required(VERSION 3.14)
project(image_resizer)
SET(LIBASYIK_ENABLE_SOCI ON)  # if SOCI database support is desired
set(CMAKE_CXX_STANDARD 17)    # set to 14 or 17 when available

add_executable(${PROJECT_NAME} main.cpp 
external/cpp-base64/base64.cpp 
usecase/base64_converter/Base64Converter.cpp 
usecase/resize_image/ResizeImage.cpp) # add more source code here

add_subdirectory(tests)

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
endif()

find_package(libasyik)
if(libasyik_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${libasyik_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} libasyik)
endif()

find_package(Boost COMPONENTS context fiber  date_time url REQUIRED)
if(Boost_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} Boost::fiber Boost::context)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE external/json)
target_include_directories(${PROJECT_NAME} PRIVATE external/cpp-base64)
target_include_directories(${PROJECT_NAME} PUBLIC usecase/base64_converter)
target_include_directories(${PROJECT_NAME} PUBLIC usecase/resize_image)

find_package(SOCI REQUIRED) # if SOCI database support is desired
if(SOCI_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC /usr/include/postgresql)
    target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/include/soci)
    target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/include/soci/postgresql)
    target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/include/soci/sqlite3)
    target_link_libraries(${PROJECT_NAME} SOCI::soci_core SOCI::soci_postgresql SOCI::soci_sqlite3)
endif()

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenSSL::SSL)