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
#include "ScriptedGossip.h"
#include "PhasingHandler.h"

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
        }
            
    }
};

 // 228644
 class spell_fate_of_the_horde : public SpellScript
 {
     PrepareSpellScript(spell_fate_of_the_horde);

     enum
     {
         MOVIE_FATE_OF_THE_HORDE = 474,
         SPELL_TELE_TO_DUROTAR_FUNERAL = 200282,
         SPELL_LEARN_FATE_OF_THE_HORDE = 198893,
     };

     void HandleOnCast()
     {
         if (Player* player = GetCaster()->ToPlayer())
         {
             player->AddMovieDelayedAction(MOVIE_FATE_OF_THE_HORDE, [player]
             {
                 player->CastSpell(player, SPELL_LEARN_FATE_OF_THE_HORDE, true);
                 player->CastSpell(player, SPELL_TELE_TO_DUROTAR_FUNERAL, true);
             });

             player->GetScheduler().Schedule(Seconds(2), [](TaskContext context)
             {
                 GetContextUnit()->RemoveAurasDueToSpell(192140); // Remove black screen
             });
         }
     }

     void Register() override
     {
         OnCast += SpellCastFn(spell_fate_of_the_horde::HandleOnCast);
     }
 };

enum eQuest {
    QUEST_ILLIDARI_LEAVING_H = 39690,
    QUEST_AUDIENCE_WITH_WARCHIEF = 40976,
    PHASE_ORGRIMMAR_WARCHIEF = 1178,
    SPELL_SUMMON_KHADGAR = 230064,
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

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_AUDIENCE_WITH_WARCHIEF) == QUEST_STATUS_INCOMPLETE)
            player->KilledMonsterCredit(100541, ObjectGuid::Empty);

        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Take me inside Grommash Hold.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        SendGossipMenuFor(player, player->GetGossipTextId(creature), creature->GetGUID()); // 19016

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
        case GOSSIP_ACTION_INFO_DEF:
            // player->KilledMonsterCredit(100934, ObjectGuid::Empty);
            player->SendMovieStart(474);
            CloseGossipMenuFor(player);
            break;
        }

        return true;
    }
};

void AddSC_orgrimmar()
{
	new play_fate_of_the_horde();
    new PlayerScript_summon_khadgar();
    new npc_lord_saurfang();
}
