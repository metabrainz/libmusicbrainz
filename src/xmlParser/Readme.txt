XMLParser v2.43
===============

The library is composed by two files: "xmlParser.cpp" and "xmlParser.h".
These are the ONLY 2 files that you need when using the library inside your own projects.

All the functions of the library are documented inside the comments of the file "xmlParser.h". 
These comments can be transformed in full-fledged HTML documentation using the DOXYGEN 
software: simply type: "doxygen doxy.cfg"

For more documentation, please refer either to the file "xmlParser.h" or "Doc/html/index.html".

Change Log
----------

* V1.00: February 20, 2002: initial version by Martyn C Brown.
* V1.01: February 13, 2005: first bug-free "internet" release.
* V1.02: March 6, 2005: 2 minor changes:
   o "parseString" function declaration changed to allow easy parsing from memory buffer
   o Minor changes to allow easy compilation under old GCC under QNX
* V1.03: April 2,2005: 3 minors changes:
   o When parsing from a user-supplied memory buffer, the library was previously modifying the content of the memory buffer. This is not the case anymore
   o Non-unicode Windows version: You can now work with unicode XML files: They are converted to ANSI charset before being processed
   o Added Visual Studio 6.0 project files
* V1.04: May 16, 2005: 3 minors changes, 1 bug fix:
   o FIX: When creating an xml string with no formatting, the formatting did not work always (due to an un-initialized variable)
   o Improved parsing speed (try increasing the constant "memoryIncrease" if you need more speed)
   o Minor changes to allow easy compilation under MSYS/MINGW under Windows
   o Added more character entities
* V1.05: May 31, 2005: 2 minors changes:
   o Changed some "char *" to "const char *"
   o Improved robustness against badly formed xml strings
* V1.06: July 11, 2005: 1 change, 1 bug fix: 
   o FIX: Some character entities were not previously correctly processed.
   o Major speed improvement. The library is now at least 10 times faster. (Try increasing the constant "memoryIncrease" if you need more speed)
   o moved the log file out of the HTML file
* V1.07: July 25, 2005: 1 change
   o Added a pre-compiler directive named "APPROXIMATE_PARSING". See header of xmlParser.cpp for more info.
* V1.08: September 8,2005: 1 bug fix: 
   o FIX: on special cases, non-matching quotes were causing malfunction
* V1.09: November 22, 2005: 1 addition
   o Added some new functions to be able to easily create a XML structure in memory
* V1.10: December 29, 2005: 2 minor change.
   o Changed some formatting when rendering a XML tree to a string 
   o added the STRICT_PARSING option
* V1.11: December 31, 2005: 1 bug fix: 
   o FIX: reduced memory consumption.
* V1.12: January 4, 2006: 1 addition. 
   o added the function "removeNodeContent" to delete a subtree
* V1.13: February 25, 2006: 1 addition. 
   o added a primitive UNICODE support under linux (thanks to Sunny Bains)
* V1.14: April 24, 2006: 1 bug fix: 
   o FIX: memory allocation errors when the XML tree is created from scratch using "addChild" method.
* V1.15: April 28, 2006: 2 additions
   o added some methods to delete attributes,clearTags and textFields from an XMLNode tree.
   o added the "addChild(XMLNode x)" method
* V1.16: May 17, 2006: 1 bug fix: 
   o FIX: memory allocation errors under linux
* V1.17: May 28, 2006: 1 bug fix, 2 additions:
   o FIX: character entities not always processed inside text block
   o position of the eXMLErrorMissingEndTag error is computed
   o added the eXMLErrorUnknownEscapeSequence
* V1.18: June 8, 2006: 1 bug fix, minors changes
   o FIX: the 'eXMLErrorFirstTagNotFound' error was not reported.
* V1.19: July 4, 2006: 3 addition.
   o added automatic convertion from/to UNICODE/ANSI in linux (this was already done in windows)
   o added getChildNodeWithAttribute()
   o added support for SOLARIS unicode (Thanks to Joseph Vijay!).
   o added support for 32 bit unicode (so that the library works on Redhat Enterprise v4 EMT64).
* V1.20: July 22, 2006: 13 additions.
   o added 9 "update" functions (like updateAttribute(LPCTSTR lpszNewValue, LPCTSTR lpszNewName=NULL,LPCTSTR lpszOldName);)
   o added 4 functions that allows you to include any binary data (images, sounds,...) into an XML file or string using "Base64 encoding".
* V2.01: July 24, 2006: 1 major change, 2 minor change, 3 additions
   o added extended support for strict UTF-8 character encoding (The characters in UTF-8 have different lengths (from 1 byte to 4 bytes)).
     Chinese, cyrilic and other extended characters are now processed successfully.
   o new character entities: This is now equivalent: '&#x41;' or '&#65;' or 'A' 
     (The ascci code of 'A' is 65 in decimal and 0x41 in hexadecimal).
   o added a function that try to guess if the encoding is UTF-8.
   o the code has been modified in order to allow easy inclusion of new entities and new clearTags (minor change).
   o the "updateAttribute" function is now adding a new attribute if the one to update is missing.
     (same behavior for "updateText" and "updateClear").
   o no more "stringDup" required for functions like "addText", "addAttribute",... 
     The old behavior is still accessible through functions like "addText_WOSD", "addAttribute_WOSD",...
	 ("_WSOD" stands for "WithOut StringDup").
     This change greatly simplifies the user's code (major update). 
     Unfortunately, old user's code must be updated to work with the new version.
     Fortunately, all the user's code used to READ the content of an XML file is left unchanged:
     Only the "creation of XML" and the "update of XML" user's code require a little updating work.
* V2.02: July 25, 2006: 1 minor change
   o changed the function "createXMLTopNode()" to "createXMLTopNode(LPCTSTR lpszName, int isDeclaration=FALSE);".
* V2.03: July 28, 2006: 1 minor change
   o changed LPTSTR to XMLSTR to avoid name-clash with the definitions in <winnt.h>
* V2.04: August 6, 2006: 1 addition
   o added one heuristic inside the function "guessUTF8ParsingParameterValue".
* V2.05: August 15, 2006: 1 addition
   o now displays the error message inside the method "openFileHelper" in a MessageBox window (WIN32 only).
* V2.06: August 16, 2006: 2 additions
   o added the method XMLNode::writeToFile to make it easier to write the content of an XMLNode to a file.
   o added support for Byte-order marks (or BOM).
* V2.07: August 22, 2006: 1 additions
   o added _XMLUNICODE preprocessor variable to make it easy to force the library into either utf16-mode or utf8-mode.
* V2.08: August 22, 2006: 1 bug fix
   o inside the tag content, the ">" and "/>" strings are not reported as errors anymore.
* V2.09: August 31, 2006: 1 bug fix
   o the character entities of type &#x04B; were not working properly (thanks to José Carlos Medeiros for notifying me!).
* V2.10: September 21, 2006: 1 bug fix
   o two consecutive calls to the deleteNodeContent() function on the same node has now no effect (as it should be).
     (Thanks to Hartmut Lemmel for notifying me!)
   o improved compatibility to Borland C++
* V2.11: October 24, 2006: 3 additions, 1 bug fix.
   o added the function getParentNode(). Thanks to Jakub Siudzinski for notifying me a good way to do it easily.
   o added one parameter to the deleteNodeContent() function to force the deletion of the underlying XMLNode tree. 
     This will release all the memory occupied by the XMLNode tree even if there still exist references to some part
     of the tree.
   o changed the usage of the base64Encode() function to reduce the number of malloc's (speed increase).
   o FIX: when parsing an XML string, if the TOP tag has no closing tag, the library now correctly 
     reports "eXMLErrorMissingEndTag".
* V2.12: October 25, 2006: 2 additions
   o refactoring of the Base64 functions to make things easier to use
   o added the _XMLPARSER_NO_MESSAGEBOX_ preprocessor variable (see header of xmlParser.cpp for explanation)
* V2.13: October 31, 2006: 1 minor change, 1 bug fix
   o changed the signature of _strnicmp to allow easy compilation under linux .
   o FIX: size of buffer for the convertion from ascii/utf8 to utf-16 was incorrect.
* V2.14: November 13, 2006: 1 minor change, 1 bug fix
   o changed the parseFile,openFileHelper,writeToFile functions so that the filename parameter is widechar when UNICODE=1
   o fixed a bug in openFileHelper when sizeof(wchar_t)=4
* V2.15: December 22, 2006: 2 additions
   o added the parameter 'pos' to the addChild,addText,addClear methods to allow insertion of new components anywhere in an already existing XMLNode structure
   o added 'postionOf*' methods.
* V2.16: December 27, 2006: 1 minor change
   o removed the un-necessary method "firstPosition()" & some code re-structuration.
* V2.17: January 9, 2007: 1 addition, 1 minor change
   o added the preprocessor variable "XML_NO_WIDE_CHAR" to allow easy compilation on exotic compilers
   o added the "const" method qualifier to some methods.
* V2.18: January 15, 2007: 1 bug fix
   o FIX: addChild(XMLNode x,int pos) was sometime inserting at the wrong position when pos!=-1
* V2.19: January 30, 2007: 1 bug fix, 3 additions.
   o FIX: Unknown Character Entities are now always reported correctly. Thanks to Vincent Vanhoucke.
   o The XML specification indicates that no white spaces should be lost when parsing the file. This is now possible setting the
     new global parameter "dropWhiteSpaces" to false.
   o The library now works under Windows CE 4.2, Windows Mobile (PPC) 2003(5) (xscale) and Mac OS X Tiger. Thanks to Zdenek Nemec.
   o The "<!DOCTYPE" tag is now always handled properly. Thanks to Zdenek Nemec.
* V2.20: February 17, 2007: 1 addition
   o added a Visual Studio projet file to build a DLL version of the library.
     Under Windows, when I have to debug a software that is using the XMLParser Library, 
     it's usually a nightmare because the library is sooOOOoooo slow in debug mode. To 
     solve this problem, during all the debugging session, I use a very fast DLL version 
     of the XMLParser Library (the DLL is compiled in release mode). Using the DLL version 
     of the XMLParser Library allows me to have lightening XML parsing speed, even in 
     debug mode! Other than that, the DLL version is useless: In the release version 
     of my tool, I always use the normal, ".cpp"-based, XMLParser Library.
* V2.21: Mars 1, 2007: 1 minor change, 1 bug fix
   o changed to a better algorithm to handle the "<!DOCTYPE" tag.
   o FIX: under SPARC processor, the heuristic that is used to check if the xml file is wchar_t* was generating a BUS error.
* V2.22: Mars 6, 2007: 1 bug fix
   o FIX: the 'tag' parameter was not always working properly in parseString
* V2.23: Mars 13, 2007: 1 bug fix
   o FIX: the library is now thread-safe.
* V2.24: April 24, 2007: 1 bug fix, 1 addition
   o FIX: "deleteClear" method was not working properly.
   o the "writeToFile" function has an improved heuristic for the generation of the header <? ... ?> tag.
* V2.25: May 18, 2007: 1 bug fix
   o FIX: "UTF-16 to MCBS convertion" was loosing the last char. Thanks to Robert P. Beyer for noticing me!
* V2.26: May 22, 2007: 1 bug fix
   o FIX: addClear method was not working properly.
* V2.27: May 28, 2007: 2 additions, 1 minor change, 2 bug fix
   o FIX: one "bus error" on Solaris removed. Thanks to Joshua L. Schmiedlin for noticing me!
   o FIX: the function "myIsTextUnicode" was not working properly when sizeof(wchar_t)=4. Thanks to Nagesh Patil for noticing me!
   o renamed "free_XMLDLL" to "freeXMLString" and renamed "toXMLString" to "toXMLStringUnSafe"
   o added some tests to make "add*" and "update*" functions more robust to user errors
   o added the ToXMLStringTool class to allow easy creation of XML files using fprintf function.
* V2.28: June 27, 2007: 2 additions, 2 minor changes
   o added native support for Shift-JIS character encoding.
   o added a primitive heuristic inside the "guessCharEncoding" function to handle the Shift-JIS character encoding. 
   o modified slightly the "setGlobalOptions" function to handle several character encodings.
   o moved the function "toXMLUnSafe" inside the "ToXMLStringTool" class.
* v2.29: July 3,2007: 1 bug fix
   o FIX: the clear tags are now case-sensitive.
* v2.30: July 31,2007: 2 bug fixes, 1 addition
   o FIX: The error when parsing two successives "<!DOCTYPE" clear tags with different closing part is removed.
   o FIX: The "deleteNodeContent" method is now working properly (and is now always in "force" mode).
   o added one XMLError code (when no XML tags are found)
* v2.31: August 29,2007: 1 fix
   o FIX: when we parse an empty file, we now close properly the FILE* handle.
* v2.32: October 4,2007: 1 addition
   o added the example 7 to enumerate the content of a XMLNode.
* v2.33: October 11, 2007: 1 addition
   o added the "deepCopy" method
* v2.34: January 25, 2008: 2 additions
   o added the function "xmltoi" and "xmltof" that are equivalent to the classical functions "atoi" and "atof" but accept a default values used when the string given as argument is NULL.
   o improved support for Borland C++ Builder 6.0
* v2.35: February 2, 2008: 1 minor change
   o changed the xmlto? functions to make them more cross-plateform.
* v2.36: March 9, 2008: 2 bug fixes, 2 additions, 4 minor changes
   o FIX: processing instructions <?anything?> that are not at the root level are now always handled correctly
   o FIX: the "deleteNodeContent" function was previously generating a memory leak.
   o added the file "XMLNodeAutoexp.txt" that shows a user-friendly representation of a XMLNode inside the watch window of the Visual Studio .NET Debugger
   o added a new global option named "removeCommentsInMiddleOfText" to increase standard XML compliance.
   o improved error reporting: character's code above 255 is forbidden in MultiByte char mode
   o improved XML string rendering (function createXMLString): the XMLNode that only contains one text are now written on one line of text instead of three.
   o isolate the functions "xmltoc,xmltoi,xmltol,xmltof,xmltoa" so that they can be easily removed to reduced the number of dependencies of the library.
   o modified slightly the "ToXMLStringTool" class to make it easier to use
* v2.37: March 24, 2008: 1 bux fix
   o FIX: compilation problem under solaris and under Borland 6.0
* v2.38: June 2, 2008: 3 additions
   o multibyte to widechar automatic convertion now uses BOM to guess if encoding.is UTF8 or ASCII
   o added doxygen-style comments for easier documentation and a simple "doxy.cfg" file
   o improved the "getChildNode(XMLCSTR name, int i)" method.
* v2.39: August 9, 2008: 4 additions, 2 bug fixes
   o FIX: on some rare occasions, the createXMLString method returned a string that was not NULL terminated.
   o FIX: on some rare occasions, if there are two declaration term <?...?> at the start of the XML file, then the parser cannot find the start tag.
   o added the "getChildNodeByPath" function
   o added the "xmltob" function and updated the "xmltoc" function
   o included the documentation in html-DOXYGEN format direclty inside the ZIP file
   o added support for GB2312 / Big5 / GBK character encodings
* v2.40: December 19, 2008: 1 minor change
   o improved support for wide char on exotic platform
   o changed the copyright notice to the name of my company (Business-Insight)
* v2.41: June 25, 2009: 1 minor change
   o modified the functions ToXMLStringTool::toXML() and XMLParserBase64Tool::decode() to accept null string as input
* v2.42: Januray 4, 2011: 4 minor changes 
   o modified the function "writeTofile" to handle gracefully the case when it's not possible to write to the file
   o slight speed improvement in parser (inside the tokenizer)
   o changed some enumeration name to avoid any "name collision" with user's code 
   o better handling of the BOM when loading a XML file
* v2.43: 1 bug fix.
   o FIX: empty CDATA were not handled properly (thanks to Botond Xantus from iGo for noticing me!)
