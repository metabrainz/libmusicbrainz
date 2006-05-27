/*
 * MusicBrainz -- The Internet music metadatabase
 *
 * Copyright (C) 2006 Lukas Lalinsky
 *	
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA	 02111-1307	 USA
 */
 
#ifndef __MUSICBRAINZ3_ARTIST_H__
#define __MUSICBRAINZ3_ARTIST_H__

#include <string>
#include <vector>
#include <musicbrainz3/musicbrainz.h>
#include <musicbrainz3/entity.h>
#include <musicbrainz3/lists.h>

namespace MusicBrainz
{

	/**
	 * Represents an artist.
	 *
	 * Artists in MusicBrainz can have a type. Currently, this type can
	 * be either Person or Group for which the following URIs are assigned:
	 *
	 *	- \a "http://musicbrainz.org/ns/mmd-1.0#Person"
	 *	- \a "http://musicbrainz.org/ns/mmd-1.0#Group"
	 *
	 * Use the \a Artist::TYPE_PERSON and \a Artist::TYPE_GROUP constants for comparison. 
	 */
	class MB_API Artist : public Entity
	{
	public:
	
		static const std::string TYPE_PERSON; 
		static const std::string TYPE_GROUP;
	
		/**
		 * Constructor.
		 *
		 * @param id a string containing an absolute URI
		 * @param type a string containing an absolute URI
		 * @param name a string containing the artist's name
		 * @param sortName a string containing the artist's sort name 
		 */
		Artist(const std::string &id = "", const std::string &type = "",
			   const std::string &name = "", const std::string &sortName = "");
		
		/**
		 * Destructor.
		 */
		~Artist();
		
		/**
		 * Returns the artist's type.
		 *
		 * @return a string containing an absolute URI	
		 */
		std::string getType() const;
		
		/**
		 * Sets the artist's type.
		 *
		 * @param type a string containing an absolute URI 
		 */
		void setType(const std::string &type);
		
		/**
		 * Returns the artist's name.
		 * 
		 * @return a string containing the artist's name, or empty string
		 */ 
		std::string getName() const;
		
		/**
		 * Sets the artist's name.
		 *
		 * @param name a string containing the artist's name
		 */
		void setName(const std::string &name);

		/**
		 * Returns the artist's sort name.
		 *
		 * <p>The sort name is the artist's name in a special format which
		 * is better suited for lexicographic sorting. The MusicBrainz
		 * style guide specifies this format.</p>
		 * 
		 * @see <a href="http://musicbrainz.org/style.html">The MusicBrainz Style Guidelines</a>
		 */ 
		std::string getSortName() const;
		
		/**
		 * Sets the artist's sort name.
		 *
		 * @param sortName: a string containing the artist's sort name
		 *
		 * @see #getSortName		 
		 */
		void setSortName(const std::string &sortName);

		std::string getDisambiguation() const;
		void setDisambiguation(const std::string &disambiguation);
		
		std::string getBeginDate() const;
		void setBeginDate(const std::string &value);
		
		std::string getEndDate() const;
		void setEndDate(const std::string &value);
		
		const ReleaseList &getReleases() const;
		void addRelease(Release *release);
		
		ArtistAliasList &getAliases();
		void addAlias(ArtistAlias *alias);
		
	private:

		std::string type;
		std::string name;
		std::string sortName;
		std::string disambiguation;
		std::string beginDate;
		std::string endDate;
		ReleaseList releases;
		ArtistAliasList aliases;
		
	};
	
}

#endif