/*
 * Copyright (C) 2017-2018 5CentsCore <https://github.com/AshamaneProject>
 * Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>
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

#include "ScriptMgr.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "CombatAI.h"
#include "GridNotifiersImpl.h"

enum
{
    NPC_KORVAS_BLOODTHORN_99343 = 99343,

    ///DH Quest
    QUEST_CALL_OF_THE_ILLIDARI_39261 = 39261,
    QUEST_CALL_OF_THE_ILLIDARI_39047 = 39047,
};

struct npc_korvas_bloodthorn_99343 : public ScriptedAI
{
    npc_korvas_bloodthorn_99343(Creature* creature) : ScriptedAI(creature) { SayHi = false; }

    void MoveInLineOfSight(Unit* who) override
    {
        if (!who || !who->IsInWorld())
            return;
        if (!me->IsWithinDist(who, 25.0f, false))
            return;

        Player* player = who->GetCharmerOrOwnerPlayerOrPlayerItself();

        if (!player)
            return;
        me->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, me->GetFollowAngle());
        if (!SayHi)
        {
            SayHi = true;
            Talk(0, player);
        }
    }

    void sQuestAccept(Player* player, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_CALL_OF_THE_ILLIDARI_39261 || quest->GetQuestId() == QUEST_CALL_OF_THE_ILLIDARI_39047)
        {
            Talk(1, player);
            me->DespawnOrUnsummon(5000);
        }
    }
private:
    bool SayHi;
};

class go_mardum_control_console : public GameObjectScript
{
public:
    go_mardum_control_console() : GameObjectScript("go_mardum_control_console") { }

    enum eCage {
        NPC_ALTRUIS = 95237,
        NPC_KAYN = 95240,
        DATA_ACTION_START = 56,
        QUEST_UNBRIDLED_POWER_ALTRUIS = 41060,
        QUEST_UNBRIDLED_POWER_KAYN = 41037,
        SPELL_ACTIVATING_CONTROL_CONSOLE = 216679,
    };

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->SetGoState(GO_STATE_READY);
        if (player->GetQuestStatus(QUEST_UNBRIDLED_POWER_ALTRUIS) == QUEST_STATUS_INCOMPLETE) {
            player->CastSpell(go, SPELL_ACTIVATING_CONTROL_CONSOLE, false);
            if (Creature* creature = go->FindNearestCreature(NPC_ALTRUIS, 25.0f, true)) {
                if (TempSummon* waypointAltruis = player->SummonCreature(creature->GetEntry(), creature->GetPosition(), TEMPSUMMON_MANUAL_DESPAWN, 0, 0, true))
                {
                    waypointAltruis->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    waypointAltruis->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VENDOR);
                    waypointAltruis->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    waypointAltruis->AI()->SetData(DATA_ACTION_START, DATA_ACTION_START);
                    creature->ForcedDespawn(1000, Seconds(15));
                }
                go->ResetDoorOrButton();
                return true;
            }
        }
        if (player->GetQuestStatus(QUEST_UNBRIDLED_POWER_KAYN) == QUEST_STATUS_INCOMPLETE) {
            player->CastSpell(go, SPELL_ACTIVATING_CONTROL_CONSOLE, false);
            if (Creature* creature = go->FindNearestCreature(NPC_KAYN, 25.0f, true)) {
                if (TempSummon* waypointKayn = player->SummonCreature(creature->GetEntry(), creature->GetPosition(), TEMPSUMMON_MANUAL_DESPAWN, 0, 0, true))
                {
                    waypointKayn->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    waypointKayn->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VENDOR);
                    waypointKayn->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    waypointKayn->AI()->SetData(DATA_ACTION_START, DATA_ACTION_START);
                    creature->ForcedDespawn(1000, Seconds(15));
                }
                go->ResetDoorOrButton();
                return true;
            }
        }
        return true;
    }
};

class npc_mardum_altruis_ch : public CreatureScript
{
public:
    npc_mardum_altruis_ch() : CreatureScript("npc_mardum_altruis_ch") { }

    enum {
        TEXT_1 = 0, // Whenever you\'re ready.
        TEXT_2 = 1, // This way.Your forces await.
        TEXT_3 = 2, // The Fel Hammer is ours at last. Gaze upon the might of the Twinblades of the Deceiver!
        TEXT_4 = 3, // We will follow our champion into battle, and we will strike down the Legion once and for all!
        TEXT_5 = 4, // Glory to the Illidari!
        EVENT_START_MOVE = 1,
        EVENT_SAY_1 = 3,
        EVENT_SAY_ASHTONGUE = 4,
        EVENT_SAY_COILSKAR = 5,
        EVENT_SAY_SHIVARRA = 6,
        EVENT_SAY_3 = 7,
        EVENT_SAY_4 = 8,
        EVENT_DESPAWN = 9,
        NPC_KILLCREDIT = 102921,
        SPELL_ASSUMING_CONTROL = 203459,
        QUEST_UNBRIDLED_POWER = 41060,
        NPC_GAARDOUN = 98650,
        NPC_LADY_STHENO = 98624,
        NPC_MOTHER_MALEVOLENCE = 98632,
        DATA_START_ANIM = 56,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_UNBRIDLED_POWER)
            creature->AI()->Talk(TEXT_1);

        return true;
    }

    struct npc_mardum_altruis_ch_AI : public ScriptedAI
    {
        npc_mardum_altruis_ch_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Reset() override
        {
            _events.Reset();
        }

        void Initialize() {}

        void UpdateAI(uint32 diff) override
        {
            UpdateVictim();
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_MOVE:
                    _events.ScheduleEvent(EVENT_START_MOVE + 1, 2500);
                    me->SetWalk(true);
                    me->GetMotionMaster()->MoveJump(1538.26f, 1417.64f, 237.1087f, 5.8971f, 10.0f, 0.0f);
                    break;
                case EVENT_START_MOVE + 1:
                    _events.ScheduleEvent(EVENT_SAY_1, 7000);
                    me->GetMotionMaster()->MovePoint(1, 1551.416f, 1414.738f, 237.1089f);
                    break;
                case EVENT_SAY_1:
                    _events.ScheduleEvent(EVENT_SAY_ASHTONGUE, 8000);
                    Talk(TEXT_3);
                    break;
                case EVENT_SAY_ASHTONGUE:
                    _events.ScheduleEvent(EVENT_SAY_COILSKAR, 5000);
                    if (Creature* gaardoun = me->FindNearestCreature(NPC_GAARDOUN, me->GetVisibilityRange(), true))
                        gaardoun->AI()->Talk(0);
                    break;
                case EVENT_SAY_COILSKAR:
                    _events.ScheduleEvent(EVENT_SAY_SHIVARRA, 5000);
                    if (Creature* ladyStheno = me->FindNearestCreature(NPC_LADY_STHENO, me->GetVisibilityRange(), true))
                        ladyStheno->AI()->Talk(0);
                    break;
                case EVENT_SAY_SHIVARRA:
                    _events.ScheduleEvent(EVENT_SAY_3, 5000);
                    if (Creature* motherMalevolence = me->FindNearestCreature(NPC_MOTHER_MALEVOLENCE, me->GetVisibilityRange(), true))
                        motherMalevolence->AI()->Talk(0);
                    break;
                case EVENT_SAY_3:
                    _events.ScheduleEvent(EVENT_SAY_4, 7000);
                    Talk(TEXT_4);
                    break;
                case EVENT_SAY_4:
                    _events.ScheduleEvent(EVENT_DESPAWN, 1000);
                    Talk(TEXT_5);
                    break;
                case EVENT_DESPAWN: {
                    std::list<Player*> players;
                    me->GetPlayerListInGrid(players, 50.0f);
                    for (Player* player : players) {
                        if (player->GetQuestStatus(QUEST_UNBRIDLED_POWER) == QUEST_STATUS_INCOMPLETE)
                            player->CastSpell(player, SPELL_ASSUMING_CONTROL, true);
                    }
                    me->DespawnOrUnsummon();
                    break;
                }   
                default:
                    break;
                }
            }
            // no melee attacks
        }

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id) {
            case DATA_START_ANIM:
                Talk(TEXT_2);
                _events.ScheduleEvent(EVENT_START_MOVE, 7000);
                break;
            default:
                break;
            }
        }

    private:
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_mardum_altruis_ch_AI(creature);
    }
};

// npc 98650, 103025 for the quest 41070 'Spoils of Victory'
class npc_mardum_battlelord_gaardoun : public CreatureScript {
public:
    npc_mardum_battlelord_gaardoun() : CreatureScript("npc_mardum_battlelord_gaardoun") { }

    enum eGaardoun {
        QUEST_SPOILS_OF_VICTORY = 41070,
        FOLLOW_GAARDOUN_KILLCREDIT = 103047,
        PHASE_NONE = 0,
        PHASE_CONTINUE = -1,
        DATA_EVENT_STARTER_GUID = 0,
        SAY_KHADGAR_1 = 3,
        SAY_KHADGAR_2 = 4,
        SAY_KHADGAR_3 = 5,
        SAY_KHADGAR_4 = 6,
        WP_START = 1,
        WP_START_TALK = 1,
        WP_NEXT_TALK = 10,
        WP_LAST_TALK = 17,
    };

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 /*action*/) override
    {
        if (player->GetQuestStatus(QUEST_SPOILS_OF_VICTORY) == QUEST_STATUS_INCOMPLETE)
        {
            if (TempSummon* waypointGaardoun = player->SummonCreature(creature->GetEntry(), creature->GetPosition(), TEMPSUMMON_MANUAL_DESPAWN, 0, 0, true))
            {
                waypointGaardoun->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                waypointGaardoun->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VENDOR);
                waypointGaardoun->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                waypointGaardoun->AI()->Talk(1);
                waypointGaardoun->AI()->SetGUID(player->GetGUID());
                player->KilledMonsterCredit(98650, ObjectGuid::Empty);
            }
        }

        return true;
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override {
        if (quest->GetQuestId() == 41064) {
            player->ForceCompleteQuest(41064);
        }
        return true;
    }

    struct npc_mardum_battlelord_gaardoun_AI : public npc_escortAI
    {
        npc_mardum_battlelord_gaardoun_AI(Creature* creature) : npc_escortAI(creature)
        {
            Initialize();
        }

        void Initialize()
        {
            _phase = PHASE_NONE;
            _moveTimer = 0;
        }

        ObjectGuid GetGUID(int32 type) const override
        {
            if (type == DATA_EVENT_STARTER_GUID)
                return _eventStarterGuid;

            return ObjectGuid::Empty;
        }

        void SetGUID(ObjectGuid guid, int32 /*id*/) override
        {
            _eventStarterGuid = guid;
            Start(false, true, guid);
            SetDespawnAtFar(false);
        }

        void LastWaypointReached() override
        {
            me->DespawnOrUnsummon();
            me->SetOrientation(2.990351f);

            if (Player* player = ObjectAccessor::FindPlayer(_eventStarterGuid))
                player->KilledMonsterCredit(FOLLOW_GAARDOUN_KILLCREDIT, ObjectGuid::Empty);
        }

        void Reset() override
        {
            me->SetWalk(false);
            me->SetSpeed(MOVE_RUN, 3.2f);
            Initialize();
            _events.Reset();
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            if (UpdateVictim())
            {
                DoMeleeAttackIfReady();
            }

            if (HasEscortState(STATE_ESCORT_NONE))
                return;

            npc_escortAI::UpdateAI(diff);

            if (_phase)
            {
                if (_moveTimer <= diff)
                {
                    switch (_phase)
                    {
                    case PHASE_CONTINUE:
                        SetEscortPaused(false);
                        _moveTimer = 0 * IN_MILLISECONDS;
                        _phase = PHASE_NONE;
                        break;
                    default:
                        break;
                    }
                }
                else if (!me->IsInCombat())
                    _moveTimer -= diff;
            }
        }

        void WaypointReached(uint32 waypointId) override
        {
            Player* player = GetPlayerForEscort();
            if (!player)
                return;

            switch (waypointId)
            {
            case WP_START_TALK:
                Talk(2);
                break;
            case WP_NEXT_TALK:
                Talk(3);
                break;
            case WP_LAST_TALK:
                Talk(4);
                break;
            default:
                break;
            }
        }

    private:
        int8 _phase;
        uint32 _moveTimer;
        ObjectGuid _eventStarterGuid;
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_mardum_battlelord_gaardoun_AI(creature);
    }
};

/*********/
/* AddSC */
/*********/
void AddSC_class_hall_dh()
{
    RegisterCreatureAI(npc_korvas_bloodthorn_99343);
    new go_mardum_control_console();
    new npc_mardum_altruis_ch();
    new npc_mardum_battlelord_gaardoun();
}
