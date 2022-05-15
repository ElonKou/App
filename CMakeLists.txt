project(SomeApp)
cmake_minimum_required(VERSION 3.2)
add_definitions(-std=c++11 -Wall -Wformat)

file(GLOB APP_SRC "3rdparty/cppbase/*.hpp")
file(GLOB APP_SRC "3rdparty/imgui/*.cpp")
aux_source_directory(Frame APP_SRC)

MESSAGE(${APP_SRC})

include_directories(
    include
    ${PROJECT_SOURCE_DIR}/3rdparty/cppbase
    ${PROJECT_SOURCE_DIR}/3rdparty/imgui
    ${PROJECT_SOURCE_DIR}/3rdparty/stb
    ${PROJECT_SOURCE_DIR}/Frame
)

# [config]
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
# SET(CMAKE_BUILD_TYPE "Release")
# SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

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
    target_link_libraries(SomeApp GLEW glfw "-framework OpenGL")
elseif(UNIX)
    target_link_libraries(SomeApp glfw dl GLEW GL)
endif()
# add_subdirectory(modules)

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
