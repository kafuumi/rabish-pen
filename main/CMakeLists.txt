set(src_files "main.c")

idf_component_register(SRCS ${src_files}
                       INCLUDE_DIRS "."
                       REQUIRES amp)
