-- Core/Scripts: Fixed Crok event not starting, Fixed Svalna entering in combat with people ouside of room
UPDATE `creature_template` SET `unit_flags`=512 WHERE `entry`=37129; -- Crok
UPDATE `creature_addon` SET `auras`=70203 WHERE `guid`=137753; -- Svalna
-- Core/Scripts: Fixed issues in Gal'darah fight
UPDATE `creature_template` SET `unit_flags`=33587200, `unit_flags2`=2080 WHERE `entry`=29791; -- Fixed flags of Rhino Spirit

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_gal_darah_stampede_charge';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (59823, 'spell_gal_darah_stampede_charge');

-- Core/Ruby Sanctum: Improved General Zarithrian encounter
-- East
DELETE FROM `script_spline_chain_meta` WHERE `entry`=39814 AND `chainId`=1;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(39814, 1, 0, 2314, 0);
DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=39814 AND `chainId`=1;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(39814, 1, 0, 0, 3062.4450, 613.99300, 84.232710),
(39814, 1, 0, 1, 3058.9580, 610.40010, 85.552370),
(39814, 1, 0, 2, 3055.7080, 606.65010, 86.302370),
(39814, 1, 0, 3, 3046.2080, 596.15010, 86.552370),
(39814, 1, 0, 4, 3043.7080, 593.15010, 87.302370),
(39814, 1, 0, 5, 3040.2080, 589.65010, 88.052370),
(39814, 1, 0, 6, 3034.4580, 583.15010, 88.802370),
(39814, 1, 0, 7, 3014.9700, 561.80730, 88.872020);
 -- West
DELETE FROM `script_spline_chain_meta` WHERE `entry`=39814 AND `chainId`=2;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(39814, 2, 0, 3486, 0);
DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=39814 AND `chainId`=2;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(39814, 2, 0, 0, 3047.4820, 454.40800, 84.374650),
(39814, 2, 0, 1, 3045.4070, 456.82900, 85.912670),
(39814, 2, 0, 2, 3043.6570, 458.57900, 86.912670),
(39814, 2, 0, 3, 3042.4070, 460.07900, 87.412670),
(39814, 2, 0, 4, 3041.6570, 460.57900, 87.662670),
(39814, 2, 0, 5, 3039.1570, 462.07900, 88.412670),
(39814, 2, 0, 6, 3037.9070, 462.82900, 88.662670),
(39814, 2, 0, 7, 3037.9070, 463.82900, 88.912670),
(39814, 2, 0, 8, 3037.9070, 464.82900, 89.162670),
(39814, 2, 0, 9, 3037.9070, 466.82900, 89.162670),
(39814, 2, 0, 10, 3033.4070, 469.07900, 89.412670),
(39814, 2, 0, 11, 3027.1570, 475.32900, 89.412670),
(39814, 2, 0, 12, 3025.1570, 477.32900, 89.412670),
(39814, 2, 0, 13, 3016.9070, 481.32900, 89.662670),
(39814, 2, 0, 14, 3014.9070, 483.32900, 89.662670),
(39814, 2, 0, 15, 3008.6570, 500.07900, 89.662670),
(39814, 2, 0, 16, 3003.8320, 501.25000, 89.450690);

-- DB/GameObject: Fel Reaver Control Console
SET @OGUID := 6570; -- 3 unused set by TC TEAM
DELETE FROM `gameobject` WHERE `id` IN (185059, 185060, 185061);
DELETE FROM `gameobject` WHERE `guid` IN (6570, 6571, 6572);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES 
(@OGUID+0, 185059, 530, 3520, 3943, '0', 0, -2668.99, 2698.53, 102.662, 2.69388, 0, 0, 0.975048, 0.221992, 300, 0, 1, 0),
(@OGUID+1, 185060, 530, 3520, 3943, '0', 0, -2671, 2694.73, 102.581, 2.57921, 0, 0, 0.960726, 0.2775, 300, 0, 1, 0),
(@OGUID+2, 185061, 530, 3520, 3943, '0', 0, -2672.43, 2691.78, 102.398, 2.5635, 0, 0, 0.958516, 0.285037, 300, 0, 1, 0);

-- DB/Quest: Take No Chances
UPDATE `gameobject_template` SET `Data0`=1505 WHERE `entry`=188112;
DELETE FROM `gameobject_template` WHERE `entry`=300184;
DELETE FROM `gameobject` WHERE `id`=300184;
SET @ENTRY := 26161;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY*100 AND `source_type`=9;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,8,0,100,1,46574,0,0,0,80,@ENTRY*100,0,0,0,0,0,1,0,0,0,0,0,0,0,"Farshire Grain Credit - On Spellhit 'Burn Grain' - Action list"),
(@ENTRY*100,9,0,0,0,0,100,0,0,0,0,0,33,26161,0,0,0,0,0,7,0,0,0,0,0,0,0,"Farshire Grain Credit - Action list - Quest Credit 'Take No Chances'"),
(@ENTRY*100,9,1,0,0,0,100,0,5000,5000,0,0,99,3,0,0,0,0,0,20,188112,10,0,0,0,0,0,"Farshire Grain Credit - Action list - Set loot state to Despawn gob"),
(@ENTRY*100,9,2,0,0,0,100,0,0,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Farshire Grain Credit - Action list - Despawn");

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=46574;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(13, 3, 46574, 0, 0, 31, 0, 3, 26161, 0, 0, 0, 0, '', 'Spell effect on Farshire Grain Credit');

-- DB/Quest: Battle Before The Citadel - Phasing
DELETE FROM `spell_area` WHERE `quest_start` IN (13861, 13862, 13863, 13864) AND `area`=4522;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `flags`, `quest_start_status`, `quest_end_status`) VALUES 
(64576, 4522, 13864, 13864, 0, 0, 2, 1, 74, 11),
(64576, 4522, 13861, 13861, 0, 0, 2, 1, 74, 11),
(64576, 4522, 13862, 13862, 0, 0, 2, 1, 74, 11),
(64576, 4522, 13863, 13863, 0, 0, 2, 1, 74, 11);

-- At The Enemy's Gates - Phasing for Icecrown -- http://www.wowhead.com/quest=13847/at-the-enemys-gates
DELETE FROM `spell_area` WHERE `quest_start` IN (13847, 13851, 13852, 13854, 13855, 13856, 13857, 13858, 13859, 13860) AND `area`=4522;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `flags`, `quest_start_status`, `quest_end_status`) VALUES 
(64576, 4522, 13847, 13847, 0, 0, 2, 1, 74, 11),
(64576, 4522, 13851, 13851, 0, 0, 2, 1, 74, 11),
(64576, 4522, 13852, 13852, 0, 0, 2, 1, 74, 11),
(64576, 4522, 13854, 13854, 0, 0, 2, 1, 74, 11),
(64576, 4522, 13855, 13855, 0, 0, 2, 1, 74, 11),
(64576, 4522, 13856, 13856, 0, 0, 2, 1, 74, 11),
(64576, 4522, 13857, 13857, 0, 0, 2, 1, 74, 11),
(64576, 4522, 13858, 13858, 0, 0, 2, 1, 74, 11),
(64576, 4522, 13859, 13859, 0, 0, 2, 1, 74, 11),
(64576, 4522, 13860, 13860, 0, 0, 2, 1, 74, 11);

-- Condition for source Spell implicit target condition type Object entry guid
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceGroup`=1 AND `SourceEntry` IN (62727, 63438, 63439, 63440, 63441, 63442, 63443, 63444, 63445, 63446) AND `SourceId`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 62727, 0, 0, 31, 0, 3, 33238, 0, 0, 0, 0, '', 'Spell Stormwind Champion''s Pennant (effect 0) will hit the potential target of the spell if target is unit Argent Squire.'),
(13, 1, 63438, 0, 0, 31, 0, 3, 33239, 0, 0, 0, 0, '', 'Spell Silvermoon Champion''s Pennant (effect 0) will hit the potential target of the spell if target is unit Argent Gruntling.'),
(13, 1, 63439, 0, 0, 31, 0, 3, 33238, 0, 0, 0, 0, '', 'Spell Exodar Champion''s Pennant (effect 0) will hit the potential target of the spell if target is unit Argent Squire.'),
(13, 1, 63440, 0, 0, 31, 0, 3, 33238, 0, 0, 0, 0, '', 'Spell Ironforge Champion''s Pennant (effect 0) will hit the potential target of the spell if target is unit Argent Squire.'),
(13, 1, 63441, 0, 0, 31, 0, 3, 33239, 0, 0, 0, 0, '', 'Spell Undercity Champion''s Pennant (effect 0) will hit the potential target of the spell if target is unit Argent Gruntling.'),
(13, 1, 63442, 0, 0, 31, 0, 3, 33238, 0, 0, 0, 0, '', 'Spell Gnomeregan Champion''s Pennant (effect 0) will hit the potential target of the spell if target is unit Argent Squire.'),
(13, 1, 63443, 0, 0, 31, 0, 3, 33238, 0, 0, 0, 0, '', 'Spell Darnassus Champion''s Pennant (effect 0) will hit the potential target of the spell if target is unit Argent Squire.'),
(13, 1, 63444, 0, 0, 31, 0, 3, 33239, 0, 0, 0, 0, '', 'Spell Orgrimmar Champion''s Pennant (effect 0) will hit the potential target of the spell if target is unit Argent Gruntling.'),
(13, 1, 63445, 0, 0, 31, 0, 3, 33239, 0, 0, 0, 0, '', 'Spell Thunder Bluff Champion''s Pennant (effect 0) will hit the potential target of the spell if target is unit Argent Gruntling.'),
(13, 1, 63446, 0, 0, 31, 0, 3, 33239, 0, 0, 0, 0, '', 'Spell Sen''jin Champion''s Pennant (effect 0) will hit the potential target of the spell if target is unit Argent Gruntling.');

-- ==================
-- Fix quest 14386 "Leader of the Pack"
-- ==================
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_q14386_call_attack_mastiffs';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(68682, 'spell_q14386_call_attack_mastiffs');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceGroup` IN (1,4) AND `SourceEntry` IN (68682) AND `SourceId`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 68682, 0, 0, 31, 0, 3, 36312, 0, 0, 0, 0, '', 'Call Attack Mastiffs Effect 0 will hit Dark Ranger Thyala'),
(13, 4, 68682, 0, 0, 31, 1, 3, 36198, 0, 0, 0, 0, '', 'Call Attack Mastiffs Effect 2 will hit Generic Trigger LAB - Multiphase (Ground)');

UPDATE `creature` SET `spawntimesecs`=120 WHERE id=36312;
UPDATE `creature_template` SET `mingold`=4,`maxgold`=10 WHERE `entry` IN (36312);

-- Dark Ranger Thyala SAI
SET @ENTRY := 36312;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry` IN (@ENTRY);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@ENTRY) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`event_param_string`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,0,0,0,0,0,0,11,6660,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dark Ranger Thyala - On Aggro - Cast 'Shoot'"),
(@ENTRY,0,1,0,9,0,100,0,0,5,10000,10000,0,11,68683,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dark Ranger Thyala - On Range 0-5 - Cast 'Knockback'"),
(@ENTRY,0,2,0,8,0,100,0,68682,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Dark Ranger Thyala - On Spellhit - Attack Start Invoker");

-- Attack Mastiff SAI
SET @ENTRY := 36405;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry` IN (@ENTRY);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@ENTRY) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`event_param_string`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,50,1,8,25,0,0,0,11,68687,0,0,0,0,0,2,0,0,0,0,0,0,0,"Attack Mastiff - Combat - Cast 'Leap' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,5000,9000,10000,10000,0,11,26281,0,0,0,0,0,2,0,0,0,0,0,0,0,"Attack Mastiff - Combat - Cast 'Taunt'"),
(@ENTRY,0,2,0,9,0,50,0,0,3,15000,15000,0,11,15971,0,0,0,0,0,1,0,0,0,0,0,0,0,"Attack Mastiff - On Range 0-5 - Cast 'Demoralizing Roar'"),
(@ENTRY,0,4,0,60,0,100,1,200,200,0,0,0,49,0,0,0,0,0,0,10,255706,36312,0,0,0,0,0,"Attack Mastiff - Update Event - Attack Dark Ranger Thyala (No Repeat)");

-- Attack Mastiff SAI
SET @ENTRY := 36409;
UPDATE `creature_template` SET `AIName`="SmartAI", `faction`=2203 WHERE `entry` IN (@ENTRY);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@ENTRY) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`event_param_string`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,50,1,8,25,0,0,0,11,68687,0,0,0,0,0,2,0,0,0,0,0,0,0,"Attack Mastiff - Combat - Cast 'Leap' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,5000,9000,10000,10000,0,11,26281,0,0,0,0,0,2,0,0,0,0,0,0,0,"Attack Mastiff - Combat - Cast 'Taunt'"),
(@ENTRY,0,2,0,9,0,50,0,0,3,15000,15000,0,11,15971,0,0,0,0,0,1,0,0,0,0,0,0,0,"Attack Mastiff - On Range 0-5 - Cast 'Demoralizing Roar'"),
(@ENTRY,0,3,0,1,0,100,1,0,0,0,0,0,49,0,0,0,0,0,0,10,255706,36312,0,0,0,0,0,"Attack Mastiff - OOC - Attack Dark Ranger Thyala (No Repeat)");

-- Lord Godfrey SAI
SET @ENTRY := 36290;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry` IN (@ENTRY);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@ENTRY) AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (3629000) AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`event_param_string`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,20,0,100,0,14386,0,0,0,0,80,3629000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lord Godfrey - quest complete - Run Script"),
(3629000,9,0,0,0,0,100,0,0,0,0,0,0,85,68483,0,0,0,0,0,7,0,0,0,0,0,0,0,"Lord Godfrey - Script - Cast 'Phase - Quest Zone-Specific 08'"),
(3629000,9,1,0,0,0,100,0,0,0,0,0,0,28,68482,0,0,0,0,0,7,0,0,0,0,0,0,0,"Lord Godfrey - Script - Unaura 'Phase - Quest Zone-Specific 07'"),
(3629000,9,2,0,0,0,100,0,500,500,0,0,0,85,69027,0,0,0,0,0,7,0,0,0,0,0,0,0,"Lord Godfrey - Script - Cast 'Forcecast Cataclysm I'"),
(3629000,9,3,0,0,0,100,0,100,100,0,0,0,1,0,1,0,0,0,0,10,255676,36291,0,0,0,0,0,"Lord Godfrey - Script - Melinda Hammond Say 0"),
(3629000,9,4,0,0,0,100,0,0,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Lord Godfrey - Script - Say 0");

DELETE FROM `creature_text` WHERE `CreatureID` IN (36290,36291);
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `comment`) VALUES
(36290, 0, 0, 'Hold your positions, men!', 14, 0, 100, 0, 0, 0, 36632, 'Lord Godfrey'),
(36291, 0, 0, 'What''s happening?!', 12, 0, 100, 0, 0, 0, 36633, 'Melinda Hammond');

-- 471 Phases 182,183
UPDATE `creature` SET `PhaseId`=0, `PhaseGroup`=471 WHERE `guid` IN
(255676,255677,255678,255679,255680,255681);

-- ==================
-- Core/Spells: implement Mad/Crazy Alchemist's potions
-- ==================
DELETE FROM spell_script_names WHERE spell_id IN (45051, 53750);
INSERT INTO spell_script_names (spell_id, ScriptName) VALUES
(45051, 'spell_item_mad_alchemists_potion'),
(53750, 'spell_item_crazy_alchemists_potion');

-- ==================
-- DB/Creature: TEMP Remove 'Legion Gateway' creature, they are aggressive and non targetable
-- ==================
DELETE FROM `creature` WHERE `id`= 101585;

-- ==================
-- DB/Creature: Fixed number of Laughing Skull summoned on Yogg Saron
-- ==================
DELETE FROM `creature_summon_groups` WHERE `summonerId`=33890 AND `entry`=33990; -- Laughing Skull
INSERT INTO `creature_summon_groups` (`summonerId`,`summonerType`,`groupId`,`entry`,`position_x`,`position_y`,`position_z`,`orientation`,`summonType`,`summonTime`) VALUES
(33890,0,0,33990,2063.156,27.95839,244.2707,5.288348,3,60000), -- Chambers of Aspects
(33890,0,0,33990,2061.257,-53.8788,239.8633,2.478368,3,60000),
(33890,0,0,33990,2109.908,29.33236,239.8817,0.1919862,3,60000),
(33890,0,0,33990,2135.219,-41.44271,239.8027,5.846853,3,60000),
(33890,0,1,33990,1932.213,-93.62798,240.073,4.852015,3,60000), -- Icecrown Citadel
(33890,0,1,33990,1905.937,-133.1651,240.073,5.77704,3,60000),
(33890,0,1,33990,1948.668,-152.4481,240.073,1.919862,3,60000),
(33890,0,1,33990,1992.463,-131.2119,240.073,3.455752,3,60000),
(33890,0,2,33990,1917.492,91.10191,239.7496,0.5235988,3,60000), -- Stormwind Keep
(33890,0,2,33990,1918.132,73.82926,241.7929,2.600541,3,60000),
(33890,0,2,33990,1922.55,54.68001,241.1263,0.1919862,3,60000);

-- ==================
-- Core/Scripts: fix wrong uses of SetHitDamage hook.
-- ==================
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_gen_50pct_count_pct_from_max_hp' AND `spell_id`=48292;
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_dark_slash';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(48292, 'spell_dark_slash');
