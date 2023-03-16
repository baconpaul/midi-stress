cmake_minimum_required(VERSION 3.10)
project(midi-stress VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "dont" FORCE)
set(RTMIDI_API_JACK OFF CACHE BOOL "dont" FORCE)
set(RTMIDI_API_ALSA OFF CACHE BOOL "dont" FORCE)
set(RTMIDI_BUILD_TESTING OFF CACHE BOOL "dont" FORCE)
add_subdirectory(libs/rtmidi)
add_subdirectory(libs/isocline)


add_executable(${PROJECT_NAME}
               src/main.cpp
               )
target_link_libraries(${PROJECT_NAME} PUBLIC rtmidi isocline)

               
