INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../include)
LINK_LIBRARIES(musicbrainz5 ${NEON_LIBRARIES})

ADD_EXECUTABLE(cdlookup cdlookup.cc)
ADD_EXECUTABLE(cdlookup_c cdlookup_c.c)
ADD_EXECUTABLE(search search.cc)
ADD_EXECUTABLE(search_c search_c.c)
ADD_EXECUTABLE(collections collections.cc)

IF(CMAKE_COMPILER_IS_GNUCXX)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic-errors")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

IF(CMAKE_COMPILER_IS_GNUCC)
		SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -pedantic-errors")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

