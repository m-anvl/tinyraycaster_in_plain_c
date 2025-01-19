#[[
mkdir build
cd build
cmake ..
]]

cmake_minimum_required(VERSION 3.20)

project(
    tinyraycaster
    LANGUAGES C
)

set(TRG_NAME ${PROJECT_NAME})

add_executable(
    ${TRG_NAME}
    src/main.c
    src/common.h
    src/defs.h
    src/framebuffer.c
    src/framebuffer.h
    src/init.c
    src/init.h
    src/input.c
    src/input.h
    src/map.c
    src/map.h
    src/render.c
    src/render.h
    src/texture.c
    src/texture.h
    src/timer.c
    src/timer.h
    src/utils.c
    src/utils.h
)

# Add SDL3
find_package(SDL3 REQUIRED)

target_include_directories(${TRG_NAME} PUBLIC ${SDL3_INCLUDE_DIRS})
target_link_libraries(${TRG_NAME} PRIVATE SDL3::SDL3)

# Copies "SDL3.dll" to the directory where executable file is built
if(WIN32)
    add_custom_command(
        TARGET ${TRG_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:${TRG_NAME}>
        VERBATIM
    )
endif()

# Set the correct startup project for the Visual Studio
if(WIN32)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()