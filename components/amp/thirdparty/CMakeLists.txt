include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/ProjectVersion.cmake")

# libopus

set(OPUS_ROOT "${CMAKE_CURRENT_LIST_DIR}/opus")
message(STATUS "Opus project path: ${OPUS_ROOT}")

get_project_version(${OPUS_ROOT} OPUS_PROJECT_VERSION)
if(OPUS_PROJECT_VERSION)
  message(STATUS "Opus version: ${OPUS_PROJECT_VERSION}")
endif()

include("${OPUS_ROOT}/cmake/OpusFunctions.cmake")

function(get_opus_sources_absolute GROUP FILE VAR)
  get_opus_sources("${GROUP}" "${OPUS_ROOT}/${FILE}" _tmp)
  set(_result "")
  foreach(f ${_tmp})
    list(APPEND _result "${OPUS_ROOT}/${f}")
  endforeach()
  set(${VAR} "${_result}" PARENT_SCOPE)
endfunction()

get_opus_sources_absolute(OPUS_HEAD          "opus_headers.mk"   opus_headers)
get_opus_sources_absolute(OPUS_SOURCES       "opus_sources.mk"   opus_sources)
get_opus_sources_absolute(OPUS_SOURCES_FLOAT "opus_sources.mk"   opus_sources_float)
get_opus_sources_absolute(CELT_HEAD          "celt_headers.mk"   opus_celt_headers)
get_opus_sources_absolute(CELT_SOURCES       "celt_sources.mk"   opus_celt_sources)
get_opus_sources_absolute(SILK_HEAD          "silk_headers.mk"   opus_silk_headers)
get_opus_sources_absolute(SILK_SOURCES       "silk_sources.mk"   opus_silk_sources)
get_opus_sources_absolute(SILK_SOURCES_FIXED "silk_sources.mk"   opus_silk_fixed_sources)
get_opus_sources_absolute(SILK_SOURCES_FLOAT "silk_sources.mk"   opus_silk_float_sources)

set(opus_src_files
  ${opus_headers}
  ${opus_sources}
  ${opus_sources_float}
  ${opus_celt_headers}
  ${opus_celt_sources}
  ${opus_silk_headers}
  ${opus_silk_sources}
  ${opus_silk_fixed_sources})

set(opus_target "opus")
add_library(${opus_target} STATIC ${opus_src_files})
add_library(Opus::opus ALIAS ${opus_target})

target_compile_definitions(${opus_target} PRIVATE
  OPUS_BUILD
  OPUS_EXPORT=
  OPUS_HAVE_RTCD=0
  HAVE_LRINT
  HAVE_LRINTF
  FIXED_POINT=1
  DISABLE_FLOAT_API
  NONTHREADSAFE_PSEUDOSTACK)

target_include_directories(${opus_target}
  PUBLIC ${OPUS_ROOT}/include
  PRIVATE ${OPUS_ROOT}
          ${OPUS_ROOT}/celt
          ${OPUS_ROOT}/silk
          ${OPUS_ROOT}/silk/fixed
          ${CMAKE_CURRENT_BINARY_DIR})

# libogg

set(OGG_ROOT "${CMAKE_CURRENT_LIST_DIR}/ogg")
message(STATUS "Ogg project path: ${OGG_ROOT}")

get_project_version(${OGG_ROOT} OGG_PROJECT_VERSION)
if(OPUS_PROJECT_VERSION)
  message(STATUS "Ogg version: ${OGG_PROJECT_VERSION}")
endif()

# Configure config_type.h
include(CheckIncludeFiles)
check_include_files(inttypes.h INCLUDE_INTTYPES_H)
check_include_files(stdint.h INCLUDE_STDINT_H)
check_include_files(sys/types.h INCLUDE_SYS_TYPES_H)

set(SIZE16 int16_t)
set(USIZE16 uint16_t)
set(SIZE32 int32_t)
set(USIZE32 uint32_t)
set(SIZE64 int64_t)
set(USIZE64 uint64_t)

include(${OGG_ROOT}/cmake/CheckSizes.cmake)

configure_file(${OGG_ROOT}/include/ogg/config_types.h.in ${OGG_ROOT}/include/ogg/config_types.h @ONLY)

set(ogg_src_files ${OGG_ROOT}/src/bitwise.c
                  ${OGG_ROOT}/src/framing.c
                  ${OGG_ROOT}/src/crctable.h)
set(ogg_target "ogg")
add_library(${ogg_target} STATIC ${ogg_src_files})
add_library(Opus::ogg ALIAS ${ogg_target})

if(CONFIG_AMP_OGG_DISABLE_CRC)
  target_compile_definitions(${ogg_target} PRIVATE DISABLE_CRC)
endif()

target_include_directories(${ogg_target} PUBLIC ${OGG_ROOT}/include)
