/*
 * Copyright (C) 2017-2018 AshamaneProject <https://github.com/AshamaneProject>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EMERALD_NIGHTMARE_H
#define EMERALD_NIGHTMARE_H

#include "Chat.h"
#include "CombatAI.h"
#include "Conversation.h"
#include "Creature.h"
#include "CreatureGroups.h"
#include "CreatureTextMgr.h"
#include "DBCEnums.h"
#include "DynamicObject.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "LFGMgr.h"
#include "LFGPackets.h"
#include "LFGQueue.h"
#include "InstanceScript.h"
#include "Map.h"
#include "MiscPackets.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "PhasingHandler.h"
#include "SceneMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "SpellAuras.h"
#include "SpellScript.h"
#include "SpellInfo.h"
#include "TemporarySummon.h"
#include "Transport.h"
#include "Unit.h"
#include "Vehicle.h"

enum DataTypes
{
    DATA_NYTHENDRA              = 0,
    DATA_ILGYNOTH               = 1,
    DATA_ELERETHE_RENFERAL      = 2,
    DATA_URSOC                  = 3,
    DATA_DRAGONS_OF_NIGHTMARE   = 4,
    DATA_CENARIUS               = 5,
    DATA_XAVIUS                 = 6,
    DATA_EYE_ILGYNOTH           = 7,
    DATA_PRE_EVENT_XAVIUS       = 8,

    DATA_MAX_ENCOUNTERS
};

enum Creatures
{
    NPC_NYTHENDRA               = 102672,
    NPC_CORRUPTED_VERMIN        = 102998,

    NPC_ILGYNOTH                = 105393,
    NPC_ELERETHE_RENFERAL       = 106087,
    NPC_URSOC                   = 100497,
    NPC_YSONDRE                 = 102679,
    NPC_EMERISS                 = 102683,
    NPC_LETHON                  = 102682,
    NPC_TAERAR                  = 102681,
    NPC_CENARIUS                = 104636,
    NPC_XAVIUS                  = 103769,

    //Ilgynoth
    NPC_EYE_OF_ILGYNOTH         = 105906,
    NPC_DOMINATOR_TENTACLE      = 105304,
    NPC_DEATHGLARE_TENTACLE     = 105322,
    NPC_CORRUPTOR_TENTACLE      = 105383,
    NPC_NIGHTMARE_HORROR        = 105591,
    NPC_NIGHTMARE_ICHOR         = 105721,
    NPC_DEATH_BLOSSOM           = 108659, //Mythic
    NPC_SHRIVELED_EYESTALK      = 108821, //Mythic

    //Xavius
    NPC_SLEEPING_VERSION        = 104096,
    NPC_DREAD_ABOMINATION       = 105343,
    NPC_LURKING_TERROR          = 103694,
    NPC_CORRUPTION_HORROR       = 103695,
    NPC_NIGHTMARE_BLADES        = 104422,
    NPC_INCONCEIVABLE_HORROR    = 105611,
    NPC_NIGHTMARE_TENTACLE      = 104592,

    // Events
    NPC_IN_THE_SHADOW           = 111370,
    NPC_NIGHTMARE_AMALGAMATION  = 111398,
    NPC_SHADOW_POUNDER          = 111405,
    NPC_DARK_DEVOURERS          = 111413,
    NPC_YZERA                   = 105245,
    NPC_SMALL_TRASH             = 111350
};

enum GameObjects
{
    GOB_NYTHENDRA_ENTRANCE_1    = 251535,
    GOB_NYTHENDRA_ENTRANCE_2    = 251536,
};

enum SpellVisualKit
{
    SPELL_VISUAL_KIT_EMERALD_NIGHTMARE_ENTRANCE_LOCATION = 70900,
    SPELL_VISUAL_KIT_EMERALD_NIGHTMATE_POST_XAVIUS_EXIT  = 74270,
};

class DelayDestCastEvent : public BasicEvent
{
public:
    DelayDestCastEvent(Unit& owner, Position _pos, uint32 s, bool _triggered, ObjectGuid c = ObjectGuid::Empty) : BasicEvent(), m_owner(owner), CasterGUID(c), pos(_pos), Spell(s), triggered(_triggered) {}

    bool Execute(uint64, uint32) override
    {
        return true;
    }

private:
    Unit& m_owner;
    ObjectGuid CasterGUID;
    Position pos;
    uint32 Spell;
    bool triggered;
};

#endif
