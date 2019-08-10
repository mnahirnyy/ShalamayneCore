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
#include "Player.h"
#include "SpellMgr.h"

class scene_jewelcrafting_game : public SceneScript
{
    public:
        scene_jewelcrafting_game() : SceneScript("scene_jewelcrafting_game") { }

    // Called when a player receive trigger from scene
    void OnSceneTriggerEvent(Player* player, uint32 /*sceneInstanceID*/, SceneTemplate const* /*sceneTemplate*/, std::string const& triggerName) override
    {
		if(player)
			if (triggerName == "achievement")
				player->CompletedAchievement(10587);
    }
};

void AddSC_legion_profession_jewelcrafting()
{
	new scene_jewelcrafting_game();
}
