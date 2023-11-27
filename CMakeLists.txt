cmake_minimum_required(VERSION 3.10)

project(noia LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(external)


file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp src/*.cc)
file(GLOB_RECURSE headers CONFIGURE_DEPENDS include/*.h include/*.hpp)
add_executable(${PROJECT_NAME} ${sources} ${headers})

target_include_directories(${PROJECT_NAME} PUBLIC include/maple)


target_link_libraries(${PROJECT_NAME} PUBLIC glfw glad glm imgui)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)