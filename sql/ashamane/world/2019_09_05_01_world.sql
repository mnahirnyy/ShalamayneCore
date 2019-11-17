UPDATE `quest_template_addon` SET `PrevQuestID`=39718 WHERE `ID`=41220;
UPDATE `quest_template_addon` SET `PrevQuestID`=41220 WHERE `ID`=38834;
-- Enchanting quests
UPDATE `quest_template_addon` SET `PrevQuestID`=39874 WHERE `ID`=39875;
UPDATE `quest_template_addon` SET `PrevQuestID`=39876 WHERE `ID`=39876;
UPDATE `quest_template_addon` SET `PrevQuestID`=39876 WHERE `ID`=39877;

DELETE FROM `smart_scripts` WHERE `entryorguid`='86563';
UPDATE `creature_template` SET `AIName`='', `ScriptName`='npc_archmage_khadgar_86563' WHERE `entry`='86563';
UPDATE `gossip_menu_option` SET `OptionText`='I\'m ready. Let\'s get down to Azsuna, Khadgar.' WHERE `MenuId` = '86563';
DELETE FROM `creature_text` WHERE `CreatureID`=86563 AND `GroupID` IN (0, 1);
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(86563, 0, 0, 'Here you are. $n, over here, Azsuna awaits.', 12, 0, 100, 3, 0, 57419, 0, 0, 'Archmage Khadgar to Player'),
(86563, 1, 0, 'Let me know when you are ready, champion.', 12, 0, 100, 1, 0, 58371, 0, 0, 'Archmage Khadgar to Player');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN (15) AND `SourceGroup` IN (86563);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `sourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(15, 86563, 1, 0, 0, 9, 0, 41220, 0, 0, 0, 0, 0, '', 'Gossip Only Shows if Quest Taken');

UPDATE `creature` SET `position_x`=-833.704, `position_y`=4276.217, `position_z`=746.254, `orientation`=1.250528 WHERE `guid`=20544383;
UPDATE `creature` SET `position_x`=-813.472, `position_y`=4288.03, `position_z`=746.282, `orientation`=3.693114 WHERE `guid`=20549214;

DELETE FROM `creature` WHERE `guid`=280000404;
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `unit_flags2`, `unit_flags3`, `dynamicflags`, `ScriptName`, `VerifiedBuild`) VALUES
(280000404,93326,1220,7334,7334,0,0,0,0,-1,0,1,-78.3393,6858.93,31.0119,1.73103,300,0,0,997696768,250,0,0,0,0,0,0,'npc_archmage_khadgar_93326',25549); -- Khadgar
DELETE FROM `creature_text` WHERE `CreatureID`=93326 AND `GroupID`=1;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(93326, 1, 0, 'Hurry. The Illidari are about to be overrun.', 12, 0, 100, 25, 0, 52607, 0, 0, 'Archmage Khadgar to Player');
UPDATE `creature_template_addon` SET `auras`='84240' WHERE `entry` = 93326;
UPDATE `creature_template` SET `AIName`='', `ScriptName`='npc_archmage_khadgar_90417' WHERE `entry`='90417';
UPDATE `creature_template` SET `AIName`='', `ScriptName`='' WHERE `entry`='91827';
DELETE FROM `waypoint_data` WHERE `id`=9332600;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES
(9332600,1,-78.3393,6858.93,31.0119,0,0,0,0,100,0),
(9332600,2,-81.4901,6880,23.6468,0,0,0,0,100,0),
(9332600,3,-80.4822,6885.37,21.999,0,0,0,0,100,0),
(9332600,4,-74.7649,6899,17.9561,0,0,0,0,100,0),
(9332600,5,-73.2156,6906.45,16.512,0,0,0,0,100,0),
(9332600,6,-73.6964,6909.42,16.0559,0,0,0,0,100,0),
(9332600,7,-76.6878,6919.45,15.2145,0,0,0,0,100,0);
SET @KHADGAR := 90417;
DELETE FROM `creature_text` WHERE `CreatureID` = @KHADGAR;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(@KHADGAR, 0, 0, 'Nobody touch it! Not until our guest arrives.', 12, 0, 100, 1, 0, 67263, 101006, 0, 'Archmage Khadgar to Player'),
(@KHADGAR, 1, 0, 'Any disturbance should catalyze the sequence. Just, uh, give it a poke or something.', 12, 0, 100, 1, 0, 67264, 100058, 0, 'Archmage Khadgar to Player'),
(@KHADGAR, 2, 0, 'Be careful, champion. The land of Suramar has been wild for ten thousand years.', 12, 0, 100, 0, 0, 67271, 100062, 0, 'Archmage Khadgar to Player'),
(@KHADGAR, 3, 0, 'I have just a thing. Follow me.', 12, 0, 100, 0, 0, 64653, 0, 0, 'Archmage Khadgar to Player'),
(@KHADGAR, 4, 0, 'Hold on just a moment. I fear I\'m a bit of a pack rat.', 12, 0, 100, 0, 0, 64654, 0, 0, 'Archmage Khadgar to Player'),
(@KHADGAR, 5, 0, 'Now let\'s see... apexis crystals? No, no, those won\'t do at all.', 12, 0, 100, 0, 0, 64655, 0, 0, 'Archmage Khadgar to Player'),
(@KHADGAR, 6, 0, 'Hmm, I must\'ve put it over here.', 12, 0, 100, 25, 0, 64656, 0, 0, 'Archmage Khadgar to Player'),
(@KHADGAR, 7, 0, 'Arcane powder... soul shards... that\'s definitely not it...', 12, 0, 100, 0, 0, 64657, 0, 0, 'Archmage Khadgar to Player'),
(@KHADGAR, 8, 0, 'A-ha! Here we are... a crystallized soul. That ought to do the trick!', 12, 0, 100, 0, 0, 64658, 0, 0, 'Archmage Khadgar to Player'),
(@KHADGAR, 9, 0, 'Would you mind grabbing it? These crystals tend to have an adverse effect on non-demonic beings.', 12, 0, 100, 0, 0, 64659, 0, 0, 'Archmage Khadgar to Player'),
(@KHADGAR, 10, 0, 'Be careful, $n. You\'re tapping into magic even Illidan would have considered dangerous.', 12, 0, 100, 0, 0, 64667, 0, 0, 'Archmage Khadgar to Player'),
(@KHADGAR, 11, 0, '$n! Councilors, this is the demon hunter I spoke of.', 12, 0, 100, 0, 0, 64660, 0, 0, 'Archmage Khadgar to Player');
UPDATE `creature` SET `spawntimesecs` = '30' WHERE `guid` = '280000404';
DELETE FROM `spell_area` WHERE `area` = 7334 AND `spell` = 81004;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `quest_start_status`, `quest_end_status`) VALUES
(81004, 7334, 41220, 38834, 74, 64);
DELETE FROM `script_waypoint` WHERE `entry`=90417;
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES
(90417,1,-848.442,4638.899,749.545,0,'Archmage Khadgar for Ask And You Shall Receive'),
(90417,2,-848.171,4641.024,749.514,0,'Archmage Khadgar for Ask And You Shall Receive'),
(90417,3,-847.318,4647.033,754.076,0,'Archmage Khadgar for Ask And You Shall Receive'),
(90417,4,-846.427,4657.34,761.238,0,'Archmage Khadgar for Ask And You Shall Receive'),
(90417,5,-845.337,4665.472,767.328,0,'Archmage Khadgar for Ask And You Shall Receive'),
(90417,6,-839.465,4667.614,767.667,0,'Archmage Khadgar for Ask And You Shall Receive'),
(90417,7,-837.08,4667.586,767.702,0,'Archmage Khadgar for Ask And You Shall Receive'),
(90417,8,-836.185,4667.269,767.716,0,'Archmage Khadgar for Ask And You Shall Receive'),
(90417,9,-834.92,4666.387,767.722,0,'Archmage Khadgar for Ask And You Shall Receive'),
(90417,10,-833.79,4665.166,767.725,0,'Archmage Khadgar for Ask And You Shall Receive'),
(90417,11,-832.274,4663.507,767.761,0,'Archmage Khadgar stop in the middle'),
(90417,12,-833.934,4661.947,767.682,0,'Archmage Khadgar go to the first chest'),
(90417,13,-830.438,4658.558,767.835,0,'Archmage Khadgar go to the second chest'),
(90417,14,-829.686,4657.596,767.829,0,'Archmage Khadgar go to the second chest'),
(90417,15,-829.414,4656.686,767.816,0,'Archmage Khadgar go to the second chest'),
(90417,16,-829.319,4654.568,767.664,0,'Archmage Khadgar at the second chest'),
(90417,17,-833.367,4664.476,767.725,0,'Archmage Khadgar return to home'),
(90417,18,-840.298,4668.154,767.664,0,'Archmage Khadgar return to home'),
(90417,19,-844.087,4665.268,767.432,0,'Archmage Khadgar return to home'),
(90417,20,-846.585,4652.285,757.706,0,'Archmage Khadgar return to home'),
(90417,21,-848.133,4641.222,749.669,0,'Archmage Khadgar return to home'),
(90417,22,-848.358,4639.632,749.532,0,'Archmage Khadgar return to home');
DELETE FROM `gameobject_loot_template` WHERE `Entry`=246561;
INSERT INTO `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
(246561, 136385, 0, 100, 1, 1, 0, 1, 1, 'Crystallized Soul');
UPDATE `gameobject_template` SET `displayId`=32954, `IconName`='questinteract', `castBarCaption`='Grabbing', `Data0`=43, `Data1`=246561, `Data14`=37379, `Data30`=53993, `Data31`=1 WHERE `entry`=248521;
UPDATE `creature` SET `spawntimesecs` = '0' WHERE `guid` = '20508639' AND `id` = '90417';
DELETE FROM `gameobject_template` WHERE `entry`=251528;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `Data24`, `Data25`, `Data26`, `Data27`, `Data28`, `Data29`, `Data30`, `Data31`, `Data32`, `RequiredLevel`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES
(251528,10,27635,'Legion Communicator','questinteract','','',0.7,93,0,0,30000,0,0,0,0,0,0,0,0,0,0,27700,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,'','go_legion_communicator',22423);
UPDATE `gameobject` SET `id` = '251528' WHERE `guid` = '20406041';
DELETE FROM `creature_equip_template` WHERE `CreatureID` IN (99262, 99254, 104909);
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(99262,1,128360,0,0,128370,0,0,0,0,0,25549),
(99254,1,128360,0,0,128370,0,0,0,0,0,25549),
(104909,1,122430,0,0,0,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`='1' WHERE `id` IN ('99254', '99262', '104909');
DELETE FROM `creature_text` WHERE `CreatureID` = 99262;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(99262, 0, 0, 'Allari, report in. Have you located the Warblades?', 12, 0, 100, 1, 0, 64662, 0, 0, 'Jace Darkweaver to Player'),
(99262, 1, 0, 'We have their position. That will have to do.', 12, 0, 100, 1, 0, 64666, 0, 0, 'Jace Darkweaver to Player');
DELETE FROM `creature_text` WHERE `CreatureID` = 104909;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(104909, 0, 0, 'Yes... <garbled> Caria... <garbled> Broken Shore... <garbled> heavy resistance...', 12, 0, 100, 0, 0, 64663, 0, 0, 'Allari the Souleater to Player'),
(104909, 1, 0, 'Damn it all! INCOMING!', 12, 0, 100, 33, 0, 64664, 0, 0, 'Allari the Souleater to Player');
UPDATE `creature_template` SET `scale` = '0.85' WHERE `entry` = '104909';
UPDATE `creature_template` SET `AIName`='', `ScriptName`='npc_jace_darkweaver_99262' WHERE `entry`='99262';
UPDATE `creature_template` SET `AIName`='', `ScriptName`='npc_allari_souleater_104909' WHERE `entry`='104909';
DELETE FROM `creature_text` WHERE `CreatureID` = 99254;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(99254, 0, 0, '$n. I have an idea.', 12, 0, 100, 1, 0, 64661, 0, 0, 'Altruis to Player');
UPDATE `creature` SET `position_x`=-864.727, `position_y`=4260.450, `position_z`=745.120, `orientation`=2.93473 WHERE `guid`=20556170;
UPDATE `gameobject` SET `position_x`=-868.421, `position_y`=4261.290 WHERE `guid`=20406041;
-- The Aldrachi Warblades Artifact Scenario
UPDATE `instance_template` SET `script`='scenario_artifact_brokenshore', `parent`=0, `insideResurrection`=1 WHERE `map`=1500;
DELETE FROM `scenarios` WHERE `map` = '1500' AND `scenario_A` = '961';
INSERT INTO `scenarios` (`map`, `difficulty`, `scenario_A`, `scenario_H`) VALUES ('1500', '12', '961', '961');
-- Allari Souleater 98882
UPDATE `creature_template` SET `AIName`='', `ScriptName`='npc_allari_souleater_98882' WHERE `entry`='98882';
DELETE FROM `creature_text` WHERE `CreatureID` = 98882;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(98882, 0, 0, '$n, is that you? Finally some good news.', 14, 0, 100, 0, 0, 58226, 0, 0, 'Allari Souleater to Player'),
(98882, 1, 0, 'Caria left me for dead... the fool!', 12, 0, 100, 0, 0, 58227, 0, 0, 'Allari Souleater to Player'),
(98882, 2, 0, 'My wounds are severe. You\'ll have to push ahead alone.', 12, 0, 100, 0, 0, 58228, 0, 0, 'Allari Souleater to Player'),
(98882, 3, 0, 'I\'ll join you as soon as I\'m able.', 12, 0, 100, 0, 0, 58229, 0, 0, 'Allari Souleater to Player');
DELETE FROM `creature_equip_template` WHERE `CreatureID`=98882;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(98882,1,122430,0,0,0,0,0,0,0,0,25549),
(98882,2,0,0,0,0,0,0,0,0,0,25549);
SET @GUID := 280000405;
DELETE FROM `creature` WHERE `guid` BETWEEN @GUID+1 AND @GUID+47;
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `unit_flags2`, `unit_flags3`, `dynamicflags`, `ScriptName`, `VerifiedBuild`) VALUES
(@GUID+1,105125,1500,7796,7797,12,0,0,0,-1,0,0,-2776.7,-198.007,42.7372,0.412475,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+2,105138,1500,7796,7797,12,0,0,0,-1,0,0,-2779.4,-201.615,42.2245,0.479234,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+3,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2633.39,42.9172,43.3673,0.588264,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+5,105125,1500,7796,7797,12,0,0,0,-1,0,0,-2741.7,-159.902,48.5941,1.51518,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+6,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2624.29,35.2339,42.6158,1.15375,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+7,98891,1500,7796,7797,12,0,0,0,-1,0,0,-2819.03,-211.928,39.2151,0.544413,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+8,105138,1500,7796,7797,12,0,0,0,-1,0,0,-2818.72,-215.646,39.175,0.544413,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+11,105125,1500,7796,7797,12,0,0,0,-1,0,0,-2774.94,-202.043,42.4006,0.412475,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+12,105125,1500,7796,7797,12,0,0,0,-1,0,0,-2752.38,-182.139,46.1015,1.03687,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+13,105125,1500,7796,7797,12,0,0,0,-1,0,0,-2754.3,-179.766,46.3346,1.11148,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+14,105125,1500,7796,7797,12,0,0,0,-1,0,0,-2742.02,-165.608,47.9461,1.51518,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+15,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2632.57,40.4857,43.4871,0.941693,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+16,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2609.77,73.9158,35.7398,0.190852,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+17,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2609.57,81.7673,35.7878,6.22271,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+18,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2607.37,79.7441,35.2339,6.23449,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+19,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2607.18,75.669,35.1404,0.0887503,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+20,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2600.5,83.9686,33.7518,5.34856,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+21,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2627.05,48.9812,41.2774,1.12862,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+22,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2616.88,49.1165,39.0248,1.19538,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+23,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2619.78,44.6529,40.2464,1.15611,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+24,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2627.64,35.4816,43.1705,0.937766,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+25,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2597.53,74.1462,32.9812,0.819961,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+26,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2604.85,68.95,34.4744,0.658948,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+27,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2624.87,53.5853,40.0687,1.12469,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+28,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2594.34,82.9146,32.5172,5.84572,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+29,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2593.16,76.8109,32.1264,0.39192,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+30,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2577.3,77.858,26.7235,0.475957,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+31,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2579.34,85.7889,27.3312,5.9117,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+32,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2577.32,89.2888,26.8618,5.2504,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+33,105000,1500,7796,7797,12,0,0,0,-1,0,0,-2574.07,75.537,25.8615,0.374648,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+34,98995,1500,7796,7797,12,0,0,0,-1,0,0,-2572.93,74.152,25.5651,2.45595,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+35,98995,1500,7796,7797,12,0,0,0,-1,0,0,-2574.5,74.1077,25.9783,2.24154,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+36,98995,1500,7796,7797,12,0,0,0,-1,0,0,-2578.97,89.7792,27.2976,5.70594,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+37,98995,1500,7796,7797,12,0,0,0,-1,0,0,-2577.09,91.1646,26.8336,6.05387,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+40,98995,1500,7796,7798,12,0,0,0,-1,0,0,-2680.71,-33.3051,49.843,4.0983,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+41,98995,1500,7796,7798,12,0,0,0,-1,0,0,-2682.25,-35.4171,49.796,0.698307,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+42,98995,1500,7796,7798,12,0,0,0,-1,0,0,-2690.99,-21.124,49.6984,6.02095,900,0,0,0,0,0,0,0,0,0,0,'',26972),
(@GUID+44,98995,1500,7796,7798,12,0,0,0,-1,0,0,-2689.22,-20.6522,48.3898,1.48999,900,0,0,0,0,0,0,0,0,0,0,'',26972);
-- Aldrachi Soulwrath SAI
UPDATE `creature_template` SET `AIName`="SmartAI", `minlevel`=100, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=1 WHERE `entry`=105000;
DELETE FROM `smart_scripts` WHERE `entryorguid`=105000 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(105000,0,0,0,0,0,100,0,5000,8000,12000,15000,11,216265,0,0,0,0,0,2,0,0,0,0,0,0,0,"Aldrachi Soulwraith - In Combat - Cast 'Dark Presence'");
-- Doomherald Akvesh 98975
UPDATE `creature_template` SET `lootid`=98975, `AIName`="SmartAI", `minlevel`=101, `maxlevel`=101, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=3 WHERE `entry`=98975;
DELETE FROM `smart_scripts` WHERE `entryorguid`=98975 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(98975,0,0,0,0,0,100,0,5000,8000,12000,15000,11,215709,0,0,0,0,0,2,0,0,0,0,0,0,0,"Doomherald Akvesh - In Combat - Cast 'Shadowflame'"),
(98975,0,1,0,0,0,100,0,10000,10000,10000,25000,11,215701,0,0,0,0,0,2,0,0,0,0,0,0,0,"Doomherald Akvesh - In Combat - Cast 'Impending Doom'");
DELETE FROM `creature_equip_template` WHERE `CreatureID`=98975;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(98975,1,134069,0,0,0,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=98975;
-- Doomherald Saera 105095
DELETE FROM `creature_template_addon` WHERE `entry`=105095;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `auras`) VALUES 
(105095,0,0,0,1,0,0,0,0,'188560 215837');
UPDATE `creature_template` SET `lootid`=105095, `AIName`='', `ScriptName`='npc_doomherald_saera_105095', `minlevel`=102, `maxlevel`=102, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=3 WHERE `entry`=105095;
DELETE FROM `creature_equip_template` WHERE `CreatureID`=105095;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(105095,1,126760,0,0,125648,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=105095;
DELETE FROM `creature_text` WHERE `CreatureID` = 105095;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(105095, 0, 0, 'Put your back into it, Taraar. Quickly!', 12, 0, 100, 0, 0, 0, 0, 0, 'Doomherald Saera to Player'),
(105095, 1, 0, 'Keep its soul in tact - Caria has plans for this one.', 12, 0, 100, 0, 0, 0, 0, 0, 'Doomherald Saera to Player'),
(105095, 2, 0, 'You are too late... he comes...', 12, 0, 100, 0, 0, 0, 0, 0, 'Doomherald Saera to Player');
-- Doomherald Taraar 105094
DELETE FROM `creature_template_addon` WHERE `entry`=105094;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `auras`) VALUES 
(105094,0,0,0,1,0,0,0,0,'188560 215837');
UPDATE `creature_template` SET `lootid`=105094, `AIName`='', `ScriptName`='npc_doomherald_taraar_105094', `minlevel`=102, `maxlevel`=102, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=3 WHERE `entry`=105094;
DELETE FROM `creature_equip_template` WHERE `CreatureID`=105094;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(105094,1,126760,0,0,125648,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=105094;
DELETE FROM `creature_text` WHERE `CreatureID` = 105094;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(105094, 0, 0, 'Me?! If you\'d focus we would be done by now!', 12, 0, 100, 0, 0, 0, 0, 0, 'Doomherald Taraar to Player'),
(105094, 1, 0, 'At last something reasonable escapes your lips.', 12, 0, 100, 0, 0, 0, 0, 0, 'Doomherald Taraar to Player');
-- Gorgonnash 99046
UPDATE `creature_template` SET `AIName`='', `ScriptName`='npc_gorgonnash_99046', `minlevel`=102, `maxlevel`=102, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=3 WHERE `entry`=99046;
DELETE FROM `creature_text` WHERE `CreatureID` = 99046;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(99046, 0, 0, 'What\'s that smell? Is that... Illidari?', 12, 0, 100, 0, 0, 58230, 0, 0, 'Gorgonnash to Player'),
(99046, 1, 0, 'Caria must complete her work. You will not intefere.', 14, 0, 100, 0, 0, 58231, 0, 0, 'Gorgonnash to Player'),
(99046, 2, 0, 'Reesh Archim, galar.', 14, 0, 100, 0, 0, 58232, 0, 0, 'Gorgonnash to Player'),
(99046, 3, 0, 'DEATH IS ALL THAT AWAITS YOU!', 14, 0, 100, 0, 0, 58234, 0, 0, 'Gorgonnash to Player');
DELETE FROM `creature_equip_template` WHERE `CreatureID`=99046;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(99046,1,127648,0,0,0,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=99046;
-- Felsoul Legionnaire SAI 105125
SET @FELSOUL_LEGIONAIRE := 105125;
UPDATE `creature_template` SET `lootid`=105125, `AIName`="SmartAI", `minlevel`=100, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=2 WHERE `entry`=@FELSOUL_LEGIONAIRE;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@FELSOUL_LEGIONAIRE AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@FELSOUL_LEGIONAIRE*100+01,@FELSOUL_LEGIONAIRE*100+02) AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@FELSOUL_LEGIONAIRE,0,1,0,10,0,100,1,1,10,0,0,87,@FELSOUL_LEGIONAIRE*100+01,@FELSOUL_LEGIONAIRE*100+02,0,0,0,0,1,0,0,0,0,0,0,0,"Felsoul Legionnaire - Within 1-10 Range Out of Combat LoS - Run Random Script (No Repeat)"),
(@FELSOUL_LEGIONAIRE,0,2,0,0,0,100,0,5000,8000,12000,15000,11,204092,0,0,0,0,0,1,0,0,0,0,0,0,0,"Felsoul Legionnaire - In Combat - Cast 'Fel Strike'"),
(@FELSOUL_LEGIONAIRE*100+01,9,0,0,0,0,100,0,100,100,0,0,1,0,5000,0,0,0,0,1,0,0,0,0,0,0,0,"Felsoul Legionnaire - On Script - Say Line 0"),
(@FELSOUL_LEGIONAIRE*100+02,9,0,0,0,0,100,0,100,100,0,0,1,1,5000,0,0,0,0,1,0,0,0,0,0,0,0,"Felsoul Legionnaire - On Script - Say Line 1");
DELETE FROM `creature_text` WHERE `CreatureID` = 105125;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `comment`) VALUES
(105125, 0, 0, 'You will meet your end!', 12, 0, 100, 0, 0, 53417, 0, 'Felsoul Legionnaire to Player'),
(105125, 1, 0, 'Reinforcements - now!', 12, 0, 100, 0, 0, 53418, 0, 'Felsoul Legionnaire to Player');
DELETE FROM `creature_equip_template` WHERE `CreatureID` IN (105125);
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(105125,1,124360,0,0,0,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=105125;
-- Felsoul Chaosweaver 105138
UPDATE `creature_template` SET `lootid`=105138, `AIName`="SmartAI", `minlevel`=100, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=2 WHERE `entry`=105138;
DELETE FROM `smart_scripts` WHERE `entryorguid`= 105138 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(105138,0,0,0,0,0,100,0,5000,8000,12000,15000,11,216009,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felsoul Chaosweaver - In Combat - Cast 'Corrupting Chaos'"),
(105138,0,1,0,0,0,100,0,0,0,3400,4700,11,183345,64,0,0,0,0,2,0,0,0,0,0,0,0,"Felsoul Chaosweaver - In Combat - Cast 'Shadow Bolt'");
DELETE FROM `creature_equip_template` WHERE `CreatureID`=105138;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(105138,1,128199,0,0,0,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=105138;
-- Felsoul Bloodseeker 98891
UPDATE `creature_template` SET `lootid`=98891, `AIName`="SmartAI", `minlevel`=100, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=2 WHERE `entry`=98891;
DELETE FROM `smart_scripts` WHERE `entryorguid`= 98891 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(98891,0,0,0,0,0,100,0,5000,8000,12000,15000,11,204885,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felsoul Bloodseeker - In Combat - Cast 'Devour Magic'"),
(98891,0,1,0,0,0,100,0,0,0,9400,14700,11,204896,64,0,0,0,0,2,0,0,0,0,0,0,0,"Felsoul Bloodseeker - In Combat - Cast 'Drain Life'");
-- Aldrachi Revenant 105151
UPDATE `creature_template` SET `lootid`=105151, `AIName`='', `ScriptName`='npc_aldrachi_revenant_105151', `minlevel`=101, `maxlevel`=101, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=3 WHERE `entry`=105151;
DELETE FROM `smart_scripts` WHERE `entryorguid`=105151 AND `source_type`=0;
DELETE FROM `creature_text` WHERE `CreatureID` = 105151;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(105151, 0, 0, 'Your soul will be ours...', 12, 0, 100, 0, 0, 0, 0, 0, 'Aldrachi Revenant to Player');
-- Eredar Shadow trapper 108646
UPDATE `creature_template` SET `AIName`='', `minlevel`=100, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=2 WHERE `entry`=108646;
DELETE FROM `creature_equip_template` WHERE `CreatureID`=108646;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(108646,1,126793,0,0,0,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=108646;
-- Caria Felsoul 99184
UPDATE `creature_template` SET `unit_class`=12, `lootid`=99184, `AIName`='', `ScriptName`='npc_caria_felsoul_99184', `minlevel`=102, `maxlevel`=102, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=3 WHERE `entry`=99184;
DELETE FROM `creature_equip_template` WHERE `CreatureID` IN (99184);
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(99184,1,128832,0,0,0,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=99184;
DELETE FROM `creature_text` WHERE `CreatureID` = 99184;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(99184, 0, 0, 'For every soul I claim, my power grows. I will rule this world... ALL worlds!', 12, 0, 100, 0, 0, 58236, 0, 0, 'Caria Felsoul to Player'),
(99184, 1, 0, 'WITNESS THE MIGHT OF THE ALDRACHI!', 14, 0, 100, 0, 0, 58237, 0, 0, 'Caria Felsoul to Player'),
(99184, 2, 0, 'Your destiny awaits!', 12, 0, 100, 0, 0, 58238, 0, 0, 'Caria Felsoul to Player'),
(99184, 3, 0, 'Varedis has shown me the true path. The Legion can make us strong once more!', 12, 0, 100, 0, 0, 0, 0, 0, 'Caria Felsoul'),
(99184, 3, 1, 'Do you not see? Kil\'jaeden offers power Illidan never could!', 12, 0, 100, 0, 0, 58239, 0, 0, 'Caria Felsoul to Player'),
(99184, 4, 0, 'I WILL claim your soul, even if I have to tear it from your lifeless corpse!', 12, 0, 100, 0, 0, 58240, 0, 0, 'Caria Felsoul to Player'),
(99184, 5, 0, 'I will... be... reborn...', 12, 0, 100, 0, 0, 58241, 0, 0, 'Caria Felsoul to Player');
-- Lesser imp (98995)
UPDATE `creature_template` SET `AIName`='', `minlevel`=100, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=0 WHERE `entry`=98995;
-- Lesser Minion (100286)
UPDATE `creature_template` SET `AIName`='', `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=0, `HealthModifier`=1 WHERE `entry`=100286;
-- Burning Crusher (105103)
UPDATE `creature_template` SET `AIName`='', `minlevel`=100, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=1 WHERE `entry`=105103;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=105103;
DELETE FROM `smart_scripts` WHERE `entryorguid`=105103 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(105103,0,0,0,0,0,100,0,5000,8000,12000,15000,11,206881,0,0,0,0,0,2,0,0,0,0,0,0,0,"Burning Crusher - In Combat - Cast 'Blazing Hellfire'"); 
-- Felsoul Portals
DELETE FROM `gameobject_template` WHERE `entry`=245119;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `Data24`, `Data25`, `Data26`, `Data27`, `Data28`, `Data29`, `Data30`, `Data31`, `Data32`, `RequiredLevel`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES
(245119,0,30796,'Collapsed Rocks','questinteract','','',1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'','go_cavern_stones_7796',23222);
UPDATE `gameobject_template` SET `type`=10, `displayId`=30007, `IconName`='questinteract', `castBarCaption`='Destroying', `size`=0.66, `Data0`=99, `Data10`=190610, `Data13`=1, `Data14`=24585, `Data20`=1, `Data23`=1, `Data25`=1, `Data26`=0, `AIName`='', `VerifiedBuild`=26822 WHERE `entry` IN ('248517', '248573');
DELETE FROM `gameobject` WHERE `guid` in (51014375, 51014376, 51014377, 51014378);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `isActive`, `ScriptName`, `VerifiedBuild`) VALUES
-- (51014375,248573,1500,7796,7797,12,0,0,0,-1,-2648.52,19.5848,48.6442,0.85781,-0,-0,-0.415875,-0.909422,7200,255,0,1,'go_brokenshore_felsoul_portal',26822),
-- (51014376,248517,1500,7796,7797,12,0,0,0,-1,-2618.59,78.8602,38.1285,6.15595,-0,-0,-0.0635752,0.997977,7200,255,0,1,'go_brokenshore_felsoul_portal',26822),
(51014377,266029,1500,7796,7797,12,0,0,0,-1,-2507.57,117.86,8.20133,0.254625,-0,-0,-0.126969,-0.991907,7200,255,1,0,'go_temporary_allari_cage',26822);
-- (51014378,245119,1500,7796,7797,12,0,0,0,-1,-2740.67,-149.12,48.4044,1.50511,0,0,0.559193,-0.829037,7200,255,1,0,'go_cavern_stones_7796',26822);
UPDATE `gameobject_template` SET `ScriptName`='go_brokenshore_felsoul_portal' WHERE `entry` IN (248573, 248517);
DELETE FROM `gameobject_addon` WHERE `guid` in (51014375, 51014376);
INSERT INTO `gameobject_addon` (`guid`, `parent_rotation0`, `parent_rotation1`, `parent_rotation2`, `parent_rotation3`, `invisibilityType`, `invisibilityValue`, `WorldEffectID`) VALUES
(51014375,0.0664606,0.00581074,0.156891,0.98536,0,0,0),
(51014376,0.0664606,0.00581074,0.156891,0.98536,0,0,0);
DELETE FROM `gameobject_template_addon` WHERE `entry` in (248573, 248517);
INSERT INTO `gameobject_template_addon` (`entry`, `faction`, `flags`, `mingold`, `maxgold`, `WorldEffectID`) VALUES
(248573,0,262176,0,0,0),
(248517,0,262176,0,0,0);
-- Creature Loot
DELETE FROM `creature_loot_template` WHERE `Entry` IN (98975, 105095, 105094, 105125, 105138, 98891, 105151, 99184);
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
(98975,132204,0,98,0,1,0,1,1,'Doomherald Akvesh: Sticky Volatile Substance'),
(98975,132199,0,2,0,1,0,1,1,'Doomherald Akvesh: Congealed Felblood'),
(98975,137677,0,18,1,1,0,1,1,'Doomherald Akvesh: Fel Blood'),
(105095,132204,0,98,0,1,0,1,1,'Doomherald Saera: Sticky Volatile Substance'),
(105095,132199,0,2,0,1,0,1,1,'Doomherald Saera: Congealed Felblood'),
(105095,138782,0,1,0,1,0,1,1,'Doomherald Saera: Brief History of the Ages'),
(105095,140221,0,2,0,1,0,1,1,'Doomherald Saera: Found Sack of Gems'),
(105095,137677,0,24,1,1,0,1,1,'Doomherald Saera: Fel Blood'),
(105094,132204,0,98,0,1,0,1,1,'Doomherald Taraar: Sticky Volatile Substance'),
(105094,132199,0,2,0,1,0,1,1,'Doomherald Taraar: Congealed Felblood'),
(105094,144345,0,2,0,1,0,1,1,'Doomherald Taraar: Pile of Pet Goodies'),
(105094,137677,0,23,1,1,0,1,1,'Doomherald Taraar: Fel Blood'),
(105125,132204,0,94,0,1,0,1,1,'Felsoul Legionnaire: Sticky Volatile Substance'),
(105125,132199,0,6,0,1,0,1,1,'Felsoul Legionnaire: Congealed Felblood'),
(105125,132231,0,1,0,1,0,1,1,'Felsoul Legionnaire: Worn Hooked Claw'),
(105125,138782,0,0.11,0,1,0,1,1,'Felsoul Legionnaire: Brief History of the Ages'),
(105125,137677,0,23,1,1,0,1,1,'Felsoul Legionnaire: Fel Blood'),
(105125,141064,0,0.09,1,1,0,1,1,'Felsoul Legionnaire: Technique Glyph of Shivarra'),
(105138,132204,0,98,0,1,0,1,1,'Felsoul Chaosweaver: Sticky Volatile Substance'),
(105138,132199,0,2,0,1,0,1,1,'Felsoul Chaosweaver: Congealed Felblood'),
(105138,132231,0,3,0,1,0,1,1,'Felsoul Chaosweaver: Worn Hooked Claw'),
(105138,138782,0,0.5,0,1,0,1,1,'Felsoul Chaosweaver: Brief History of the Ages'),
(105138,138781,0,0.02,0,1,0,1,1,'Felsoul Chaosweaver: Brief History of the Aeons'),
(105138,137677,0,25,1,1,0,1,1,'Felsoul Chaosweaver: Fel Blood'),
(98891,132204,0,3,0,1,0,1,1,'Felsoul Bloodseeker: Sticky Volatile Substance'),
(98891,132231,0,99,0,1,0,1,1,'Felsoul Bloodseeker: Worn Hooked Claw'),
(98891,138781,0,0.02,0,1,0,1,1,'Felsoul Bloodseeker: Brief History of the Aeons'),
(98891,137677,0,24,1,1,0,1,1,'Felsoul Bloodseeker: Fel Blood'),
(105151,132204,0,98,0,1,0,1,1,'Aldrachi Revenant: Sticky Volatile Substance'),
(105151,132199,0,1.2,0,1,0,1,1,'Aldrachi Revenant: Congealed Felblood'),
(105151,138781,0,0.01,0,1,0,1,1,'Aldrachi Revenant: Brief History of the Aeons'),
(105151,137677,0,23,1,1,0,1,1,'Aldrachi Revenant: Fel Blood'),
(99184,132231,0,70,0,1,0,1,1,'Caira Felsoul: Worn Hooked Claw'),
(99184,138782,0,20,0,1,0,1,1,'Caria Felsoul: Brief History of the Ages');
-- go loot 248785 aldrachi-warblades
DELETE FROM `gameobject_loot_template` WHERE `Entry` IN (248785, 65644);
INSERT INTO `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES 
(65644, 128832, 0, 100, 0, 1, 0, 1, 1, 'aldrachi-warblades');
DELETE FROM `gameobject_template` WHERE `Entry`= 248785;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `Data24`, `Data25`, `Data26`, `Data27`, `Data28`, `Data29`, `Data30`, `Data31`, `Data32`, `RequiredLevel`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES
(248785, 3, 9806, 'Aldrachi Warblades', 'questinteract', 'Wielding', '', 2, 1691, 65644, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 107711, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 'go_aldrachi_warblades_248785', 26822);
DELETE FROM `gameobject_template_addon` WHERE `entry`=248785;
INSERT INTO `gameobject_template_addon` (`entry`, `faction`, `flags`) VALUES
(248785, 0, 2097152); -- Aldrachi Warblades
-- Fel Familiar auras
DELETE FROM `creature_template_addon` WHERE `entry`=108686;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `auras`) VALUES 
(108686,0,0,0,1,0,0,0,0,'215847');
-- TEST
UPDATE `creature_template` SET `ScriptName`='npc_portal_bunny' WHERE `entry`='105204'; -- npc_portal_bunny
-- General DH fixes (Should be moved to the appropriate file)
DELETE FROM `creature` WHERE `guid` IN (20542659, 20542665);
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `unit_flags2`, `unit_flags3`, `dynamicflags`, `ScriptName`, `VerifiedBuild`) VALUES
(20542659,103655,1468,0,0,1,0,0,0,-1,0,0,4312.78,-590.177,-281.187,6.08924,7200,0,0,0,0,0,0,0,0,0,0,'',22423),
(20542665,103658,1468,0,0,1,0,0,0,-1,0,0,4339.06,-590.076,-281.158,3.3436,7200,0,0,0,0,0,0,0,0,0,0,'',22423);
UPDATE `creature` SET `PhaseId`=171 WHERE `guid` IN (20542616, 20542615);
DELETE FROM `script_waypoint` WHERE `entry`=99632;
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES
(99632,1,4315.13,-590.317,-281.665,0,'Altruis the Sufferer for Breaking Out'),
(99632,2,4316.88,-590.817,-281.665,0,'Altruis the Sufferer for Breaking Out'),
(99632,3,4317.88,-590.817,-281.665,0,'Altruis the Sufferer for Breaking Out'),
(99632,4,4318.88,-590.816,-281.665,0,'Altruis the Sufferer for Breaking Out'),
(99632,5,4319.63,-590.067,-281.665,0,'Altruis the Sufferer for Breaking Out'),
(99632,6,4320.13,-589.317,-281.665,0,'Altruis the Sufferer for Breaking Out'),
(99632,7,4319.88,-588.817,-281.665,0,'Altruis the Sufferer for Breaking Out'),
(99632,8,4319.15,-586.838,-281.673,0,'Altruis the Sufferer at Weapons Crate'),
(99632,9,4320.9,-586.338,-281.673,0,'Altruis the Sufferer for Breaking Out'),
(99632,10,4321.9,-585.088,-281.673,0,'Altruis the Sufferer for Breaking Out'),
(99632,11,4323.64,-583.668,-281.753,0,'Altruis the Sufferer for Breaking Out');
DELETE FROM `script_waypoint` WHERE `entry`=99631;
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES
(99631, 1, 4337.47, -590.45, -281.415, 0, 'Kayn Sunfury for Breaking Out'),
(99631, 2, 4336.72, -590.7, -281.665, 0, 'Kayn Sunfury for Breaking Out'),
(99631, 3, 4334.97, -590.95, -281.665, 0, 'Kayn Sunfury for Breaking Out'),
(99631, 4, 4333.97, -590.95, -281.665, 0, 'Kayn Sunfury for Breaking Out'),
(99631, 5, 4332.72, -590.7, -281.665, 0, 'Kayn Sunfury for Breaking Out'),
(99631, 6, 4331.97, -590.2, -281.665, 0, 'Kayn Sunfury for Breaking Out'),
(99631, 7, 4331.97, -589.45, -281.665, 0, 'Kayn Sunfury for Breaking Out'),
(99631, 8, 4332.22, -588.95, -281.665, 0, 'Kayn Sunfury at Weapon Crate'),
(99631, 9, 4331.29, -587.508, -281.862, 0, 'Kayn Sunfury for Breaking Out'),
(99631, 10, 4331.29, -586.508, -281.862, 0, 'Kayn Sunfury for Breaking Out'),
(99631, 11, 4331.29, -585.758, -281.862, 0, 'Kayn Sunfury for Breaking Out'),
(99631, 12, 4331.04, -584.758, -281.862, 0, 'Kayn Sunfury for Breaking Out'),
(99631, 13, 4330.54, -584.258, -281.862, 0, 'Kayn Sunfury for Breaking Out'),
(99631, 14, 4328.46, -583.66, -281.729, 0, 'Kayn Sunfury for Breaking Out');
DELETE FROM `creature_equip_template` WHERE `CreatureID`=99632;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(99632,1,128360,0,0,128370,0,0,0,0,0,25549),
(99632,2,0,0,0,0,0,0,0,0,0,25549),
(99632,3,0,0,0,128370,0,0,0,0,0,25549);
DELETE FROM `creature_equip_template` WHERE `CreatureID`=99631;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(99631,1,128359,0,0,128371,0,0,0,0,0,25549),
(99631,2,0,0,0,0,0,0,0,0,0,25549),
(99631,3,0,0,0,128371,0,0,0,0,0,25549);
UPDATE `creature_template` SET `ScriptName`='npc_altruis_sufferer_freed_99632' WHERE `entry`=99632;
UPDATE `creature_template` SET `ScriptName`='npc_kayn_sunfury_freed_99631' WHERE `entry`=99631;
DELETE FROM `gameobject` WHERE `guid` BETWEEN 51014379 AND 51014389;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `isActive`, `ScriptName`, `VerifiedBuild`) VALUES
(51014379,244596,1468,7814,7873,0,0,171,0,-1,4312.67,-605.875,-281.41,0.161516,0,0,0.0806702,0.996741,7200,255,1,0,'',26822),
(51014380,244943,1468,7814,7873,0,0,171,0,-1,4333.72,-587.326,-281.146,0.598127,0,0,0.294625,0.955613,7200,255,1,0,'',26822),
(51014381,244944,1468,7814,7873,0,0,171,0,-1,4318.35,-587.293,-281.11,6.07018,0,0,0.106301,-0.994334,7200,255,1,0,'',26822),
(51014382,244582,1468,7814,7873,0,0,171,0,-1,4330.88,-605.516,-281.922,3.21962,0,0,0.999239,-0.0390038,7200,255,1,0,'',26822),
(51014383,244943,1468,7814,7873,0,0,171,0,-1,4334.09,-587.684,-281.203,0.598127,0,0,0.294625,0.955613,7200,255,1,0,'',26822),
(51014384,244944,1468,7814,7873,0,0,171,0,-1,4318.39,-586.839,-281.127,6.07018,0,0,0.106301,-0.994334,7200,255,1,0,'',26822),
(51014385,244582,1468,7814,7873,0,0,171,0,-1,4317.79,-587.068,-281.922,6.05931,0,0,0.111704,-0.993742,7200,255,1,0,'',26822),
(51014386,244582,1468,7814,7873,0,0,171,0,-1,4334.39,-587.222,-281.922,3.73722,0,0,0.95598,-0.293431,7200,255,1,0,'',26822),
(51014387,253189,1468,7814,7873,0,0,171,0,-1,4330.34,-605.172,-281.156,0.0324739,0,0,0.0162362,0.999868,7200,255,1,0,'',26822),
(51014388,253189,1468,7814,7873,0,0,171,0,-1,4330.37,-605.495,-281.14,0.0324739,0,0,0.0162362,0.999868,7200,255,1,0,'',26822),
(51014389,244596,1468,7814,7873,0,0,171,0,-1,4339.11,-605.908,-281.326,2.96785,0,0,0.996229,0.0867621,7200,255,1,0,'',26822);
DELETE FROM `creature` WHERE `guid` IN (280000453, 280000454);
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `unit_flags2`, `unit_flags3`, `dynamicflags`, `ScriptName`, `VerifiedBuild`) VALUES
(280000453,103655,1468,7814,7873,0,0,0,0,-1,0,0,4312.78,-590.177,-281.187,6.08924,30,0,0,0,0,0,0,0,0,0,0,'',22423),
(280000454,103658,1468,7814,7873,0,0,0,0,-1,0,0,4339.06,-590.076,-281.158,3.3436,30,0,0,0,0,0,0,0,0,0,0,'',22423);
DELETE FROM `spell_area` WHERE `area` = 7873 AND `spell` = 59074;
-- INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `quest_start_status`, `quest_end_status`) VALUES
-- (59074, 7873, 38672, 38672, 8 | 32, 2);
UPDATE `creature` SET `ScriptName` = 'npc_maiev_shadowsong' WHERE `guid`= 20542899 AND `id` = 92718;
UPDATE `creature_template` SET `ScriptName` = 'npc_illidari_felbat_94324' WHERE `entry` = 94324;
UPDATE `creature_template` SET `ScriptName` = 'npc_illidari_felbat_99227' WHERE `entry` = 99227;
DELETE FROM `creature` WHERE `guid` = 280000453;
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `unit_flags2`, `unit_flags3`, `dynamicflags`, `ScriptName`, `VerifiedBuild`) VALUES
(280000453,94324,1220,8445,8445,0,0,0,0,-1,0,0,-845.698,4252.15,746.286,1.05337,300,0,0,87,0,0,0,0,0,0,0,'',26972);
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (99227, 94324);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(99227, 46598, 1, 0),
(94324, 46598, 1, 0);
-- (20542615,103655,1468,0,0,1,0,0,0,-1,0,0,4312.78,-590.177,-281.27,6.08924,7200,0,0,0,0,0,0,0,0,0,0,'',22423)
UPDATE `creature` SET `PhaseId`=0 WHERE `guid`='20542615';
UPDATE `creature_template` SET `ScriptName`='npc_jace_darkweaver_109196' WHERE `entry`=109196;
UPDATE `quest_template_addon` SET `PrevQuestID`=42869 WHERE `ID`=42872;
-- Delete NPCs Altruis and Kayn in the cells, they will be spawned as tempsummon cretures via script
DELETE FROM `creature` WHERE `guid` IN (20542660, 20542664);
-- Vampiric Illidari Felbat
UPDATE `creature_template` SET `unit_flags`=0, `VehicleId`=1051, `MovementId`=0, `AIName`='', `ScriptName`='npc_vault_of_the_wardens_vampiric_felbat' WHERE `entry`=99443;
DELETE FROM `smart_scripts` WHERE `entryorguid`=99443 AND `source_type`=0;
UPDATE `quest_template_addon` SET `ScriptName`='q_securing_the_way' WHERE `ID`=42872;
-- make creatures dead
UPDATE `creature` SET `spawndist`=0, `MovementType`=0, `unit_flags`=537133824 WHERE `guid` IN (20543315, 20543317,
20543325, 20543314, 20543320, 20543332, 20543327, 20543309, 20543329, 20543310, 20543318, 20543311, 20543341,
20543340, 20543348, 20543362, 20543351, 20543355, 20543363, 20543365, 20543370, 20543372, 20543373, 20543378,
20543383, 20543376, 20543377, 20543401, 20543397, 20543386, 20543388, 20543398, 20543395, 20543381, 20543380,
20543407, 20543404, 20543408, 20543409, 20543412, 20543410);

DELETE FROM `creature_addon` WHERE `guid` IN (20543315, 20543317, 20543325, 20543314, 20543320, 20543332, 20543327,
20543309, 20543329, 20543310, 20543318, 20543311, 20543341, 20543340, 20543348, 20543362, 20543351, 20543355,
20543363, 20543365, 20543370, 20543372, 20543373, 20543378, 20543383, 20543376, 20543377, 20543401, 20543397,
20543386, 20543388, 20543398, 20543395, 20543381, 20543380, 20543407, 20543404, 20543408, 20543409, 20543412,
20543410);
INSERT INTO `creature_addon` (`guid`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES
(20543315, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543317, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543325, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543314, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543320, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543332, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543327, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543309, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543329, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543310, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543318, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543311, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543341, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543340, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543348, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543362, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543351, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543355, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543363, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543365, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543370, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543372, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543373, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543378, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543383, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543376, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543377, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543401, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543397, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543386, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543388, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543398, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543395, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543381, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543380, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543407, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543404, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543408, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543409, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543412, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(20543410, 0, 0x0, 0x1, '29266'); -- 25680 - 29266 - 29266
DELETE FROM `creature_template_addon` WHERE `entry` IN (97225, 92782);
-- TEST
UPDATE `creature_template` SET `ScriptName`='npc_elerion_bladedancer_101004' WHERE `entry`=101004;
UPDATE `creature_template` SET `ScriptName`='npc_khadgars_upgraded_servant_114562' WHERE `entry`=114562;
-- Illidari Redoupt Spawns
DELETE FROM `creature` WHERE `guid` BETWEEN 280000455 AND 280000467;
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `unit_flags2`, `unit_flags3`, `dynamicflags`, `ScriptName`, `VerifiedBuild`) VALUES
(280000455,109196,1220,8445,8445,0,0,0,0,-1,0,1,-947.054,4090.14,648.258,5.9197,30,0,0,870,0,0,0,0,0,0,0,'',22423),
(280000456,109247,1220,7502,8284,0,0,0,0,-1,0,1,-948.914,4066.53,648.208,1.2770,30,0,0,87,0,0,0,0,0,0,0,'',22423),
(280000457,109252,1220,8445,8445,0,0,0,0,-1,0,0,-962.38,4080.87,648.141,6.20936,30,0,0,87,0,0,0,0,0,0,0,'',22423),
(280000458,109252,1220,7502,8284,0,0,0,0,-1,0,0,-961.318,4081.57,648.144,6.1426,30,0,0,87,0,0,0,0,0,0,0,'',22423),
(280000459,109340,1220,7502,8284,0,0,0,0,-1,0,1,-940.248,4073.51,648.268,2.44179,30,0,0,870,0,0,0,0,0,0,0,'',22423),
(280000460,102798,1220,7502,8284,0,0,0,0,-1,0,1,-948.018,4070.11,648.221,4.53723,30,0,0,870,0,0,0,0,0,0,0,'',22423),
(280000461,102797,1220,7502,8284,0,0,0,0,-1,0,1,-958.567,4080.89,648.161,3.03712,30,0,0,870,0,0,0,0,0,0,0,'',22423),
(280000462,109295,1220,8445,8445,0,0,0,0,-1,0,0,-949.179,4090.21,650.038,5.625,300,0,0,522,0,0,0,0,0,0,0,'',22423),
(280000463,109252,1220,7502,8284,0,0,0,0,-1,0,0,-962.345,4079.65,648.139,0.0675981,30,0,0,87,0,0,0,0,0,0,0,'',22423),
(280000464,95237,1519,0,0,0,0,0,0,-1,0,1,1524.24,1417.57,243.791,0.0834095,30,0,0,1203351,0,0,0,0,0,0,0,'',22423),
(280000465,95240,1519,0,0,0,0,0,0,-1,0,1,1524.21,1406.65,243.764,6.12075,30,0,0,113100,0,0,0,0,0,0,0,'',22423),
(280000466,95237,1519,8022,8023,0,0,0,0,-1,0,1,1551.41,1414.73,237.108,6.225207,30,0,0,1203351,0,0,0,0,0,0,0,'',22423),
(280000467,103025,1519,8022,8023,0,0,0,0,-1,0,1,1584.68,1409.38,218.026,2.990351,30,0,0,1203351,0,0,0,0,0,0,0,'',22423);
DELETE FROM `creature_equip_template` WHERE `CreatureID` IN (109196, 109247, 109340, 102798, 102797, 95237);
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(109196,1,128360,0,0,128370,0,0,0,0,0,25549),
(109247,1,127651,0,0,0,0,0,0,0,0,25549),
(109340,1,128359,0,0,128371,0,0,0,0,0,25549),
(102798,1,128361,0,0,128369,0,0,0,0,0,25549),
(102797,1,128361,0,0,128369,0,0,0,0,0,25549),
(95237,1,128358,0,0,128372,0,0,0,0,0,25549);
DELETE FROM `gameobject` WHERE `guid` IN (51014378, 51014379);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `isActive`, `ScriptName`, `VerifiedBuild`) VALUES
(51014378,251528,1220,7502,8284,0,0,0,0,-1,-949.313,4090.18,648.245,05.66822,-0,-0,-0.302659,0.953099,300,255,1,0,'',26822),
(51014379,251579,1220,7502,8284,0,0,0,0,-1,-964.162,4066.11,648.119,0.634656,-0,-0,-0.312029,-0.950073,300,255,1,0,'',26822);
DELETE FROM `spell_script_names` WHERE `spell_id` = 217377;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(217377, 'spell_redoubt_sentence_to_death');
UPDATE `creature_template` SET `ScriptName`='npc_redoubt_asha' WHERE `entry` = 102798;
UPDATE `creature_template` SET `ScriptName`='npc_redoubt_belath' WHERE `entry` = 102797;
DELETE FROM `creature_template_addon` WHERE `entry` IN (102798, 102797);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `auras`) VALUES 
(102798,0,0,0,1,0,0,0,0,'18950'),
(102797,0,0,0,1,0,0,0,0,'18950');
UPDATE `quest_template_addon` SET `PrevQuestID`=42872 WHERE `ID`=41033;
UPDATE `quest_template_addon` SET `PrevQuestID`=42872 WHERE `ID`=41221;
-- BreadCrumb Quest "Return To Mardum"
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=19 AND `SourceEntry` IN (41033, 41221);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(19,0,41033,0,0,14,0,40374,0,0,0,0,0,"","Quest 'Return To Mardum' can only be taken if quest 'Obtained Kayn' is not taken"),
(19,0,41221,0,0,14,0,40375,0,0,0,0,0,"","Quest 'Return To Mardum' can only be taken if quest 'Obtained Altruis' is not taken");
DELETE FROM `spell_script_names` WHERE `spell_id` = 215782;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(215782, 'spell_redoubt_teleport_to_dh_ch');
UPDATE `creature_template` SET `minlevel`=100, `maxlevel`=102, `HealthModifier`=3 WHERE `entry`=95237;
DELETE FROM `creature_queststarter` WHERE `quest` IN (41060, 41070, 41037, 41062, 41064, 41066, 41096, 41067);
INSERT INTO `creature_queststarter` (`id`, `quest`) VALUES
(95237, 41060),
(95237, 41070),
(95240, 41037),
(95240, 41062),
(103025, 41064),
(95238, 41066),
(95238, 41096),
(95238, 41067);
UPDATE `quest_template_addon` SET `PrevQuestID` = 41060, `NextQuestID` = 41064, `ExclusiveGroup` = 41070 WHERE `ID` = 41070; -- Spoils of Victory
UPDATE `quest_template_addon` SET `PrevQuestID` = 41037, `NextQuestID` = 41064, `ExclusiveGroup` = 41070 WHERE `ID` = 41062; -- Spoils of Victory
UPDATE `quest_template_addon` SET `PrevQuestID` = 41064 WHERE `ID` = 41066;
UPDATE `quest_template_addon` SET `PrevQuestID` = 41066 WHERE `ID` = 41096;
UPDATE `quest_template_addon` SET `PrevQuestID` = 41066 WHERE `ID` = 41067;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=19 AND `SourceEntry` IN (41096, 41067);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(19,0,41096,0,0,14,0,40374,0,0,0,0,0,"","Quest 'Time is of the Essence' can only be taken if quest 'Obtained Kayn' is not taken"),
(19,0,41067,0,0,14,0,40375,0,0,0,0,0,"","Quest 'Time is of the Essence' can only be taken if quest 'Obtained Altruis' is not taken");
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=19 AND `SourceEntry` IN (41060, 41037);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(19,0,41060,0,0,14,0,40374,0,0,0,0,0,"","Quest 'Unbridled Power' can only be taken if quest 'Obtained Kayn' is not taken"),
(19,0,41037,0,0,14,0,40375,0,0,0,0,0,"","Quest 'Unbridled Power' can only be taken if quest 'Obtained Altruis' is not taken");
UPDATE `gameobject_template` SET `ScriptName`='go_mardum_control_console' WHERE `entry`=254245;
UPDATE `creature_template` SET `ScriptName`='npc_mardum_altruis_ch' WHERE `entry`=95237;
DELETE FROM `creature_equip_template` WHERE `CreatureID` = 98650;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(98650,1,17383,0,0,0,0,0,0,0,0,25549);
UPDATE `creature` SET `id` = 98650, `orientation` = 4.717611, `equipment_id` = 1 WHERE `guid` = 20547034;
UPDATE `creature_template` SET `gossip_menu_id` = 98650, `minlevel` = 110, `maxlevel` = 110, `npcflag` = 3, `speed_run` = 0.992063, `ScriptName`='npc_mardum_battlelord_gaardoun' WHERE `entry`=98650;
DELETE FROM `creature_text` WHERE `CreatureID` = 95237;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(95237, 0, 0, 'Whenever you\'re ready.', 12, 0, 100, 0, 0, 64700, 147331, 0, 'Altruis the Sufferer to Player'),
(95237, 1, 0, 'This way. Your forces await.', 12, 0, 100, 0, 0, 58265, 147332, 0, 'Altruis the Sufferer to Player'),
(95237, 2, 0, 'The Fel Hammer is ours at last. Gaze upon the might of the Twinblades of the Deceiver!', 12, 0, 100, 0, 0, 58266, 147333, 0, 'Altruis the Sufferer to Player'),
(95237, 3, 0, 'We will follow $n into battle, and we will strike down the Legion once and for all!', 12, 0, 100, 0, 0, 58267, 147337, 0, 'Altruis the Sufferer to Player'),
(95237, 4, 0, 'Glory to the Illidari!', 14, 0, 100, 0, 0, 58268, 147338, 0, 'Altruis the Sufferer to Player'),
(95237, 5, 0, 'Welcome to the Fel Hammer, $n.', 14, 0, 100, 0, 0, 58271, 0, 0, 'Altruis the Sufferer to Player');
DELETE FROM `creature_text` WHERE `CreatureID` = 98650;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(98650, 0, 0, 'The Ashtongue will fight beside you.', 12, 0, 100, 0, 0, 64714, 147334, 0, 'Gaardoun to Player'),
(98650, 1, 0, 'Ah, of course. Right this way.', 12, 0, 100, 0, 0, 64701, 0, 0, 'Gaardoun to Player'),
(98650, 2, 0, 'Legion reinforcements arrived soon after you left for the Black Temple, destroying the portal behind you. Oh, it was a glorious battle!', 12, 0, 100, 0, 0, 64702, 0, 0, 'Gaardoun to Player'),
(98650, 3, 0, 'In the aftermath, we uncovered an ancient Nathrezim forge used to create many of the Legion\'s most powerful weapons.', 12, 0, 100, 0, 0, 64703, 0, 0, 'Gaardoun to Player'),
(98650, 4, 0, 'We\'ve guarded it carefully ever since. I think it prove quite useful to you.', 12, 0, 100, 0, 0, 64704, 0, 0, 'Gaardoun to Player');
DELETE FROM `creature_text` WHERE `CreatureID` = 103025;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(103025, 0, 0, 'Move, you fools! Show $n some respect!', 12, 0, 100, 0, 0, 64705, 0, 0, 'Gaardoun to Player');
DELETE FROM `creature_text` WHERE `CreatureID` = 98624;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(98624, 0, 0, 'You may call upon the Coilskar as well.', 12, 0, 100, 0, 0, 64715, 147335, 0, 'Lady Stheno to Player');
DELETE FROM `creature_text` WHERE `CreatureID` = 98632;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(98632, 0, 0, 'Our mission is not yel complete. We are all yours to command.', 12, 0, 100, 0, 0, 64716, 147336, 0, 'Matron Mother Nalevolence to Player');
DELETE FROM `script_waypoint` WHERE `entry`=98650;
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES
(98650,1,1561.03,1423.589,237.108,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,2,1577.71,1427.824,237.108,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,3,1581.88,1429.974,237.117,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,4,1585.12,1432.572,236.635,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,5,1590.02,1438.280,239.425,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,6,1593.77,1443.242,243.055,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,7,1595.04,1446.464,243.339,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,8,1594.92,1449.646,243.377,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,9,1593.88,1452.219,243.776,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,10,1590.93,1455.502,241.058,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,11,1587.41,1457.452,239.082,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,12,1579.35,1461.667,234.515,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,13,1572.21,1463.673,231.405,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,14,1566.23,1464.733,230.877,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,15,1561.88,1461.941,230.803,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,16,1561.19,1459.083,230.760,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,17,1561.52,1453.845,226.304,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,18,1561.41,1446.114,219.558,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,19,1567.48,1418.781,217.639,0,'Battlelord Gaardoun for Spoils of Victory'),
(98650,20,1584.68,1409.386,218.026,0,'Battlelord Gaardoun for Spoils of Victory');
DELETE FROM `gossip_menu` WHERE `MenuId` = 98650;
INSERT INTO `gossip_menu` (`MenuId`, `TextId`, `VerifiedBuild`) VALUES
(98650, 147331, 25549);
DELETE FROM `gossip_menu_option` WHERE `MenuId` = 98650;
INSERT INTO `gossip_menu_option` (`MenuId`, `OptionIndex`, `OptionIcon`, `OptionText`, `OptionBroadcastTextId`, `OptionType`, `OptionNpcFlag`, `VerifiedBuild`) VALUES
(98650, 1, 0, 'Show me what we acquired in our conquest', 0, 1, 1, 25549);
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN (15) AND `SourceGroup` IN (98650);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `sourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(15, 98650, 1, 0, 0, 9, 0, 41070, 0, 0, 0, 0, 0, '', 'Gossip Only Shows if Quest Taken');
DELETE FROM `spell_script_names` WHERE `spell_id` IN (207407, 213010, 213017, 212817);
INSERT IGNORE INTO `spell_script_names` (`scriptname`, `spell_id`) VALUES
('spell_dh_artifact_soul_carver', 207407),
('spell_dh_artifact_charred_warblades', 213010),
('spell_dh_artifact_fueled_by_pain', 213017),
('spell_dh_artifact_fiery_demise', 212817);
