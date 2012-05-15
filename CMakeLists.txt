cmake_minimum_required(VERSION 2.6)

PROJECT(libmusicbrainz5)
SET(PROJECT_VERSION 5.0.0)

# 1. If the library source code has changed at all since the last update, then increment revision.
# 2. If any interfaces have been added, removed, or changed since the last update, increment current, and set revision to 0.
# 3. If any interfaces have been added since the last public release, then increment age.
# 4. If any interfaces have been removed since the last public release, then set age to 0.
SET(musicbrainz5_SOVERSION_CURRENT  0)
SET(musicbrainz5_SOVERSION_REVISION 0)
SET(musicbrainz5_SOVERSION_AGE      0)

MATH(EXPR musicbrainz5_SOVERSION_MAJOR "${musicbrainz5_SOVERSION_CURRENT} - ${musicbrainz5_SOVERSION_AGE}")
MATH(EXPR musicbrainz5_SOVERSION_MINOR "${musicbrainz5_SOVERSION_AGE}")
MATH(EXPR musicbrainz5_SOVERSION_PATCH "${musicbrainz5_SOVERSION_REVISION}")

SET(musicbrainz5_VERSION ${musicbrainz5_SOVERSION_MAJOR}.${musicbrainz5_SOVERSION_MINOR}.${musicbrainz5_SOVERSION_PATCH})
SET(musicbrainz5_SOVERSION ${musicbrainz5_SOVERSION_MAJOR})

SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
FIND_PACKAGE(Neon REQUIRED)

SET(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)")
SET(EXEC_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX} CACHE PATH "Installation prefix for executables and object code libraries" FORCE)
SET(BIN_INSTALL_DIR ${EXEC_INSTALL_PREFIX}/bin CACHE PATH "Installation prefix for user executables" FORCE)
SET(LIB_INSTALL_DIR ${EXEC_INSTALL_PREFIX}/lib${LIB_SUFFIX} CACHE PATH  "Installation prefix for object code libraries" FORCE)
SET(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include CACHE PATH "Installation prefix for C header files" FORCE)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/libmusicbrainz5.pc.cmake ${CMAKE_CURRENT_BINARY_DIR}/libmusicbrainz5.pc)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.cmake ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

FILE(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/include/musicbrainz5/*.h)
INSTALL(FILES ${headers} include/musicbrainz5/mb5_c.h DESTINATION ${INCLUDE_INSTALL_DIR}/musicbrainz5)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/libmusicbrainz5.pc DESTINATION ${LIB_INSTALL_DIR}/pkgconfig)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)
ADD_SUBDIRECTORY(examples)

ADD_CUSTOM_TARGET(docs
	doxygen
)

ADD_DEPENDENCIES(docs src_gen)

ADD_CUSTOM_TARGET(dist
    rm -rf "libmusicbrainz-${PROJECT_VERSION}"
    COMMAND git archive --prefix="libmusicbrainz-${PROJECT_VERSION}/" release-${PROJECT_VERSION} | gzip -9 > libmusicbrainz-${PROJECT_VERSION}.tar.gz
)
