-- DB/Uldum
-- Pathing for  Entry: 46402 'TDB FORMAT' 
SET @NPC := 264940;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-9510.48,`position_y`=-945.682,`position_z`=104.7723 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-9510.48,-945.682,104.7723,0,1,0,0,100,0),
(@PATH,2,-9490.02,-945.651,109.2862,0,1,0,0,100,0),
(@PATH,3,-9481.64,-925.976,109.2723,0,1,0,0,100,0),
(@PATH,4,-9464.31,-923.748,112.5456,0,1,0,0,100,0),
(@PATH,5,-9445.52,-922.311,112.5456,0,1,0,0,100,0),
(@PATH,6,-9464.31,-923.748,112.5456,0,1,0,0,100,0),
(@PATH,7,-9481.64,-925.976,109.2723,0,1,0,0,100,0),
(@PATH,8,-9490.02,-945.651,109.2862,0,1,0,0,100,0),
(@PATH,9,-9510.48,-945.682,104.7723,0,1,0,0,100,0),
(@PATH,10,-9533.89,-946.705,104.7548,0,1,0,0,100,0),
(@PATH,11,-9549.63,-945.835,100.3798,0,1,0,0,100,0),
(@PATH,12,-9554.9,-939.823,100.3798,0,1,0,0,100,0),
(@PATH,13,-9560.75,-931.833,100.2973,0,1,0,0,100,0),
(@PATH,14,-9569,-926.535,100.2999,0,1,0,0,100,0),
(@PATH,15,-9575.53,-925.012,100.2999,0,1,0,0,100,0),
(@PATH,16,-9569,-926.535,100.2999,0,1,0,0,100,0),
(@PATH,17,-9560.75,-931.833,100.2973,0,1,0,0,100,0),
(@PATH,18,-9554.9,-939.823,100.3798,0,1,0,0,100,0),
(@PATH,19,-9549.63,-945.835,100.3798,0,1,0,0,100,0),
(@PATH,20,-9533.89,-946.705,104.7548,0,1,0,0,100,0);
-- 0x2030A400202D508000003B0002176446 .go xyz -9510.48 -945.682 104.7723

-- Pathing for  Entry: 46402 'TDB FORMAT' 
SET @NPC := 264918;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-9484.29,`position_y`=-969.646,`position_z`=109.2723 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-9484.29,-969.646,109.2723,0,0,0,0,100,0),
(@PATH,2,-9469.68,-976.174,109.2723,0,0,0,0,100,0),
(@PATH,3,-9458.85,-979.596,111.0884,0,0,0,0,100,0),
(@PATH,4,-9449.62,-988.665,111.0884,0,0,0,0,100,0),
(@PATH,5,-9442.48,-1009.54,111.0884,0,0,0,0,100,0),
(@PATH,6,-9449.62,-988.665,111.0884,0,0,0,0,100,0),
(@PATH,7,-9458.85,-979.596,111.0884,0,0,0,0,100,0),
(@PATH,8,-9469.68,-976.174,109.2723,0,0,0,0,100,0),
(@PATH,9,-9484.29,-969.646,109.2723,0,0,0,0,100,0),
(@PATH,10,-9508.17,-970.24,104.7574,0,0,0,0,100,0),
(@PATH,11,-9517.24,-974.8,104.7574,0,0,0,0,100,0),
(@PATH,12,-9518.43,-984.09,104.7574,0,0,0,0,100,0),
(@PATH,13,-9517.24,-974.8,104.7574,0,0,0,0,100,0),
(@PATH,14,-9508.17,-970.24,104.7574,0,0,0,0,100,0);
-- 0x203EF000202D50800012DE00038179D8 .go xyz -9484.29 -969.646 109.2723

-- Pathing for  Entry: 48883 'TDB FORMAT' 
SET @NPC := 263867;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-9478.011,`position_y`=-956.4583,`position_z`=109.2862 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-9478.011,-956.4583,109.2862,0,0,0,0,100,0),
(@PATH,2,-9483.828,-947.7882,109.2862,0,0,0,0,100,0),
(@PATH,3,-9493.745,-946.2916,109.288,0,0,0,0,100,0),
(@PATH,4,-9507.291,-946.875,104.7723,0,0,0,0,100,0),
(@PATH,5,-9527.058,-945.5486,104.7723,0,0,0,0,100,0),
(@PATH,6,-9549.873,-945.8264,100.3798,0,0,0,0,100,0),
(@PATH,7,-9553.707,-951.0538,100.3798,0,0,0,0,100,0),
(@PATH,8,-9555.106,-961.9149,100.3798,0,0,0,0,100,0),
(@PATH,9,-9552.356,-965.5,100.3798,0,0,0,0,100,0),
(@PATH,10,-9544.797,-967.2292,101.4913,0,0,0,0,100,0),
(@PATH,11,-9531.134,-967.6788,104.7574,0,0,0,0,100,0),
(@PATH,12,-9513.389,-968.243,104.7574,0,0,0,0,100,0),
(@PATH,13,-9500.127,-969.6476,107.0643,0,0,0,0,100,0),
(@PATH,14,-9488.435,-969.3143,109.2723,0,0,0,0,100,0),
(@PATH,15,-9479.194,-964.6597,109.2862,0,0,0,0,100,0);
-- 0x2030A400202FBCC000003B0000176451 .go xyz -9478.011 -956.4583 109.2862

DELETE FROM `creature_addon` WHERE `guid` IN (263870, 263868, 263933, 263932, 263921, 263920, 263862, 263860);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(263870, 0, 0, 0, 257, 375, ''),
(263868, 0, 0, 0, 257, 375, ''),
(263933, 0, 0, 0, 257, 375, ''),
(263932, 0, 0, 0, 257, 375, ''),
(263921, 0, 0, 0, 257, 375, ''),
(263920, 0, 0, 0, 257, 375, ''),
(263862, 0, 0, 0, 257, 375, ''),
(263860, 0, 0, 0, 257, 375, '');

-- Creature Ramkahen Citizen 46402 SAI
SET @ENTRY := 46402;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`= @ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;

SET @ENTRY := -264447;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 1, 0, 100, 0, 2000, 10000, 2000, 10000, 5, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 2000 and 10000 ms (and later repeats every 2000 and 10000 ms) - Self: Play emote 1 // "),
(@ENTRY, 0, 1, 0, 1, 0, 100, 0, 20000, 30000, 20000, 30000, 5, 25, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 20000 and 30000 ms (and later repeats every 20000 and 30000 ms) - Self: Play emote 25 // ");

SET @ENTRY := -264446;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 1, 0, 100, 0, 2000, 10000, 2000, 10000, 5, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 2000 and 10000 ms (and later repeats every 2000 and 10000 ms) - Self: Play emote 1 // "),
(@ENTRY, 0, 1, 0, 1, 0, 100, 0, 20000, 30000, 20000, 30000, 5, 25, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 20000 and 30000 ms (and later repeats every 20000 and 30000 ms) - Self: Play emote 25 // ");

SET @ENTRY := -264933;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 1, 0, 100, 0, 2000, 10000, 2000, 10000, 5, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 2000 and 10000 ms (and later repeats every 2000 and 10000 ms) - Self: Play emote 1 // "),
(@ENTRY, 0, 1, 0, 1, 0, 100, 0, 20000, 30000, 20000, 30000, 5, 25, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 20000 and 30000 ms (and later repeats every 20000 and 30000 ms) - Self: Play emote 25 // ");

SET @ENTRY := -264934;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 1, 0, 100, 0, 2000, 10000, 2000, 10000, 5, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 2000 and 10000 ms (and later repeats every 2000 and 10000 ms) - Self: Play emote 1 // "),
(@ENTRY, 0, 1, 0, 1, 0, 100, 0, 20000, 30000, 20000, 30000, 5, 25, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 20000 and 30000 ms (and later repeats every 20000 and 30000 ms) - Self: Play emote 25 // ");

SET @ENTRY := -264930;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 1, 0, 100, 0, 2000, 10000, 2000, 10000, 5, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 2000 and 10000 ms (and later repeats every 2000 and 10000 ms) - Self: Play emote 1 // "),
(@ENTRY, 0, 1, 0, 1, 0, 100, 0, 20000, 30000, 20000, 30000, 5, 25, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 20000 and 30000 ms (and later repeats every 20000 and 30000 ms) - Self: Play emote 25 // ");

SET @ENTRY := -264932;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 1, 0, 100, 0, 2000, 10000, 2000, 10000, 5, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 2000 and 10000 ms (and later repeats every 2000 and 10000 ms) - Self: Play emote 1 // "),
(@ENTRY, 0, 1, 0, 1, 0, 100, 0, 20000, 30000, 20000, 30000, 5, 25, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 20000 and 30000 ms (and later repeats every 20000 and 30000 ms) - Self: Play emote 25 // ");

SET @ENTRY := -264931;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 1, 0, 100, 0, 2000, 10000, 2000, 10000, 5, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 2000 and 10000 ms (and later repeats every 2000 and 10000 ms) - Self: Play emote 1 // "),
(@ENTRY, 0, 1, 0, 1, 0, 100, 0, 20000, 30000, 20000, 30000, 5, 25, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 20000 and 30000 ms (and later repeats every 20000 and 30000 ms) - Self: Play emote 25 // ");

SET @ENTRY := -264938;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 1, 0, 100, 0, 2000, 10000, 2000, 10000, 5, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 2000 and 10000 ms (and later repeats every 2000 and 10000 ms) - Self: Play emote 1 // "),
(@ENTRY, 0, 1, 0, 1, 0, 100, 0, 20000, 30000, 20000, 30000, 5, 25, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 20000 and 30000 ms (and later repeats every 20000 and 30000 ms) - Self: Play emote 25 // ");

SET @ENTRY := -264939;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 1, 0, 100, 0, 2000, 10000, 2000, 10000, 5, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 2000 and 10000 ms (and later repeats every 2000 and 10000 ms) - Self: Play emote 1 // "),
(@ENTRY, 0, 1, 0, 1, 0, 100, 0, 20000, 30000, 20000, 30000, 5, 25, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 20000 and 30000 ms (and later repeats every 20000 and 30000 ms) - Self: Play emote 25 // ");

SET @ENTRY := -264936;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 1, 0, 100, 0, 2000, 10000, 2000, 10000, 5, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 2000 and 10000 ms (and later repeats every 2000 and 10000 ms) - Self: Play emote 1 // "),
(@ENTRY, 0, 1, 0, 1, 0, 100, 0, 20000, 30000, 20000, 30000, 5, 25, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 20000 and 30000 ms (and later repeats every 20000 and 30000 ms) - Self: Play emote 25 // ");

SET @ENTRY := -264937;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 1, 0, 100, 0, 2000, 10000, 2000, 10000, 5, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 2000 and 10000 ms (and later repeats every 2000 and 10000 ms) - Self: Play emote 1 // "),
(@ENTRY, 0, 1, 0, 1, 0, 100, 0, 20000, 30000, 20000, 30000, 5, 25, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "When out of combat and timer at the begining between 20000 and 30000 ms (and later repeats every 20000 and 30000 ms) - Self: Play emote 25 // ");

-- Creature Samir 
SET @ENTRY := 47625;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`= @ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 60, 0, 100, 0, 5000, 5000, 55000, 55000, 17, 69, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Every 55000 and 55000 ms (for the first time, timer between 5000 and 5000 ms) - Self: Set emote state (UNIT_NPC_EMOTESTATE) to 69 // "),
(@ENTRY, 0, 1, 0, 60, 0, 100, 0, 12500, 12500, 55000, 55000, 17, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Every 55000 and 55000 ms (for the first time, timer between 12500 and 12500 ms) - Self: Set emote state (UNIT_NPC_EMOTESTATE) to 0 // "),
(@ENTRY, 0, 2, 0, 60, 0, 100, 0, 13000, 13000, 55000, 55000, 66, 0, 0, 0, 0, 0, 0, 10, 263934, 0, 0, 0, 0, 0, 0, "Every 55000 and 55000 ms (for the first time, timer between 13000 and 13000 ms) - Self: Look at Creature Blacksmith Abasi 48617 (263934) // "),
(@ENTRY, 0, 3, 0, 60, 0, 100, 0, 15000, 15000, 55000, 55000, 5, 397, 0, 0, 0, 0, 0, 10, 263934, 0, 0, 0, 0, 0, 0, "Every 55000 and 55000 ms (for the first time, timer between 15000 and 15000 ms) - Creature Blacksmith Abasi 48617 (263934): Play emote 397 // "),
(@ENTRY, 0, 4, 0, 60, 0, 100, 0, 15600, 15600, 55000, 55000, 5, 274, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Every 55000 and 55000 ms (for the first time, timer between 15600 and 15600 ms) - Self: Play emote 274 // "),
(@ENTRY, 0, 5, 0, 60, 0, 100, 0, 19400, 19400, 55000, 55000, 5, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Every 55000 and 55000 ms (for the first time, timer between 19400 and 19400 ms) - Self: Play emote 6 // "),
(@ENTRY, 0, 6, 0, 60, 0, 100, 0, 19700, 19700, 55000, 55000, 5, 396, 0, 0, 0, 0, 0, 10, 263934, 0, 0, 0, 0, 0, 0, "Every 55000 and 55000 ms (for the first time, timer between 19700 and 19700 ms) - Creature Blacksmith Abasi 48617 (263934): Play emote 396 // "),
(@ENTRY, 0, 7, 0, 60, 0, 100, 0, 22900, 22900, 55000, 55000, 5, 273, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Every 55000 and 55000 ms (for the first time, timer between 22900 and 22900 ms) - Self: Play emote 273 // "),
(@ENTRY, 0, 8, 0, 60, 0, 100, 0, 24500, 24500, 55000, 55000, 5, 396, 0, 0, 0, 0, 0, 10, 263934, 0, 0, 0, 0, 0, 0, "Every 55000 and 55000 ms (for the first time, timer between 24500 and 24500 ms) - Creature Blacksmith Abasi 48617 (263934): Play emote 396 // "),
(@ENTRY, 0, 9, 0, 60, 0, 100, 0, 26500, 26500, 55000, 55000, 66, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Every 55000 and 55000 ms (for the first time, timer between 26500 and 26500 ms) - Self: Look at home position // "),
(@ENTRY, 0, 10, 0, 60, 0, 100, 0, 27700, 27700, 55000, 55000, 17, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Every 55000 and 55000 ms (for the first time, timer between 27700 and 27700 ms) - Self: Set emote state (UNIT_NPC_EMOTESTATE) to 0 // "),
(@ENTRY, 0, 11, 0, 60, 0, 100, 0, 31500, 31500, 55000, 55000, 17, 233, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Every 55000 and 55000 ms (for the first time, timer between 31500 and 31500 ms) - Self: Set emote state (UNIT_NPC_EMOTESTATE) to 233 // "),
(@ENTRY, 0, 12, 0, 60, 0, 100, 0, 49800, 49800, 55000, 55000, 17, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Every 55000 and 55000 ms (for the first time, timer between 49800 and 49800 ms) - Self: Set emote state (UNIT_NPC_EMOTESTATE) to 0 // ");

DELETE FROM `creature_addon` WHERE `guid`= 264935;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(264935, 0, 0, 0, 1, 0, ''); -- 47625

UPDATE `creature` SET `equipment_id`= 1 WHERE `guid`= 264935;

DELETE FROM `creature_equip_template` WHERE `CreatureID`= 47625;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`) VALUES
(47625, 1, 1903, 0, 0); -- 47625
-- ---------------------------------------------------
-- DB/Elwynn: added pathing to Fargodeep Mines Kobolds and Princess
-- Pathing for  Entry: 475 'TDB FORMAT' 
SET @NPC := 280185;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-9857.371,`position_y`=179.0012,`position_z`=20.34673 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-9857.371,179.0012,20.34673,0,0,0,0,100,0),
(@PATH,2,-9865.824,179.7147,18.95403,0,0,0,0,100,0),
(@PATH,3,-9875.407,186.6826,17.52646,0,0,0,0,100,0),
(@PATH,4,-9883.963,195.0957,15.47739,0,0,0,0,100,0),
(@PATH,5,-9893.877,206.7493,14.13369,0,0,0,0,100,0),
(@PATH,6,-9900.333,215.4647,14.84706,0,0,0,0,100,0),
(@PATH,7,-9912.066,220.6375,17.55446,0,0,0,0,100,0),
(@PATH,8,-9936.305,225.5934,22.25602,0,0,0,0,100,0),
(@PATH,9,-9912.066,220.6375,17.55446,0,0,0,0,100,0),
(@PATH,10,-9900.333,215.4647,14.84706,0,0,0,0,100,0),
(@PATH,11,-9893.877,206.7493,14.13369,0,0,0,0,100,0),
(@PATH,12,-9884.15,195.3242,15.47739,0,0,0,0,100,0),
(@PATH,13,-9875.619,186.8867,17.47739,0,0,0,0,100,0),
(@PATH,14,-9865.939,179.8086,18.91875,0,0,0,0,100,0),
(@PATH,15,-9857.371,179.0012,20.34673,0,0,0,0,100,0),
(@PATH,16,-9845.659,183.0172,20.97102,0,0,0,0,100,0),
(@PATH,17,-9838.6,191.2428,23.04388,0,0,0,0,100,0),
(@PATH,18,-9845.029,183.2025,21.20053,0,0,0,0,100,0),
(@PATH,19,-9857.371,179.0012,20.34673,0,0,0,0,100,0);
-- 0x203CC400000076C00013930003F8925A .go xyz -9857.371 179.0012 20.34673

-- Pathing for  Entry: 475 'TDB FORMAT' 
SET @NPC := 280142;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-9761.747,`position_y`=106.7565,`position_z`=26.45013 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-9761.747,106.7565,26.45013,0,0,0,0,100,0),
(@PATH,2,-9770.365,103.1574,27.18955,0,0,0,0,100,0),
(@PATH,3,-9781.66,98.24756,28.74007,0,0,0,0,100,0),
(@PATH,4,-9789.447,94.47607,28.77352,0,0,0,0,100,0),
(@PATH,5,-9797.38,89.08634,28.51797,0,0,0,0,100,0),
(@PATH,6,-9789.447,94.47607,28.77352,0,0,0,0,100,0),
(@PATH,7,-9781.66,98.24756,28.74007,0,0,0,0,100,0),
(@PATH,8,-9770.365,103.1574,27.18955,0,0,0,0,100,0),
(@PATH,9,-9761.747,106.7565,26.45013,0,0,0,0,100,0),
(@PATH,10,-9748.221,110.5554,25.59357,0,0,0,0,100,0),
(@PATH,11,-9740.368,112.9743,24.81501,0,0,0,0,100,0),
(@PATH,12,-9748.221,110.5554,25.59357,0,0,0,0,100,0);
-- 0x203CC400000076C00013930001F8925B .go xyz -9761.747 106.7565 26.45013

-- Pathing for  Entry: 475 'TDB FORMAT' 
SET @NPC := 280145;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-9788.127,`position_y`=149.6609,`position_z`=25.07858 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-9788.127,149.6609,25.07858,0,0,0,0,100,0),
(@PATH,2,-9794.722,152.9546,24.72138,0,0,0,0,100,0),
(@PATH,3,-9797.021,159.9689,25.46847,0,0,0,0,100,0),
(@PATH,4,-9800.761,172.8822,23.31731,0,0,0,0,100,0),
(@PATH,5,-9803.823,180.0129,22.35514,0,0,0,0,100,0),
(@PATH,6,-9809.692,182.0895,22.5449,0,0,0,0,100,0),
(@PATH,7,-9821.691,180.9642,22.81018,0,0,0,0,100,0),
(@PATH,8,-9809.692,182.0895,22.5449,0,0,0,0,100,0),
(@PATH,9,-9803.823,180.0129,22.35514,0,0,0,0,100,0),
(@PATH,10,-9800.761,172.8822,23.31731,0,0,0,0,100,0),
(@PATH,11,-9797.021,159.9689,25.46847,0,0,0,0,100,0);
-- 0x203CC400000076C0001393000178925B .go xyz -9788.127 149.6609 25.07858

-- Pathing for  Entry: 475 'TDB FORMAT' 
SET @NPC := 280248;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-9772.54,`position_y`=97.54986,`position_z`=6.61907 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-9772.54,97.54986,6.61907,0,0,0,0,100,0),
(@PATH,2,-9762.998,91.01275,11.75701,0,0,0,0,100,0),
(@PATH,3,-9751.17,89.2978,13.26458,0,0,0,0,100,0),
(@PATH,4,-9746.868,89.78358,12.87456,0,0,0,0,100,0),
(@PATH,5,-9744.331,97.00578,12.62533,0,0,0,0,100,0),
(@PATH,6,-9749.636,106.8764,13.79356,0,0,0,0,100,0),
(@PATH,7,-9753.591,118.0865,15.39913,0,0,0,0,100,0),
(@PATH,8,-9751.409,126.1938,17.07101,0,0,0,0,100,0),
(@PATH,9,-9749.368,136.0419,19.43791,0,0,0,0,100,0),
(@PATH,10,-9751.409,126.1938,17.07101,0,0,0,0,100,0),
(@PATH,11,-9753.591,118.0865,15.39913,0,0,0,0,100,0),
(@PATH,12,-9749.636,106.8764,13.79356,0,0,0,0,100,0),
(@PATH,13,-9744.331,97.00578,12.62533,0,0,0,0,100,0),
(@PATH,14,-9746.868,89.78358,12.87456,0,0,0,0,100,0),
(@PATH,15,-9751.17,89.2978,13.26458,0,0,0,0,100,0),
(@PATH,16,-9762.998,91.01275,11.75701,0,0,0,0,100,0),
(@PATH,17,-9772.54,97.54986,6.61907,0,0,0,0,100,0);
-- 0x203CC400000076C00013930000F8925B .go xyz -9744.331 97.00578 12.62533

-- Pathing for  Entry: 330 'TDB FORMAT' 
SET @NPC := 280296;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-9946.83,`position_y`=408.503,`position_z`=34.89249 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '87519');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-9946.83,408.503,34.89249,0,0,0,0,100,0),
(@PATH,2,-9934.89,375.823,35.15996,0,0,0,0,100,0),
(@PATH,3,-9905.29,378.352,35.28614,0,0,0,0,100,0),
(@PATH,4,-9889.87,404.354,35.3951,0,0,0,0,100,0),
(@PATH,5,-9911.25,423.392,35.39784,0,0,0,0,100,0);
-- 0x203CC80000005280003C9800004BCA0D .go xyz -9946.83 408.503 34.89249
-- --------------------------------------------------------------------
-- DB/TSC: added pathing for most of the Stonecore trash npc's
-- Pathing for  Entry: 42810 'TDB FORMAT' 
SET @NPC := 340551;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1181.825,`position_y`=1069.069,`position_z`=264.2993 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1181.825,1069.069,264.2993,0,0,0,0,100,0),
(@PATH,2,1183.867,1087.719,263.8982,0,0,0,0,100,0),
(@PATH,3,1187.34,1063.681,263.3675,0,0,0,0,100,0),
(@PATH,4,1187.34,1063.681,263.3675,5.602507,6000,0,0,100,0),
(@PATH,5,1156.91,1047.903,265.4753,0,0,0,0,100,0);
-- 0x2030A45AA029CE8000298500002EC493 .go xyz 1181.825 1069.069 264.2993

-- Pathing for  Entry: 42810 'TDB FORMAT' 
SET @NPC := 340513;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1117.345,`position_y`=1014.186,`position_z`=266.6829 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1117.345,1014.186,266.6829,0,0,0,0,100,0),
(@PATH,2,1136.958,1026.087,267.018,0,0,0,0,100,0),
(@PATH,3,1117.345,1014.186,266.6829,0,0,0,0,100,0),
(@PATH,4,1091.625,992.7847,264.373,0,0,0,0,100,0),
(@PATH,5,1069.092,963.934,260.1193,0,0,0,0,100,0),
(@PATH,6,1091.625,992.7847,264.373,0,0,0,0,100,0);
-- 0x2030A45AA029CE800029850000AEC493 .go xyz 1117.345 1014.186 266.6829

-- Pathing for  Entry: 42810 'TDB FORMAT' 
SET @NPC := 340516;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1150.245,`position_y`=929.8108,`position_z`=284.7753 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1150.245,929.8108,284.7753,0,0,0,0,100,0),
(@PATH,2,1149.689,946.9427,283.7964,0,0,0,0,100,0),
(@PATH,3,1152.821,963.9549,282.9501,0,0,0,0,100,0),
(@PATH,4,1160.462,974.0677,279.9007,0,0,0,0,100,0),
(@PATH,5,1170.483,995.6285,273.9234,0,0,0,0,100,0),
(@PATH,6,1163.292,1017.347,269.8757,0,0,0,0,100,0),
(@PATH,7,1170.483,995.6285,273.9234,0,0,0,0,100,0),
(@PATH,8,1160.508,974.1669,279.8546,0,0,0,0,100,0),
(@PATH,9,1152.821,963.9549,282.9501,0,0,0,0,100,0),
(@PATH,10,1149.689,946.9427,283.7964,0,0,0,0,100,0);
-- 0x2030A45AA029CE8000298500012EC493 .go xyz 1150.245 929.8108 284.7753

-- Pathing for  Entry: 42695 'TDB FORMAT' 
SET @NPC := 340694;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1550.526,`position_y`=1193.469,`position_z`=220.5685 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1550.526,1193.469,220.5685,0,0,0,0,100,0),
(@PATH,2,1543.656,1212.661,223.2393,0,0,0,0,100,0),
(@PATH,3,1563.814,1178.012,218.4005,0,0,0,0,100,0),
(@PATH,4,1574.295,1151.352,216.1228,0,0,0,0,100,0),
(@PATH,5,1567.819,1105.63,215.8223,0,0,0,0,100,0),
(@PATH,6,1573.047,1131.243,215.7169,0,0,0,0,100,0),
(@PATH,7,1570.785,1160.727,216.7745,0,0,0,0,100,0),
(@PATH,8,1557.627,1183.724,219.0554,0,0,0,0,100,0);
-- 0x2030A45AA029B1C000298500002EC493 .go xyz 1550.526 1193.469 220.5685

-- Pathing for  Entry: 42695 'TDB FORMAT' 
SET @NPC := 340711;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1546.345,`position_y`=1159.319,`position_z`=216.7407 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1546.345,1159.319,216.7407,0,0,0,0,100,0),
(@PATH,2,1547.222,1147.325,216.423,0,0,0,0,100,0),
(@PATH,3,1547.339,1128.038,216.3325,0,0,0,0,100,0),
(@PATH,4,1544.799,1114.207,216.3325,0,0,0,0,100,0),
(@PATH,5,1540.96,1106.8,216.3931,0,0,0,0,100,0),
(@PATH,6,1544.799,1114.207,216.3325,0,0,0,0,100,0),
(@PATH,7,1547.339,1128.038,216.3325,0,0,0,0,100,0),
(@PATH,8,1547.222,1147.325,216.423,0,0,0,0,100,0);
-- 0x2030A45AA029B1C000298500002EC494 .go xyz 1546.345 1159.319 216.7407

-- Pathing for  Entry: 42695 'TDB FORMAT' 
SET @NPC := 340654;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1442.42,`position_y`=1189.29,`position_z`=230.9655 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1442.42,1189.29,230.9655,3.682645,7000,0,0,100,0),
(@PATH,2,1460.662,1197.037,230.4427,0,0,0,0,100,0),
(@PATH,3,1455.39,1211.3,230.9601,0,0,0,0,100,0),
(@PATH,4,1448.73,1220.99,231.6259,0,0,0,0,100,0),
(@PATH,5,1444.97,1202.81,229.8786,0,0,0,0,100,0);
-- 0x2030A45AA029B1C00029850000AEC493 .go xyz 1442.42 1189.29 230.9655

-- Pathing for  Entry: 42695 'TDB FORMAT' 
SET @NPC := 340712;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1566.243,`position_y`=1120.368,`position_z`=215.719 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1566.243,1120.368,215.719,0,0,0,0,100,0),
(@PATH,2,1582.618,1117.285,216.2138,0,0,0,0,100,0),
(@PATH,3,1566.243,1120.368,215.719,0,0,0,0,100,0),
(@PATH,4,1574.88,1117.925,215.7319,0,0,0,0,100,0),
(@PATH,5,1553.618,1124.535,216.3345,0,0,0,0,100,0),
(@PATH,6,1541.175,1130.726,216.3325,0,0,0,0,100,0),
(@PATH,7,1566.243,1120.368,215.719,0,0,0,0,100,0),
(@PATH,8,1582.618,1117.285,216.2138,0,0,0,0,100,0),
(@PATH,9,1592.052,1115.46,216.2268,0,0,0,0,100,0),
(@PATH,10,1574.88,1117.925,215.7319,0,0,0,0,100,0);
-- 0x2030A45AA029B1C00029850000AEC494 .go xyz 1566.243 1120.368 215.719

-- Pathing for  Entry: 42692 'TDB FORMAT' 
SET @NPC := 340678;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1288.18,`position_y`=1081.26,`position_z`=212.5155 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1288.18,1081.26,212.5155,4.502949,6000,0,0,100,0),
(@PATH,2,1322.95,1068.75,212.3748,0,0,0,0,100,0),
(@PATH,3,1349.6,1069.2,212.994,0,0,0,0,100,0),
(@PATH,4,1377.69,1068.29,213.098,0,0,0,0,100,0),
(@PATH,5,1404.79,1059.38,212.7177,0,0,0,0,100,0),
(@PATH,6,1386.41,1114.62,212.7551,0,0,0,0,100,0),
(@PATH,7,1356.41,1123.34,213.0578,0,0,0,0,100,0),
(@PATH,8,1335.37,1119.48,213.1407,0,0,0,0,100,0),
(@PATH,9,1313.96,1102.96,212.944,0,0,0,0,100,0);
-- 0x2030A45AA029B10000298500002EC493 .go xyz 1288.18 1081.26 212.5155

-- Pathing for  Entry: 42692 'TDB FORMAT' 
SET @NPC := 340693;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1539.342,`position_y`=1085.764,`position_z`=215.9438 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1539.342,1085.764,215.9438,0,0,0,0,100,0),
(@PATH,2,1553.276,1097.672,215.7756,0,0,0,0,100,0),
(@PATH,3,1554.925,1169.472,216.6244,0,0,0,0,100,0),
(@PATH,4,1562.587,1147.788,215.7576,0,0,0,0,100,0);
-- 0x2030A45AA029B10000298500002EC494 .go xyz 1539.342 1085.764 215.9438

-- Pathing for  Entry: 42692 'TDB FORMAT' 
SET @NPC := 340719;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1554.5,`position_y`=1069.16,`position_z`=217.8835 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1554.5,1069.16,217.8835,0,18000,0,0,100,0),
(@PATH,2,1530.8,1100.64,216.442,0,18000,0,0,100,0);
-- 0x2030A45AA029B1000029850000AEC493 .go xyz 1554.5 1069.16 217.8835

-- Pathing for  Entry: 42692 'TDB FORMAT' 
SET @NPC := 340732;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1585.593,`position_y`=1096.939,`position_z`=216.8126 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1585.593,1096.939,216.8126,0,0,0,0,100,0),
(@PATH,2,1593.496,1103.934,216.6328,0,0,0,0,100,0),
(@PATH,3,1593.496,1103.934,216.6328,0.549201,500,0,0,100,0);
-- 0x2030A45AA029B10000298500012EC493 .go xyz 1585.593 1096.939 216.8126
-- ---------------------------------------------------------------------
