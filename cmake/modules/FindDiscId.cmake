INCLUDE(FindPackageHandleStandardArgs)
INCLUDE(UsePkgConfig)
PKGCONFIG(libdiscid _DiscIdIncDir _DiscIdLinkDir _DiscIdLinkFlags _DiscIdCflags)

FIND_PATH(DISCID_INCLUDE_DIR discid/discid.h
    ${_DiscIdIncDir}
    /usr/include
    /usr/local/include
)

FIND_LIBRARY(DISCID_LIBRARIES discid
    ${_DiscIdLinkDir}
    /usr/lib
    /usr/local/lib
)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(DiscId DEFAULT_MSG DISCID_LIBRARIES DISCID_INCLUDE_DIR)
