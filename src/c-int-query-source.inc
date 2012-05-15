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

Mb5Query mb5_query_new(const char *UserAgent, const char *Server, int Port)
{
	return new MusicBrainz5::CQuery(UserAgent, Server ? Server : "musicbrainz.org", Port!=0 ? Port : 80);
}

MB5_C_STR_SETTER(Query,query,UserName,username)
MB5_C_STR_SETTER(Query,query,Password,password)
MB5_C_STR_SETTER(Query,query,ProxyHost,proxyhost)
MB5_C_INT_SETTER(Query,query,ProxyPort,proxyport)
MB5_C_STR_SETTER(Query,query,ProxyUserName,proxyusername)
MB5_C_STR_SETTER(Query,query,ProxyPassword,proxypassword)

Mb5ReleaseList mb5_query_lookup_discid(Mb5Query Query, const char *DiscID)
{
	if (Query)
	{
		try
		{
			MusicBrainz5::CQuery *TheQuery=reinterpret_cast<MusicBrainz5::CQuery *>(Query);
			if (TheQuery)
				return new MusicBrainz5::CReleaseList(TheQuery->LookupDiscID(DiscID));
		}

		catch(...)
		{
		}
	}

	return 0;
}

Mb5Release mb5_query_lookup_release(Mb5Query Query, const char *Release)
{
	if (Query)
	{
		try
		{
			MusicBrainz5::CQuery *TheQuery=reinterpret_cast<MusicBrainz5::CQuery *>(Query);
			if (TheQuery)
				return new MusicBrainz5::CRelease(TheQuery->LookupRelease(Release));
		}

		catch(...)
		{
		}
	}

	return 0;
}

Mb5Metadata mb5_query_query(Mb5Query Query, const char *Entity, const char *ID, const char *Resource, int NumParams, char **ParamName, char **ParamValue)
{
	if (Query)
	{
		try
		{
			MusicBrainz5::CQuery::tParamMap Params;

			for (int count=0;count<NumParams;count++)
			{
				if (ParamName[count] && ParamValue[count])
					Params[ParamName[count]]=ParamValue[count];
			}

			MusicBrainz5::CQuery *TheQuery=reinterpret_cast<MusicBrainz5::CQuery *>(Query);
			if (TheQuery)
				return new MusicBrainz5::CMetadata(TheQuery->Query(Entity?Entity:"",
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

unsigned char mb5_query_add_collection_entries(Mb5Query Query, const char *Collection, int NumEntries, const char **Entries)
{
	if (Query)
	{
		try
		{
			std::vector<std::string> VecEntries;

			MusicBrainz5::CQuery *TheQuery=reinterpret_cast<MusicBrainz5::CQuery *>(Query);
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

unsigned char mb5_query_delete_collection_entries(Mb5Query Query, const char *Collection, int NumEntries, const char **Entries)
{
	if (Query)
	{
		try
		{
			std::vector<std::string> VecEntries;

			MusicBrainz5::CQuery *TheQuery=reinterpret_cast<MusicBrainz5::CQuery *>(Query);
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

tQueryResult mb5_query_get_lastresult(Mb5Query o)
{
	if (o)
	{
		try
		{
			return (tQueryResult)((MusicBrainz5::CQuery *)o)->LastResult();
		}

		catch (...)
		{
		}
	}

	return eQuery_FetchError;
}

