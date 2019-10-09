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
    NPC_DOOMHERALD_SAERA = 105095,
    NPC_DOOMHERALD_TARAAR = 105094,
    NPC_ALDRACHI_REVENANT = 105151,
    NPC_CARIA_FELSOUL = 99184,
    NPC_ALDRACHI_WARBLADES = 105155,
    GO_ALDRACHI_WARBLADES = 248785,
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
        _allariGUID = ObjectGuid::Empty;
        _doomheraldSaeraGUID = ObjectGuid::Empty;
        _doomheraldTaraarGUID = ObjectGuid::Empty;
        _cariaFelsoulGUID = ObjectGuid::Empty;
        _aldrachiRevenantGUID = ObjectGuid::Empty;
    }

    void OnPlayerEnter(Player* player) override
    {
        InstanceScript::OnPlayerEnter(player);
        TC_LOG_ERROR("server.worldserver", " === scenario_artifact_brokenshore: Player Entered  === ");
        if (player->GetMapId() == 1500)
        {
            _playerGUID = player->GetGUID();
            PhasingHandler::AddPhase(player, NORMAL_PHASE, true);
        }
        SummonAllariSouleater();
    }

    void OnCreatureCreate(Creature* creature) override
    {
        InstanceScript::OnCreatureCreate(creature);

        switch (creature->GetEntry())
        {
        case NPC_GORGONNASH:
            _gorgonnashGUID = creature->GetGUID();
            break;
        case NPC_ALLARI_SOULEATER:
            _allariGUID = creature->GetGUID();
            break;
        case NPC_DOOMHERALD_SAERA:
            _doomheraldSaeraGUID = creature->GetGUID();
            break;
        case NPC_DOOMHERALD_TARAAR:
            _doomheraldTaraarGUID = creature->GetGUID();
            break;
        case NPC_CARIA_FELSOUL:
            _cariaFelsoulGUID = creature->GetGUID();
            break;
        case NPC_ALDRACHI_REVENANT:
            _aldrachiRevenantGUID = creature->GetGUID();
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
            if (demonPortalsDestroyed == 2) {
                NextStep();
                SummonDemonTwins();
            }
        }
        else if (type == DATA_STAGE_3 && data == DONE)
        {
            ++demonTwinsKilled;
            if (demonTwinsKilled == 2) {
                NextStep();
                SummonGorgonnash();
            }
        }
        else if (type == DATA_STAGE_4 && data == DONE)
        {
            NextStep();
        }
        else if (type == DATA_STAGE_5 && data == DONE)
        {
            NextStep();
            SummonAldrachiRevenant();
            SummonCariaFelsoul();
        }
        else if (type == DATA_STAGE_6 && data == DONE)
        {
            NextStep();
            //summon Aldrachi Warblades GO + NPC
            SummonAldrachiWarblades();
        }
        else if (type == DATA_STAGE_7 && data == DONE)
        {
            NextStep();
            // CompleteScenario();
            DoPlayScenePackageIdOnPlayers(DH_VENGEANCE_ARTIFACT_ACQUISTION_LOOTED_SCENE);
        }
    }

    void SummonAllariSouleater()
    {
        TempSummon* allari = instance->SummonCreature(NPC_ALLARI_SOULEATER, Position(-2507.72f, 117.919f, 8.1995f, 0.079414f));
    }

    void SummonGorgonnash()
    {
        TempSummon* gorgonnash = instance->SummonCreature(NPC_GORGONNASH, Position(-2784.22f, -98.7661f, 47.9949f, 0.511382f));
        gorgonnash->AI()->SetData(51, 51);
    }
    
    void SummonDemonTwins()
    {
        TempSummon* doomheralSaera = instance->SummonCreature(NPC_DOOMHERALD_SAERA, Position(-2751.16f, -69.521f, 46.6362f, 4.99993f));
        TempSummon* doomheralTaraar = instance->SummonCreature(NPC_DOOMHERALD_TARAAR, Position(-2746.54f, -84.4343f, 46.6362f, 1.93767f));
        doomheralSaera->AI()->SetData(52, 52);
    }

    void SummonAldrachiRevenant()
    {   
        TempSummon* revenant = instance->SummonCreature(NPC_ALDRACHI_REVENANT, Position(-2810.06f, -243.924f, 38.6361f, 1.92589f));
    }

    void SummonCariaFelsoul()
    {
        TempSummon* caria = instance->SummonCreature(NPC_CARIA_FELSOUL, Position(-2749.17f, -330.338f, 38.7842f, 1.88583f));
    }

    void SummonAldrachiWarblades()
    {
        TempSummon* aldrachiWb = instance->SummonCreature(NPC_ALDRACHI_WARBLADES, Position(-2746.991f, -328.47f, 38.4056f, 2.2876f));
        GameObject* aldrachiWbLoot = instance->SummonGameObject(GO_ALDRACHI_WARBLADES, Position(-2747.71f, -328.3544f, 38.4344f, 2.28768f), QuaternionData(), 300);
    }

private:
    EventMap events;
    uint8 StepID;
    bool isComplete;
    ObjectGuid _playerGUID;
    ObjectGuid _gorgonnashGUID;
    ObjectGuid _allariGUID;
    ObjectGuid _doomheraldSaeraGUID;
    ObjectGuid _doomheraldTaraarGUID;
    ObjectGuid _cariaFelsoulGUID;
    ObjectGuid _aldrachiRevenantGUID;
    uint8 demonPortalsDestroyed;
    uint8 demonTwinsKilled;
};

class npc_allari_souleater_98882 : public CreatureScript
{
public:
    npc_allari_souleater_98882() : CreatureScript("npc_allari_souleater_98882") { }

    enum eAllari {
        DATA_FREED = 56,
        DATA_START_TALK = 55,
        EVENT_YELL_1 = 1,
        EVENT_SAY_2 = 2,
        EVENT_SAY_3 = 3,
        EVENT_SAY_4 = 4,
        EVENT_DESPAWN = 5,
    };

    struct npc_allari_souleater_98882_AI : public ScriptedAI
    {
        npc_allari_souleater_98882_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            sayGreeting = false;
            instance = me->GetInstanceScript();
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (!who || !who->IsInWorld() || !me->IsWithinDist(who, 70.0f, false))
                return;

            Player* player = who->GetCharmerOrOwnerPlayerOrPlayerItself();
            if (!player)
                return;
            if (instance->GetData(DATA_STAGE_1) == NOT_STARTED && !sayGreeting)
            {
                sayGreeting = true;
                Talk(0);
            }
        }

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_START_TALK:
                _events.ScheduleEvent(EVENT_YELL_1, 4000);
                break;
            case DATA_FREED:
                sayGreeting = false;
                Talk(1);
                _events.ScheduleEvent(EVENT_SAY_3, 3000);

                if (instance->GetData(DATA_STAGE_1) == NOT_STARTED)
                    instance->SetData(DATA_STAGE_1, DONE);
                break;
            default:
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_YELL_1:
                    Talk(0);
                    break;
                case EVENT_SAY_2:
                    me->LoadEquipment(1);
                    break;
                case EVENT_SAY_3:
                    me->HandleEmoteCommand(EMOTE_STATE_SIT_GROUND);
                    Talk(2);
                    _events.ScheduleEvent(EVENT_SAY_4, 3000);
                    break;
                case EVENT_SAY_4:
                    Talk(3);
                    _events.ScheduleEvent(EVENT_DESPAWN, 30000);
                    break;
                case EVENT_DESPAWN:
                    me->HandleEmoteCommand(EMOTE_STATE_NONE);
                    me->DespawnOrUnsummon();
                    break;
                default:
                    break;
                }
            }
        }

    private:
        EventMap _events;
        InstanceScript * instance;
        bool sayGreeting;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_allari_souleater_98882_AI(creature);
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
        DATA_ALLARI_FREED = 56,
    };

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->SetGoState(GO_STATE_READY);
        if (InstanceScript * instance = go->GetInstanceScript())
        {
            if (instance->GetData(DATA_STAGE_1) == NOT_STARTED)
            {
                if (Creature* chained_allari = go->FindNearestCreature(NPC_CHAINED_ALLARI, 10.0f, true))
                {
                    chained_allari->AI()->SetData(DATA_ALLARI_FREED, DATA_ALLARI_FREED);

                    go->ResetDoorOrButton();
                    go->DestroyForPlayer(player);

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
        EVENT_SAY_1 = 4,
        EVENT_SAY_2 = 5,
        SPELL_DEMON_LINK = 215837,
        SPELL_SHADOW_BOLT = 215885,
        SPELL_STALKING_SHADOWS = 215861,
        DATA_START_CONVERSATION = 52,
        DATA_START_TARAAR_CONVERSATION = 53,
    };

    struct npc_doomherald_saera_105095_AI : public ScriptedAI
    {
        npc_doomherald_saera_105095_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            instance = me->GetInstanceScript();
            conversationStarted = false;
        }

        void Reset() override
        {
            _events.Reset();
            Initialize();
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (!who || !who->IsInWorld() || !me->IsWithinDist(who, 60.0f, false))
                return;

            Player* player = who->GetCharmerOrOwnerPlayerOrPlayerItself();
            if (!player)
                return;
            if (instance->GetData(DATA_STAGE_3) == NOT_STARTED && !conversationStarted)
            {
                conversationStarted = true;
                _events.ScheduleEvent(EVENT_SAY_1, 500);
            }
        }

        void EnterCombat(Unit* /*who*/) override
        {
            _events.ScheduleEvent(EVENT_SHADOW_BOLT, 1000);
            _events.ScheduleEvent(EVENT_STALKING_SHADOWS, urand(8000, 10000));
        }

        void JustDied(Unit* /*killer*/) override
        {
            Talk(2);
            conversationStarted = false;
            instance->SetData(DATA_STAGE_3, DONE);
        }

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_START_CONVERSATION:
                Talk(0);
                _events.ScheduleEvent(EVENT_SAY_2, 3000);
                break;
            default:
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

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
                case EVENT_SAY_1:
                    Talk(0);
                    _events.ScheduleEvent(EVENT_SAY_2, 3000);
                    break;
                case EVENT_SAY_2:
                    Talk(1);
                    if (Creature* doomherald_taraar = me->FindNearestCreature(105094, 20.0f, true))
                        doomherald_taraar->AI()->SetData(DATA_START_TARAAR_CONVERSATION, DATA_START_TARAAR_CONVERSATION);
                    break;
                default:
                    break;
                }
            }
            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

    private:
        EventMap _events;
        InstanceScript * instance;
        bool conversationStarted;
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
        EVENT_SAY_1 = 4,
        EVENT_SAY_2 = 5,
        SPELL_DEMON_LINK = 215837,
        SPELL_FEL_FIREBALL = 215852,
        SPELL_SUMMON_FEL_FAMILIARS = 215842,
        DATA_START_TALK = 53,
        NPC_FEL_FAMILIAR = 108686,
        SPELL_FEL_FAMILIAR = 215844,
        SPELL_FEL_FAMILIAR_2 = 215847,
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
            _events.ScheduleEvent(EVENT_FEL_FIREBALL, 1000);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            /*if (HealthBelowPct(60))
                _events.ScheduleEvent(EVENT_SUMMON_FEL_FAMILIARS, 500);*/
        }

        void JustDied(Unit* /*killer*/) override
        {
           std::list<Creature*> summonedFelFamiliars;
            me->GetCreatureListWithEntryInGrid(summonedFelFamiliars, NPC_FEL_FAMILIAR, me->GetVisibilityRange());
            for (std::list<Creature*>::const_iterator itr = summonedFelFamiliars.begin(); itr != summonedFelFamiliars.end(); ++itr)
                (*itr)->ToCreature()->DespawnOrUnsummon(0);

            instance->SetData(DATA_STAGE_3, DONE);
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_FEL_FIREBALL:
                    DoCastVictim(SPELL_FEL_FIREBALL);
                    _events.ScheduleEvent(EVENT_FEL_FIREBALL, 4000);
                    break;
                case EVENT_SUMMON_FEL_FAMILIARS:
                    // DoCastVictim(SPELL_SUMMON_FEL_FAMILIARS);
                    //if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                    //    SummomNearTarget(2, NPC_FEL_FAMILIAR, target->GetPosition(), 20000); // 2 Fel Familiars
                    break;
                case EVENT_SAY_1:
                    Talk(0);
                    _events.ScheduleEvent(EVENT_SAY_2, 3000);
                    break;
                case EVENT_SAY_2:
                    Talk(1);
                    break;
                default:
                    break;
                }
            }
            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_START_TALK:
                _events.ScheduleEvent(EVENT_SAY_1, 2000);
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
        DATA_START_ANIM = 51,
        NPC_BURNING_CRUSHER = 105103,
    };

    struct npc_gorgonnash_99046_AI : public ScriptedAI
    {
        npc_gorgonnash_99046_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            instance = me->GetInstanceScript();
            infernalsSummoned = false;
        }

        void Reset() override
        {
            _events.Reset();
            Initialize();
            me->setActive(true);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            Talk(1);
            _events.ScheduleEvent(EVENT_CREEPING_DOOM, 5000);
            _events.ScheduleEvent(EVENT_FEL_CLEAVE, 500);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (damage >= me->GetHealth())
                Talk(3);

            if (HealthBelowPct(40) && !infernalsSummoned)
            {
                infernalsSummoned = true;
                _events.ScheduleEvent(EVENT_SUMMON_FEL_CRUSHER, 500);
            }
                
        }

        void JustDied(Unit* /*killer*/) override
        {
            infernalsSummoned = false;

            std::list<Creature*> summonedCrushers;
            me->GetCreatureListWithEntryInGrid(summonedCrushers, NPC_BURNING_CRUSHER, me->GetVisibilityRange());
            for (std::list<Creature*>::const_iterator itr = summonedCrushers.begin(); itr != summonedCrushers.end(); ++itr)
                (*itr)->ToCreature()->DespawnOrUnsummon(0);

            if (instance->GetData(DATA_STAGE_4) == NOT_STARTED)
                instance->SetData(DATA_STAGE_4, DONE);
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CREEPING_DOOM:
                    DoCastVictim(SPELL_CREEPING_DOOM);
                    _events.ScheduleEvent(EVENT_CREEPING_DOOM, urand(6000, 9000));
                    break;
                case EVENT_FEL_CLEAVE:
                    DoCastVictim(SPELL_FEL_CLEAVE);
                    _events.ScheduleEvent(EVENT_FEL_CLEAVE, urand(15000, 18000));
                    break;
                case EVENT_SUMMON_FEL_CRUSHER:
                    _events.CancelEvent(EVENT_SUMMON_FEL_CRUSHER);
                    Talk(2);
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                        SummomNearTarget(2, NPC_BURNING_CRUSHER, target->GetPosition(), 20000); // 2 Burning Crushers
                    break;
                default:
                    break;
                }
            }
            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_START_ANIM:
                Talk(0);
                me->SetAIAnimKitId(6870);
                break;
            default:
                break;
            }
        }

        void SummomNearTarget(uint8 count, uint32 entry, Position targetPos, uint32 duration)
        {
            for (uint8 i = 0; i < count; i++)
            {
                uint8 rand = urand(1, 2);
                float angle = frand(0.0f, 5.0f * float(M_PI));
                float x = targetPos.GetPositionX() + (10.0f * std::cos(angle));
                float y = targetPos.GetPositionY() + (10.0f * std::sin(angle));
                Position randomPosition = {
                    x, y, targetPos.GetPositionZ(), targetPos.GetOrientation()
                };
                me->SummonCreature(entry, randomPosition, TEMPSUMMON_CORPSE_DESPAWN, duration);
            }
        }

    private:
        EventMap _events;
        InstanceScript * instance;
        bool infernalsSummoned;
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
        SPELL_CALL_WARBLADES_VISUAL_1 = 195154,
        SPELL_CALL_WARBLADES_VISUAL_2 = 195151,
        EVENT_CALL_OF_THE_WARBLADES = 1,
        EVENT_FELSOUL_SLAM = 2,
        EVENT_SIGIL_OF_POWER = 3,
        EVENT_SIGIL_OF_POWER_2 = 4,
        EVENT_SOUL_CARVER = 5,
        EVENT_TALK_3 = 6,
        EVENT_TALK_4 = 7,
        EVENT_CALL_WARBLADES_VISUAL_1 = 8,
        EVENT_CALL_WARBLADES_VISUAL_2 = 9,
        TEXT_SAY_1 = 0, // 'For every soul I claim, my power grows. I will rule this world... ALL worlds!'
        TEXT_SAY_2 = 1, // 'WITNESS THE MIGHT OF THE ALDRACHI!'
        TEXT_SAY_3 = 2, // 'Your destiny awaits!'
        TEXT_SAY_4 = 3, // 'Do you not see? Kil\'jaeden offers power Illidan never could!'
        TEXT_SAY_5 = 4, // 'I WILL claim your soul, even if I have to tear it from your lifeless corpse!'
        TEXT_SAY_6 = 5, // 'I will... be... reborn...'
    };

    struct npc_caria_felsoul_99184_AI : public ScriptedAI
    {
        npc_caria_felsoul_99184_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            instance = me->GetInstanceScript();
            _playerGUID = ObjectGuid::Empty;
            startTalk = false;
            jumpPosition = false;
        }

        void Reset() override
        {
            _events.Reset();
            Initialize();
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (!who || !who->IsInWorld() || !me->IsWithinDist(who, 60.0f, false))
                return;

            Player* player = who->GetCharmerOrOwnerPlayerOrPlayerItself();
            if (!player)
                return;
            _playerGUID = player->GetGUID();
            if (instance->GetData(DATA_STAGE_6) == NOT_STARTED && !startTalk)
            {
                startTalk = true;
                Talk(TEXT_SAY_1);
                _events.ScheduleEvent(EVENT_CALL_WARBLADES_VISUAL_1, 2000);
            }
        }

        void EnterCombat(Unit* /*who*/) override
        {
            Talk(TEXT_SAY_3);
            _events.ScheduleEvent(EVENT_FELSOUL_SLAM, 1500);
            _events.ScheduleEvent(EVENT_SIGIL_OF_POWER, 8000);
            _events.ScheduleEvent(EVENT_SIGIL_OF_POWER_2, 4000);
            _events.ScheduleEvent(EVENT_SOUL_CARVER, 5000);
            _events.ScheduleEvent(EVENT_TALK_3, 5000);
        }

        void JustDied(Unit* /*killer*/) override
        {
            startTalk = false;
            jumpPosition = false;
            Talk(TEXT_SAY_6);
            if (instance->GetData(DATA_STAGE_6) == NOT_STARTED)
                instance->SetData(DATA_STAGE_6, DONE);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (HealthBelowPct(25) && !jumpPosition)
            {
                jumpPosition = true;
                _events.ScheduleEvent(EVENT_CALL_OF_THE_WARBLADES, 500);
            }  
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CALL_WARBLADES_VISUAL_1:
                    DoCastSelf(SPELL_CALL_WARBLADES_VISUAL_1, true);
                    _events.ScheduleEvent(EVENT_CALL_WARBLADES_VISUAL_2, 6000);
                    break;
                case EVENT_CALL_WARBLADES_VISUAL_2:
                    DoCastSelf(SPELL_CALL_WARBLADES_VISUAL_2, true);
                    Talk(TEXT_SAY_2);
                    break;
                case EVENT_TALK_3:
                    Talk(TEXT_SAY_4);
                    break;
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
                    Talk(TEXT_SAY_5);
                    _events.CancelEvent(EVENT_FELSOUL_SLAM);
                    _events.CancelEvent(EVENT_SOUL_CARVER);
                    _events.CancelEvent(SPELL_SIGIL_OF_POWER);
                    _events.CancelEvent(EVENT_SIGIL_OF_POWER_2);
                    me->SetReactState(REACT_PASSIVE);
                    me->GetMotionMaster()->MoveJump(-2726.95f, -313.85f, 30.8943f, 2.2876f, 15.0f, 10.0f);
                    if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                        me->CastSpell(player, SPELL_CALL_OF_THE_WARBLADES, true);
                    break;
                default:
                    break;
                }
            }
            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

    private:
        EventMap _events;
        InstanceScript * instance;
        ObjectGuid _playerGUID;
        bool startTalk;
        bool jumpPosition;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_caria_felsoul_99184_AI(creature);
    }
};

// Aldrachi Revenant 105151
class npc_aldrachi_revenant_105151 : public CreatureScript
{
public:
    npc_aldrachi_revenant_105151() : CreatureScript("npc_aldrachi_revenant_105151") { }

    enum eRevenant
    {
        SPELL_DARK_PRESENCE = 208196,
        SPELL_DESPAIR = 216020,
        EVENT_DARK_PRESENCE = 1,
        EVENT_DESPAIR = 2,
        TEXT_SAY_1 = 0, // 'Your soul will be ours...'
    };

    struct npc_aldrachi_revenant_105151_AI : public ScriptedAI
    {
        npc_aldrachi_revenant_105151_AI(Creature* creature) : ScriptedAI(creature) {
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
        }

        void EnterCombat(Unit* /*who*/) override
        {
            Talk(TEXT_SAY_1);
            _events.ScheduleEvent(EVENT_DARK_PRESENCE, 1500);
            _events.ScheduleEvent(EVENT_DESPAIR, 8000);
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_DARK_PRESENCE:
                    DoCastVictim(SPELL_DARK_PRESENCE);
                    _events.ScheduleEvent(EVENT_DARK_PRESENCE, urand(6000, 8000));
                    break;
                case EVENT_DESPAIR:
                    DoCastVictim(SPELL_DESPAIR);
                    _events.ScheduleEvent(EVENT_DESPAIR, 5000);
                    break;
                default:
                    break;
                }
            }
            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

    private:
        EventMap _events;
        InstanceScript * instance;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_aldrachi_revenant_105151_AI(creature);
    }
};

class go_aldrachi_warblades_248785 : public GameObjectScript
{
public:
    go_aldrachi_warblades_248785() : GameObjectScript("go_aldrachi_warblades_248785") { isLooted = false; }

    void OnLootStateChanged(GameObject* go, uint32 state, Unit* unit)
    {
        /*if (!isLooted)
        {
            isLooted = true;
            if (Player* player = unit->ToPlayer())
                if (!player->GetQuestObjectiveData(42430, 1))
                    player->KilledMonsterCredit(114514);

            if (InstanceScript * instance = go->GetInstanceScript())
                if (instance->GetData(DATA_STAGE_7) == NOT_STARTED)
                    instance->SetData(DATA_STAGE_7, DONE);
        }*/
        if (state == GO_ACTIVATED && unit)
            if (Player* player = unit->ToPlayer())
                TC_LOG_ERROR("server.worldserver", " === go_aldrachi_warblades_248785  STATE  %u === ", state);
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
            if (!isUsed)
            {
                isUsed = true;
                go->DestroyForPlayer(player);

                if (instance->GetData(DATA_STAGE_5) == NOT_STARTED)
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
    new npc_allari_souleater_98882();
    new go_temporary_allari_cage();
    new go_brokenshore_felsoul_portal();
    new npc_doomherald_saera_105095();
    new npc_doomherald_taraar_105094();
    new npc_gorgonnash_99046();
    new npc_aldrachi_revenant_105151();
    new npc_caria_felsoul_99184();
    new go_aldrachi_warblades_248785();
    new go_cavern_stones_7796();
}
