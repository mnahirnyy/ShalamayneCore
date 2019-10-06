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
            DoPlayScenePackageIdOnPlayers(DH_VENGEANCE_ARTIFACT_ACQUISTION_LOOTED_SCENE);
        }
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

    void SummonAldrachiWarblades()
    {
        TempSummon* aldrachiWb = instance->SummonCreature(NPC_ALDRACHI_WARBLADES, Position(-2746.991f, -328.47f, 38.4056f, 2.2876f));
        GameObject* aldrachiWbLoot = instance->SummonGameObject(GO_ALDRACHI_WARBLADES, Position(-2747.71f, -328.3544f, 38.4344f, 2.28768f), QuaternionData(), WEEK);
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
        EVENT_YELL_1 = 1,
        EVENT_SAY_2 = 2,
        EVENT_SAY_3 = 3,
        EVENT_SAY_4 = 4,
        EVENT_DESPAWN = 5,
    };

    struct npc_allari_soulweaver_98882_AI : public ScriptedAI
    {
        npc_allari_soulweaver_98882_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            sayGreeting = false;
            instance = me->GetInstanceScript();
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (who->IsPlayer())
                if (!sayGreeting)
                {
                    sayGreeting = true;
                    _events.ScheduleEvent(EVENT_YELL_1, 500);
                }
        }

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_FREED:
                if (instance->GetData(DATA_STAGE_1) == NOT_STARTED)
                    instance->SetData(DATA_STAGE_1, DONE);
                _events.ScheduleEvent(EVENT_SAY_2, 1000);
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
                    Talk(1);
                    _events.ScheduleEvent(EVENT_SAY_3, 4000);
                    me->LoadEquipment(1);
                    break;
                case EVENT_SAY_3:
                    Talk(2);
                    me->HandleEmoteCommand(EMOTE_STATE_KNEEL);
                    _events.ScheduleEvent(EVENT_SAY_4, 6000);
                    break;
                case EVENT_SAY_4:
                    Talk(3);
                    _events.ScheduleEvent(EVENT_DESPAWN, Seconds(60));
                    break;
                case EVENT_DESPAWN:
                    me->DespawnOrUnsummon();
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
        bool sayGreeting;
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
                if (Creature* chained_allari = go->FindNearestCreature(NPC_CHAINED_ALLARI, 10.0f, true))
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
            me->setActive(true);
            me->SetReactState(REACT_AGGRESSIVE);
        }

        void Reset() override
        {
            _events.Reset();
            Initialize();
        }

        void EnterCombat(Unit* /*who*/) override
        {
            _events.ScheduleEvent(EVENT_SHADOW_BOLT, 1000);
            _events.ScheduleEvent(EVENT_STALKING_SHADOWS, urand(8000, 10000));
        }

        void JustDied(Unit* /*killer*/) override
        {
            instance->SetData(DATA_STAGE_3, DONE);
            // me->DespawnOrUnsummon(20000, Seconds(300));
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (damage >= me->GetHealth())
                Talk(2);
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (who->IsPlayer())
                if (!conversationStarted)
                {   
                    _events.ScheduleEvent(EVENT_SAY_1, 500);
                    conversationStarted = true;
                }
        }

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_START_CONVERSATION:
                _events.ScheduleEvent(EVENT_SAY_1, 4000);
                break;
            default:
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

           /* if (!UpdateVictim())
                return;*/

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
                    _events.ScheduleEvent(EVENT_SAY_2, 4000);
                    break;
                case EVENT_SAY_2:
                    Talk(1);
                    if (Creature* doomherald_taraar = me->FindNearestCreature(105094, 15.0f, true))
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
            // me->DespawnOrUnsummon(20000, Seconds(300));
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            /*if (!UpdateVictim())
                return;*/

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

        void SummomNearTarget(uint8 count, uint32 entry, Position targetPos, uint32 duration)
        {
            for (uint8 i = 0; i < count; i++)
            {
                uint8 rand = urand(1, 2);
                float angle = frand(0.0f, 2.0f * float(M_PI));
                float x = targetPos.GetPositionX() + (5.0f * std::cos(angle));
                float y = targetPos.GetPositionY() + (5.0f * std::sin(angle));
                Position randomPosition = {
                    x, y, targetPos.GetPositionZ(), targetPos.GetOrientation()
                };
                me->SummonCreature(entry, randomPosition, TEMPSUMMON_CORPSE_DESPAWN, duration);
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
            // _events.ScheduleEvent(EVENT_SUMMON_FEL_CRUSHER, 10000);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (damage >= me->GetHealth())
                Talk(3);
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (me->CanStartAttack(who, false) && me->IsWithinDistInMap(who, me->GetAttackDistance(who) + me->m_CombatDistance))
                EnterCombat(who);
        }

        void JustDied(Unit* /*killer*/) override
        {
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
                    _events.ScheduleEvent(EVENT_FEL_CLEAVE, urand(6000, 9000));
                    break;
                case EVENT_FEL_CLEAVE:
                    DoCastVictim(SPELL_FEL_CLEAVE);
                    _events.ScheduleEvent(EVENT_FEL_CLEAVE, urand(8000, 10000));
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
                me->SetAIAnimKitId(0);
                me->PlayOneShotAnimKitId(15);
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
                float angle = frand(0.0f, 2.0f * float(M_PI));
                float x = targetPos.GetPositionX() + (5.0f * std::cos(angle));
                float y = targetPos.GetPositionY() + (5.0f * std::sin(angle));
                Position randomPosition = {
                    x, y, targetPos.GetPositionZ(), targetPos.GetOrientation()
                };
                me->SummonCreature(entry, randomPosition, TEMPSUMMON_CORPSE_DESPAWN, duration);
            }
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

class go_aldrachi_warblades_248785 : public GameObjectScript
{
public:
    go_aldrachi_warblades_248785() : GameObjectScript("go_aldrachi_warblades_248785") { isLooted = false; }

    void OnLootStateChanged(GameObject* go, uint32 state, Unit* unit)
    {
        if (state == GO_ACTIVATED && unit && !isLooted)
        {
            isLooted = true;
            if (Player* player = unit->ToPlayer())
                if (!player->GetQuestObjectiveData(42430, 1))
                    player->KilledMonsterCredit(114514);

            if (InstanceScript * instance = go->GetInstanceScript())
                if (instance->GetData(DATA_STAGE_7) == NOT_STARTED)
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
    new npc_allari_soulweaver_98882();
    new go_temporary_allari_cage();
    new go_brokenshore_felsoul_portal();
    new npc_doomherald_saera_105095();
    new npc_doomherald_taraar_105094();
    new npc_gorgonnash_99046();
    new npc_caria_felsoul_99184();
    new go_aldrachi_warblades_248785();
    new go_cavern_stones_7796();
}
