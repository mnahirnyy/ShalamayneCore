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

#include "ScriptMgr.h"
#include "CreatureAIImpl.h"
#include "GameObject.h"
#include "MotionMaster.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "SpellInfo.h"
#include "SpellScript.h"
#include "PhasingHandler.h"
#include "ObjectMgr.h"

enum eQuest {
    QUEST_AUDIENCE_WARCHIEF = 40976,
    QUEST_SECOND_SIGHT = 40982,
    QUEST_DEMONS_AMONG_THEM = 40983,
    QUEST_WEAPON_OF_THE_HORDE = 41002,
};

enum eScene {
    SCENE_DEMONS_AMONG_THEM_HORDE = 1453,
};

/*######
## Quest 37446: Lazy Peons
## npc_lazy_peon
######*/

enum LazyPeonYells
{
    SAY_SPELL_HIT = 0,
};

enum LazyPeon
{
    QUEST_LAZY_PEONS    = 37446,
    GO_LUMBERPILE       = 175784,
    SPELL_BUFF_SLEEP    = 17743,
    SPELL_AWAKEN_PEON   = 19938
};

class npc_lazy_peon : public CreatureScript
{
public:
    npc_lazy_peon() : CreatureScript("npc_lazy_peon") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lazy_peonAI(creature);
    }

    struct npc_lazy_peonAI : public ScriptedAI
    {
        npc_lazy_peonAI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
        }

        void Initialize()
        {
            RebuffTimer = 0;
            work = false;
        }

        uint32 RebuffTimer;
        bool work;

        void Reset() override
        {
            Initialize();
        }

        void MovementInform(uint32 /*type*/, uint32 id) override
        {
            if (id == 1)
                work = true;
        }

        void SpellHit(Unit* caster, const SpellInfo* spell) override
        {
            if (spell->Id != SPELL_AWAKEN_PEON)
                return;

            Player* player = caster->ToPlayer();
            if (player && player->GetQuestStatus(QUEST_LAZY_PEONS) == QUEST_STATUS_INCOMPLETE)
            {
                player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
                Talk(SAY_SPELL_HIT, caster);
                me->RemoveAllAuras();
                if (GameObject* Lumberpile = me->FindNearestGameObject(GO_LUMBERPILE, 20))
                    me->GetMotionMaster()->MovePoint(1, Lumberpile->GetPositionX()-1, Lumberpile->GetPositionY(), Lumberpile->GetPositionZ());
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (work == true)
                me->HandleEmoteCommand(EMOTE_ONESHOT_WORK_CHOPWOOD);
            if (RebuffTimer <= diff)
            {
                DoCast(me, SPELL_BUFF_SLEEP);
                RebuffTimer = 300000; //Rebuff agian in 5 minutes
            }
            else
                RebuffTimer -= diff;
            if (!UpdateVictim())
                return;
            DoMeleeAttackIfReady();
        }
    };
};

enum VoodooSpells
{
    SPELL_BREW      = 16712, // Special Brew
    SPELL_GHOSTLY   = 16713, // Ghostly
    SPELL_HEX1      = 16707, // Hex
    SPELL_HEX2      = 16708, // Hex
    SPELL_HEX3      = 16709, // Hex
    SPELL_GROW      = 16711, // Grow
    SPELL_LAUNCH    = 16716, // Launch (Whee!)
};

// 17009
class spell_voodoo : public SpellScriptLoader
{
    public:
        spell_voodoo() : SpellScriptLoader("spell_voodoo") { }

        class spell_voodoo_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_voodoo_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                return ValidateSpellInfo(
                {
                    SPELL_BREW,
                    SPELL_GHOSTLY,
                    SPELL_HEX1,
                    SPELL_HEX2,
                    SPELL_HEX3,
                    SPELL_GROW,
                    SPELL_LAUNCH
                });
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                uint32 spellid = RAND(SPELL_BREW, SPELL_GHOSTLY, RAND(SPELL_HEX1, SPELL_HEX2, SPELL_HEX3), SPELL_GROW, SPELL_LAUNCH);
                if (Unit* target = GetHitUnit())
                    GetCaster()->CastSpell(target, spellid, false);
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_voodoo_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_voodoo_SpellScript();
        }
};

class npc_lady_sylvana_funeral : CreatureScript
{
public:
    npc_lady_sylvana_funeral() : CreatureScript("npc_lady_sylvana_funeral") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_DEMONS_AMONG_THEM) == QUEST_STATUS_INCOMPLETE) {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "This cannot wait. There are demons among your ranks. Let me show you.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        }
        SendGossipMenuFor(player, 30561, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        ClearGossipMenuFor(player);
        switch (action)
        {
        case GOSSIP_ACTION_INFO_DEF:
            player->GetSceneMgr().PlayScene(SCENE_DEMONS_AMONG_THEM_HORDE);
            CloseGossipMenuFor(player);
            break;
        }
        return true;
    }
};

class scene_demons_among_them_horde : public SceneScript
{
public:
    scene_demons_among_them_horde() : SceneScript("scene_demons_among_them_horde") { }
    enum {
        KILL_CREDIT_WARN_SYLVANAS = 100866,
        PHASE_FIGHT_IN_FUNERAL = 1181,
    };
    void OnSceneEnd(Player* player, uint32 /*sceneInstanceID*/, SceneTemplate const* /*sceneTemplate*/) override
    {
        player->KilledMonsterCredit(KILL_CREDIT_WARN_SYLVANAS, ObjectGuid::Empty);
        PhasingHandler::AddPhase(player, PHASE_FIGHT_IN_FUNERAL, true);
    }
};

class PlayerScript_durotar_funeral : public PlayerScript
{
public:
    PlayerScript_durotar_funeral() : PlayerScript("PlayerScript_durotar_funeral") {}

    uint32 checkTimer = 1000;
    
    void OnUpdate(Player* player, uint32 diff) override
    {
        if (checkTimer <= diff)
        {
            if (player->getClass() == CLASS_DEMON_HUNTER &&
                player->GetAreaId() == 4982 &&
                player->GetQuestStatus(40976) == QUEST_STATUS_COMPLETE &&
                !player->GetPhaseShift().HasPhase(1180)) {
                    PhasingHandler::RemovePhase(player, 1178);
                    PhasingHandler::AddPhase(player, 1180, true);
            }
            checkTimer = 1000;
        }
        else checkTimer -= diff;
    }
};

/*######
## npc_durotar_duelist
## quest 44281
######*/
#define GOSSIP_LETS_DUEL "Let's duel."

enum eDuelist
{   
    QUEST_TO_BE_PREPARED = 44281,
    KILL_CREDIT_WARM_DUEL = 108722,
    EVENT_DO_CAST = 1,
    EVENT_STOP_DUEL = 2,
    DATA_START_DUEL = 10,
    SPELL_DUEL = 52996,
    SPELL_DUEL_TRIGGERED = 52990,
    SPELL_DUEL_VICTORY = 52994,
    SPELL_DUEL_FLAG = 52991,
};

std::map<uint32, uint32> const creatureAbilities
{
    { 113955,  172675 }, // Utona Wolfeye : Lighting Bolt
    { 113951,  171884 }, // Sahale : Denounce
    { 113947,  172769 }, // Maska : Mortal Strike
    { 113545,  171764 }, // Dawn Merculus : Fireball
    { 113961,  172028 }, // Pinkee Rizzo : Sinister Strike
    { 113956,  171858 }, // Taela Shatterborne : Frostbolt
    { 113952,  171957 }, // Aila Dourblade : Hemorrhage
    { 113948,  172673 }, // Arienne Black : Holy Smite
    { 113542,  11538 }, // Marius Sunshard : Frostbolt + Ice Barrier (33245)
    { 113954,  171919 }, // Argonis Solheart : Crusader Strike
    { 113544,  171777 }, // Neejala : Starfire
    { 113950,  172779 }, // Lonan : Stormstrike
    { 113546,  172673 }, // Yaalo : Holy Smite
};

class npc_durotar_duelist : public CreatureScript
{
public:
    npc_durotar_duelist() : CreatureScript("npc_durotar_duelist") { }

    struct npc_durotar_duelist_AI : public ScriptedAI {
        npc_durotar_duelist_AI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            _events.Reset();
            me->RestoreFaction();
            me->SetReactState(REACT_DEFENSIVE);
        }

        void EnterCombat(Unit* who) override {
            _events.ScheduleEvent(EVENT_DO_CAST, 1000);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (damage >= me->GetHealth())
            {
                damage = me->GetHealth() - 1;
                _events.Reset();
                me->RemoveAllAuras();
                me->setFaction(35);
                me->AttackStop();
                attacker->AttackStop();
                attacker->ClearInCombat();
                attacker->ToPlayer()->KilledMonsterCredit(KILL_CREDIT_WARM_DUEL);
                _events.ScheduleEvent(EVENT_STOP_DUEL, 1000);
            }
        }

        void UpdateAI(uint32 diff) override {
            if (!UpdateVictim())
                return;

            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent()) {
                switch (eventId) {
                    case EVENT_DO_CAST:
                        DoCastVictim(creatureAbilities.at(me->GetEntry()));
                        _events.RescheduleEvent(EVENT_DO_CAST, 4000);
                        break;
                    case EVENT_STOP_DUEL:
                        me->Say("Fine duel.", LANG_UNIVERSAL, nullptr);
                        me->GetMotionMaster()->MoveTargetedHome();
                        break;
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }

        void SetGUID(ObjectGuid guid, int32 /*id*/) override {
            _playerGuid = guid;
        }

    private:
        EventMap _events;
        ObjectGuid _playerGuid = ObjectGuid::Empty;
    };

    bool OnGossipHello(Player* player, Creature* creature) override {
        if (player->GetQuestStatus(QUEST_TO_BE_PREPARED) == QUEST_STATUS_INCOMPLETE)
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_LETS_DUEL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        SendGossipMenuFor(player, player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF + 1) {
            creature->AI()->SetGUID(player->GetGUID());
            creature->setFaction(FACTION_TEMPLATE_FLAG_PVP);
            creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            creature->SetReactState(REACT_AGGRESSIVE);

            player->CastSpell(creature, SPELL_DUEL, false);
            player->CastSpell(player, SPELL_DUEL_FLAG, true);

            creature->AI()->AttackStart(player);
            CloseGossipMenuFor(player);
        }
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const override {
        return new npc_durotar_duelist_AI(creature);
    }
};

void AddSC_durotar()
{
    new npc_lazy_peon();
    new spell_voodoo();
    new npc_lady_sylvana_funeral();
    new scene_demons_among_them_horde();
    new PlayerScript_durotar_funeral();
    new npc_durotar_duelist();
}
