/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libmusicbrainz5 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include <iostream>

#include "musicbrainz5/Query.h"
#include "musicbrainz5/HTTPFetch.h"

/* For further information, see the web service search documentation:
 *
 * http://wiki.musicbrainz.org/Text_Search_Syntax
 */

void DoSearch(const std::string& Entity, const std::string Search)
{
	MusicBrainz5::CQuery Query("queryexample-1.0");

	MusicBrainz5::CQuery::tParamMap Params;
	Params["query"]=Search;
	Params["limit"]="10";

	try
	{
		MusicBrainz5::CMetadata Metadata=Query.Query(Entity,"","",Params);

		std::cout << "First 10 " << Entity << "s matching: " << Search << std::endl << Metadata << std::endl;
	}

	catch (MusicBrainz5::CConnectionError& Error)
	{
		std::cout << "Connection Exception: '" << Error.what() << "'" << std::endl;
		std::cout << "LastResult: " << Query.LastResult() << std::endl;
		std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
		std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
	}

	catch (MusicBrainz5::CTimeoutError& Error)
	{
		std::cout << "Timeout Exception: '" << Error.what() << "'" << std::endl;
		std::cout << "LastResult: " << Query.LastResult() << std::endl;
		std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
		std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
	}

	catch (MusicBrainz5::CAuthenticationError& Error)
	{
		std::cout << "Authentication Exception: '" << Error.what() << "'" << std::endl;
		std::cout << "LastResult: " << Query.LastResult() << std::endl;
		std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
		std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
	}

	catch (MusicBrainz5::CFetchError& Error)
	{
		std::cout << "Fetch Exception: '" << Error.what() << "'" << std::endl;
		std::cout << "LastResult: " << Query.LastResult() << std::endl;
		std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
		std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
	}

	catch (MusicBrainz5::CRequestError& Error)
	{
		std::cout << "Request Exception: '" << Error.what() << "'" << std::endl;
		std::cout << "LastResult: " << Query.LastResult() << std::endl;
		std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
		std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
	}

	catch (MusicBrainz5::CResourceNotFoundError& Error)
	{
		std::cout << "ResourceNotFound Exception: '" << Error.what() << "'" << std::endl;
		std::cout << "LastResult: " << Query.LastResult() << std::endl;
		std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
		std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
	}
}

int main(int argc, const char *argv[])
{
	argc=argc;
	argv=argv;

	//Search for all releases by Kate Bush

	DoSearch("release","artist:\"Kate Bush\"");

	//Search for all releases with 'sensual' in the title

	DoSearch("release","release:sensual");

	//Search for all artists with 'john' in the name

	DoSearch("artist","artist:john");
}
