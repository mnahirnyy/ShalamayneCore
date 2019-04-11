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
// class spell_fate_of_the_horde : public SpellScript
// {
//     PrepareSpellScript(spell_fate_of_the_horde);

//     enum
//     {
//         MOVIE_FATE_OF_THE_HORDE = 474,
//         SPELL_TELE_TO_DUROTAR_FUNERAL = 200282,
//         SPELL_LEARN_FATE_OF_THE_HORDE = 198893,
//     };

//     void HandleOnCast()
//     {
//         if (Player* player = GetCaster()->ToPlayer())
//         {
//             player->AddMovieDelayedAction(MOVIE_FATE_OF_THE_HORDE, [player]
//             {
//                 player->CastSpell(player, SPELL_LEARN_FATE_OF_THE_HORDE, true);
//                 player->CastSpell(player, SPELL_TELE_TO_DUROTAR_FUNERAL, true);
//             });

//             player->GetScheduler().Schedule(Seconds(2), [](TaskContext context)
//             {
//                 GetContextUnit()->RemoveAurasDueToSpell(192140); // Remove black screen
//             });
//         }
//     }

//     void Register() override
//     {
//         OnCast += SpellCastFn(spell_fate_of_the_horde::HandleOnCast);
//     }
// };

void AddSC_orgrimmar()
{
	new play_fate_of_the_horde();
}
