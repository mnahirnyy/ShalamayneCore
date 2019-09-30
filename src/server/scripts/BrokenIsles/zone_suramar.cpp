/*
* Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>
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

enum SPELLS
{
    QUEST_MASQUERADE = 42079,
    LEARN_MASQUERADE = 211086,
    SPELL_MASQUERADE = 211135,
};
// Quest wowhead.com/quest=42079/masquerade
class Player_Spell_Masquerade : public PlayerScript
{

public:
    Player_Spell_Masquerade() : PlayerScript("Player_Spell_Masquerade") { }

    void OnLogin(Player* player, bool /*firstLogin*/)
    {       
        UseSpellMasquerade(player, player->GetAreaId(), true);
    }

    void OnUpdateArea(Player* player, Area* newArea, Area* /*oldArea*/) override
    {
        UseSpellMasquerade(player, newArea->GetId(), false);
    }

    void UseSpellMasquerade(Player* player, uint32 area, bool trigger)
    {        
        switch (area)
        {
        case 8149: ///A??a????
        case 8148: ///EOA­Ae?C
        case 8150: ///E??CI?O?
        case 7963: ///?o??µA
        case 8351: ///¶?IiO°
        case 8352: ///EOOAE?µA??N?
        case 8353: ///AuOE?a??
        case 8355: ///OOI«?oIu
        case 8378: ///OAO«AeI·
        case 8379: ///oI????E?
        case 8380: ///IcO?I?O?
        case 8381: ///±¦E???O°
        case 8386: ///O?O°»?O°
        case 8385: ///OAOA??E?
        case 8384: ///??NyO®?i
        case 8383: ///?¤???oµA
        case 8382: ///??OA???Y
        case 8395: ///°?E?E?I??U
        case 8397: ///?oµI??I?
        case 8398: ///UIAi??I?
        case 8431: ///OE?o?oµi
        case 8436: ///EOAa?«O°
        case 8441: ///OA?a?¤µI
        case 8434: ///»??CO???IY
        case 8345: ///E?I?°AEoE¦µA??O°
        case 8461: ///?oµIE?µi
        case 8487: ///OAOA??I?
        case 8496: ///EOA­AeIa
            //if (!player->HasAura(LEARN_MASQUERADE) ||)
            //    return;
            //if (player->GetQuestStatus(QUEST_MASQUERADE) != QUEST_STATUS_REWARDED)
            //    return;
            if(trigger)
                player->RemoveAurasDueToSpell(SPELL_MASQUERADE);
            if (!player->HasAura(SPELL_MASQUERADE))
                player->CastSpell(player, SPELL_MASQUERADE, true);
            player->GetQuestObjectiveCriteriaMgr();
            return;
            break;
        default:
            return;
            break;
        }
    }
};

void AddSC_suramar()
{
    new Player_Spell_Masquerade();
}
