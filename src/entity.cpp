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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Id$
 */
 
#include <string>
#include <musicbrainz3/entity.h>

using namespace std;
using namespace MusicBrainz;

Entity::Entity(const string &id)
{
	setId(id);
}

Entity::~Entity()
{
	for (RelationList::iterator i = relations.begin(); i != relations.end(); i++) 
		delete *i;
	relations.clear();
}

string
Entity::getId() const
{
	return id;
}

void
Entity::setId(const string &id)
{
	this->id = id;
}

RelationList 
Entity::getRelations(const std::string &targetType,
					 const std::string &relationType) const
{
	if (targetType.empty() && relationType.empty())
		return relations;
	
	RelationList result;
	
	if (targetType.empty()) {
		for (RelationList::const_iterator i = relations.begin(); i != relations.end(); i++) {
			if ((*i)->getType() == relationType) {
				result.push_back(*i);
			}
		}
	}
	else if (relationType.empty()) {
		for (RelationList::const_iterator i = relations.begin(); i != relations.end(); i++) {
			if ((*i)->getTargetType() == targetType) {
				result.push_back(*i);
			}
		}
	}
	else {
		for (RelationList::const_iterator i = relations.begin(); i != relations.end(); i++) {
			if ((*i)->getType() == relationType && (*i)->getTargetType() == targetType) {
				result.push_back(*i);
			}
		}
	}
	
	return result;	
}

void
Entity::addRelation(Relation *relation)
{
	relations.push_back(relation);
}

int
Entity::getNumRelations() const
{
	return relations.size();
}

Relation * 
Entity::getRelation(int i)
{
	return relations[i];
}

