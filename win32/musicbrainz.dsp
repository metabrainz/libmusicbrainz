# Microsoft Developer Studio Project File - Name="musicbrainz" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=musicbrainz - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "musicbrainz.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "musicbrainz.mak" CFG="musicbrainz - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "musicbrainz - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "musicbrainz - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "musicbrainz - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MB_CLIENT_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\osdep" /I ".." /I "..\lib" /I "..\..\expat\Source\lib" /I "..\lib\bitzi" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MB_CLIENT_EXPORTS" /D "NOMINMAX" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 /LIBPATH:"..\..\expat\Libs" winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib comctl32.lib libexpat.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "musicbrainz - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MB_CLIENT_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\osdep" /I ".." /I "..\lib" /I "..\..\expat\Source\lib" /I "..\lib\bitzi" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MB_CLIENT_EXPORTS" /D "NOMINMAX" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /LIBPATH:"..\..\expat\Libs" winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib comctl32.lib libexpat.lib /nologo 
/dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "musicbrainz - Win32 Release"
# Name "musicbrainz - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\lib\base64.c
# End Source File
# Begin Source File

SOURCE=..\lib\c_wrapper.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\comhttpsocket.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\diskid.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\haar.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\http.cpp
# End Source File
# Begin Source File

SOURCE=..\osdep\mb_win32.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\musicbrainz.cpp
# End Source File
# Begin Source File

SOURCE=.\musicbrainz.def
# End Source File
# Begin Source File

SOURCE=..\lib\rdfextract.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\rdfparse.c
# End Source File
# Begin Source File

SOURCE=..\lib\sha1.c
# End Source File
# Begin Source File

SOURCE=..\lib\sigclient.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\sigfft.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\signature.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\sigxdr.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\uuid.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\wincomsocket.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Bitzi"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\lib\bitzi\bitprint.c
# End Source File
# Begin Source File

SOURCE=..\lib\bitzi\dirsearch.c
# End Source File
# Begin Source File

SOURCE=..\lib\bitzi\gui_win32.c
# End Source File
# Begin Source File

SOURCE=..\lib\bitzi\id3.c
# End Source File
# Begin Source File

SOURCE=..\lib\bitzi\list.c
# End Source File
# Begin Source File

SOURCE=..\lib\bitzi\main.c
# End Source File
# Begin Source File

SOURCE=..\lib\bitzi\md5.c
# End Source File
# Begin Source File

SOURCE=..\lib\bitzi\mp3.c
# End Source File
# Begin Source File

SOURCE=..\lib\bitzi\plugin_win32.c
# End Source File
# Begin Source File

SOURCE=..\lib\bitzi\sboxes.c
# End Source File
# Begin Source File

SOURCE=..\lib\bitzi\tiger.c
# End Source File
# Begin Source File

SOURCE=..\lib\bitzi\tigertree.c
# End Source File
# End Group
# End Target
# End Project
