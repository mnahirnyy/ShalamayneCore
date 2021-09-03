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

#include "LFGMgr.h"
#include "LFGQueue.h"
#include "LFGPackets.h"
#include "DynamicObject.h"
#include "ScriptedEscortAI.h"
#include "CreatureTextMgr.h"
#include "MiscPackets.h"
#include "GameObjectAI.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "Creature.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "Vehicle.h"
#include "MotionMaster.h"
#include "TemporarySummon.h"
#include "GameObject.h"
#include "CombatAI.h"
#include "SpellInfo.h"
#include "GameObjectAI.h"
#include "Map.h"
#include "Transport.h"
#include "InstanceScript.h"
#include "DBCEnums.h"
#include "PhasingHandler.h"

#define GOSSIP_SHOW_DEMONS "This cannot wait. There are demons among your ranks. Let me show you."

enum {
    QUEST_THE_CALL_OF_WAR = 39691,
    QUEST_WEAPON_OF_THE_ALLIANCE = 44473,
    QUEST_BLINK_OF_AN_EYE = 44663,
    QUEST_DEMONS_AMONG_THEM = 44463,
    SCENE_DEMONS_AMONG_THEM = 1456,
    KILL_CREDIT_WARN_ANDUIN_WRYNN = 111585,
    SPELL_PHASE_175 = 57569,
    SPELL_PHASE_176 = 74789,
};

// 102585 - Jace Darkweaver
class npc_stormwind_jace : public CreatureScript
{
public:
    npc_stormwind_jace() : CreatureScript("npc_stormwind_jace") { }

    struct npc_stormwind_jaceAI : public ScriptedAI
    {
        npc_stormwind_jaceAI(Creature* creature) : ScriptedAI(creature) { }

        void MoveInLineOfSight(Unit* unit) override
        {
            if (Player* player = unit->ToPlayer())
                if (player->GetDistance(me) < 10.0f)
                    if (player->HasQuest(QUEST_THE_CALL_OF_WAR) && player->GetQuestStatus(QUEST_THE_CALL_OF_WAR) == QUEST_STATUS_INCOMPLETE)
                        player->KilledMonsterCredit(me->GetEntry());
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_stormwind_jaceAI(creature);
    }
};

class npc_anduin_wrynn : public CreatureScript
{
public:
    npc_anduin_wrynn() : CreatureScript("npc_anduin_wrynn") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->HasQuest(QUEST_DEMONS_AMONG_THEM) &&
            player->GetQuestStatus(QUEST_DEMONS_AMONG_THEM) != QUEST_STATUS_REWARDED)
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_SHOW_DEMONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
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
            player->GetSceneMgr().PlayScene(SCENE_DEMONS_AMONG_THEM);
            CloseGossipMenuFor(player);
            break;
        }
        return true;
    }
};

class scene_demons_among_them_alliance : public SceneScript
{
public:
    scene_demons_among_them_alliance() : SceneScript("scene_demons_among_them_alliance") { }

    void OnSceneEnd(Player* player, uint32 /*sceneInstanceID*/, SceneTemplate const* /*sceneTemplate*/) override
    {
        player->KilledMonsterCredit(KILL_CREDIT_WARN_ANDUIN_WRYNN, ObjectGuid::Empty);
        PhasingHandler::OnConditionChange(player);
    }
};

class quest_demons_among_them : public QuestScript
{
public:
    quest_demons_among_them() : QuestScript("quest_demons_among_them") { }

    void OnQuestStatusChange(Player* player, Quest const* /*quest*/, QuestStatus /*oldStatus*/, QuestStatus newStatus) override
    {
        if (newStatus == QUEST_STATUS_NONE)
        {
            PhasingHandler::OnConditionChange(player);
        }
    }
};

// Elerion Bladedancer <Illidari>
class npc_elerion_bladedancer_101004 : public CreatureScript
{
public:
    npc_elerion_bladedancer_101004() : CreatureScript("npc_elerion_bladedancer_101004") { }

    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*item*/) override
    {
        if (quest->GetQuestId() == QUEST_WEAPON_OF_THE_ALLIANCE)
        {
            player->CastSpell(player, 228002, true);
        }

        return true;
    }
};

// Khadgar's Upgraded Servant
class npc_khadgars_upgraded_servant_114562 : public CreatureScript
{
public:
    npc_khadgars_upgraded_servant_114562() : CreatureScript("npc_khadgars_upgraded_servant_114562") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_BLINK_OF_AN_EYE)
        {
            creature->DestroyForPlayer(player);
        }
        return true;
    }
};


class PlayerScript_phase_correction : public PlayerScript
{
public:
    PlayerScript_phase_correction() : PlayerScript("PlayerScript_phase_correction") {}

    uint32 checkTimer = 1000;
    
    void OnUpdate(Player* player, uint32 diff) override
    {
        if (checkTimer <= diff)
        {
            if (player->getClass() == CLASS_DEMON_HUNTER && player->GetAreaId() == 6292 &&
                player->GetQuestStatus(QUEST_DEMONS_AMONG_THEM) == QUEST_STATUS_COMPLETE &&
                player->GetPhaseShift().HasPhase(175) && player->GetPhaseShift().HasPhase(176))
            {
                PhasingHandler::RemovePhase(player, 175);
            }

            if (player->getClass() == CLASS_DEMON_HUNTER && player->GetAreaId() == 6292 &&
                player->GetQuestStatus(QUEST_DEMONS_AMONG_THEM) == QUEST_STATUS_NONE)
            {
                PhasingHandler::OnConditionChange(player);
                player->AddAura(SPELL_PHASE_175);
            }

            checkTimer = 1000;
        }
        else checkTimer -= diff;
    }
};

/* https://www.wowhead.com/quest=30987/joining-the-alliance */
enum eQuestAlly {
    QUEST_JOINING_THE_ALLIANCE = 30987,
    NPC_AYSA = 60566,
    NPC_JOJO = 60567,
};

class quest_joining_the_alliance : public QuestScript
{
public:
    quest_joining_the_alliance() : QuestScript("quest_joining_the_alliance") { }

    void OnQuestStatusChange(Player* player, Quest const* /*quest*/, QuestStatus oldStatus, QuestStatus newStatus) override
    {
        if (newStatus == QUEST_STATUS_NONE || QUEST_STATUS_REWARDED) {
            if (Creature* tempAysa = player->GetSummonedCreatureByEntry(NPC_AYSA))
                tempAysa->DespawnOrUnsummon();
            if (Creature* tempJojo = player->GetSummonedCreatureByEntry(NPC_JOJO))
                tempJojo->DespawnOrUnsummon();
        }
    }
};

class npc_stormwind_aysa_cloudsinger : public CreatureScript
{
public:
    npc_stormwind_aysa_cloudsinger() : CreatureScript("npc_stormwind_aysa_cloudsinger") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_JOINING_THE_ALLIANCE) {
            if (TempSummon* followerAysa = player->SummonCreature(creature->GetEntry(), creature->GetPosition(), TEMPSUMMON_MANUAL_DESPAWN, 0, 0, true))
            {
                followerAysa->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                followerAysa->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VENDOR);
                followerAysa->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                followerAysa->AI()->Talk(1);
                followerAysa->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, float(M_PI));
            }
            if (TempSummon* followerJojo = player->SummonCreature(NPC_JOJO, -9064.97f, 436.71f, 93.055f, 0.6891f, TEMPSUMMON_MANUAL_DESPAWN, 0, true))
            {
                followerJojo->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                followerJojo->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VENDOR);
                followerJojo->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                followerJojo->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, float(M_PI) / 2);
            }
        }
        return true;
    }

    enum eAysa {
        NPC_HAMMOND = 65153,
        NPC_BOARD_BUNNY = 70496,
        EVENT_SAY_LINE2 = 1,
        EVENT_SAY_LINE3 = 2,
        EVENT_SAY_LINE4 = 3,
        EVENT_CONTINUE_FOLLOW = 4,
        EVENT_HAMMOND_TALK = 5,
        DATA_SAY_LINE2 = 61,
        DATA_SAY_LINE6 = 63,
        DATA_SAY_LINE3 = 65,
    };

    struct npc_stormwind_aysa_cloudsinger_AI : public ScriptedAI
    {
        npc_stormwind_aysa_cloudsinger_AI(Creature* creature) : ScriptedAI(creature) {
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

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SAY_LINE2:
                    if (Creature* hammond = me->FindNearestCreature(NPC_HAMMOND, me->GetVisibilityRange(), true)) {
                        me->GetMotionMaster()->MoveCloserAndStop(0, hammond, 5.1f);
                        me->AI()->Talk(2);
                        _events.ScheduleEvent(EVENT_CONTINUE_FOLLOW, Seconds(3));
                    }
                    break;
                case EVENT_SAY_LINE3:
                    if (Creature* boardBunny = me->FindNearestCreature(NPC_BOARD_BUNNY, me->GetVisibilityRange())) {
                        me->GetMotionMaster()->MoveCloserAndStop(1, boardBunny, 6.1f);
                        me->AI()->Talk(3);
                        _events.ScheduleEvent(EVENT_SAY_LINE4, Seconds(4));
                    }
                    break;
                case EVENT_SAY_LINE4:
                    me->AI()->Talk(4);
                    if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGuid))
                        me->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, float(M_PI));
                    break;
                case EVENT_CONTINUE_FOLLOW:
                    if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGuid))
                        me->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, float(M_PI));
                    _events.ScheduleEvent(EVENT_HAMMOND_TALK, Seconds(1));
                    break;
                case EVENT_HAMMOND_TALK:
                    if (Creature* hammond = me->FindNearestCreature(NPC_HAMMOND, me->GetVisibilityRange(), true)) {
                        hammond->AI()->Talk(5);
                        hammond->AI()->SetData(DATA_SAY_LINE6, DATA_SAY_LINE6);
                    }
                    break;
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
            case DATA_SAY_LINE2:
                _events.ScheduleEvent(EVENT_SAY_LINE2, Seconds(3));
                break;
            case DATA_SAY_LINE3:
                _events.ScheduleEvent(EVENT_SAY_LINE3, Seconds(3));
                break;
            default:
                break;
            }
        }

    private:
        EventMap _events;
        ObjectGuid _playerGuid;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_stormwind_aysa_cloudsinger_AI(creature);
    }
};
// bunny 70496
class npc_stormwind_heros_board : public CreatureScript
{
public:
    npc_stormwind_heros_board() : CreatureScript("npc_stormwind_heros_board") { }

    struct npc_stormwind_heros_board_AI : public ScriptedAI
    {
        npc_stormwind_heros_board_AI(Creature* creature) : ScriptedAI(creature) {}

        uint32 giveKillCredit;

        void Reset() {
            giveKillCredit = 1000;
        }

        void UpdateAI(uint32 diff) {
            std::list<Player*> playerList;
            me->GetPlayerListInGrid(playerList, 20.0f);
            for (Player* player : playerList) {
                if (player->GetQuestStatus(QUEST_JOINING_THE_ALLIANCE) == QUEST_STATUS_COMPLETE) {
                    if (giveKillCredit <= diff) {
                        if (Creature* aysa = me->FindNearestCreature(NPC_AYSA, me->GetVisibilityRange(), true)) {
                            aysa->AI()->SetData(65, 65);
                            giveKillCredit = 60000;
                        }
                        else
                            giveKillCredit = 1000;
                    }
                    else
                        giveKillCredit -= diff;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_stormwind_heros_board_AI(creature);
    }
};

class npc_stormwind_general_hammond_greet : public CreatureScript {
public:
    npc_stormwind_general_hammond_greet() : CreatureScript("npc_stormwind_general_hammond_greet") { }

    enum eGeneral {
        NPC_AYSA = 60566,
        EVENT_SAY_LINE5 = 1,
        EVENT_SAY_LINE6 = 2,
        EVENT_RESET = 3,
        DATA_SAY_LINE5 = 62,
        DATA_SAY_LINE6 = 63,
    };

    struct npc_stormwind_general_hammond_greet_AI : public ScriptedAI {
        npc_stormwind_general_hammond_greet_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Reset() override {
            Initialize();
            _events.Reset();
        }

        void Initialize() {
            _alreadyGreet = false;
            _playerGuid = ObjectGuid::Empty;
        }

        void MoveInLineOfSight(Unit* unit) override {
            if (!unit || !unit->IsInWorld())
                return;

            if (Player* player = unit->ToPlayer()) {
                if (player->GetDistance(me) < 25.0f) {
                    if (player->HasQuest(QUEST_JOINING_THE_ALLIANCE) && !_alreadyGreet) {
                        _playerGuid = player->GetGUID();
                        me->AI()->Talk(4);
                        _alreadyGreet = true;
                        if (Creature* aysa = me->FindNearestCreature(NPC_AYSA, me->GetVisibilityRange(), true))
                            aysa->AI()->SetData(61, 61);
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
                case EVENT_SAY_LINE5:
                    me->AI()->Talk(5);
                    break;
                case EVENT_SAY_LINE6:
                    me->AI()->Talk(6);
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

        void SetData(uint32 id, uint32 value) override
        {
            switch (id)
            {
            case DATA_SAY_LINE5:
                _events.ScheduleEvent(EVENT_SAY_LINE5, Seconds(4));
                break;
            case DATA_SAY_LINE6:
                _events.ScheduleEvent(EVENT_SAY_LINE6, Seconds(4));
                break;
            default:
                break;
            }
        }

    private:
        bool _alreadyGreet;
        ObjectGuid _playerGuid;
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_stormwind_general_hammond_greet_AI(creature);
    }
};

class npc_stormwind_guard_greet : public CreatureScript {
public:
    npc_stormwind_guard_greet() : CreatureScript("npc_stormwind_guard_greet") { }

    enum eGuard {
        EVENT_RESET = 1,
    };

    struct npc_stormwind_guard_greet_AI : public ScriptedAI {
        npc_stormwind_guard_greet_AI(Creature* creature) : ScriptedAI(creature) {
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
                    if (player->HasQuest(QUEST_JOINING_THE_ALLIANCE) && !_alreadyGreet) {
                        me->AI()->Talk(6);
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
        return new npc_stormwind_guard_greet_AI(creature);
    }
};

class npc_stormwind_moni_greet : public CreatureScript {
public:
    npc_stormwind_moni_greet() : CreatureScript("npc_stormwind_moni_greet") { }

    enum eMoni {
        NPC_ALYN_BLACK = 61834,
        EVENT_TALK_ALYN = 1,
        EVENT_RESET = 2,
        DATA_SAY_LINE_2 = 64,
    };

    struct npc_stormwind_moni_greet_AI : public ScriptedAI {
        npc_stormwind_moni_greet_AI(Creature* creature) : ScriptedAI(creature) {
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
                    if (player->HasQuest(QUEST_JOINING_THE_ALLIANCE) && !_alreadyGreet) {
                        me->AI()->Talk(0);
                        _alreadyGreet = true;
                        _events.ScheduleEvent(EVENT_TALK_ALYN, Seconds(3));
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
                case EVENT_TALK_ALYN:
                    if (Creature* alyn = me->FindNearestCreature(NPC_ALYN_BLACK, me->GetVisibilityRange(), true))
                        alyn->AI()->Talk(0);
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
        bool _alreadyGreet;
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_stormwind_moni_greet_AI(creature);
    }
};

class npc_stormwind_marty_josie_greet : public CreatureScript {
public:
    npc_stormwind_marty_josie_greet() : CreatureScript("npc_stormwind_marty_josie_greet") { }

    enum eMarty {
        NPC_JOSIE = 61896,
        EVENT_TALK_JOSIE = 1,
        EVENT_TALK_JOSIE_2 = 2,
        EVENT_RESET = 3,
    };

    struct npc_stormwind_marty_josie_greet_AI : public ScriptedAI {
        npc_stormwind_marty_josie_greet_AI(Creature* creature) : ScriptedAI(creature) {
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
                    if (player->HasQuest(QUEST_JOINING_THE_ALLIANCE) && !_alreadyGreet) {
                        me->AI()->Talk(0);
                        _alreadyGreet = true;
                        _events.ScheduleEvent(EVENT_TALK_JOSIE, Seconds(3));
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
                case EVENT_TALK_JOSIE:
                    if (Creature* josie = me->FindNearestCreature(NPC_JOSIE, me->GetVisibilityRange(), true))
                        josie->AI()->Talk(0);
                    _events.ScheduleEvent(EVENT_TALK_JOSIE_2, Seconds(3));
                    break;
                case EVENT_TALK_JOSIE_2:
                    if (Creature* josie = me->FindNearestCreature(NPC_JOSIE, me->GetVisibilityRange(), true))
                        josie->AI()->Talk(1);
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
        bool _alreadyGreet;
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_stormwind_marty_josie_greet_AI(creature);
    }
};

class npc_stormwind_gavin_greet : public CreatureScript {
public:
    npc_stormwind_gavin_greet() : CreatureScript("npc_stormwind_gavin_greet") { }

    enum eGavin {
        NPC_JOJO = 60567,
        EVENT_SAY_2 = 1,
        EVENT_JOJO_SAY = 2,
        EVENT_RESET = 3,
    };

    struct npc_stormwind_gavin_greet_AI : public ScriptedAI {
        npc_stormwind_gavin_greet_AI(Creature* creature) : ScriptedAI(creature) {
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
                    if (player->HasQuest(QUEST_JOINING_THE_ALLIANCE) && !_alreadyGreet) {
                        me->AI()->Talk(0);
                        _alreadyGreet = true;
                        _events.ScheduleEvent(EVENT_SAY_2, Seconds(4));
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
                    me->AI()->Talk(1);
                    _events.ScheduleEvent(EVENT_JOJO_SAY, Seconds(3));
                    break;
                case EVENT_JOJO_SAY:
                    if (Creature* jojo = me->FindNearestCreature(NPC_JOJO, me->GetVisibilityRange(), true))
                        jojo->AI()->Talk(0);
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
        return new npc_stormwind_gavin_greet_AI(creature);
    }
};

class npc_stormwind_leria_greet : public CreatureScript {
public:
    npc_stormwind_leria_greet() : CreatureScript("npc_stormwind_leria_greet") { }

    enum eLeria {
        EVENT_RESET = 1,
    };

    struct npc_stormwind_leria_greet_AI : public ScriptedAI {
        npc_stormwind_leria_greet_AI(Creature* creature) : ScriptedAI(creature) {
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
                    if (player->HasQuest(QUEST_JOINING_THE_ALLIANCE) && !_alreadyGreet) {
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
        return new npc_stormwind_leria_greet_AI(creature);
    }
};

class npc_stormwind_lucas_naanae_greet : public CreatureScript {
public:
    npc_stormwind_lucas_naanae_greet() : CreatureScript("npc_stormwind_lucas_naanae_greet") { }

    enum eLucas {
        NPC_AYSA = 60566,
        NPC_JOJO = 60567,
        NPC_NANNAE = 61840,
        EVENT_TALK_NANNAE = 1,
        EVENT_TALK_NANNAE_2 = 2,
        EVENT_TALK_JOJO = 3,
        EVENT_TALK_AYSA = 4,
        EVENT_RESET = 5,
    };

    struct npc_stormwind_lucas_naanae_greet_AI : public ScriptedAI {
        npc_stormwind_lucas_naanae_greet_AI(Creature* creature) : ScriptedAI(creature) {
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
                if (player->GetDistance(me) < 40.0f) {
                    if (player->HasQuest(QUEST_JOINING_THE_ALLIANCE) && !_alreadyGreet) {
                        me->AI()->Talk(0);
                        _alreadyGreet = true;
                        _events.ScheduleEvent(EVENT_TALK_NANNAE, Seconds(3));
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
                case EVENT_TALK_NANNAE:
                    if (Creature* nannae = me->FindNearestCreature(NPC_NANNAE, me->GetVisibilityRange(), true))
                        nannae->AI()->Talk(0);
                    _events.ScheduleEvent(EVENT_TALK_NANNAE_2, Seconds(3));
                    break;
                case EVENT_TALK_NANNAE_2:
                    if (Creature* nannae = me->FindNearestCreature(NPC_NANNAE, me->GetVisibilityRange(), true))
                        nannae->AI()->Talk(1);
                    _events.ScheduleEvent(EVENT_TALK_JOJO, Seconds(3));
                    _events.ScheduleEvent(EVENT_TALK_AYSA, Seconds(4));
                    break;
                case EVENT_TALK_JOJO:
                    if (Creature* jojo = me->FindNearestCreature(NPC_JOJO, me->GetVisibilityRange(), true))
                        jojo->AI()->Talk(1);
                    break;
                case EVENT_TALK_AYSA:
                    if (Creature* aysa = me->FindNearestCreature(NPC_AYSA, me->GetVisibilityRange(), true))
                        aysa->AI()->Talk(0);
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
        bool _alreadyGreet;
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_stormwind_lucas_naanae_greet_AI(creature);
    }
};

/*********/
/* AddSC */
/*********/
void AddSC_stormwind_city()
{   
    new npc_stormwind_jace();
    new npc_anduin_wrynn();
    new scene_demons_among_them_alliance();
    new quest_demons_among_them();
    new npc_elerion_bladedancer_101004();
    new npc_khadgars_upgraded_servant_114562();
    new PlayerScript_phase_correction();
    new quest_joining_the_alliance();
    new npc_stormwind_aysa_cloudsinger();
    new npc_stormwind_heros_board();
    new npc_stormwind_general_hammond_greet();
    new npc_stormwind_guard_greet();
    new npc_stormwind_marty_josie_greet();
    new npc_stormwind_moni_greet();
    new npc_stormwind_gavin_greet();
    new npc_stormwind_leria_greet();
    new npc_stormwind_lucas_naanae_greet();
}
