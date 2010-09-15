INCLUDE(FindPackageHandleStandardArgs)
INCLUDE(UsePkgConfig)
PKGCONFIG(neon _NeonIncDir _NeonLinkDir _NeonLinkFlags _NeonCflags)

FIND_PATH(NEON_INCLUDE_DIR ne_request.h
    PATHS
    ${_NeonIncDir}
    /usr/include
    /usr/local/include
    PATH_SUFFIXES neon
)

FIND_LIBRARY(NEON_LIBRARIES neon
    ${_NeonLinkDir}
    /usr/lib
    /usr/local/lib
)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(Neon DEFAULT_MSG NEON_LIBRARIES NEON_INCLUDE_DIR)
