/*
 * Copyright (C) 2019-2021 5CentsCore <https://github.com/mnahirnyy/5CentsCore>
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
#include "GameObjectAI.h"
#include "PhasingHandler.h"
#include "SceneMgr.h"
#include "ScriptMgr.h"
#include "CombatAI.h"
#include "TemporarySummon.h"
#include "Unit.h"

enum DataTypes
{
	SCENARIO_ID_DH = 900, // The Twinblades of the Deceiver
    SCENARIO_ID_WARL = 1097, // Dark Whispers
    /* DH Scenario Data */
	DATA_DH_STEP_1 = 1808, // Fly into Felsoul Hold. (Stalking Your Prey)
	DATA_DH_STEP_2 = 1821, // Dive into the fray. (They Are Not Prepared)
	DATA_DH_STEP_3 = 1822, // Destroy the wards protecting Varedis and absorb the souls of his minions. (Wrath of the Illidari)
	DATA_DH_STEP_4 = 1825, // Kill Varedis Felsoul. (Unleashed Havoc)
	DATA_DH_STEP_5 = 2712, // Wield the Twinblades of the Deceiver. (The Twinblades of the Deceiver)
    CRITERIA_DH_STEP_1 = 44016,
    CRITERIA_DH_STEP_2 = 44321,
    CRITERIA_DH_STEP_3 = 44323,
    CRITERIA_DH_STEP_4 = 44331,
    CRITERIA_DH_STEP_5 = 49475,
    /* Demo Warlock Scenario Data */
    DATA_WARL_STEP_1 = 2443, // The skull should be within Felsoul Hold.Make your way down the path and search for it. (Searching the Hold)
    DATA_WARL_STEP_2 = 2475, // Defeat the Felborn Overfiend. (Getting Over the Overfiend)
    DATA_WARL_STEP_3 = 2476, // Mephistroth has escaped with the skull. Find a way across his trap and chase after him! (Demon Hunting)
    DATA_WARL_STEP_4 = 2477, // Mephistroth has sent his minions after you.Survive their assault until Lady Tyrana and Pain Mistress Nikta arrives, then kill them. (The Legion)
    DATA_WARL_STEP_5 = 2478, // Mephistroth is attempting to destroy the skull!Clear the way to his ritual site and stop him! (Screams of the Skull)
    DATA_WARL_STEP_6 = 2479, // Mephistroth has escaped but the skull is intact.Take it. (The Skull of the Man''ari)
    DATA_WARL_STEP_7 = 2502, // The skull is yours!Step through its portal to depart this place. (There''s a New Master in Town)
    CRITERIA_WARL_STEP_1 = 47894,
    CRITERIA_WARL_STEP_2 = 48017,
    CRITERIA_WARL_STEP_3 = 48045,
    CRITERIA_WARL_STEP_4 = 48047,
    CRITERIA_WARL_STEP_5 = 48050,
    CRITERIA_WARL_STEP_6 = 48053,
    CRITERIA_WARL_STEP_7 = 48097,
	DATA_MAX_ENCOUNTERS_DH = 5,
	NORMAL_PHASE = 169,
    DH_PHASE = 251,
    WARL_PHASE = 252,
	DATA_SURAMAR_ACQUISITION = 0,
	DATA_STAGE_1 = 1,
	DATA_STAGE_2 = 2,
	DATA_STAGE_3 = 3,
	DATA_STAGE_4 = 4,
	DATA_STAGE_5 = 5,
    DATA_STAGE_6 = 6,
    DATA_STAGE_7 = 7,
    DATA_STAGE_8 = 8,
    DATA_CANCEL_SCENE = 12,
    DATA_GET_BRIDGE = 13,
    GO_FIRST_FELSHIELD_WARD = 243428,
    GO_SECOND_FELSHIELD_WARD = 243472,
    GO_THIRD_FELSHIELD_WARD = 243473,
    NPC_VAREDIS_FELSOUL = 94836,
    NPC_TWINBLADES_OF_THE_DECEIVER = 109978,
    NPC_FELSOUL_BERSERKER = 95423,
    NPC_FEL_COMMANDER_IGRIUS = 95285,
    NPC_FIST_OF_DECEIVER = 95429,
    GO_TWINBLADES_OF_THE_DECEIVER = 251878,
    KJ_CONVERSATION_1 = 6805,
    KJ_CONVERSATION_2 = 6806,
    IGRIUS_CONV_1 = 6809, // To arms! Lord Felsoul must not be disturbed.
    IGRIUS_CONV_2 = 6810, // Do you crave death, elf? Do you dare face my lords wrath alone?
    IGRIUS_CONV_3 = 6811, // Moarg to the front! This has gone on long enough.
    IGRIUS_CONV_4 = 6812, // Bathe them in hellfire! Halt their advance!
    VAREDIS_CONV_1 = 6813, // Its been years. You should know better than to stand against me.
    VAREDIS_CONV_2 = 6814, // Pity your allies had to die. But dont worry. Ill put their souls to good use.
    KAYN_CONV_1 = 6815, // The demons underestimate your power. Punish them for their hubris.
    ALTRUIS_CONV_1 = 6816, // The fools think they can stand against you. Show them the price of their arrogance!
    QUEST_THE_HUNT_ALTRUIS = 41119,
    QUEST_THE_HUNT_KAYN = 39247,
    QUEST_DARK_WHISPERS = 42125,
    RED_ILLIDARI_FELBAT = 101902,
    TWINBLADES_KILLCREDIT = 114515,
    SPELL_VAREDIS_FELSOUL_REVEAL = 189475,
    SPELL_VAREDIS_FELSOUL_REVEAL_CANCEL = 189501,
    SPELL_TWINBLADES_OF_DECEIVER = 189916,
    SPELL_DH_CAMP_EXPLOSION = 186760,
    SPELL_DH_CAMP_EXPLOSION_CANCEL = 189002,
    /* Demo Warlock Data */
    SPELL_RETRIEVING_THE_SKULL = 211766,
    SPELL_SKULL_WANDER_AURA = 223917,
    NPC_THALKIEL_SKULL_OF_THE_MANARI = 111031,
    GO_SKULL_OF_THE_MANARI = 249821,
    KILLCREDIT_OBTAIN_SKULL_OF_MANARI = 106973,
    NPC_PORTAL_THALKIEL = 106846,
};

struct scenario_artifact_suramar_acquisition : public InstanceScript
{
	scenario_artifact_suramar_acquisition(InstanceMap* map) : InstanceScript(map) { }

	void Initialize() override
	{
		SetBossNumber(1);
		SetData(DATA_SURAMAR_ACQUISITION, NOT_STARTED);
        ClassMode = DATA_STAGE_7;
		StepID = DATA_STAGE_1;
		isComplete = false;
        _playerGUID = ObjectGuid::Empty;
        _varedisGUID = ObjectGuid::Empty;
        demonSoulsAbsorbed = 0.0f;
        firstWardDestroyed = false;
        secondWardDestroyed = false;
        thirdWardDestroyed = false;
        allWardsDestroyed = false;
        _currentScenarioId = 0;
        eredarsKilled = 0;
	}

	void OnPlayerEnter(Player* player) override
	{
        if (player->getClass() == CLASS_DEMON_HUNTER)
        {
            _currentScenarioId = 900;
            _playerGUID = player->GetGUID();
            // Phase
            // player->GetPhaseShift().AddPhase(DH_PHASE, PhaseFlags::None, nullptr);
            ClassMode = DATA_STAGE_5;
            SendScenarioState(ScenarioData(SCENARIO_ID_DH, DATA_DH_STEP_1));
            // Reset the scenario data
            for (uint8 i = 1; i <= ClassMode; ++i)
                SetData(i, NOT_STARTED);
            // Dungeon Diificulty
            player->SetDungeonDifficultyID(DIFFICULTY_3_MAN_SCENARIO_N);
            player->SendDungeonDifficulty(DIFFICULTY_3_MAN_SCENARIO_N);
            // We just skip two steps when player flying and floating to the area
            SkipTwoSteps();
        }
        else if (player->getClass() == CLASS_WARLOCK)
        {
            _currentScenarioId = 1097;
            _playerGUID = player->GetGUID();
            // Phase
            // player->GetPhaseShift().AddPhase(WARL_PHASE, PhaseFlags::None, nullptr);
            ClassMode = DATA_STAGE_7;
            SendScenarioState(ScenarioData(SCENARIO_ID_WARL, DATA_WARL_STEP_1));
            // Reset the scenario data
            for (uint8 i = 1; i <= ClassMode; ++i)
                SetData(i, NOT_STARTED);
            // Dungeon Diificulty
            player->SetDungeonDifficultyID(DIFFICULTY_3_MAN_SCENARIO_N);
            player->SendDungeonDifficulty(DIFFICULTY_3_MAN_SCENARIO_N);
            // Zone summons and specific things
        }
        else {
            // default one
            _playerGUID = player->GetGUID();
            player->SetDungeonDifficultyID(DIFFICULTY_NORMAL);
            player->SendDungeonDifficulty(DIFFICULTY_NORMAL);
            ClassMode = DATA_SURAMAR_ACQUISITION;
        }

        InstanceScript::OnPlayerEnter(player);
	}

    void OnPlayerExit(Player* player) override {}

	void OnCreatureCreate(Creature* creature) override
	{
		InstanceScript::OnCreatureCreate(creature);

        switch (creature->GetEntry())
        {
        case NPC_VAREDIS_FELSOUL:
            _varedisGUID = creature->GetGUID();
            break;
        case NPC_FIST_OF_DECEIVER:
            _fistDeceiverGUID = creature->GetGUID();
            break;
        case NPC_FEL_COMMANDER_IGRIUS:
            _igriusGUID = creature->GetGUID();
            break;
        default:
            break;
        }
	}

    void OnUnitDeath(Unit* who)
    {
        InstanceScript::OnUnitDeath(who);

        switch (who->GetEntry())
        {
        case 95329: // Felsoul Fleshcarver
        case 95314: // Felsoul Stalker
        case 95313: // Felsoul Chaosweaver
        case 95848: // Felsoul Ritualist
        case 95423: // Felsoul Berserker
        case 95429: // Fist of the Deceiver
        case 95452: // Felsoul Crusher
            demonSoulsAbsorbed = demonSoulsAbsorbed + 6.5f;
            if (who->GetEntry() == 95452)
                DoDelayedConversation(6000, VAREDIS_CONV_2); // Pity your allies had to die. Dont worry. Ill put their souls to good use.
            break;
        case 106698: // Eredar Doomweaver
            eredarsKilled = eredarsKilled + 1;
            SetData(DATA_STAGE_1, 106698);
            break;
        case 106644: // Felborn Overfiend
            SetData(DATA_STAGE_2, DONE);
            break;
        default:
            break;
        }
    }

	void NextStep()
	{
		if (StepID < ClassMode)
		{
			++StepID;
			if (Scenario* scenario = instance->GetInstanceScenario())
                scenario->CompleteCurrStep();
		}
		else if (StepID == ClassMode)
		{
			if (Scenario* scenario = instance->GetInstanceScenario())
			{
				if (!isComplete) {
					scenario->CompleteCurrStep();
				}
				else {
                    scenario->CompleteCurrStep(); // COMPLETE CURRENT STEP
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

        if (type == DATA_STAGE_1) //  && data == DONE
        {
            switch (data)
            {
            case 106698:
                if (_currentScenarioId == SCENARIO_ID_WARL && eredarsKilled == 3)
                    SummonMephisroth1(); // Summon Mephistroth 106692
                break;
            case DONE:
                NextStep();
                if (_currentScenarioId == SCENARIO_ID_WARL)
                    SummonOverfiend(); // Summon Felborn Overfiend 106644
                break;
            default:
                break;
            }
            // NextStep();
        }
        else if (type == DATA_STAGE_2 && data == DONE)
        {
            NextStep();
            if (_currentScenarioId == SCENARIO_ID_DH)
            {
                // DoCastSpellOnPlayers(SPELL_DH_CAMP_EXPLOSION);
                DoPlayScenePackageIdOnPlayers(1411);
                DoDelayedConversation(1000, IGRIUS_CONV_1);
            }
        }
        else if (type == DATA_STAGE_3)
        {
            switch (data)
            {
            case GO_FIRST_FELSHIELD_WARD:
                firstWardDestroyed = true;
                DoConversation(IGRIUS_CONV_4);
                break;
            case GO_SECOND_FELSHIELD_WARD:
                secondWardDestroyed = true;
                DoConversation(VAREDIS_CONV_1);
                // SummonFistOfTheDeceiver();
                break;
            case GO_THIRD_FELSHIELD_WARD:
                thirdWardDestroyed = true;
                break;
            case DONE:
                NextStep();
                break;
            default:
                break;
            }

            if (isAllWardsDestroyed() && demonSoulsAbsorbed >= 100)
            {
                allWardsDestroyed = true;
                NextStep();
                DoCastSpellOnPlayers(SPELL_VAREDIS_FELSOUL_REVEAL);
            }
        }
        else if (type == DATA_STAGE_4 && data == DATA_CANCEL_SCENE)
        {
            SummonVaredisFelsoul(); // Summon Varedis Felsoul
        }
        else if (type == DATA_STAGE_4 && data == DONE)
        {
            NextStep();
            if (_currentScenarioId == SCENARIO_ID_DH)
                SummonTwinbladesOfDeceiver(); // Summon Twinblades of the Deceiver GO + NPC
        }
        else if (type == DATA_STAGE_5 && data == DONE)
        {
            if (_currentScenarioId == SCENARIO_ID_DH)
            {
                DoCastSpellOnPlayers(SPELL_TWINBLADES_OF_DECEIVER);
                isComplete = true;
                NextStep();
                SummonFelBat(); // Summon Felbat to return to Dalaran
            }
            else if (_currentScenarioId == SCENARIO_ID_WARL)
            {
                SummonSkullOfManari();
                NextStep();
            }

        }
        else if (type == DATA_STAGE_6 && data == DONE)
        {
            DoCastSpellOnPlayers(SPELL_RETRIEVING_THE_SKULL);
            NextStep();
            SummonPortalOfThalkiel();
        }
        else if (type == DATA_STAGE_7 && data == DONE)
        {
            isComplete = true;
            NextStep();
        }
	}

    bool isAllWardsDestroyed()
    {
        return firstWardDestroyed && secondWardDestroyed && thirdWardDestroyed;
    }

    void SummonTwinbladesOfDeceiver()
    {
        Map::PlayerList const& players = instance->GetPlayers();
        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
        {
            if (Player* player = itr->GetSource())
            {
                Creature* twinbladesWb = player->SummonCreature(NPC_TWINBLADES_OF_THE_DECEIVER, Position(984.354f, 4826.77f, 34.7617f, 2.80852f));
                GameObject* twinbladesWbLoot = player->SummonGameObject(GO_TWINBLADES_OF_THE_DECEIVER, Position(984.354f, 4826.77f, 34.7617f, 2.80852f), QuaternionData(), 300);
            }
        }
    }

    void SummonSkullOfManari()
    {
        Map::PlayerList const& players = instance->GetPlayers();
        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
        {
            if (Player* player = itr->GetSource())
            {
                Creature* manariWb = instance->SummonCreature(NPC_THALKIEL_SKULL_OF_THE_MANARI, Position(1003.776f, 4932.012f, 36.2760f, 0.442167f));
                GameObject* manariWbLoot = instance->SummonGameObject(GO_SKULL_OF_THE_MANARI, Position(1003.776f, 4932.012f, 36.2760f, 0.442167f), QuaternionData(), 300);
            }
        }
    }

    void SummonVaredisFelsoul()
    {
        Map::PlayerList const& players = instance->GetPlayers();
        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
        {
            if (Player* player = itr->GetSource())
                if (Creature* varedisFelsoul = player->SummonCreature(NPC_VAREDIS_FELSOUL, Position(976.344f, 4842.468f, 35.1716f, 1.17540f)))
                    varedisFelsoul->AI()->SetData(DATA_GET_BRIDGE, DATA_GET_BRIDGE);
        }
    }

    void SummonMephisroth1()
    {
        Map::PlayerList const& players = instance->GetPlayers();
        Map::PlayerList::const_iterator itr = players.begin();
        if (Player* player = itr->GetSource())
            if (Creature* mephi1 = player->SummonCreature(106692, Position(1044.419f, 5128.788f, 57.953f, 6.15776f)))
                mephi1->AI()->SetData(1515, 1515);

    }

    void SummonOverfiend()
    {
        Map::PlayerList const& players = instance->GetPlayers();
        Map::PlayerList::const_iterator itr = players.begin();
            if (Player* player = itr->GetSource())
                Creature* overfiend = player->SummonCreature(106644, Position(1052.626f, 5129.9101f, 57.259f, 5.98881f));
    }

    void SummonFelBat()
    {
        Map::PlayerList const& players = instance->GetPlayers();
        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
        {
            if (Player* player = itr->GetSource())
                Creature* felbat = instance->SummonCreature(RED_ILLIDARI_FELBAT, Position(960.155f, 4858.343f, 35.267f, 4.5778f));
        }
    }

    void SummonPortalOfThalkiel()
    {
        Creature* thalkielPortal = instance->SummonCreature(NPC_PORTAL_THALKIEL, Position(1015.169f, 4942.440f, 36.276f, 0.705941f));
    }

    void SkipTwoSteps() // Skip the flying and floating steps in Demon Hunter Scenario
    {
        if (GetData(DATA_STAGE_1) == NOT_STARTED)
        {
            SetData(DATA_STAGE_1, DONE);
            SetData(DATA_STAGE_2, DONE);
        }
    }

private:
	uint8 StepID;
	bool isComplete;
    uint8 ClassMode;
    ObjectGuid _playerGUID;
    ObjectGuid _igriusGUID;
    ObjectGuid _fistDeceiverGUID;
    ObjectGuid _varedisGUID;
    double demonSoulsAbsorbed;
    bool firstWardDestroyed;
    bool secondWardDestroyed;
    bool thirdWardDestroyed;
    bool allWardsDestroyed;
    int _currentScenarioId;
    int eredarsKilled;
};

/* Demon Hunter Havoc Artifact Acquisition Scripts */
class scene_camp_explosion : public SceneScript
{
public:
    scene_camp_explosion() : SceneScript("scene_camp_explosion") {}

    void OnSceneComplete(Player* player, uint32 /*sceneInstanceID*/, SceneTemplate const* /*sceneTemplate*/) override
    {
        if (InstanceScript * instance = player->GetInstanceScript())
        {
            if (player->HasQuest(QUEST_THE_HUNT_ALTRUIS))
                instance->DoDelayedConversation(5000, ALTRUIS_CONV_1);
            else if (player->HasQuest(QUEST_THE_HUNT_KAYN))
                instance->DoDelayedConversation(5000, KAYN_CONV_1);
            // instance->DoCastSpellOnPlayers(SPELL_DH_CAMP_EXPLOSION_CANCEL);
        }
    }
};

class scene_varedis_reveal : public SceneScript
{
public:
    scene_varedis_reveal() : SceneScript("scene_varedis_reveal") {}

    void OnSceneEnd(Player* player, uint32 /*sceneInstanceID*/, SceneTemplate const* /*sceneTemplate*/) override
    {
        if (InstanceScript * instance = player->GetInstanceScript())
            instance->SetData(DATA_STAGE_4, DATA_CANCEL_SCENE);
    }
};

class scene_twinblades_looted : public SceneScript
{
public:
    scene_twinblades_looted() : SceneScript("scene_twinblades_looted") {}

    void OnSceneEnd(Player* player, uint32 /*sceneInstanceID*/, SceneTemplate const* /*sceneTemplate*/) override
    {
        if (InstanceScript * instance = player->GetInstanceScript())
        {
            if (player->HasQuest(41119))
                instance->DoDelayedConversation(500, 6818);
            else if (player->HasQuest(39247))
                instance->DoDelayedConversation(500, 6817);
        }
    }
};

/* First Felshield Ward 243428 */
class go_first_felshieldward : public GameObjectScript
{
public:
    go_first_felshieldward() : GameObjectScript("go_first_felshieldward") {}

    struct go_first_felshieldward_AI : public GameObjectAI
    {
        go_first_felshieldward_AI(GameObject* go) : GameObjectAI(go), instance(go->GetInstanceScript()) { }

        void OnStateChanged(uint32 state, Unit* who) override
        {
            if (state == GO_ACTIVATED)
            {
                if (who)
                    go->SendCustomAnim(ANIM_DESTROY);
            }
            else if (state == GO_JUST_DEACTIVATED)
            {
                go->DespawnOrUnsummon();
                instance->SetData(DATA_STAGE_3, go->GetEntry());
            }
        }

        InstanceScript* instance;
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_first_felshieldward_AI(go);
    }
};

/* Second Felshield Ward 243472 */
class go_second_felshieldward : public GameObjectScript
{
public:
    go_second_felshieldward() : GameObjectScript("go_second_felshieldward") {}

    struct go_second_felshieldward_AI : public GameObjectAI
    {
        go_second_felshieldward_AI(GameObject* go) : GameObjectAI(go), instance(go->GetInstanceScript()) { }

        void OnStateChanged(uint32 state, Unit* who) override
        {
            if (state == GO_ACTIVATED)
            {
                if (who)
                    go->SendCustomAnim(ANIM_DESTROY);
            }
            else if (state == GO_JUST_DEACTIVATED)
            {
                go->DespawnOrUnsummon();
                instance->SetData(DATA_STAGE_3, go->GetEntry());
            }
        }

        InstanceScript* instance;
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_second_felshieldward_AI(go);
    }
};

/* Third Felshield Ward 243473*/
class go_third_felshieldward : public GameObjectScript
{
public:
    go_third_felshieldward() : GameObjectScript("go_third_felshieldward") {}

    struct go_third_felshieldward_AI : public GameObjectAI
    {
        go_third_felshieldward_AI(GameObject* go) : GameObjectAI(go), instance(go->GetInstanceScript()) { }

        void OnStateChanged(uint32 state, Unit* who) override
        {
            if (state == GO_ACTIVATED)
            {
                if (who)
                    go->SendCustomAnim(ANIM_DESTROY);
            }
            else if (state == GO_JUST_DEACTIVATED)
            {
                go->DespawnOrUnsummon();
                instance->SetData(DATA_STAGE_3, go->GetEntry());
            }
        }

        InstanceScript* instance;
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_third_felshieldward_AI(go);
    }
};

/* Felsoul Obliterator 101695 */
class npc_felsoul_obliterator_101695 : public CreatureScript
{
public:
    npc_felsoul_obliterator_101695() : CreatureScript("npc_felsoul_obliterator_101695") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_felsoul_obliterator_101695_AI(creature);
    }

    enum eData {
        SPELL_DEVASTATOR_BOMBARDMENT = 191669,
        SPELL_CHAOS_BOMB = 205726,
        AREA_FELSOUL_HOLD = 7768,
    };

    struct npc_felsoul_obliterator_101695_AI : public ScriptedAI
    {
        npc_felsoul_obliterator_101695_AI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
            me->setActive(true);
        }

        uint32 timer = 1000;

        void UpdateAI(uint32 diff) override
        {
            if (timer <= diff)
            {
                Position pos = me->GetPosition();
                me->GetMap()->LoadGrid(pos.GetPositionX(), pos.GetPositionY());
                Map::PlayerList const& players = me->GetMap()->GetPlayers();
                for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                {
                    if (Player* player = itr->GetSource())
                        if (player->GetAreaId() == AREA_FELSOUL_HOLD &&
                            player->GetPosition().m_positionX >= 1038.0f && player->GetPosition().m_positionX <= 1199.0f &&
                            player->GetPosition().m_positionY >= 4984.0f && player->GetPosition().m_positionY <= 5141.0f)
                            me->CastSpell(player, SPELL_CHAOS_BOMB, true);
                }
                timer = urand(12000, 14000);
            }
            else
                timer -= diff;
        }
    };
};

/* Fel Commander Igrius 95285 */
class npc_fel_commander_igrius_95285 : public CreatureScript
{
public:
    npc_fel_commander_igrius_95285() : CreatureScript("npc_fel_commander_igrius_95285") { }

    enum eIgrius
    {
        EVENT_FEL_WINDS = 1,
        EVENT_FEL_SPIKES = 2,
        EVENT_ARCING_SMASH = 3,
        SPELL_FEL_WINDS = 193908,
        SPELL_FEL_SPIKES = 199094,
        SPELL_ARCING_SMASH = 205817,
    };

    struct npc_fel_commander_igrius_95285_AI : public ScriptedAI
    {
        npc_fel_commander_igrius_95285_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            instance = me->GetInstanceScript();
            _firstTextTrigger = false;
            _felSpikesTrigger = false;
        }

        void Reset() override
        {
            _events.Reset();
            Initialize();
        }

        void EnterCombat(Unit* /*who*/) override
        {
            _events.ScheduleEvent(EVENT_FEL_WINDS, 5000);
            _events.ScheduleEvent(EVENT_ARCING_SMASH, urand(3000, 4000));
            Talk(4); // You have gone far enough, mortal.This ends here.
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (HealthBelowPct(60) && !_firstTextTrigger) {
                Talk(5); // Your life is forfeit!
                _firstTextTrigger = true;
            }

            if (HealthBelowPct(27) && !_felSpikesTrigger) {
                Talk(1); // DIE!
                _events.ScheduleEvent(EVENT_FEL_SPIKES, 1000);
                _felSpikesTrigger = true;
            }
        }

        void JustDied(Unit* /*killer*/) override
        {
            Talk(6); // Master... I have... failed...
            instance->DoKilledMonsterKredit(0, me->GetEntry());
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_FEL_WINDS:
                    DoCastVictim(SPELL_FEL_WINDS);
                    break;
                case EVENT_ARCING_SMASH:
                    DoCastVictim(SPELL_ARCING_SMASH);
                    _events.ScheduleEvent(EVENT_ARCING_SMASH, 12000);
                    break;
                case EVENT_FEL_SPIKES:
                    DoCastVictim(SPELL_FEL_SPIKES);
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
        bool _firstTextTrigger;
        bool _felSpikesTrigger;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_fel_commander_igrius_95285_AI(creature);
    }
};

/* Varedis Felsoul 94836 */
class npc_varedis_felsoul_94836 : public CreatureScript
{
public:
    npc_varedis_felsoul_94836() : CreatureScript("npc_varedis_felsoul_94836") { }

    enum eVaredis
    {
        SPELL_DEMONS_BITE = 190226,
        SPELL_EYE_BEAM = 190231,
        SPELL_CHAOS_NOVA = 190246,
        SPELL_EMPOWERED_CHAOS_NOVA = 218930,
        SPELL_FEL_PORTAL = 219124, // 241648,
        SPELL_TWINBLADES = 218933,
        SPELL_FEL_ERUPTION = 218621, // 197217
        EVENT_DEMONS_BITE = 1,
        EVENT_EYE_BEAM = 2,
        EVENT_CHAOS_NOVA = 3,
        EVENT_EMPOWERED_CHAOS_NOVA = 4,
        EVENT_RESTORE_COMBAT = 5,
        EVENT_THROW_WARBLADES = 6,
        EVENT_MOVE_MARDUM = 7,
    };

    struct npc_varedis_felsoul_94836_AI : public ScriptedAI
    {
        npc_varedis_felsoul_94836_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            instance = me->GetInstanceScript();
            _firstTextTrigger = false;
            _secondTextTrigger = false;
            _thirdTextTrigger = false;
            _firstConversationTrigger = false;
            _secondConversationTrigger = false;
            _sayGreeting = false;
        }

        void Reset() override
        {
            _events.Reset();
            Initialize();
        }

        void EnterCombat(Unit* /*who*/) override
        {
            Talk(2); // Join me! Unleash your true power. Do not let the weak hold you back!
            _events.ScheduleEvent(EVENT_DEMONS_BITE, 4000);
            _events.ScheduleEvent(EVENT_EYE_BEAM, 18000);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (HealthBelowPct(80) && !_firstTextTrigger) {
                Talk(3); // Behold the might of the Deceiver! Behold the glory of the demon within!
                _firstTextTrigger = true;
            }

            if (HealthBelowPct(65) && !_secondTextTrigger) {
                Talk(4); // I am a GOD! KNEEL BEFORE ME!
                _secondTextTrigger = true;
            }

            if (HealthBelowPct(50) && !_thirdTextTrigger) {
                Talk(5); // I am through with this charade! Your soul will feed the Twinblades.
                _thirdTextTrigger = true;
            }

            if (HealthBelowPct(25) && !_firstConversationTrigger) {
                _events.ScheduleEvent(EVENT_CHAOS_NOVA, 1000);
                _firstConversationTrigger = true;
            }

            if (HealthBelowPct(6) && !_secondConversationTrigger) {
                _events.ScheduleEvent(EVENT_EMPOWERED_CHAOS_NOVA, 1000);
                _secondConversationTrigger = true;
            }
        }

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_GET_BRIDGE:
                // Moved out from UpdateAI
                me->GetScheduler().Schedule(Seconds(2), [this](TaskContext context)
                {
                    Player* player = me->SelectNearestPlayer(500.0f);
                    Talk(0, player); // Behold the infinite power of the Twinblades!
                    me->CastSpell(me, SPELL_FEL_ERUPTION, true);
                }).Schedule(Seconds(8), [this](TaskContext context)
                {
                    me->SummonGameObject(243468, Position(987.344f, 4869.25f, 31.0751f, 5.95153f), QuaternionData(-0.0f, -0.0f, -0.0f, 1.0f), 900); // Bridge
                    Player* player = me->SelectNearestPlayer(500.0f);
                    Talk(1, player); // So, Illidari, you seek my head, that you might take the Twinblades as your own?
                }).Schedule(Seconds(10), [this](TaskContext context)
                {
                    me->GetMotionMaster()->MoveJump({ 960.845f, 4811.054f, 34.4906f, 1.09558f }, 15.9f, 15.9f, 1, true);
                    me->HandleEmoteCommand(EMOTE_STATE_READY2H_ALLOW_MOVEMENT);
                });
                break;
            default:
                break;
            }
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
                    case EVENT_DEMONS_BITE:
                        DoCastVictim(SPELL_DEMONS_BITE, true);
                        _events.RescheduleEvent(EVENT_DEMONS_BITE, 5000);
                        break;
                    case EVENT_EYE_BEAM:
                        DoCastVictim(SPELL_EYE_BEAM);
                        _events.RescheduleEvent(EVENT_EYE_BEAM, 16000);
                        break;
                    case EVENT_CHAOS_NOVA:
                        DoCastVictim(SPELL_CHAOS_NOVA);
                        me->AttackStop();
                        me->SetReactState(REACT_PASSIVE);
                        // Kiljaeden conversation 1
                        if (InstanceScript* l_InstanceScript = me->GetInstanceScript())
                            l_InstanceScript->DoConversation(KJ_CONVERSATION_1);
                        _events.ScheduleEvent(EVENT_RESTORE_COMBAT, 6000);
                        break;
                    case EVENT_EMPOWERED_CHAOS_NOVA:
                        DoCastVictim(SPELL_EMPOWERED_CHAOS_NOVA);
                        me->AttackStop();
                        me->SetReactState(REACT_PASSIVE);
                        // Kiljaeden conversation 2
                        if (InstanceScript* l_InstanceScript = me->GetInstanceScript())
                            l_InstanceScript->DoConversation(KJ_CONVERSATION_2);
                        _events.ScheduleEvent(EVENT_THROW_WARBLADES, 3000);
                        break;
                    case EVENT_RESTORE_COMBAT:
                        Talk(8); // Gladly, my master.
                        me->SetReactState(REACT_AGGRESSIVE);
                        break;
                    case EVENT_THROW_WARBLADES:
                        Talk(6); // I have no need for mortal armaments!
                        me->CastSpell(984.354f, 4826.77f, 34.7617f, SPELL_TWINBLADES, true);
                        me->GetMotionMaster()->MovePoint(1, 957.53f, 4801.32f, 34.835f, false);
                        _events.ScheduleEvent(EVENT_MOVE_MARDUM, 4000);
                        break;
                    case EVENT_MOVE_MARDUM:
                        Talk(7); // This is not over... Illidari.
                        instance->SetData(DATA_STAGE_4, DONE);
                        DoCast(me, SPELL_FEL_PORTAL, true);
                        me->DespawnOrUnsummon(4000);
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
        bool _firstTextTrigger;
        bool _secondTextTrigger;
        bool _thirdTextTrigger;
        bool _firstConversationTrigger;
        bool _secondConversationTrigger;
        bool _sayGreeting;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_varedis_felsoul_94836_AI(creature);
    }
};

/* Generic Bunny 54638 for Fel Spike */
class npc_fel_spike_bunny : public CreatureScript
{
public:
    npc_fel_spike_bunny() : CreatureScript("npc_fel_spike_bunny") { }

    enum eBunny {
        SPELL_FEL_SPIKE = 243163,
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_fel_spike_bunny_AI(creature);
    }

    struct npc_fel_spike_bunny_AI : public ScriptedAI
    {
        npc_fel_spike_bunny_AI(Creature* creature) : ScriptedAI(creature) { }

        bool _spikeCasted = false;

        void MoveInLineOfSight(Unit* unit) override
        {
            if (Player* player = unit->ToPlayer())
                if (player->GetDistance(me) < 40.0f && !_spikeCasted)
                {
                    me->CastSpell(me, SPELL_FEL_SPIKE, true);
                    _spikeCasted = true;
                    me->GetScheduler().Schedule(Seconds(180), [this](TaskContext context)
                    {
                        Creature* bunny = GetContextCreature();
                        bunny->RemoveAurasDueToSpell(SPELL_FEL_SPIKE);
                        bunny->DespawnOrUnsummon(1000);
                    });
                }
        }
    };
};

class go_twinblades_of_the_deceiver_251878 : public GameObjectScript
{
public:
    go_twinblades_of_the_deceiver_251878() : GameObjectScript("go_twinblades_of_the_deceiver_251878") {
        isLooted = false;
        prevState = 0;
        playerGuid = ObjectGuid::Empty;
    }

    void OnLootStateChanged(GameObject* go, uint32 state, Unit* unit)
    {
        if (state == GO_ACTIVATED && unit) {
            if (Player* player = unit->ToPlayer())
                playerGuid = player->GetGUID();
        }
        if (state == GO_JUST_DEACTIVATED && prevState == GO_ACTIVATED && playerGuid != ObjectGuid::Empty && !isLooted)
        {
            isLooted = true;
            if (Player* player = ObjectAccessor::GetPlayer(*go, playerGuid)) {
                if (!player->GetQuestObjectiveData(QUEST_THE_HUNT_ALTRUIS, 0) || !player->GetQuestObjectiveData(QUEST_THE_HUNT_KAYN, 1))
                    player->KilledMonsterCredit(TWINBLADES_KILLCREDIT);
                // TO DO: Force Artifact Equip
                if (InstanceScript * instance = go->GetInstanceScript())
                    instance->SetData(DATA_STAGE_5, DONE);

                if (Creature* npc_twinblades = go->FindNearestCreature(NPC_TWINBLADES_OF_THE_DECEIVER, go->GetVisibilityRange(), true))
                    npc_twinblades->DespawnOrUnsummon(2000);
                go->DespawnOrUnsummon(2000ms);
            }
        }
        prevState = state;
    }
    bool isLooted;
    uint32 prevState;
    ObjectGuid playerGuid;
};

Position const outPath[] =
{
    { 959.700f, 4857.300f, 35.2306f },
    { 958.793f, 4853.807f, 42.1418f },
    { 968.536f, 4847.749f, 48.2015f },
    { 977.809f, 4858.744f, 56.2919f },
    { 970.890f, 4862.689f, 64.6040f },
    { 928.861f, 4839.043f, 96.0083f },
    { 888.862f, 4831.604f, 136.0509f }
};
size_t const toDalaranPathSize = std::extent<decltype(outPath)>::value;

class npc_illidari_felbat_101902 : public CreatureScript
{
public:
    npc_illidari_felbat_101902() : CreatureScript("npc_illidari_felbat_101902") { }

    enum eFelBal {
        EVENT_START_PATH = 1,
        EVENT_TELEPORT = 2,
        SPELL_RIDE_VEHICLE_HARD_CODED = 46598,
    };

    struct npc_illidari_felbat_101902_AI : public VehicleAI
    {
        npc_illidari_felbat_101902_AI(Creature* creature) : VehicleAI(creature) { }

        void Reset() override
        {
            _events.Reset();
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
            if (type == EFFECT_MOTION_TYPE && pointId == toDalaranPathSize)
                _events.ScheduleEvent(EVENT_TELEPORT, 300);
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_PATH:
                    me->GetMotionMaster()->MoveSmoothPath(uint32(toDalaranPathSize), outPath, toDalaranPathSize, false, true);
                    break;
                case EVENT_TELEPORT:
                    me->RemoveAllAuras();
                    if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID)) {
                        player->TeleportTo(1220, Position(-839.796f, 4259.4711f, 746.2744f, 1.207325f));
                    }
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
        return new npc_illidari_felbat_101902_AI(creature);
    }
};

/* AOI Bunny 95899 */
class npc_suramar_first_AOIbunny : public CreatureScript
{
public:
    npc_suramar_first_AOIbunny() : CreatureScript("npc_suramar_first_AOIbunny") { }

    struct npc_suramar_first_AOIbunny_AI : public ScriptedAI
    {
        npc_suramar_first_AOIbunny_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            instance = me->GetInstanceScript();
        }

        void Reset() override
        {
            Initialize();
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (!who || !who->IsInWorld() || !me->IsWithinDist(who, 15.0f, false))
                return;

            Player* player = who->ToPlayer();

            if (!player)
                return;

            if (instance->GetData(DATA_STAGE_3) == NOT_STARTED && !_actionStarted)
            {
                _actionStarted = true;
                instance->DoDelayedConversation(1000, IGRIUS_CONV_2);
            }
        }

    private:
        InstanceScript * instance;
        bool _actionStarted;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_suramar_first_AOIbunny_AI(creature);
    }
};

/* AOI Bunny 95899 */
class npc_suramar_second_AOIbunny : public CreatureScript
{
public:
    npc_suramar_second_AOIbunny() : CreatureScript("npc_suramar_second_AOIbunny") { }

    struct npc_suramar_second_AOIbunny_AI : public ScriptedAI
    {
        npc_suramar_second_AOIbunny_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            instance = me->GetInstanceScript();
        }

        void Reset() override
        {
            Initialize();
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (!who || !who->IsInWorld() || !me->IsWithinDist(who, 15.0f, false))
                return;

            Player* player = who->ToPlayer();

            if (!player)
                return;

            if (instance->GetData(DATA_STAGE_3) == NOT_STARTED && !_actionStarted)
            {
                _actionStarted = true;
                instance->DoDelayedConversation(1000, IGRIUS_CONV_3);
                // Move Moargs closer to the first Felshield Ward
                SummonBerserkers();
            }
        }

        void SummonBerserkers()
        {
            std::list<Creature*> felsoulBerserkers;
            felsoulBerserkers = me->FindNearestCreatures(NPC_FELSOUL_BERSERKER, 30.0f);
            for (std::list<Creature*>::const_iterator itr = felsoulBerserkers.begin(); itr != felsoulBerserkers.end(); ++itr)
                if (Creature* berserker = (*itr)->ToCreature())
                    berserker->GetScheduler().Schedule(Seconds(1), [berserker](TaskContext context) {
                        if (Creature* nearFleshcarver = berserker->FindNearestCreature(95329, berserker->GetVisibilityRange(), true))
                            berserker->GetMotionMaster()->MoveCloserAndStop(1, nearFleshcarver, 15.0f); // MovePoint(1, 1045.68f, 5121.78f, 57.57029f);
                    });
        }

    private:
        InstanceScript * instance;
        bool _actionStarted;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_suramar_second_AOIbunny_AI(creature);
    }
};
/* Demon Hunter (Havoc) Artifact Acquisition Scripts END */

/* Warlock (Demonology) Artifact Acquisition Scripts */
// 210920 - Teleport to Felsoul Hold
class spell_teleport_felsoul_hold : public SpellScript
{
    PrepareSpellScript(spell_teleport_felsoul_hold);

    void HandleOnCast()
    {
        if (Player* player = GetCaster()->ToPlayer())
        {
            WorldLocation location(1498, 1267.38f, 5239.71f, 93.5321f, 1.47446f);
            player->TeleportTo(location);
            player->KilledMonsterCredit(106033);
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_teleport_felsoul_hold::HandleOnCast);
    }
};

/* Mephistroth 106811 (Bunny to summon 3 waves and generals ) */
class npc_mephistroth_106811 : public CreatureScript
{
public:
    npc_mephistroth_106811() : CreatureScript("npc_mephistroth_106811") { }

    enum eMephi
    {
        EVENT_SUMMON_SOULWRATH = 1,
        DATA_CANCEL_WAVE = 59,
    };

    struct npc_mephistroth_106811_AI : public ScriptedAI
    {
        npc_mephistroth_106811_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            instance = me->GetInstanceScript();
            waveStarted = false;
            creaturesSpawned = 0;
        }

        void Reset() override
        {
            _events.Reset();
            Initialize();
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (!who || !who->IsInWorld() || !me->IsWithinDist(who, 25.0f, false))
                return;

            Player* player = who->GetCharmerOrOwnerPlayerOrPlayerItself();
            if (!player)
                return;
            if (instance->GetData(DATA_STAGE_2) == NOT_STARTED && !waveStarted)
            {
                waveStarted = true;
                _events.ScheduleEvent(EVENT_SUMMON_SOULWRATH, 500);
            }
        }

        void SetData(uint32 id, uint32 /*value*/) override
        {
            switch (id)
            {
            case DATA_CANCEL_WAVE:
                _events.CancelEvent(EVENT_SUMMON_SOULWRATH);
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
                case EVENT_SUMMON_SOULWRATH:
                    if (creaturesSpawned == 8) {
                        _events.CancelEvent(EVENT_SUMMON_SOULWRATH);
                        break;
                    }
                    // dreadguard sentry + eredar soul binder
                    // wrathguard hellblade and Fel mongrel
                    // eredar soul binder + eredar soul binder + fel mongrel
                    // tyrana and nikta

                    if (TempSummon* soulwrath = me->SummonCreature(105000, me->GetPosition(), TEMPSUMMON_DEAD_DESPAWN, 20000, 0, true))
                    {
                        float x, y, z;
                        soulwrath->GetClosePoint(x, y, z, soulwrath->GetObjectSize() / 3, 25.0f);
                        soulwrath->GetMotionMaster()->MovePoint(0, x, y, z);
                        soulwrath->SetReactState(REACT_AGGRESSIVE);
                    }
                    ++creaturesSpawned;
                    _events.ScheduleEvent(EVENT_SUMMON_SOULWRATH, 8000);
                    break;
                default:
                    break;
                }
            }
        }

    private:
        EventMap _events;
        InstanceScript * instance;
        bool waveStarted;
        uint32 creaturesSpawned;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_mephistroth_106811_AI(creature);
    }
};

/* Mephistroth 106692 (Bunny to summon overfiend) */
class npc_mephistroth_106692 : public CreatureScript
{
public:
    npc_mephistroth_106692() : CreatureScript("npc_mephistroth_106692") { }

    enum eMephi
    {
        EVENT_START_ACTION = 1,
        EVENT_CONTINUE_TALK = 2,
        EVENT_SUMMON_OVERFIEND = 3,
    };

    struct npc_mephistroth_106692_AI : public ScriptedAI
    {
        npc_mephistroth_106692_AI(Creature* creature) : ScriptedAI(creature) {
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

        void SetData(uint32 id, uint32 /*value*/) override
        {
            if (id == 1515)
                _events.ScheduleEvent(EVENT_START_ACTION, 1000);
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
                case EVENT_START_ACTION:
                    Talk(0); // Foolish warlock! Did you really think I would remain unaware of your infantile plot to steal my treasure? You underestimate the Nathrezim!
                    _events.ScheduleEvent(EVENT_CONTINUE_TALK, 8000);
                    break;
                case EVENT_CONTINUE_TALK:
                    Talk(1); // As for you, treacherous skull. I''ll deal with you later.
                    _events.ScheduleEvent(EVENT_SUMMON_OVERFIEND, 4000);
                    break;
                case EVENT_SUMMON_OVERFIEND:
                    instance->SetData(DATA_STAGE_1, DONE);
                    me->CastSpell(me, 211701, true);
                    break;
                default:
                    break;
                }
            }
        }

    private:
        EventMap _events;
        InstanceScript *instance;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_mephistroth_106692_AI(creature);
    }
};

/* Mephistroth 106652 (Battle Target before artifact summon) */
class npc_mephistroth_106652 : public CreatureScript
{
public:
    npc_mephistroth_106652() : CreatureScript("npc_mephistroth_106652") { }

    enum eMephistroth
    {
        SPELL_MIND_BLAST = 196944,
        EVENT_MIND_BLAST = 1,
        EVENT_ESCAPE = 2,
        EVENT_DESPAWN = 3,
    };

    struct npc_mephistroth_106652_AI : public ScriptedAI
    {
        npc_mephistroth_106652_AI(Creature* creature) : ScriptedAI(creature) {
            Initialize();
        }

        void Initialize()
        {
            instance = me->GetInstanceScript();
            _firstTextTrigger = false;
        }

        void Reset() override
        {
            _events.Reset();
            Initialize();
        }

        void EnterCombat(Unit* /*who*/) override
        {
            Talk(0); // I grow tired of your interference! DIE!
            _events.ScheduleEvent(EVENT_MIND_BLAST, 1000);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (HealthBelowPct(8) && !_firstTextTrigger) {
                _events.ScheduleEvent(EVENT_ESCAPE, 1000);
                _firstTextTrigger = true;
            }
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
                case EVENT_MIND_BLAST:
                    DoCastVictim(SPELL_MIND_BLAST, true);
                    _events.RescheduleEvent(EVENT_MIND_BLAST, 5000);
                    break;
                case EVENT_ESCAPE:
                    me->AttackStop();
                    me->SetReactState(REACT_PASSIVE);
                    Talk(1); // Enjoy your victory while you can, warlock. This isn't over between us. It has only begun!
                    _events.ScheduleEvent(EVENT_DESPAWN, 6000);
                    break;
                case EVENT_DESPAWN:
                    me->DespawnOrUnsummon();
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
        bool _firstTextTrigger;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_mephistroth_106652_AI(creature);
    }
};

class go_skull_of_the_manari_249821 : public GameObjectScript
{
public:
    go_skull_of_the_manari_249821() : GameObjectScript("go_skull_of_the_manari_249821") {
        isLooted = false;
        prevState = 0;
        playerGuid = ObjectGuid::Empty;
    }

    void OnLootStateChanged(GameObject* go, uint32 state, Unit* unit)
    {
        if (state == GO_ACTIVATED && unit) {
            if (Player* player = unit->ToPlayer())
                playerGuid = player->GetGUID();
        }
        if (state == GO_JUST_DEACTIVATED && prevState == GO_ACTIVATED && playerGuid != ObjectGuid::Empty && !isLooted)
        {
            isLooted = true;
            if (Player* player = ObjectAccessor::GetPlayer(*go, playerGuid)) {
                if (!player->GetQuestObjectiveData(QUEST_DARK_WHISPERS, 1))
                    player->KilledMonsterCredit(KILLCREDIT_OBTAIN_SKULL_OF_MANARI); // Obtain the Skull of the Manari
                // TO DO: Force Artifact Equip
                if (InstanceScript * instance = go->GetInstanceScript())
                    instance->SetData(DATA_STAGE_6, DONE);

                if (Creature* npc_skull_manari = go->FindNearestCreature(NPC_THALKIEL_SKULL_OF_THE_MANARI, go->GetVisibilityRange(), true))
                    npc_skull_manari->DespawnOrUnsummon(2000);
                go->DespawnOrUnsummon(2000ms);
            }
        }
        prevState = state;
    }
    bool isLooted;
    uint32 prevState;
    ObjectGuid playerGuid;
};
/* Warlock (Demonology) Artifact Acquisition Scripts END */

/*********/
/* AddSC */
/*********/
void AddSC_scenario_artifact_suramar_acquisition()
{
	RegisterInstanceScript(scenario_artifact_suramar_acquisition, 1498);

    /* DH Havoc */
    new scene_camp_explosion();
    new go_first_felshieldward();
    new go_second_felshieldward();
    new go_third_felshieldward();
    new npc_felsoul_obliterator_101695();
    new npc_fel_commander_igrius_95285();
    new npc_varedis_felsoul_94836();
    new npc_fel_spike_bunny();
    new go_twinblades_of_the_deceiver_251878();
    new npc_illidari_felbat_101902();
    new npc_suramar_first_AOIbunny();
    new npc_suramar_second_AOIbunny();
    new scene_varedis_reveal();
    new scene_twinblades_looted();
    /* DH Havoc END */
    /* Warl Demo */
    new npc_mephistroth_106811();
    new npc_mephistroth_106692();
    new npc_mephistroth_106652();
    RegisterSpellScript(spell_teleport_felsoul_hold);
    new go_skull_of_the_manari_249821();
    /* Warl Demo END */
}
