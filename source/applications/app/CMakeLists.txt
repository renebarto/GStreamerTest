project(app)

include(setup_target_properties_library)
include(show_target_properties)

message("Setting up app")

set(APPLICATIONS_APP_TEST_DEFINITIONS
    CACHE INTERNAL "${PROJECT_NAME}: Definitions" FORCE)

set(APPLICATIONS_APP_TEST_INCLUDE
    include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

set(APPLICATIONS_APP_TEST_LIBS
    gstreamer++
    CACHE INTERNAL "${PROJECT_NAME}: Link libraries" FORCE)

file(GLOB APPLICATIONS_APP_TEST_INCLUDES include/*.h)
file(GLOB APPLICATIONS_APP_TEST_SOURCES src/*.cpp)

#if (INSTALL_HEADERS_TO_TARGET)
#    install(FILES ${APPLICATIONS_APP_TEST_INCLUDES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/cppsdk/generics)
#else()
#    foreach(path ${CMAKE_FIND_ROOT_PATH})
#        file(COPY ${APPLICATIONS_APP_TEST_INCLUDES} DESTINATION ${path}/usr/include/cppsdk/generics)
#    endforeach()
#endif()

set(APPLICATIONS_APP_TEST_INPUT
    ${APPLICATIONS_APP_TEST_SOURCES}
    ${APPLICATIONS_APP_TEST_INCLUDES}
    CACHE INTERNAL "${PROJECT_NAME}: Source files" FORCE)

add_executable(${PROJECT_NAME} ${APPLICATIONS_APP_TEST_INPUT})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${APPLICATIONS_APP_TEST_DEFINITIONS})
target_include_directories(${PROJECT_NAME} PRIVATE ${APPLICATIONS_APP_TEST_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE ${APPLICATIONS_APP_TEST_LIBS})
set_target_properties(${PROJECT_NAME} PROPERTIES DEFINE_SYMBOL APPLICATIONS_APP_TEST)
#set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${GSTREAMER_TEST_VERSION})

setup_target_properties_library(${PROJECT_NAME})

show_target_properties(${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
