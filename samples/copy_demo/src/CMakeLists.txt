# rga_copy_demo
add_executable(rga_copy_demo
    rga_copy_demo.cpp
)
target_link_libraries(rga_copy_demo
    utils_obj
    ${RGA_LIB}
)
install(TARGETS rga_copy_demo DESTINATION ${CMAKE_INSTALL_BINDIR})

# rga_copy_splice_demo
add_executable(rga_copy_splice_demo
    rga_copy_splice_demo.cpp
)
target_link_libraries(rga_copy_splice_demo
    utils_obj
    ${RGA_LIB}
)
install(TARGETS rga_copy_splice_demo DESTINATION ${CMAKE_INSTALL_BINDIR})

# rga_copy_splice_task_demo
add_executable(rga_copy_splice_task_demo
    rga_copy_splice_task_demo.cpp
)
target_link_libraries(rga_copy_splice_task_demo
    utils_obj
    ${RGA_LIB}
)
install(TARGETS rga_copy_splice_task_demo DESTINATION ${CMAKE_INSTALL_BINDIR})
