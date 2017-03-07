cmake_minimum_required(VERSION 3.6)
project(GStreamerTest)

set(GSTREAMER_TEST_VERSION_MAJOR 1)
set(GSTREAMER_TEST_VERSION_MINOR 0)
set(GSTREAMER_TEST_VERSION "${GSTREAMER_TEST_VERSION_MAJOR}.${GSTREAMER_TEST_VERSION_MINOR}")

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake CACHE STRING
        "CMake module path." FORCE)

find_package(GStreamer REQUIRED)

include(add_defines)
include(config)
include(dump_vars)
include(setup_default_options)
include(platform)

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)

set(BUILD_SHARED_LIBS ON)
set(BUILD_TESTS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(CONFIG_DIR "debug" CACHE STRING "Build config directory" FORCE)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(CONFIG_DIR "release" CACHE STRING "Build config directory" FORCE)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel")
    set(CONFIG_DIR "releaseMinSize" CACHE STRING "Build config directory" FORCE)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
    set(CONFIG_DIR "releaseMinSize" CACHE STRING "Build config directory" FORCE)
else()
    message(FATAL_ERROR "Invalid build type: " ${CMAKE_BUILD_TYPE})
endif()

set(BUILD_BASE_DIR ${CMAKE_SOURCE_DIR}/build CACHE STRING
        "Build root directory.")
set(CMAKE_BINARY_DIR ${BUILD_BASE_DIR}/${CONFIG_DIR} CACHE STRING
        "Build directory.")
message(STATUS "Build base directory: " ${BUILD_BASE_DIR})
message(STATUS "Build config directory: " ${CMAKE_BINARY_DIR})

set(OUTPUT_BASE_DIR ${CMAKE_SOURCE_DIR}/output)
message(STATUS "Output base directory: " ${OUTPUT_BASE_DIR})

if(WIN_MSVC)
    set(GSTREAMER_TEST_PLATFORM "PC_WINDOWS" CACHE STRING "Defines on what platform cppsdk will run")
    set(FLAGS_CXX
            /Wall /WX- /Gd /GR /sdl- /Zc:wchar_t /Zc:inline /fp:precise)
    set(FLAGS_CXX_DEBUG /Od /Gm- /ZI /RTC1 /MDd)
    set(FLAGS_CXX_RELEASE /Ox /GL /GS /Gy /Oi /MD)
    set(FLAGS_CXX_MINSIZEREL /O1 /GL /GS /Gy /Oi /MD)
    set(FLAGS_CXX_RELWITHDEBINFO /O2 /GL /GS /Gy /Oi /Zi /MD)

    set(FLAGS_C
            /Wall /WX- /Gd /GR /sdl- /Zc:wchar_t /Zc:inline /fp:precise)
    set(FLAGS_C_DEBUG /Od /Gm- /ZI /RTC1 /MDd)
    set(FLAGS_C_RELEASE /Ox /GL /GS /Gy /Oi /MD)
    set(FLAGS_C_MINSIZEREL /O1 /GL /GS /Gy /Oi /MD)
    set(FLAGS_C_RELWITHDEBINFO /O2 /GL /GS /Gy /Oi /Zi /MD)

    set(DEFINES __DYNAMIC_LINKAGE__ _CRT_SECURE_NO_WARNINGS WIN32 _WINDOWS)
    set(DEFINES_DEBUG _DEBUG)
    set(DEFINES_RELEASE NDEBUG)
    set(DEFINES_MINSIZEREL NDEBUG)
    set(DEFINES_RELWITHDEBINFO NDEBUG)

elseif(MINGW)
    set(GSTREAMER_TEST_PLATFORM "PC_MINGW" CACHE STRING "Defines on what platform cppsdk will run")
    set(FLAGS_CXX -std=c++11 -Wall -Wextra -fPIC)
    set(FLAGS_CXX_DEBUG -O0 -g)
    set(FLAGS_CXX_RELEASE -O3)
    set(FLAGS_CXX_MINSIZEREL -O3)
    set(FLAGS_CXX_RELWITHDEBINFO -O2 -g)

    set(FLAGS_C -Wall -Wextra -fPIC)
    set(FLAGS_C_DEBUG -O0 -g)
    set(FLAGS_C_RELEASE -O3)
    set(FLAGS_C_MINSIZEREL -O3)
    set(FLAGS_C_RELWITHDEBINFO -O2 -g)

    set(DEFINES )
    set(DEFINES_DEBUG _DEBUG)
    set(DEFINES_RELEASE NDEBUG)
    set(DEFINES_MINSIZEREL NDEBUG)
    set(DEFINES_RELWITHDEBINFO NDEBUG)

elseif(LINUX)
    set(GSTREAMER_TEST_PLATFORM "PC_UNIX" CACHE STRING "Defines on what platform cppsdk will run")
    set(FLAGS_CXX -std=c++11 -Wall -Wextra -fPIC)
    set(FLAGS_CXX_DEBUG -O0 -g)
    set(FLAGS_CXX_RELEASE -O3)
    set(FLAGS_CXX_MINSIZEREL -O3)
    set(FLAGS_CXX_RELWITHDEBINFO -O2 -g)

    set(FLAGS_C -Wall -Wextra -fPIC)
    set(FLAGS_C_DEBUG -O0 -g)
    set(FLAGS_C_RELEASE -O3)
    set(FLAGS_C_MINSIZEREL -O3)
    set(FLAGS_C_RELWITHDEBINFO -O2 -g)

    set(DEFINES )
    set(DEFINES_DEBUG _DEBUG)
    set(DEFINES_RELEASE NDEBUG)
    set(DEFINES_MINSIZEREL NDEBUG)
    set(DEFINES_RELWITHDEBINFO NDEBUG)

elseif(APPLE)
    set(GSTREAMER_TEST_PLATFORM "PC_MAC" CACHE STRING "Defines on what platform cppsdk will run")
    set(FLAGS_CXX -std=c++11 -Wall -Wextra -fPIC)
    set(FLAGS_CXX_DEBUG -O0 -g)
    set(FLAGS_CXX_RELEASE -O3)
    set(FLAGS_CXX_MINSIZEREL -O3)
    set(FLAGS_CXX_RELWITHDEBINFO -O2 -g)

    set(FLAGS_C -Wall -Wextra -fPIC)
    set(FLAGS_C_DEBUG -O0 -g)
    set(FLAGS_C_RELEASE -O3)
    set(FLAGS_C_MINSIZEREL -O3)
    set(FLAGS_C_RELWITHDEBINFO -O2 -g)

    set(DEFINES )
    set(DEFINES_DEBUG _DEBUG)
    set(DEFINES_RELEASE NDEBUG)
    set(DEFINES_MINSIZEREL NDEBUG)
    set(DEFINES_RELWITHDEBINFO NDEBUG)

else()
    message(STATUS "Unsupported platform " ${CMAKE_HOST_SYSTEM})
    return()
endif()

if (BUILDREF_GSTREAMER_TEST)
    add_defines(DEFINES BUILDREF_GSTREAMER_TEST="${BUILDREF_GSTREAMER_TEST}")
else()
    add_defines(DEFINES BUILDREF_GSTREAMER_TEST="${GSTREAMER_TEST_VERSION}")
endif()

if(CMAKE_USE_PTHREADS_INIT)
    message(STATUS "Adding pthread flags")
    list(APPEND FLAGS_CXX -pthread)
    list(APPEND FLAGS_C -pthread)
endif()

set(CMAKE_COMPILER_IS_CLANG OFF)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "Using Clang")
    set(CMAKE_COMPILER_IS_CLANG ON)
elseif(${CMAKE_COMPILER_IS_GNUCXX})
    message(STATUS "Using Gcc")
else()
    message(STATUS "Compiler " ${CMAKE_CXX_COMPILER_ID})
endif()

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/gstreamertest.pc.in"
        "${CMAKE_BINARY_DIR}/gstreamertest.pc"
        @ONLY)

# uninstall target
configure_file(
        ${CMAKE_SOURCE_DIR}/cmake/uninstall.cmake.in
        ${CMAKE_BINARY_DIR}/uninstall.cmake
        IMMEDIATE @ONLY)

add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/uninstall.cmake)

add_custom_target(install_${PROJECT_NAME}
        $(MAKE) install
        COMMENT "Installing ${PROJECT_NAME}")

install(FILES ${CMAKE_BINARY_DIR}/gstreamertest.pc DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig")

add_subdirectory(source)

setup_default_options()
