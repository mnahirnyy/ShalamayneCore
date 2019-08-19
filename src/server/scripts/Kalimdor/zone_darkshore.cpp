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

#include "ScriptMgr.h"
#include "ObjectAccessor.h"
#include "CellImpl.h"
#include "GridNotifiersImpl.h"

 /*########
 ## Quest: Bearer of Good Fortune
 ########*/

enum CliffspringAnimalCage
{
    QUEST_BEARER_OF_GOOD_FORTUNE = 13557,
    NPC_UNCORRUPTED_DUSKRAT = 33023,
    NPC_UNCORRUPTED_THISTLE_BEAR = 33024,
    GO_SECURE_DUSKRAT_CAGE = 194133,
    GO_SECURE_BEAR_CAGE = 194124,
    POINT_INIT = 1,
    EVENT_DESPAWN = 1,
};

class npc_uncorrupted_animal : public CreatureScript
{
public:
    npc_uncorrupted_animal() : CreatureScript("npc_uncorrupted_animal") { }

    struct npc_uncorrupted_animalAI : public ScriptedAI
    {
        npc_uncorrupted_animalAI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
        }

        void Initialize()
        {
            _playerGUID.Clear();
            _movementComplete = false;
        }

        void Reset() override
        {
            if (GameObject* cage = me->FindNearestGameObject(GO_SECURE_DUSKRAT_CAGE, 5.0f))
            {
                cage->SetLootState(GO_JUST_DEACTIVATED);
                cage->SetGoState(GO_STATE_READY);
            }
            if (GameObject* cage = me->FindNearestGameObject(GO_SECURE_BEAR_CAGE, 5.0f))
            {
                cage->SetLootState(GO_JUST_DEACTIVATED);
                cage->SetGoState(GO_STATE_READY);
            }
            _events.Reset();
            Initialize();
        }

        void StartMoving(Player* owner)
        {
            if (owner)
            {   
                _playerGUID = owner->GetGUID();
            }
            Position pos = me->GetNearPosition(3.0f, 0.0f);
            me->GetMotionMaster()->MovePoint(POINT_INIT, pos);
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type != POINT_MOTION_TYPE || id != POINT_INIT)
                return;

            if (Player* _player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                _player->KilledMonsterCredit(NPC_UNCORRUPTED_THISTLE_BEAR, ObjectGuid::Empty);

            _movementComplete = true;
            _events.ScheduleEvent(EVENT_DESPAWN, 3500);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!_movementComplete)
                return;

            _events.Update(diff);

            if (_events.ExecuteEvent() == EVENT_DESPAWN)
                me->DespawnOrUnsummon();
        }

    private:
        ObjectGuid _playerGUID;
        EventMap _events;
        bool _movementComplete;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_uncorrupted_animalAI(creature);
    }
};

class go_secure_animal_cage : public GameObjectScript
{
public:
    go_secure_animal_cage() : GameObjectScript("go_secure_animal_cage") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->SetGoState(GO_STATE_READY);
        if (player->GetQuestStatus(QUEST_BEARER_OF_GOOD_FORTUNE) == QUEST_STATUS_INCOMPLETE)
        {
            if (Creature* uncorrupted_bear = go->FindNearestCreature(NPC_UNCORRUPTED_THISTLE_BEAR, 5.0f, true))
            {
                go->ResetDoorOrButton();
                ENSURE_AI(npc_uncorrupted_animal::npc_uncorrupted_animalAI, uncorrupted_bear->AI())->StartMoving(player);
                return false;
            }
            if (Creature* uncorrupted_duskrat = go->FindNearestCreature(NPC_UNCORRUPTED_DUSKRAT, 5.0f, true))
            {
                go->ResetDoorOrButton();
                ENSURE_AI(npc_uncorrupted_animal::npc_uncorrupted_animalAI, uncorrupted_duskrat->AI())->StartMoving(player);
                return false;
            }
        }
        return true;
    }
};

/*######
## AddSC
######*/
void AddSC_darkshore()
{
    new npc_uncorrupted_animal();
    new go_secure_animal_cage();
}
