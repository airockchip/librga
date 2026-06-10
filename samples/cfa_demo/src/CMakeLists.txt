# rga_cfa_demo
SET(DEMO_NAME rga_cfa_demo)
add_executable(${DEMO_NAME}
    ${DEMO_NAME}.cpp
)
target_link_libraries(${DEMO_NAME}
    utils_obj
    ${RGA_LIB}
)
install(TARGETS ${DEMO_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})

# rga_cfa_a2_demo
SET(DEMO_NAME rga_cfa_a2_demo)
add_executable(${DEMO_NAME}
    ${DEMO_NAME}.cpp
)
target_link_libraries(${DEMO_NAME}
    utils_obj
    ${RGA_LIB}
)
install(TARGETS ${DEMO_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})

# rga_cfa_bcsh_demo
SET(DEMO_NAME rga_cfa_bcsh_demo)
add_executable(${DEMO_NAME}
    ${DEMO_NAME}.cpp
)
target_link_libraries(${DEMO_NAME}
    utils_obj
    ${RGA_LIB}
)
install(TARGETS ${DEMO_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
