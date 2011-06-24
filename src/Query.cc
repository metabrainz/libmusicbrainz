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

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

//http://musicbrainz.org/doc/XML_Web_Service/Version_2
//http://bugs.musicbrainz.org/browser/mmd-schema/trunk/schema/musicbrainz_mmd-2.0.rng
//http://wiki.musicbrainz.org/Picard_Tag_Mapping

#include "musicbrainz4/Query.h"

#include <sstream>
#include <iostream>

#include <string.h>
#include <sys/time.h>

#include "musicbrainz4/HTTPFetch.h"
#include "musicbrainz4/Disc.h"

#include "config.h"

class MusicBrainz4::CQueryPrivate
{
	public:
		CQueryPrivate()
		:	m_Port(80),
			m_ProxyPort(0)
		{
		}

		std::string m_UserAgent;
		std::string m_Server;
		int m_Port;
		std::string m_UserName;
		std::string m_Password;
		std::string m_ProxyHost;
		int m_ProxyPort;
		std::string m_ProxyUserName;
		std::string m_ProxyPassword;
};

MusicBrainz4::CQuery::CQuery(const std::string& UserAgent, const std::string& Server, int Port)
:	m_d(new CQueryPrivate)
{
	m_d->m_UserAgent=UserAgent;
	m_d->m_Server=Server;
	m_d->m_Port=Port;
}

MusicBrainz4::CQuery::~CQuery()
{
	delete m_d;
}

void MusicBrainz4::CQuery::SetUserName(const std::string& UserName)
{
	m_d->m_UserName=UserName;
}

void MusicBrainz4::CQuery::SetPassword(const std::string& Password)
{
	m_d->m_Password=Password;
}

void MusicBrainz4::CQuery::SetProxyHost(const std::string& ProxyHost)
{
	m_d->m_ProxyHost=ProxyHost;
}

void MusicBrainz4::CQuery::SetProxyPort(int ProxyPort)
{
	m_d->m_ProxyPort=ProxyPort;
}

void MusicBrainz4::CQuery::SetProxyUserName(const std::string& ProxyUserName)
{
	m_d->m_ProxyUserName=ProxyUserName;
}

void MusicBrainz4::CQuery::SetProxyPassword(const std::string& ProxyPassword)
{
	m_d->m_ProxyPassword=ProxyPassword;
}

MusicBrainz4::CMetadata MusicBrainz4::CQuery::PerformQuery(const std::string& Query)
{
	WaitRequest();

	CMetadata Metadata;

	std::string UserAgent=m_d->m_UserAgent;
	if (!UserAgent.empty())
		UserAgent+=" ";
	UserAgent+=PACKAGE "/v" VERSION;

	CHTTPFetch Fetch(UserAgent,m_d->m_Server,m_d->m_Port);

	if (!m_d->m_UserName.empty())
		Fetch.SetUserName(m_d->m_UserName);

	if (!m_d->m_Password.empty())
		Fetch.SetPassword(m_d->m_Password);

	if (!m_d->m_ProxyHost.empty())
		Fetch.SetProxyHost(m_d->m_ProxyHost);

	if (0!=m_d->m_ProxyPort)
		Fetch.SetProxyPort(m_d->m_ProxyPort);

	if (!m_d->m_ProxyUserName.empty())
		Fetch.SetProxyUserName(m_d->m_ProxyUserName);

	if (!m_d->m_ProxyPassword.empty())
		Fetch.SetProxyPassword(m_d->m_ProxyPassword);

	int Ret=Fetch.Fetch(Query);
	std::cout << "Ret: " << Ret << std::endl;

	if (Ret>0)
	{
		std::vector<unsigned char> Data=Fetch.Data();
		std::string strData(Data.begin(),Data.end());

		std::cout << "Ret is '" << strData << "'" << std::endl;

		XMLResults Results;
		XMLNode TopNode=XMLNode::parseString(strData.c_str(), 0, &Results);
		if (Results.error==eXMLErrorNone)
		{
			XMLNode MetadataNode=TopNode.getChildNode("metadata");
			if (!MetadataNode.isEmpty())
			{
				Metadata=CMetadata(MetadataNode);
			}
		}
	}

	return Metadata;

}

MusicBrainz4::CMetadata MusicBrainz4::CQuery::Query(const std::string& Entity, const std::string& ID, const std::string& Resource, const tParamMap& Params)
{
	std::stringstream os;

	os << "/ws/2/" << Entity;

	if (!ID.empty())
	{
		os << "/" << ID;

		if (!Resource.empty())
			os << "/" << Resource;
	}

	if (!Params.empty())
	{
		bool FirstParam=true;

		std::map<std::string,std::string>::const_iterator ThisParam=Params.begin();
		while (ThisParam!=Params.end())
		{
			std::string Name=(*ThisParam).first;
			std::string Values=(*ThisParam).second;

			if (FirstParam)
			{
				os << "?";
				FirstParam=false;
			}
			else
				os << "&";

			os << Name;

			if (!Values.empty())
			{
				bool FirstValue=true;

				os << "=";

				std::string::size_type ThisSpace=Values.find(" ");
				while (ThisSpace!=std::string::npos)
				{
					std::string ThisValue=Values.substr(0,ThisSpace);

					if (FirstValue)
						FirstValue=false;
					else
						os << "+";

					os << ThisValue;
					Values=Values.substr(ThisSpace+1);

					ThisSpace=Values.find(" ");
				}

				if (!Values.empty())
				{
					if (!FirstValue)
						os << "+";

					os << Values;
				}
			}

			++ThisParam;
		}
	}

	std::cout << "Query is '" << os.str() << "'" << std::endl;

	return PerformQuery(os.str());
}

MusicBrainz4::CGenericList<MusicBrainz4::CRelease> MusicBrainz4::CQuery::LookupDiscID(const std::string& DiscID)
{
	//Will this work soon (and return disc IDs as well)?
	//http://www.musicbrainz.org/ws/2/discid/arIS30RPWowvwNEqsqdDnZzDGhk-?inc=artists+labels+recordings+release-groups+artist-credits

	MusicBrainz4::CGenericList<MusicBrainz4::CRelease> ReleaseList;

	CMetadata Metadata=Query("discid",DiscID);

	CDisc *Disc=Metadata.Disc();
	if (Disc && Disc->ReleaseList())
		ReleaseList=*Disc->ReleaseList();

	return ReleaseList;
}

MusicBrainz4::CRelease MusicBrainz4::CQuery::LookupRelease(const std::string& ReleaseID)
{
	MusicBrainz4::CRelease Release;

	tParamMap Params;
	Params["inc"]="artists labels recordings release-groups url-rels discids artist-credits";

	CMetadata Metadata=Query("release",ReleaseID,"",Params);
	if (Metadata.Release())
		Release=*Metadata.Release();

	return Release;
}

void MusicBrainz4::CQuery::WaitRequest() const
{
	if (m_d->m_Server.find("musicbrainz.org")!=std::string::npos)
	{
		static struct timeval LastRequest;
		const int TimeBetweenRequests=2;

		struct timeval TimeNow;
		gettimeofday(&TimeNow,0);

		if (LastRequest.tv_sec!=0 || LastRequest.tv_usec!=0)
		{
			struct timeval Diff;

			do
			{
				gettimeofday(&TimeNow,0);
				timersub(&TimeNow,&LastRequest,&Diff);

				if (Diff.tv_sec<TimeBetweenRequests)
					usleep(100000);
			}	while (Diff.tv_sec<TimeBetweenRequests);
		}

		memcpy(&LastRequest,&TimeNow,sizeof(LastRequest));
	}
}

