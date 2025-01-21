set(DMA_ALLOC_SRC
    ${CMAKE_CURRENT_LIST_DIR}/dma_alloc.cpp
)

set(DRM_ALLOC_SRC
    ${CMAKE_CURRENT_LIST_DIR}/drm_alloc.cpp
)

if(RGA_SOURCE_CODE_TYPE STREQUAL c)
    set_source_files_properties(${DMA_ALLOC_SRC} PROPERTIES LANGUAGE C COMPILE_FLAGS "-x c")
    set_source_files_properties(${DRM_ALLOC_SRC} PROPERTIES LANGUAGE C COMPILE_FLAGS "-x c")
endif()

target_sources(utils_obj
    PRIVATE
        ${DMA_ALLOC_SRC}
        ${DRM_ALLOC_SRC}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include/dma_alloc.h
        ${CMAKE_CURRENT_LIST_DIR}/include/drm_alloc.h
)

target_include_directories(utils_obj
    PUBLIC
        ${THIRD_PARTY_PATH}/libdrm/include
        ${THIRD_PARTY_PATH}/libdrm/include/libdrm
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(utils_obj INTERFACE dl)
