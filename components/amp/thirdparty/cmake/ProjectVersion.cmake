if(__project_version)
  return()
endif()
set(__project_version INCLUDED)

function(get_project_version PROJECT_ROOT_PATH PACKAGE_VERSION)
  find_package(Git)
  if(GIT_FOUND AND EXISTS "${PROJECT_ROOT_PATH}/.git")
    execute_process(COMMAND ${GIT_EXECUTABLE}
                          "--git-dir=${PROJECT_ROOT_PATH}/.git"
                          "describe"
                          --tags --match "v*" OUTPUT_VARIABLE _version)
    if(_version)
      string(STRIP "${_version}" _version)
      string(REPLACE "\n" "" _version "${_version}")
      string(REPLACE "," "" _version "${_version}")
      set(${PACKAGE_VERSION} "${_version}" PARENT_SCOPE)
    endif()
  endif()
endfunction()
