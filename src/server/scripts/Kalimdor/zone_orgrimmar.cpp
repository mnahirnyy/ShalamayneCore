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

class PlayerScript_summon_khadgar : public PlayerScript
{
public:
    PlayerScript_summon_khadgar() : PlayerScript("PlayerScript_summon_khadgar") {}

    uint32 checkTimer = 1000;
    bool _khadgarSummoned = false;

    void OnUpdate(Player* player, uint32 diff) override
    {
        if (checkTimer <= diff)
        {
            if (player->getClass() == CLASS_DEMON_HUNTER &&
                (player->GetAreaId() == 1637 || 5170 || 5356) &&
                player->GetQuestStatus(QUEST_ILLIDARI_LEAVING_H) == QUEST_STATUS_REWARDED &&
                !player->GetPhaseShift().HasPhase(PHASE_ORGRIMMAR_WARCHIEF)) {
                    PhasingHandler::AddPhase(player, PHASE_ORGRIMMAR_WARCHIEF, true);
            }
            checkTimer = 1000;
        }
        else checkTimer -= diff;
    }
};

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

void AddSC_orgrimmar()
{
	new play_fate_of_the_horde();
    new PlayerScript_summon_khadgar();
    new npc_lord_saurfang();
    new PlayerScript_summon_khadgar_servant();
    new npc_khadgars_upgraded_servant();
}
