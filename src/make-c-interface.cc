/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include "config.h"
#include "musicbrainz4/defines.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "musicbrainz4/xmlParser.h"

void ProcessBoilerplate(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include);
void ProcessHeader(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include);
void ProcessEntity(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include);
void ProcessClass(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include);
void ProcessList(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include);
void ProcessDeclare(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include);

int main(int argc, const char *argv[])
{
	for (int count=0;count<argc;count++)
		std::cout << argv[count] << " ";

	std::cout << std::endl;

	if (argc==6)
	{
		std::string XMLFile=std::string(argv[1])+"/"+argv[2];
		XMLResults Results;
		XMLNode TopNode=XMLNode::parseFile(XMLFile.c_str(),"cinterface",&Results);
		if (!TopNode.isEmpty())
		{
			std::cout << "Generating '" << argv[3] << "/" << argv[4] << "' and '" << argv[3] << "/" << argv[5] << "'" << std::endl;

			std::string IncludeName=std::string(argv[3])+"/"+argv[5];
			std::ofstream Include(IncludeName.c_str());

			std::string SourceName=std::string(argv[3])+"/" + argv[4];
			std::ofstream Source(SourceName.c_str());

			if (!Include.is_open())
			{
				std::cerr << "Error opening '" << IncludeName << "'" << std::endl;
				return 1;
			}

			if (!Source.is_open())
			{
				std::cerr << "Error opening '" << SourceName << "'" << std::endl;
				return 1;
			}

			for (int count=0;count<TopNode.nChildNode();count++)
			{
				XMLNode Node=TopNode.getChildNode(count);
				std::string Name=Node.getName();

				if ("boilerplate"==Name)
					ProcessBoilerplate(Node,Source,Include);
				else if ("header"==Name)
					ProcessHeader(Node,Source,Include);
				else if ("declare"==Name)
					ProcessDeclare(TopNode,Source,Include);
				else if ("entity"==Name)
					ProcessEntity(Node,Source,Include);
				else if ("class"==Name)
					ProcessClass(Node,Source,Include);
				else if ("list"==Name)
					ProcessList(Node,Source,Include);
				else
				{
					std::cerr << "Unrecognised item " << Name << std::endl;
					return 1;
				}
			}
		}
		else
		{
			std::cerr << "Error reading XML: " << XMLNode::getError(Results.error) << " at line " << Results.nLine << std::endl;
			return 1;
		}
	}

	return 0;
}

std::ofstream *GetFile(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include)
{
	std::ofstream *File=&Source;

	if (Node.isAttributeSet("target"))
	{
		std::string Target=Node.getAttribute("target");
		if ("source"==Target)
			File=&Source;
		else if ("include"==Target)
			File=&Include;
	}

	return File;
}

void ProcessHeader(const XMLNode& /*Node*/, std::ofstream& Source, std::ofstream& Include)
{
	std::stringstream os;
	os << "/* --------------------------------------------------------------------------" << std::endl;
	os << std::endl;
	os << "   libmusicbrainz4 - Client library to access MusicBrainz" << std::endl;
	os << std::endl;
	os << "   Copyright (C) 2011 Andrew Hawkins" << std::endl;
	os << std::endl;
	os << "   This file is part of libmusicbrainz4." << std::endl;
	os << std::endl;
	os << "   This library is free software; you can redistribute it and/or" << std::endl;
	os << "   modify it under the terms of v2 of the GNU Lesser General Public" << std::endl;
	os << "   License as published by the Free Software Foundation." << std::endl;
	os << std::endl;
	os << "   libmusicbrainz4 is distributed in the hope that it will be useful," << std::endl;
	os << "   but WITHOUT ANY WARRANTY; without even the implied warranty of" << std::endl;
	os << "   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU" << std::endl;
	os << "   Lesser General Public License for more details." << std::endl;
	os << std::endl;
	os << "   You should have received a copy of the GNU General Public License" << std::endl;
	os << "   along with this library.  If not, see <http://www.gnu.org/licenses/>." << std::endl;
	os << std::endl;
	os << "   THIS FILE IS AUTOMATICALLY GENERATED - DO NOT EDIT IT!" << std::endl;
	os << std::endl;
	os << "----------------------------------------------------------------------------*/" << std::endl;
	os << std::endl;

	Source << os.str() << std::endl;
	Include << os.str() << std::endl;
}

void ProcessBoilerplate(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include)
{
	std::ofstream *File=GetFile(Node,Source,Include);

	if (Node.isAttributeSet("file"))
	{
		std::string FileName=Node.getAttribute("file");
		std::ifstream InFile(FileName.c_str());
		if (InFile.is_open())
			*File << InFile.rdbuf() << std::endl;
		else
		{
			std::cerr << "Error opening include file '" << FileName << "'" << std::endl;
			exit(1);
		}
	}
	else if (Node.getText())
	{
		*File << Node.getText() << std::endl;
	}

	*File << std::endl;
}

void ProcessEntity(const XMLNode& /*Node*/, std::ofstream& Source, std::ofstream& Include)
{
	Include << "/**" << std::endl;
	Include << " * Returns the number of extension attributes for the entity" << std::endl;
	Include << " *" << std::endl;
	Include << " * @param Entity #Mb4Entity object" << std::endl;
	Include << " *" << std::endl;
	Include << " * @return The number of characters in the string to copy (not including terminating NULL)" << std::endl;
	Include << " */" << std::endl;
	Include << "  int mb4_entity_ext_attributes_size(Mb4Entity Entity);" << std::endl;
	Include << std::endl;

	Include << "/**" << std::endl;
	Include << " * Returns the name of the requested extension attribute" << std::endl;
	Include << " *" << std::endl;
	Include << " * @param Entity #Mb4Entity object" << std::endl;
	Include << " * @param Item Item to return" << std::endl;
	Include << " * @param str Returned string" << std::endl;
	Include << " * @param len Number of characters available in return string" << std::endl;
	Include << " *" << std::endl;
	Include << " * @return The number of characters in the string to copy (not including terminating NULL)" << std::endl;
	Include << " */" << std::endl;
	Include << "  int mb4_entity_ext_attribute_name(Mb4Entity Entity, int Item, char *str, int len);" << std::endl;
	Include << std::endl;

	Include << "/**" << std::endl;
	Include << " * Returns the value of the requested extension attribute" << std::endl;
	Include << " *" << std::endl;
	Include << " * @param Entity #Mb4Entity object" << std::endl;
	Include << " * @param Item Item to return" << std::endl;
	Include << " * @param str Returned string" << std::endl;
	Include << " * @param len Number of characters available in return string" << std::endl;
	Include << " *" << std::endl;
	Include << " * @return The number of characters in the string to copy (not including terminating NULL)" << std::endl;
	Include << " */" << std::endl;
	Include << "  int mb4_entity_ext_attribute_value(Mb4Entity Entity, int Item, char *str, int len);" << std::endl;
	Include << std::endl;

	Include << "/**" << std::endl;
	Include << " * Returns the number of extension elements for the entity" << std::endl;
	Include << " *" << std::endl;
	Include << " * @param Entity #Mb4Entity object" << std::endl;
	Include << " *" << std::endl;
	Include << " * @return The number of characters in the string to copy (not including terminating NULL)" << std::endl;
	Include << " */" << std::endl;
	Include << "  int mb4_entity_ext_elements_size(Mb4Entity Entity);" << std::endl;
	Include << std::endl;

	Include << "/**" << std::endl;
	Include << " * Returns the name of the requested extension element" << std::endl;
	Include << " *" << std::endl;
	Include << " * @param Entity #Mb4Entity object" << std::endl;
	Include << " * @param Item Item to return" << std::endl;
	Include << " * @param str Returned string" << std::endl;
	Include << " * @param len Number of characters available in return string" << std::endl;
	Include << " *" << std::endl;
	Include << " * @return The number of characters in the string to copy (not including terminating NULL)" << std::endl;
	Include << " */" << std::endl;
	Include << "  int mb4_entity_ext_element_name(Mb4Entity Entity, int Item, char *str, int len);" << std::endl;
	Include << std::endl;

	Include << "/**" << std::endl;
	Include << " * Returns the value of the requested extension element" << std::endl;
	Include << " *" << std::endl;
	Include << " * @param Entity #Mb4Entity object" << std::endl;
	Include << " * @param Item Item to return" << std::endl;
	Include << " * @param str Returned string" << std::endl;
	Include << " * @param len Number of characters available in return string" << std::endl;
	Include << " *" << std::endl;
	Include << " * @return The number of characters in the string to copy (not including terminating NULL)" << std::endl;
	Include << " */" << std::endl;
	Include << "  int mb4_entity_ext_element_value(Mb4Entity Entity, int Item, char *str, int len);" << std::endl;
	Include << std::endl;

	Source << "  MB4_C_EXT_GETTER(Attribute,attribute)" << std::endl;
	Source << "  MB4_C_EXT_GETTER(Element,element)" << std::endl;
	Source << std::endl;
}

void ProcessClass(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include)
{
	if (Node.isAttributeSet("name"))
	{
		std::string LowerName=Node.getAttribute("name");

		std::string UpperName=LowerName;
		if (Node.isAttributeSet("uppername"))
			UpperName=Node.getAttribute("uppername");
		else
			UpperName[0]=toupper(UpperName[0]);

		Include << "/**" << std::endl;
		Include << "* Delete an #Mb4" << UpperName << " object" << std::endl;
		Include << "*" << std::endl;
		Include << "* @param " << UpperName << " Object to delete" << std::endl;
		Include << "*/" << std::endl;
		Include << "  void mb4_" << LowerName << "_delete(Mb4" << UpperName << " " << UpperName << ");" << std::endl;
		Include << std::endl;

		Source << "  MB4_C_DELETE(" << UpperName << "," << LowerName << ")" << std::endl;

		Include << "/**" << std::endl;
		Include << "* Clone an #Mb4" << UpperName << " object" << std::endl;
		Include << "*" << std::endl;
		Include << "* @param " << UpperName << " Object to clone" << std::endl;
		Include << "*" << std::endl;
		Include << "* @return Cloned object. This object <b>must</b> be deleted once" << std::endl;
		Include << "*				finished with." << std::endl;
		Include << "*/" << std::endl;
		Include << "  Mb4" << UpperName << " mb4_" << LowerName << "_clone(Mb4" << UpperName << " " << UpperName << ");" << std::endl;
		Include << std::endl;

		Source << "  MB4_C_CLONE(" << UpperName << "," << LowerName << ")" << std::endl;

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string Name=ChildNode.getName();

			if ("property"==Name)
			{
				if (ChildNode.isAttributeSet("name") && ChildNode.isAttributeSet("type"))
				{
					std::string PropertyLowerName=ChildNode.getAttribute("name");

					std::string PropertyUpperName=PropertyLowerName;
					if (ChildNode.isAttributeSet("uppername"))
						PropertyUpperName=ChildNode.getAttribute("uppername");
					else
						PropertyUpperName[0]=toupper(PropertyUpperName[0]);

					std::string PropertyType=ChildNode.getAttribute("type");

					if ("string"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @see MusicBrainz4::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * @param " << UpperName << " #Mb4" << UpperName << " object" << std::endl;
						Include << " * @param str Returned string" << std::endl;
						Include << " * @param len Number of characters available in return string" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return The number of characters in the string to copy (not including terminating NULL)" << std::endl;
						Include << " */" << std::endl;
						Include << "  int mb4_" << LowerName << "_get_" << PropertyLowerName << "(Mb4" << UpperName << " " << UpperName << ", char *str, int len);" << std::endl;
						Include << std::endl;

						Source << "  MB4_C_STR_GETTER(" << UpperName << "," << LowerName << "," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;
					}
					else if ("integer"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @see MusicBrainz4::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * @param " << UpperName << " #Mb4" << UpperName << " object" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return Returned value" << std::endl;
						Include << " */" << std::endl;
						Include << "  int mb4_" << LowerName << "_get_" << PropertyLowerName << "(Mb4" << UpperName << " " << UpperName << ");" << std::endl;
						Include << std::endl;

						Source << "  MB4_C_INT_GETTER(" << UpperName << "," << LowerName << "," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;
					}
					else if ("double"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @see MusicBrainz4::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * @param " << UpperName << " #Mb4" << UpperName << " object" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return Returned value" << std::endl;
						Include << " */" << std::endl;
						Include << "  double mb4_" << LowerName << "_get_" << PropertyLowerName << "(Mb4" << UpperName << " " << UpperName << ");" << std::endl;
						Include << std::endl;

						Source << "  MB4_C_DOUBLE_GETTER(" << UpperName << "," << LowerName << "," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;
					}
					else if ("object"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @see MusicBrainz4::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * @param " << UpperName << " #Mb4" << UpperName << " object" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return #Mb4" << PropertyUpperName << " object" << std::endl;
						Include << " */" << std::endl;
						Include << "  Mb4" << PropertyUpperName << " mb4_" << LowerName << "_get_" << PropertyLowerName << "(Mb4" << UpperName << " " << UpperName << ");" << std::endl;
						Include << std::endl;

						Source << "  MB4_C_OBJ_GETTER(" << UpperName << "," << LowerName << "," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;
					}
					else if ("relationlist"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @deprecated @see MusicBrainz4::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * <b>This method is deprecated, please use #mb4_" << LowerName << "_get_" << PropertyLowerName << "list</b>" << std::endl;
						Include << " *" << std::endl;
						Include << " * @param " << UpperName << " #Mb4" << UpperName << " object" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return #Mb4" << PropertyUpperName << " object" << std::endl;
						Include << " */" << std::endl;
						Include << " Mb4" << PropertyUpperName << " mb4_" << LowerName << "_get_" << PropertyLowerName << "(Mb4" << UpperName << " " << UpperName << ") LIBMB4_DEPRECATED(mb4_" << LowerName << "_get_" << PropertyLowerName << "list) ;" << std::endl;
						Include << std::endl;

						Source << "  MB4_C_OBJ_GETTER(" << UpperName << "," << LowerName << "," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;

						Include << "/**" << std::endl;
						Include << " * @see MusicBrainz4::C" << UpperName << "::" << PropertyUpperName << "List" << std::endl;
						Include << " *" << std::endl;
						Include << " * @param " << UpperName << " #Mb4" << UpperName << "List object" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return #Mb4" << PropertyUpperName << "List object" << std::endl;
						Include << " */" << std::endl;
						Include << "  Mb4" << PropertyUpperName << "List mb4_" << LowerName << "_get_" << PropertyLowerName << "list(Mb4" << UpperName << " " << UpperName << ");" << std::endl;
						Include << std::endl;

						Source << "  MB4_C_OBJ_GETTER(" << UpperName << "," << LowerName << "," << PropertyUpperName << "List," << PropertyLowerName << "list)" << std::endl;
					}
					else if ("iswc"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @deprecated @see MusicBrainz4::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * <b>This method is deprecated, please use #mb4_" << LowerName << "_get_" << PropertyLowerName << "list</b>" << std::endl;
						Include << " *" << std::endl;
						Include << " * @param " << UpperName << " #Mb4" << UpperName << " object" << std::endl;
						Include << " * @param str Returned string" << std::endl;
						Include << " * @param len Number of characters available in return string" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return The number of characters in the string to copy (not including terminating NULL)" << std::endl;
						Include << " */" << std::endl;
						Include << "  int mb4_" << LowerName << "_get_" << PropertyLowerName << "(Mb4" << UpperName << " " << UpperName << ", char *str, int len) LIBMB4_DEPRECATED(mb4_" << LowerName << "_get_" << PropertyLowerName << "list);" << std::endl;
						Include << std::endl;

						Source << "  MB4_C_STR_GETTER(" << UpperName << "," << LowerName << "," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;

						Include << "/**" << std::endl;
						Include << " * @see MusicBrainz4::C" << UpperName << "::" << PropertyUpperName << "List" << std::endl;
						Include << " *" << std::endl;
						Include << " * @param " << UpperName << " #Mb4" << UpperName << "List object" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return #Mb4" << PropertyUpperName << "List object" << std::endl;
						Include << " */" << std::endl;
						Include << "  Mb4" << PropertyUpperName << "List mb4_" << LowerName << "_get_" << PropertyLowerName << "list(Mb4" << UpperName << " " << UpperName << ");" << std::endl;
						Include << std::endl;

						Source << "  MB4_C_OBJ_GETTER(" << UpperName << "," << LowerName << "," << PropertyUpperName << "List," << PropertyLowerName << "list)" << std::endl;
					}
					else
					{
						std::cerr << "Unexpected property type: '" << PropertyType << "'" << std::endl;
						exit(1);
					}
				}
				else
				{
					std::cerr << "Class " << LowerName << " property specified with no name or type" << std::endl;
					exit(1);
				}
			}
		}

		Source << std::endl;
	}
	else
	{
		std::cerr << "Class specified with no name" << std::endl;
		exit(1);
	}
}

void ProcessList(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include)
{
	if (Node.isAttributeSet("name"))
	{
		std::string LowerName=Node.getAttribute("name");

		std::string UpperName=LowerName;
		if (Node.isAttributeSet("uppername"))
			UpperName=Node.getAttribute("uppername");
		else
			UpperName[0]=toupper(UpperName[0]);

		Include << "/**" << std::endl;
		Include << " * Delete a #Mb4" << UpperName << "List" << std::endl;
		Include << " *" << std::endl;
		Include << " * @param List List to delete" << std::endl;
		Include << " */" << std::endl;
		Include << "  void mb4_" << LowerName << "_list_delete(Mb4" << UpperName << "List List);" << std::endl;
		Include << std::endl;
		Include << "/**" << std::endl;
		Include << " * Return the number of entries in a #Mb4" << UpperName << "List" << std::endl;
		Include << " *" << std::endl;
		Include << " * @param	List List to use" << std::endl;
		Include << " */" << std::endl;
		Include << "  int mb4_" << LowerName << "_list_size(Mb4" << UpperName << "List List);" << std::endl;
		Include << std::endl;
		Include << "/**" << std::endl;
		Include << " * Returns an entry from a #Mb4" << UpperName << "List" << std::endl;
		Include << " *" << std::endl;
		Include << " * @param List List to use" << std::endl;
		Include << " * @param Item Item number to return" << std::endl;
		Include << " *" << std::endl;
		Include << " * @return A #Mb4" << UpperName << " object." << std::endl;
		Include << " */" << std::endl;
		Include << "  Mb4" << UpperName << " mb4_" << LowerName << "_list_item(Mb4" << UpperName << "List List, int Item);" << std::endl;
		Include << std::endl;
		Include << "/**" << std::endl;
		Include << " *	Return the count of entries in an #Mb4" << UpperName << "List" << std::endl;
		Include << " *" << std::endl;
		Include << " * @param	List List to use" << std::endl;
		Include << " */" << std::endl;
		Include << "	int mb4_" << LowerName << "_list_get_count(Mb4" << UpperName << "List List);" << std::endl;
		Include << std::endl;
		Include << "/**" << std::endl;
		Include << " *	Return the offset of entries in an #Mb4" << UpperName << "List" << std::endl;
		Include << " *" << std::endl;
		Include << " * @param	List List to use" << std::endl;
		Include << " */" << std::endl;
		Include << "	int mb4_" << LowerName << "_list_get_offset(Mb4" << UpperName << "List List);" << std::endl;
		Include << std::endl;

		Source << "  MB4_C_LIST_GETTER(" << UpperName << "," << LowerName << ")" << std::endl;

		Include << "/**" << std::endl;
		Include << "* Clone an #Mb4" << UpperName << "List object" << std::endl;
		Include << "*" << std::endl;
		Include << "* @param " << UpperName << "List Object to clone" << std::endl;
		Include << "*" << std::endl;
		Include << "* @return Cloned list. This list <b>must</b> be deleted once" << std::endl;
		Include << "*				finished with." << std::endl;
		Include << "*/" << std::endl;
		Include << "  Mb4" << UpperName << "List mb4_" << LowerName << "_list_clone(Mb4" << UpperName << "List " << UpperName << "List" << ");" << std::endl;
		Include << std::endl;

		Source << "  MB4_C_CLONE(" << UpperName << "List," << LowerName << "_list)" << std::endl;

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string Name=ChildNode.getName();

			if ("property"==Name)
			{
				if (ChildNode.isAttributeSet("name") && ChildNode.isAttributeSet("type"))
				{
					std::string PropertyLowerName=ChildNode.getAttribute("name");

					std::string PropertyUpperName=PropertyLowerName;
					if (ChildNode.isAttributeSet("uppername"))
						PropertyUpperName=ChildNode.getAttribute("uppername");
					else
						PropertyUpperName[0]=toupper(PropertyUpperName[0]);

					std::string PropertyType=ChildNode.getAttribute("type");

					if ("string"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @see MusicBrainz4::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * @param List List to use" << std::endl;
						Include << " * @param str Returned string" << std::endl;
						Include << " * @param len Number of characters available in return string" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return The number of characters in the string to copy (not including terminating NULL)" << std::endl;
						Include << " */" << std::endl;
						Include << "  int mb4_" << LowerName << "_list_get_" << PropertyLowerName << "(Mb4" << UpperName << "List List, char *str, int len);" << std::endl;
						Include << std::endl;

						Source << "  MB4_C_STR_GETTER(" << UpperName << "List," << LowerName << "_list," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;
					}
					else if ("integer"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @see MusicBrainz4::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * @param List List to use" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return Returned value" << std::endl;
						Include << " */" << std::endl;
						Include << "  int mb4_" << LowerName << "_list_get_" << PropertyLowerName << "(Mb4" << UpperName << "List List);" << std::endl;
						Include << std::endl;

						Source << "  MB4_C_INT_GETTER(" << UpperName << "List," << LowerName << "_list," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;
					}
					else if ("double"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @see MusicBrainz4::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * @param List List to use" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return Returned value" << std::endl;
						Include << " */" << std::endl;
						Include << "  double mb4_" << LowerName << "_list_get_" << PropertyLowerName << "(Mb4" << UpperName << "List List);" << std::endl;
						Include << std::endl;

						Source << "  MB4_C_DOUBLE_GETTER(" << UpperName << "List," << LowerName << "_list," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;
					}
					else if ("object"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @see MusicBrainz4::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * @param List List to use" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return #Mb4" << PropertyUpperName << " object" << std::endl;
						Include << " */" << std::endl;
						Include << "  int mb4_" << LowerName << "_list_get_" << PropertyLowerName << "(Mb4" << UpperName << "List List);" << std::endl;
						Include << std::endl;

						Source << "  MB4_C_OBJ_GETTER(" << UpperName << "List," << LowerName << "_list," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;
					}
					else
					{
						std::cerr << "Unexpected property type: '" << PropertyType << "'" << std::endl;
						exit(1);
					}
				}
				else
				{
					std::cerr << "List " << LowerName << " property specified with no name or type" << std::endl;
					exit(1);
				}
			}
		}

		Source << std::endl;
	}
	else
	{
		std::cerr << "List specified with no name" << std::endl;
		exit(1);
	}
}

void ProcessDeclare(const XMLNode& Node, std::ofstream& /*Source*/, std::ofstream& Include)
{
	std::vector<std::string> Classes;
	Classes.push_back("Entity");

	for (int count=0;count<Node.nChildNode();count++)
	{
		XMLNode ChildNode=Node.getChildNode(count);
		std::string Name=ChildNode.getName();

		if ("class"==Name || "list"==Name)
		{
			if (ChildNode.isAttributeSet("name"))
			{
				std::string UpperName=ChildNode.getAttribute("name");
				if (ChildNode.isAttributeSet("uppername"))
					UpperName=ChildNode.getAttribute("uppername");
				else
					UpperName[0]=toupper(UpperName[0]);

				if ("list"==Name)
					UpperName+="List";

				Classes.push_back(UpperName);
			}
			else
			{
				std::cerr << "Entity, Class or List specified with no name or type" << std::endl;
				exit(1);
			}
		}
	}

	for (std::vector<std::string>::const_iterator Class=Classes.begin();Class!=Classes.end();Class++)
	{
		Include << "  typedef void *Mb4" << *Class << ";" << std::endl;
	}

	Include << std::endl;

}
