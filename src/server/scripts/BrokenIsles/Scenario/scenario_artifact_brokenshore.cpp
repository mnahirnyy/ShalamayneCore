/*
 * Copyright (C) 2019-2019 5CentsCore <https://github.com/osleyder85/LegionCore>
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
#include "Scenario.h"
#include "InstanceScenario.h"
#include "GameObject.h"
#include "PhasingHandler.h"
#include "SceneMgr.h"
#include "ScriptMgr.h"

enum DataTypes
{
    SCENARIO_ID_DH = 961, // The Aldrachi Warblades
    SCENARIO_ID_PALADIN = 775, // The Legend of The Ashbringer
    DATA_DH_STEP_1 = 1939, // Free Allari from her chains.(Picking Up the Pieces)
    DATA_DH_STEP_2 = 1940, // Cut through the demon hordes and destroy their portals. (Their Blood Will Flow)
    DATA_DH_STEP_3 = 2299, // Two of Caria's lieutenants are performing a dark ritual. They must be stopped. (A River of Souls)
    DATA_DH_STEP_4 = 1948, // Gorgonnash has risen to stop your assault. (In the Darkness of the Pit)
    DATA_DH_STEP_5 = 1941, // Use your demonic senses to pickup Caria's trail. (Nowhere to Hide)
    DATA_DH_STEP_6 = 1942, // Caria Felsoul's time has come. (Vengeance for the Illidari)
    DATA_DH_STEP_7 = 2302, // Claim the Aldrachi Warblades as your own. (Right by Ascension)
    DATA_PALADIN_STEP_1 = 1488, // Lead the paladins of the Argent Crusade into battle. (Sounding the Charge)
    DATA_PALADIN_STEP_2 = 1485, // Destroy the demon army. (Crusaders' March)
    DATA_PALADIN_STEP_3 = 1486, // Destroy Jailer Zerus and save Highlord Tirion Fordring. (Holy Vengeance)
    DATA_PALADIN_STEP_4 = 1487, // Find the Ashbringer within the Lost Temple. (The Ashbringer)
    DATA_PALADIN_STEP_5 = 2632, // Call upon the power of the Ashbringer to break free from Balnazzar's control. (One Final Blessing)
    DATA_PALADIN_STEP_6 = 1853, // Defeat Balnazzar. (Balnazzar the Risen)
    DATA_PALADIN_STEP_7 = 1854, // Return to Tirion Fordring. (The Fate of the Highlord)
    DATA_MAX_ENCOUNTERS_DH = 7,
    DATA_MAX_ENCOUNTERS_PALADIN = 7,
    PHASE_DH = 5875,
    PHASE_PALADIN = 5171,
    NPC_ALLARI_SOULEATER = 98882,
    NPC_GORGONNASH = 99046,
    GO_ALDRACHI_WARBLADES = 99999,
    GO_FELSOUL_PORTAL_1 = 248573,
    GO_FELSOUL_PORTAL_2 = 248517,
    GO_FELSOUL_CAGE = 266029,
    GO_STONE_WALL = 245045,
    NORMAL_PHASE = 169,
    DATA_BROKENSHORE = 0,
    DATA_STAGE_1 = 1,
    DATA_STAGE_2 = 2,
    DATA_STAGE_3 = 3,
    DATA_STAGE_4 = 4,
    DATA_STAGE_5 = 5,
    DATA_STAGE_6 = 6,
    DATA_STAGE_7 = 7,
    DH_VENGEANCE_ARTIFACT_ACQUISTION_LOOTED_SCENE = 1245,
    QUEST_VENGEANCE_WILL_BE_OURS_1 = 40249,
    QUEST_VENGEANCE_WILL_BE_OURS_2 = 41863,
};

struct ScenarioSpawnData
{
    uint32 event, npcId;
    float X;
    float Y;
    float Z;
    float orientation;
};

ScenarioSpawnData const spawnData[] =
{
    { DATA_STAGE_1, NPC_GORGONNASH, -2784.22f, -98.766f, 47.994f, 0.51138f },
};

struct scenario_artifact_brokenshore : public InstanceScript
{
    scenario_artifact_brokenshore(InstanceMap* map) : InstanceScript(map) { }

    void Initialize() override
    {
        SetBossNumber(DATA_MAX_ENCOUNTERS_DH);
        SetData(DATA_BROKENSHORE, NOT_STARTED);
        for (uint8 i = 1; i < 7; ++i)
            SetData(i, NOT_STARTED);
        StepID = DATA_STAGE_1;
        isComplete = false;
        demonPortalsDestroyed = 0;
        demonTwinsKilled = 0;
        _playerGUID = ObjectGuid::Empty;
        _gorgonnashGUID = ObjectGuid::Empty;
    }

    void OnPlayerEnter(Player* player) override
    {
        InstanceScript::OnPlayerEnter(player);
        TC_LOG_ERROR("server.worldserver", " === scenario_artifact_brokenshore  === ");
        if (player->GetMapId() == 1500)
        {
            _playerGUID = player->GetGUID();
            PhasingHandler::AddPhase(player, NORMAL_PHASE, true);
        }
    }

    void OnCreatureCreate(Creature* creature) override
    {
        InstanceScript::OnCreatureCreate(creature);

        switch (creature->GetEntry())
        {
        case NPC_GORGONNASH:
            _gorgonnashGUID = creature->GetGUID();
            break;
        default:
            break;
        }
    }

    void OnGameObjectCreate(GameObject* go) override
    {
        InstanceScript::OnGameObjectCreate(go);

        switch (go->GetEntry())
        {
        /*case GO_FELSOUL_PORTAL_1:
            go->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_FELSOUL_PORTAL_2:
            go->SetGoState(GO_STATE_ACTIVE);
            break;*/
        case GO_STONE_WALL:
            go->SetLootState(GO_READY);
        default:
            break;
        }
    }

    void NextStep()
    {
        TC_LOG_ERROR("server.worldserver", " === scenario_artifact_brokenshore  NextStep  %u === ", StepID);
        if (StepID < DATA_STAGE_7)
        {
            ++StepID;
            if (Scenario* scenario = instance->GetInstanceScenario())
                scenario->CompleteCurrStep();
        }
        else if (StepID == DATA_STAGE_7)
        {
            if (!isComplete)
                if (Scenario* scenario = instance->GetInstanceScenario())
                    scenario->CompleteCurrStep();

            // COMPLETE SCENARIO
            if (Scenario* scenario = instance->GetInstanceScenario())
                scenario->CompleteScenario();
        }
    }

    void SetData(uint32 type, uint32 data) override
    {
        InstanceScript::SetData(type, data);

        if (data == NOT_STARTED)
            return;

        if (type == DATA_STAGE_1 && data == DONE)
        {
            NextStep();
        }
        else if (type == DATA_STAGE_2 && data == DONE)
        {
            ++demonPortalsDestroyed;
            if (demonPortalsDestroyed == 2)
                NextStep();
        }
        else if (type == DATA_STAGE_3 && data == DONE)
        {
            ++demonTwinsKilled;
            if (demonTwinsKilled == 2)
                NextStep();
        }
        else if (type == DATA_STAGE_4 && data == DONE)
        {
            NextStep();
        }
        else if (type == DATA_STAGE_5 && data == DONE)
        {
            NextStep();
        }
        else if (type == DATA_STAGE_6 && data == DONE)
        {
            NextStep();
        }
        else if (type == DATA_STAGE_7 && data == DONE)
        {
            NextStep();
            DoPlayScenePackageIdOnPlayers(DH_VENGEANCE_ARTIFACT_ACQUISTION_LOOTED_SCENE);
        }
    }

private:
    EventMap events;
    uint8 StepID;
    bool isComplete;
    ObjectGuid _playerGUID;
    ObjectGuid _gorgonnashGUID;
    uint8 demonPortalsDestroyed;
    uint8 demonTwinsKilled;
};

class npc_allari_soulweaver_98882 : public CreatureScript
{
public:
    npc_allari_soulweaver_98882() : CreatureScript("npc_allari_soulweaver_98882") { }

    enum eAllari {
        DATA_FREED = 11,
    };

    struct npc_allari_soulweaver_98882_AI : public ScriptedAI
    {
        npc_allari_soulweaver_98882_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            instance = me->GetInstanceScript();
        }

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_FREED:
                if (instance->GetData(DATA_STAGE_1) == NOT_STARTED)
                    instance->SetData(DATA_STAGE_1, DONE);
                break;
            default:
                break;
            }
        }

    private:
        EventMap _events;
        InstanceScript * instance;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_allari_soulweaver_98882_AI(creature);
    }
};

class go_brokenshore_felsoul_portal : public GameObjectScript
{
public:
    go_brokenshore_felsoul_portal() : GameObjectScript("go_brokenshore_felsoul_portal") {}

    enum eLegionPortal {
        SPELL_PORTAL_EXPLOSION = 196084,
        SPELL_DESTROYING_LEGION_PORTAL = 202064,
    };

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (InstanceScript * instance = go->GetInstanceScript())
        {                   
            player->CastSpell(go, SPELL_DESTROYING_LEGION_PORTAL, true);
            player->CastSpell(go, SPELL_PORTAL_EXPLOSION, true);
            go->DestroyForPlayer(player);
            instance->SetData(DATA_STAGE_2, DONE);
        }
        return false;
    }
};

class go_temporary_allari_cage : public GameObjectScript
{
public:
    go_temporary_allari_cage() : GameObjectScript("go_temporary_allari_cage") { }

    enum eCage {
        NPC_CHAINED_ALLARI = 98882,
        DATA_FREED = 11,
    };

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->SetGoState(GO_STATE_READY);
        if (InstanceScript * instance = go->GetInstanceScript())
        {
            if (instance->GetData(DATA_STAGE_1) == NOT_STARTED)
            {
                if (Creature* chained_allari = go->FindNearestCreature(NPC_CHAINED_ALLARI, 5.0f, true))
                {
                    go->ResetDoorOrButton();
                    go->DestroyForPlayer(player);
                    chained_allari->AI()->SetData(DATA_FREED, DATA_FREED);
                    return false;
                }
            }
        }
        return true;
    }
};

// Doomherald Saera 105095
class npc_doomherald_saera_105095 : public CreatureScript
{
public:
    npc_doomherald_saera_105095() : CreatureScript("npc_doomherald_saera_105095") { }

    enum eSaera
    {
        EVENT_DEMON_LINK = 1,
        EVENT_SHADOW_BOLT = 2,
        EVENT_STALKING_SHADOWS = 3,
        SPELL_DEMON_LINK = 215837,
        SPELL_SHADOW_BOLT = 215885,
        SPELL_STALKING_SHADOWS = 215861,
    };

    struct npc_doomherald_saera_105095_AI : public ScriptedAI
    {
        npc_doomherald_saera_105095_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            instance = me->GetInstanceScript();
        }

        void Reset() override
        {
            _events.Reset();
            Initialize();
            me->setActive(true);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            me->AddAura(SPELL_DEMON_LINK, me);
            _events.ScheduleEvent(EVENT_SHADOW_BOLT, 1000);
            _events.ScheduleEvent(EVENT_STALKING_SHADOWS, urand(8000, 10000));
        }

        void JustDied(Unit* /*killer*/) override
        {
            instance->SetData(DATA_STAGE_3, DONE);
            me->DespawnOrUnsummon(20000, Seconds(300));
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
                case EVENT_SHADOW_BOLT:
                    DoCastVictim(SPELL_SHADOW_BOLT);
                    _events.ScheduleEvent(EVENT_SHADOW_BOLT, 4000);
                    break;
                case EVENT_STALKING_SHADOWS:
                    DoCastVictim(SPELL_STALKING_SHADOWS);
                    _events.ScheduleEvent(EVENT_STALKING_SHADOWS, 8000);
                    break;
                default:
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }

    private:
        EventMap _events;
        InstanceScript * instance;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_doomherald_saera_105095_AI(creature);
    }
};

// Doomherald Taraar 105094
class npc_doomherald_taraar_105094 : public CreatureScript
{
public:
    npc_doomherald_taraar_105094() : CreatureScript("npc_doomherald_taraar_105094") { }

    enum eTaraar
    {
        EVENT_DEMON_LINK = 1,
        EVENT_FEL_FIREBALL = 2,
        EVENT_SUMMON_FEL_FAMILIARS = 3,
        SPELL_DEMON_LINK = 215837,
        SPELL_FEL_FIREBALL = 215852,
        SPELL_SUMMON_FEL_FAMILIARS = 215842,
    };

    struct npc_doomherald_taraar_105094_AI : public ScriptedAI
    {
        npc_doomherald_taraar_105094_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            instance = me->GetInstanceScript();
        }

        void Reset() override
        {
            _events.Reset();
            Initialize();
            me->setActive(true);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            me->AddAura(SPELL_DEMON_LINK, me);
            _events.ScheduleEvent(EVENT_FEL_FIREBALL, 1000);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (HealthAbovePct(60))
                _events.ScheduleEvent(EVENT_SUMMON_FEL_FAMILIARS, 1000);
        }

        void JustDied(Unit* /*killer*/) override
        {
            instance->SetData(DATA_STAGE_3, DONE);
            me->DespawnOrUnsummon(20000, Seconds(300));
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
                case EVENT_FEL_FIREBALL:
                    DoCastVictim(SPELL_FEL_FIREBALL);
                    _events.ScheduleEvent(EVENT_FEL_FIREBALL, 4000);
                    break;
                case EVENT_SUMMON_FEL_FAMILIARS:
                    DoCastVictim(SPELL_SUMMON_FEL_FAMILIARS);
                    break;
                default:
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }

    private:
        EventMap _events;
        InstanceScript * instance;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_doomherald_taraar_105094_AI(creature);
    }
};

// Gorgonnash 99046
class npc_gorgonnash_99046 : public CreatureScript
{
public:
    npc_gorgonnash_99046() : CreatureScript("npc_gorgonnash_99046") { }

    enum eGorgonnash
    {
        EVENT_CREEPING_DOOM = 1,
        EVENT_FEL_CLEAVE = 2,
        EVENT_SUMMON_FEL_CRUSHER = 3,
        SPELL_CREEPING_DOOM = 215978,
        SPELL_FEL_CLEAVE = 215925,
    };

    struct npc_gorgonnash_99046_AI : public ScriptedAI
    {
        npc_gorgonnash_99046_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            instance = me->GetInstanceScript();
        }

        void Reset() override
        {
            _events.Reset();
            Initialize();
            me->setActive(true);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            _events.ScheduleEvent(EVENT_CREEPING_DOOM, 5000);
            _events.ScheduleEvent(EVENT_FEL_CLEAVE, 500);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            // TO DO
            // if (HealthBelowPct(60))
                // _events.ScheduleEvent(EVENT_SUMMON_FEL_CRUSHER, 1000);
        }

        void JustDied(Unit* /*killer*/) override
        {
            if (instance->GetData(DATA_STAGE_4) == NOT_STARTED)
                instance->SetData(DATA_STAGE_4, DONE);

            me->DespawnOrUnsummon(20000, Seconds(300));
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
                case EVENT_CREEPING_DOOM:
                    DoCastVictim(SPELL_CREEPING_DOOM);
                    _events.ScheduleEvent(EVENT_FEL_CLEAVE, urand(6000, 9000));
                    break;
                case EVENT_FEL_CLEAVE:
                    DoCastVictim(SPELL_FEL_CLEAVE);
                    _events.ScheduleEvent(EVENT_FEL_CLEAVE, urand(8000, 10000));
                    break;
                default:
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }

    private:
        EventMap _events;
        InstanceScript * instance;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_gorgonnash_99046_AI(creature);
    }
};

// Caria Felsoul 99184
class npc_caria_felsoul_99184 : public CreatureScript
{
public:
    npc_caria_felsoul_99184() : CreatureScript("npc_caria_felsoul_99184") { }

    enum eCaria
    {
        SPELL_CALL_OF_THE_WARBLADES = 208464,
        SPELL_FELSOUL_SLAM = 216164,
        SPELL_SIGIL_OF_POWER = 216229,
        SPELL_SIGIL_OF_POWER_2 = 216228,
        SPELL_SOUL_CARVER = 216188,
        EVENT_CALL_OF_THE_WARBLADES = 1,
        EVENT_FELSOUL_SLAM = 2,
        EVENT_SIGIL_OF_POWER = 3,
        EVENT_SIGIL_OF_POWER_2 = 4,
        EVENT_SOUL_CARVER = 5,
    };

    struct npc_caria_felsoul_99184_AI : public ScriptedAI
    {
        npc_caria_felsoul_99184_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            instance = me->GetInstanceScript();
        }

        void Reset() override
        {
            _events.Reset();
            Initialize();
            me->setActive(true);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            _events.ScheduleEvent(EVENT_FELSOUL_SLAM, 1500);
            _events.ScheduleEvent(EVENT_SIGIL_OF_POWER, 8000);
            _events.ScheduleEvent(EVENT_SIGIL_OF_POWER_2, 4000);
            _events.ScheduleEvent(EVENT_SOUL_CARVER, 5000);
        }

        void JustDied(Unit* /*killer*/) override
        {
            if (instance->GetData(DATA_STAGE_6) == NOT_STARTED)
                instance->SetData(DATA_STAGE_6, DONE);

            me->DespawnOrUnsummon(20000, Seconds(1));
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (HealthBelowPct(20))
                _events.ScheduleEvent(EVENT_CALL_OF_THE_WARBLADES, 500);
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
                case EVENT_FELSOUL_SLAM:
                    DoCastVictim(SPELL_FELSOUL_SLAM);
                    _events.ScheduleEvent(EVENT_FELSOUL_SLAM, urand(6000, 8000));
                    break;
                case EVENT_SIGIL_OF_POWER:
                    DoCastSelf(SPELL_SIGIL_OF_POWER);
                    _events.ScheduleEvent(SPELL_SIGIL_OF_POWER, urand(8000, 10000));
                    break;
                case EVENT_SIGIL_OF_POWER_2:
                    DoCastSelf(SPELL_SIGIL_OF_POWER_2);
                    _events.ScheduleEvent(EVENT_SIGIL_OF_POWER_2, urand(10000, 12000));
                    break;
                case EVENT_SOUL_CARVER:
                    DoCastVictim(SPELL_SOUL_CARVER);
                    _events.ScheduleEvent(EVENT_SOUL_CARVER, 5000);
                    break;
                case EVENT_CALL_OF_THE_WARBLADES:
                    _events.CancelEvent(EVENT_FELSOUL_SLAM);
                    _events.CancelEvent(EVENT_SOUL_CARVER);
                    _events.CancelEvent(SPELL_SIGIL_OF_POWER);
                    _events.CancelEvent(EVENT_SIGIL_OF_POWER_2);
                    break;
                default:
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }

    private:
        EventMap _events;
        InstanceScript * instance;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_caria_felsoul_99184_AI(creature);
    }
};

class go_aldrachi_warblades : public GameObjectScript
{
public:
    go_aldrachi_warblades() : GameObjectScript("go_aldrachi_warblades") { isLooted = false; }

    void OnLootStateChanged(GameObject* go, uint32 state, Unit* unit)
    {
        if (state == GO_ACTIVATED && unit && !isLooted)
        {
            isLooted = true;
            if (Player* player = unit->ToPlayer())
                if (!player->GetQuestObjectiveData(42430, 1))
                    player->KilledMonsterCredit(114514);

            if (InstanceScript * instance = go->GetInstanceScript())
                instance->SetData(DATA_STAGE_7, DONE);
        }
    }
    bool isLooted;
};

class go_cavern_stones_7796 : public GameObjectScript
{
public:
    go_cavern_stones_7796() : GameObjectScript("go_cavern_stones_7796") { isUsed = false; }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (InstanceScript * instance = go->GetInstanceScript())
        {
            if (!isUsed && player->HasAura(188501))
            {
                isUsed = true;
                go->DestroyForPlayer(player);
                instance->SetData(DATA_STAGE_5, DONE);
            }
        }
        return false;
    }
    bool isUsed;
};

// AddSC
void AddSC_scenario_artifact_brokenshore()
{
    RegisterInstanceScript(scenario_artifact_brokenshore, 1500);
    new npc_allari_soulweaver_98882();
    new go_temporary_allari_cage();
    new go_brokenshore_felsoul_portal();
    new npc_doomherald_saera_105095();
    new npc_doomherald_taraar_105094();
    new npc_gorgonnash_99046();
    new npc_caria_felsoul_99184();
    new go_aldrachi_warblades();
    new go_cavern_stones_7796();
}
