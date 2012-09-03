/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   libmusicbrainz4 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

Mb4Query mb4_query_new(const char *UserAgent, const char *Server, int Port)
{
	return new MusicBrainz4::CQuery(UserAgent, Server ? Server : "musicbrainz.org", Port!=0 ? Port : 80);
}

MB4_C_STR_SETTER(Query,query,UserName,username)
MB4_C_STR_SETTER(Query,query,Password,password)
MB4_C_STR_SETTER(Query,query,ProxyHost,proxyhost)
MB4_C_INT_SETTER(Query,query,ProxyPort,proxyport)
MB4_C_STR_SETTER(Query,query,ProxyUserName,proxyusername)
MB4_C_STR_SETTER(Query,query,ProxyPassword,proxypassword)

Mb4ReleaseList mb4_query_lookup_discid(Mb4Query Query, const char *DiscID)
{
	if (Query)
	{
		try
		{
			MusicBrainz4::CQuery *TheQuery=reinterpret_cast<MusicBrainz4::CQuery *>(Query);
			if (TheQuery)
				return new MusicBrainz4::CReleaseList(TheQuery->LookupDiscID(DiscID));
		}

		catch(...)
		{
		}
	}

	return 0;
}

Mb4Release mb4_query_lookup_release(Mb4Query Query, const char *Release)
{
	if (Query)
	{
		try
		{
			MusicBrainz4::CQuery *TheQuery=reinterpret_cast<MusicBrainz4::CQuery *>(Query);
			if (TheQuery)
				return new MusicBrainz4::CRelease(TheQuery->LookupRelease(Release));
		}

		catch(...)
		{
		}
	}

	return 0;
}

Mb4Metadata mb4_query_query(Mb4Query Query, const char *Entity, const char *ID, const char *Resource, int NumParams, char **ParamName, char **ParamValue)
{
	if (Query)
	{
		try
		{
			MusicBrainz4::CQuery::tParamMap Params;

			for (int count=0;count<NumParams;count++)
			{
				if (ParamName[count] && ParamValue[count])
					Params[ParamName[count]]=ParamValue[count];
			}

			MusicBrainz4::CQuery *TheQuery=reinterpret_cast<MusicBrainz4::CQuery *>(Query);
			if (TheQuery)
				return new MusicBrainz4::CMetadata(TheQuery->Query(Entity?Entity:"",
																											ID?ID:"",
																											Resource?Resource:"",
																											Params));
		}

		catch(...)
		{
		}
	}

	return 0;
}

unsigned char mb4_query_add_collection_entries(Mb4Query Query, const char *Collection, int NumEntries, const char **Entries)
{
	if (Query)
	{
		try
		{
			std::vector<std::string> VecEntries;

			MusicBrainz4::CQuery *TheQuery=reinterpret_cast<MusicBrainz4::CQuery *>(Query);
			if (TheQuery)
			{
				for (int count=0;count<NumEntries;count++)
				{
					if (Entries && Entries[count])
					{
						VecEntries.push_back(Entries[count]);
					}
				}

				return TheQuery->AddCollectionEntries(Collection,VecEntries)?1:0;
			}
		}

		catch(...)
		{
		}
	}

	return 0;
}

unsigned char mb4_query_delete_collection_entries(Mb4Query Query, const char *Collection, int NumEntries, const char **Entries)
{
	if (Query)
	{
		try
		{
			std::vector<std::string> VecEntries;

			MusicBrainz4::CQuery *TheQuery=reinterpret_cast<MusicBrainz4::CQuery *>(Query);
			if (TheQuery)
			{
				for (int count=0;count<NumEntries;count++)
				{
					if (Entries && Entries[count])
					{
						VecEntries.push_back(Entries[count]);
					}
				}

				return TheQuery->AddCollectionEntries(Collection,VecEntries)?1:0;
			}
		}

		catch(...)
		{
		}
	}

	return 0;
}

tQueryResult mb4_query_get_lastresult(Mb4Query o)
{
	if (o)
	{
		try
		{
			return (tQueryResult)((MusicBrainz4::CQuery *)o)->LastResult();
		}

		catch (...)
		{
		}
	}

	return eQuery_FetchError;
}

