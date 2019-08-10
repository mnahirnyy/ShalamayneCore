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

#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "ScriptedCreature.h"
#include "ScriptMgr.h"
#include "SpellAuras.h"
#include "SpellScript.h"
#include "tomb_of_sargeras.h"

//constant positions about teleports and Kasparian Jumps
Position const LunaspyreTeleports[5] =
{
    {},
    {},
    {},
    {},
    {},
};

Position const CenterCombat[1] =
{
    {},
};

Position const YathaeTeleports[5] =
{
    {},
    {},
    {},
    {},
    {},
};

Position const KasparianJumps[5] =
{
    {},
    {},
    {},
    {},
    {},
};


enum Says
{
    //Sisters
    SAY_SISTERS_AGGRO     = 1,
    SAY_SISTERS_DEATH     = 2,
    //Kasparian
    SAY_SPELL_GLAIVE      = 3,
    SAY_KASPARIAN_KILLS   = 4,
    SAY_KSISTER_KILLS     = 5,
    //Yathae
    SAY_YPHASE_COMBAT     = 6,
    SAY_SPELLS_ARROW      = 7,
    SAY_SPELL_AOE         = 8,
    SAY_YATHAE_KILLS      = 9,
    SAY_YSISTER_KILLS     = 10,
    //Lunaspyre
    SAY_LPHASE_COMBAT     = 11,
    SAY_SPELL             = 12,
    SAY_FOUNTAIN_OF_ELUNE = 13,
    SAY_LUNASPYRE_KILLS   = 14
};

enum SistersSpells
{
    //Generic
    SPELL_QUIET_SUICIDE 				= 3617, // Serverside spell
    SPELL_INCORPOREAL_TELEPORT 			= 236115, //Cast
    SPELL_INCORPOREAL_TELEPORT_2 		= 236224, //Not sure if this is the teleport or need script. Instant cast. These two teleport spells are the same for Lunaspyre
    SPELL_COOLDOWN_CREATURE_SPECIAL 	= 61207, //To block other spells from interfering with their special
    SPELL_GHOST_AURA 					= 235268, //Cosmetic for Sisters
    SPELL_ELUNE_FOUNTAIN 				= 236357, //Create AT 11284
    SPELL_LUNAR_SUFFUSION 				= 234995, //Add the aura every 3 seconds on the bright side
    SPELL_UMBRA_SUFFUSION 				= 234996, //Add the aura every 3 seconds on the dark side
    SPELL_ASTRAL_PURGE 					= 234998, //Will trigger on change side in Fountain of Elune, and reset Suffusion marks.
    //Kasparian
    SPELL_TWILIGHT_GLAIVE_AT 			= 236529,// AT 9785 and add aura to bunny + make bunny got target,then return
    SPELL_TWILIGHT_GLAIVE_DAMAGE 		= 236541,
    SPELL_TWILIGHT_GLAIVE_DUMMY 		= 237561,
    SPELL_MOON_GLAIVE 					= 236547,
    SPELL_DISCORPORATE 					= 236550, //Astral Purge will remove it.
    SPELL_GLAIVE_STORM 					= 239379, //Only used in Elune's Fountain Phase 3 (normal), phase 2 and 3 heroic and mythic
    //Yathae
    SPELL_SHADOW_SHOT 					= 237630,
    SPELL_INCORPOREAL_SHOT_CAST 		= 236305,//Only used in Elune's Fountain Phase 2 (normal), phase 1 and 3 heroic and mythic
    SPELL_INCORPOREAL_SHOT_DAMAGE 		= 236306,
    SPELL_CALL_MOONTALON 				= 236694,
    SPELL_TWILIGHT_VOLLEY_AT 			= 236442,// AT 9777
    SPELL_TWILIGHT_VOLLEY_DAMAGE 		= 236516, //Apply this aura OnUnitEnter();
    SPELL_RAPID_SHOT 					= 236598,
    SPELL_RAPID_SHOT_AURA 				= 236596,
    //Lunaspyre
    SPELL_EMBRACE_OF_THE_ECLIPSE_BOSS 	= 233263,//Shields Heal
    SPELL_EMBRACE_OF_THE_ECLIPSE_BOSS_2 = 233264,//Shield Boss
    SPELL_LUNAR_BEACON 					= 236712,//OnRemove(); actives Lunar barrage.
    SPELL_LUNAR_FIRE 					= 239264,//Only on current target,active.
    SPELL_LUNAR_STRIKE 					= 237632,
    SPELL_MOON_BURN 					= 236518,//Astral Purge will remove this.
    SPELL_LUNAR_BARRAGE_AT 				= 236726,//AT 9807
    SPELL_LUNAR_BARRAGE_DAMAGE 			= 237351,
};

enum Events
{
    ///Possible Events
    //General
    EVENT_INCORPOREAL_TELEPORT = 1,
    EVENT_TELEPORT_CENTER_COMBAT,
    EVENT_BACK_TO_GHOST,
    EVENT_BERSERKER,
    //Kasparian
    EVENT_TWILIGHT_GLAIVE,
    EVENT_MOON_GLAIVE,
    EVENT_GLAIVE_STORM,
    EVENT_JUMP_TIGER,
    //Yathae
    EVENT_SHADOW_SHOT,
    EVENT_INCORPOREAL_SHOT,
    EVENT_CALL_MOONTALON,
    EVENT_TWILIGHT_VOLLEY,
    EVENT_RAPID_SHOT,
    //Lunaspyre
    EVENT_EMBRACE_OF_THE_ECLIPSE,
    EVENT_LUNAR_BEACON,
    EVENT_LUNAR_FIRE,
    EVENT_LUNAR_STRIKE,
    EVENT_MOON_BURN
};

enum Phases
{
    PHASE_THE_HUNTRESS   = 1,
    PHASE_THE_CAPTAIN    = 2,
    PHASE_THE_PRIESTESS  = 3
};

enum Misc //If needed
{
    ACTION_YATHAE_COMBAT = 1,
    ACTION_LUNASPYRE_ACTION,
};

void AddSC_boss_sisters_of_moon()
{
}
