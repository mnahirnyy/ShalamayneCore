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
#include "MapManager.h"
#include "ObjectMgr.h"
#include "PhasingHandler.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "SpellScript.h"

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
}
