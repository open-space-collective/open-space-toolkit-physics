################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           tools/cmake/FindNRLMSISE-00-00.cmake
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

SET (NRLMSISE-00_ROOT_DIR ${NRLMSISE-00_ROOT_DIR} "/usr/local")

FIND_PATH (NRLMSISE-00_INCLUDE_DIR "nrlmsise/nrlmsise-00.h" PATHS ${NRLMSISE-00_ROOT_DIR} PATH_SUFFIXES "include" NO_DEFAULT_PATH)

FIND_LIBRARY (NRLMSISE-00_LIBRARY NAMES "libnrlmsise00.a" PATHS ${NRLMSISE-00_ROOT_DIR} PATH_SUFFIXES "lib" NO_DEFAULT_PATH)

SET (NRLMSISE-00_LIBRARIES ${NRLMSISE-00_LIBRARY})
SET (NRLMSISE-00_INCLUDE_DIRS ${NRLMSISE-00_INCLUDE_DIR})

INCLUDE (FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS (NRLMSISE-00 DEFAULT_MSG NRLMSISE-00_LIBRARY NRLMSISE-00_INCLUDE_DIR)

MARK_AS_ADVANCED (NRLMSISE-00_INCLUDE_DIR NRLMSISE-00_LIBRARY)

################################################################################################################################################################
