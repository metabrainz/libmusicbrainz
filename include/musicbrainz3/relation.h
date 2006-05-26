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
 
#ifndef __MUSICBRAINZ3_RELATION_H__
#define __MUSICBRAINZ3_RELATION_H__

#include <string>
#include <vector>
#include <musicbrainz3/musicbrainz.h>

namespace MusicBrainz
{
    
    class Entity;
    
    /**
     * Represents a relation between two Entities.
     *
     * There may be an arbitrary number of relations between all first
     * class objects in MusicBrainz. The Relation itself has multiple
     * attributes, which may or may not be used for a given relation
     * type.
     *
     * Note that a Relation object only contains the target but not
     * the source end of the relation.
     */
    class MB_API Relation
    {
    public:

        enum TargetType {
            //! No relation target type.
            TO_NULL,
            //! Identifies relations linking to an Artist. 
            TO_ARTIST,
            //! Identifies relations linking to a Release. 
            TO_RELEASE,
            //! Identifies relations linking to a Track. 
            TO_TRACK,
            //! Identifies relations linking to an URL. 
            TO_URL
        };
    
        enum Direction {
            //! Relation reading direction doesn't matter. 
            DIR_BOTH,
            //! Relation reading direction is from source to target. 
            DIR_FORWARD,
            //! Relation reading direction is from target to source. 
            DIR_BACKWARD
        };
        
        typedef std::vector<std::string> Attributes;
        
        /**
         * Constructor.
         */
        Relation(const std::string &relationType = std::string(),
                 const TargetType targetType = TO_NULL,
                 const std::string &targetId = std::string(),
                 const Direction direction = DIR_BOTH,
                 const Attributes &attributes = Attributes(),
                 const std::string beginDate = std::string(),
                 const std::string endDate = std::string(),
                 Entity *target = NULL);
        
        std::string getType() const;
        void setType(const std::string &type);
        
        std::string getTargetId() const;
        void setTargetId(const std::string &value);
        
        TargetType getTargetType() const;
        void setTargetType(const TargetType value);
        
        std::string getBeginDate() const;
        void setBeginDate(const std::string &value);
        
        std::string getEndDate() const;
        void setEndDate(const std::string &value);
        
        Direction getDirection() const;
        void setDirection(const Direction value);
        
        const Attributes &getAttributes() const;
        void addAttribute(const std::string &value);
        
        /**
         * Returns this relation's target object.
         *
         * Note that URL relations never have a target object. Use the
         * getTargetId method to get the URL.
         * 
         * @return a subclass of Entity, or NULL 
         */ 
        Entity *getTarget() const;
        
        /**
         * Sets this relation's target object.
         *
         * Note that URL relations never have a target object, they
         * are set using setTargetId.
         * 
         * @param target a subclass of Entity 
         */
        void setTarget(Entity *target);
        
    private:
        
        std::string type;
        TargetType targetType;
        std::string targetId;
        Direction direction;
        Entity *target;
        std::string beginDate;
        std::string endDate;
        Attributes attributes;
        
    };
    
}

#endif