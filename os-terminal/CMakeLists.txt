cmake_minimum_required(VERSION 3.12)

project(sgl-os-terminal)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/)
set(TARGET_SOURCES
  src/LinuxTerminal.cpp
  # src/WinTerminal.cpp
)

add_compile_definitions(_LINUX)
include_directories(include)
add_library(${PROJECT_NAME} ${TARGET_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME})
