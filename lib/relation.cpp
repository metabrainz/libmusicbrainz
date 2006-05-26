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
 */
 
#include <string>
#include "relation.h"

using namespace std;
using namespace MusicBrainz;

Relation::Relation(const std::string &relationType,
                   const TargetType targetType,
                   const std::string &targetId,
                   const Direction direction,
                   const std::vector<std::string> &attributes,
                   const std::string beginDate,
                   const std::string endDate,
                   Entity *target)
{
    setType(relationType);
    setTargetType(targetType);
    setTargetId(targetId);
    setDirection(direction);
    this->attributes = attributes;
    setBeginDate(beginDate);
    setEndDate(endDate);
    setTarget(target);
}

string
Relation::getType() const
{
    return type;
}

void
Relation::setType(const string &value)
{
    type = value;
}

string
Relation::getTargetId() const
{
    return targetId;
}

void
Relation::setTargetId(const string &value)
{
    targetId = value;
}

Relation::Direction
Relation::getDirection() const
{
    return direction;
}

void
Relation::setDirection(const Relation::Direction value)
{
    direction = value;
}

Relation::TargetType
Relation::getTargetType() const
{
    return targetType;
}

void
Relation::setTargetType(const Relation::TargetType value)
{
    targetType = value;
}

Entity *
Relation::getTarget() const
{
    return target;
}

void
Relation::setTarget(Entity *value)
{
    target = value;
}

const Relation::Attributes &
Relation::getAttributes() const
{
    return attributes;
}

void
Relation::addAttribute(const string &value)
{
    attributes.push_back(value);
}

string
Relation::getBeginDate() const
{
    return beginDate;
}

void
Relation::setBeginDate(const string &value)
{
    beginDate = value;
}

string
Relation::getEndDate() const
{
    return endDate;
}

void
Relation::setEndDate(const string &value)
{
    endDate = value;
} 


