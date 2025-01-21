# rga_gauss_demo
SET(DEMO_NAME rga_gauss_demo)

set(DEMO_SRC
    ${DEMO_NAME}.cpp
)

if(RGA_SOURCE_CODE_TYPE STREQUAL c)
    set_source_files_properties(${DEMO_SRC} PROPERTIES LANGUAGE C COMPILE_FLAGS "-x c")
endif()

add_executable(${DEMO_NAME}
    ${DEMO_SRC}
)
target_link_libraries(${DEMO_NAME}
    utils_obj
    ${RGA_LIB}
)
install(TARGETS ${DEMO_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})

if (RGA_SOURCE_CODE_TYPE STREQUAL cpp)
    #rga_gauss_matrix_demo
    SET(DEMO_NAME rga_gauss_matrix_demo)

    set(DEMO_SRC
        ${DEMO_NAME}.cpp
    )

    add_executable(${DEMO_NAME}
        ${DEMO_SRC}
    )
    target_link_libraries(${DEMO_NAME}
        utils_obj
        ${RGA_LIB}
    )
    install(TARGETS ${DEMO_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()