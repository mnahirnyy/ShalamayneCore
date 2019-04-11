/*
* Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>
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
SDName: Duskwood
SD%Complete: 100
SDComment: Quest Support:8735
SDCategory: Duskwood
EndScriptData */

#include "MotionMaster.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Spell.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "SpellInfo.h"
#include "SpellScript.h"
#include "TemporarySummon.h"

enum TwilightCorrupter
{
    NPC_TWILIGHT_CORRUPTER = 15625,
    YELL_TWILIGHT_CORRUPTOR_RESPAWN = 0,
    YELL_TWILIGHT_CORRUPTOR_AGGRO = 1,
    YELL_TWILIGHT_CORRUPTOR_KILL = 2,

    SPELL_SOUL_CORRUPTION = 25805,
    SPELL_CREATURE_OF_NIGHTMARE = 25806,
    SPELL_LEVEL_UP = 24312,

    EVENT_SOUL_CORRUPTION = 1,
    EVENT_CREATURE_OF_NIGHTMARE = 2,

    QUEST_NIGHTMARES_CORRUPTION = 8735
};

/*######
# boss_twilight_corrupter
######*/

struct boss_twilight_corrupter : public ScriptedAI
{
    boss_twilight_corrupter(Creature* creature) : ScriptedAI(creature)
    {
        Initialize();
    }

    void Initialize()
    {
        KillCount = 0;
    }

    void Reset() override
    {
        _events.Reset();
        Initialize();
    }

    void EnterCombat(Unit* /*who*/) override
    {
        Talk(YELL_TWILIGHT_CORRUPTOR_AGGRO);
        _events.ScheduleEvent(EVENT_SOUL_CORRUPTION, 15000);
        _events.ScheduleEvent(EVENT_CREATURE_OF_NIGHTMARE, 30000);
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim->GetTypeId() == TYPEID_PLAYER)
        {
            ++KillCount;
            Talk(YELL_TWILIGHT_CORRUPTOR_KILL, victim);

            if (KillCount == 3)
            {
                DoCast(me, SPELL_LEVEL_UP, true);
                KillCount = 0;
            }
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_SOUL_CORRUPTION:
                DoCastAOE(SPELL_SOUL_CORRUPTION);
                _events.ScheduleEvent(EVENT_SOUL_CORRUPTION, urand(15000, 19000));
                break;
            case EVENT_CREATURE_OF_NIGHTMARE:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                    DoCast(target, SPELL_CREATURE_OF_NIGHTMARE);
                _events.ScheduleEvent(EVENT_CREATURE_OF_NIGHTMARE, 45000);
                break;
            default:
                break;
            }
        }

        DoMeleeAttackIfReady();
    }

private:
    EventMap _events;
    uint8 KillCount;
};

/*######
# at_twilight_grove
######*/

Position const TwillightCorrupter = { -10328.16f, -489.57f, 49.95f, 0.0f };

class at_twilight_grove : public AreaTriggerScript
{
public:
    at_twilight_grove() : AreaTriggerScript("at_twilight_grove") { }

    bool OnTrigger(Player* player, const AreaTriggerEntry* /*areaTrigger*/, bool /*entered*/) override
    {
        if (player->GetQuestStatus(QUEST_NIGHTMARES_CORRUPTION) == QUEST_STATUS_INCOMPLETE)
            if (!player->FindNearestCreature(NPC_TWILIGHT_CORRUPTER, 500.0f, true))
                if (Creature* corrupter = player->SummonCreature(NPC_TWILIGHT_CORRUPTER, TwillightCorrupter, TEMPSUMMON_MANUAL_DESPAWN, 60000))
                    corrupter->AI()->Talk(YELL_TWILIGHT_CORRUPTOR_RESPAWN, player);

        return false;
    };
};

enum SpellSummonStalvanData
{
    NPC_STALVAN = 315,
    NPC_TOBIAS = 43453,
    NPC_WORGEN_TOBIAS = 43797,

    DISPLAYID_WORGEN_TOBIAS = 33508,
    QUEST_MISTMANTLES_REVENGE = 26674,
};

const Position stalvanPosition      = { -10371.72f, -1251.92f, 35.99339f };
const Position stalvanDestination   = { -10369.932617f, -1253.7677f, 35.909294f };
const float stalvanOrientation      = 5.532694f;

const uint8 tobiasPositionsCount = 4;
const Position tobiasPositions[tobiasPositionsCount] =
{
    { -10351.5f, -1256.7f, 34.8566f },
    { -10357.5f, -1256.8f, 35.3863f },
    { -10363.5f, -1257.0f, 35.9107f },
    { -10365.8f, -1255.7f, 35.9098f }
};

enum StalvanData
{
    SPELL_WORGEN_TRANSFORMATION = 81908,

    EVENT_STALVAN_STEP_1 = 1,
    EVENT_STALVAN_STEP_2 = 2,
    EVENT_STALVAN_STEP_3 = 3,
    EVENT_STALVAN_STEP_4 = 4,
    EVENT_STALVAN_STEP_5 = 5,
    EVENT_STALVAN_STEP_6 = 6,

    EVENT_TOBIAS_STEP_1 = 7,
    EVENT_TOBIAS_STEP_2 = 8,
    EVENT_TOBIAS_STEP_3 = 9,
    EVENT_TOBIAS_STEP_4 = 10,

    SAY_00 = 0,
    SAY_01 = 1,
    SAY_02 = 2,
    SAY_03 = 3,
    SAY_04 = 4,
    SAY_05 = 5,
    SAY_06 = 6,
};

struct npc_stalvan : public ScriptedAI
{
    npc_stalvan(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        _events.Reset();
        _events.ScheduleEvent(EVENT_STALVAN_STEP_1, 3000);
        _events.ScheduleEvent(EVENT_STALVAN_STEP_2, 8000);
        _events.ScheduleEvent(EVENT_STALVAN_STEP_3, 15000);
        _events.ScheduleEvent(EVENT_STALVAN_STEP_4, 23000);
        _events.ScheduleEvent(EVENT_STALVAN_STEP_5, 26000);
        _events.ScheduleEvent(EVENT_STALVAN_STEP_6, 32000);

        _events.ScheduleEvent(EVENT_TOBIAS_STEP_1, 5000);
        _events.ScheduleEvent(EVENT_TOBIAS_STEP_2, 9000);
        _events.ScheduleEvent(EVENT_TOBIAS_STEP_3, 16000);
        _events.ScheduleEvent(EVENT_TOBIAS_STEP_4, 27000);
    }

    void JustDied(Unit* /*killer*/) override
    {
        if (Creature* tobias = GetTobias())
        {
            Talk(SAY_06, tobias);
            tobias->AI()->Talk(SAY_04);
            tobias->DespawnOrUnsummon(4000);
        }
    }

    Creature* GetTobias()
    {
        if (Creature* tobias = me->FindNearestCreature(NPC_TOBIAS, 30, true))
            return tobias;

        return me->FindNearestCreature(NPC_WORGEN_TOBIAS, 30, true);
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_STALVAN_STEP_1:
                    me->SetWalk(true);
                    me->SetSpeed(MOVE_WALK, 2.5);
                    me->GetMotionMaster()->MovePoint(0, stalvanDestination, true);
                    Talk(SAY_00, GetTobias());
                    break;

                case EVENT_STALVAN_STEP_2:
                    Talk(SAY_01, GetTobias());
                    break;

                case EVENT_STALVAN_STEP_3:
                    Talk(SAY_02, GetTobias());
                    break;

                case EVENT_STALVAN_STEP_4:
                    Talk(SAY_03, GetTobias());
                    break;

                case EVENT_STALVAN_STEP_5:
                    Talk(SAY_04, GetTobias());
                    break;

                case EVENT_STALVAN_STEP_6:
                    Talk(SAY_05, GetTobias());
                    break;

                case EVENT_TOBIAS_STEP_1:
                    if (Creature* tobias = GetTobias())
                    {
                        tobias->SetFacingToObject(me, true);
                        me->SetFacingToObject(tobias, true);
                        tobias->AI()->Talk(SAY_00, me);
                    }
                    break;

                case EVENT_TOBIAS_STEP_2:
                    if (Creature* tobias = GetTobias())
                        tobias->AI()->Talk(SAY_01, me);
                    break;

                case EVENT_TOBIAS_STEP_3:
                    if (Creature* tobias = GetTobias())
                        tobias->AI()->Talk(SAY_02, me);
                    break;

                case EVENT_TOBIAS_STEP_4:
                    if (Creature* tobias = GetTobias())
                    {
                        tobias->CastSpell(tobias, SPELL_WORGEN_TRANSFORMATION, true);
                        tobias->SetReactState(REACT_AGGRESSIVE);

                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
                        me->AddThreat(tobias, 10.f);
                        tobias->AddThreat(me, 10.f);
                        tobias->SetInCombatWith(me);

                        if (me->Attack(tobias, true))
                            me->GetMotionMaster()->MoveChase(tobias);

                        if (tobias->Attack(me, true))
                            tobias->GetMotionMaster()->MoveChase(me);

                        me->SetReactState(REACT_AGGRESSIVE);

                        tobias->AI()->Talk(SAY_03, tobias->GetOwner());
                    }
                    break;

                default:
                    break;
            }
        }

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }

private:
    EventMap _events;
};

enum SoothingIncenseCloudData
{
    EVENT_SELECT_TARGET = 1,
    NPC_FORLORN_SPIRIT = 43923,
    NPC_FORLORN_SPIRIT_KILLCREDIT = 43930,
};

struct npc_soothing_incense_cloud : public ScriptedAI
{
    npc_soothing_incense_cloud(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _events.Reset();
        _events.ScheduleEvent(EVENT_SELECT_TARGET, 500);
    }

    Player* GetOwner()
    {
        return me->ToTempSummon()->GetSummoner()->ToPlayer();
    }

    void SelectTargets()
    {
        me->GetCreatureListWithEntryInGrid(_selectedTargets, NPC_FORLORN_SPIRIT, 5.f);
    }

    void KillSelectedCreaturesAndRewardPlayer()
    {
        for (auto creature : _selectedTargets)
        {
            if (!creature->IsAlive())
                continue;

            GetOwner()->RewardPlayerAndGroupAtEvent(NPC_FORLORN_SPIRIT_KILLCREDIT, GetOwner());
            creature->DisappearAndDie();
        }
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_SELECT_TARGET:
                SelectTargets();
                KillSelectedCreaturesAndRewardPlayer();
                break;
            }
        }
    }

private:
    EventMap _events;
    std::list<Creature*> _selectedTargets;
};

enum MorbentFel
{
    SPELL_SACRED_CLEANSING   = 82130,
    NPC_WEAKENED_MORBENT_FEL = 43762,
    NPC_MORBENT_FEL          = 43761
};

class spell_sacred_cleansing : public SpellScript
{
    PrepareSpellScript(spell_sacred_cleansing);

    void SelectTarget(WorldObject*& target)
    {
        target = GetCaster()->FindNearestCreature(NPC_MORBENT_FEL, 15.0f, true);
    }

    SpellCastResult CheckRequirement()
    {
        if (Creature* fel = GetCaster()->FindNearestCreature(NPC_MORBENT_FEL, 15.0f, true))
            return SPELL_CAST_OK;

        return SPELL_FAILED_INCORRECT_AREA;
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* hitUnit = GetHitUnit();
        if (!hitUnit || !GetCaster()->IsPlayer())
            return;

        if (Creature* target = hitUnit->ToCreature())
        {
            if (target->GetEntry() == NPC_MORBENT_FEL)
            {
                GetCaster()->SummonCreature(NPC_WEAKENED_MORBENT_FEL, target->GetPosition());
                target->DespawnOrUnsummon();
            }
        }
    }

    void Register() override
    {
        OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_sacred_cleansing::SelectTarget, EFFECT_0, TARGET_UNIT_NEARBY_ENTRY);
        OnEffectHitTarget += SpellEffectFn(spell_sacred_cleansing::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnCheckCast += SpellCheckCastFn(spell_sacred_cleansing::CheckRequirement);
    }
};

class spell_summon_stalvan : public SpellScript
{
    PrepareSpellScript(spell_summon_stalvan);

    bool IsEventRunning()
    {
        return GetCaster()->FindNearestCreature(NPC_STALVAN, 20, true) != nullptr;
    }

    SpellCastResult CheckRequirement()
    {
        return SPELL_CAST_OK;
    }

    void HandleSendEvent(SpellEffIndex /*effIndex*/)
    {
        if (!GetCaster()->IsPlayer())
            return;

        if (GetCaster()->ToPlayer()->GetQuestStatus(QUEST_MISTMANTLES_REVENGE) != QUEST_STATUS_INCOMPLETE)
            return;

        if (IsEventRunning())
            return;

        SummonStalvan();
        SummonTobias();
    }

    void SummonStalvan()
    {
        if (TempSummon* stalvan = GetCaster()->SummonCreature(NPC_STALVAN, stalvanPosition))
        {
            stalvan->SetFacingTo(stalvanOrientation, true);
            stalvan->SetReactState(REACT_PASSIVE);
        }
    }

    void SummonTobias()
    {
        if (TempSummon* tobias = GetCaster()->SummonCreature(NPC_TOBIAS, tobiasPositions[0]))
        {
            tobias->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER | UNIT_NPC_FLAG_GOSSIP);
            tobias->SetWalk(true);
            tobias->SetSpeed(MOVE_WALK, 3.5);
            tobias->GetMotionMaster()->MovePoint(0, tobiasPositions[3], true);
            tobias->SetReactState(REACT_PASSIVE);
        }
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_summon_stalvan::HandleSendEvent, EFFECT_0, SPELL_EFFECT_SEND_EVENT);
        OnCheckCast += SpellCheckCastFn(spell_summon_stalvan::CheckRequirement);
    }

};

struct npc_ebenlocke : public ScriptedAI
{
    enum Data
    {
        QUEST_EMBALMERS_REVENGE    = 26727,
        NPC_STITCHES               = 43862
    };
    
    npc_ebenlocke(Creature* creature) : ScriptedAI(creature) { }

    void sQuestAccept(Player* /*player*/, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_EMBALMERS_REVENGE)
        {
            me->GetScheduler().Schedule(2s, [this](TaskContext /*context*/)
            {
                me->SummonCreature(NPC_STITCHES, -10553.90f, -1171.27f, 27.8604f, 1.48514f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000, true);
            });
        }
    }
};

//enum eCryForMoon
//{
//    QUEST_CRY_FOR_THE_MOON = 26760,
//    NPC_OLIVER_HARRIS = 43858,
//    NPC_JITTERS = 43859,
//    NPC_LUR_WORGEN = 43950,
//    SPELL_CHOKING_JITTERS = 82262,
//    SPELL_CHOKED_BY_SVEN = 82266,
//    SPELL_EJECT_PASSENGERS = 65785,
//    SPELL_KILL_CREDIT = 43969
//};
//
//class npc_oliver_harris : public CreatureScript
//{
//public:
//    npc_oliver_harris() : CreatureScript("npc_oliver_harris") {}
//
//    CreatureAI* GetAI(Creature* creature) const override
//    {
//        return new npc_oliver_harrisAI(creature);
//    }
//
//    struct npc_oliver_harrisAI : public ScriptedAI
//    {
//        npc_oliver_harrisAI(Creature* creature) : ScriptedAI(creature) {}
//
//        uint8 Phase;
//        uint32 SummonTimer;
//        ObjectGuid PlayerGUID;
//        ObjectGuid OliverHarrisGUID;
//        ObjectGuid JittersGUID;
//        ObjectGuid LurWorgenGUID;
//
//        bool bSumm;
//        bool bSummHarris;
//        bool bSummJitters;
//        bool bSummWorgen;
//        bool bExit;
//
//        void Reset() override
//        {
//            Phase = 0;
//            SummonTimer = 2000;
//            bSumm = false;
//            bSummHarris = false;
//            bSummJitters = false;
//            bSummWorgen = false;
//            bExit = false;
//        }
//
//        void MoveInLineOfSight(Unit* who) override
//        {
//            ScriptedAI::MoveInLineOfSight(who);
//
//            if (who->GetTypeId() != TYPEID_PLAYER)
//                return;
//
//            if (who->ToPlayer()->GetQuestStatus(QUEST_CRY_FOR_THE_MOON) == QUEST_STATUS_INCOMPLETE)
//            {
//                if (who->IsWithinDistInMap(me, 10.0f) && !bSumm)
//                {
//                    PlayerGUID = who->GetGUID();
//                    StartEvent();
//                }
//            }
//        }
//
//        void StartEvent()
//        {
//            if (!bSumm)
//            {
//                if (!bSummHarris)
//                {
//                    if (Creature* OliverHarris = me->SummonCreature(NPC_OLIVER_HARRIS, -10752.87f, 338.19f, 37.294f, 5.48f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
//                    {
//                        OliverHarrisGUID = OliverHarris->GetGUID();
//                        // OliverHarris->SetWalk(true);
//                        // OliverHarris->GetMotionMaster()->MovePoint(0, -10745.14f, 331.53f, 37.86f);
//                        bSummHarris = true;
//                    }
//                }
//
//                if (!bSummJitters)
//                {
//                    if (Creature* Jitters = me->SummonCreature(NPC_JITTERS, -10748.52f, 333.62f, 37.46f, 5.37f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
//                    {
//                        JittersGUID = Jitters->GetGUID();
//                        bSummJitters = true;
//                    }
//                }
//
//
//                if (!bSummWorgen)
//                {
//                    if (Creature* Worgen = me->SummonCreature(NPC_LUR_WORGEN, -10747.40f, 332.28f, 37.74f, 4.48f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
//                    {
//                        LurWorgenGUID = Worgen->GetGUID();
//                        bSummWorgen = true;
//                    }
//                }
//
//                if (bSummHarris && bSummJitters && bSummWorgen)
//                {
//                    bSumm = true;
//                    SummonTimer = 2000;
//                }
//            }
//        }
//
//        void UpdateAI(uint32 diff) override
//        {
//            if (SummonTimer < diff)
//            {
//                if (bSumm)
//                {
//                    if (Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID))
//                        if (Creature* Harris = ObjectAccessor::GetCreature(*me, OliverHarrisGUID))
//                            if (Creature* Jitters = ObjectAccessor::GetCreature(*me, JittersGUID))
//                                if (Creature* Worgen = ObjectAccessor::GetCreature(*me, LurWorgenGUID))
//                                {
//                                    switch (Phase) {
//                                        case 0: {
//                                            Harris->GetMotionMaster()->MovePoint(0, -10745.14f, 331.53f, 37.86f);
//                                            Jitters->HandleEmoteCommand(69);
//                                            SummonTimer = 4000;
//                                            Phase++;
//                                            break;
//                                        }
//                                        case 1: {
//                                            Harris->Say("Here we go... ", LANG_UNIVERSAL);
//                                            Harris->SetFacingToObject(Worgen);
//                                            Harris->HandleEmoteCommand(396);
//                                            SummonTimer = 3500;
//                                            Phase++;
//                                            break;
//                                        }
//                                        case 2: {
//                                            Harris->Say("It's working. Hold him still, Jitters.", LANG_UNIVERSAL);
//                                            Harris->HandleEmoteCommand(390);
//                                            SummonTimer = 2500;
//                                            Phase++;
//                                            break;
//                                        }
//                                        case 3: {
//                                            Jitters->Say("I... I can't", LANG_UNIVERSAL);
//                                            SummonTimer = 2000;
//                                            Phase++;
//                                            break;
//                                        }
//                                        case 4: {
//                                            Worgen->Say("Jitters... ", LANG_UNIVERSAL);
//                                            SummonTimer = 1000;
//                                            Phase++;
//                                            break;
//                                        }
//                                        case 5: {
//                                            Harris->Say("Damn it, Jitters. I said HOLD!", LANG_UNIVERSAL);
//                                            Harris->HandleEmoteCommand(5);
//                                            SummonTimer = 3000;
//                                            Phase++;
//                                            break;
//                                        }
//                                        case 6: {
//                                            Worgen->Yell("JITTERS!", LANG_UNIVERSAL);
//                                            Worgen->HandleEmoteCommand(53);
//                                            Worgen->SetOrientation(2.3997f);
//                                            SummonTimer = 4000;
//                                            Phase++;
//                                            break;
//                                        }
//                                        case 7: {
//                                            Worgen->Say("I remember now... it's all your fault!", LANG_UNIVERSAL);
//                                            Worgen->HandleEmoteCommand(384);
//                                            Jitters->HandleEmoteCommand(473);
//                                            SummonTimer = 4500;
//                                            Phase++;
//                                            break;
//                                        }
//                                        case 8: {
//                                            Worgen->Say("You brought the worgen to Duskwood! You led the Dark Riders to my farm, and hid while they murdered my family!", LANG_UNIVERSAL);
//                                            SummonTimer = 4500;
//                                            Phase++;
//                                            break;
//                                        }
//                                        case 9: {
//                                            Worgen->Yell("Every speak of suffering in my life is YOUR PATHETIC FAULT! I SHOULD KILL YOU!", LANG_UNIVERSAL);
//                                            SummonTimer = 9000;
//                                            Phase++;
//                                            break;
//                                        }
//                                        case 10: {
//                                            Harris->Say("Letting him go is the only thing that's going to separate you from the beasts now, my friend.", LANG_UNIVERSAL);
//                                            SummonTimer = 1500;
//                                            Phase++;
//                                            break;
//                                        }
//                                        case 11: {
//                                            Worgen->Say("You've got a lot to make up for, Jitters. I won't give you the easy way out.", LANG_UNIVERSAL);
//                                            SummonTimer = 2000;
//                                            Phase++;
//                                            break;
//                                        }
//                                        case 12: {
//                                            Worgen->GetMotionMaster()->MovePoint(1, -10761.66f, 338.77f, 37.82f);
//                                            Worgen->HandleEmoteCommand(0);
//                                            Jitters->HandleEmoteCommand(0);
//                                            SummonTimer = 6000;
//                                            Phase++;
//                                            break;
//                                        }
//                                        case 13: {
//                                            Worgen->SetFacingToObject(Jitters);
//                                            Harris->GetMotionMaster()->MoveTargetedHome();
//                                            SummonTimer = 3000;
//                                            Phase++;
//                                            break;
//                                        }
//                                        case 14: {
//                                            player->KilledMonsterCredit(SPELL_KILL_CREDIT, PlayerGUID);
//                                            SummonTimer = 1000;
//                                            Phase++;
//                                            break;
//                                        }
//                                        case 15: {
//                                            if (!bExit) {
//                                                Jitters->DespawnOrUnsummon(1000);
//                                                Harris->DespawnOrUnsummon(1000);
//                                                Worgen->DespawnOrUnsummon(1000);
//                                                bExit = true;
//                                            }
//                                        }
//                                        break;
//                                        default:
//                                            break;
//                                    }
//                                }
//                }
//            }
//            else SummonTimer -= diff;
//        }
//    };
//};

enum eCryForMoon
{
    SPELL_INVISIBILITY_7 = 82288,
    SPELL_INVISIBILITY_8 = 82289,
    SPELL_CHOKING_JITTERS = 82262,
    SPELL_DUSKWOOD_CHOKED_BY_SVEN = 82266,
    SPELL_EJECT_PASSENGERS = 65785,
    SPELL_KILL_CREDIT = 82286,

    NPC_OLIVER_HARRIS = 43730, // 43730 (43858 summoned)
    NPC_JITTERS = 288, // 288 (43859 summoned)
    NPC_LURKING_WORGEN = 43950, // summoned
    NPC_SVEN_YORGEN = 43861,

    QUEST_CRY_FOR_THE_MOON = 26760,
};

class npc_oliver_harris : public CreatureScript
{
public:
    npc_oliver_harris() : CreatureScript("npc_oliver_harris") {}

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_oliver_harrisAI(creature);
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_CRY_FOR_THE_MOON)
        {
            player->RemoveAurasDueToSpell(SPELL_INVISIBILITY_7);
            player->RemoveAurasDueToSpell(SPELL_INVISIBILITY_8);

            ENSURE_AI(npc_oliver_harris::npc_oliver_harrisAI, creature->AI())->PlayerGUID = player->GetGUID();

            if (!(ENSURE_AI(npc_oliver_harris::npc_oliver_harrisAI, creature->AI())->EventStarted))
            {
                ENSURE_AI(npc_oliver_harris::npc_oliver_harrisAI, creature->AI())->EventStarted = true;
            }

            if (!player->FindNearestCreature(NPC_LURKING_WORGEN, 20.0f, true))
            {
                player->SummonCreature(NPC_LURKING_WORGEN, -10747.40f, 332.28f, 37.74f, 4.48f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000);
            }
        }
        return true;
    }

    struct npc_oliver_harrisAI : public ScriptedAI
    {
        npc_oliver_harrisAI(Creature* creature) : ScriptedAI(creature) {}

        ObjectGuid PlayerGUID;
        ObjectGuid OliverHarrisGUID;
        ObjectGuid JittersGUID;
        ObjectGuid WorgenGUID;

        uint32 EventTimer;
        uint8 Phase;
        bool EventStarted;

        void Reset() override
        {
            Phase = 0;
            EventTimer = 2000;
            EventStarted = false;
            me->RemoveAllAuras();
        }

        void UpdateAI(uint32 diff) override
        {
            if (EventStarted)
            {
                if (EventTimer < diff)
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID))
                        if (Creature* Jitters = me->FindNearestCreature(NPC_JITTERS, 20.0f, true))
                            if (Creature* Worgen = me->FindNearestCreature(NPC_LURKING_WORGEN, 20.0f, true))
                                if (Creature* Harris = me->FindNearestCreature(NPC_OLIVER_HARRIS, 20.0f, true))
                                {
                                    switch (Phase)
                                    {
                                    case 0:
                                    {
                                        Jitters->GetMotionMaster()->MovePoint(0, -10748.52f, 333.62f, 37.46f);
                                        me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                                        me->GetMotionMaster()->MovePoint(1, -10745.14f, 331.53f, 37.86f);
                                        Jitters->HandleEmoteCommand(69); // doing something
                                        EventTimer = 4000;
                                        Phase++;
                                        break;
                                    }
                                    case 1:
                                    {
                                        me->Say("Here we go... ", LANG_UNIVERSAL);
                                        me->SetFacingToObject(Worgen);
                                        me->HandleEmoteCommand(396); // cool story 1
                                        EventTimer = 3500;
                                        Phase++;
                                        break;
                                    }
                                    case 2:
                                    {
                                        me->Say("It's working. Hold him still, Jitters.", LANG_UNIVERSAL);
                                        me->HandleEmoteCommand(390); // cool story 2
                                        EventTimer = 2500;
                                        Phase++;
                                        break;
                                    }
                                    case 3:
                                    {
                                        Jitters->Say("I... I can't", LANG_UNIVERSAL);
                                        EventTimer = 2000;
                                        Phase++;
                                        break;
                                    }
                                    case 4:
                                    {
                                        Worgen->Say("Jitters... ", LANG_UNIVERSAL);
                                        EventTimer = 1000;
                                        Phase++;
                                        break;
                                    }
                                    case 5:
                                    {
                                        me->Say("Damn it, Jitters. I said HOLD!", LANG_UNIVERSAL);
                                        me->HandleEmoteCommand(5);
                                        EventTimer = 3000;
                                        Phase++;
                                        break;
                                    }
                                    case 6:
                                    {
                                        Worgen->Yell("JITTERS!", LANG_UNIVERSAL);
                                        Worgen->HandleEmoteCommand(53); // Roar!
                                        // Worgen->SetOrientation(2.3997f);
                                        Worgen->SetFacingToObject(Jitters);
                                        EventTimer = 4000;
                                        Phase++;
                                        break;
                                    }
                                    case 7:
                                    {
                                        // Worgen->HandleEmoteCommand(384); // take something in hand
                                        Worgen->CastSpell(Worgen, SPELL_DUSKWOOD_CHOKED_BY_SVEN, true);
                                        // Jitters->HandleEmoteCommand(473); // throat sore
                                        Jitters->CastSpell(Jitters, SPELL_CHOKING_JITTERS, true);
                                        Worgen->Say("I remember now... it's all your fault!", LANG_UNIVERSAL);
                                        EventTimer = 4500;
                                        Phase++;
                                        break;
                                    }
                                    case 8:
                                    {
                                        Worgen->Say("You brought the worgen to Duskwood! You led the Dark Riders to my farm, and hid while they murdered my family!", LANG_UNIVERSAL);
                                        EventTimer = 4500;
                                        Phase++;
                                        break;
                                    }
                                    case 9:
                                    {
                                        Worgen->Yell("Every speak of suffering in my life is YOUR PATHETIC FAULT! I SHOULD KILL YOU!", LANG_UNIVERSAL);
                                        EventTimer = 9000;
                                        Phase++;
                                        break;
                                    }
                                    case 10:
                                    {
                                        me->Say("Letting him go is the only thing that's going to separateyou from the beasts now, my friend.", LANG_UNIVERSAL);
                                        EventTimer = 1500;
                                        Phase++;
                                        break;
                                    }
                                    case 11:
                                    {
                                        // Worgen->CastSpell(Jitters, SPELL_EJECT_PASSENGERS, true);
                                        Jitters->CastSpell(Jitters, SPELL_EJECT_PASSENGERS, true);
                                        Jitters->RemoveAurasDueToSpell(SPELL_CHOKING_JITTERS);
                                        Worgen->RemoveAurasDueToSpell(SPELL_DUSKWOOD_CHOKED_BY_SVEN);
                                        Worgen->HandleEmoteCommand(0); // initial
                                        Jitters->HandleEmoteCommand(0); // initial
                                        Worgen->Say("You've got a lot to make up for, Jitters. I won't give you the easy way out.", LANG_UNIVERSAL);
                                        EventTimer = 2000;
                                        Phase++;
                                        break;
                                    }
                                    case 12:
                                    {
                                        Jitters->HandleEmoteCommand(0); // initial
                                        // Jitters->GetMotionMaster()->MovePoint(2, -10761.66f, 338.77f, 37.82f);
                                        Jitters->GetMotionMaster()->MoveTargetedHome();
                                        Worgen->HandleEmoteCommand(0); // initial
                                        Worgen->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                                        Worgen->GetMotionMaster()->MovePoint(2, -10761.66f, 338.77f, 37.82f);
                                        EventTimer = 6000;
                                        Phase++;
                                        break;
                                    }
                                    case 13:
                                    {
                                        me->GetMotionMaster()->MoveTargetedHome();
                                        // Jitters->GetMotionMaster()->MoveTargetedHome();
                                        EventTimer = 3000;
                                        Phase++;
                                        break;
                                    }
                                    case 14:
                                    {
                                        Worgen->DespawnOrUnsummon();
                                        player->CastSpell(player, 82288, true);
                                        player->CastSpell(player, 82289, true);
                                        player->KilledMonsterCredit(43969, PlayerGUID);
                                        me->AI()->Reset();
                                        EventTimer = 1000;
                                        Phase++;
                                        break;
                                    }
                                    case 15:
                                    {
                                        EventTimer = 100;
                                        if (Creature* Worgen = me->FindNearestCreature(NPC_LURKING_WORGEN, 40.0f, true))
                                        {
                                            Worgen->DespawnOrUnsummon();
                                        }
                                        Phase++;
                                    }
                                    break;
                                    default:
                                        break;
                                    }
                                }
                }
                else EventTimer -= diff;
            }
        }

    };
};

void AddSC_duskwood()
{
    RegisterCreatureAI(boss_twilight_corrupter);
    new at_twilight_grove();
    RegisterSpellScript(spell_summon_stalvan);
    RegisterCreatureAI(npc_stalvan);
    RegisterCreatureAI(npc_soothing_incense_cloud);
    RegisterSpellScript(spell_sacred_cleansing);
    RegisterCreatureAI(npc_ebenlocke);
    new npc_oliver_harris();
}
