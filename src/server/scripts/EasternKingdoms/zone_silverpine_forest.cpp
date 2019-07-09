 /*
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Silverpine_Forest
SD%Complete: 100
SDComment: Quest support: 435
SDCategory: Silverpine Forest
EndScriptData */

/* ContentData
npc_deathstalker_erland
EndContentData */

#include "ScriptMgr.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "Vehicle.h"
#include "CombatAI.h"
#include "Log.h"

/*######
## npc_deathstalker_erland
######*/

enum eErland
{
    SAY_QUESTACCEPT     = 0,
    SAY_START           = 1,
    SAY_AGGRO           = 2,
    SAY_PROGRESS        = 3,
    SAY_LAST            = 4,

    SAY_RANE            = 0,
    SAY_RANE_ANSWER     = 5,
    SAY_MOVE_QUINN      = 6,

    SAY_QUINN           = 7,
    SAY_QUINN_ANSWER    = 0,
    SAY_BYE             = 8,

    QUEST_ESCORTING     = 435,
    NPC_RANE            = 1950,
    NPC_QUINN           = 1951
};

class npc_deathstalker_erland : public CreatureScript
{
public:
    npc_deathstalker_erland() : CreatureScript("npc_deathstalker_erland") { }

    struct npc_deathstalker_erlandAI : public npc_escortAI
    {
        npc_deathstalker_erlandAI(Creature* creature) : npc_escortAI(creature) { }

        void WaypointReached(uint32 waypointId) override
        {
            Player* player = GetPlayerForEscort();
            if (!player)
                return;

            switch (waypointId)
            {
                case 1:
                    Talk(SAY_START, player);
                    break;
                case 10:
                    Talk(SAY_PROGRESS);
                    break;
                case 13:
                    Talk(SAY_LAST, player);
                    player->GroupEventHappens(QUEST_ESCORTING, me);
                    break;
                case 15:
                    if (Creature* rane = me->FindNearestCreature(NPC_RANE, 20.0f))
                        rane->AI()->Talk(SAY_RANE);
                    break;
                case 16:
                    Talk(SAY_RANE_ANSWER);
                    break;
                case 17:
                    Talk(SAY_MOVE_QUINN);
                    break;
                case 24:
                    Talk(SAY_QUINN);
                    break;
                case 25:
                    if (Creature* quinn = me->FindNearestCreature(NPC_QUINN, 20.0f))
                        quinn->AI()->Talk(SAY_QUINN_ANSWER);
                    break;
                case 26:
                    Talk(SAY_BYE);
                    break;
            }
        }

        void Reset() override { }

        void EnterCombat(Unit* who) override
        {
            Talk(SAY_AGGRO, who);
        }
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_ESCORTING)
        {
            creature->AI()->Talk(SAY_QUESTACCEPT, player);

            if (npc_escortAI* pEscortAI = CAST_AI(npc_deathstalker_erland::npc_deathstalker_erlandAI, creature->AI()))
                pEscortAI->Start(true, false, player->GetGUID());
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_deathstalker_erlandAI(creature);
    }
};

// entry: 44615, quest: 26965 'The Warchief Cometh'
class npc_grand_executor_mortuus : public CreatureScript
{
public:
    npc_grand_executor_mortuus() : CreatureScript("npc_grand_executor_mortuus") { }

    enum eNPC
    {
        QUEST_THE_WARCHIEF_COMETH = 26965,
        NPC_GARROSH_HELLSCREAM = 44629,
        NPC_HIGH_WARLORD_CROMUSH = 44640,
        NPC_LADY_SYLVANAS_WINDRUNNER = 44365,
        NPC_HELLSCREEMS_ELITE = 44636,
        NPC_AGATHA = 44608,
        NPC_PORTAL_FROM_ORGRIMMAR = 44630,
        PLAYER_GUID = 99999,
        MOVE_CROMUSH_TO_SYLVANAS = 5405701,
        MOVE_CROMUSH_TO_HOME = 5405702,
        SPELL_RAISE_FORSAKEN = 83173,
        SPELL_AIR_REVENANT_ENTRANCE = 55761,
        SPELL_SIMPLE_TELEPORT = 12980,
        ACTION_START_ANIM = 101,
        EVENT_START_ANIM = 11,
        EVENT_AGATHA_RAISE_FORSAKEN = 201,
        EVENT_TALK_SEQUENCE = 301,
        EVENT_SUMMON_PORTAL = 401,
        EVENT_SUMMON_GARROSH = 12,
        CROMUSH_PATH_TO_GARROSH = 5405701,
        CROMUSH_PATH_TO_HOME = 5405702,
    };

    bool OnQuestAccept(Player* player, Creature* creature, const Quest* quest) override
    {
        if (quest->GetQuestId() == QUEST_THE_WARCHIEF_COMETH)
        {
            creature->GetAI()->SetGUID(player->GetGUID(), PLAYER_GUID);
            creature->GetAI()->DoAction(ACTION_START_ANIM);
            return true;
        }

        return false;
    }

    struct npc_grand_executor_mortuus_AI : public ScriptedAI
    {
        npc_grand_executor_mortuus_AI(Creature* creature) : ScriptedAI(creature) { }

        void Initialize() { }

        void Reset() override
        {
            _events.Reset();
            _playerGUID = ObjectGuid::Empty;
            _garroshGUID = ObjectGuid::Empty;
            _cromushGUID = ObjectGuid::Empty;
            _sylvanasGUID = ObjectGuid::Empty;
            _agathaGUID = ObjectGuid::Empty;
            _animPhase = 0;
            spawnedList.clear();
            portalList.clear();
        }

        void JustSummoned(Creature* summon) override
        {
            spawnedList.push_back(summon->GetGUID());

            switch (summon->GetEntry())
            {
                case NPC_GARROSH_HELLSCREAM:
                {
                    summon->CastSpell(summon, SPELL_SIMPLE_TELEPORT);
                    _garroshGUID = summon->GetGUID();
                    break;
                }
                case NPC_HELLSCREEMS_ELITE:
                {
                    summon->CastSpell(summon, SPELL_SIMPLE_TELEPORT);
                    break;
                }
                case NPC_PORTAL_FROM_ORGRIMMAR:
                {
                    portalList.push_back(summon->GetGUID());
                    break;
                }
                default:
                    break;
            }
        }

        void SetGUID(ObjectGuid guid, int32 id)
        {
            switch (id)
            {
                case PLAYER_GUID:
                {
                    _playerGUID = guid;
                    break;
                }
            }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_START_ANIM:
            {
                if (!_animPhase)
                {
                    if (Creature* cromush = me->FindNearestCreature(NPC_HIGH_WARLORD_CROMUSH, 50.0f))
                        if (Creature* sylvanas = me->FindNearestCreature(NPC_LADY_SYLVANAS_WINDRUNNER, 10.0f))
                            if (Creature* agatha = me->FindNearestCreature(NPC_AGATHA, 25.0f))
                            {
                                _animPhase = 1;
                                _cromushGUID = cromush->GetGUID();
                                _sylvanasGUID = sylvanas->GetGUID();
                                _agathaGUID = agatha->GetGUID();
                                _events.ScheduleEvent(EVENT_START_ANIM, 2000);
                            }
                }
                break;
            }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            UpdateVictim();
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_ANIM:
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE, 1000);
                    _events.ScheduleEvent(EVENT_SUMMON_PORTAL, 4000);
                    _events.ScheduleEvent(EVENT_SUMMON_GARROSH, 5500);
                    break;
                case EVENT_SUMMON_PORTAL:
                    SummonPortalsFromOrgrimmar();
                    break;
                case EVENT_SUMMON_GARROSH:
                    SummonGarroshAndHisEliteGuards();
                    break;
                case EVENT_TALK_SEQUENCE:
                    if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, _sylvanasGUID))
                        sylvanas->AI()->Talk(0);
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 1, 6000);
                    break;
                case EVENT_TALK_SEQUENCE + 1:
                {
                    if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, _sylvanasGUID)) {
                        sylvanas->SetFacingTo(0.808979f);
                        sylvanas->AI()->Talk(1);
                    }
                    if (Creature* garrosh = ObjectAccessor::GetCreature(*me, _garroshGUID))
                        garrosh->GetMotionMaster()->MoveJump(1378.65f, 1044.23f, 53.8389f, 5.251f, 15.0f, 10.0f);
                    if (Creature* cromush = ObjectAccessor::GetCreature(*me, _cromushGUID))
                        cromush->GetMotionMaster()->MovePath(CROMUSH_PATH_TO_GARROSH, false);
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 2, 5000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 2:
                {
                    if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, _sylvanasGUID))
                        sylvanas->SetFacingTo(3.924652f);
                    if (Creature* garrosh = ObjectAccessor::GetCreature(*me, _garroshGUID))
                        garrosh->AI()->Talk(0);
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 3, 12000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 3:
                {
                    if (Creature* garrosh = ObjectAccessor::GetCreature(*me, _garroshGUID)) {
                        garrosh->SetFacingTo(3.9670f);
                        garrosh->AI()->Talk(1);
                    }
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 4, 7000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 4:
                {
                    if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, _sylvanasGUID)) {
                        sylvanas->SetFacingTo(2.426115f);
                        sylvanas->AI()->Talk(2);
                    }
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 5, 5000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 5:
                {
                    if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, _sylvanasGUID)) {
                        sylvanas->SetFacingTo(3.924652f);
                        sylvanas->AI()->Talk(3);
                    }
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 6, 14000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 6:
                {
                    if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, _sylvanasGUID))
                        sylvanas->AI()->Talk(4);
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 7, 5000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 7:
                {
                    if (Creature* garrosh = ObjectAccessor::GetCreature(*me, _garroshGUID))
                        garrosh->AI()->Talk(2);
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 8, 5000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 8:
                {
                    if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, _sylvanasGUID))
                        sylvanas->AI()->Talk(5);
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 9, 6000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 9:
                {
                    if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, _sylvanasGUID))
                        sylvanas->AI()->Talk(6);
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 10, 6000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 10:
                {
                    if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, _sylvanasGUID))
                        sylvanas->AI()->Talk(7);
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 11, 8000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 11:
                {
                    if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, _sylvanasGUID))
                        sylvanas->AI()->Talk(8);
                    _events.ScheduleEvent(EVENT_AGATHA_RAISE_FORSAKEN, 2000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 12:
                {
                    if (Creature* cromush = ObjectAccessor::GetCreature(*me, _cromushGUID))
                        cromush->AI()->Talk(0);
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 13, 6000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 13:
                {
                    if (Creature* garrosh = ObjectAccessor::GetCreature(*me, _garroshGUID))
                        garrosh->AI()->Talk(3);
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 14, 14000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 14:
                {
                    if (Creature* agatha = ObjectAccessor::GetCreature(*me, _agathaGUID))
                        agatha->GetMotionMaster()->MovePoint(1236, agatha->GetHomePosition());
                    if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, _sylvanasGUID))
                        sylvanas->AI()->Talk(9);
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 15, 10000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 15:
                {
                    if (Creature* agatha = ObjectAccessor::GetCreature(*me, _agathaGUID))
                        agatha->SetFacingTo(0.855211f);
                    if (Creature* garrosh = ObjectAccessor::GetCreature(*me, _garroshGUID))
                        garrosh->AI()->Talk(4);
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 16, 6000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 16:
                {
                    if (Creature* garrosh = ObjectAccessor::GetCreature(*me, _garroshGUID))
                        garrosh->AI()->Talk(5);
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 17, 6000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 17:
                {
                    if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, _sylvanasGUID))
                        sylvanas->AI()->Talk(10);
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 18, 6000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 18:
                {
                    if (Creature* garrosh = ObjectAccessor::GetCreature(*me, _garroshGUID)) {
                        garrosh->SetFacingTo(5.251188f);
                        garrosh->AI()->Talk(6);
                    }
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 19, 6000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 19:
                {
                    if (Creature* garrosh = ObjectAccessor::GetCreature(*me, _garroshGUID)) {
                        garrosh->SetFacingTo(2.426115f);
                        garrosh->AI()->Talk(7);
                    }
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 20, 17000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 20:
                {
                    if (Creature* cromush = ObjectAccessor::GetCreature(*me, _cromushGUID))
                        cromush->AI()->Talk(1);
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 21, 5000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 21:
                {
                    if (Creature* garrosh = ObjectAccessor::GetCreature(*me, _garroshGUID)) {
                        garrosh->SetFacingTo(5.251188f);
                        garrosh->AI()->Talk(8);
                    }
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 22, 15000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 22:
                {
                    if (Creature* cromush = ObjectAccessor::GetCreature(*me, _cromushGUID))
                        cromush->GetMotionMaster()->MovePath(CROMUSH_PATH_TO_HOME, false);
                    if (Creature* garrosh = ObjectAccessor::GetCreature(*me, _garroshGUID)) {
                        garrosh->SetFacingTo(3.967066f);
                        garrosh->SetWalk(true);
                        garrosh->GetMotionMaster()->MovePoint(1234, 1357.04f, 1056.93f, 52.95f);
                    }
                    if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                        player->KilledMonsterCredit(NPC_GARROSH_HELLSCREAM);
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 23, 8000);
                    break;
                }
                case EVENT_TALK_SEQUENCE + 23:
                {
                    RemoveAllSpawnedCreatures();
                    if (Creature* cromush = ObjectAccessor::GetCreature(*me, _cromushGUID))
                        cromush->GetMotionMaster()->MoveTargetedHome();
                    Reset();
                    break;
                }
                case EVENT_AGATHA_RAISE_FORSAKEN:
                {
                    if (Creature* agatha = ObjectAccessor::GetCreature(*me, _agathaGUID))
                    {
                        agatha->GetMotionMaster()->MovePoint(1235, 1367.02f, 1031.54f, 55.9914f);
                    }
                    _events.ScheduleEvent(EVENT_AGATHA_RAISE_FORSAKEN + 1, 6000);
                    break;
                }
                case EVENT_AGATHA_RAISE_FORSAKEN + 1:
                {
                    if (Creature* agatha = ObjectAccessor::GetCreature(*me, _agathaGUID))
                        agatha->CastSpell(1368.65f, 1032.19f, 63.3033f, SPELL_RAISE_FORSAKEN, true);
                    _events.ScheduleEvent(EVENT_TALK_SEQUENCE + 12, 9000);
                    break;
                }
                default:
                    break;
                }
            }
            // no melee attacks
        }

        void SummonPortalsFromOrgrimmar()
        {
            me->SummonCreature(NPC_PORTAL_FROM_ORGRIMMAR, 1358.62f, 1054.72f, 53.1200f, 0, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_PORTAL_FROM_ORGRIMMAR, 1393.27f, 1021.20f, 53.2225f, 0, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_PORTAL_FROM_ORGRIMMAR, 1404.71f, 1063.73f, 60.5617f, 0, TEMPSUMMON_TIMED_DESPAWN, 300000);
        }

        void SummonGarroshAndHisEliteGuards()
        {
            for (std::list<ObjectGuid>::const_iterator itr = portalList.begin(); itr != portalList.end(); itr++)
                if (Creature* portal = ObjectAccessor::GetCreature(*me, (*itr)))
                    portal->CastSpell(portal, SPELL_AIR_REVENANT_ENTRANCE);

            // one side
            me->SummonCreature(NPC_HELLSCREEMS_ELITE, 1387.90f, 1029.71f, 53.21853f, 2.827433f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE, 1389.79f, 1024.51f, 53.20833f, 2.827433f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE, 1388.05f, 1026.91f, 53.20833f, 2.827433f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE, 1388.16f, 1020.88f, 53.25523f, 2.827433f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE, 1385.79f, 1025.99f, 53.22593f, 2.827433f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE, 1386.69f, 1023.26f, 53.24393f, 2.827433f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE, 1384.33f, 1022.04f, 53.28123f, 2.827433f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE, 1391.10f, 1027.73f, 53.20483f, 2.827433f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            // other side
            me->SummonCreature(NPC_HELLSCREEMS_ELITE, 1359.10f, 1046.55f, 52.97053f, 5.253441f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE, 1360.89f, 1051.81f, 53.19793f, 5.253441f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE, 1360.75f, 1048.84f, 53.12893f, 5.253441f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE, 1364.43f, 1053.62f, 53.29343f, 5.253441f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE, 1363.08f, 1048.15f, 53.22223f, 5.253441f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE, 1364.08f, 1050.84f, 53.29163f, 5.253441f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE, 1366.69f, 1050.31f, 53.34203f, 5.253441f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE, 1357.85f, 1050.12f, 52.99823f, 5.253441f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            // Garrosh
            me->SummonCreature(NPC_GARROSH_HELLSCREAM, 1402.45f, 1061.62f, 60.56173f, 3.926991f, TEMPSUMMON_TIMED_DESPAWN, 300000);
        }

        void RemoveAllSpawnedCreatures()
        {
            for (std::list<ObjectGuid>::const_iterator itr = spawnedList.begin(); itr != spawnedList.end(); itr++)
                if (Creature* npc = ObjectAccessor::GetCreature(*me, (*itr)))
                    npc->DespawnOrUnsummon(1);
        }

    private:
        EventMap _events;
        ObjectGuid _playerGUID;
        ObjectGuid _garroshGUID;
        ObjectGuid _cromushGUID;
        ObjectGuid _sylvanasGUID;
        ObjectGuid _agathaGUID;
        uint8 _animPhase;
        std::list<ObjectGuid>spawnedList;
        std::list<ObjectGuid>portalList;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_grand_executor_mortuus_AI(creature);
    }
};

// 44592 44593 // quest 26965
class npc_fallen_human : public CreatureScript
{
public:
    npc_fallen_human() : CreatureScript("npc_fallen_human") { }

    enum eSpell
    {
        SPELL_FEIGNED = 80636,
    };

    struct npc_fallen_human_AI : public ScriptedAI
    {
        npc_fallen_human_AI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            me->AddAura(SPELL_FEIGNED, me);
            me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_fallen_human_AI(creature);
    }
};

// spell 83149 'Forsaken Trooper Master Script' for the quest 26965 'The Warchief Cometh'
class spell_forsaken_trooper_master_script : public SpellScriptLoader
{
public:
    spell_forsaken_trooper_master_script() : SpellScriptLoader("spell_forsaken_trooper_master_script") { }

    enum eSpell
    {
        SPELL_FORSAKEN_TROOPER_MALE_01 = 83150,
        SPELL_FORSAKEN_TROOPER_MALE_02 = 83163,
        SPELL_FORSAKEN_TROOPER_MALE_03 = 83164,
        SPELL_FORSAKEN_TROOPER_MALE_04 = 83165,
        SPELL_FORSAKEN_TROOPER_FEMALE_01 = 83152,
        SPELL_FORSAKEN_TROOPER_FEMALE_02 = 83166,
        SPELL_FORSAKEN_TROOPER_FEMALE_03 = 83167,
        SPELL_FORSAKEN_TROOPER_FEMALE_04 = 83168,

    };

    class spell_forsaken_trooper_master_script_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_forsaken_trooper_master_script_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* unit = GetCaster())
                if (Creature* fallenHuman = unit->ToCreature())
                {
                    uint32 roll = RAND(83150, 83163, 83164, 83165, 83152, 83166, 83167, 83168);
                    fallenHuman->CastSpell(fallenHuman, roll, true);
                    fallenHuman->DespawnOrUnsummon(100000);
                }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_forsaken_trooper_master_script_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_forsaken_trooper_master_script_SpellScript();
    }
};

// spell 83173 'Raise Forsaken' for the quest 26965 'The Warchief Cometh'
class spell_raise_forsaken : public SpellScriptLoader
{
public:
    spell_raise_forsaken() : SpellScriptLoader("spell_raise_forsaken") { }

    enum eSpell
    {
        NPC_FALLEN_HUMAN_MALE = 44592,
        NPC_FALLEN_HUMAN_FEMALE = 44593,
        SPELL_FEIGNED = 80636,
    };

    class IsNotInEntryList
    {
    public:
        explicit IsNotInEntryList(std::list<uint32>entrys) : _entrys(entrys) { }

        bool operator()(WorldObject* obj) const
        {
            if (Creature* target = obj->ToCreature())
                for (std::list<uint32>::const_iterator itr = _entrys.begin(); itr != _entrys.end(); ++itr)
                    if (target->GetEntry() == *itr)
                        return false;

            return true;
        }

    private:
        std::list<uint32> _entrys;
    };

    class spell_raise_forsaken_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_raise_forsaken_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            std::list<uint32>entrys;
            entrys.push_back(NPC_FALLEN_HUMAN_MALE);
            entrys.push_back(NPC_FALLEN_HUMAN_FEMALE);
            targets.remove_if(IsNotInEntryList(entrys));
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_raise_forsaken_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_raise_forsaken_SpellScript();
    }

    class spell_raise_forsaken_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_raise_forsaken_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* unit = GetTarget())
                if (Creature* fallenHuman = unit->ToCreature())
                {
                    fallenHuman->SetHover(true);
                    fallenHuman->SetFloatValue(UNIT_FIELD_HOVERHEIGHT, frand(1.8f, 2.2f));
                }
        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* unit = GetTarget())
                if (Creature* fallenHuman = unit->ToCreature())
                {
                    fallenHuman->SetHover(false);
                    fallenHuman->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
                    fallenHuman->RemoveAura(SPELL_FEIGNED);
                    fallenHuman->CastSpell(fallenHuman, 83149, true);
                }
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_raise_forsaken_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            AfterEffectRemove += AuraEffectRemoveFn(spell_raise_forsaken_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_raise_forsaken_AuraScript();
    }
};

// npc 44825 for the quest 26998 'Iterating upon success'
#define GOSSIP_TAXI_TEXT "Show me where I can fly."
#define GOSSIP_OPTION_TEXT "I need to take a bat to the Dawning Isles."
class npc_bat_handler_maggotbreath : public CreatureScript
{
public:
    npc_bat_handler_maggotbreath() : CreatureScript("npc_bat_handler_maggotbreath") { }

    enum eNPC
    {
        QUEST_ITERATING_UPON_SUCCESS = 26998,
        SPELL_SUMMON_BAT = 83584,
        GOSSIP_ACTION_ID = 1,
    };

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();

        if (action == GOSSIP_ACTION_ID)
        {
            if (player->GetQuestStatus(QUEST_ITERATING_UPON_SUCCESS) == QUEST_STATUS_INCOMPLETE)
            {
                CloseGossipMenuFor(player);
                player->CastSpell(player, SPELL_SUMMON_BAT);
                creature->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                creature->AI()->Talk(0);
            }
        }

        return true;
    }
};

static const Position ForsakenBatLandInstance[32] =
{
    {1413.167f, 1020.025f, 56.2354f},
    {1379.672f, 1021.698f, 59.9887f},
    {1249.737f, 1001.905f, 66.9924f},
    {1212.133f, 981.977f, 65.3913f},
    {1180.250f, 927.461f, 60.3111f},
    {1149.332f, 766.078f, 57.3167f},
    {1192.427f, 475.569f, 62.4255f},
    {1204.811f, 329.134f, 50.3452f},
    {1197.199f, 295.636f, 47.8965f},
    {1119.129f, 234.839f, 46.6181f},
    {989.850f, 180.368f, 52.3217f},
    {904.214f, 168.247f, 53.1545f},
    {736.523f, 178.213f, 52.4740f},
    {721.224f, 213.371f, 53.8464f},
    {720.123f, 256.447f, 55.9538f},
    {790.195f, 289.270f, 52.1988f},
    {1058.381f, 312.523f, 51.4779f},
    {1078.933f, 313.845f, 51.2958f},
    {1174.250f, 330.960f, 51.4075f},
    {1186.853f, 345.036f, 50.4988f},
    {1209.858f, 406.546f, 54.7870f},
    {1300.053f, 659.114f, 70.2942f},
    {1361.854f, 853.952f, 70.2904f},
    {1408.335f, 1010.895f, 60.1401f},
    {1419.274f, 1020.781f, 54.8617f},

    {1009.702f, 353.118f, 57.484f},
    {994.671f, 465.943f, 80.597f},
    {972.181f, 656.085f, 119.203f},
    {986.189f, 699.040f, 122.876f},
    {1097.166f, 790.282f, 103.229f},
    {1338.653f, 979.091f, 68.574f},
    {1418.537f, 1019.482f, 53.918f},
};

// npc 44821 for the quest 26998 'Iterating upon success'
class npc_forsaken_bat : public CreatureScript
{
public:
    npc_forsaken_bat() : CreatureScript("npc_forsaken_bat") { }

    enum eNPC
    {
        QUEST_ITERATING_UPON_SUCCESS = 26998,
        NPC_VILE_FIN_ORACLE = 1908,
        NPC_BAT_HANDLER_MAGGOTBREATH = 44825,
        SPELL_GO_HOME = 83594,
    };

    struct npc_forsaken_bat_AI : public VehicleAI
    {
        npc_forsaken_bat_AI(Creature *c) : VehicleAI(c) { }

        uint8 uiPoint = 0;
        ObjectGuid _playerGUID = ObjectGuid::Empty;
        bool FlyDisabled;
        bool Fly;
        bool FlyAway;
        bool boarded;
        bool returning;

        void Reset() override
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            _playerGUID = ObjectGuid::Empty;
            Fly = false;
            FlyDisabled = false;
            boarded = false;
            returning = false;
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
                if (player->GetQuestStatus(QUEST_ITERATING_UPON_SUCCESS) == QUEST_STATUS_INCOMPLETE)
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        _playerGUID = player->GetGUID();
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply) override
        {
            if (who->GetTypeId() == TYPEID_PLAYER)
            {
                if (apply)
                {
                    if (who->ToPlayer()->GetQuestStatus(QUEST_ITERATING_UPON_SUCCESS) == QUEST_STATUS_INCOMPLETE)
                    {
                        me->SetCanFly(true);
                        me->SetDisableGravity(true);
                        me->SetSpeed(MOVE_FLIGHT, 9.9f);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        me->GetMotionMaster()->MoveTakeoff(uiPoint, ForsakenBatLandInstance[uiPoint]);
                        boarded = true;
                        returning = false;
                    }
                }
            }
        }

        //Called at waypoint reached or PointMovement end
        void MovementInform(uint32 /*type*/, uint32 id) override
        {
            if (id == uiPoint && !FlyDisabled)
            {
                ++uiPoint;
                Fly = true;
            }
            if (id == uiPoint && id == 6)
            {
                // attempt to reduce the speed like in one time call handler
                me->SetSpeed(MOVE_FLIGHT, 3.5f);
                ++uiPoint;
                Fly = true;
            }
            if (id == uiPoint && id == 15)
            {
                // attempt to increase the speed like in one time call handler
                me->SetSpeed(MOVE_FLIGHT, 9.9f);
                ++uiPoint;
                Fly = true;
            }
        }

        void GoToTheNextPoint()
        {   
            me->GetMotionMaster()->MovePoint(uiPoint, ForsakenBatLandInstance[uiPoint]);
        }

        void UpdateAI(uint32 /*diff*/) override
        {
            // if player jumps off while flying there is no need to continue
            if (boarded && !FlyDisabled && !me->GetVehicleKit()->IsVehicleInUse())
            {
                me->DespawnOrUnsummon();
                return;
            }
            if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
            {
                if (Fly && !FlyDisabled)
                {
                    Fly = false;
                    GoToTheNextPoint();
                    if (uiPoint == 1)
                    {
                        player->KilledMonsterCredit(NPC_BAT_HANDLER_MAGGOTBREATH);
                    }
                    if (uiPoint == 7)
                    {
                        // we are ready to kill the murlocks
                        Talk(0, player);
                    }
                    if (uiPoint >= 25 && !returning)
                    {
                        // we returned but the job is not done
                        if (Unit *player = me->GetVehicleKit()->GetPassenger(0))
                        {
                            player->ExitVehicle(me);
                            me->DespawnOrUnsummon();
                        }
                        FlyDisabled = true;
                        Fly = true;
                        boarded = false;
                    }
                    if (uiPoint >= 32)
                    {
                        // All is done! Finishing the staff.
                        if (Unit *player = me->GetVehicleKit()->GetPassenger(0))
                        {
                            player->ExitVehicle(me);
                            me->DespawnOrUnsummon();
                        }
                        FlyDisabled = true;
                        Fly = false;
                        boarded = false;
                    }
                }
                if (player->GetReqKillOrCastCurrentCount(QUEST_ITERATING_UPON_SUCCESS, NPC_VILE_FIN_ORACLE) >= 50 && !returning)
                {
                    // Coming home.
                    Talk(1, player);
                    me->CastSpell(me, SPELL_GO_HOME, true);
                    me->GetMotionMaster()->Clear();
                    uiPoint = 26;
                    returning = true;
                    me->SetSpeed(MOVE_FLIGHT, 9.9f);
                    GoToTheNextPoint();
                    Fly = false;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_forsaken_bat_AI(creature);
    }
};

// gameobject 205143 for the quest 27045 'Waiting to Exsanguinate'
class go_abandoned_outhouse : public GameObjectScript
{
public:
    go_abandoned_outhouse() : GameObjectScript("go_abandoned_outhouse") { }

    enum eGameObject
    {
        QUEST_WAITING_TO_EXSANGUINATE = 27045,
        SPELL_SUMMON_DEATHSTALKER_YORICK = 83751,
    };

    bool OnQuestAccept(Player* player, GameObject* go, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_WAITING_TO_EXSANGUINATE)
            player->CastSpell(1301.87f, 1189.36f, 52.1045f, SPELL_SUMMON_DEATHSTALKER_YORICK, true, 0, 0, player->GetGUID());

        return false;
    }
};

// npc 44882 for the quest 27045 'Waiting to exsanguinate'
class npc_deathstalker_rane_yorick : public CreatureScript
{
public:
    npc_deathstalker_rane_yorick() : CreatureScript("npc_deathstalker_rane_yorick") { }

    enum eNPC
    {
        NPC_DEATHSTALKER_RANE_YORICK = 44882,
        NPC_ARMOIRE_IN_ROOM = 44894,
        NPC_ARMOIRE_SUMMONED = 44893,
        NPC_PACKLEADER_IVAR_BLOODFANG = 44884,
        SPELL_STEALTH = 34189,
        SPELL_PERMANENT_FEIGN_DEATH = 29266,
        WAYPOINTS_UP = 4488201,
        MOVEPOINT_HIDDEN_PLACE = 1234,
        EVENT_START_ANIM = 101,
        EVENT_WAIT_ON_PLAYER,
        EVENT_TALK_TO_PLAYER,
        EVENT_HIDE,
        EVENT_SET_FACE_TO_BLOODFANG,
        EVENT_RANE_LAST_MOVE,
        ACTION_RANE_JUMP_DEATH = 2,
    };

    struct npc_deathstalker_rane_yorick_AI : public ScriptedAI
    {
        npc_deathstalker_rane_yorick_AI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
        }

        void Initialize()
        {
            _playerGUID = ObjectGuid::Empty;
            _bloodfangGUID = ObjectGuid::Empty;
            _playerArrived = false;
            _events.Reset();
        }

        void IsSummonedBy(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
                _playerGUID = player->GetGUID();
            _events.ScheduleEvent(EVENT_START_ANIM, 1000);
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE)
                switch (id)
                {
                    case 1:
                        Talk(0);
                        break;
                    case 15:
                        _events.ScheduleEvent(EVENT_WAIT_ON_PLAYER, 1000);
                        break;
                }
            if (type == POINT_MOTION_TYPE)
                switch (id)
                {
                    case MOVEPOINT_HIDDEN_PLACE:
                        me->SetFacingTo(4.8f);
                        break;
                }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
                case ACTION_RANE_JUMP_DEATH:
                    _events.ScheduleEvent(EVENT_RANE_LAST_MOVE, 10);
                    break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            UpdateVictim();
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_START_ANIM:
                    {
                        me->GetMotionMaster()->MovePath(WAYPOINTS_UP, false);
                        break;
                    }
                    case EVENT_WAIT_ON_PLAYER:
                    {
                        if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                            if (abs(player->GetPositionZ() - me->GetPositionZ()) < 0.1f && player->GetDistance2d(me) < 5.0f && !_playerArrived)
                            {
                                _events.ScheduleEvent(EVENT_TALK_TO_PLAYER, 1000);
                                _playerArrived = true;
                            }
                            else
                                _events.ScheduleEvent(EVENT_WAIT_ON_PLAYER, 1000);
                        break;
                    }
                    case EVENT_TALK_TO_PLAYER:
                    {
                        Talk(1);
                        _events.ScheduleEvent(EVENT_HIDE, 3000);
                        _events.ScheduleEvent(EVENT_SET_FACE_TO_BLOODFANG, 5000);
                        break;
                    }
                    case EVENT_HIDE:
                    {
                        me->GetMotionMaster()->MovePoint(MOVEPOINT_HIDDEN_PLACE, 1313.515f, 1212.22f, 58.4988f);
                        me->CastSpell(me, SPELL_STEALTH);
                        break;
                    }
                    case EVENT_SET_FACE_TO_BLOODFANG:
                    {
                        if (!_bloodfangGUID)
                            if (Creature* ivar = me->FindNearestCreature(NPC_PACKLEADER_IVAR_BLOODFANG, 25.0f))
                                _bloodfangGUID = ivar->GetGUID();

                        if (Creature* ivar = ObjectAccessor::GetCreature(*me, _bloodfangGUID))
                            me->SetFacingToObject(ivar);

                        _events.ScheduleEvent(EVENT_SET_FACE_TO_BLOODFANG, 1000);
                        break;
                    }
                    case EVENT_RANE_LAST_MOVE:
                    {
                        me->MonsterMoveWithSpeed(1299.025f, 1206.724f, 59.64236f, 5.0f);
                        _events.ScheduleEvent(EVENT_RANE_LAST_MOVE + 1, 1000);
                        break;
                    }
                    case EVENT_RANE_LAST_MOVE + 1:
                    {
                        me->SetDisableGravity(false);
                        me->AddAura(SPELL_PERMANENT_FEIGN_DEATH, me);
                        me->DespawnOrUnsummon(60000);
                        break;
                    }
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
        private:
            EventMap _events;
            ObjectGuid _playerGUID;
            ObjectGuid _bloodfangGUID;
            bool _playerArrived;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_deathstalker_rane_yorick_AI(creature);
    }
};

// npc armoire 44893 for quest 27045
class npc_armoire : public CreatureScript
{
public:
    npc_armoire() : CreatureScript("npc_armoire") { }

    enum eNPC
    {
        NPC_RANE_YORICK = 44882,
        NPC_LORD_DARIUS_CROWLEY = 44883,
        NPC_PACKLEADER_IVAR_BLOODFANG = 44884,
        PLAYER_GUID = 99999,
        MOVEPATH_DARIUS = 4488301,
        MOVEPATH_IVAR = 4488401,
        QUEST_WAITING_TO_EXSANGUINATE = 27045,
        SPELL_STEALTH = 34189,
        SPELL_PERMANENT_FEIGN_DEATH = 29266,
        SPELL_EJECT_PASSENGER_1 = 80743,
        SPELL_SUMMON_CROWLEY = 83752,
        SPELL_SUMMON_BLOODFANG = 83753,
        SPELL_SUMMON_CROWLEY_BLOODFANG_MASTER = 83762, // for spell effect 160 is no handler written in core
        SPELL_ARMOIRE_CAMERA_A = 83763,
        SPELL_ARMOIRE_CAMERA_B = 83764,
        SPELL_ARMOIRE_CAMERA_C = 83768,
        SPELL_ARMOIRE_CAMERA_D = 83769,
        SPELL_CONVERSATION_TRIGGER_01A = 83773,
        SPELL_CONVERSATION_TRIGGER_01B = 83774,
        SPELL_CONVERSATION_TRIGGER_01C = 83782,
        SPELL_CONVERSATION_TRIGGER_02A = 83775,
        SPELL_CONVERSATION_TRIGGER_02B = 83777,
        SPELL_CONVERSATION_TRIGGER_02C = 83779,
        SPELL_CONVERSATION_TRIGGER_02D = 83955,
        SPELL_CONVERSATION_TRIGGER_03 = 83787,
        SPELL_CONVERSATION_TRIGGER_04 = 83784,
        SPELL_REVERSE_RIDE_VEHICLE = 83781,
        SPELL_KILL_CREDIT_YORICK = 83786,
        SPELL_HIDE_IN_ARMOIRE = 83788,
        SPELL_DESPAWN_ALL = 83770,
        ACTION_MOVE_TO_RANA = 500,
        ACTION_RANE_JUMP_DEATH = 2,
        EVENT_START_ANIMATION = 101,
        EVENT_CAMERA_STEP = 200,
        EVENT_TEXT_STEP = 300,
    };

    struct npc_armoire_AI : public VehicleAI
    {
        npc_armoire_AI(Creature* creature) : VehicleAI(creature)
        {
            Initialize();
        }

        void Initialize()
        {
            m_playerGUID = ObjectGuid::Empty;
            m_raneGUID = ObjectGuid::Empty;
            m_crowleyGUID = ObjectGuid::Empty;
            m_bloodfangGUID = ObjectGuid::Empty;
            m_events.Reset();
        }

        void IsSummonedBy(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
                if (player->GetQuestStatus(QUEST_WAITING_TO_EXSANGUINATE) == QUEST_STATUS_INCOMPLETE)
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        m_playerGUID = player->GetGUID();
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        {
            if (apply)
            {
                if (Player* player = passenger->ToPlayer())
                    if (player->GetQuestStatus(QUEST_WAITING_TO_EXSANGUINATE) == QUEST_STATUS_INCOMPLETE)
                    {
                        m_playerGUID = player->GetGUID();
                        m_events.ScheduleEvent(EVENT_START_ANIMATION, 2000);
                        return;
                    }
            }
            else
            {
                if (Creature* darius = ObjectAccessor::GetCreature(*me, m_crowleyGUID))
                    darius->DespawnOrUnsummon(1000);
                if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                    ivar->DespawnOrUnsummon(1000);
                if (Creature* rane = ObjectAccessor::GetCreature(*me, m_raneGUID))
                    rane->DespawnOrUnsummon(1000);
                me->DespawnOrUnsummon(1000);
            }

            m_playerGUID = ObjectGuid::Empty;
        }

        void SetGUID(ObjectGuid guid, int32 id)
        {
            switch (id)
            {
            case PLAYER_GUID:
                m_playerGUID = guid;
                break;
            case NPC_LORD_DARIUS_CROWLEY:
                m_crowleyGUID = guid;
                break;
            case NPC_PACKLEADER_IVAR_BLOODFANG:
                m_bloodfangGUID = guid;
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_ANIMATION:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->CastSpell(player, SPELL_SUMMON_CROWLEY_BLOODFANG_MASTER, true);
                        m_events.ScheduleEvent(EVENT_START_ANIMATION + 1, 2000);
                        m_events.ScheduleEvent(EVENT_CAMERA_STEP + 1, 4000);
                    }
                    break;
                }
                case EVENT_START_ANIMATION + 1:
                {
                    if (Creature* darius = ObjectAccessor::GetCreature(*me, m_crowleyGUID))
                        darius->GetMotionMaster()->MovePath(MOVEPATH_DARIUS, false);
                    if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                        ivar->GetMotionMaster()->MovePath(MOVEPATH_IVAR, false);
                    if (Creature* rane = me->FindNearestCreature(NPC_RANE_YORICK, 15.0f))
                        m_raneGUID = rane->GetGUID();
                    break;
                }
                case EVENT_CAMERA_STEP + 1:
                {
                    if (Creature* rane = ObjectAccessor::GetCreature(*me, m_raneGUID))
                        me->CastSpell(rane->GetPositionX(), rane->GetPositionY(), rane->GetPositionZ(), SPELL_CONVERSATION_TRIGGER_02D, true);
                    if (Creature* darius = ObjectAccessor::GetCreature(*me, m_crowleyGUID))
                        darius->SetOrientation(3.1577f);

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 2, 16250);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 1, 11500);
                    break;
                }
                case EVENT_CAMERA_STEP + 2:
                {
                    if (Creature* darius = ObjectAccessor::GetCreature(*me, m_crowleyGUID))
                        if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                            darius->CastSpell(ivar->GetPositionX(), ivar->GetPositionY(), ivar->GetPositionZ(), SPELL_CONVERSATION_TRIGGER_01A, true);

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 3, 12000);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 2, 3700);
                    break;
                }
                case EVENT_CAMERA_STEP + 3:
                {
                    if (Creature* darius = ObjectAccessor::GetCreature(*me, m_crowleyGUID))
                        if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                            ivar->CastSpell(darius->GetPositionX(), darius->GetPositionY(), darius->GetPositionZ(), SPELL_CONVERSATION_TRIGGER_01B, true);

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 4, 19250);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 3, 3700);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 4, 12000);
                    break;
                }
                case EVENT_CAMERA_STEP + 4:
                {
                    if (Creature* darius = ObjectAccessor::GetCreature(*me, m_crowleyGUID))
                        if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                            darius->CastSpell(ivar->GetPositionX(), ivar->GetPositionY(), ivar->GetPositionZ(), SPELL_CONVERSATION_TRIGGER_02A, true);

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 5, 18100);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 5, 3700);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 6, 7300);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 7, 9800);
                    break;
                }
                case EVENT_CAMERA_STEP + 5:
                {
                    if (Creature* darius = ObjectAccessor::GetCreature(*me, m_crowleyGUID))
                        if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                            ivar->CastSpell(darius->GetPositionX(), darius->GetPositionY(), darius->GetPositionZ(), SPELL_CONVERSATION_TRIGGER_02B, true);

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 6, 4800);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 8, 2500);
                    break;
                }
                case EVENT_CAMERA_STEP + 6:
                {
                    if (Creature* darius = ObjectAccessor::GetCreature(*me, m_crowleyGUID))
                        if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                            darius->CastSpell(ivar->GetPositionX(), ivar->GetPositionY(), ivar->GetPositionZ(), SPELL_CONVERSATION_TRIGGER_02C, true);

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 7, 30000);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 9, 3700);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 10, 7300);
                    // m_events.ScheduleEvent(EVENT_TEXT_STEP + 11, 12100);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 12, 12500); // 20500
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 13, 20600); // 26600
                    break;
                }
                case EVENT_CAMERA_STEP + 7:
                {
                    if (Creature* rane = ObjectAccessor::GetCreature(*me, m_raneGUID))
                        if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                        {
                            ivar->CastSpell(rane->GetPositionX(), rane->GetPositionY(), rane->GetPositionZ(), SPELL_CONVERSATION_TRIGGER_01C, true);
                            rane->RemoveAura(SPELL_STEALTH);
                            rane->SetDisableGravity(true);
                            rane->EnterVehicle(ivar, 0);
                        }

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 8, 3600);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 14, 500);
                    break;
                }
                case EVENT_CAMERA_STEP + 8:
                {
                    if (Creature* rane = ObjectAccessor::GetCreature(*me, m_raneGUID))
                        if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                        {
                            rane->CastSpell(ivar->GetPositionX(), ivar->GetPositionY(), ivar->GetPositionZ(), SPELL_CONVERSATION_TRIGGER_04, true);
                            //ivar->CastSpell(ivar, SPELL_EJECT_PASSENGER_1);
                            rane->ExitVehicle(0);
                            rane->GetAI()->DoAction(ACTION_RANE_JUMP_DEATH);
                        }

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 9, 14500);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 15, 1500);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 16, 7400);
                    break;
                }
                case EVENT_CAMERA_STEP + 9:
                {
                    if (Creature* darius = ObjectAccessor::GetCreature(*me, m_crowleyGUID))
                        if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                            ivar->CastSpell(darius->GetPositionX(), darius->GetPositionY(), darius->GetPositionZ(), SPELL_CONVERSATION_TRIGGER_03, true);

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 10, 6000);
                    break;
                }
                case EVENT_CAMERA_STEP + 10:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        if (Creature* darius = ObjectAccessor::GetCreature(*me, m_crowleyGUID))
                            darius->GetAI()->DoAction(ACTION_MOVE_TO_RANA);
                        if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                            ivar->GetAI()->DoAction(ACTION_MOVE_TO_RANA);

                        player->RemoveAura(SPELL_HIDE_IN_ARMOIRE);
                        player->GetMotionMaster()->Clear();
                        //player->GetMotionMaster()->MovePoint(1231, 1313.48f, 1206.09f, 58.5119f);
                    }

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 11, 1000);
                    break;
                }
                case EVENT_CAMERA_STEP + 11:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        if (player->GetQuestStatus(QUEST_WAITING_TO_EXSANGUINATE) == QUEST_STATUS_INCOMPLETE)
                            player->KilledMonsterCredit(44882, ObjectGuid::Empty);
                    me->CastSpell(me, SPELL_DESPAWN_ALL);
                    me->DespawnOrUnsummon(10);
                    break;
                }
                case EVENT_TEXT_STEP + 1:
                    if (Creature* crowley = ObjectAccessor::GetCreature(*me, m_crowleyGUID))
                        crowley->AI()->Talk(0);
                    break;
                case EVENT_TEXT_STEP + 2:
                    if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(0);
                    break;
                case EVENT_TEXT_STEP + 3:
                    if (Creature* crowley = ObjectAccessor::GetCreature(*me, m_crowleyGUID))
                        crowley->AI()->Talk(1);
                    break;
                case EVENT_TEXT_STEP + 4:
                    if (Creature* crowley = ObjectAccessor::GetCreature(*me, m_crowleyGUID))
                        crowley->AI()->Talk(2);
                    break;
                case EVENT_TEXT_STEP + 5:
                    if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(1);
                    break;
                case EVENT_TEXT_STEP + 6:
                    if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(2);
                    break;
                case EVENT_TEXT_STEP + 7:
                    if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(3);
                    break;
                case EVENT_TEXT_STEP + 8:
                    if (Creature* crowley = ObjectAccessor::GetCreature(*me, m_crowleyGUID))
                        crowley->AI()->Talk(3);
                    break;
                case EVENT_TEXT_STEP + 9:
                    if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(4);
                    break;
                case EVENT_TEXT_STEP + 10:
                    if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(5);
                    break;
                /*case EVENT_TEXT_STEP + 11:
                    if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(6);
                    break;*/
                case EVENT_TEXT_STEP + 12:
                    if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(6);
                    break;
                case EVENT_TEXT_STEP + 13:
                    if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(7);
                    break;
                case EVENT_TEXT_STEP + 14:
                    if (Creature* rane = ObjectAccessor::GetCreature(*me, m_raneGUID))
                        rane->AI()->Talk(2);
                    break;
                case EVENT_TEXT_STEP + 15:
                    if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(8);
                    break;
                case EVENT_TEXT_STEP + 16:
                    if (Creature* ivar = ObjectAccessor::GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(9);
                    break;
                }
            }
            // no melee attack
        }

        private:
            EventMap m_events;
            ObjectGuid m_playerGUID;
            ObjectGuid m_raneGUID;
            ObjectGuid m_crowleyGUID;
            ObjectGuid m_bloodfangGUID;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_armoire_AI(creature);
    }
};

// npc armoire 44894 for quest 27045
class npc_armoire_next : public CreatureScript
{
public:
    npc_armoire_next() : CreatureScript("npc_armoire_next") { }

    enum eNPC
    {
        NPC_DEATHSTALKER_RANE_YORICK = 44882,
        QUEST_WAITING_TO_EXSANGUINATE = 27045,
        SPELL_HIDE_IN_ARMOIRE = 83788,
        SPELL_SUMMON_HIDING_SPOT = 83756,
    };

    struct npc_armoire_next_AI : public ScriptedAI
    {
        npc_armoire_next_AI(Creature* creature) : ScriptedAI(creature) { }

        void OnSpellClick(Unit* clicker, bool& result) override
        {
            if (Player* player = clicker->ToPlayer())
                if (player->GetQuestStatus(QUEST_WAITING_TO_EXSANGUINATE) == QUEST_STATUS_INCOMPLETE)
                    if (Creature* rane = me->FindNearestCreature(NPC_DEATHSTALKER_RANE_YORICK, 5.0f))
                    {
                        player->CastSpell(me, SPELL_HIDE_IN_ARMOIRE, true);
                        player->CastSpell(1314.91f, 1211.39f, 58.49675f, SPELL_SUMMON_HIDING_SPOT, true);
                        return;
                    }

            result = false;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_armoire_next_AI(creature);
    }
};

// npc 44883 Lord Darius Crowley for quest 27045 "Waiting to Exsanguinate"
class npc_lord_darius_crowley : public CreatureScript
{
public:
    npc_lord_darius_crowley() : CreatureScript("npc_lord_darius_crowley") { }

    enum eNPC
    {
        NPC_ARMOIRE = 44893,
        NPC_PACKLEADER_IVAR_BLOODFANG = 44884,
        EVENTS_TURN_FACE,
        ACTION_MOVE_TO_RANA = 500,
    };

    struct npc_lord_darius_crowley_AI : public ScriptedAI
    {
        npc_lord_darius_crowley_AI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
        }

        void Initialize()
        {   
            _playerGUID = ObjectGuid::Empty;
            _armoireGUID = ObjectGuid::Empty;
            _bloodfangGUID = ObjectGuid::Empty;
            _events.Reset();
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
                _playerGUID = player->GetGUID();

            FindAllGuid();
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            FindAllGuid();
            if (type == WAYPOINT_MOTION_TYPE)
                if (id == 5)
                    _events.ScheduleEvent(EVENTS_TURN_FACE, 250);

            if (type == POINT_MOTION_TYPE && id == 1230)
                me->DespawnOrUnsummon(1000);
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
                case ACTION_MOVE_TO_RANA:
                {
                    me->SetSpeed(MOVE_WALK, 1.0f);
                    me->GetMotionMaster()->MovePoint(1230, 1299.025f, 1206.724f, 59.64236f);
                    break;
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENTS_TURN_FACE:
                    {
                        if (Creature* ivar = ObjectAccessor::GetCreature(*me, _bloodfangGUID))
                            me->SetFacingToObject(ivar);
                        break;
                    }
                }
            }
            // no melee attack
        }

        void FindAllGuid()
        {
            if (!_bloodfangGUID)
                if (Creature* ivar = me->FindNearestCreature(NPC_PACKLEADER_IVAR_BLOODFANG, 30.0f))
                    _bloodfangGUID = ivar->GetGUID();

            if (!_armoireGUID)
                if (Creature* armoire = me->FindNearestCreature(NPC_ARMOIRE, 30.0f))
                {
                    _armoireGUID = armoire->GetGUID();
                    armoire->GetAI()->SetGUID(me->GetGUID(), me->GetEntry());
                }
        }
    private:
        EventMap _events;
        ObjectGuid _playerGUID;
        ObjectGuid _armoireGUID;
        ObjectGuid _bloodfangGUID;

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lord_darius_crowley_AI(creature);
    }
};

// npc 44884 Packleader Ivar Bloodfang for quest 27045 "Waiting to Exsanguinate"
class npc_packleader_ivar_bloodfang : public CreatureScript
{
public:
    npc_packleader_ivar_bloodfang() : CreatureScript("npc_packleader_ivar_bloodfang") { }

    enum eNPC
    {
        NPC_ARMOIRE = 44893,
        ACTION_MOVE_TO_RANA = 500,
    };

    struct npc_packleader_ivar_bloodfang_AI : public ScriptedAI
    {
        npc_packleader_ivar_bloodfang_AI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
        }

        void Initialize()
        {
            _playerGUID = ObjectGuid::Empty;
            _armoireGUID = ObjectGuid::Empty;
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void IsSummonedBy(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
                _playerGUID = player->GetGUID();
            if (Creature* armoire = me->FindNearestCreature(NPC_ARMOIRE, 30.0f))
            {
                _armoireGUID = armoire->GetGUID();
                armoire->GetAI()->SetGUID(me->GetGUID(), me->GetEntry());
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == POINT_MOTION_TYPE && id == 1230)
                me->DespawnOrUnsummon(1000);
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
                case ACTION_MOVE_TO_RANA:
                {
                    me->SetSpeed(MOVE_WALK, 1.0f);
                    me->GetMotionMaster()->MovePoint(1230, 1299.025f, 1206.724f, 59.64236f);
                    break;
                }
            }
        }
    private:
        EventMap _events;
        ObjectGuid _playerGUID;
        ObjectGuid _armoireGUID;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_packleader_ivar_bloodfang_AI(creature);
    }
};

// npc 44365 Lady Sylvanas Windrunner for quests 27065, 27096, 27097, 27099
class npc_44365_lady_sylvanas_windrunner : public CreatureScript
{
public:
    npc_44365_lady_sylvanas_windrunner() : CreatureScript("npc_44365_lady_sylvanas_windrunner") { }

    enum eNPC
    {
        QUEST_THE_WARCHIEFS_FLEET_27065 = 27065,
        QUEST_ORCS_ARE_IN_ORDER = 27096,
        QUEST_RISE_FORSAKEN = 27097,
        QUEST_NO_ESCAPE = 27099,
        SPELL_SUMMON_AGATHA = 83982,
        SPELL_SEE_QUEST_INVIS_5 = 84241,
        SPELL_DEATH_WALK = 85451,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_THE_WARCHIEFS_FLEET_27065)
            player->AddAura(SPELL_SEE_QUEST_INVIS_5, player);
        else if (quest->GetQuestId() == QUEST_RISE_FORSAKEN)
            player->CastSpell(1380.69f, 1037.616f, 53.046f, SPELL_SUMMON_AGATHA, true);
        else if (quest->GetQuestId() == QUEST_NO_ESCAPE)
            player->CastSpell(1380.69f, 1037.616f, 53.046f, SPELL_SUMMON_AGATHA, true);
        return false;
    }

    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/) override
    {
        if (quest->GetQuestId() == QUEST_ORCS_ARE_IN_ORDER)
            player->RemoveAura(SPELL_SEE_QUEST_INVIS_5);
        if (quest->GetQuestId() == QUEST_RISE_FORSAKEN)
            player->RemoveAura(SPELL_DEATH_WALK);
        if (quest->GetQuestId() == QUEST_NO_ESCAPE)
            player->RemoveAura(SPELL_DEATH_WALK);
        return false;
    }
};

// npc 44914 Orc Sea Pup for the quest 27069 "Steel Thunder"
class npc_orc_sea_pup : public CreatureScript
{
public:
    npc_orc_sea_pup() : CreatureScript("npc_orc_sea_pup") { }

    enum eNPC
    {
        QUEST_STEEL_THUNDER = 27069,
        NPC_ORC_CRATE = 44915,
        SPELL_SUMMON_ORC_CRATE = 83835,
        SPELL_PICK_UP_ORC_CRATE = 83838,
        SPELL_DESPAWN_ALL = 83840,
        SPELL_CREDIT = 83843,
        EVENT_TALK_TO_PLAYER = 100,
        EVENT_CHECK_PLAYER_ALIVE,
    };

    struct npc_orc_sea_pup_AI : public VehicleAI
    {
        npc_orc_sea_pup_AI(Creature* creature) : VehicleAI(creature)
        {
            Initialize();
        }

        void Initialize()
        {
            _playerGUID = ObjectGuid::Empty;
            _IsFull = false;
        }

        void Reset() override
        {
            _playerGUID = ObjectGuid::Empty;
            _IsFull = false;
            _events.Reset();
        }

        void IsSummonedBy(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
                if (player->GetQuestStatus(QUEST_STEEL_THUNDER) == QUEST_STATUS_INCOMPLETE)
                {
                    Talk(0);
                    _playerGUID = player->GetGUID();
                    me->GetMotionMaster()->MoveFollow(player, 3.0f, (float)M_PI);
                    _events.ScheduleEvent(EVENT_CHECK_PLAYER_ALIVE, 1000);
                    int c = player->GetReqKillOrCastCurrentCount(QUEST_STEEL_THUNDER, NPC_ORC_CRATE);
                    for (int i = 0; i < c; i++)
                        me->CastSpell(me, SPELL_SUMMON_ORC_CRATE, true);
                }
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        {
            if (passenger->GetEntry() == NPC_ORC_CRATE)
                if (apply)
                {
                    Talk(seatId + 1);
                    if (seatId == 5)
                    {
                        _IsFull = true;
                        _events.ScheduleEvent(EVENT_TALK_TO_PLAYER, 1000);
                    }
                }
                else
                {
                    if (Creature* crate = passenger->ToCreature())
                        crate->DespawnOrUnsummon(6000);
                }
        }

        void JustSummoned(Creature* summon) override
        {
            if (summon->GetEntry() == NPC_ORC_CRATE)
                if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                    summon->EnterVehicle(me, -1);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                if (spell->Id == SPELL_PICK_UP_ORC_CRATE)
                {
                    me->CastSpell(me, SPELL_SUMMON_ORC_CRATE, true);
                    me->CastSpell(player, SPELL_CREDIT);
                }
        }

        void DoAction(int32 param) override
        {
            if (param == 2)
            {
                _events.CancelEvent(EVENT_TALK_TO_PLAYER);
                Talk(6);
                me->GetVehicleKit()->RemoveAllPassengers();
                me->DespawnOrUnsummon(6000);
            }
            else if (param == 3)
                if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                    player->CastSpell(player, SPELL_DESPAWN_ALL);
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TALK_TO_PLAYER:
                    {
                        Talk(7);
                        _events.ScheduleEvent(EVENT_TALK_TO_PLAYER, urand(10000, 20000));
                        break;
                    }
                    case EVENT_CHECK_PLAYER_ALIVE:
                    {
                        if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                            if (player->IsAlive() && player->IsInWorld())
                            {
                                _events.ScheduleEvent(EVENT_CHECK_PLAYER_ALIVE, 1000);
                                break;
                            }

                        me->GetVehicleKit()->RemoveAllPassengers();
                        me->DespawnOrUnsummon(10);
                        break;
                    }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
        private:
            EventMap _events;
            ObjectGuid _playerGUID;
            bool _IsFull;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_orc_sea_pup_AI(creature);
    }
};

// npc 44916 Admiral Hatchet for the quest 27069 "Steel Thunder"
class npc_admiral_hatchet : public CreatureScript
{
public:
    npc_admiral_hatchet() : CreatureScript("npc_admiral_hatchet") { }

    enum eNPC
    {
        QUEST_STEEL_THUNDER = 27069,
        NPC_WARLORD_TOROK = 44917,
        NPC_SEA_PUP = 44914,
        SPELL_SUMMON_SEA_PUP = 83839,
        SPELL_SEA_PUP_TRIGGER = 83865,
        EVENT_CHECK_TALK = 100,
        EVENT_TALK_COOLDOWN = 101,
        EVENT_TALK = 200,
    };

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        if (player->GetQuestStatus(QUEST_STEEL_THUNDER) == QUEST_STATUS_INCOMPLETE)
            if (creature->FindNearestCreature(NPC_SEA_PUP, 10.0f) == 0)
                if (action == 1)
                {
                    player->CastSpell(player, SPELL_SEA_PUP_TRIGGER);
                    CloseGossipMenuFor(player);
                    return true;
                }

        return false;
    }

    bool OnQuestReward(Player* /*player*/, Creature* creature, Quest const* quest, uint32 /*opt*/) override
    {
        if (quest->GetQuestId() == QUEST_STEEL_THUNDER)
            if (Creature* pup = creature->FindNearestCreature(NPC_SEA_PUP, 10.0f))
                pup->GetAI()->DoAction(2);

        return false;
    }

    struct npc_admiral_hatchet_AI : public ScriptedAI
    {
        npc_admiral_hatchet_AI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
        }

        void Initialize()
        {
            _playerGUID = ObjectGuid::Empty;
            _torokGUID = ObjectGuid::Empty;
            _playerNear = false;
        }

        void Reset() override
        {   
            _events.Reset();
            Initialize();
            _events.ScheduleEvent(EVENT_CHECK_TALK, 1000);
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            if (!UpdateVictim())
                return;

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_TALK:
                    {
                        CheckForTorok();
                        if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                            if (player->GetDistance2d(me) < 20.0f && !_playerNear)
                            {
                                _playerGUID = player->GetGUID();
                                _events.ScheduleEvent(EVENT_TALK + 1, 1000);
                                _events.ScheduleEvent(EVENT_TALK_COOLDOWN, 90000);
                                _playerNear = true;
                            }
                            else
                                _events.ScheduleEvent(EVENT_CHECK_TALK, 1000);
                        break;
                    }
                    case EVENT_TALK_COOLDOWN:
                    {
                        Reset();
                        break;
                    }
                    case EVENT_TALK + 1:
                    {
                        Talk(0);
                        _events.ScheduleEvent(EVENT_TALK + 2, 8000);
                        break;
                    }
                    case EVENT_TALK + 2:
                    {
                        if (Creature* torok = ObjectAccessor::GetCreature(*me, _torokGUID))
                            torok->AI()->Talk(0);
                        _events.ScheduleEvent(EVENT_TALK + 3, 6000);
                        break;
                    }
                    case EVENT_TALK + 3:
                    {
                        Talk(1);
                        _events.ScheduleEvent(EVENT_TALK + 4, 6000);
                        break;
                    }
                    case EVENT_TALK + 4:
                    {
                        if (Creature* torok = ObjectAccessor::GetCreature(*me, _torokGUID))
                            torok->AI()->Talk(1);
                        break;
                    }
                }
            }

            DoMeleeAttackIfReady();
        }

        void CheckForTorok()
        {
            if (!_torokGUID)
                if (Creature* torok = me->FindNearestCreature(NPC_WARLORD_TOROK, 30.0f))
                    _torokGUID = torok->GetGUID();
        }

    private:
        EventMap _events;
        ObjectGuid _playerGUID;
        ObjectGuid _torokGUID;
        bool _playerNear;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_admiral_hatchet_AI(creature);
    }
};

// Spell 83865 "Sea Pup Trigger" for the quest 27069
class spell_sea_pup_trigger_83865 : public SpellScriptLoader
{
public:
    spell_sea_pup_trigger_83865() : SpellScriptLoader("spell_sea_pup_trigger_83865") { }

    enum eSpell
    {
        SPELL_SUMMON_SEA_PUP = 83839,
    };

    class IsNotPlayerGuid
    {
    public:
        explicit IsNotPlayerGuid(ObjectGuid guid) : _guid(guid) { }

        bool operator()(WorldObject* obj) const
        {
            if (Player* player = obj->ToPlayer())
                return player->GetGUID() != _guid;

            return true;
        }

    private:
        ObjectGuid _guid;
    };

    class spell_sea_pup_trigger_83865_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sea_pup_trigger_83865_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(IsNotPlayerGuid(GetCaster()->GetGUID()));
        }

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* unit = GetCaster())
                if (Player* player = unit->ToPlayer())
                    player->CastSpell(player, SPELL_SUMMON_SEA_PUP);
        }
        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sea_pup_trigger_83865_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            OnEffectHitTarget += SpellEffectFn(spell_sea_pup_trigger_83865_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_sea_pup_trigger_83865_SpellScript();
    }
};

// Spell 83838 "Pick Up Orc Crate" for the quest 27069
class spell_pick_up_orc_crate_83838 : public SpellScriptLoader
{
public:
    spell_pick_up_orc_crate_83838() : SpellScriptLoader("spell_pick_up_orc_crate_83838") { }

    enum eSpell
    {
        NPC_ORC_SEA_PUP = 44914,
    };

    class IsNotEntry
    {
    public:
        explicit IsNotEntry(uint32 entry) : _entry(entry) { }

        bool operator()(WorldObject* obj) const
        {
            if (Creature* target = obj->ToCreature())
                return target->GetEntry() != _entry;

            return true;
        }

    private:
        uint32 _entry;
    };

    class spell_pick_up_orc_crate_83838_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pick_up_orc_crate_83838_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(IsNotEntry(NPC_ORC_SEA_PUP));
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pick_up_orc_crate_83838_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pick_up_orc_crate_83838_SpellScript();
    }
};

// Orc Sea Dog
class npc_orc_sea_dog : public CreatureScript
{
public:
    npc_orc_sea_dog() : CreatureScript("npc_orc_sea_dog") { }

    enum eNPC
    {
        QUEST_LOST_IN_THE_DARKNESS = 27093,
        NPC_WEBBED_VICTIM = 44941,
        NPC_ORC_SEA_DOG = 44942,
        SPELL_DESPAWN_ALL_SUMMONS = 83935,
        EVENT_CHECK_PLAYER = 100,
    };

    struct npc_orc_sea_dog_AI : public ScriptedAI
    {
        npc_orc_sea_dog_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            _playerGUID = ObjectGuid::Empty;
        }

        void Reset() override
        {
            _events.Reset();
            Initialize();
            me->SetReactState(REACT_PASSIVE);
        }

        void IsSummonedBy(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
            {
                _playerGUID = player->GetGUID();
                me->GetMotionMaster()->MoveFollow(player, 4.0f, frand(1.57f, 4.71f));
                _events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            if (!UpdateVictim())
                return;

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_PLAYER:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                        if (player->IsAlive() && player->IsInWorld() && !player->IsQuestRewarded(QUEST_LOST_IN_THE_DARKNESS))
                        {
                            _events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                            break;
                        }

                    me->DespawnOrUnsummon(10);
                    break;
                }
                }
            }
            DoMeleeAttackIfReady();
        }

    private:
        EventMap _events;
        ObjectGuid _playerGUID;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_orc_sea_dog_AI(creature);
    }
};

// Webbed Victim
class npc_webbed_victim_skitterweb : public CreatureScript
{
public:
    npc_webbed_victim_skitterweb() : CreatureScript("npc_webbed_victim_skitterweb") { }

    enum eNPC
    {
        QUEST_LOST_IN_THE_DARKNESS = 27093,
        NPC_ORC_SEA_DOG = 44942,
        SPELL_FREE_WEBBED_VICTIM1 = 83919,
        SPELL_FREE_WEBBED_VICTIM2 = 83921,
        SPELL_FREE_WEBBED_VICTIM3 = 83927,
    };

    struct npc_webbed_victim_skitterweb_AI : public ScriptedAI
    {
        npc_webbed_victim_skitterweb_AI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
        }

        void Initialize()
        {
            _playerGUID = ObjectGuid::Empty;
        }

        void Reset() override
        {
            Initialize();
        }

        void JustDied(Unit* killer) override
        {
            if (Player* player = killer->ToPlayer())
                if (player->GetQuestStatus(QUEST_LOST_IN_THE_DARKNESS) == QUEST_STATUS_INCOMPLETE)
                {
                    _playerGUID = player->GetGUID();
                    player->CastSpell(me, SPELL_FREE_WEBBED_VICTIM3, true);
                    player->KilledMonsterCredit(NPC_ORC_SEA_DOG, ObjectGuid::Empty);
                }
        }

    private:
        ObjectGuid _playerGUID;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_webbed_victim_skitterweb_AI(creature);
    }
};

/*######
## AddSC
######*/
void AddSC_silverpine_forest()
{
    new npc_deathstalker_erland();
    new npc_grand_executor_mortuus();
    new spell_raise_forsaken();
    new spell_forsaken_trooper_master_script();
    new npc_fallen_human();
    new npc_bat_handler_maggotbreath();
    new npc_forsaken_bat();
    new go_abandoned_outhouse();
    new npc_deathstalker_rane_yorick();
    new npc_armoire();
    new npc_armoire_next();
    new npc_lord_darius_crowley();
    new npc_packleader_ivar_bloodfang();
    new npc_44365_lady_sylvanas_windrunner();
    new npc_orc_sea_pup();
    new npc_admiral_hatchet();
    new spell_sea_pup_trigger_83865();
    new spell_pick_up_orc_crate_83838();
    new npc_orc_sea_dog();
    new npc_webbed_victim_skitterweb();
}
