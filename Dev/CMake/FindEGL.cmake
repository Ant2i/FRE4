# Find EGL
#
# EGL_INCLUDE_DIR
# EGL_LIBRARY
# EGL_FOUND

FIND_PATH(EGL_INCLUDE_DIR NAMES EGL/egl.h)

SET(egl_names ${egl_names} egl EGL)
FIND_LIBRARY(EGL_LIBRARY NAMES ${egl_names})

INCLUDE(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EGL DEFAULT_MSG EGL_LIBRARY EGL_INCLUDE_DIR)

MARK_AS_ADVANCED(EGL_INCLUDE_DIR EGL_LIBRARY)