################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           tools/cmake/FindSOFA.cmake.in
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

SET (SOFA_ROOT_DIR ${SOFA_ROOT_DIR} "/usr/local")

FIND_PATH (SOFA_INCLUDE_DIR "sofa/sofa.h" PATHS ${SOFA_ROOT_DIR} PATH_SUFFIXES "include" NO_DEFAULT_PATH)

FIND_LIBRARY (SOFA_LIBRARY NAMES "libsofa_c.a" PATHS ${SOFA_ROOT_DIR} PATH_SUFFIXES "lib" NO_DEFAULT_PATH)

SET (SOFA_LIBRARIES ${SOFA_LIBRARY})
SET (SOFA_INCLUDE_DIRS ${SOFA_INCLUDE_DIR})

INCLUDE (FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS (SOFA DEFAULT_MSG SOFA_LIBRARY SOFA_INCLUDE_DIR)

MARK_AS_ADVANCED (SOFA_INCLUDE_DIR SOFA_LIBRARY)

################################################################################################################################################################
