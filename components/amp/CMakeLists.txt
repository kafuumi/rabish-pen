set(src_files "opus_decoder.c")

set(priv_requires cutils)

idf_component_register(SRCS ${src_files}
        INCLUDE_DIRS      "include/"
        PRIV_INCLUDE_DIRS "."
        REQUIRES
        PRIV_REQUIRES ${priv_requires})

add_subdirectory(thirdparty)

target_link_libraries(${COMPONENT_LIB} PRIVATE Opus::opus)
target_link_libraries(${COMPONENT_LIB} PRIVATE Opus::ogg)
