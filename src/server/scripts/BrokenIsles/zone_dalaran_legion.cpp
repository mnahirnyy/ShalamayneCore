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

#include "Conversation.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "MapManager.h"
#include "ObjectMgr.h"
#include "PhasingHandler.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "SpellScript.h"
#include "Log.h"

/*
 * Dalaran above Karazhan
 *
 * Legion Intro
 */

enum
{
    PHASE_DALARAN_KARAZHAN  = 5829,
    QUEST_BLINK_OF_AN_EYE   = 44663,
    QUEST_CALL_OF_THE_ILLIDARI = 39047,
};

// TODO : All this script is temp fix,
// remove it when legion start quests are properly fixed
class OnLegionArrival : public PlayerScript
{
public:
    OnLegionArrival() : PlayerScript("OnLegionArrival") { }

    enum
    {
        SPELL_MAGE_LEARN_GUARDIAN_HALL_TP   = 204287,
        SPELL_WAR_LEARN_JUMP_TO_SKYHOLD     = 192084,
        SPELL_DRUID_CLASS_HALL_TP           = 204874,
        SPELL_CREATE_CLASS_HALL_ALLIANCE    = 185506,
        SPELL_CREATE_CLASS_HALL_HORDE       = 192191,

        CONVERSATION_KHADGAR_BLINK_OF_EYE   = 3827,
    };

    void OnLogin(Player* player, bool firstLogin) override
    {
        // Can happen in recovery cases
        if (player->getLevel() >= 100 && firstLogin)
            HandleLegionArrival(player);
    }

    void OnLevelChanged(Player* player, uint8 oldLevel) override
    {
        if (oldLevel < 100 && player->getLevel() >= 100)
            HandleLegionArrival(player);
    }

    void HandleLegionArrival(Player* player)
    {
        switch (player->getClass())
        {
            case CLASS_MAGE:
                player->CastSpell(player, SPELL_MAGE_LEARN_GUARDIAN_HALL_TP, true);
                break;
            case CLASS_WARRIOR:
                player->CastSpell(player, SPELL_WAR_LEARN_JUMP_TO_SKYHOLD, true);
                break;
            case CLASS_DRUID:
                player->CastSpell(player, SPELL_DRUID_CLASS_HALL_TP, true);
                break;
            case CLASS_HUNTER:
                player->m_taxi.SetTaximaskNode(1848); // Hunter Class Hall
                break;
            default:
                break;
        }

        player->CastSpell(player, player->IsInAlliance() ? SPELL_CREATE_CLASS_HALL_ALLIANCE : SPELL_CREATE_CLASS_HALL_HORDE, true);

        // if (player->GetQuestStatus(QUEST_BLINK_OF_AN_EYE) == QUEST_STATUS_NONE)
        // {
        //     Conversation::CreateConversation(CONVERSATION_KHADGAR_BLINK_OF_EYE, player, player->GetPosition(), { player->GetGUID() });

        //     if (const Quest* quest = sObjectMgr->GetQuestTemplate(QUEST_BLINK_OF_AN_EYE))
        //         player->AddQuest(quest, nullptr);
        // }
    }
};

class On110Arrival : public PlayerScript
{
public:
    On110Arrival() : PlayerScript("On110Arrival") { }

    enum
    {
        QUEST_UNITING_THE_ISLES     = 43341,
    };

    void OnLogin(Player* player, bool firstLogin) override
    {
        // Can happen in recovery cases
        if (player->getLevel() >= 110 && firstLogin)
            Handle110Arrival(player);
    }

    void OnLevelChanged(Player* player, uint8 oldLevel) override
    {
        if (oldLevel < 110 && player->getLevel() >= 110)
            Handle110Arrival(player);
    }

    void Handle110Arrival(Player* player)
    {
        if (player->GetQuestStatus(QUEST_UNITING_THE_ISLES) == QUEST_STATUS_NONE)
            if (const Quest* quest = sObjectMgr->GetQuestTemplate(QUEST_UNITING_THE_ISLES))
                player->AddQuest(quest, nullptr);
    }
};

// 228329 & 228330 - Teleportation
class spell_dalaran_teleportation : public SpellScript
{
    PrepareSpellScript(spell_dalaran_teleportation);

    void EffectTeleportDalaranKarazhan(SpellEffIndex effIndex)
    {
        if (Player* player = GetCaster()->ToPlayer())
        {
            if (player->getLevel() < 100 || player->GetQuestStatus(QUEST_BLINK_OF_AN_EYE) != QUEST_STATUS_INCOMPLETE)
                PreventHitEffect(effIndex);
            else
            {
                if (SpellTargetPosition const* targetPosition = sSpellMgr->GetSpellTargetPosition(GetSpellInfo()->Id, effIndex))
                    if (Map* map = sMapMgr->FindMap(targetPosition->target_mapId, 0))
                        map->LoadGrid(targetPosition->target_X, targetPosition->target_Y);
            }
        }
    }

    void EffectTeleportDalaranLegion(SpellEffIndex effIndex)
    {
        if (Player* player = GetCaster()->ToPlayer())
            if (player->getLevel() < 100 || player->GetQuestStatus(QUEST_BLINK_OF_AN_EYE) == QUEST_STATUS_INCOMPLETE)
                PreventHitEffect(effIndex);
    }

    void Register() override
    {
        OnEffectLaunch += SpellEffectFn(spell_dalaran_teleportation::EffectTeleportDalaranKarazhan, EFFECT_0, SPELL_EFFECT_TRIGGER_SPELL);
        OnEffectLaunch += SpellEffectFn(spell_dalaran_teleportation::EffectTeleportDalaranLegion, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);
    }
};

// 113986 - Khadgar
class npc_dalaran_karazhan_khadgar : public CreatureScript
{
public:
    npc_dalaran_karazhan_khadgar() : CreatureScript("npc_dalaran_karazhan_khadgar") { }

    enum
    {
        SPELL_PLAY_DALARAN_TELEPORTATION_SCENE = 227861
    };

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*uiSender*/, uint32 /*uiAction*/) override
    {
        player->CastSpell(player, SPELL_PLAY_DALARAN_TELEPORTATION_SCENE, true);
        return true;
    }
};

class scene_dalaran_kharazan_teleportion : public SceneScript
{
public:
    scene_dalaran_kharazan_teleportion() : SceneScript("scene_dalaran_kharazan_teleportion") { }

    void OnSceneTriggerEvent(Player* player, uint32 /*sceneInstanceID*/, SceneTemplate const* /*sceneTemplate*/, std::string const& triggerName) override
    {
        if (triggerName == "invisibledalaran")
            PhasingHandler::AddPhase(player, PHASE_DALARAN_KARAZHAN);
    }

    void OnSceneEnd(Player* player, uint32 /*sceneInstanceID*/, SceneTemplate const* /*sceneTemplate*/) override
    {
        player->KilledMonsterCredit(114506);
        player->TeleportTo(1220, -827.82f, 4369.25f, 738.64f, 1.893364f);
    }
};

/*
 * Legion Dalaran
 */

// Zone 8392
class zone_legion_dalaran_underbelly : public ZoneScript
{
public:
    zone_legion_dalaran_underbelly() : ZoneScript("zone_legion_dalaran_underbelly") { }

    void OnPlayerEnter(Player* player) override
    {
        player->SeamlessTeleportToMap(MAP_DALARAN_UNDERBELLY);
    }

    void OnPlayerExit(Player* player) override
    {
        if (player->GetMapId() == MAP_DALARAN_UNDERBELLY)
            player->SeamlessTeleportToMap(MAP_BROKEN_ISLANDS);
    }
};

class CastEventTP : public BasicEvent
{
public:
    CastEventTP(Unit* caster, uint32 spellId, bool trigger) :
        _caster(caster), _spellId(spellId), _trigger(trigger) { }

    bool Execute(uint64 /*time*/, uint32 /*diff*/)
    {
        if (_caster)
            _caster->CastSpell(_caster, _spellId, _trigger);
        return true;
    }

private:
    Unit * _caster;
    uint32 _spellId;
    bool _trigger;
};

// 108868 7.x.x
class npc_hunter_talua : public CreatureScript
{
public:
    npc_hunter_talua() : CreatureScript("npc_hunter_talua") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 /*action*/) override
    {
        if (player->getLevel() < 98 || player->getClass() != CLASS_HUNTER)
            return true;

        if (Pet* pet = player->GetPet())
            player->RemovePet(nullptr, PET_SAVE_DISMISS, false);

        player->CastSpell(player, 216213, true);
        player->m_Events.AddEvent(new CastEventTP(player, 216216, true), player->m_Events.CalculateTime(10000));

        return true;
    }
};

class npc_great_eagle : public CreatureScript
{
public:
    npc_great_eagle() : CreatureScript("npc_great_eagle") { }

    struct npc_great_eagleAI : public ScriptedAI
    {
        npc_great_eagleAI(Creature* creature) : ScriptedAI(creature) { }

        uint8 curID;
        void Reset()
        {
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            me->GetMotionMaster()->MoveDistract(1000);
            me->GetMotionMaster()->MovePoint(1, -854.9718f, 4185.322f, 754.1122f);
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE)
                return;

            switch (id)
            {
            case 1:
                me->DespawnOrUnsummon(0);
                break;
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_great_eagleAI(creature);
    }
};

enum ChoicesAndKillcredits
{
    DRUID_CHOICE                            = 247,
    DRUID_ARTIFACT_QUEST_KILLCREDIT         = 101296,
    HUNTER_CHOICE                           = 240,
    HUNTER_ARTIFACT_QUEST_KILLCREDIT        = 104634,
    ROGUE_CHOICE                            = 280,
    ROGUE_ARTIFACT_QUEST_KILLCREDIT         = 105953,
    PALADIN_CHOICE                          = 235,
    PALADIN_ARTIFACT_QUEST_KILLCREDIT       = 90369,
    DEATH_KNIGHT_CHOICE                     = 253,
    DEATH_KNIGHT_ARTIFACT_QUEST_KILLCREDIT  = 101441,
    PRIEST_CHOICE                           = 248,
    PRIEST_ARTIFACT_QUEST_KILLCREDIT        = 100583,
    DEMON_HUNTER_CHOICE                     = 255,
    DEMON_HUNTER_ARTIFACT_QUEST_KILLCREDIT  = 105177,
    MAGE_CHOICE                             = 265,
    MAGE_ARTIFACT_QUEST_KILLCREDIT          = 103037,
    WARLOCK_CHOICE                          = 245,
    WARLOCK_ARTIFACT_QUEST_KILLCREDIT       = 101095,
    WARRIOR_CHOICE                          = 236,
    WARRIOR_ARTIFACT_QUEST_KILLCREDIT       = 100583,
    SHAMAN_CHOICE                           = 266,
    SHAMAN_ARTIFACT_QUEST_KILLCREDIT        = 96527,
    MONK_CHOICE                             = 242,
    MONK_ARTIFACT_QUEST_KILLCREDIT          = 100438,
};

class player_artifact_choice : public PlayerScript
{
public:
    player_artifact_choice() : PlayerScript("player_artifact_choice") { }
 
    void OnCompleteQuestChoice(Player* player, uint32 choiceId, uint32 /*responseId*/)
    {
        switch (choiceId)
        {
            case DRUID_CHOICE:
                player->KilledMonsterCredit(DRUID_ARTIFACT_QUEST_KILLCREDIT);
                break;
            case HUNTER_CHOICE:
                player->KilledMonsterCredit(HUNTER_ARTIFACT_QUEST_KILLCREDIT);
                break;
            case ROGUE_CHOICE:
                player->KilledMonsterCredit(ROGUE_ARTIFACT_QUEST_KILLCREDIT);
                break;
            case PALADIN_CHOICE:
                player->KilledMonsterCredit(PALADIN_ARTIFACT_QUEST_KILLCREDIT);
                break;
            case DEATH_KNIGHT_CHOICE:
                player->KilledMonsterCredit(DEATH_KNIGHT_ARTIFACT_QUEST_KILLCREDIT);
                break;
            case PRIEST_CHOICE:
                player->KilledMonsterCredit(PRIEST_ARTIFACT_QUEST_KILLCREDIT);
                break;
            case DEMON_HUNTER_CHOICE:
                player->KilledMonsterCredit(DEMON_HUNTER_ARTIFACT_QUEST_KILLCREDIT);
                break;
            case MAGE_CHOICE:
                player->KilledMonsterCredit(MAGE_ARTIFACT_QUEST_KILLCREDIT);
                break;
            case WARLOCK_CHOICE:
                player->KilledMonsterCredit(WARLOCK_ARTIFACT_QUEST_KILLCREDIT);
                break;
            case WARRIOR_CHOICE:
                player->KilledMonsterCredit(WARRIOR_ARTIFACT_QUEST_KILLCREDIT);
                break;
            case SHAMAN_CHOICE:
                player->KilledMonsterCredit(SHAMAN_ARTIFACT_QUEST_KILLCREDIT);
                break;
            case MONK_CHOICE:
                player->KilledMonsterCredit(MONK_ARTIFACT_QUEST_KILLCREDIT);
                break;
        }
 
    }
};

class PlayerScript_summon_korvas_bloodthorn : public PlayerScript
{
public:
    PlayerScript_summon_korvas_bloodthorn() : PlayerScript("PlayerScript_summon_korvas_bloodthorn") {}

    uint32 checkTimer = 1000;
    bool _korvasSummoned = false;

    void OnUpdate(Player* player, uint32 diff) override
    {
        if (checkTimer <= diff)
        {
            if (player->getClass() == CLASS_DEMON_HUNTER && player->GetAreaId() == 7581 &&
                player->GetQuestStatus(QUEST_BLINK_OF_AN_EYE) == QUEST_STATUS_REWARDED &&
                player->GetQuestStatus(QUEST_CALL_OF_THE_ILLIDARI) == QUEST_STATUS_NONE && !_korvasSummoned
                ) {
                    if (Creature* creature = player->FindNearestCreature(116704, 10.0f)) {
                        creature->DestroyForPlayer(player);
                        _korvasSummoned = false;
                    }

                    player->CastSpell(player, 232347, true);
                    _korvasSummoned = true;
            }
            checkTimer = 1000;
        }
        else checkTimer -= diff;
    }
};

class npc_korvas_bloodthorn_summon : public CreatureScript
{
public:
    npc_korvas_bloodthorn_summon() : CreatureScript("npc_korvas_bloodthorn_summon") { }

    enum {
        TEXT_GREETING = 0,
        TEXT_ACCEPT_ALTRUIS = 1,
        TEXT_ACCEPT_KAYN = 2,
        TEXT_EXTRA_GREETING_1 = 3,
        TEXT_EXTRA_GREETING_2 = 4,
        TEXT_EXTRA_GREETING_3 = 5,
        EVENT_EXTRA_GREETING_1 = 10,
        EVENT_EXTRA_GREETING_2 = 11,
        EVENT_EXTRA_GREETING_3 = 12,
        EVENT_EXTRA_GREETING_4 = 13,
        DATA_GREETING_ENDED = 20,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_CALL_OF_THE_ILLIDARI)
        {
            creature->AI()->SetData(DATA_GREETING_ENDED, DATA_GREETING_ENDED);
            creature->AI()->Talk(TEXT_ACCEPT_ALTRUIS);
            creature->DespawnOrUnsummon(15000);
        }
        return true;
    }

    struct npc_korvas_summonAI : public ScriptedAI
    {
        npc_korvas_summonAI(Creature* creature) : ScriptedAI(creature) {
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
                    if (!player->HasQuest(QUEST_CALL_OF_THE_ILLIDARI) && !_alreadyGreet)
                    {
                        _events.ScheduleEvent(EVENT_EXTRA_GREETING_1, 1000);
                        _events.ScheduleEvent(EVENT_EXTRA_GREETING_2, 25000);
                        _events.ScheduleEvent(EVENT_EXTRA_GREETING_3, 45000);
                        _events.ScheduleEvent(EVENT_EXTRA_GREETING_4, 75000);
                        _alreadyGreet = true;
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
                case EVENT_EXTRA_GREETING_1:
                    Talk(TEXT_GREETING, me->GetOwner());
                    break;
                case EVENT_EXTRA_GREETING_2:
                    Talk(TEXT_EXTRA_GREETING_1, me->GetOwner());
                    break;
                case EVENT_EXTRA_GREETING_3:
                    Talk(TEXT_EXTRA_GREETING_2, me->GetOwner());
                    break;
                case EVENT_EXTRA_GREETING_4:
                    Talk(TEXT_EXTRA_GREETING_3, me->GetOwner());
                    break;
                default:
                    break;
                }
            }
            // no melee attacks
        }

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
                case DATA_GREETING_ENDED:
                {
                    _events.CancelEvent(EVENT_EXTRA_GREETING_2);
                    _events.CancelEvent(EVENT_EXTRA_GREETING_3);
                    _events.CancelEvent(EVENT_EXTRA_GREETING_4);
                    _alreadyGreet = true;
                    break;
                }
            }
        }

    private:
        bool _alreadyGreet;
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_korvas_summonAI(creature);
    }
};

enum eChoices
{
    QUEST_THE_POWER_TO_SURVIVE = 40816,
    SPELL_PLAYERCHOICE = 201092,
    PLAYER_CHOICE_DH_ARTIFACT_SELECTION = 255,
    PLAYER_CHOICE_DH_HAVOC = 641,
    PLAYER_CHOICE_DH_VENGEANCE = 640,
    SPELL_DH_SPEC_HAVOK = 201093,
    SPELL_DH_SPEC_VENGEANCE = 201094,
    QUEST_ALDRACHI_WARBLADES_CHOSEN = 40818,
    QUEST_TWINBLADES_OFTHE_DECEIVER_CHOSEN = 40817,
    KILL_CREDIT_DH_ARTIFACT_CHOSEN = 105177,
};

class npc_altruis_sufferer_artifact : public CreatureScript
{
public:
    npc_altruis_sufferer_artifact() : CreatureScript("npc_altruis_sufferer_artifact") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_THE_POWER_TO_SURVIVE)
        {
            player->CastSpell(player, 201092, true); // Display player spec choice
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->HasQuest(QUEST_THE_POWER_TO_SURVIVE) &&
            player->GetQuestStatus(QUEST_THE_POWER_TO_SURVIVE) != QUEST_STATUS_REWARDED) {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I would like to review weapons we might pursue.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
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
                player->CastSpell(player, 201092, true); // Display player spec choice
                CloseGossipMenuFor(player);
                break;
        }
        return true;
    }
};

class PlayerScript_DH_artifact_choice : public PlayerScript
{
public:
    PlayerScript_DH_artifact_choice() : PlayerScript("PlayerScript_DH_artifact_choice") {}

    void OnCompleteQuestChoice(Player* player, uint32 choiceID, uint32 responseID)
    {
        if (choiceID != PLAYER_CHOICE_DH_ARTIFACT_SELECTION)
            return;

        switch (responseID)
        {
            case PLAYER_CHOICE_DH_HAVOC:
            {
                player->RemoveRewardedQuest(QUEST_ALDRACHI_WARBLADES_CHOSEN);
                player->KilledMonsterCredit(KILL_CREDIT_DH_ARTIFACT_CHOSEN);

                if (ChrSpecializationEntry const* spec = sChrSpecializationStore.AssertEntry(577))
                    player->ActivateTalentGroup(spec);

                break;
            }   
            case PLAYER_CHOICE_DH_VENGEANCE:
            {
                player->RemoveRewardedQuest(QUEST_TWINBLADES_OFTHE_DECEIVER_CHOSEN);
                player->KilledMonsterCredit(KILL_CREDIT_DH_ARTIFACT_CHOSEN);

                if (ChrSpecializationEntry const* spec = sChrSpecializationStore.AssertEntry(581))
                    player->ActivateTalentGroup(spec);

                break;
            }   
            default:
                break;
        }
    }
};

#define GOSSIP_HELLO_ALTURAS1 "There's no time to explain. Let us inside the hold, warden."
#define GOSSIP_HELLO_ALTURAS2 "Let us inside or I'll show you the difference."
#define GOSSIP_HELLO_ALTURAS3 "Do you want to find out?"
#define GOSSIP_HELLO_ALTURAS4 "What do you have to lose either way?"
class npc_warden_alturas : public CreatureScript
{
public:
    npc_warden_alturas() : CreatureScript("npc_warden_alturas") { }

    enum {
        TEXT_ALLOW_ENTER = 3,
        EVENT_TELEPORT_VIOLETHOLD = 11,
        EVENT_START_MOVE = 12,
        EVENT_MOVE_TO_GATES = 13,
        EVENT_TELEPORT = 14,
        EVENT_RESET = 15,
        DATA_START_EVENT = 21,
    };

    bool _diffsPicked = false;
    bool _noTimePicked = false;
    
    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (player->GetQuestStatus(41121) == QUEST_STATUS_INCOMPLETE && !_diffsPicked && !_noTimePicked)
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_HELLO_ALTURAS1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        if (player->GetQuestStatus(41121) == QUEST_STATUS_INCOMPLETE && !_diffsPicked)
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_HELLO_ALTURAS2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

        if (player->GetQuestStatus(41121) == QUEST_STATUS_INCOMPLETE && _diffsPicked)
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_HELLO_ALTURAS3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

        if (player->GetQuestStatus(41121) == QUEST_STATUS_INCOMPLETE && _diffsPicked)
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_HELLO_ALTURAS4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);

        SendGossipMenuFor(player, player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        if (!player)
            return false;

        player->PlayerTalkClass->ClearMenus();

        if (action == GOSSIP_ACTION_INFO_DEF + 1)
        {
            _noTimePicked = true;
            creature->AI()->Talk(0);
            creature->SetStandState(UNIT_STAND_STATE_STAND);
            CloseGossipMenuFor(player);
        }

        if (action == GOSSIP_ACTION_INFO_DEF + 2)
        {
            _diffsPicked = true;
            creature->SetStandState(UNIT_STAND_STATE_STAND);
            CloseGossipMenuFor(player);
        }

        if (action == GOSSIP_ACTION_INFO_DEF + 3)
        {
            creature->AI()->Talk(2);
            player->KilledMonsterCredit(96313);
            creature->AI()->SetData(DATA_START_EVENT, DATA_START_EVENT);
            CloseGossipMenuFor(player);
        }

        if (action == GOSSIP_ACTION_INFO_DEF + 4)
        {
            creature->AI()->Talk(1);
            player->KilledMonsterCredit(96313);
            creature->AI()->SetData(DATA_START_EVENT, DATA_START_EVENT);
            CloseGossipMenuFor(player);
        }

        return true;
    }

    bool OnQuestAccept(Player* /*player*/, Creature* /*creature*/, Quest const* quest) override
    {
        if (quest->GetQuestId() == 41121)
        {
            _diffsPicked = false;
            _noTimePicked = false;
        }

        return true;
    }

    struct npc_warden_alturas_AI : public ScriptedAI
    {
        npc_warden_alturas_AI(Creature* creature) : ScriptedAI(creature) {
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
                case EVENT_TELEPORT_VIOLETHOLD: {
                    Talk(TEXT_ALLOW_ENTER, me->GetOwner());
                    _events.ScheduleEvent(EVENT_START_MOVE, 4000);
                    break;
                }   
                case EVENT_START_MOVE: {
                    _events.ScheduleEvent(EVENT_MOVE_TO_GATES, 2000);
                    me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    me->SetOrientation(4.0119f);
                    break;
                }
                case EVENT_MOVE_TO_GATES: {
                    _events.ScheduleEvent(EVENT_TELEPORT, 3000);
                    me->GetMotionMaster()->MovePoint(2, -958.91f, 4326.97f, 740.20f);
                    break;
                }
                case EVENT_TELEPORT: {
                    _events.ScheduleEvent(EVENT_RESET, 1500);
                    me->CastSpell(me, 52096, true); // cosmetic-teleport-effect
                    break;
                }
                case EVENT_RESET: {
                    me->AI()->Reset();
                    _events.CancelEvent(EVENT_TELEPORT_VIOLETHOLD);
                    _events.CancelEvent(EVENT_START_MOVE);
                    _events.CancelEvent(EVENT_MOVE_TO_GATES);
                    _events.CancelEvent(EVENT_TELEPORT);
                    me->DespawnOrUnsummon(5000, Seconds(3));
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
            switch (id)
            {
                case DATA_START_EVENT:
                {
                    _events.ScheduleEvent(EVENT_TELEPORT_VIOLETHOLD, 3000);
                    break;
                }
            }
        }

    private:
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_warden_alturas_AI(creature);
    }
};

class go_violethold_entrance_portal : public GameObjectScript
{
public:
    go_violethold_entrance_portal() : GameObjectScript("go_violethold_entrance_portal")
    {
        checkTimer = 1000;
        giveKillCredit = 1000;
    }

    uint32 checkTimer;
    uint32 giveKillCredit;

    void OnUpdate(GameObject* p_Object, uint32 diff) override
    {
        if (checkTimer < diff)
        {
            checkTimer -= diff;
            return;
        }

        checkTimer = 1000;
        giveKillCredit = 1000;

        std::list<Player*> playerList;
        GetPlayerListInGrid(playerList, p_Object, 2.0f);

        for (Player* player : playerList)
        {
            if (player->GetQuestStatus(41121) == QUEST_STATUS_INCOMPLETE)
            {
                player->KilledMonsterCredit(95731, ObjectGuid::Empty);
                player->TeleportTo(1494, 1293.185f, -262.720f, 44.364f, 0.307976f);
            }
        }
    }
};

// 86563
class npc_archmage_khadgar_86563 : public CreatureScript
{
public:
    npc_archmage_khadgar_86563() : CreatureScript("npc_archmage_khadgar_86563") { }

    enum eNpc
    {   
        QUEST_DOWN_TO_AZSUNA = 41220,
        SPELL_TAXI_DALARAN_AZSUNA_ALLIANCE = 205098,
        SPELL_TAXI_DALARAN_AZSUNA_HORDE = 205203,
    };

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 /*action*/) override
    {
        if (player->HasQuest(QUEST_DOWN_TO_AZSUNA) || player->GetQuestStatus(QUEST_DOWN_TO_AZSUNA) == QUEST_STATUS_INCOMPLETE)
            player->CastSpell(player, player->IsInAlliance() ? SPELL_TAXI_DALARAN_AZSUNA_ALLIANCE : SPELL_TAXI_DALARAN_AZSUNA_HORDE, true); // KillCredit & SendTaxi

        return true;
    }

    bool OnQuestAccept(Player* /*player*/, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_DOWN_TO_AZSUNA)
        {
            creature->AI()->Talk(1);
        }
        return true;
    }
};

// npc 90417 for the quest 41804 'Ask and You Shall Receive'
class npc_archmage_khadgar_90417 : public CreatureScript {
public:
    npc_archmage_khadgar_90417() : CreatureScript("npc_archmage_khadgar_90417") { }

    enum Khadgar {
        QUEST_ASK_AND_YOU_SHALL_RECEIVE = 41804,
        QUEST_RETURN_TO_JACE = 41806,
        SPELL_CRYSTALLIZED_SOUL = 208510,
        PHASE_NONE = 0,
        PHASE_CONTINUE = -1,
        DATA_EVENT_STARTER_GUID = 0,
        SAY_KHADGAR_1 = 3,
        SAY_KHADGAR_2 = 4,
        SAY_KHADGAR_3 = 5,
        SAY_KHADGAR_4 = 6,
        SAY_KHADGAR_5 = 7,
        SAY_KHADGAR_6 = 8,
        SAY_KHADGAR_7 = 9,
        SAY_KHADGAR_8 = 10,
        WP_START = 1,
        WP_START_WALK = 4,
        WP_IN_THE_MIDDLE = 10,
        WP_AT_FIRST_CHEST = 11,
        WP_AT_SECOND_CHEST = 15,
        WP_AT_HOME = 21,
        PHASE_WAIT_IN_MIDDLE = 1,
        PHASE_SEEK_IN_FIRST_CHEST_1 = 2,
        PHASE_SEEK_IN_FIRST_CHEST_2 = 3,
        PHASE_SEEK_IN_FIRST_CHEST_3 = 4,
        PHASE_SEEK_IN_SECOND_CHEST_1 = 5,
        PHASE_SEEK_IN_SECOND_CHEST_2 = 6,
        PHASE_SEEK_IN_SECOND_CHEST_3 = 7,
        PHASE_SEEK_IN_SECOND_CHEST_4 = 8,
        PHASE_MOVE_HOME = 9,
        PHASE_DESPAWN = 10,
        GO_CRYSTALLIZED_SOUL = 248521,
    };

    struct npc_archmage_khadgar_90417_AI : public npc_escortAI
    {
        npc_archmage_khadgar_90417_AI(Creature* creature) : npc_escortAI(creature)
        {
            Initialize();
        }

        void Initialize()
        {
            _phase = PHASE_NONE;
            _moveTimer = 0;
        }

        void sQuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_ASK_AND_YOU_SHALL_RECEIVE)
            {
                SetGUID(player->GetGUID(), DATA_EVENT_STARTER_GUID);
                Talk(SAY_KHADGAR_1);
                Start(false, true, player->GetGUID(), quest);
            }
            if (quest->GetQuestId() == QUEST_RETURN_TO_JACE)
            {
                Talk(SAY_KHADGAR_8);
            }
        }

        ObjectGuid GetGUID(int32 type) const override
        {
            if (type == DATA_EVENT_STARTER_GUID)
                return _eventStarterGuid;

            return ObjectGuid::Empty;
        }

        void SetGUID(ObjectGuid guid, int32 type) override
        {
            switch (type)
            {
            case DATA_EVENT_STARTER_GUID:
                _eventStarterGuid = guid;
                break;
            default:
                break;
            }
        }

        void Reset() override
        {
            me->SetWalk(false);
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
                    case PHASE_WAIT_IN_MIDDLE:
                        _moveTimer = 0 * IN_MILLISECONDS;
                        _phase = PHASE_CONTINUE;
                        break;
                    case PHASE_SEEK_IN_FIRST_CHEST_1:
                        me->HandleEmoteCommand(EMOTE_STATE_USESTANDING);
                        Talk(SAY_KHADGAR_3);
                        _moveTimer = 7 * IN_MILLISECONDS;
                        _phase = PHASE_SEEK_IN_FIRST_CHEST_2;
                        break;
                    case PHASE_SEEK_IN_FIRST_CHEST_2:
                        me->HandleEmoteCommand(EMOTE_STATE_NONE);
                        me->SetFacingTo(5.1576f);
                        Talk(SAY_KHADGAR_4);
                        _moveTimer = 3 * IN_MILLISECONDS;
                        _phase = PHASE_SEEK_IN_FIRST_CHEST_3;
                        break;
                    case PHASE_SEEK_IN_FIRST_CHEST_3:
                        SetEscortPaused(false);
                        _moveTimer = 0 * IN_MILLISECONDS;
                        _phase = PHASE_NONE;
                        break;
                    case PHASE_SEEK_IN_SECOND_CHEST_1:
                        me->HandleEmoteCommand(EMOTE_STATE_USESTANDING);
                        Talk(SAY_KHADGAR_5);
                        _moveTimer = 7 * IN_MILLISECONDS;
                        _phase = PHASE_SEEK_IN_SECOND_CHEST_2;
                        break;
                    case PHASE_SEEK_IN_SECOND_CHEST_2:
                        me->HandleEmoteCommand(EMOTE_STATE_NONE);
                        Talk(SAY_KHADGAR_6);
                        _moveTimer = 6 * IN_MILLISECONDS;
                        _phase = PHASE_SEEK_IN_SECOND_CHEST_3;
                        break;
                    case PHASE_SEEK_IN_SECOND_CHEST_3:
                        me->CastSpell(me, SPELL_CRYSTALLIZED_SOUL);
                        me->SummonGameObject(GO_CRYSTALLIZED_SOUL, -829.154f, 4653.472f, 768.774f, 1.46863f, QuaternionData(), 60);
                        if (Player* player = ObjectAccessor::GetPlayer(*me, _eventStarterGuid))
                        {
                            player->KilledMonsterCredit(90417, ObjectGuid::Empty);
                        }
                        me->SetFacingTo(1.9587f);
                        Talk(SAY_KHADGAR_7);
                        _moveTimer = 5 * IN_MILLISECONDS;
                        _phase = PHASE_SEEK_IN_SECOND_CHEST_4;
                        break;
                    case PHASE_SEEK_IN_SECOND_CHEST_4:
                        SetEscortPaused(false);
                        _moveTimer = 0 * IN_MILLISECONDS;
                        _phase = PHASE_NONE;
                        break;
                    case PHASE_DESPAWN:
                        me->DespawnOrUnsummon(5000, Seconds(1));
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
            case WP_START_WALK:
                _moveTimer = 0 * IN_MILLISECONDS;
                _phase = PHASE_NONE;
                me->SetWalk(true);
                me->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);
                break;
            case WP_IN_THE_MIDDLE:
                SetEscortPaused(true);
                me->SetFacingTo(2.3671f);
                Talk(SAY_KHADGAR_2);
                _moveTimer = 5 * IN_MILLISECONDS;
                _phase = PHASE_WAIT_IN_MIDDLE;
                break;
            case WP_AT_FIRST_CHEST:
                SetEscortPaused(true);
                me->SetFacingTo(3.6316f);
                _moveTimer = 0.2 * IN_MILLISECONDS;
                _phase = PHASE_SEEK_IN_FIRST_CHEST_1;
                break;
            case WP_AT_SECOND_CHEST:
                SetEscortPaused(true);
                _moveTimer = 0.2 * IN_MILLISECONDS;
                _phase = PHASE_SEEK_IN_SECOND_CHEST_1;
                break;
            case WP_AT_HOME:
                _moveTimer = 0.2 * IN_MILLISECONDS;
                _phase = PHASE_DESPAWN;
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
        return new npc_archmage_khadgar_90417_AI(creature);
    }
};

enum eQuest41807 {
    QUEST_ESTABLISHING_A_CONNECTION = 41807,
    KILLCREDIT_ACTIVATE_COMMUNICATOR = 104907,
    KILLCREDIT_REPORT_RECEIVED = 104908,
    DATA_COMMUNICATOR_ACTIVATED = 21,
    DATA_REPORT_RECEIVED = 22,
    DATA_GARBLED_POSITION = 23,
    DATA_GARBLED_INCOMING = 24,
    SPELL_SUMMON_ALLARI = 207795,
};

// npc 99262 for the quest 41807 'Establishing A Connection'
class npc_jace_darkweaver_99262 : public CreatureScript
{
public:
    npc_jace_darkweaver_99262() : CreatureScript("npc_jace_darkweaver_99262") { }

    enum eJace {
        SAY_JACE_1 = 0,
        SAY_JACE_2 = 1,
        SAY_ALTRUIS_1 = 0,
    };

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) override
    {
        if (quest->GetQuestId() == QUEST_ESTABLISHING_A_CONNECTION)
            if (Creature* altruis = creature->FindNearestCreature(99254, 15.0f))
                altruis->AI()->Talk(SAY_ALTRUIS_1);
        return true;
    }

    struct npc_jace_darkweaver_99262_AI : public ScriptedAI
    {
        npc_jace_darkweaver_99262_AI(Creature* creature) : ScriptedAI(creature) {
            me->SetReactState(REACT_PASSIVE);
        }

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_COMMUNICATOR_ACTIVATED:
                Talk(SAY_JACE_1);
                break;
            case DATA_REPORT_RECEIVED:
                Talk(SAY_JACE_2);
                break;
            }
        }

    private:
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_jace_darkweaver_99262_AI(creature);
    }
};

// gameobject 251528 for the quest 41807 'Establishing A Connection'
class go_legion_communicator : public GameObjectScript
{
public:
    go_legion_communicator() : GameObjectScript("go_legion_communicator") { }

    enum eAllari {
        EVENT_TALK_JACE_00 = 1,
        EVENT_TALK_JACE_01 = 2,
        EVENT_TALK_PART_00 = 3,
        EVENT_TALK_PART_01 = 4,
        EVENT_GIVE_CREDIT = 5,
        NPC_ALLARI_SOULEATER = 104909,
    };

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (player->HasQuest(QUEST_ESTABLISHING_A_CONNECTION) &&
            !player->GetQuestObjectiveData(QUEST_ESTABLISHING_A_CONNECTION, 0))
        {
            Position allariPosition = { go->GetPositionX(), go->GetPositionY(), 747.019f, 0.385333f };
            player->SummonCreature(NPC_ALLARI_SOULEATER, allariPosition, TEMPSUMMON_TIMED_DESPAWN, 30000);
        }

        return false;
    }

    struct go_legion_communicator_AI : public GameObjectAI
    {
        go_legion_communicator_AI(GameObject* go) : GameObjectAI(go) { }

        EventMap    _events;
        ObjectGuid  _playerGUID;
        ObjectGuid  _allariGUID;
        ObjectGuid  _jaceGUID;

        void Reset() override
        {
            _playerGUID = ObjectGuid::Empty;
            _allariGUID = ObjectGuid::Empty;
            _jaceGUID = ObjectGuid::Empty;
        }

        void OnStateChanged(uint32 /*state*/, Unit* unit) override
        {
            if (unit)
                if (unit->ToPlayer()->HasQuest(QUEST_ESTABLISHING_A_CONNECTION) &&
                    !unit->ToPlayer()->GetQuestObjectiveData(QUEST_ESTABLISHING_A_CONNECTION, 0))
                    if (Creature* allari = go->FindNearestCreature(104909, 3.0f))
                        if (Creature* jace = go->FindNearestCreature(99262, 5.0f))
                            if (Player* player = unit->ToPlayer())
                            {
                                _playerGUID = player->GetGUID();
                                _allariGUID = allari->GetGUID();
                                _jaceGUID = jace->GetGUID();
                                _events.ScheduleEvent(EVENT_TALK_JACE_00, 1000);
                                _events.RescheduleEvent(EVENT_TALK_PART_00, 7000);
                            }
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_JACE_00:
                {
                    if (Creature* jace = ObjectAccessor::GetCreature(*go, _jaceGUID))
                        if (Player* player = ObjectAccessor::GetPlayer(*go, _playerGUID))
                        {
                            jace->AI()->SetData(DATA_COMMUNICATOR_ACTIVATED, DATA_COMMUNICATOR_ACTIVATED);
                            player->KilledMonsterCredit(KILLCREDIT_ACTIVATE_COMMUNICATOR, ObjectGuid::Empty);
                        }   
                    break;
                }
                case EVENT_TALK_PART_00:
                {
                    if (Creature* allari = ObjectAccessor::GetCreature(*go, _allariGUID))
                        if (Player* player = ObjectAccessor::GetPlayer(*go, _playerGUID))
                            allari->AI()->SetData(DATA_GARBLED_POSITION, DATA_GARBLED_POSITION);
                    _events.ScheduleEvent(EVENT_TALK_PART_01, 6000);
                    break;
                }
                case EVENT_TALK_PART_01:
                {
                    if (Creature* allari = ObjectAccessor::GetCreature(*go, _allariGUID))
                        if (Player* player = ObjectAccessor::GetPlayer(*go, _playerGUID))
                            allari->AI()->SetData(DATA_GARBLED_INCOMING, DATA_GARBLED_INCOMING);
                    _events.ScheduleEvent(EVENT_GIVE_CREDIT, 2000);
                    break;
                }
                case EVENT_GIVE_CREDIT:
                {
                    if (Creature* allari = ObjectAccessor::GetCreature(*go, _allariGUID))
                        if (Player* player = ObjectAccessor::GetPlayer(*go, _playerGUID))
                        {
                            player->KilledMonsterCredit(KILLCREDIT_REPORT_RECEIVED, ObjectGuid::Empty);
                            allari->DespawnOrUnsummon(Seconds(2));
                        }
                    _events.ScheduleEvent(EVENT_TALK_JACE_01, 2000);
                    break;
                }
                case EVENT_TALK_JACE_01:
                {
                    if (Creature* jace = ObjectAccessor::GetCreature(*go, _jaceGUID))
                        if (Player* player = ObjectAccessor::GetPlayer(*go, _playerGUID))
                            jace->AI()->SetData(DATA_REPORT_RECEIVED, DATA_REPORT_RECEIVED);
                    break;
                }
                default:
                    break;
                }                
            }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_legion_communicator_AI(go);
    }
};

// npc 104909 for the quest 41807 'Establishing A Connection'
class npc_allari_souleater_104909 : public CreatureScript
{
public:
    npc_allari_souleater_104909() : CreatureScript("npc_allari_souleater_104909") { }

    enum eAllari {
        SAY_ALLARI_1 = 0,
        SAY_ALLARI_2 = 1,
    };

    struct npc_allari_souleater_104909_AI : public ScriptedAI
    {
        npc_allari_souleater_104909_AI(Creature* creature) : ScriptedAI(creature) {
            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, Emote::EMOTE_STATE_READY2H);
        }

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_GARBLED_POSITION:
                Talk(SAY_ALLARI_1);
                break;
            case DATA_GARBLED_INCOMING:
                Talk(SAY_ALLARI_2);
                break;
            }
        }

    private:
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_allari_souleater_104909_AI(creature);
    }
};

struct npc_illidari_fel_bat_94324 : public ScriptedAI
{
    npc_illidari_fel_bat_94324(Creature* creature) : ScriptedAI(creature)
    {
        me->SetAIAnimKitId(0);
    }

    enum eQuest {
        QUEST_THE_HUNT_1 = 39247,
        QUEST_THE_HUNT_2 = 41119,
        QUEST_VENGEANCE_WILL_BE_OURS_1 = 40249,
        QUEST_VENGEANCE_WILL_BE_OURS_2 = 41863,
    };

    void OnSpellClick(Unit* clicker, bool& /*result*/)
    {
        if (Player* player = clicker->ToPlayer())
        {
            if (player->HasQuest(QUEST_THE_HUNT_1) || player->HasQuest(QUEST_THE_HUNT_2))
            {
                me->SetAIAnimKitId(4061);
                player->KilledMonsterCredit(94321); // 52391
                player->TeleportTo(1498, Position(1263.69f, 5236.659f, 93.531f, 2.73693f));
            }

            if (player->HasQuest(QUEST_VENGEANCE_WILL_BE_OURS_1) || player->HasQuest(QUEST_VENGEANCE_WILL_BE_OURS_2))
            {
                me->SetAIAnimKitId(4061);
                player->KilledMonsterCredit(99250);
                player->TeleportTo(1500, Position(-2379.679f, 174.2f, 3.5625f, 3.733872f));
            }
        }
    }
};


void AddSC_dalaran_legion()
{
    new OnLegionArrival();
    new On110Arrival();

    RegisterSpellScript(spell_dalaran_teleportation);
    new npc_dalaran_karazhan_khadgar();
    new scene_dalaran_kharazan_teleportion();
    new zone_legion_dalaran_underbelly();
    new npc_hunter_talua();
    new npc_great_eagle();
    // new player_artifact_choice();
    new npc_warden_alturas();
    new go_violethold_entrance_portal();
    new PlayerScript_DH_artifact_choice();
    new PlayerScript_summon_korvas_bloodthorn();
    new npc_korvas_bloodthorn_summon();
    new npc_altruis_sufferer_artifact();
    new npc_archmage_khadgar_86563();
    new npc_archmage_khadgar_90417();
    new npc_jace_darkweaver_99262();
    new go_legion_communicator();
    new npc_allari_souleater_104909();
    RegisterCreatureAI(npc_illidari_fel_bat_94324);
}
