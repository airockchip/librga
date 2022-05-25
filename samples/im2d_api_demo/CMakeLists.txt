cmake_minimum_required(VERSION 2.8)

project(rgaImDemo)

if(NOT CMAKE_BUILD_TYPE)
    message("default to Release build for GCC builds")
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
endif()

if(CMAKE_BUILD_TARGET STREQUAL android_ndk)
    message("set ndk toolchain")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error -DLOG_TAG=librga")
    add_compile_options(-DLINUX)
    add_compile_options(-DANDROID_VNDK)
    string(REPLACE "-DANDROID" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

if(CMAKE_BUILD_TARGET STREQUAL buildroot)
    message("set ${BUILD_TOOlCHAINS_PATH} toolchain")
    set(CMAKE_TOOLCHAIN_FILE
        ${CMAKE_SOURCE_DIR}/${BUILD_TOOlCHAINS_PATH})
    include(${CMAKE_SOURCE_DIR}/${BUILD_TOOlCHAINS_PATH})
    add_compile_options(-DLINUX)
    set(CMAKE_CXX_FLAGS "-std=c++11 -O2 -pthread")
endif()

if(CMAKE_BUILD_TARGET STREQUAL cmake_linux)
    message("RGA build with cmake")
    add_compile_options(-DLINUX)
    # TO support pass external CMAKE_CXX_FLAGS
    set(CMAKE_CXX_FLAGS_EXT "-std=c++11 -O2 -pthread")

    if (NOT DEFINED CMAKE_C_COMPILER)
        message(FATAL_ERROR "RGA: CMAKE_C_COMPILER not define")
    endif()

    if (NOT DEFINED CMAKE_CXX_COMPILER)
        message(FATAL_ERROR "RGA: CMAKE_CXX_COMPILER not define")
    endif()

endif()

set(IM2D_DEMO_NAME ${PROJECT_NAME})

set(IM2D_DEMO_SRCS
    args.cpp
    rgaImDemo.cpp)

set(IM2D_DEMO_INCLUDE
    ./
    ../../include
    ../../im2d_api)

add_executable(${IM2D_DEMO_NAME} ${IM2D_DEMO_SRCS})

target_include_directories(${IM2D_DEMO_NAME} PUBLIC ${IM2D_DEMO_INCLUDE})

if ((BUILD_WITH_LIBDRM STREQUAL true) AND (EXISTS ${LIBDRM_FILE_LIB}/libdrm.so))
    target_link_libraries(${IM2D_DEMO_NAME} ${LIBDRM_FILE_LIB}/libdrm.so)
elseif (BUILD_WITH_LIBDRM STREQUAL true)
    target_link_libraries(${IM2D_DEMO_NAME} drm)
endif()

if ((BUILD_WITH_LIBRGA STREQUAL true) AND (EXISTS ${LIBRGA_FILE_LIB}/librga.so))
	message("load ${LIBRGA_FILE_LIB}/librga.so")
	target_link_libraries(${IM2D_DEMO_NAME} ${LIBRGA_FILE_LIB}/librga.so)
else ()
	target_link_libraries(${IM2D_DEMO_NAME} rga)
endif()

if (NOT DEFINED CMAKE_INSTALL_BINDIR)
    set(CMAKE_INSTALL_BINDIR bin)
endif()

install(TARGETS ${IM2D_DEMO_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
