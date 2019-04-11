-- 'Undead start zone Lilian Voss Spawn creature_id=38895' quest_id=24960'
DELETE FROM creature WHERE id IN (38895);
INSERT INTO creature (id, map, phaseId, position_x, position_y, position_z, orientation, spawntimesecs, MovementType) VALUES
(38895, 0, 0, 1755.741333, 1666.410278, 121.318573, 3.3375, 300, 0);

-- Fix npcflag to npc Young Night Web Spider=1504 and Night Web Spider=1505
UPDATE creature_template SET npcflag=0 WHERE entry IN (1504, 1505);

-- Spirit Healer menu fix
UPDATE creature_template SET npcflag=16384 WHERE entry=6491;

-- Last Rites, First Rites quest fix (https://www.wowhead.com/quest=24861/last-rites-first-rites)
DELETE FROM `spell_script_names` WHERE `spell_id` = '71898';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (71898, 'spell_funeral_offering');

-- Passing Wisdom quest 29790 fix
DELETE FROM conditions WHERE conditions.SourceTypeOrReferenceId = 26 AND conditions.SourceGroup IN (1885, 1527) AND conditions.ConditionValue1 = 29790;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
('26', '1885', '0', '0', '0', '9', '0', '29790', '0', '0', '0', '0', '0', '', 'Wandering Isle Phase 1885 when Quest 29790 taken'),
('26', '1885', '0', '0', '1', '28', '0', '29790', '0', '0', '0', '0', '0', '', 'Wandering Isle Phase 1885 when Quest 29790 complete'),
('26', '1885', '0', '0', '2', '8', '0', '29790', '0', '0', '0', '0', '0', '', 'Wandering Isle Phase 1885 when Quest 29790 rewarded');

-- Cry For The Moon custom script register
UPDATE `creature_template` SET ScriptName = 'npc_oliver_harris' WHERE entry = 43730;

-- Bidden to Greatness
UPDATE `conditions` SET `ScriptName` = "" WHERE `SourceGroup` = 878 AND `ConditionTypeOrReference` = "48";
DELETE FROM `smart_scripts` WHERE `entryorguid`=7710;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param_string`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
('7710','2','0','0','46','0','100','0','7710','0','0','0','','85','115442','2','0','0','0','0','7','0','0','0','0','0','0','0','On Trigger - Invoker Cast Summon Mandori Gate NPCs');
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param_string`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
('7710','2','1','0','46','0','100','0','7710','0','0','0','','85','115343','2','0','0','0','0','7','0','0','0','0','0','0','0','On Trigger - Invoker Cast Summon Mandori Gate NPCs');
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param_string`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
('7710','2','2','0','46','0','100','0','7710','0','0','0','','85','115351','2','0','0','0','0','7','0','0','0','0','0','0','0','On Trigger - Invoker Cast Summon Mandori Gate NPCs');
-- INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `unit_flags2`, `unit_flags3`, `dynamicflags`, `ScriptName`, `VerifiedBuild`) VALUES
-- (1, '60566','0','12','7486','1','0','0','0','-1','0','0','-9114.68','388.256','92.1206','1.87039','120','0','0','338','0','0','0','0','0','0','0','','0');

-- Delivery Cart (57740)
UPDATE `smart_scripts` SET `event_param1`='33' WHERE  `entryorguid`=57740 AND `source_type`=0 AND `id`=7 AND `link`=0;
DELETE FROM `waypoints` WHERE `entry`=57740 AND `pointid` IN (34,35,36,37,38,39);

-- Nourished Yak (57742)
UPDATE `smart_scripts` SET `event_param1`='33' WHERE  `entryorguid`=57742 AND `source_type`=0 AND `id`=4 AND `link`=0;
DELETE FROM `waypoints` WHERE `entry`=57742 AND `pointid` IN (34,35,36,37,38,39);

-- Plump Virmen (55483)
UPDATE `creature_template` SET `flags_extra`='2' WHERE  `entry`=55483;

-- Fix Quest cleansing-the-waters - 9427
DELETE FROM `creature` WHERE `id`=17000;

-- displayID original was 299, data1 was 25
UPDATE `gameobject_template` SET  `displayid`='0', `Data1`='50' WHERE  `entry`=300069;

UPDATE `gameobject` SET `spawntimesecs`='300',`position_x`='418.33', `position_y`='3461.26', `position_z`='82.99' WHERE  `guid`=49513;

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (17000, 1700000);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`,`event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param_string`, `action_type`, `action_param1`, `action_param2`, `action_param3`,`action_param4`,`action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(17000, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 0, 80, 1700000, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Aggonis - Just Created - Cast Spaw'),
(17000, 0, 1, 0, 0, 0, 100, 0, 3000, 5000, 12000, 16000, 0, 11, 22678, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Aggonis - Cast Fear'),
(1700000, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 11, 24240, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Aggonis - On Script - Cast Lightning'),
(1700000, 9, 1, 0, 0, 0, 100, 0, 3500, 3500, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,'Script');

DELETE FROM `creature_text` WHERE `creatureID`=17000;
INSERT INTO `creature_text` (`creatureid`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES 
(17000, 0, 0, 'Fools!  You seek to abjure my father\'s presence?  Death awaits you, mortals!', 12, 0, 100, 0, 0, 0, 0, 'Aggonis SAY');

-- Quest id: 10368 - "The Dreghood Elders" - Add missing gossip menu option
DELETE FROM `gossip_menu_option` WHERE `MenuId`=20679;
INSERT INTO `gossip_menu_option` (`MenuId`, `OptionIndex`, `OptionIcon`, `OptionText`, `OptionBroadcastTextId`, `OptionType`, `OptionNpcFlag`, `VerifiedBuild`) VALUES
(20679, 0, 0, 'You are free to go!', 0, 1, 1, 29416);

-- DB Errors (Testing)
-- Corrected flags for some quest givers
UPDATE creature_template SET npcflag = 3 WHERE entry IN(18927,20102,20870,20885,20886,20912,22113,51998,107997);
UPDATE creature_template SET npcflag = 3 WHERE entry IN(17076,17296,36479,39063);

-- Deleted some mess
DELETE FROM game_event_creature WHERE guid IN(136150,136166,136167,136168,136169,136170,136171,136172,136173,136174,136175,136176,136177,136178,136179,136180,136181,136182,136185,136186,136187,136188,136200,136201,136202,136203,136215,136224,136225,136226,136227);
DELETE FROM game_event_creature WHERE guid BETWEEN 136228 AND 142240;
DELETE FROM game_event_creature WHERE guid BETWEEN 373394 AND 374888;
DELETE FROM game_event_creature WHERE guid BETWEEN 375109 AND 375150;
DELETE FROM game_event_gameobject WHERE guid IN(200965,200966,203103,203104,212814,214896,215000,215003,216443,216444);

UPDATE creature_template SET trainer_type = 3 WHERE entry IN (16583,19341,47420,108825,95844);
UPDATE creature_template SET npcflag = 4307 WHERE entry IN (16583,19341,47420,108825,95844);

DELETE FROM `achievement_reward` WHERE `ItemID` IN (147876, 140998, 140997, 139284, 128513, 116788, 115301, 90918, 71134, 49362, 46894, 44819);


