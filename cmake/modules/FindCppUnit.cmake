INCLUDE(FindPackageHandleStandardArgs)
INCLUDE(UsePkgConfig)
PKGCONFIG(cppunit _CppUnitIncDir _CppUnitLinkDir _CppUnitLinkFlags _CppUnitCflags)

FIND_PATH(CPPUNIT_INCLUDE_DIR cppunit/TestCase.h
    ${_CppUnitIncDir}
    /usr/local/include
    /usr/include
)

FIND_LIBRARY(CPPUNIT_LIBRARIES cppunit
    ${_CppUnitLinkDir}
    /usr/local/lib
    /usr/lib
)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(CppUnit DEFAULT_MSG CPPUNIT_LIBRARIES CPPUNIT_INCLUDE_DIR)
