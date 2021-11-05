/*
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
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

#include "Log.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "PhasingHandler.h"
#include "Conversation.h"

class play_fate_of_the_horde : public PlayerScript
{
public:
    play_fate_of_the_horde() : PlayerScript("play_fate_of_the_horde") { }
    enum
    {
        MOVIE_FATE_OF_THE_HORDE = 474,
        SPELL_TELE_TO_DUROTAR_FUNERAL = 200282,
        SPELL_LEARN_FATE_OF_THE_HORDE = 198893,
    };

    void OnMovieComplete(Player* player, uint32 movieId)
    {
        if (movieId == MOVIE_FATE_OF_THE_HORDE)
        {
            player->CastSpell(player, SPELL_LEARN_FATE_OF_THE_HORDE, true);
            player->CastSpell(player, SPELL_TELE_TO_DUROTAR_FUNERAL, true);
            if (player->GetPhaseShift().HasPhase(1178)) {
                PhasingHandler::RemovePhase(player, 1178);
            }
            PhasingHandler::AddPhase(player, 1180, true);
        }
            
    }
};

enum eQuest {
    QUEST_ILLIDARI_LEAVING_H = 39690,
    QUEST_AUDIENCE_WITH_WARCHIEF = 40976,
    QUEST_WEAPON_OF_THE_HORDE = 41002,
    QUEST_BLINK_OF_AN_EYE = 44663,
    PHASE_ORGRIMMAR_WARCHIEF = 1178,
    SPELL_SUMMON_KHADGAR = 230064,
    CONVERSATION_KHADGAR_BLINK_OF_EYE = 3827,
};

//class PlayerScript_summon_khadgar : public PlayerScript
//{
//public:
//    PlayerScript_summon_khadgar() : PlayerScript("PlayerScript_summon_khadgar") {}
//
//    uint32 checkTimer = 1000;
//    bool _khadgarSummoned = false;
//
//    void OnUpdate(Player* player, uint32 diff) override
//    {
//        if (checkTimer <= diff)
//        {
//            if (player->getClass() == CLASS_DEMON_HUNTER &&
//                (player->GetAreaId() == 1637 || 5170 || 5356) &&
//                player->GetQuestStatus(QUEST_ILLIDARI_LEAVING_H) == QUEST_STATUS_REWARDED &&
//                !player->GetPhaseShift().HasPhase(PHASE_ORGRIMMAR_WARCHIEF)) {
//                    PhasingHandler::AddPhase(player, PHASE_ORGRIMMAR_WARCHIEF, true);
//            }
//            checkTimer = 1000;
//        }
//        else checkTimer -= diff;
//    }
//};

class npc_archmage_khadgar : public CreatureScript
{
public:
    npc_archmage_khadgar() : CreatureScript("npc_archmage_khadgar") { }
    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_AUDIENCE_WITH_WARCHIEF)
        {
            creature->CastSpell(creature, 177425, true);
            creature->DespawnOrUnsummon(2000);
        }
        return true;
    }
};

class npc_lord_saurfang : public CreatureScript
{
public:
    npc_lord_saurfang() : CreatureScript("npc_lord_saurfang") { }

    enum {
        TEXT_GREETING = 0,
    };

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_AUDIENCE_WITH_WARCHIEF) == QUEST_STATUS_INCOMPLETE) {
            player->KilledMonsterCredit(100541, ObjectGuid::Empty);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Take me inside Grommash Hold.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        }
        SendGossipMenuFor(player, player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        ClearGossipMenuFor(player);
        switch (action)
        {
        case GOSSIP_ACTION_INFO_DEF + 1:
            player->SendMovieStart(474);
            CloseGossipMenuFor(player);
            break;
        }
        return true;
    }

    struct npc_lord_saurfangAI : public ScriptedAI
    {
        npc_lord_saurfangAI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Reset() override {
            Initialize();
        }

        void Initialize()
        {
            _alreadyGreet = false;
        }

        void MoveInLineOfSight(Unit* unit) override
        {
            if (Player* player = unit->ToPlayer())
                if (player->GetDistance(me) < 15.0f)
                    if (player->HasQuest(QUEST_AUDIENCE_WITH_WARCHIEF) && !_alreadyGreet) {
                        me->AI()->Talk(TEXT_GREETING);
                        _alreadyGreet = true;
                    }
        }

        private:
            bool _alreadyGreet;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lord_saurfangAI(creature);
    }
};

class PlayerScript_summon_khadgar_servant : public PlayerScript
{
public:
    PlayerScript_summon_khadgar_servant() : PlayerScript("PlayerScript_summon_khadgar_servant") {}

    uint32 checkTimer = 1000;
    bool _khadgarServantSummoned = false;

    void OnUpdate(Player* player, uint32 diff) override
    {
        if (checkTimer <= diff)
        {
            if (player->getClass() == CLASS_DEMON_HUNTER &&
                player->GetQuestStatus(QUEST_WEAPON_OF_THE_HORDE) == QUEST_STATUS_REWARDED &&
                player->GetQuestStatus(QUEST_BLINK_OF_AN_EYE) == QUEST_STATUS_NONE && !_khadgarServantSummoned
            ) {
                if (Creature* creature = player->FindNearestCreature(114562, 10.0f)) {
                    creature->DestroyForPlayer(player);
                    _khadgarServantSummoned = false;
                }

                if (TempSummon* personalCreature = player->SummonCreature(114562, player->GetPosition(), TEMPSUMMON_MANUAL_DESPAWN, 0, 0, true))
                {
                    _khadgarServantSummoned = true;
                    float x, y, z;
                    personalCreature->GetClosePoint(x, y, z, personalCreature->GetObjectSize() / 3, 10.0f);
                    personalCreature->GetMotionMaster()->MovePoint(0, x, y, z);
                }
            }
            checkTimer = 1000;
        }
        else checkTimer -= diff;
    }
};

/// Khadgars Upgraded Servant - 114562 (Dalaran quest chain starter)
class npc_khadgars_upgraded_servant : public CreatureScript
{
public:
    npc_khadgars_upgraded_servant() : CreatureScript("npc_khadgars_upgraded_servant") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        switch (quest->GetQuestId())
        {
        case QUEST_BLINK_OF_AN_EYE:
        {
            Conversation::CreateConversation(CONVERSATION_KHADGAR_BLINK_OF_EYE, player, player->GetPosition(), { player->GetGUID() });
            player->PlayerTalkClass->SendCloseGossip();
            creature->DespawnOrUnsummon(5000);
            break;
        }
        default:
            break;
        }

        return false;
    }
};

/* https://www.wowhead.com/quest=31012/joining-the-horde */
enum eQuestHorde {
    QUEST_JOINING_THE_HORDE = 31012,
    NPC_JI = 60570,
};

class quest_joining_the_horde : public QuestScript
{
public:
    quest_joining_the_horde() : QuestScript("quest_joining_the_horde") { }

    void OnQuestStatusChange(Player* player, Quest const* /*quest*/, QuestStatus oldStatus, QuestStatus newStatus) override
    {
        if (newStatus == QUEST_STATUS_NONE || QUEST_STATUS_REWARDED) {
            if (Creature* tempJi = player->GetSummonedCreatureByEntry(NPC_JI))
                tempJi->DespawnOrUnsummon();
        }
    }
};

class npc_orgri_ji_firepaw : public CreatureScript
{
public:
    npc_orgri_ji_firepaw() : CreatureScript("npc_orgri_ji_firepaw") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_JOINING_THE_HORDE) {
            if (TempSummon* followerJi = player->SummonCreature(creature->GetEntry(), creature->GetPosition(), TEMPSUMMON_MANUAL_DESPAWN, 0, 0, true))
            {
                followerJi->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                followerJi->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VENDOR);
                followerJi->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                followerJi->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, float(M_PI));
            }
        }
        return true;
    }

    struct npc_orgri_ji_firepaw_AI : public ScriptedAI
    {
        npc_orgri_ji_firepaw_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize() {
            _playerGuid = ObjectGuid::Empty;
        }

        void Reset() override {
            Initialize();
            _events.Reset();
        }

        void IsSummonedBy(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
                _playerGuid = who->GetGUID();
        }

        void EnterEvadeMode(EvadeReason /*why*/) override {}

        /*void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                default:
                    break;
                }
            }
            // no melee attacks
        }

        void SetData(uint32 id, uint32 value) override
        {
            switch (id)
            {
            default:
                break;
            }
        }*/

    private:
        EventMap _events;
        ObjectGuid _playerGuid;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_orgri_ji_firepaw_AI(creature);
    }
};

class npc_orgri_guard_greet : public CreatureScript {
public:
    npc_orgri_guard_greet() : CreatureScript("npc_orgri_guard_greet") { }

    enum eGuard {
        EVENT_SAY_2 = 1,
        EVENT_RESET = 2,
    };

    struct npc_orgri_guard_greet_AI : public ScriptedAI {
        npc_orgri_guard_greet_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Reset() override {
            Initialize();
            _events.Reset();
        }

        void Initialize() {
            _alreadyGreet = false;
        }

        void MoveInLineOfSight(Unit* unit) override {
            if (!unit || !unit->IsInWorld())
                return;

            if (Player* player = unit->ToPlayer()) {
                if (player->GetDistance(me) < 15.0f) {
                    if (player->HasQuest(QUEST_JOINING_THE_HORDE) && !_alreadyGreet) {
                        me->AI()->Talk(6);
                        _alreadyGreet = true;
                        _events.ScheduleEvent(EVENT_SAY_2, Seconds(5));
                        _events.ScheduleEvent(EVENT_RESET, Seconds(60));
                    }
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
                case EVENT_SAY_2:
                    me->AI()->Talk(7);
                    break;
                case EVENT_RESET:
                    Reset();
                    break;
                default:
                    break;
                }
            }
            // no melee attacks
        }

    private:
        EventMap _events;
        bool _alreadyGreet;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_orgri_guard_greet_AI(creature);
    }
};

class npc_orgri_shanggok_greet : public CreatureScript {
public:
    npc_orgri_shanggok_greet() : CreatureScript("npc_orgri_shanggok_greet") { }

    enum eShang {
        EVENT_RESET = 1,
    };

    struct npc_orgri_shanggok_greet_AI : public ScriptedAI {
        npc_orgri_shanggok_greet_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Reset() override {
            Initialize();
            _events.Reset();
        }

        void Initialize() {
            _alreadyGreet = false;
        }

        void MoveInLineOfSight(Unit* unit) override {
            if (!unit || !unit->IsInWorld())
                return;

            if (Player* player = unit->ToPlayer()) {
                if (player->GetDistance(me) < 25.0f) {
                    if (player->HasQuest(QUEST_JOINING_THE_HORDE) && !_alreadyGreet) {
                        me->AI()->Talk(0);
                        _alreadyGreet = true;
                        _events.ScheduleEvent(EVENT_RESET, Seconds(60));
                    }
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
                case EVENT_RESET:
                    Reset();
                    break;
                default:
                    break;
                }
            }
            // no melee attacks
        }

    private:
        bool _alreadyGreet;
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_orgri_shanggok_greet_AI(creature);
    }
};

enum e31013 {
    NPC_TEMP_JI = 62081,
    NPC_TEMP_GARROSH = 62087,
    QUEST_THE_HORDE_WAY = 31013,
};

class quest_the_horde_way : public QuestScript
{
public:
    quest_the_horde_way() : QuestScript("quest_the_horde_way") { }

    void OnQuestStatusChange(Player* player, Quest const* /*quest*/, QuestStatus oldStatus, QuestStatus newStatus) override
    {
        if (newStatus == QUEST_STATUS_NONE || QUEST_STATUS_REWARDED) {
            if (Creature* tempJi = player->GetSummonedCreatureByEntry(NPC_TEMP_JI))
                tempJi->DespawnOrUnsummon();
            if (Creature* tempGarrosh = player->GetSummonedCreatureByEntry(NPC_TEMP_GARROSH))
                tempGarrosh->DespawnOrUnsummon();
        }
    }
};

// npc 39605 for the quest 31013 'The Horde Way'
class npc_garrosh_hellscream_39605 : public CreatureScript {
public:
    npc_garrosh_hellscream_39605() : CreatureScript("npc_garrosh_hellscream_39605") { }

    enum eHellscream {
        PHASE_NONE = 0,
        PHASE_CONTINUE = -1,
        DATA_EVENT_STARTER_GUID = 0,
        WP_TALK_1 = 0,
        WP_TALK_3 = 2,
        WP_TALK_4 = 3,
        WP_TALK_5 = 4,
        WP_TALK_6 = 5,
        WP_TALK_9 = 6,
        WP_TALK_10 = 7,
        WP_TALK_12 = 8,
        WP_TALK_13 = 11,
        PHASE_TALK_2 = 1,
        PHASE_TALK_2_CONTINUE = 2,
        PHASE_TALK_5 = 3,
        PHASE_TALK_5_CONTINUE = 4,
        PHASE_TALK_6 = 5,
        PHASE_TALK_6_CONTINUE = 6,
        PHASE_TALK_7 = 7,
        PHASE_TALK_7_CONTINUE = 8,
        PHASE_TALK_8 = 9,
        PHASE_TALK_8_CONTINUE = 10,
        PHASE_TALK_9 = 11,
        PHASE_TALK_9_CONTINUE = 12,
        PHASE_TALK_10 = 13,
        PHASE_TALK_11 = 14,
        PHASE_TALK_11_CONTINUE = 15,
        PHASE_TALK_12 = 16,
        PHASE_TALK_12_CONTINUE = 17,
        PHASE_TALK_13 = 18,
        PHASE_TALK_13_CONTINUE = 19,
        PHASE_DESPAWN = 22,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override {
        if (quest->GetQuestId() == QUEST_THE_HORDE_WAY) {
            if (TempSummon* waypointGarrosh = player->SummonCreature(NPC_TEMP_GARROSH, creature->GetPosition(), TEMPSUMMON_MANUAL_DESPAWN, 0, 0, true))
            {
                waypointGarrosh->AI()->SetGUID(player->GetGUID(), DATA_EVENT_STARTER_GUID);
            }
            if (TempSummon* jiFirepaw = player->SummonCreature(NPC_TEMP_JI, player->GetPosition(), TEMPSUMMON_MANUAL_DESPAWN, 0, 0, true))
            {
                jiFirepaw->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                jiFirepaw->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VENDOR);
                jiFirepaw->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                jiFirepaw->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, float(M_PI));
            }
        }
        return true;
    }

    struct npc_garrosh_hellscream_39605_AI : public npc_escortAI {
        npc_garrosh_hellscream_39605_AI(Creature* creature) : npc_escortAI(creature) {
            Initialize();
        }

        void Initialize() {
            _phase = PHASE_NONE;
            _moveTimer = 0;
        }

        void Reset() override {
            Initialize();
            _events.Reset();
        }

        ObjectGuid GetGUID(int32 type) const override {
            if (type == DATA_EVENT_STARTER_GUID)
                return _eventStarterGuid;

            return ObjectGuid::Empty;
        }

        void SetGUID(ObjectGuid guid, int32 type) override {
            switch (type) {
                case DATA_EVENT_STARTER_GUID:
                    _eventStarterGuid = guid;
                    Start(false, false, guid);
                    SetDespawnAtFar(false);
                    Talk(0);
                    break;
                default:
                    break;
            }
        }

        /*void LastWaypointReached() override {
            me->DespawnOrUnsummon();
            me->SetFacingTo(5.631830f);

            if (Player* player = ObjectAccessor::FindPlayer(playerGuid))
                player->ForceCompleteQuest(QUEST_FINDING_A_FOOTHOLD);
        }*/

        void UpdateAI(uint32 diff) override {
            _events.Update(diff);

            if (UpdateVictim()) {
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
                    case PHASE_TALK_2:
                        if (Player* player = ObjectAccessor::GetPlayer(*me, _eventStarterGuid))
                        {
                            me->SetFacingToObject(player);
                        }
                        Talk(2);
                        _moveTimer = 7 * IN_MILLISECONDS;
                        _phase = PHASE_TALK_2_CONTINUE;
                        break;
                    case PHASE_TALK_2_CONTINUE:
                        SetEscortPaused(false);
                        _moveTimer = 0 * IN_MILLISECONDS;
                        _phase = PHASE_NONE;
                        break;
                    case PHASE_TALK_5:
                        Talk(5);
                        _moveTimer = 6 * IN_MILLISECONDS;
                        _phase = PHASE_TALK_5_CONTINUE;
                        break;
                    case PHASE_TALK_5_CONTINUE:
                        SetEscortPaused(false);
                        _moveTimer = 0 * IN_MILLISECONDS;
                        _phase = PHASE_NONE;
                        break;
                    case PHASE_TALK_6:
                        Talk(6);
                        _moveTimer = 6 * IN_MILLISECONDS;
                        _phase = PHASE_TALK_7;
                        break;
                    case PHASE_TALK_7:
                        if (Player* player = ObjectAccessor::GetPlayer(*me, _eventStarterGuid))
                        {
                            me->SetFacingToObject(player);
                        }
                        Talk(7);
                        _moveTimer = 6 * IN_MILLISECONDS;
                        _phase = PHASE_TALK_7_CONTINUE;
                        break;
                    case PHASE_TALK_7_CONTINUE:
                        if (Creature* jiFirepaw = me->FindNearestCreature(NPC_TEMP_JI, me->GetVisibilityRange(), true)) {
                            jiFirepaw->SetFacingToObject(me);
                            jiFirepaw->AI()->Talk(3);
                        }
                        _moveTimer = 3 * IN_MILLISECONDS;
                        _phase = PHASE_TALK_8;
                        break;
                    case PHASE_TALK_8:
                        Talk(8);
                        _moveTimer = 2 * IN_MILLISECONDS;
                        _phase = PHASE_TALK_8_CONTINUE;
                        break;
                    case PHASE_TALK_8_CONTINUE:
                        SetEscortPaused(false);
                        _moveTimer = 0 * IN_MILLISECONDS;
                        _phase = PHASE_NONE;
                        break;
                    case PHASE_TALK_10:
                        Talk(10);
                        _moveTimer = 4 * IN_MILLISECONDS;
                        _phase = PHASE_TALK_11;
                        break;
                    case PHASE_TALK_11:
                        if (Player* player = ObjectAccessor::GetPlayer(*me, _eventStarterGuid))
                        {
                            me->SetFacingToObject(player);
                        }
                        Talk(11);
                        _moveTimer = 3 * IN_MILLISECONDS;
                        _phase = PHASE_TALK_11_CONTINUE;
                        break;
                    case PHASE_TALK_11_CONTINUE:
                        SetEscortPaused(false);
                        _moveTimer = 0 * IN_MILLISECONDS;
                        _phase = PHASE_NONE;
                        break;
                    case PHASE_TALK_12:
                        Talk(12);
                        _moveTimer = 6 * IN_MILLISECONDS;
                        _phase = PHASE_TALK_12_CONTINUE;
                        break;
                    case PHASE_TALK_12_CONTINUE:
                        SetEscortPaused(false);
                        _moveTimer = 0 * IN_MILLISECONDS;
                        _phase = PHASE_NONE;
                        break;
                    case PHASE_TALK_13:
                        Talk(13);
                        _moveTimer = 6 * IN_MILLISECONDS;
                        _phase = PHASE_TALK_12_CONTINUE;
                        break;
                    case PHASE_TALK_13_CONTINUE:
                        SetEscortPaused(false);
                        _moveTimer = 0 * IN_MILLISECONDS;
                        _phase = PHASE_NONE;
                        break;
                    case PHASE_DESPAWN:
                        me->Respawn(false);
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
            case WP_TALK_1:
                SetEscortPaused(true);
                Talk(1);
                _moveTimer = 8 * IN_MILLISECONDS;
                _phase = PHASE_TALK_2;
                break;
            case WP_TALK_3:
                Talk(3);
                _moveTimer = 5 * IN_MILLISECONDS;
                _phase = PHASE_NONE;
                break;
            case WP_TALK_4:
                Talk(4);
                _moveTimer = 5 * IN_MILLISECONDS;
                _phase = PHASE_NONE;
                break;
            case WP_TALK_5:
                SetEscortPaused(true);
                _moveTimer = 1 * IN_MILLISECONDS;
                _phase = PHASE_TALK_5;
                break;
            case WP_TALK_6:
                SetEscortPaused(true);
                _moveTimer = 2 * IN_MILLISECONDS;
                _phase = PHASE_TALK_6;
                break;
            case WP_TALK_9:
                Talk(9);
                _moveTimer = 12 * IN_MILLISECONDS;
                _phase = PHASE_NONE;
                break;
            case WP_TALK_10:
                SetEscortPaused(true);
                _moveTimer = 1 * IN_MILLISECONDS;
                _phase = PHASE_TALK_10;
                break;
            case WP_TALK_12:
                SetEscortPaused(true);
                _moveTimer = 1 * IN_MILLISECONDS;
                _phase = PHASE_TALK_12;
                break;
            case WP_TALK_13:
                SetEscortPaused(true);
                _moveTimer = 1 * IN_MILLISECONDS;
                _phase = PHASE_TALK_13;
                break;
            default:
                break;
            }
        }

    private:
        int8 _phase;
        uint32 _moveTimer;
        ObjectGuid _eventStarterGuid;
        GuidList _explosivesGuids;
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_garrosh_hellscream_39605_AI(creature);
    }
};

void AddSC_orgrimmar()
{
	new play_fate_of_the_horde();
    // new PlayerScript_summon_khadgar();
    new npc_lord_saurfang();
    new PlayerScript_summon_khadgar_servant();
    new npc_khadgars_upgraded_servant();
    new quest_joining_the_horde();
    new npc_orgri_ji_firepaw();
    new npc_orgri_guard_greet();
    new npc_orgri_shanggok_greet();
    new npc_garrosh_hellscream_39605();
    new quest_the_horde_way();
}
