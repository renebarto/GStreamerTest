# - Try to find GObject
# Once done this will define
#
#  GOBJECT_FOUND - system has GObject
#  GOBJECT_INCLUDE_DIR - the GObject include directory
#  GOBJECT_LIBRARIES - the libraries needed to use GObject
#  GOBJECT_DEFINITIONS - Compiler switches required for using GObject

# Copyright (c) 2006, Tim Beaulen <tbscope@gmail.com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

message(STATUS "Find GObject2")

if(GOBJECT_INCLUDE_DIR AND GOBJECT_LIBRARIES)
    # in cache already
    set(GObject_FIND_QUIETLY TRUE)
else()
    set(GObject_FIND_QUIETLY FALSE)
endif()

if(NOT WIN32)
    # use pkg-config to get the directories and then use these values
    # in the find_path() and find_library() calls
    FIND_PACKAGE(PkgConfig)
    PKG_CHECK_MODULES(PC_GOBJECT gobject-2.0)
    #MESSAGE(STATUS "DEBUG: GObject include directory = ${GOBJECT_INCLUDE_DIRS}")
    #MESSAGE(STATUS "DEBUG: GObject link directory = ${GOBJECT_LIBRARY_DIRS}")
    #MESSAGE(STATUS "DEBUG: GObject CFlags = ${GOBJECT_CFLAGS}")
    set(GOBJECT_DEFINITIONS ${PC_GOBJECT_CFLAGS_OTHER})
endif()

find_path(GOBJECT_INCLUDE_DIR gobject.h
    PATHS
    ${PC_GOBJECT_INCLUDEDIR}
    ${PC_GOBJECT_INCLUDE_DIRS}
    PATH_SUFFIXES glib-2.0/gobject/)

find_library(_GObjectLibs NAMES gobject-2.0
    PATHS
    ${PC_GOBJECT_LIBDIR}
    ${PC_GOBJECT_LIBRARY_DIRS})
find_library(_GModuleLibs NAMES gmodule-2.0
    PATHS
    ${PC_GOBJECT_LIBDIR}
    ${PC_GOBJECT_LIBRARY_DIRS})
find_library(_GThreadLibs NAMES gthread-2.0
    PATHS
    ${PC_GOBJECT_LIBDIR}
    ${PC_GOBJECT_LIBRARY_DIRS})
find_library(_GLibs NAMES glib-2.0
    PATHS
    ${PC_GOBJECT_LIBDIR}
    ${PC_GOBJECT_LIBRARY_DIRS})

set(GOBJECT_LIBRARIES ${_GObjectLibs} ${_GModuleLibs} ${_GThreadLibs} ${_GLibs} )

if(GOBJECT_INCLUDE_DIR AND GOBJECT_LIBRARIES)
    set(GOBJECT_FOUND TRUE)
else()
    set(GOBJECT_FOUND FALSE)
endif()

if(GOBJECT_FOUND)
    if(NOT GObject_FIND_QUIETLY)
        MESSAGE(STATUS "Found GObject libraries: ${GOBJECT_LIBRARIES}")
        MESSAGE(STATUS "Found GObject includes : ${GOBJECT_INCLUDE_DIR}")
    endif()
else()
    if(GObject_FIND_REQUIRED)
        MESSAGE(STATUS "Could NOT find GObject")
    endif()
endif()

mark_as_advanced(GOBJECT_INCLUDE_DIR _GObjectLibs _GModuleLibs _GThreadLibs _GLibs)