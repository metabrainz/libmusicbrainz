SET(CMAKE_INCLUDE_CURRENT_DIR ON)
INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/..
	${CMAKE_CURRENT_SOURCE_DIR}/../include
	${CMAKE_CURRENT_BINARY_DIR}/../include
	${NEON_INCLUDE_DIR}
	${LIBXML2_INCLUDE_DIR}
)

SET(_sources_cc Alias.cc Annotation.cc Artist.cc ArtistCredit.cc Attribute.cc CDStub.cc Collection.cc
	Disc.cc Entity.cc FreeDBDisc.cc HTTPFetch.cc ISRC.cc Label.cc LabelInfo.cc Lifespan.cc List.cc
	Medium.cc MediumList.cc Message.cc Metadata.cc NameCredit.cc NonMBTrack.cc Offset.cc PUID.cc
	Query.cc Rating.cc Recording.cc Relation.cc RelationList.cc Release.cc ReleaseGroup.cc Tag.cc
	TextRepresentation.cc Track.cc UserRating.cc UserTag.cc Work.cc xmlParser.cc
	RelationListList.cc ISWCList.cc ISWC.cc SecondaryType.cc SecondaryTypeList.cc IPI.cc)
SET(_sources_c mb5_c.cc)

# when crosscompiling import the executable targets from a file
IF(CMAKE_CROSSCOMPILING)
  SET(IMPORT_EXECUTABLES "IMPORTFILE-NOTFOUND" CACHE FILEPATH "Point it to the export file from a native build")
  INCLUDE(${IMPORT_EXECUTABLES})
ENDIF(CMAKE_CROSSCOMPILING)

# only build the generator if not crosscompiling
IF(NOT CMAKE_CROSSCOMPILING)
	ADD_EXECUTABLE(make-c-interface make-c-interface.cc xmlParser.cc)
	TARGET_LINK_LIBRARIES(make-c-interface ${LIBXML2_LIBRARIES})
ENDIF(NOT CMAKE_CROSSCOMPILING)

# export the generator target to a file, so it can be imported (see above) by another build
# the IF() is not necessary, but makes the intention clearer
IF(NOT CMAKE_CROSSCOMPILING)
  EXPORT(TARGETS make-c-interface FILE ${CMAKE_BINARY_DIR}/ImportExecutables.cmake )
ENDIF(NOT CMAKE_CROSSCOMPILING)

ADD_CUSTOM_COMMAND(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mb5_c.cc ${CMAKE_CURRENT_BINARY_DIR}/mb5_c.h ${CMAKE_CURRENT_BINARY_DIR}/../include/musicbrainz5/mb5_c.h
	COMMAND make-c-interface ${CMAKE_CURRENT_SOURCE_DIR} cinterface.xml ${CMAKE_CURRENT_BINARY_DIR} mb5_c.cc mb5_c.h
	COMMAND ${CMAKE_COMMAND} -E copy_if_different 	${CMAKE_CURRENT_BINARY_DIR}/mb5_c.h ${CMAKE_CURRENT_BINARY_DIR}/../include/musicbrainz5/mb5_c.h
	DEPENDS make-c-interface cinterface.xml *.inc
)

ADD_CUSTOM_TARGET(src_gen DEPENDS mb5_c.h)

ADD_LIBRARY(musicbrainz5cc SHARED ${_sources_cc})
ADD_LIBRARY(musicbrainz5 SHARED ${_sources_c})

SET_TARGET_PROPERTIES(musicbrainz5cc PROPERTIES
    VERSION ${musicbrainz5_VERSION}
    SOVERSION ${musicbrainz5_SOVERSION}
    DEFINE_SYMBOL MB_API_EXPORTS
)

SET_TARGET_PROPERTIES(musicbrainz5 PROPERTIES
    VERSION ${musicbrainz5c_VERSION}
    SOVERSION ${musicbrainz5c_SOVERSION}
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

TARGET_LINK_LIBRARIES(musicbrainz5cc ${NEON_LIBRARIES} ${LIBXML2_LIBRARIES})
TARGET_LINK_LIBRARIES(musicbrainz5 musicbrainz5cc)

IF(WIN32)
    TARGET_LINK_LIBRARIES(musicbrainz5 wsock32 winmm ws2_32)
ENDIF(WIN32)

IF(CMAKE_COMPILER_IS_GNUCXX)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic-errors")
		IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../.git)
			SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
		ENDIF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../.git)
		#set_source_files_properties(mb5_c.cc PROPERTIES COMPILE_FLAGS "-Wno-deprecated-declarations")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

INSTALL(TARGETS musicbrainz5cc musicbrainz5 DESTINATION ${LIB_INSTALL_DIR})
