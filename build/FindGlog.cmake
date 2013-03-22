# Pass GLOG_ROOT if u want us search in it
#
# Try to find the libglog libraries
# Once done this will define :
#
# Glog_FOUND - system has libglog
# Glog_INCLUDE_DIRS - the libglog include directory
# Glog_LIBRARIES - libglog library
include(FindPackageHandleStandardArgs)

if(MSVC)
    FIND_PATH(GLOG_INCLUDE_DIR glog/logging.h 
            PATHS ${GLOG_ROOT}/src/windows)
    FIND_LIBRARY(GLOG_LIBRARY_DEBUG NAMES libglog_static
            PATHS ${GLOG_ROOT}
            PATH_SUFFIXES Debug)
    FIND_LIBRARY(GLOG_LIBRARY_RELEASE NAMES libglog_static
            PATHS ${GLOG_ROOT}
            PATH_SUFFIXES Release)
    set (GLOG_LIBRARY optimized ${GLOG_LIBRARY_RELEASE} debug ${GLOG_LIBRARY_DEBUG})
else()    
    FIND_PATH(GLOG_INCLUDE_DIR glog/logging.h 
            PATHS /include /usr/include /usr/local/include ${GLOG_ROOT})
    FIND_LIBRARY(GLOG_LIBRARY NAMES glog 
            PATHS /  /usr /usr/local ${GLOG_ROOT}
            PATH_SUFFIXES lib lib64)
endif()

find_package_handle_standard_args(GLOG DEFAULT_MSG GLOG_INCLUDE_DIR GLOG_LIBRARY)

if (GLOG_FOUND)
    set(GLOG_INCLUDE_DIRS ${GLOG_INCLUDE_DIR})
    set(GLOG_LIBRARIES ${GLOG_LIBRARY})
    #MARK_AS_ADVANCED(GLOG_INCLUDE_DIRS GLOG_LIBRARIES)
endif()    
