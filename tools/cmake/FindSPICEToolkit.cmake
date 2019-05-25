################################################################################################################################################################

# @project        Library ▸ Physics
# @file           tools/cmake/FindSPICEToolkit.cmake.in
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

SET (SPICEToolkit_ROOT_DIR ${SPICEToolkit_ROOT_DIR} "/usr/local")

FIND_PATH (SPICEToolkit_INCLUDE_DIR "cspice/f2c.h" PATHS ${SPICEToolkit_ROOT_DIR} PATH_SUFFIXES "include" NO_DEFAULT_PATH)

FIND_LIBRARY (SPICEToolkit_LIBRARY NAMES "cspice.a" PATHS ${SPICEToolkit_ROOT_DIR} PATH_SUFFIXES "lib" NO_DEFAULT_PATH)

SET (SPICEToolkit_LIBRARIES ${SPICEToolkit_LIBRARY})
SET (SPICEToolkit_INCLUDE_DIRS ${SPICEToolkit_INCLUDE_DIR})

INCLUDE (FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS (SPICEToolkit DEFAULT_MSG SPICEToolkit_LIBRARY SPICEToolkit_INCLUDE_DIR)

MARK_AS_ADVANCED (SPICEToolkit_INCLUDE_DIR SPICEToolkit_LIBRARY)

################################################################################################################################################################
