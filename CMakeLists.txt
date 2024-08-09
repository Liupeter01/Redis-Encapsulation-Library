cmake_minimum_required(VERSION 3.16)
include(FetchContent)
if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wall -Wextra)
endif(CMAKE_COMPILER_IS_GNUCXX)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/WX /wd4530)
endif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

if(NOT MSVC)
    find_program(CCACHE_PROGRAM ccache)
    if(CCACHE_PROGRAM)
        message(STATUS "Found CCache: ${CCACHE_PROGRAM}")
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PROGRAM})
    endif()
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(REDIS_SOURCE_DIR src)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

project(redis)

file(GLOB_RECURSE source_file CONFIGURE_DEPENDS src/*.cpp src/*.cc src/*.c)
file(GLOB_RECURSE header_file CONFIGURE_DEPENDS include/redis/*.hpp  include/tools/*.hpp)

add_library(redis OBJECT ${source_file} ${header_file})
target_include_directories(redis PUBLIC include)

#import boost 1.84.0 library
FetchContent_Declare(
    hiredis
    GIT_REPOSITORY https://github.com/redis/hiredis.git
    GIT_TAG v1.2.0
)
FetchContent_MakeAvailable(hiredis)

add_subdirectory(inifile)

target_link_libraries(redis PUBLIC 
    hiredis::hiredis
    inicpp::inicpp
)

target_compile_definitions(redis PUBLIC 
    -DCONFIG_HOME=\"${CMAKE_CURRENT_SOURCE_DIR}/\"
)