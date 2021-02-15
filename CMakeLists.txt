cmake_minimum_required(VERSION 3.0.2)
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PlotCsv)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(PythonLibs 2.7)

add_executable(${PROJECT_NAME} "main.cpp")


target_include_directories(${PROJECT_NAME} PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
