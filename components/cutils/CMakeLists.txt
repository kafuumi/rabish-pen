
message(STATUS "SDS library version: v2.0.0")

set(src_files "sds/sds.c" "sds/sdsalloc.h")

idf_component_register(SRCS ${src_files}
    INCLUDE_DIRS "."
  )
