SET(CMAKE_INCLUDE_CURRENT_DIR ON)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/../include ${NEON_INCLUDE_DIR})

SET(_sources Alias.cc Annotation.cc Artist.cc ArtistCredit.cc Attribute.cc CDStub.cc Collection.cc
	Disc.cc Entity.cc FreeDBDisc.cc HTTPFetch.cc ISRC.cc Label.cc LabelInfo.cc Lifespan.cc List.cc
	mb4_c.cc Medium.cc MediumList.cc Message.cc Metadata.cc NameCredit.cc NonMBTrack.cc PUID.cc
	Query.cc Rating.cc Recording.cc Relation.cc RelationList.cc Release.cc ReleaseGroup.cc Tag.cc
	TextRepresentation.cc Track.cc UserRating.cc UserTag.cc Work.cc xmlParser.cpp)

ADD_EXECUTABLE(make-c-interface make-c-interface.cc xmlParser.cpp)

ADD_CUSTOM_COMMAND(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mb4_c.cc ${CMAKE_CURRENT_BINARY_DIR}/mb4_c.h ${CMAKE_CURRENT_BINARY_DIR}/../include/musicbrainz4/mb4_c.h
	COMMAND make-c-interface ${CMAKE_CURRENT_SOURCE_DIR} cinterface.xml ${CMAKE_CURRENT_BINARY_DIR} mb4_c.cc mb4_c.h
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/mb4_c.h ${CMAKE_CURRENT_BINARY_DIR}/../include/musicbrainz4
	DEPENDS make-c-interface cinterface.xml *.inc
)

ADD_CUSTOM_TARGET(src_gen DEPENDS mb4_c.h)

ADD_LIBRARY(musicbrainz4 SHARED ${_sources})

SET_TARGET_PROPERTIES(musicbrainz4 PROPERTIES
    VERSION ${musicbrainz4_VERSION}
    SOVERSION ${musicbrainz4_SOVERSION}
    DEFINE_SYMBOL MB_API_EXPORTS
)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	SET_TARGET_PROPERTIES(musicbrainz4 PROPERTIES
		DEFINE_SYMBOL _MB4_DEBUG_
	)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ggdb -O0")
endif(CMAKE_BUILD_TYPE STREQUAL Debug)

TARGET_LINK_LIBRARIES(musicbrainz4 ${NEON_LIBRARIES})

IF(WIN32)
    TARGET_LINK_LIBRARIES(musicbrainz4 wsock32 winmm ws2_32)
ENDIF(WIN32)

IF(CMAKE_COMPILER_IS_GNUCXX)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic-errors")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

INSTALL(TARGETS musicbrainz4 DESTINATION ${LIB_INSTALL_DIR})
