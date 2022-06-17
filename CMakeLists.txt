cmake_minimum_required(VERSION 3.2)
set(APP_VERSION 0.2.3)
project(SomeApp VERSION ${APP_VERSION})
add_definitions(-std=c++11 -Wall -Wformat)

file(GLOB APP_SRC "3rdparty/cppbase/*.hpp")
file(GLOB APP_SRC "3rdparty/imgui/*.cpp")
aux_source_directory(Frame APP_SRC)
aux_source_directory(Demo/DemoCommon APP_SRC)
# aux_source_directory(Demo/AppDemo APP_SRC)
# aux_source_directory(Demo/View3D APP_SRC)
# aux_source_directory(Demo/Physics2D APP_SRC)
aux_source_directory(Demo/RayTracing APP_SRC)

add_subdirectory(3rdparty/assimp)

include_directories(
    include
    ${PROJECT_SOURCE_DIR}/3rdparty/cppbase
    ${PROJECT_SOURCE_DIR}/3rdparty/imgui
    ${PROJECT_SOURCE_DIR}/3rdparty/stb
    ${PROJECT_SOURCE_DIR}/3rdparty/assimp
    ${PROJECT_SOURCE_DIR}/Frame
    ${PROJECT_SOURCE_DIR}/Demo/DemoCommon
    # ${PROJECT_SOURCE_DIR}/Demo/AppDemo
    # ${PROJECT_SOURCE_DIR}/Demo/View3D
    # ${PROJECT_SOURCE_DIR}/Demo/Physics2D
    ${PROJECT_SOURCE_DIR}/Demo/RayTracing
)

# [config]
# SET(CMAKE_BUILD_TYPE "Debug")
# SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# set(CMAKE_INSTALL_PREFIX /opt/App)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

IF (APPLE)
	MESSAGE(STATUS "Code is build on Apple systems.")
    include_directories(
        /opt/homebrew/include
    )
    link_directories(
        /opt/homebrew/lib
    )
ENDIF ()

set(APP_INSTALL_PATH ${CMAKE_INSTALL_PREFIX})

configure_file(
    "${PROJECT_SOURCE_DIR}/AppConfig.hh.in"
    "${PROJECT_SOURCE_DIR}/Frame/AppConfig.hh"
)

# [build]
add_executable(SomeApp ${APP_SRC})

if(APPLE)
    target_link_libraries(SomeApp GLEW glfw assimp "-framework OpenGL")
elseif(UNIX)
    target_link_libraries(SomeApp glfw assimp dl GLEW GL)
endif()

# [install]
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# install(DIRECTORY resources app DESTINATION ${CMAKE_INSTALL_PREFIX})

# uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
