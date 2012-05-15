# Install script for directory: /home/adhawkins/libmusicbrainz.git

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/include/musicbrainz4" TYPE FILE FILES
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/RecordingList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Work.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/LabelList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/ArtistCredit.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/ListImpl.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/PUIDList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/NameCredit.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/ReleaseGroupList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Release.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/TextRepresentation.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Artist.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/AttributeList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Track.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Annotation.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/DiscList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/MediumList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/ReleaseGroup.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Alias.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Metadata.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/WorkList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/xmlParser.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/RelationListList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/HTTPFetch.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/ISWC.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/FreeDBDisc.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/LabelInfo.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/CDStub.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Rating.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/UserTag.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Disc.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Collection.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Tag.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/NameCreditList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/AliasList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/SecondaryTypeList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/CollectionList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/NonMBTrack.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Recording.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/defines.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Message.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/NonMBTrackList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/RelationList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/FreeDBDiscList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Attribute.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/PUID.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/LabelInfoList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/ReleaseList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/TrackList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/ArtistList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/ISRC.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Lifespan.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/List.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/ISRCList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Label.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Relation.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Query.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/AnnotationList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/ISWCList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/IPI.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/UserRating.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/IPIList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Medium.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/CDStubList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/UserTagList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/SecondaryType.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/Entity.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/TagList.h"
    "/home/adhawkins/libmusicbrainz.git/include/musicbrainz4/mb4_c.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/lib/pkgconfig" TYPE FILE FILES "/home/adhawkins/libmusicbrainz.git/libmusicbrainz4.pc")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/adhawkins/libmusicbrainz.git/src/cmake_install.cmake")
  INCLUDE("/home/adhawkins/libmusicbrainz.git/tests/cmake_install.cmake")
  INCLUDE("/home/adhawkins/libmusicbrainz.git/examples/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/adhawkins/libmusicbrainz.git/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/adhawkins/libmusicbrainz.git/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
