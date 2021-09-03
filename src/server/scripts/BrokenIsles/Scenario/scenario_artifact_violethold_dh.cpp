/*
 * Copyright (C) 2019-2018 5CentsCore <https://github.com/mnahirnyy/5centsCore>
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

#include "Creature.h"
#include "GameObject.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "SceneMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellMgr.h"
#include "Scenario.h"
#include "InstanceScenario.h"
#include "TemporarySummon.h"
#include "PhasingHandler.h"
#include "Log.h"

enum DataTypes
{
    DATA_MAX_ENCOUNTERS_DH = 1,
    NPC_ALTURAS = 99473,
    NPC_KAYN = 94902,
    NPC_ALTRUIS = 103156,
    NPC_TALDATH = 94731,
    NPC_ELEMENTAL = 96308,
    NPC_VH_GUARD = 96312,
    NPC_GBUNNY = 54638,
    NORMAL_PHASE = 169,
    DATA_VIOLET_HOLD = 0,
    DATA_STAGE_1 = 1,
    DATA_ALTURAS_START_EVENT = 27,
    QUEST_BY_ANY_MEANS_K = 39051,
    QUEST_BY_ANY_MEANS_A = 41121,
    SPELL_ARCANE_CHANNEL = 190953,
    SPELL_TELEPORT_COSMETIC = 195453,
    SPELL_ARCANE_WALL = 234577,
    SPELL_KAYN_CONVERSATION_1093 = 201103,
    SPELL_KAYN_CONVERSATION_1096 = 201105,
    SPELL_KAYN_CONVERSATION_1097 = 201106,
    SPELL_ALTRUIS_CONVERSATION_1088 = 201029,
    SPELL_ALTRUIS_CONVERSATION_1089 = 201034,
    SPELL_ALTRUIS_CONVERSATION_1095 = 201104,
};

struct scenario_artifact_violethold_dh : public InstanceScript
{
    scenario_artifact_violethold_dh(InstanceMap* map) : InstanceScript(map) { }

    void Initialize() override
    {
        SetBossNumber(DATA_MAX_ENCOUNTERS_DH);
        SetData(DATA_VIOLET_HOLD, NOT_STARTED);
        for (uint8 i = 1; i <= 7; ++i)
            SetData(i, NOT_STARTED);
        StepID = DATA_STAGE_1;
        isComplete = false;
        _playerGUID = ObjectGuid::Empty;
        _taldathGUID = ObjectGuid::Empty;
        _kaynGUID = ObjectGuid::Empty;
        _altruisGUID = ObjectGuid::Empty;
        _alturasGUID = ObjectGuid::Empty;
        _elementalGUID = ObjectGuid::Empty;
    }

    void OnPlayerEnter(Player* player) override
    {
        InstanceScript::OnPlayerEnter(player);

        if (player->GetMapId() == 1494) {
            _playerGUID = player->GetGUID();
            PhasingHandler::AddPhase(player, NORMAL_PHASE, true);
        }

        SummonAlturasAndOthers(player);
    }

    void OnCreatureCreate(Creature* creature) override
    {
        InstanceScript::OnCreatureCreate(creature);

        switch (creature->GetEntry())
        {
        case NPC_ALTURAS:
            _alturasGUID = creature->GetGUID();
            break;
        case NPC_KAYN:
            _kaynGUID = creature->GetGUID();
            break;
        case NPC_ALTRUIS:
            _altruisGUID = creature->GetGUID();
            break;
        case NPC_TALDATH:
            _taldathGUID = creature->GetGUID();
            break;
        case NPC_ELEMENTAL:
            _elementalGUID = creature->GetGUID();
            break;
        default:
            break;
        }
    }

    void OnGameObjectCreate(GameObject* go) override
    {
        InstanceScript::OnGameObjectCreate(go);
    }

    void NextStep()
    {
        if (StepID == DATA_STAGE_1)
        {
            if (Scenario* scenario = instance->GetInstanceScenario())
            {
                if (!isComplete) {
                    scenario->CompleteCurrStep();
                }
                else {
                    scenario->CompleteScenario(); // COMPLETE SCENARIO
                }
            }
        }
    }

    void SetData(uint32 type, uint32 data) override
    {
        InstanceScript::SetData(type, data);

        if (data == NOT_STARTED)
            return;

        if (type == DATA_STAGE_1 && data == DONE)
        {
            isComplete = true;
            NextStep();
        }
    }

    void SummonAlturasAndOthers(Player* player)
    {
        if (Creature* alturas = instance->GetCreature(_alturasGUID))
            alturas->Respawn();
        if (Creature* protector = instance->GetCreature(_elementalGUID))
            protector->Respawn();
        if (Creature* taldath = instance->GetCreature(_taldathGUID))
            taldath->Respawn();

        if (TempSummon* alturas = instance->SummonCreature(NPC_ALTURAS, Position(1290.730f, -264.305f, 44.364f, 0.06528f)))
        {
            _alturasGUID = alturas->GetGUID();
            /* Start Event */
            alturas->AI()->SetData(DATA_ALTURAS_START_EVENT, DATA_ALTURAS_START_EVENT);
        }

        if (TempSummon* elemental = instance->SummonCreature(NPC_ELEMENTAL, Position(1315.67f, -262.983f, 44.1398f, 0.055067f)))
            _elementalGUID = elemental->GetGUID();

        if (TempSummon* taldath = instance->SummonCreature(NPC_TALDATH, Position(1426.02f, -263.519f, 52.4466f, 3.04486f)))
            _taldathGUID = taldath->GetGUID();

        /* conditional summon */
        if (player->HasQuest(QUEST_BY_ANY_MEANS_K))
            if (TempSummon* kayn = instance->SummonCreature(NPC_KAYN, Position(1300.655f, -259.887f, 44.272f, 0.05115f)))
                _kaynGUID = kayn->GetGUID();

        if (player->HasQuest(QUEST_BY_ANY_MEANS_A))
            if (TempSummon* altruis = instance->SummonCreature(NPC_ALTRUIS, Position(1300.655f, -259.887f, 44.272f, 0.05115f)))
                _altruisGUID = altruis->GetGUID();
    }

private:
    EventMap events;
    uint8 StepID;
    bool isComplete;
    ObjectGuid _playerGUID;
    ObjectGuid _taldathGUID;
    ObjectGuid _kaynGUID;
    ObjectGuid _altruisGUID;
    ObjectGuid _alturasGUID;
    ObjectGuid _elementalGUID;
};

class go_violethold_exit_portal : public GameObjectScript
{
public:
    go_violethold_exit_portal() : GameObjectScript("go_violethold_exit_portal")
    {
        checkTimer = 1000;
    }

    uint32 checkTimer;

    void OnUpdate(GameObject* p_Object, uint32 diff) override
    {
        if (checkTimer < diff)
        {
            checkTimer -= diff;
            return;
        }

        checkTimer = 1000;

        std::list<Player*> playerList;
        GetPlayerListInGrid(playerList, p_Object, 2.0f);

        for (Player* player : playerList)
            player->TeleportTo(1220, -953.287f, 4334.03f, 740.184f, 0.307976f);
    }
};

class npc_warden_alturas_vh : public CreatureScript
{
public:
    npc_warden_alturas_vh() : CreatureScript("npc_warden_alturas_vh") { }

    enum {
        TEXT_LOWER_BARRIER = 0,
        TEXT_OPEN_CELL = 1,
        TEXT_MEET_TALDATH = 2,
        TEXT_WERE_NEVER_HERE = 3,
        EVENT_MOVE_TO_CIRCLE = 11,
        EVENT_ASK_TO_LOWER_BARRIER = 12,
        EVENT_MOVE_FURTHER = 13,
        EVENT_MOVE_FURTHER_1 = 14,
        EVENT_MOVE_FURTHER_2 = 15,
        EVENT_MOVE_FURTHER_3 = 16,
        EVENT_MOVE_FURTHER_4 = 17,
        EVENT_MOVE_FURTHER_5 = 18,
        EVENT_MEET_TALDATH = 19,
        EVENT_SAY_GOODBYE = 20,
        EVENT_CAST_TELEPORT = 21,
    };

    struct npc_warden_alturas_vh_AI : public ScriptedAI
    {
        npc_warden_alturas_vh_AI(Creature* creature) : ScriptedAI(creature) {
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
                case EVENT_MOVE_TO_CIRCLE: {
                    _events.ScheduleEvent(EVENT_ASK_TO_LOWER_BARRIER, 7000);
                    me->SetWalk(true);
                    me->GetMotionMaster()->MovePoint(1, 1305.759f, -263.837f, 44.169f);
                    break;
                }
                case EVENT_ASK_TO_LOWER_BARRIER: {
                    _events.ScheduleEvent(EVENT_MOVE_FURTHER, 8000);
                    Talk(TEXT_LOWER_BARRIER, me->GetOwner());
                    if (Creature* elem = me->FindNearestCreature(NPC_ELEMENTAL, me->GetVisibilityRange(), true)) {
                        elem->GetScheduler().Schedule(Seconds(3), [this](TaskContext context)
                        {
                            Creature* protector = GetContextCreature();
                            protector->CastSpell(protector, SPELL_ARCANE_CHANNEL, true);

                            std::list<Creature*> bunnies;
                            me->GetCreatureListWithEntryInGrid(bunnies, NPC_GBUNNY, 25.0f);
                            for (Creature* bunny : bunnies)
                                bunny->RemoveAurasDueToSpell(SPELL_ARCANE_WALL);

                            std::list<Creature*> guards;
                            me->GetCreatureListWithEntryInGrid(guards, NPC_VH_GUARD, 25.0f);
                            for (Creature* guard : guards)
                                guard->GetMotionMaster()->MovePoint(1, 1270.492f, -263.185f, 44.364f, true);
                        }).Schedule(Seconds(6), [this](TaskContext context)
                        {
                            Creature* protector = GetContextCreature();
                            protector->KillSelf();

                            std::list<Creature*> guards;
                            me->GetCreatureListWithEntryInGrid(guards, NPC_VH_GUARD, 25.0f);
                            for (Creature* guard : guards)
                                guard->DespawnOrUnsummon();
                        });
                    }   
                    me->GetMotionMaster()->MovePoint(6, 1401.761f, -245.726f, 52.420f);
                    break;
                }
                case EVENT_MOVE_FURTHER: {
                    _events.ScheduleEvent(EVENT_MOVE_FURTHER_1, 5000);
                    Talk(TEXT_OPEN_CELL, me->GetOwner());
                    me->SetWalk(false);
                    me->GetMotionMaster()->MovePoint(2, 1337.645f, -263.426f, 38.656f);
                    break;
                }
                case EVENT_MOVE_FURTHER_1: {
                    _events.ScheduleEvent(EVENT_MOVE_FURTHER_2, 6000);
                    me->SetOrientation(0.01502f);
                    me->GetMotionMaster()->MovePoint(3, 1382.611f, -263.272f, 43.333f);
                    if (Player* nearestPlayer = me->SelectNearestPlayer(60.0f)) {
                        if (nearestPlayer->HasQuest(QUEST_BY_ANY_MEANS_A))
                            nearestPlayer->CastSpell(nearestPlayer, SPELL_ALTRUIS_CONVERSATION_1088, true);
                        if (nearestPlayer->HasQuest(QUEST_BY_ANY_MEANS_K))
                            nearestPlayer->CastSpell(nearestPlayer, SPELL_KAYN_CONVERSATION_1093, true);
                    }   
                    break;
                }
                case EVENT_MOVE_FURTHER_2: {
                    _events.ScheduleEvent(EVENT_MOVE_FURTHER_3, 2000);
                    me->GetMotionMaster()->MovePoint(4, 1390.999f, -250.864f, 48.092f);
                    break;
                }
                case EVENT_MOVE_FURTHER_3: {
                    _events.ScheduleEvent(EVENT_MOVE_FURTHER_4, 1500);
                    me->GetMotionMaster()->MovePoint(5, 1399.311f, -246.174f, 52.416f);
                    break;
                }
                case EVENT_MOVE_FURTHER_4: {
                    _events.ScheduleEvent(EVENT_MOVE_FURTHER_5, 1000);
                    if (Creature* taldath = me->FindNearestCreature(NPC_TALDATH, me->GetVisibilityRange(), true))
                        taldath->AI() ->SetData(12, 12);
                    me->GetMotionMaster()->MovePoint(6, 1401.761f, -245.726f, 52.420f);
                    break;
                }
                case EVENT_MOVE_FURTHER_5: {
                    _events.ScheduleEvent(EVENT_MEET_TALDATH, 9000);
                    me->SetWalk(true);
                    me->GetMotionMaster()->MovePoint(7, 1414.849f, -263.256f, 52.421f);
                    break;
                }
                case EVENT_MEET_TALDATH: {
                    _events.ScheduleEvent(EVENT_SAY_GOODBYE, 7000);
                    Talk(TEXT_MEET_TALDATH, me->GetOwner());
                    break;
                }
                case EVENT_SAY_GOODBYE: {
                    _events.ScheduleEvent(EVENT_CAST_TELEPORT, 2000);
                    Talk(TEXT_WERE_NEVER_HERE, me->GetOwner());
                    break;
                }
                case EVENT_CAST_TELEPORT: {
                    me->CastSpell(me, SPELL_TELEPORT_COSMETIC, true);
                    if (Creature* taldath = me->FindNearestCreature(NPC_TALDATH, me->GetVisibilityRange(), true))
                        taldath->AI()->SetData(13, 13);
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
            switch (id)
            {
                case DATA_ALTURAS_START_EVENT: {
                    _events.ScheduleEvent(EVENT_MOVE_TO_CIRCLE, 3000);
                    break;
                }
            }
        }

    private:
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_warden_alturas_vh_AI(creature);
    }
};

/**
* NPC: Taldath The Destroyer (94731)
* Abilities:
* - 199758 Burning Fel
* - 199828 Chaos Nova
* - 199836 Fel Spirit
*/
enum eTaldath
{
    EVENT_FELSTOMP = 5,
    EVENT_SLAGBLAST = 6,
    EVENT_BREATH_OF_FELFLAME = 7,
    EVENT_CONVERSATION_1 = 8,
    EVENT_CONVERSATION_2 = 9,
    DATA_SAY_EVENT = 12,
    DATA_START_EVENT = 13,
    SPELL_GRIP_OF_AGONY = 191030,
    SPELL_FELSTOMP = 202583,
    SPELL_FEL_SLAGBLAST = 202590,
    SPELL_BREATH_OF_FELFLAME = 202598,
};

class npc_violethold_taldath : public CreatureScript
{
public:
    npc_violethold_taldath() : CreatureScript("npc_violethold_taldath") { }

    struct npc_violethold_taldathAI : public ScriptedAI
    {
        npc_violethold_taldathAI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {   
            _phase1 = false;
            _phase2 = false;
            _phase3 = false;
            me->SetHealth(me->CountPctFromMaxHealth(27));
            me->setRegeneratingHealth(false);
        }

        void Reset() override
        {
            _events.Reset();
            Initialize();
            me->setActive(true);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            _events.ScheduleEvent(EVENT_FELSTOMP, 6000);
            _events.ScheduleEvent(EVENT_SLAGBLAST, 3000);
            _events.ScheduleEvent(EVENT_BREATH_OF_FELFLAME, 12000);
        }

        void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/) override
        {
            if (HealthBelowPct(22) && !_phase1) {
                Talk(2); // Varedis will hunt down every one of your disgusting ilk. Pity you won't around to witness it.
                _phase1 = true;
                _events.ScheduleEvent(EVENT_CONVERSATION_1, 6000);
            }

            if (HealthBelowPct(15) && !_phase2) {
                Talk(3); // Vermin! My lord wields power beyond your comprehension! He will end you!
                _phase2 = true;
            }

            if (HealthBelowPct(8) && !_phase3) {
                Talk(4); // Your efforts mean NOTHING! Soon all of Suramar will bow to my master's will!
                _phase3 = true;
                _events.ScheduleEvent(EVENT_CONVERSATION_2, 3000);
            }
        }

        void JustDied(Unit* /*killer*/) override
        {
            Talk(5); // The Twinblades... will be your end...

            std::list<Player*> players;
            me->GetPlayerListInGrid(players, 20.0f);
            for (Player* player : players)
                player->KilledMonsterCredit(me->GetEntry());
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {   
                case EVENT_FELSTOMP:
                    DoCast(SPELL_FELSTOMP);
                    _events.RescheduleEvent(EVENT_FELSTOMP, Seconds(12));
                    break;
                case EVENT_SLAGBLAST:
                    DoCast(SPELL_FEL_SLAGBLAST);
                    _events.RescheduleEvent(EVENT_SLAGBLAST, Seconds(4));
                    break;
                case EVENT_BREATH_OF_FELFLAME:
                    DoCast(SPELL_BREATH_OF_FELFLAME);
                    _events.RescheduleEvent(EVENT_BREATH_OF_FELFLAME, Seconds(19));
                    break;
                case EVENT_CONVERSATION_1:
                    if (Player* nearestPlayer = me->SelectNearestPlayer(50.0f)) {
                        if (nearestPlayer->HasQuest(QUEST_BY_ANY_MEANS_A))
                            nearestPlayer->CastSpell(nearestPlayer, SPELL_ALTRUIS_CONVERSATION_1089, false);
                        if (nearestPlayer->HasQuest(QUEST_BY_ANY_MEANS_K))
                            nearestPlayer->CastSpell(nearestPlayer, SPELL_KAYN_CONVERSATION_1096, false);
                    }
                    break;
                case EVENT_CONVERSATION_2:
                    if (Player* nearestPlayer = me->SelectNearestPlayer(50.0f)) {
                        if (nearestPlayer->HasQuest(QUEST_BY_ANY_MEANS_A))
                            nearestPlayer->CastSpell(nearestPlayer, SPELL_ALTRUIS_CONVERSATION_1095, false);
                        if (nearestPlayer->HasQuest(QUEST_BY_ANY_MEANS_K))
                            nearestPlayer->CastSpell(nearestPlayer, SPELL_KAYN_CONVERSATION_1097, false);
                    }
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }

        void DoActions(Creature* creature, int secondsDelay)
        {
            creature->GetScheduler().Schedule(Seconds(3), [this](TaskContext context)
            {
                Creature* taldath = GetContextCreature();
                if (Player* nearestPlayer = taldath->SelectNearestPlayer(50.0f))
                {
                    taldath->CastSpell(nearestPlayer, SPELL_GRIP_OF_AGONY, true);
                    nearestPlayer->NearTeleportTo(1362.98f, -263.514f, 38.6569f, 3.084f, true);
                    taldath->GetMotionMaster()->MoveJump(1362.98f, -263.514f, 38.6569f, 3.084f, 15.0f, 15.0f);
                }
            }).Schedule(Seconds(4), [this](TaskContext context)
            {
                Creature* taldath = GetContextCreature();
                me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                if (Player* nearestPlayer = taldath->SelectNearestPlayer(50.0f)) {
                    nearestPlayer->RemoveAurasDueToSpell(SPELL_GRIP_OF_AGONY);
                    taldath->Attack(nearestPlayer, true);
                }   
            });
        }

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_SAY_EVENT:
                Talk(0); // $p?! You would stand before me after so many of your kin have fallen? Release me now and I may yet spare you.
                break;
            case DATA_START_EVENT:
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                me->GetMotionMaster()->MovePoint(1, 1416.159f, -263.403f, 52.411f, false);
                Talk(1); // FOOL! You dare face me alone ?
                DoActions(me, 3000);
                break;
            default:
                break;
            }
        }

    private:
        EventMap _events;
        bool _phase1;
        bool _phase2;
        bool _phase3;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_violethold_taldathAI(creature);
    }
};

/*********/
/* AddSC */
/*********/
void AddSC_scenario_artifact_violethold_dh()
{
    RegisterInstanceScript(scenario_artifact_violethold_dh, 1494);
    new go_violethold_exit_portal();
    new npc_warden_alturas_vh();
    new npc_violethold_taldath();
}
