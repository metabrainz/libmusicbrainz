SET(CMAKE_INCLUDE_CURRENT_DIR ON)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/../include ${NEON_INCLUDE_DIR})

SET(_sources Alias.cc Annotation.cc Artist.cc ArtistCredit.cc Attribute.cc CDStub.cc Collection.cc
	Disc.cc Entity.cc FreeDBDisc.cc HTTPFetch.cc ISRC.cc Label.cc LabelInfo.cc Lifespan.cc List.cc
	mb5_c.cc Medium.cc MediumList.cc Message.cc Metadata.cc NameCredit.cc NonMBTrack.cc PUID.cc
	Query.cc Rating.cc Recording.cc Relation.cc RelationList.cc Release.cc ReleaseGroup.cc Tag.cc
	TextRepresentation.cc Track.cc UserRating.cc UserTag.cc Work.cc xmlParser.cpp
	RelationListList.cc ISWCList.cc ISWC.cc SecondaryType.cc SecondaryTypeList.cc IPI.cc)

ADD_EXECUTABLE(make-c-interface make-c-interface.cc xmlParser.cpp)

ADD_CUSTOM_COMMAND(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mb5_c.cc ${CMAKE_CURRENT_BINARY_DIR}/mb5_c.h ${CMAKE_CURRENT_BINARY_DIR}/../include/musicbrainz5/mb5_c.h
	COMMAND make-c-interface ${CMAKE_CURRENT_SOURCE_DIR} cinterface.xml ${CMAKE_CURRENT_BINARY_DIR} mb5_c.cc mb5_c.h
	COMMAND ${CMAKE_COMMAND} -E copy_if_different 	${CMAKE_CURRENT_BINARY_DIR}/mb5_c.h ${CMAKE_CURRENT_BINARY_DIR}/../include/musicbrainz5
	DEPENDS make-c-interface cinterface.xml *.inc
)

ADD_CUSTOM_TARGET(src_gen DEPENDS mb5_c.h)

ADD_LIBRARY(musicbrainz5 SHARED ${_sources})

SET_TARGET_PROPERTIES(musicbrainz5 PROPERTIES
    VERSION ${musicbrainz5_VERSION}
    SOVERSION ${musicbrainz5_SOVERSION}
    DEFINE_SYMBOL MB_API_EXPORTS
)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	SET_TARGET_PROPERTIES(musicbrainz5 PROPERTIES
		DEFINE_SYMBOL _MB5_DEBUG_
	)
	IF(CMAKE_COMPILER_IS_GNUCXX)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ggdb -O0")
	ENDIF(CMAKE_COMPILER_IS_GNUCXX)
endif(CMAKE_BUILD_TYPE STREQUAL Debug)

TARGET_LINK_LIBRARIES(musicbrainz5 ${NEON_LIBRARIES})

IF(WIN32)
    TARGET_LINK_LIBRARIES(musicbrainz5 wsock32 winmm ws2_32)
ENDIF(WIN32)

IF(CMAKE_COMPILER_IS_GNUCXX)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic-errors")
		set_source_files_properties(mb5_c.cc PROPERTIES COMPILE_FLAGS "-Wno-deprecated-declarations")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

INSTALL(TARGETS musicbrainz5 DESTINATION ${LIB_INSTALL_DIR})
