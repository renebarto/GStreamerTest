cmake_minimum_required(VERSION 3.6)
project(GStreamerTest)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
find_package(GStreamer REQUIRED)

message(STATUS "GLib includes: " ${GLIB2_INCLUDE_DIRS})
message(STATUS "GLib library: " ${GLIB2_LIBRARIES})
message(STATUS "GObject includes1: " ${GOBJECT_INCLUDE_DIR})
message(STATUS "GObject libraries: " ${GOBJECT_LIBRARIES})
message(STATUS "GStreamer includes: " ${GSTREAMER_INCLUDE_DIRS})
message(STATUS "GStreamer libraries: " ${GSTREAMER_LIBRARIES} " " ${GSTREAMER_BASE_LIBRARIES} " " ${GSTREAMER_APP_LIBRARIES})

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME}
        PRIVATE ${GOBJECT_INCLUDE_DIR} ${GSTREAMER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GOBJECT_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GSTREAMER_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GSTREAMER_BASE_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GSTREAMER_APP_LIBRARIES})