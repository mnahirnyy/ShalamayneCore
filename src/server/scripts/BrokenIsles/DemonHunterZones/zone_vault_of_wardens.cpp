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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "QuestPackets.h"
#include "ScenePackets.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "ObjectAccessor.h"
#include "SpellAuras.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "MotionMaster.h"
#include "WorldSession.h"
#include "PhasingHandler.h"
#include "CombatAI.h"
#include "Log.h"

enum eQuests
{
    QUEST_BREAKING_OUT          = 38672,
    QUEST_RISE_OF_THE_ILLIDARI  = 38690,
    QUEST_FEL_INFUSION          = 38689,
    QUEST_VAULT_OF_THE_WARDENS  = 39742, // optional bonus objective
    QUEST_STOP_GULDAN_H         = 38723,
    QUEST_STOP_GULDAN_A         = 40253,
    QUEST_GRAND_THEFT_FELBAT    = 39682,
    QUEST_FROZEN_IN_TIME        = 39685,
    QUEST_BEAM_ME_UP            = 39684,
    QUEST_FORGED_IN_FIRE_H      = 39683,
    QUEST_FORGED_IN_FIRE_V      = 40254,
    QUEST_ALL_THE_WAY_UP        = 39686,
    QUEST_A_NEW_DIRECTION       = 40373,
    QUEST_BETWEEN_US_AND_FREEDOM_HH = 39694,
    QUEST_BETWEEN_US_AND_FREEDOM_HA = 39688,
    QUEST_BETWEEN_US_AND_FREEDOM_VA = 40255,
    QUEST_BETWEEN_US_AND_FREEDOM_VH = 40256,
    QUEST_ILLIDARI_LEAVING_A = 39689,
    QUEST_ILLIDARI_LEAVING_H = 39690,
};

enum eSpells
{
    SPELL_FEL_INFUSION          = 133508,
    SPELL_CANCEL_FEL_BAR        = 133510,
    SPELL_UNLOCKING_ALTRUIS     = 184012,
    SPELL_UNLOCKING_KAYN        = 177803,
    SPELL_PRISON_EXPLOSION      = 232248,
};

enum eKillCredits
{
    KILL_CREDIT_KAYN_PICKED_UP_WEAPONS          = 112276,
    KILL_CREDIT_ALTRUIS_PICKED_UP_WEAPONS       = 112277,
    KILL_CREDIT_REUNION_FINISHED_KAYN           = 99326,
    KILL_CREDIT_REUNION_FINISHED_ALTRUIS        = 112287,
};

class npc_maiev_shadowsong_welcome : public CreatureScript
{
public:
    npc_maiev_shadowsong_welcome() : CreatureScript("npc_maiev_shadowsong_welcome") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_BREAKING_OUT) {
            player->SummonCreature(92718, creature->GetPosition(), TEMPSUMMON_MANUAL_DESPAWN, 10000, 0, true);
        }
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_maiev_shadowsong_welcome_AI(creature);
    }

    struct npc_maiev_shadowsong_welcome_AI : public ScriptedAI
    {
        npc_maiev_shadowsong_welcome_AI(Creature* creature) : ScriptedAI(creature)
        {
            timer = 0;
            movein = false;
        }

        uint32 timer;
        bool movein;

        void IsSummonedBy(Unit* summoner) override
        {
            Player* player = summoner->ToPlayer();

            if (!player)
                return;

            timer = 2000;
            movein = true;

            Talk(0);
        }

        void UpdateAI(uint32 diff) override
        {
            if (movein)
            {
                if (timer <= diff)
                {
                    if (GameObject* go = me->FindNearestGameObject(244925, me->GetVisibilityRange()))
                        go->UseDoorOrButton();

                    me->GetMotionMaster()->MovePath(1092718, false);

                    me->GetScheduler().Schedule(Seconds(4), [this](TaskContext context)
                    {
                        Creature* maiev = GetContextCreature();
                        if (GameObject* go = maiev->FindNearestGameObject(244925, maiev->GetVisibilityRange()))
                            go->ResetDoorOrButton();
                    });

                    movein = false;
                    me->DespawnOrUnsummon(5000);
                }
                else timer -= diff;
            }
        }
    };
};

// 103658
class npc_kayn_cell : public CreatureScript
{
public:
   npc_kayn_cell() : CreatureScript("npc_kayn_cell") { }

   bool OnGossipHello(Player* player, Creature* creature) override
   {
       if (player->GetQuestStatus(QUEST_BREAKING_OUT) == QUEST_STATUS_INCOMPLETE)
       {
           if (creature == nullptr)
               return false;

           player->CastSpell(creature, SPELL_UNLOCKING_KAYN, true);
           creature->DespawnOrUnsummon(60);
           player->SummonCreature(99631, 4343.16f, -589.57f, -281.40f, 3.38f, TEMPSUMMON_TIMED_DESPAWN, 60000, false);
       }
       return true;
   }
};

// 103655
class npc_altruis_cell : public CreatureScript
{
public:
    npc_altruis_cell() : CreatureScript("npc_altruis_cell") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {   
        if (player->GetQuestStatus(QUEST_BREAKING_OUT) == QUEST_STATUS_INCOMPLETE)
        {
            if (creature == nullptr)
                return false;

            player->CastSpell(creature, SPELL_UNLOCKING_ALTRUIS, true);
            creature->DespawnOrUnsummon(60);
            player->SummonCreature(99632, 4309.94f, -589.618f, -281.407f, 6.13126f, TEMPSUMMON_TIMED_DESPAWN, 60000, false);
        }
        return true;
    }
};

class q_breaking_out : public QuestScript
{
public:
    q_breaking_out() : QuestScript("q_breaking_out") { }

    void OnQuestStatusChange(Player* player, Quest const* /*quest*/, QuestStatus /*oldStatus*/, QuestStatus newStatus) override
    {
        if (newStatus == QUEST_STATUS_NONE)
        {
            PhasingHandler::OnConditionChange(player);
            if (GameObject* go = player->FindNearestGameObject(244925, 200.0f))
                go->ResetDoorOrButton();
        }
        else if (newStatus == QUEST_STATUS_REWARDED)
        {
            if (GameObject* go = player->FindNearestGameObject(244925, 200.0f))
                go->UseDoorOrButton();
        }
        else if (newStatus == QUEST_STATUS_COMPLETE)
        {
            if (Creature* Kayn = player->FindNearestCreature(99631, player->GetVisibilityRange(), true)) {
                Kayn->AI()->SetData(21, 21);
                Kayn->GetScheduler().Schedule(Seconds(3), [](TaskContext context)
                {
                    Creature* kayn = GetContextCreature();
                    kayn->AI()->Talk(1);
                });
            }
                
            if (Creature* Altruis = player->FindNearestCreature(99632, player->GetVisibilityRange(), true)) {
                Altruis->AI()->SetData(21, 21);
                Altruis->GetScheduler().Schedule(Seconds(8), [](TaskContext context)
                {
                    Creature* altruis = GetContextCreature();
                    altruis->AI()->Talk(1);
                });
            }
        }
    }
};

class npc_fel_infusion : public CreatureScript
{
public:
    npc_fel_infusion() : CreatureScript("npc_fel_infusion") { }

    struct npc_fel_infusionAI : public ScriptedAI
    {
        npc_fel_infusionAI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
        }

        void Initialize() {}

        void Reset() override
        {
            Initialize();
            events.Reset();
        }

        void JustDied(Unit* killer) override
        {
            if (killer->GetTypeId() == TYPEID_PLAYER)
            {
                killer->ToPlayer()->SetPower(POWER_ALTERNATE_POWER, killer->GetPower(POWER_ALTERNATE_POWER) + 8);

                for (uint8 i = 0; i < 8; ++i)
                    killer->ToPlayer()->KilledMonsterCredit(89297, ObjectGuid::Empty);
            }
        }

        void EnterCombat(Unit* who) override {}

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);
            if (UpdateVictim())
                DoMeleeAttackIfReady();
        }

    private:
        EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_fel_infusionAI(creature);
    }
};

class q_fel_infusion : public QuestScript
{
public:
    q_fel_infusion() : QuestScript("q_fel_infusion") { }

    void OnQuestStatusChange(Player* player, Quest const* /*quest*/, QuestStatus /*oldStatus*/, QuestStatus newStatus) override
    {
        if (newStatus == QUEST_STATUS_NONE || newStatus == QUEST_STATE_COMPLETE)
        {
            player->CastSpell(player, SPELL_CANCEL_FEL_BAR, true);
            PhasingHandler::OnConditionChange(player);
        }
    }
};

// 92986 Altruis
class npc_altruis : public CreatureScript
{
public:
    npc_altruis() : CreatureScript("npc_altruis") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_FEL_INFUSION)
            player->CastSpell(player, SPELL_FEL_INFUSION, true);

        return true;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) override
    {
        if (quest->GetQuestId() == QUEST_FEL_INFUSION)
            player->CastSpell(player, SPELL_CANCEL_FEL_BAR, true);

        return true;
    }
};

// 96665 kayn
class npc_kayn_3 : public CreatureScript
{
public:
    npc_kayn_3() : CreatureScript("npc_kayn_3") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) override
    {
        if (quest->GetQuestId() == QUEST_RISE_OF_THE_ILLIDARI)
        {
            if (GameObject* go = player->FindNearestGameObject(245467, 200.0f))
                go->UseDoorOrButton();
            if (GameObject* go = player->FindNearestGameObject(244404, 200.0f))
                go->UseDoorOrButton();
            if (GameObject* go = player->FindNearestGameObject(253400, 200.0f))
                go->UseDoorOrButton();
        }
        return true;
    }
};

// guid: 20542913 id: 92984 Kayn Sunfury to fight with Sledge
enum KaynSledgeFightEvents
{
    EVENT_EYE_BEAM = 1,
    EVENT_BLINK = 2,
    SAY_DO_NOT_SPEAK_OLD_TIMES = 10,
    SAY_HE_WAS_FIGHTING = 11,
    SAY_HE_MADE_HARD_CHOICES = 12,
};

enum KaynSledgeFightSpells
{
    SPELL_EYE_BEAM = 197641,
    SPELL_BLINK = 117312,
    SPELL_ANNIHILATE = 199604,
};

enum KaynSledgeFightData
{
    DATA_ALTRUIS_TALK_OLD_TIMES = 21,
    DATA_ALTRUIS_TALK_AFTER_10K_YEARS = 22,
    DATA_ALTRUIS_TALK_FOLLOW_BLINDLY = 23,
    DATA_ALTRUIS_TALK_DID_NOT_MURDER = 24,
    DATA_SLEDGE_DEATH = 4,
    DATA_CRUSHER_DEATH = 5,
};

enum KaynSledgeFightTexts
{
    TEXT_KAYN_ANSWER_1 = 0,
    TEXT_KAYN_ANSWER_2 = 1,
    TEXT_KAYN_ANSWER_3 = 2,
};

enum KaynSledgeFightMisc
{
    NPC_KAYN_SUNFURY_SLEDGE = 92984,
    NPC_ALTRUIS_SUFFERER_CRUSHER = 92985,
    NPC_CRUSHER = 97632,
    NPC_SLEDGE = 92990,
    DB_PHASE_FIGHT = 543,
    DB_PHASE_AFTER_FIGHT = 993
};

enum SledgeMisc
{
    QUEST_KILL_CREDIT = 106241,
};


class npc_kayn_sledge_fight : public CreatureScript
{
public:
    npc_kayn_sledge_fight() : CreatureScript("npc_kayn_sledge_fight") { }

    struct npc_kayn_sledge_fightAI : public ScriptedAI
    {
        npc_kayn_sledge_fightAI(Creature* creature) : ScriptedAI(creature) {
            me->SetReactState(REACT_DEFENSIVE);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        }

        bool _talkedKaynFirstLine = false;
        bool _talkedKaynSecondLine = false;
        bool _talkedKaynThirdLine = false;
        
        void MoveInLineOfSight(Unit* who) override
        {
            if (who->IsPlayer())
                if (Creature* creature = me->FindNearestCreature(NPC_SLEDGE, me->GetVisibilityRange(), true))
                    AttackStart(creature);
        }

        void EnterCombat(Unit* who) override
        {
            who->GetAI()->AttackStart(me);
            _events.ScheduleEvent(EVENT_EYE_BEAM, urand(20000, 40000));
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage) override
        {
            if (HealthAbovePct(85))
                damage = urand(1, 2);
            else
                me->SetHealth(me->GetMaxHealth() * 0.85f);
        }

        void SpellHit(Unit* /*caster*/, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_ANNIHILATE)
            {
                _events.CancelEvent(EVENT_EYE_BEAM);
                _events.ScheduleEvent(EVENT_BLINK, 1000);
            }
        }

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_ALTRUIS_TALK_OLD_TIMES:
                if (!_talkedKaynFirstLine) {
                    Talk(TEXT_KAYN_ANSWER_1);
                    _events.ScheduleEvent(SAY_DO_NOT_SPEAK_OLD_TIMES, 9000);
                    _talkedKaynFirstLine = true;
                }
                break;
            case DATA_ALTRUIS_TALK_AFTER_10K_YEARS:
                if (!_talkedKaynSecondLine) {
                    Talk(TEXT_KAYN_ANSWER_2);
                    _events.ScheduleEvent(SAY_HE_WAS_FIGHTING, 7000);
                    _talkedKaynSecondLine = true;
                }
                break;
            case DATA_ALTRUIS_TALK_FOLLOW_BLINDLY:
                if (!_talkedKaynThirdLine) {
                    Talk(TEXT_KAYN_ANSWER_3);
                    _events.ScheduleEvent(SAY_HE_MADE_HARD_CHOICES, 7000);
                    _talkedKaynThirdLine = true;
                }
                break;
            case DATA_SLEDGE_DEATH:
                EnterEvadeMode(EVADE_REASON_OTHER);
                _events.CancelEvent(EVENT_EYE_BEAM);
                _events.CancelEvent(SAY_DO_NOT_SPEAK_OLD_TIMES);
                _events.CancelEvent(SAY_HE_WAS_FIGHTING);
                _events.CancelEvent(SAY_HE_MADE_HARD_CHOICES);
                break;
            }
        }

        void JustReachedHome() override {}

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {   
                case SAY_DO_NOT_SPEAK_OLD_TIMES:
                    if (Creature* creature = me->FindNearestCreature(NPC_ALTRUIS_SUFFERER_CRUSHER, me->GetVisibilityRange(), true))
                        creature->AI()->SetData(DATA_ALTRUIS_TALK_AFTER_10K_YEARS, DATA_ALTRUIS_TALK_AFTER_10K_YEARS);
                    break;
                case SAY_HE_WAS_FIGHTING:
                    if (Creature* creature = me->FindNearestCreature(NPC_ALTRUIS_SUFFERER_CRUSHER, me->GetVisibilityRange(), true))
                        creature->AI()->SetData(DATA_ALTRUIS_TALK_FOLLOW_BLINDLY, DATA_ALTRUIS_TALK_FOLLOW_BLINDLY);
                    break;
                case SAY_HE_MADE_HARD_CHOICES:
                    if (Creature* creature = me->FindNearestCreature(NPC_ALTRUIS_SUFFERER_CRUSHER, me->GetVisibilityRange(), true))
                        creature->AI()->SetData(DATA_ALTRUIS_TALK_DID_NOT_MURDER, DATA_ALTRUIS_TALK_DID_NOT_MURDER);
                    break;
                case EVENT_EYE_BEAM:
                    DoCastVictim(SPELL_EYE_BEAM);
                    _events.ScheduleEvent(EVENT_EYE_BEAM, urand(20000, 40000));
                    break;
                case EVENT_BLINK:
                    DoCastVictim(SPELL_BLINK);
                    _events.ScheduleEvent(EVENT_EYE_BEAM, urand(15000, 17000));
                    break;
                default:
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }

    private:
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_kayn_sledge_fightAI(creature);
    }
};

/** guid: 20542915 npc: 92990 "Sledge"
 *  guid: 20542912 npc: 97632 "Crusher"
 *  abilities:
 *   - 199556/brutal-attacks,
 *   - 199375/demon-link,
 *   - 199604/annihilate,
 *   - 199474/leaping-retreat,
 *   - 199481/shoulder-charge
*/
enum SledgeEvents
{
    EVENT_BRUTAL_ATTACKS = 1,
    EVENT_ANNIHILATE = 2,
    EVENT_SHOULDER_CHARGE = 3,
    EVENT_LEAPING_RETREAT = 4,
    EVENT_DEMON_LINK = 5,
    EVENT_FACE_KICK = 6,
};

enum SledgeSpells
{
    SPELL_BRUTAL_ATTACKS = 199556,
    SPELL_DEMON_LINK = 199375,
    SPELL_LEAPING_RETREAT = 199474,
    SPELL_SHOULDER_CHARGE = 199481,
    SPELL_FACE_KICK = 199645,
    SPELL_DEATH_INVIS = 117555,
    SPELL_SEE_DEATH_INVIS = 117491,
    SPELL_STOP_GULDAN_QUEST_ACCEPT = 223661,
    SPELL_STOP_GULDAN_TAKING_POWER_02 = 210461,
    SPELL_STOP_GULDAN_CRUSHER_DIES_01 = 210439,
};

class npc_sledge_crusher : public CreatureScript
{
public:
    npc_sledge_crusher() : CreatureScript("npc_sledge_crusher") { }

    struct npc_sledge_crusher_AI : public ScriptedAI
    {
        npc_sledge_crusher_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            _playerParticipating = false;
            _secondBrutalAttack = false;
            _brutalAnnounced = false;
            _conversationStarted = false;
        }

        void Reset() override
        {
            _events.Reset();
            Initialize();
            me->setActive(true);
            me->SetReactState(REACT_DEFENSIVE);

            if (me->GetVictim() || me->IsInEvadeMode())
                return;

            std::list<Unit*> list;
            me->GetAttackableUnitListInRange(list, 70.0f);
            for (auto enemy : list)
            {
                if (enemy->ToPlayer())
                    continue;
                me->AI()->AttackStart(enemy);
                break;
            }
        }

        void EnterCombat(Unit* /*who*/) override
        {
            if (me->GetEntry() == NPC_SLEDGE) {
                _events.ScheduleEvent(EVENT_ANNIHILATE, 20000);
                _events.ScheduleEvent(EVENT_BRUTAL_ATTACKS, urand(18000, 20000));
            }

            if (me->GetEntry() == NPC_CRUSHER)
                _events.ScheduleEvent(EVENT_FACE_KICK, 16000);

            _events.ScheduleEvent(EVENT_LEAPING_RETREAT, urand(9000, 18000));
            _events.ScheduleEvent(EVENT_SHOULDER_CHARGE, urand(18000, 24000));
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (HealthAbovePct(85) && attacker->IsCreature())
                if (attacker->GetEntry() == NPC_KAYN_SUNFURY_SLEDGE || attacker->GetEntry() == NPC_ALTRUIS_SUFFERER_CRUSHER)
                    damage = urand(1, 2);

            if (HealthBelowPct(85) && attacker->IsCreature())
                if (attacker->GetEntry() == NPC_KAYN_SUNFURY_SLEDGE || attacker->GetEntry() == NPC_ALTRUIS_SUFFERER_CRUSHER)
                    me->SetHealth(me->GetHealth() + damage);

            if (HealthBelowPct(80) && me->GetEntry() == 97632 /* Crusher*/ && !_conversationStarted)
            {
                if (Creature* creature = me->FindNearestCreature(NPC_ALTRUIS_SUFFERER_CRUSHER, me->GetVisibilityRange(), true))
                {
                    creature->AI()->SetData(DATA_ALTRUIS_TALK_OLD_TIMES, DATA_ALTRUIS_TALK_OLD_TIMES);
                    _conversationStarted = true;
                }
            }

            if (Creature* oAdd = GetOtherAdd())
                if (damage < me->GetHealth())
                    oAdd->SetHealth(oAdd->GetHealth() - damage);

            if (attacker->IsPlayer() && me->HasAura(SPELL_BRUTAL_ATTACKS) && !_brutalAnnounced) {
                Talk(0);
                _brutalAnnounced = true;
            }
                
        }

        void JustDied(Unit* killer) override
        {
            if (Creature* oAdd = GetOtherAdd())
                killer->Kill(oAdd, false);

            if (me->GetEntry() == NPC_SLEDGE)
                if (Creature* creature = me->FindNearestCreature(NPC_KAYN_SUNFURY_SLEDGE, me->GetVisibilityRange(), true))
                    creature->AI()->SetData(DATA_SLEDGE_DEATH, DATA_SLEDGE_DEATH);

            if (me->GetEntry() == NPC_CRUSHER)
                if (Creature* creature = me->FindNearestCreature(NPC_ALTRUIS_SUFFERER_CRUSHER, me->GetVisibilityRange(), true))
                    creature->AI()->SetData(DATA_CRUSHER_DEATH, DATA_CRUSHER_DEATH);


            me->GetScheduler().Schedule(Seconds(3), [this](TaskContext context) {
                std::list<Player*> lList;
                me->GetPlayerListInGrid(lList, me->GetVisibilityRange());
                for (auto player : lList) {
                    player->CastSpell(player, SPELL_STOP_GULDAN_TAKING_POWER_02);

                    if (player->GetQuestStatus(QUEST_STOP_GULDAN_H) == QUEST_STATUS_INCOMPLETE
                        || player->GetQuestStatus(QUEST_STOP_GULDAN_A) == QUEST_STATUS_INCOMPLETE)
                            player->KilledMonsterCredit(QUEST_KILL_CREDIT);
                }
            });

            me->DespawnOrUnsummon(20000, Seconds(30));
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = _events.ExecuteEvent())
            {   
                switch (eventId)
                {
                case EVENT_BRUTAL_ATTACKS:
                    DoCast(me, SPELL_BRUTAL_ATTACKS, true);
                    _events.RescheduleEvent(EVENT_BRUTAL_ATTACKS, 42000);
                    _brutalAnnounced = false;
                    break;
                case EVENT_ANNIHILATE:
                    DoCast(SPELL_ANNIHILATE);
                    _events.RescheduleEvent(EVENT_ANNIHILATE, urand(15000, 18000));
                    break;
                case EVENT_FACE_KICK:
                    DoCast(SPELL_FACE_KICK);
                    _events.RescheduleEvent(EVENT_FACE_KICK, urand(16000, 18000));
                    break;
                case EVENT_SHOULDER_CHARGE:
                    DoCast(SPELL_SHOULDER_CHARGE);
                    _events.ScheduleEvent(EVENT_SHOULDER_CHARGE, urand(12000, 16000));
                    break;
                case EVENT_LEAPING_RETREAT:
                    DoCast(SPELL_LEAPING_RETREAT);
                    break;
                default:
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }

        Creature* GetOtherAdd() {

            if (Creature* secondAdd = me->FindNearestCreature((me->GetEntry() == NPC_SLEDGE ? NPC_SLEDGE : NPC_CRUSHER), me->GetVisibilityRange(), true))
            {
                if (secondAdd->IsAlive())
                    return secondAdd;
            }
            return NULL;
        }

    private:
        EventMap _events;
        bool _playerParticipating;
        bool _secondBrutalAttack;
        bool _brutalAnnounced;
        bool _conversationStarted;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sledge_crusher_AI(creature);
    }
};

// guid: 20542914 id: 92985 Altruis the Sufferer to fight with Crusher
enum AltruisCrusherFightTexts
{
    TEXT_SAY_OLD_TIMES = 0,
    TEXT_SAY_ABOUT_ILLIDAN = 1,
    TEXT_SAY_FOLLOW_BLINDLY = 2,
    TEXT_SAY_DIDNT_MURDER = 3,
};

class npc_altruis_crusher_fight : public CreatureScript
{
public:
    npc_altruis_crusher_fight() : CreatureScript("npc_altruis_crusher_fight") { }

    enum AltruisCrusherFightEvents
    {
        EVENT_EYE_BEAM = 1,
        EVENT_BLINK = 2,
        EVENT_UPDATE_PHASES = 3,
        EVENT_SET_DATA_FOR_KAYN_ANSWER_1 = 4,
        EVENT_SET_DATA_FOR_KAYN_ANSWER_2 = 5,
        EVENT_SET_DATA_FOR_KAYN_ANSWER_3 = 6,
    };

    struct npc_altruis_crusher_fightAI : public ScriptedAI
    {
        npc_altruis_crusher_fightAI(Creature* creature) : ScriptedAI(creature) {
            me->SetReactState(REACT_DEFENSIVE);
        }

        bool _talkedAltruisFirstLine = false;
        bool _talkedAltruisSecondLine = false;
        bool _talkedAltruisThirdLine = false;
        bool _talkedAltruisFourthLine = false;

        void MoveInLineOfSight(Unit* who) override
        {
            if (who->IsPlayer())
                if (Creature* creature = me->FindNearestCreature(NPC_CRUSHER, me->GetVisibilityRange(), true))
                    AttackStart(creature);
        }

        void EnterCombat(Unit* who) override
        {
            who->GetAI()->AttackStart(me);
            _events.ScheduleEvent(EVENT_EYE_BEAM, urand(20000, 40000));
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage) override
        {
            if (HealthAbovePct(85))
                damage = urand(1, 2);
            else
                me->SetHealth(me->GetMaxHealth() * 0.85f);
        }

        void SpellHit(Unit* /*caster*/, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_FACE_KICK)
            {
                _events.CancelEvent(EVENT_EYE_BEAM);
                _events.ScheduleEvent(EVENT_BLINK, 1000);
            }
        }

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_ALTRUIS_TALK_OLD_TIMES:
                if (!_talkedAltruisFirstLine) {
                    Talk(TEXT_SAY_OLD_TIMES);
                    _events.ScheduleEvent(EVENT_SET_DATA_FOR_KAYN_ANSWER_1, 3000);
                    _talkedAltruisFirstLine = true;
                }
                break;
            case DATA_ALTRUIS_TALK_AFTER_10K_YEARS:
                if (!_talkedAltruisSecondLine) {
                    Talk(TEXT_SAY_ABOUT_ILLIDAN);
                    _events.ScheduleEvent(EVENT_SET_DATA_FOR_KAYN_ANSWER_2, 7000);
                    _talkedAltruisSecondLine = true;
                }
                break;
            case DATA_ALTRUIS_TALK_FOLLOW_BLINDLY:
                if (!_talkedAltruisThirdLine) {
                    Talk(TEXT_SAY_FOLLOW_BLINDLY);
                    _events.ScheduleEvent(EVENT_SET_DATA_FOR_KAYN_ANSWER_3, 5000);
                    _talkedAltruisThirdLine = true;
                }
                break;
            case DATA_ALTRUIS_TALK_DID_NOT_MURDER:
                if (!_talkedAltruisFourthLine) {
                    Talk(TEXT_SAY_DIDNT_MURDER);
                    _talkedAltruisFourthLine = true;
                }
                break;
            case DATA_CRUSHER_DEATH:
                EnterEvadeMode(EVADE_REASON_OTHER);
                _events.CancelEvent(EVENT_EYE_BEAM);
                _events.CancelEvent(EVENT_SET_DATA_FOR_KAYN_ANSWER_1);
                _events.CancelEvent(EVENT_SET_DATA_FOR_KAYN_ANSWER_2);
                _events.CancelEvent(EVENT_SET_DATA_FOR_KAYN_ANSWER_3);
                break;
            }
        }

        void JustReachedHome() override {}

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {   
                case EVENT_SET_DATA_FOR_KAYN_ANSWER_1:
                    if (Creature* creature = me->FindNearestCreature(NPC_KAYN_SUNFURY_SLEDGE, me->GetVisibilityRange(), true))
                        creature->AI()->SetData(DATA_ALTRUIS_TALK_OLD_TIMES, DATA_ALTRUIS_TALK_OLD_TIMES);
                    break;
                case EVENT_SET_DATA_FOR_KAYN_ANSWER_2:
                    if (Creature* creature = me->FindNearestCreature(NPC_KAYN_SUNFURY_SLEDGE, me->GetVisibilityRange(), true))
                        creature->AI()->SetData(DATA_ALTRUIS_TALK_AFTER_10K_YEARS, DATA_ALTRUIS_TALK_AFTER_10K_YEARS);
                    break;
                case EVENT_SET_DATA_FOR_KAYN_ANSWER_3:
                    if (Creature* creature = me->FindNearestCreature(NPC_KAYN_SUNFURY_SLEDGE, me->GetVisibilityRange(), true))
                        creature->AI()->SetData(DATA_ALTRUIS_TALK_FOLLOW_BLINDLY, DATA_ALTRUIS_TALK_FOLLOW_BLINDLY);
                    break;
                case EVENT_EYE_BEAM:
                    DoCastVictim(SPELL_EYE_BEAM);
                    _events.ScheduleEvent(EVENT_EYE_BEAM, urand(20000, 40000));
                    break;
                case EVENT_BLINK:
                    DoCastVictim(SPELL_BLINK);
                    _events.ScheduleEvent(EVENT_EYE_BEAM, urand(15000, 17000));
                    break;
                default:
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }

    private:
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_altruis_crusher_fightAI(creature);
    }
};

/* Korvas Bloodthorn (97643) https://www.wowhead.com/npc=97643/korvas-bloodthorn */
class npc_korvas_bloodthorn_97643 : public CreatureScript
{
public:
    npc_korvas_bloodthorn_97643() : CreatureScript("npc_korvas_bloodthorn_97643") { }

    bool OnQuestReward(Player* player, Creature* /*creature*/, const Quest* quest, uint32 /*p_Option*/) override
    {
        if (quest->GetQuestId() == QUEST_GRAND_THEFT_FELBAT) {
            WorldLocation loc;
            loc.m_mapId = 1468;
            loc.m_positionX = 4317.87f;
            loc.m_positionY = -451.61f;
            loc.m_positionZ = 259.36f;
            loc.SetOrientation(player->GetOrientation());
            player->SetHomebind(loc, 7866);
            player->SendBindPointUpdate();
        }
        return true;
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_FROZEN_IN_TIME) {
            creature->AI()->Talk(1);

            creature->GetScheduler().Schedule(Seconds(8), [this](TaskContext context)
            {
                Creature* korvas = GetContextCreature();
                korvas->AI()->Talk(2);
            });
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_korvas_bloodthorn_97643_AI(creature);
    }

    struct npc_korvas_bloodthorn_97643_AI : public ScriptedAI
    {
        npc_korvas_bloodthorn_97643_AI(Creature* creature) : ScriptedAI(creature) { }

        bool _greetSaid = false;

        void MoveInLineOfSight(Unit* unit) override
        {
            if (Player* player = unit->ToPlayer())
                if (player->GetDistance(me) < 15.0f)
                    if (player->GetQuestStatus(QUEST_GRAND_THEFT_FELBAT) == QUEST_STATUS_COMPLETE && !_greetSaid) {
                        me->AI()->Talk(0);
                        _greetSaid = true;
                    }
        }
    };
};

/* Reflective Mirror (244449) https://www.wowhead.com/object=244449/reflective-mirror */
enum ReflectiveMirror {
    NPC_GLAZER = 96680,
    SPELL_ROTATING = 191917,
    SPELL_ARCANE_EXPLOSION = 202220,
    PHASE_GLAZER_STUNNED = 556,
};
class go_reflective_mirror : public GameObjectScript
{
public:
    go_reflective_mirror() : GameObjectScript("go_reflective_mirror") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        player->CastSpell(go, SPELL_ROTATING, true);

        if (Creature* glazer = player->FindNearestCreature(NPC_GLAZER, player->GetVisibilityRange(), true))
            glazer->CastSpell(glazer, SPELL_ARCANE_EXPLOSION, true);

        return true;
    }
};

/* Lingering Gaze https://www.wowhead.com/spell=196460/lingering-gaze */
class spell_196460 : public SpellScriptLoader
{
public:
    spell_196460() : SpellScriptLoader("spell_196460") { }

    class spell_196460_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_196460_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (!GetCaster())
                return;

            uint32 missiles = urand(1, 3);
            float directionX = frand(0.0f, 6.0f);
            float directionY = 6.0f - directionX;
            if (urand(0, 1))
                directionX *= -1.0f;
            if (urand(0, 1))
                directionY *= -1.0f;

            Position pos = GetCaster()->GetRandomNearPosition(25.0f);
            for (uint8 i = 0; i < missiles; i++)
            {
                GetCaster()->CastSpell(pos, 196504, true);
                pos.m_positionX += directionX;
                pos.m_positionY += directionY;
            }
        }

        void Register() override
        {
            OnEffectLaunch += SpellEffectFn(spell_196460_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_196460_SpellScript();
    }
};

/* Pulse https://www.wowhead.com/spell=196462/pulse */
class spell_196462 : public SpellScriptLoader
{
public:
    spell_196462() : SpellScriptLoader("spell_196462") { }

    class spell_196462_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_196462_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (!GetCaster())
                return;

            Position pos = GetCaster()->GetPosition();
            pos.SetOrientation(frand(0.0f, 2.0f) * static_cast<float>(M_PI));
            GetCaster()->CastSpell(pos, 194853, true);
        }

        void Register() override
        {
            OnEffectLaunch += SpellEffectFn(spell_196462_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_196462_SpellScript();
    }
};

enum eCountermeasures
{
    KILL_CREDIT_WESTERN_COUNTERMEASURE      = 99732,
    KILL_CREDIT_SOUTHERN_COUNTERMEASURE     = 99731,
    KILL_CREDIT_EASTERN_COUNTERMEASURE      = 99709,
};

// 204588
class spell_activate_countermeasure : public SpellScriptLoader
{
public:
    spell_activate_countermeasure() : SpellScriptLoader("spell_activate_countermeasure") { }

    class spell_activate_countermeasure_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_activate_countermeasure_SpellScript);

        void HandleKillCredit()
        {
            if (Creature* creature = GetCaster()->ToPlayer()->FindNearestCreature(99732, 5.0f))
                GetCaster()->ToPlayer()->KilledMonsterCredit(KILL_CREDIT_WESTERN_COUNTERMEASURE, ObjectGuid::Empty);

            if (Creature* creature = GetCaster()->ToPlayer()->FindNearestCreature(99731, 5.0f))
                GetCaster()->ToPlayer()->KilledMonsterCredit(KILL_CREDIT_SOUTHERN_COUNTERMEASURE, ObjectGuid::Empty);

            if (Creature* creature = GetCaster()->ToPlayer()->FindNearestCreature(99709, 5.0f))
                GetCaster()->ToPlayer()->KilledMonsterCredit(KILL_CREDIT_EASTERN_COUNTERMEASURE, ObjectGuid::Empty);
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_activate_countermeasure_SpellScript::HandleKillCredit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_activate_countermeasure_SpellScript();
    }
};

class q_frozen_in_time : public QuestScript
{
public:
    q_frozen_in_time() : QuestScript("q_frozen_in_time") { }

    void OnQuestStatusChange(Player* player, Quest const* /*quest*/, QuestStatus /*oldStatus*/, QuestStatus newStatus) override
    {
        if (newStatus == QUEST_STATUS_COMPLETE)
        {
            if (Creature* ashgolm = player->FindNearestCreature(96681, 200.0f))
                ashgolm->CastSpell(nullptr, 200354, true);
        }
    }
};

// 244644 Warden's Ascent
class go_warden_ascent : public GameObjectScript
{
public:
    go_warden_ascent() : GameObjectScript("go_warden_ascent") { }

    struct go_warden_ascentAI : public GameObjectAI
    {
        go_warden_ascentAI(GameObject* pGO) : GameObjectAI(pGO) {}

        uint32 giveKillCredit;

        void Reset()
        {
            giveKillCredit = 1000;
        }

        void UpdateAI(uint32 diff)
        {
            std::list<Player*> playerList;
            go->GetPlayerListInGrid(playerList, 10.0f);
            for (Player* player : playerList)
            {
                if (player->GetQuestStatus(39686) == QUEST_STATUS_INCOMPLETE)
                {
                    if (giveKillCredit <= diff)
                    {
                        if (player->GetPositionZ() >= 253.0f) {
                            player->KilledMonsterCredit(96814, ObjectGuid::Empty);
                            player->AddDelayedConversation(2000, 6804);
                        }

                        giveKillCredit = 1000;
                    }
                    else
                        giveKillCredit -= diff;
                }
            }
        }
    };

    GameObjectAI* GetAI(GameObject* pGO) const
    {
        return new go_warden_ascentAI(pGO);
    }
};

// 243967
class go_pool_of_judgements : public GameObjectScript
{
public:
    go_pool_of_judgements() : GameObjectScript("go_pool_of_judgements") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        player->KilledMonsterCredit(100166, ObjectGuid::Empty);
        player->SendMovieStart(478);
        return false;
    }
};

/* Kayn Subfury (97273) or Altruis the Sufferer (97274) will assist the Player in Bastillax fight */
class npc_bastillax_attacker : public CreatureScript
{
    enum atData {
        NPC_BASTILLAX = 96783,
        DATA_BASTILLAX_DEATH = 21,
        EVENT_EYE_BEAM = 1,
        EVENT_CHAOS_STRIKE = 2,
        SPELL_EYE_BEAM = 197641,
        SPELL_CHAOS_STRIKE = 197639,
    };
public:
    npc_bastillax_attacker() : CreatureScript("npc_bastillax_attacker") { }

    struct npc_bastillax_attacker_AI : public ScriptedAI
    {
        npc_bastillax_attacker_AI(Creature* creature) : ScriptedAI(creature) {
            me->SetReactState(REACT_DEFENSIVE);
        }

        void MoveInLineOfSight(Unit* who) override {
            if (Player* player = who->ToPlayer())
                if (player->GetDistance(me) < 20.0f && player->IsInCombat())
                    if (player->HasQuest(QUEST_BETWEEN_US_AND_FREEDOM_HA) ||
                        player->HasQuest(QUEST_BETWEEN_US_AND_FREEDOM_HH) ||
                        player->HasQuest(QUEST_BETWEEN_US_AND_FREEDOM_VA) ||
                        player->HasQuest(QUEST_BETWEEN_US_AND_FREEDOM_VH))
                            if (Creature* bastillax = me->FindNearestCreature(NPC_BASTILLAX, me->GetVisibilityRange(), true))
                                AttackStart(bastillax);
        }

        void EnterCombat(Unit* who) override
        {   
            _events.ScheduleEvent(EVENT_EYE_BEAM, urand(20000, 35000));
            _events.ScheduleEvent(EVENT_CHAOS_STRIKE, urand(15000, 45000));
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage) override
        {
            if (HealthBelowPct(45))
                damage = urand(1, 2);
            else
                me->SetHealth(me->GetMaxHealth() * 0.85f);
        }

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_BASTILLAX_DEATH:
                Talk(0);
                EnterEvadeMode(EVADE_REASON_OTHER);
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_EYE_BEAM:
                    DoCast(SPELL_EYE_BEAM);
                    _events.ScheduleEvent(EVENT_EYE_BEAM, 12000);
                    break;
                case EVENT_CHAOS_STRIKE:
                    DoCast(SPELL_CHAOS_STRIKE);
                    _events.ScheduleEvent(EVENT_EYE_BEAM, 22000);
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }

    private:
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_bastillax_attacker_AI(creature);
    }
};

/* Bastillax (96783) https://www.wowhead.com/npc=96783/bastillax#abilities
 * Abilities:
 * - Blur of Shadows (https://www.wowhead.com/spell=200002/blur-of-shadows)
 * - Crushing Shadows (https://www.wowhead.com/spell=200027/crushing-shadows)
 * - Crushing Shadows (https://www.wowhead.com/spell=200066/crushing-shadows)
 * - Fel Annihilation (https://www.wowhead.com/spell=200007/fel-annihilation)
 * - Portal Surge (https://www.wowhead.com/spell=200104/portal-surge)
 */
enum eBastillax
{
    EVENT_FEL_ANNIHILATION = 0,
    EVENT_CRUSHING_SHADOWS = 1,
    EVENT_BLUR_OF_SHADOWS = 2,
    EVENT_PORTAL_SURGE = 3,
    SPELL_FEL_ANNIHILATION = 200007,
    SPELL_CRUSHING_SHADOWS = 200066,
    SPELL_BLUR_OF_SHADOWS = 200002,
    SPELL_PORTAL_SURGE = 200104,
    SPELL_POWER_02 = 210500,
    BASTILLAXS_POWER_QUEST_CREDIT = 106255,
};

class npc_bastillax : public CreatureScript
{
public:
    npc_bastillax() : CreatureScript("npc_bastillax") { }

    struct npc_bastillaxAI : public ScriptedAI
    {
        npc_bastillaxAI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            _firstTextTrigger = false;
            _secondTextTrigger = false;
            _thirdTextTrigger = false;
            me->SetCorpseDelay(30);
            me->SetRespawnDelay(15);
        }

        void Reset() override
        {
            events.Reset();
            Initialize();
        }

        void JustDied(Unit* killer) override
        {   
            /* Give Kill Credit to all players in the range */
            std::list<Player*> players;
            me->GetPlayerListInGrid(players, 30.0f);
            for (Player* player : players)
            {
                player->KilledMonsterCredit(BASTILLAXS_POWER_QUEST_CREDIT);
                player->CastSpell(player, SPELL_POWER_02);
                player->ClearInCombat();
            }

            /* Set Data for Kayn (97273) and Altruis (97274) to talk and go */
            if (Creature* creature = me->FindNearestCreature(97273, me->GetVisibilityRange(), true))
                creature->AI()->SetData(21, 21);
            if (Creature* creature = me->FindNearestCreature(97274, me->GetVisibilityRange(), true))
                creature->AI()->SetData(21, 21);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            events.RescheduleEvent(EVENT_FEL_ANNIHILATION, urand(4000, 6000));
            events.RescheduleEvent(EVENT_CRUSHING_SHADOWS, 22000);
            events.RescheduleEvent(EVENT_BLUR_OF_SHADOWS, 13000);
            events.RescheduleEvent(EVENT_PORTAL_SURGE, 35000);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (HealthBelowPct(65) && !_firstTextTrigger) {
                Talk(0);
                _firstTextTrigger = true;
            }

            if (HealthBelowPct(50) && !_secondTextTrigger) {
                Talk(1);
                _secondTextTrigger = true;
            }

            if (HealthBelowPct(25) && !_thirdTextTrigger) {
                Talk(2);
                _thirdTextTrigger = true;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_FEL_ANNIHILATION:
                    DoCast(SPELL_FEL_ANNIHILATION);
                    events.RescheduleEvent(EVENT_FEL_ANNIHILATION, 15000);
                    break;
                case EVENT_CRUSHING_SHADOWS:
                    DoCast(SPELL_CRUSHING_SHADOWS);
                    events.RescheduleEvent(EVENT_CRUSHING_SHADOWS, 32000);
                    break;
                case EVENT_BLUR_OF_SHADOWS:
                    Talk(3);
                    DoCast(SPELL_BLUR_OF_SHADOWS);
                    events.RescheduleEvent(EVENT_BLUR_OF_SHADOWS, 23000);
                    break;
                case EVENT_PORTAL_SURGE:
                    DoCast(SPELL_PORTAL_SURGE);
                    for (uint8 i = 0; i < 3; i++)
                    {
                        if (Creature* add = me->SummonCreature(101505, 4221.51f + irand(-3, 3), -627.92f + irand(-3, 3), 255.12f, 3.10f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 30000))
                        {
                            add->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
                            if (Unit* target = me->GetVictim())
                                add->AI()->AttackStart(target);
                        }
                    }
                    for (uint8 i = 0; i < 3; i++)
                    {
                        if (Creature* add = me->SummonCreature(101505, 4146.97f + irand(-3, 3), -626.29f + irand(-3, 3), 255.12f, 6.27f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 30000))
                        {
                            add->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
                            if (Unit* target = me->GetVictim())
                                add->AI()->AttackStart(target);
                        }
                    }
                    events.RescheduleEvent(EVENT_PORTAL_SURGE, 50000);
                    break;
                default:
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }
    private:
        EventMap events;
        bool _firstTextTrigger;
        bool _secondTextTrigger;
        bool _thirdTextTrigger;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_bastillaxAI(creature);
    }
};

//  Cyanna: 20543125 (96672)
enum CyanaImmolanthFightData
{
    DATA_IMMOLANTH_DEATH = 1,
};

enum CyanaImmolanthFightTexts
{
    TEXT_DEATH = 0,
};

enum CyanaImmolanthFightMisc
{
    NPC_IMMOLANTH = 96682,
};

class npc_cyana_immolanth_fight : public CreatureScript
{
public:
    npc_cyana_immolanth_fight() : CreatureScript("npc_cyana_immolanth_fight") { }

    struct npc_cyana_immolanth_fightAI : public ScriptedAI
    {
        npc_cyana_immolanth_fightAI(Creature* creature) : ScriptedAI(creature) {
            me->SetReactState(REACT_DEFENSIVE);
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (who->IsPlayer())
                if (Creature* creature = me->FindNearestCreature(NPC_IMMOLANTH, me->GetVisibilityRange(), true))
                    AttackStart(creature);
        }

        void EnterCombat(Unit* who) override
        {
            who->GetAI()->AttackStart(me);
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage) override
        {
            if (HealthAbovePct(85))
                damage = urand(1, 2);
            else
                me->SetHealth(me->GetMaxHealth() * 0.85f);
        }

        void SpellHit(Unit* /*caster*/, SpellInfo const* spell) override {}

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_IMMOLANTH_DEATH:
                Talk(TEXT_DEATH);
                EnterEvadeMode(EVADE_REASON_OTHER);
                break;
            }
        }

        void JustReachedHome() override {}

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            // while (uint32 eventId = _events.ExecuteEvent())
            // {
                // switch (eventId)
                // {
                    // case EVENT_TEMPERED_FURY:
                    //     DoCastVictim(SPELL_TEMPERED_FURY);
                    //     _events.ScheduleEvent(EVENT_TEMPERED_FURY, urand(2000, 4000));
                    //     break;
                // }
            // }

            DoMeleeAttackIfReady();
        }

    private:
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_cyana_immolanth_fightAI(creature);
    }
};

/**
* NPC: Immolanth (96682)
* Abilities:
* - 199758 Burning Fel
* - 199828 Chaos Nova
* - 199836 Fel Spirit
*/
enum ImmolanthEvents
{
    EVENT_BURNING_FEL = 1,
    EVENT_CHAOS_NOVA = 2,
    EVENT_SUMMON_BURNING_FEL = 3,
    EVENT_FEL_SPIRIT = 3,
};

enum ImmolanthSpells
{
    SPELL_CHAOS_NOVA = 199828,
    SPELL_BURNING_FEL = 199758,
    SPELL_FEL_SPIRIT = 199836,
};

enum ImmolanthMisc
{
    NPC_CYANA_IMMOLANTH = 96672,
    NPC_BURNING_FEL = 60685,
    KILL_CREDIT_BONUS_OBJECTIVE = 97970,
    IMMOLANTH_POWER_TAKEN = 106254,
    FORGED_IN_FIRE_TAKING_POWER_02 = 210486,
    FORGED_IN_FIRE_IMMOLANTH_DIES_01 = 210483,
};

class npc_immolanth : public CreatureScript
{
public:
    npc_immolanth() : CreatureScript("npc_immolanth") { }

    struct npc_immolanthAI : public ScriptedAI
    {
        npc_immolanthAI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            _playerParticipating = false;
            _phase1 = false;
            _phase2 = false;
            me->SetHealth(me->CountPctFromMaxHealth(27));
            me->setRegeneratingHealth(false);
        }

        void Reset() override
        {
            _events.Reset();
            Initialize();
            me->setActive(true);
            me->SetReactState(REACT_PASSIVE);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            _events.ScheduleEvent(EVENT_BURNING_FEL, 18000);
            _events.ScheduleEvent(EVENT_FEL_SPIRIT, 8000);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (HealthBelowPct(27) && attacker->IsCreature())
                if (attacker->GetEntry() == NPC_CYANA_IMMOLANTH)
                    damage = urand(1, 2);

            if (HealthBelowPct(15) && !_phase1) {
                Talk(0);
                _phase1 = true;
            }

            if (HealthBelowPct(6) && !_phase2) {
                Talk(1);
                _phase2 = true;
                _events.ScheduleEvent(EVENT_CHAOS_NOVA, Seconds(1));
            }   

            if (!_playerParticipating && attacker->ToPlayer()) {
                if (Creature* creature = me->FindNearestCreature(NPC_CYANA_IMMOLANTH, me->GetVisibilityRange(), true))
                    _playerParticipating = true;
            }
        }

        void JustDied(Unit* /*killer*/) override
        {
            if (Creature* creature = me->FindNearestCreature(NPC_CYANA_IMMOLANTH, me->GetVisibilityRange(), true))
                creature->AI()->SetData(DATA_IMMOLANTH_DEATH, DATA_IMMOLANTH_DEATH);

            std::list<Player*> players;
            me->GetPlayerListInGrid(players, 30.0f);
            for (Player* player : players)
            {
                player->CastSpell(player, FORGED_IN_FIRE_TAKING_POWER_02, true);
                player->KilledMonsterCredit(IMMOLANTH_POWER_TAKEN);
                player->KilledMonsterCredit(KILL_CREDIT_BONUS_OBJECTIVE);
            }

            me->DespawnOrUnsummon(20000, Seconds(1));
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
                case EVENT_CHAOS_NOVA:
                    if (Unit* target = me->GetVictim())
                        me->CastSpell(target, SPELL_CHAOS_NOVA, true);
                    break;
                case EVENT_BURNING_FEL:
                    if (Unit* target = me->GetVictim())
                        me->CastSpell(target, SPELL_BURNING_FEL, true);
                    _events.ScheduleEvent(EVENT_BURNING_FEL, urand(10000, 14000));
                    break;
                case EVENT_FEL_SPIRIT:
                    if (Unit* target = me->GetVictim())
                        me->CastSpell(target, SPELL_FEL_SPIRIT, true);
                    _events.ScheduleEvent(EVENT_FEL_SPIRIT, urand(8000, 12000));
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }

    private:
        EventMap _events;
        bool _playerParticipating;
        bool _phase1;
        bool _phase2;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_immolanthAI(creature);
    }
};

/* Burning Fel https://www.wowhead.com/spell=199760/burning-fel */
class spell_199760 : public SpellScriptLoader
{
public:
    spell_199760() : SpellScriptLoader("spell_199760") { }
    class spell_199760_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_199760_SpellScript);
        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            PreventHitDefaultEffect(EFFECT_0);
            if (!GetCaster())
                return;
            Position pos;
            GetCaster()->GetRandomNearPosition(20.0f);
            WorldLocation* dest = const_cast<WorldLocation*>(GetExplTargetDest());
            dest->Relocate(pos);
        }
        void Register() override
        {
            OnEffectLaunch += SpellEffectFn(spell_199760_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_TRIGGER_MISSILE);
        }
    };
    SpellScript* GetSpellScript() const override
    {
        return new spell_199760_SpellScript();
    }
};

// 96681
struct npc_vow_ashgolm : public ScriptedAI
{
    npc_vow_ashgolm(Creature* creature) : ScriptedAI(creature) { }

    enum Spells
    {
        SPELL_FISSURE = 192522,
        SPELL_LAVA = 192519,
        SPELL_LAVA_WREATH = 192631,
    };

    void Reset() override { }

    void EnterCombat(Unit*) override
    {
        me->GetScheduler().Schedule(Seconds(15), [this](TaskContext context)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                me->CastSpell(target, SPELL_FISSURE);

            context.Repeat(Seconds(35));
        })
            .Schedule(Seconds(45), [this](TaskContext context)
        {
            me->CastSpell(nullptr, SPELL_LAVA);
            me->CastSpell(nullptr, SPELL_LAVA_WREATH);
            
            context.Repeat(Seconds(30));
        });
    }
};

enum eChoices
{
    PLAYER_CHOICE_DH_FOLLOWER_SELECTION = 234,
    PLAYER_CHOICE_DH_FOLLOWER_SELECTION_KAYN = 486,
    PLAYER_CHOICE_DH_FOLLOWER_SELECTION_ALTRUIS = 487,
    SPELL_NEW_DIRECTION_CHOICE_KAYN_OR_ALTRUIS = 196650,
    SPELL_NEW_DIRECTION_CHOSE_ALTRUIS = 196662,
    SPELL_NEW_DIRECTION_CHOSE_KAYN = 196661,
    QUEST_OBTAINED_KAYN = 40374,
    QUEST_OBTAINED_ALTRUIS = 40375,
};

/* Korvas Bloodthorn (97644) https://www.wowhead.com/npc=97644/korvas-bloodthorn */
class npc_korvas_bloodthorn : public CreatureScript
{
public:
    npc_korvas_bloodthorn() : CreatureScript("npc_korvas_bloodthorn") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        player->CastSpell(player, SPELL_NEW_DIRECTION_CHOICE_KAYN_OR_ALTRUIS, true); // Display follower choice 234
        
        return false;
    }

    bool OnQuestReward(Player* player, Creature* /*creature*/, const Quest* quest, uint32 /*p_Option*/) override
    {
        if (quest->GetQuestId() == QUEST_ALL_THE_WAY_UP) {
            WorldLocation loc;
            loc.m_mapId = 1468; // Warden Prison DH Quests
            loc.m_positionX = 4282.88f;
            loc.m_positionY = -452.90f;
            loc.m_positionZ = 259.51f;
            loc.SetOrientation(player->GetOrientation());
            player->SetHomebind(loc, 7865); // The Wardens Court
            player->SendBindPointUpdate();
        }
        return true;
    }
    
    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_BETWEEN_US_AND_FREEDOM_HA ||
            quest->GetQuestId() == QUEST_BETWEEN_US_AND_FREEDOM_HH ||
            quest->GetQuestId() == QUEST_BETWEEN_US_AND_FREEDOM_VA ||
            quest->GetQuestId() == QUEST_BETWEEN_US_AND_FREEDOM_VH)
                creature->AI()->Talk(1);
    
        return true;
    }
    
    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_korvas_bloodthorn_AI(creature);
    }
    
    struct npc_korvas_bloodthorn_AI : public ScriptedAI
    {
        npc_korvas_bloodthorn_AI(Creature* creature) : ScriptedAI(creature) { }
    
        bool _greetSaid = false;
    
        void MoveInLineOfSight(Unit* unit) override
        {
            if (Player* player = unit->ToPlayer())
                if (player->GetDistance(me) < 15.0f)
                    if (player->GetQuestStatus(QUEST_ALL_THE_WAY_UP) == QUEST_STATUS_COMPLETE && !_greetSaid)
                    {
                        me->AI()->Talk(0);
                        if (Creature* kayn = me->FindNearestCreature(97265, me->GetVisibilityRange(), true))
                            kayn->AI()->SetData(24, 24);
                        if (Creature* altruis = me->FindNearestCreature(97267, me->GetVisibilityRange(), true))
                            altruis->AI()->SetData(24, 24);
                        _greetSaid = true;
                    }
        }
    };
};

/* Kayn (97265) and Altruis (97267) scripts for quest "A New Direction" */
enum eData {
    DATA_CHOICE_KAYN = 22,
    DATA_CHOICE_ALTRUIS = 23,
    DATA_START_CONVERSATION = 24,
};
class npc_votw_kayn_altruis_choice : public CreatureScript
{   
public:
    npc_votw_kayn_altruis_choice() : CreatureScript("npc_votw_kayn_altruis_choice") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_votw_kayn_altruis_choice_AI(creature);
    }

    struct npc_votw_kayn_altruis_choice_AI : public ScriptedAI
    {
        npc_votw_kayn_altruis_choice_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize() {
            /*if (me->GetEntry() == 97265)
                if (Creature* altruis = me->FindNearestCreature(97267, me->GetVisibilityRange(), true))
                    AttackStart(altruis);
            if (me->GetEntry() == 97267)
                if (Creature* kayn = me->FindNearestCreature(97265, me->GetVisibilityRange(), true))
                    AttackStart(kayn);*/
        }

        void Reset() override
        {
            Initialize();
            me->SetCorpseDelay(0);
            me->SetRespawnDelay(0);
            me->SetRespawnTime(0);
        }

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_CHOICE_KAYN:
                if (me->GetEntry() == 97267) { // Altruis
                    Talk(1);
                    me->GetScheduler().Schedule(Seconds(6), [this](TaskContext context)
                    {
                        Creature* altruis = GetContextCreature();
                        altruis->GetMotionMaster()->MovePoint(4227.93f, -449.99f, 266.79f, false);
                        altruis->DespawnOrUnsummon(6000, Seconds(15));
                    });
                }
                break;
            case DATA_CHOICE_ALTRUIS:
                if (me->GetEntry() == 97265) { // Kayn
                    Talk(2);
                }
                me->GetScheduler().Schedule(Seconds(6), [this](TaskContext context)
                {
                    Creature* kayn = GetContextCreature();
                    kayn->GetMotionMaster()->MovePoint(4227.93f, -449.99f, 266.79f, false);
                    kayn->DespawnOrUnsummon(6000, Seconds(15));
                });
                break;
            case DATA_START_CONVERSATION:
                if (me->GetEntry() == 97265)
                {
                    me->GetScheduler().Schedule(Seconds(4), [this](TaskContext context)
                    {
                        Creature* kayn = GetContextCreature();
                        kayn->AI()->Talk(0);
                    })
                    .Schedule(Seconds(18), [this](TaskContext context)
                    {
                        Creature* kayn = GetContextCreature();
                        kayn->AI()->Talk(1);
                    });
                }
                if (me->GetEntry() == 97267)
                {
                    me->GetScheduler().Schedule(Seconds(13), [this](TaskContext context)
                    {
                        Creature* altruis = GetContextCreature();
                        altruis->AI()->Talk(0);
                    });
                }
                break;
            }
        }
    };
};

class PlayerScript_follower_choice : public PlayerScript
{
public:
    PlayerScript_follower_choice() : PlayerScript("PlayerScript_follower_choice") {}

    void OnPlayerChoiceResponse(Player* player, uint32 choiceID, uint32 responseID) override
    {
        if (choiceID != PLAYER_CHOICE_DH_FOLLOWER_SELECTION)
            return;

        switch (responseID)
        {
        case PLAYER_CHOICE_DH_FOLLOWER_SELECTION_KAYN:
            player->CastSpell(player, SPELL_NEW_DIRECTION_CHOSE_KAYN, true);
            player->ForceCompleteQuest(QUEST_OBTAINED_KAYN);
            if (Creature* altruis = player->FindNearestCreature(97267, player->GetVisibilityRange(), true))
                altruis->AI()->SetData(22, 22);
            break;
        case PLAYER_CHOICE_DH_FOLLOWER_SELECTION_ALTRUIS:
            player->CastSpell(player, SPELL_NEW_DIRECTION_CHOSE_ALTRUIS, true);
            player->ForceCompleteQuest(QUEST_OBTAINED_ALTRUIS);
            if (Creature* kayn = player->FindNearestCreature(97265, player->GetVisibilityRange(), true))
                kayn->AI()->SetData(23, 23);
            break;
        default:
            break;
        }
    }
};

// 20543507 (97978)
class npc_khadgar : public CreatureScript
{
public:
    npc_khadgar() : CreatureScript("npc_khadgar") { }
    enum eKhadgar {
        SPELL_TELEPORT_TO_STORMWIND = 192757,
        SPELL_TELEPORT_TO_ORGRIMMAR = 192758,
    };
    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) override
    {
        if (quest->GetQuestId() == QUEST_ILLIDARI_LEAVING_H)
        {
            player->CastSpell(player, SPELL_TELEPORT_TO_ORGRIMMAR, true);
        } else if (quest->GetQuestId() == QUEST_ILLIDARI_LEAVING_A)
        {
            player->CastSpell(player, SPELL_TELEPORT_TO_STORMWIND, true);
        }

        return true;
    }
};

class npc_maiev_shadowsong : public CreatureScript
{
public:
    npc_maiev_shadowsong() : CreatureScript("npc_maiev_shadowsong") { }
    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_STOP_GULDAN_H || QUEST_STOP_GULDAN_A)
            player->CastSpell(player, 187864);
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_maiev_shadowsong_AI(creature);
    }

    struct npc_maiev_shadowsong_AI : public ScriptedAI
    {
        npc_maiev_shadowsong_AI(Creature* creature) : ScriptedAI(creature) { }

        bool _greetSaid = false;

        void MoveInLineOfSight(Unit* unit) override
        {
            if (Player* player = unit->ToPlayer())
                if (player->GetDistance(me) < 10.0f)
                    if (player->GetQuestStatus(QUEST_RISE_OF_THE_ILLIDARI) == QUEST_STATUS_COMPLETE
                        && player->GetQuestStatus(QUEST_FEL_INFUSION) == QUEST_STATUS_COMPLETE
                        && !_greetSaid)
                    {
                        me->AI()->Talk(1);
                        _greetSaid = true;
                    }
        }
    };
 };

/* https://www.wowhead.com/spell=187864/play-scene
 * (1423) 7.0 DH-VotW - Illidan's Chamber - Illidan Breakout
 */
class spell_play_scene_1423 : public SpellScriptLoader
{
public:
    spell_play_scene_1423() : SpellScriptLoader("spell_play_scene_1423") { }

    class spell_play_scene_1423_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_play_scene_1423_AuraScript);

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* target = GetTarget();

            if (!target || !target->ToPlayer())
                return;

            target->ToPlayer()->TeleportTo(1468, 4084.27f, -298.11f, -282.07f, 3.118031f);
            target->ToPlayer()->KilledMonsterCredit(99303);
        }

        void Register() override
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_play_scene_1423_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PLAY_SCENE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_play_scene_1423_AuraScript();
    }
};


enum eLegionPortal {
    SPELL_PORTAL_EXPLOSION = 196084,
    SPELL_DESTROYING_LEGION_PORTAL = 202064,
    SPELL_KILL_CREDIT_BONUS_OBJECTIVE = 97969,
};
class npc_legion_portal : public CreatureScript
{
public:
    npc_legion_portal() : CreatureScript("npc_legion_portal") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        player->CastSpell(creature, SPELL_DESTROYING_LEGION_PORTAL, true);
        player->CastSpell(creature, SPELL_PORTAL_EXPLOSION, true);
        creature->DespawnOrUnsummon(25);
        player->KilledMonsterCredit(SPELL_KILL_CREDIT_BONUS_OBJECTIVE, ObjectGuid::Empty);
        return true;
    }
};

//class On100DHArrival : public PlayerScript
//{
//public:
//    On100DHArrival() : PlayerScript("On100DHArrival") { }
//    enum
//    {
//        SPELL_DH_IMPRISON = 217832,
//        SPELL_DH_DARKNESS = 196718,
//        SPELL_DH_BLADE_DANCE = 188499,
//        SPELL_DH_SIGIL_OF_FLAME = 204596,
//    };
//
//    void OnLogin(Player* player, bool firstLogin) override
//    {
//        // For recovery purposes
//        if (player->getLevel() >= 100 && firstLogin)
//            Handle100DHArrival(player);
//    }
//
//    void OnLevelChanged(Player* player, uint8 oldLevel) override
//    {
//        if (oldLevel < 100 && player->getLevel() >= 100)
//            Handle100DHArrival(player);
//    }
//
//    void Handle100DHArrival(Player* player)
//    {
//        if (player->getClass() == CLASS_DEMON_HUNTER)
//        {
//            player->LearnSpell(SPELL_DH_IMPRISON, false);
//            if (player->GetSpecializationId() == TALENT_SPEC_DEMON_HUNTER_HAVOC) {
//                player->LearnSpell(SPELL_DH_BLADE_DANCE, false);
//            }
//            else {
//                player->LearnSpell(SPELL_DH_SIGIL_OF_FLAME, false);
//            }
//        }
//    }
//};

class PlayerScript_bonus_objective : public PlayerScript
{
public:
    PlayerScript_bonus_objective() : PlayerScript("PlayerScript_bonus_objective") {}

    uint32 checkTimer = 1000;

    void OnUpdate(Player* player, uint32 diff) override
    {
        if (checkTimer <= diff)
        {
            if (player->getClass() == CLASS_DEMON_HUNTER && player->GetAreaId() == 7873 && player->GetQuestStatus(QUEST_BREAKING_OUT) == QUEST_STATUS_REWARDED)
            {
                if (player->GetQuestStatus(QUEST_VAULT_OF_THE_WARDENS) == QUEST_STATUS_NONE)
                {
                    if (const Quest* quest = sObjectMgr->GetQuestTemplate(QUEST_VAULT_OF_THE_WARDENS))
                        player->AddQuest(quest, nullptr);
                }
            }

            checkTimer = 1000;
        }
        else checkTimer -= diff;
    }
};

/* Attempt to script Kayn and Altruis for quest 'Breaking Out' */
class npc_altruis_sufferer_freed_99632 : public CreatureScript {
public:
    npc_altruis_sufferer_freed_99632() : CreatureScript("npc_altruis_sufferer_freed_99632") { }

    enum eAltruisFreed {
        PHASE_NONE = 0,
        PHASE_CONTINUE = -1,
        DATA_EVENT_STARTER_GUID = 0,
        QUEST_BREAKING_OUT = 38672,
        PHASE_PEEK_WEAPONS_1 = 1,
        PHASE_PEEK_WEAPONS_2 = 2,
        PHASE_PEEK_WEAPONS_3 = 3,
        PHASE_PEEK_WEAPONS_4 = 4,
        PHASE_DESPAWN = 5,
        WP_START = 1,
        WP_AT_WEAPON_CRATE = 6,
        WP_AT_HOME = 10,
        DATA_TALK_QUEST_COMPLETE = 21,
        EVENT_TALK_1 = 22,
    };

    struct npc_altruis_sufferer_freed_99632_AI : public npc_escortAI
    {
        npc_altruis_sufferer_freed_99632_AI(Creature* creature) : npc_escortAI(creature)
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

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_TALK_QUEST_COMPLETE:
                _events.ScheduleEvent(EVENT_TALK_1, 2s);
                break;
            default:
                break;
            }
        }

        void Reset() override
        {
            Initialize();
            _events.Reset();
        }

        void IsSummonedBy(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
            {
                _eventStarterGuid = who->GetGUID();
                me->SetWalk(true);
                me->LoadEquipment(2);
                Start(false, false, _eventStarterGuid);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent()) {
                switch (eventId) {
                case EVENT_TALK_1:
                    Talk(1);
                    break;
                default:
                    break;
                }
            }

            if (UpdateVictim())
                DoMeleeAttackIfReady();

            /*if (HasEscortState(STATE_ESCORT_NONE))
                return;*/

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
                    case PHASE_PEEK_WEAPONS_1:
                        me->LoadEquipment(3);
                        _moveTimer = 2 * IN_MILLISECONDS;
                        _phase = PHASE_PEEK_WEAPONS_2;
                        break;
                    case PHASE_PEEK_WEAPONS_2:
                        me->HandleEmoteCommand(EMOTE_STATE_KNEEL_2);
                        me->LoadEquipment(1);
                        if (Player* player = ObjectAccessor::GetPlayer(*me, _eventStarterGuid))
                        {
                            player->KilledMonsterCredit(KILL_CREDIT_ALTRUIS_PICKED_UP_WEAPONS, ObjectGuid::Empty);
                        }   
                        _moveTimer = 2 * IN_MILLISECONDS;
                        _phase = PHASE_PEEK_WEAPONS_3;
                        break;
                    case PHASE_PEEK_WEAPONS_3:
                        me->HandleEmoteCommand(EMOTE_STATE_NONE);
                        SetEscortPaused(false);
                        _moveTimer = 0 * IN_MILLISECONDS;
                        _phase = PHASE_NONE;
                        break;
                        SetEscortPaused(true);
                    case PHASE_DESPAWN:
                        // me->DespawnOrUnsummon();
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
            case WP_START:
                _moveTimer = 0 * IN_MILLISECONDS;
                _phase = PHASE_NONE;
                Talk(0);
                break;
            case WP_AT_WEAPON_CRATE:
                SetEscortPaused(true);
                me->SetOrientation(2.81188f);
                me->HandleEmoteCommand(EMOTE_STATE_KNEEL_2);
                _moveTimer = 0.2 * IN_MILLISECONDS;
                _phase = PHASE_PEEK_WEAPONS_1;
                break;
            case WP_AT_HOME:
                if (Player* player = ObjectAccessor::GetPlayer(*me, _eventStarterGuid)) {
                    player->KilledMonsterCredit(KILL_CREDIT_REUNION_FINISHED_ALTRUIS, ObjectGuid::Empty);
                }
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
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_altruis_sufferer_freed_99632_AI(creature);
    }
};

class npc_kayn_sunfury_freed_99631 : public CreatureScript {
public:
    npc_kayn_sunfury_freed_99631() : CreatureScript("npc_kayn_sunfury_freed_99631") { }

    enum eKaynFreed {
        PHASE_NONE = 0,
        PHASE_CONTINUE = -1,
        DATA_EVENT_STARTER_GUID = 0,
        QUEST_BREAKING_OUT = 38672,
        PHASE_PEEK_WEAPONS_1 = 1,
        PHASE_PEEK_WEAPONS_2 = 2,
        PHASE_PEEK_WEAPONS_3 = 3,
        PHASE_PEEK_WEAPONS_4 = 4,
        PHASE_DESPAWN = 5,
        WP_START = 1,
        WP_AT_WEAPON_CRATE = 6,
        WP_AT_HOME = 13,
        DATA_TALK_QUEST_COMPLETE = 21,
        EVENT_TALK_1 = 22,
    };

    struct npc_kayn_sunfury_freed_99631_AI : public npc_escortAI
    {
        npc_kayn_sunfury_freed_99631_AI(Creature* creature) : npc_escortAI(creature)
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

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_TALK_QUEST_COMPLETE:
                _events.ScheduleEvent(EVENT_TALK_1, 7s);
                break;
            default:
                break;
            }
        }

        void Reset() override
        {
            Initialize();
            _events.Reset();
        }

        void IsSummonedBy(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
            {
                _eventStarterGuid = who->GetGUID();
                me->SetWalk(true);
                me->LoadEquipment(2);
                Start(false, false, _eventStarterGuid);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent()) {
                switch (eventId) {
                case EVENT_TALK_1:
                    Talk(1);
                    break;
                default:
                    break;
                }
            }

            if (UpdateVictim())
                DoMeleeAttackIfReady();

            /*if (HasEscortState(STATE_ESCORT_NONE))
                return;*/

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
                    case PHASE_PEEK_WEAPONS_1:
                        me->LoadEquipment(3);
                        _moveTimer = 2 * IN_MILLISECONDS;
                        _phase = PHASE_PEEK_WEAPONS_2;
                        break;
                    case PHASE_PEEK_WEAPONS_2:
                        me->HandleEmoteCommand(EMOTE_STATE_KNEEL_2);
                        me->LoadEquipment(1);
                        if (Player* player = ObjectAccessor::GetPlayer(*me, _eventStarterGuid))
                        {
                            player->KilledMonsterCredit(KILL_CREDIT_KAYN_PICKED_UP_WEAPONS, ObjectGuid::Empty);
                        }   
                        _moveTimer = 2 * IN_MILLISECONDS;
                        _phase = PHASE_PEEK_WEAPONS_3;
                        break;
                    case PHASE_PEEK_WEAPONS_3:
                        me->HandleEmoteCommand(EMOTE_STATE_NONE);
                        SetEscortPaused(false);
                        _moveTimer = 0 * IN_MILLISECONDS;
                        _phase = PHASE_NONE;
                        SetEscortPaused(true);
                        break;
                    case PHASE_DESPAWN:
                        // me->DespawnOrUnsummon();
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
            case WP_START:
                _moveTimer = 0 * IN_MILLISECONDS;
                _phase = PHASE_NONE;
                Talk(0);
                break;
            case WP_AT_WEAPON_CRATE:
                SetEscortPaused(true);
                me->SetOrientation(0.10776f);
                me->HandleEmoteCommand(EMOTE_STATE_KNEEL_2);
                _moveTimer = 0.2 * IN_MILLISECONDS;
                _phase = PHASE_PEEK_WEAPONS_1;
                break;
            case WP_AT_HOME:
                if (Player* player = ObjectAccessor::GetPlayer(*me, _eventStarterGuid)) {
                    player->KilledMonsterCredit(KILL_CREDIT_REUNION_FINISHED_KAYN, ObjectGuid::Empty);
                }
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
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_kayn_sunfury_freed_99631_AI(creature);
    }
};

Position const secondStagePath[] =
{
    { 4438.449f, -290.577f, -244.036f },
    { 4444.083f, -301.119f, -239.666f },
    { 4450.647f, -320.770f, -235.952f },
    { 4450.647f, -320.770f, -197.235f },
    { 4450.647f, -320.770f, -158.749f },
    { 4450.647f, -320.770f, -107.313f },
    { 4450.647f, -320.770f, -47.358f },
    { 4450.647f, -320.770f, -5.029f },
    { 4450.647f, -320.770f, 37.068f },
    { 4450.647f, -320.770f, 97.366f },
    { 4450.647f, -320.770f, 127.221f },
    { 4450.647f, -320.770f, 130.252f },
    { 4450.646f, -344.573f, 128.044f }
};
size_t const pathSize = std::extent<decltype(secondStagePath)>::value;

class npc_vault_of_the_wardens_vampiric_felbat : public CreatureScript
{
public:
    npc_vault_of_the_wardens_vampiric_felbat() : CreatureScript("npc_vault_of_the_wardens_vampiric_felbat") { }

    enum eFelBat {
        EVENT_START_PATH = 1,
        EVENT_DESPAWN = 2,
    };

    struct npc_vault_of_the_wardens_vampiric_felbat_AI : public VehicleAI
    {
        npc_vault_of_the_wardens_vampiric_felbat_AI(Creature* creature) : VehicleAI(creature) { }

        void Initialize()
        {
            me->SetCanFly(true);
            me->SetSpeed(MOVE_FLIGHT, 26);
            me->SetReactState(REACT_PASSIVE);
            me->SetMovementAnimKitId(3);
            me->SetSpeed(MOVE_FLIGHT, 75);
        }

        void Reset() override
        {
            _events.Reset();
            Initialize();
            _playerGUID = ObjectGuid::Empty;
        }

        void PassengerBoarded(Unit* passenger, int8 /*seatId*/, bool apply) override
        {
            if (apply && passenger->GetTypeId() == TYPEID_PLAYER) {
                _playerGUID = passenger->ToPlayer()->GetGUID();
                _events.ScheduleEvent(EVENT_START_PATH, Seconds(1));
            }
        }

        void MovementInform(uint32 type, uint32 pointId) override
        {       
            if (type == EFFECT_MOTION_TYPE && pointId == pathSize)
                _events.ScheduleEvent(EVENT_DESPAWN, 200);
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_PATH:
                    me->GetMotionMaster()->MoveSmoothPath(uint32(pathSize), secondStagePath, pathSize, false, true);
                    if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                        player->AddDelayedConversation(10000, 6803);
                    break;
                case EVENT_DESPAWN:
                    me->RemoveAllAuras();
                    if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                        player->KilledMonsterCredit(96659, ObjectGuid::Empty);
                    me->DespawnOrUnsummon();
                    break;
                default:
                    break;
                }
            }
        }
    private:
        EventMap _events;
        ObjectGuid _playerGUID;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_vault_of_the_wardens_vampiric_felbat_AI(creature);
    }
};

enum grandFelbatQuest {
    NPC_KAYN_FOLLOWER_ALTRUIS = 92985
};
// 92984 - Kayn Sunfury - Grand Theft Felbat
class npc_kayn_sunfury_felbat : public CreatureScript
{
public:
    npc_kayn_sunfury_felbat() : CreatureScript("npc_kayn_sunfury_felbat") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_GRAND_THEFT_FELBAT)
        {
            creature->AI()->SetGUID(player->GetGUID());

            if (Creature* normalAltruis = creature->FindNearestCreature(NPC_KAYN_FOLLOWER_ALTRUIS, 50.0f))
            {   
                normalAltruis->AI()->SetGUID(player->GetGUID());
            }
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_kayn_sunfury_felbatAI(creature);
    }

    struct npc_kayn_sunfury_felbatAI : public npc_escortAI
    {
        npc_kayn_sunfury_felbatAI(Creature* creature) : npc_escortAI(creature) { }

        ObjectGuid playerGuid;

        void Reset() override
        {
            playerGuid = ObjectGuid::Empty;
            me->SetCorpseDelay(0);
            me->SetRespawnDelay(0);
            me->SetRespawnTime(0);
        }

        void SetGUID(ObjectGuid guid, int32 /*id*/) override
        {
            playerGuid = guid;
            Start(false, true, guid);
            SetDespawnAtFar(false);
        }

        void WaypointReached(uint32 pointId) override
        {
            switch (pointId) {
                case 0:
                    Talk(3);
                    break;
                case 4:
                    Talk(4);
                    break;
            }
        }

        void LastWaypointReached() override
        {
            me->DespawnOrUnsummon();
            me->setDeathState(JUST_DIED);
            me->Respawn();
        }
    };
};

// 92985 (Altruis) - Kayn Sunfury follower - Grand Theft Felbat
class npc_kayn_sunfury_follower : public CreatureScript
{
public:
    npc_kayn_sunfury_follower() : CreatureScript("npc_kayn_sunfury_follower") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_kayn_sunfury_followerAI(creature);
    }

    struct npc_kayn_sunfury_followerAI : public npc_escortAI
    {
        npc_kayn_sunfury_followerAI(Creature* creature) : npc_escortAI(creature) { }

        void Reset() override
        {
            me->SetCorpseDelay(0);
            me->SetRespawnDelay(0);
            me->SetRespawnTime(0);
        }

        void SetGUID(ObjectGuid guid, int32 /*id*/) override
        {
            Start(true, true, guid);
        }

        void WaypointReached(uint32 pointId) override
        {
            switch (pointId) {
                case 1:
                    Talk(4);
                    break;
            }
        }

        void LastWaypointReached() override
        {
            me->DespawnOrUnsummon();
            me->setDeathState(JUST_DIED);
            me->Respawn();
        }
    };
};

/*********/
/* AddSC */
/*********/
void AddSC_zone_vault_of_wardens() {
    new npc_kayn_cell();
    new npc_altruis_cell();
    new npc_fel_infusion();
    new npc_altruis();
    new npc_kayn_3();
    new q_fel_infusion();
    new q_breaking_out();
    new q_frozen_in_time();
    new npc_kayn_sledge_fight();
    new npc_altruis_crusher_fight();
    new npc_sledge_crusher();
    new go_reflective_mirror();
    new spell_activate_countermeasure();
    new go_warden_ascent();
    new npc_korvas_bloodthorn();
    new go_pool_of_judgements();
    new npc_bastillax();
    new npc_khadgar();
    new npc_cyana_immolanth_fight();
    new npc_immolanth();
    RegisterCreatureAI(npc_vow_ashgolm);
    new npc_maiev_shadowsong();
    new npc_legion_portal();
    new PlayerScript_follower_choice();
    // new On100DHArrival();
    new PlayerScript_bonus_objective();
    new npc_altruis_sufferer_freed_99632();
    new npc_kayn_sunfury_freed_99631();
    new npc_vault_of_the_wardens_vampiric_felbat();
    new npc_maiev_shadowsong_welcome();
    new spell_play_scene_1423(); // 187864: Play Scene
    new npc_kayn_sunfury_felbat();
    new npc_kayn_sunfury_follower();
    new spell_196460(); // Lingering Gaze
    new spell_196462(); // Pulse
    new spell_199760(); // Burning Fel
    new npc_korvas_bloodthorn_97643(); // 97643
    new npc_votw_kayn_altruis_choice(); // 97265, 97267 
    new npc_bastillax_attacker(); // 97273, 97274
 }
