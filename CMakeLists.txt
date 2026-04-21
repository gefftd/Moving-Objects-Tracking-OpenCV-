set(CMAKE_MINIMUM_REQUIRED_VERSION 3.10)
project(Project3)

set(CMAKE_CXX_STANDARD 17)

add_executable(main
src/main.cpp
src/backGroundsub.cpp
src/ContourDetect.cpp
src/Track.cpp)
find_package(OpenCV REQUIRED)

set(target main)

target_include_directories(${target} PRIVATE include)

target_link_libraries(${target} ${OpenCV_LIBS})

