CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)
PROJECT(glog_builder C CXX)

INCLUDE(ExternalProject)
ExternalProject_Add(googlelog
    SVN_REPOSITORY https://github.com/emzeat/google-glog.git/
    CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=Debug
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=Release
               -DCMAKE_CXX_FLAGS=${MSVC_COMPILER_DEFS}
     PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
# Disable install step
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(googlelog source_dir)
SET(GLOG_INCLUDE_DIRS ${source_dir}/include PARENT_SCOPE)

ExternalProject_Get_Property(googlelog binary_dir)
SET(GLOG_LIBS_DIR ${binary_dir} PARENT_SCOPE)
