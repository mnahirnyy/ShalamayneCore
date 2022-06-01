-- "Dark Whispers" Artifact Scenario
DELETE FROM `scenarios` WHERE `map` = '1498' AND `scenario_A`='1097';
INSERT INTO `scenarios` (`map`, `difficulty`, `scenario_A`, `scenario_H`) VALUES
('1498', '17', '1097', '1097');
UPDATE `gameobject_template` SET `type`='10', `displayId`='12983', `size`='1.25', `Data10`='210920', `Data22`= '39995', `Data23`=1 WHERE `entry`='249813';
DELETE FROM `spell_script_names` WHERE `spell_id`=210920;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES ('210920', 'spell_teleport_felsoul_hold');
/* Dark Whispers Scenario spawns */
SET @CGUID := 280001210;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+36;
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `unit_flags2`, `unit_flags3`, `dynamicflags`, `ScriptName`, `VerifiedBuild`) VALUES
(@CGUID+0,106646,1498,7637,7768,12,0,282,0,-1,0,0,1054.39,4964.27,43.4807,5.97269,900,0,0,0,1039267,0,0,0,0,0,0,'',25549), -- Dreadguard Sentry (Flame Charge 170067, Flame Charge 170068, Flamelash 170080)
(@CGUID+1,106687,1498,7637,7768,12,0,282,0,-1,0,0,1052.38,4959.56,43.5768,6.01981,900,0,0,665131,1100000,0,0,0,0,0,0,'',25549), -- Eredar Soul Binder (Fel Gravity Well 217809, Fel Storm 206564)
(@CGUID+2,106646,1498,7637,7768,12,0,282,0,-1,0,0,1117.12,4971.23,49.8437,0.443479,900,0,0,1039267,0,0,0,0,0,0,0,'',25549), -- Dreadguard Sentry (Flame Charge 170067, Flame Charge 170068, Flamelash 170080)
(@CGUID+3,106657,1498,7637,7768,12,0,282,0,-1,0,0,1120.02,4963.38,49.725,0.573069,900,0,0,1039267,0,0,0,0,0,0,0,'',25549), -- Wrathguard Hellblade (Dread Blades 201027, Flurry 204082)
(@CGUID+5,106811,1498,7637,7768,12,0,282,0,-1,0,0,1204.3,4979.39,57.6364,2.21948,900,0,0,2494242,1100000,0,0,0,0,0,0,'',25549), -- Mephistroth
(@CGUID+7,106693,1498,7637,7768,12,0,282,0,-1,0,0,1004.36,4931.7,38.2676,0.442167,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Thal'kiel
(@CGUID+8,106652,1498,7637,7768,12,0,282,0,-1,0,0,998.981,4920.24,36.3607,1.12745,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Mephistroth (Mind Blast 196944)
(@CGUID+9,106783,1498,7637,7768,12,0,282,0,-1,0,0,1175.74,5069.89,58.257,2.27231,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Fel Creep
(@CGUID+10,106647,1498,7637,7768,12,0,282,0,-1,0,0,1270.59,5057.21,74.2907,3.4144,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Dreadflame Swarmer (Bloodletting Bite 166347, Fel Spit 211311)
(@CGUID+11,106647,1498,7637,7768,12,0,282,0,-1,0,0,1151.48,4931.98,71.0787,0,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Dreadflame Swarmer (Bloodletting Bite 166347, Fel Spit 211311)
(@CGUID+12,106647,1498,7637,7768,12,0,282,0,-1,0,0,1147.03,4911.99,70.7998,0,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Dreadflame Swarmer (Bloodletting Bite 166347, Fel Spit 211311)
(@CGUID+13,106647,1498,7637,7768,12,0,282,0,-1,0,0,1141.56,4922.86,60.9749,0,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Dreadflame Swarmer (Bloodletting Bite 166347, Fel Spit 211311)
(@CGUID+14,106783,1498,7637,7768,12,0,282,0,-1,0,0,1151.37,5032.54,53.3217,2.27231,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Fel Creep
(@CGUID+15,106783,1498,7637,7768,12,0,282,0,-1,0,0,1159.54,5047.11,56.0956,2.27231,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Fel Creep
(@CGUID+16,106783,1498,7637,7768,12,0,282,0,-1,0,0,1155.6,5061.11,57.8158,5.41687,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Fel Creep
(@CGUID+17,106647,1498,7637,7768,12,0,282,0,-1,0,0,1247.49,5053.21,70.1041,0,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Dreadflame Swarmer (Bloodletting Bite 166347, Fel Spit 211311)
(@CGUID+18,106698,1498,7637,7768,12,0,282,0,-1,0,0,1069.51,5127.47,57.3847,3.01127,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Eredar Doomweaver (Fel Fireball 202295, Fel Flamestrike 238677)
(@CGUID+19,106698,1498,7637,7768,12,0,282,0,-1,0,0,1065.45,5148.29,58.3317,3.68506,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Eredar Doomweaver (Fel Fireball 202295, Fel Flamestrike 238677)
(@CGUID+20,106693,1498,7637,7768,12,0,282,0,-1,0,0,1053.67,5129.77,61.3745,6.21348,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Thal'kiel
(@CGUID+21,106698,1498,7637,7768,12,0,282,0,-1,0,0,1053.93,5111.1,57.0739,2.16075,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Eredar Doomweaver (Fel Fireball 202295, Fel Flamestrike 238677)
(@CGUID+22,106783,1498,7637,7768,12,0,282,0,-1,0,0,1169.43,5059.16,57.1509,1.06266,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Fel Creep
(@CGUID+23,106647,1498,7637,7768,12,0,282,0,-1,0,0,1259.53,5034.89,78.6137,0,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Dreadflame Swarmer (Bloodletting Bite 166347, Fel Spit 211311)
(@CGUID+24,106658,1498,7637,7768,12,0,282,0,-1,0,0,1185.23,5255.81,79.1498,0.124193,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Wyrmtongue Servant (Putrid Jar 188039, Retched Belch 197735)
(@CGUID+25,106660,1498,7637,7768,12,0,282,0,-1,0,0,1113.9,5159.39,63.2106,1.12628,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Fel Mongrel (Helbite 198603)
(@CGUID+26,106658,1498,7637,7768,12,0,282,0,-1,0,0,1144.45,5205.47,69.7158,6.23565,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Wyrmtongue Servant (Putrid Jar 188039, Retched Belch 197735)
(@CGUID+27,106658,1498,7637,7768,12,0,282,0,-1,0,0,1136.33,5217.99,69.2413,4.20799,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Wyrmtongue Servant (Putrid Jar 188039, Retched Belch 197735)
(@CGUID+28,106660,1498,7637,7768,12,0,282,0,-1,0,0,1094.8,5172.84,62.0235,0.260655,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Fel Mongrel (Helbite 198603)
(@CGUID+29,106657,1498,7637,7768,12,0,282,0,-1,0,0,1093.52,5167.2,61.1212,0.342257,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Wrathguard Hellblade (Dread Blades 201027, Flurry 204082)
(@CGUID+30,106658,1498,7637,7768,12,0,282,0,-1,0,0,1133.7,5214.18,69.0359,0.725886,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Wyrmtongue Servant (Putrid Jar 188039, Retched Belch 197735)
(@CGUID+31,106660,1498,7637,7768,12,0,282,0,-1,0,0,1122.16,5159.75,65.017,2.31133,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Fel Mongrel (Helbite 198603)
(@CGUID+32,106657,1498,7637,7768,12,0,282,0,-1,0,0,1116.46,5154.81,63.4179,1.20789,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Wrathguard Hellblade (Dread Blades 201027, Flurry 204082)
(@CGUID+33,106789,1498,7637,7768,12,0,282,0,-1,0,0,1215.62,5065.52,57.2834,3.12875,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Hellfire Gun
(@CGUID+34,106660,1498,7637,7768,12,0,282,0,-1,0,0,1096.85,5164.43,61.3647,0.795235,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Fel Mongrel (Helbite 198603)
(@CGUID+35,106789,1498,7637,7768,12,0,282,0,-1,0,0,1177.42,4985.1,55.2302,1.84963,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Hellfire Gun
(@CGUID+36,106789,1498,7637,7768,12,0,282,0,-1,0,0,1214.39,5047.83,57.941,3.17993,900,0,0,0,0,0,0,0,0,0,0,'',25549); -- Hellfire Gun
SET @OGUID := 51014710;
DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+29;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `isActive`, `ScriptName`, `VerifiedBuild`) VALUES
(@OGUID+0,249792,1498,7637,7768,12,0,282,0,-1,1153.96,5213.09,71.0694,5.37724,0,0,0,1,7200,255,0,1,'',22423), -- Loot Stack
(@OGUID+1,249785,1498,7637,7768,12,0,282,0,-1,1090.31,5238.9,75.2302,5.9602,0,0,0,1,7200,255,0,1,'',22423), -- Fel Pool
(@OGUID+2,249802,1498,7637,7768,12,0,282,0,-1,1126.49,5139.75,93.6947,1.14722,0,0,0,1,7200,255,0,1,'',22423), -- Wall Chains
(@OGUID+3,249795,1498,7637,7768,12,0,282,0,-1,1134.24,5134.76,66.1277,4.45029,0,0,0,1,7200,255,0,1,'',22423), -- Wall Segment
(@OGUID+4,249794,1498,7637,7768,12,0,282,0,-1,1116.38,5144.31,60.7557,0.581167,0,0,0,1,7200,255,0,1,'',22423), -- Wall Segment
(@OGUID+5,249807,1498,7637,7768,12,0,282,0,-1,1053.71,5129.88,57.1822,6.01918,0,0,0,1,7200,255,0,1,'',22423), -- Rune
(@OGUID+6,249789,1498,7637,7768,12,0,282,0,-1,1134.01,5225.02,70.1337,0,0,0,0,1,7200,255,0,1,'',22423), -- Legion Cage Tower
(@OGUID+7,243492,1498,7637,7768,12,0,282,0,-1,1166.4,4983.57,53.8423,0.355701,0,0,0,1,7200,255,0,1,'',22423), -- Fel Wall
(@OGUID+8,249784,1498,7637,7768,12,0,282,0,-1,1175.77,5231.35,76.051,2.37016,0,0,0,1,7200,255,0,1,'',22423), -- Legion Wall
(@OGUID+9,249793,1498,7637,7768,12,0,282,0,-1,1147.44,5206.41,70.6657,5.80756,0,0,0,1,7200,255,0,1,'',22423), -- Loot Stack - Weapons
(@OGUID+10,243492,1498,7637,7768,12,0,282,0,-1,1152.92,5000.87,53.8766,1.04823,0,0,0,1,7200,255,0,1,'',22423), -- Fel Wall
(@OGUID+11,249787,1498,7637,7768,12,0,282,0,-1,1084.2,5249.18,77.5703,5.71868,0,0,0,1,7200,255,0,1,'',22423), -- Pillar
(@OGUID+12,249792,1498,7637,7768,12,0,282,0,-1,1147.29,5205.19,70.6657,1.09798,0,0,0,1,7200,255,0,1,'',22423), -- Loot Stack
(@OGUID+13,249790,1498,7637,7768,12,0,282,0,-1,1153.37,5213.98,69.8732,6.22403,0,0,0,1,7200,255,0,1,'',22423), -- Loot Platform
(@OGUID+14,249779,1498,7637,7768,12,0,282,0,-1,1019.82,5135.91,68.2981,6.05009,0,0,0,1,7200,255,0,1,'',22423), -- Legion Gates
(@OGUID+15,249783,1498,7637,7768,12,0,282,0,-1,1263.82,5235.14,92.732,5.6493,0,0,0,1,7200,255,0,0,'',22423), -- Legion Portal
(@OGUID+16,249793,1498,7637,7768,12,0,282,0,-1,1154.7,5213.64,71.0345,3.02032,0,0,0,1,7200,255,0,1,'',22423), -- Loot Stack - Weapons
(@OGUID+17,249802,1498,7637,7768,12,0,282,0,-1,1059.33,5176.26,81.5661,3.43203,0,0,0,1,7200,255,0,1,'',22423), -- Wall Chains
(@OGUID+18,249800,1498,7637,7768,12,0,282,0,-1,1101.71,5156.11,101.935,4.09064,0,0,0,1,7200,255,0,1,'',22423), -- Wall Chains
(@OGUID+19,243492,1498,7637,7768,12,0,282,0,-1,1109.82,5003.1,55.0368,1.06916,0,0,0,1,7200,255,0,1,'',22423), -- Fel Wall
(@OGUID+20,249790,1498,7637,7768,12,0,282,0,-1,1147.5,5205.25,69.4982,1.08961,0,0,0,1,7200,255,0,1,'',22423), -- Loot Platform
(@OGUID+21,249784,1498,7637,7768,12,0,282,0,-1,1191.61,5243.75,78.6104,1.55658,0,0,0,1,7200,255,0,1,'',22423), -- Legion Wall
(@OGUID+22,249784,1498,7637,7768,12,0,282,0,-1,1107.43,5195.99,65.7785,6.11784,0,0,0,1,7200,255,0,1,'',22423), -- Legion Wall
(@OGUID+23,249792,1498,7637,7768,12,0,282,0,-1,1148.47,5205.56,70.6657,5.37724,0,0,0,1,7200,255,0,1,'',22423), -- Loot Stack
(@OGUID+24,249794,1498,7637,7768,12,0,282,0,-1,1065.23,5168.92,49.7826,0.961022,0,0,0,1,7200,255,0,1,'',22423), -- Wall Segment
(@OGUID+25,249798,1498,7637,7768,12,0,282,0,-1,1054.84,5186.01,53.322,3.98278,0,0,0,1,7200,255,0,1,'',22423), -- Wall Segment
(@OGUID+26,243490,1498,7637,7768,12,0,282,0,-1,1134.25,5079.54,59.1818,2.53077,0,0,0,1,7200,255,0,1,'',22423), -- Wall Fel
(@OGUID+27,249791,1498,7637,7768,12,0,282,0,-1,1152.89,5215.41,70.9794,2.08113,0,0,0,1,7200,255,0,1,'',22423), -- Fel Chest
(@OGUID+28,249791,1498,7637,7768,12,0,282,0,-1,1146.2,5205.34,70.6657,2.69802,0,0,0,1,7200,255,0,1,'',22423), -- Fel Chest
(@OGUID+29,249791,1498,7637,7768,12,0,282,0,-1,1148.46,5204.39,70.6657,1.06244,0,0,0,1,7200,255,0,1,'',22423); -- Fel Chest
DELETE FROM `gameobject_template` WHERE `entry` IN (249792, 249785, 249802, 249795, 249794, 249807, 249789, 243492, 249784, 249793, 249787, 249790, 249779, 249783, 249800, 249798, 243490, 249791);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `Data24`, `Data25`, `Data26`, `Data27`, `Data28`, `Data29`, `Data30`, `Data31`, `Data32`, `RequiredLevel`, `ScriptName`, `VerifiedBuild`) VALUES
(249792, 5, 14901, 'Loot Stack', '', '', '', 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 23420), -- Loot Stack
(249785, 5, 30755, 'Fel Pool', '', '', '', 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 23420), -- Fel Pool
(249802, 5, 33689, 'Wall Chains', '', '', '', 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 23420), -- Wall Chains
(249795, 5, 32781, 'Wall Segment', '', '', '', 1.5, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 23420), -- Wall Segment
(249794, 5, 31790, 'Wall Segment', '', '', '', 1.5, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 23420), -- Wall Segment
(249807, 5, 30992, 'Rune', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 23420), -- Rune
(249789, 5, 33183, 'Legion Cage Tower', '', '', '', 0.8, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 23420), -- Legion Cage Tower
(243492, 0, 26055, 'Fel Wall', '', '', '', 0.85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 23420), -- Fell Wall
(249784, 5, 27616, 'Legion Wall', '', '', '', 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 23420), -- Legion Wall
(249793, 5, 33684, 'Loot Stack - Weapons', '', '', '', 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 23420), -- Loot Stack - Weapons
(249787, 5, 31146, 'Pillar', '', '', '', 0.75, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 23420), -- Pillar
(249790, 5, 29815, 'Loot Platform', '', '', '', 0.8, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 23420), -- Loot Platform
(249779, 43, 30511, 'Legion Gates', '', '', '', 3, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 23420), -- Legion Gates
(249783, 5, 29634, 'Legion Portal', '', '', '', 1.5, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 23420), -- Legion Portal
(249800, 5, 31445, 'Wall Chains', '', '', '', 1.25, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 23420), -- Wall Chains
(249798, 5, 31790, 'Wall Segment', '', '', '', 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 23420), -- Wall Segment
(243490, 0, 26055, 'Wall Fel', '', '', '', 0.65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 23420), -- Wall Fel
(249791, 5, 33263, 'Fel Chest', '', '', '', 1.5, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 23420); -- Fel Chest
-- Dreadguard Sentry 106646
UPDATE `creature_template` SET `lootid`=106646, `AIName`="SmartAI", `minlevel`=98, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32768, `HealthModifier`=1 WHERE `entry`=106646;
DELETE FROM `smart_scripts` WHERE `entryorguid`=106646 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(106646,0,0,0,0,0,100,0,5000,8000,12000,15000,11,170080,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dreadguard Sentry - In Combat - Cast 'Flamelash'"),
(106646,0,1,0,0,0,100,0,2000,5000,3000,5000,11,170067,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dreadguard Sentry - In Combat - Cast 'Flame Charge'"),
(106646,0,2,5,6,0,100,1,0,0,0,0,45,1,1,0,0,0,0,19,99739,100,0,0,0,0,0,'Dreadguard Sentry - On Death - Send Data'),
(106646,0,3,0,61,0,100,1,0,0,0,0,205,92,50960,0,0,0,0,7,0,0,0,0,0,0,0,'Dreadguard Sentry - Link - Complete Scenario Criteria');
DELETE FROM `creature_equip_template` WHERE `CreatureID`=106646;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(106646,1,111354,0,0,0,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=106646;
-- Eredar Soul Binder 106687 (Fel Gravity Well 217809, Fel Storm 206564)
UPDATE `creature_template` SET `lootid`=106687, `AIName`="SmartAI", `minlevel`=98, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32768, `HealthModifier`=1 WHERE `entry`=106687;
DELETE FROM `smart_scripts` WHERE `entryorguid`=106687 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(106687,0,0,0,0,0,100,0,5000,8000,10000,12000,11,206564,0,0,0,0,0,2,0,0,0,0,0,0,0,"Eredar Soul Binder - In Combat - Cast 'Fel Storm'"),
(106687,0,1,0,0,0,100,0,2000,5000,3000,5000,11,183345,0,0,0,0,0,1,0,0,0,0,0,0,0,"Eredar Soul Binder - In Combat - Cast 'Fel Gravity Well'"),
(106687,0,2,5,6,0,100,1,0,0,0,0,45,1,1,0,0,0,0,19,99739,100,0,0,0,0,0,'Eredar Soul Binder - On Death - Send Data'),
(106687,0,3,0,61,0,100,1,0,0,0,0,205,92,50960,0,0,0,0,7,0,0,0,0,0,0,0,'Eredar Soul Binder - Link - Complete Scenario Criteria'),
(106687,0,4,0,6,0,100,1,0,0,0,0,45,3,3,0,0,0,0,19,99739,100,0,0,0,0,0,'Eredar Soul Binder - On Death - Send Data');
DELETE FROM `creature_equip_template` WHERE `CreatureID`=106687;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(106687,1,55064,0,0,127347,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=106687;
-- Wrathguard Hellblade 106657 (Dread Blades 201027, Flurry 204082)
UPDATE `creature_template` SET `lootid`=106657, `AIName`="SmartAI", `minlevel`=98, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32768, `HealthModifier`=1 WHERE `entry`=106657;
DELETE FROM `smart_scripts` WHERE `entryorguid`=106657 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(106657,0,0,0,0,0,100,0,5000,8000,10000,12000,11,204082,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wrathguard Hellblade - In Combat - Cast 'Flurry'"),
(106657,0,1,0,0,0,100,0,2000,5000,3000,5000,11,201027,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wrathguard Hellblade - In Combat - Cast 'Dread Blades'"),
(106657,0,4,5,6,0,100,1,0,0,0,0,45,2,2,0,0,0,0,19,99739,100,0,0,0,0,0,'Wrathguard Hellblade - On Death - Send Data'),
(106657,0,5,0,61,0,100,1,0,0,0,0,205,92,50960,0,0,0,0,7,0,0,0,0,0,0,0,'Wrathguard Hellblade - Link - Complete Scenario Criteria'),
(106657,0,6,0,6,0,100,1,0,0,0,0,45,3,3,0,0,0,0,19,99739,100,0,0,0,0,0,'Wrathguard Hellblade - On Death - Send Data');
DELETE FROM `creature_equip_template` WHERE `CreatureID`=106657;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(106657,1,132920,0,0,132920,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=106657;
-- Wild Imps 99739
UPDATE `creature_template` SET `lootid`=99739, `AIName`="SmartAI", `minlevel`=98, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `HealthModifier`=1 WHERE `entry`=99739;
-- Fel Creep 106783
UPDATE `creature_template` SET `lootid`=106783, `AIName`="SmartAI", `minlevel`=98, `maxlevel`=100, `faction`=35, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=1 WHERE `entry`=106783;
DELETE FROM `smart_scripts` WHERE `entryorguid`=106783 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(106783,0,0,0,60,0,100,1,0,0,0,0,11,194073,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fel Creep - Event Update - Cast Spell');
-- Dreadflame Swarmer 106647 (Bloodletting Bite 166347, Fel Spit 211311)
UPDATE `creature_template` SET `lootid`=106647, `AIName`="SmartAI", `minlevel`=98, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32768, `HealthModifier`=1 WHERE `entry`=106647;
DELETE FROM `smart_scripts` WHERE `entryorguid`=106647 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(106647,0,0,0,0,0,100,0,5000,8000,12000,15000,11,211311,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felsoul Stalker - In Combat - Cast 'Fel Spit'"),
(106647,0,1,0,0,0,100,0,10000,10000,10000,25000,11,166347,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felsoul Stalker - In Combat - Cast 'Bloodletting Bite''");
-- Eredar Doomweaver 106698 (Fel Fireball 202295, Fel Flamestrike 238677)
UPDATE `creature_template` SET `lootid`=106698, `AIName`="SmartAI", `minlevel`=98, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=1 WHERE `entry`=106698;
DELETE FROM `smart_scripts` WHERE `entryorguid`=106698 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(106698,0,0,0,0,0,100,0,5000,8000,10000,12000,11,202277,0,0,0,0,0,2,0,0,0,0,0,0,0,"Eredar Doomweaver - In Combat - Cast 'Fel Flamestrike'"),
(106698,0,1,0,0,0,100,0,2000,5000,3000,5000,11,202295,0,0,0,0,0,1,0,0,0,0,0,0,0,"Eredar Doomweaver - In Combat - Cast 'el Fireball'");
DELETE FROM `creature_equip_template` WHERE `CreatureID`=106698;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(106698,1,75010,0,0,127580,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=106698;
-- Wyrmtongue Servant 106658 (Putrid Jar 188039, Retched Belch 197735)
UPDATE `creature_template` SET `lootid`=106658, `AIName`="SmartAI", `minlevel`=98, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=1 WHERE `entry`=106658;
DELETE FROM `smart_scripts` WHERE `entryorguid`=106658 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(106658,0,0,1,10,0,100,1,1,15,25000,25000,1,0,10000,0,0,0,0,18,15,0,0,0,0,0,0,"Wyrmtongue Servant - Within 1-15 Range Out of Combat LoS - Say Line 0 (No Repeat)"),
(106658,0,1,0,0,0,100,0,5000,8000,12000,15000,11,188039,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wyrmtongue Servant - In Combat - Cast 'Putrid Jar'"),
(106658,0,2,0,0,0,100,0,10000,12000,18000,22000,11,197735,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wyrmtongue Servant - In Combat - Cast 'Retched Belch'");
DELETE FROM `creature_text` WHERE `CreatureID` = 106658;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(106658, 0, 0, 'An intruder! I must warn the others!', 14, 0, 100, 0, 0, 62316, 0, 0, 'Pain Mistress Nikta to Player');
-- Fel Mongrel 106660 (Helbite 198603)
UPDATE `creature_template` SET `lootid`=106660, `AIName`="SmartAI", `minlevel`=98, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=0.5 WHERE `entry`=106660;
DELETE FROM `smart_scripts` WHERE `entryorguid`=106660 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(106660,0,0,0,0,0,100,0,0,0,5000,5000,11,198603,0,0,0,0,0,2,0,0,0,0,0,0,0,"Fel Mongrel - In Combat - Cast 'Felbite'");
-- Hellfire Gun 106789
UPDATE `creature_template` SET `lootid`=106789, `AIName`="SmartAI", `minlevel`=98, `maxlevel`=100, `faction`=35, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `HealthModifier`=1 WHERE `entry`=106789;
-- Mephistroth 106652 (Mind Blast 196944)
UPDATE `creature_template` SET `lootid`=106652, `AIName`="", `ScriptName`='npc_mephistroth_106652', `minlevel`=100, `maxlevel`=101, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=2.0 WHERE `entry`=106652;
DELETE FROM `creature_equip_template` WHERE `CreatureID`=106652;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(106652,1,106693,0,0,212497,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=106652;
DELETE FROM `creature_text` WHERE `CreatureID` = 106652;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(106652, 0, 0, 'I grow tired of your interference! DIE!', 14, 0, 100, 0, 0, 62329, 0, 0, 'Mephistroth to to Player'),
(106652, 1, 0, 'Enjoy your victory while you can, warlock. This isn\'t over between us. It has only begun!', 14, 0, 100, 0, 0, 62325, 0, 0, 'Mephistroth to Player');
-- Mephistroth 106692 (Bunny1)
UPDATE `creature_template` SET `lootid`=106692, `unit_flags`=32832, `AIName`="", `ScriptName`='npc_mephistroth_106692', `minlevel`=100, `maxlevel`=100, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `HealthModifier`=1.0 WHERE `entry`=106692;
DELETE FROM `creature_text` WHERE `CreatureID` = 106692;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(106692, 0, 0, 'Foolish warlock! Did you really think I would remain unaware of your infantile plot to steal my treasure? You underestimate the Nathrezim!', 12, 0, 100, 0, 0, 62314, 0, 0, 'Mephistroth to to Player'),
(106692, 1, 0, 'As for you, treacherous skull. I''ll deal with you later.', 12, 0, 100, 0, 0, 62317, 0, 0, 'Mephistroth to to Player'),
(106692, 2, 0, 'Come to me, servant of hellfire! Rid me of this uninvited guest.', 12, 0, 100, 0, 0, 62319, 0, 0, 'Mephistroth to to Player');
-- Mephistroth 106811 (Bunny2)
UPDATE `creature_template` SET `lootid`=106811, `AIName`="", `ScriptName`='npc_mephistroth_106811', `minlevel`=100, `maxlevel`=101, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `HealthModifier`=1.0 WHERE `entry`=106811;
DELETE FROM `creature_text` WHERE `CreatureID` = 106811;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(106811, 0, 0, 'Fire the guns! Cover the path in Hellfire! Don\'t let that Warlock through!', 14, 0, 100, 0, 0, 62321, 0, 0, 'Mephistroth to to Player'),
(106811, 1, 0, 'Your persistence will be the death of you! Minions, attack!', 12, 0, 100, 0, 0, 62323, 0, 0, 'Mephistroth to Player');
-- Felborn Overfiend 106644 (Fel Blast 217802 Fel Sear 217804, Felflame Shield 217806)
UPDATE `creature_template` SET `lootid`=106644, `AIName`="SmartAI", `minlevel`=98, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32768, `HealthModifier`=1 WHERE `entry`=106644;
DELETE FROM `smart_scripts` WHERE `entryorguid`=106644 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(106644,0,0,0,54,0,100,1,0,0,0,0,49,0,0,0,0,0,0,21,50,0,0,0,0,0,0,'Just Summoned - Attack Start'),
(106644,0,1,0,0,0,100,0,5000,8000,5000,10000,11,217804,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felborn Overfiend - In Combat - Cast 'Fel Sear'"),
(106644,0,2,0,0,0,100,0,2000,5000,3000,6000,11,217802,0,0,0,0,0,1,0,0,0,0,0,0,0,"Felborn Overfiend - In Combat - Cast 'Fel Blast'"),
(106644,0,3,0,6,0,100,0,0,0,0,0,9,0,0,0,0,0,0,15,243490,150,0,0,0,0,0,'On Death - Activate Gameobject');
-- Dreadfall Infernal 106958 (Blast Wave 212376 Blazing Hellfire 205258, Blazing Hellfire 205259)
UPDATE `creature_template` SET `lootid`=106958, `AIName`="SmartAI", `minlevel`=98, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32768, `HealthModifier`=1 WHERE `entry`=106958;
DELETE FROM `smart_scripts` WHERE `entryorguid`=106958 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(106958,0,0,0,0,0,100,0,5000,8000,10000,12000,11,205258,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dreadfall Infernal - In Combat - Cast 'Blazing Hellfire'"),
(106958,0,1,0,0,0,100,0,5000,8000,10000,12000,11,205259,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dreadfall Infernal - In Combat - Cast 'Blazing Hellfire'"),
(106958,0,2,0,0,0,100,0,2000,5000,3000,5000,11,212376,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dreadfall Infernal - In Combat - Cast 'Blast Wave'");
-- Lady Tyrana 106825 (Fel Gravity Well 217809, Fel Storm 206564)
UPDATE `creature_template` SET `lootid`=106825, `AIName`="SmartAI", `minlevel`=98, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32768, `HealthModifier`=1 WHERE `entry`=106825;
DELETE FROM `smart_scripts` WHERE `entryorguid`=106825 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(106825,0,0,0,0,0,100,0,5000,8000,10000,12000,11,217809,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lady Tyrana - In Combat - Cast 'Fel Gravity Well'"),
(106825,0,1,0,0,0,100,0,2000,5000,3000,5000,11,206564,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lady Tyrana - In Combat - Cast 'Fel Storm'");
DELETE FROM `creature_equip_template` WHERE `CreatureID`=106825;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(106825,1,115950,0,0,0,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=106825;
DELETE FROM `creature_text` WHERE `CreatureID` = 106825;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(106825, 0, 0, 'Playtime\'s over, mortal!', 14, 0, 100, 0, 0, 62330, 0, 0, 'Lady Tyranna to Player');
-- Pain Mistress Nikta 106827 (Chaotic Ablution 211631, Shadow Bolt 210014)
UPDATE `creature_template` SET `lootid`=106827, `AIName`="SmartAI", `minlevel`=98, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32768, `HealthModifier`=1 WHERE `entry`=106827;
DELETE FROM `smart_scripts` WHERE `entryorguid`=106827 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(106827,0,0,0,0,0,100,0,5000,8000,10000,12000,11,211631,0,0,0,0,0,2,0,0,0,0,0,0,0,"Pain Mistress Nikta - In Combat - Cast 'Chaotic Ablution'"),
(106827,0,1,0,0,0,100,0,2000,5000,3000,5000,11,210014,0,0,0,0,0,1,0,0,0,0,0,0,0,"Pain Mistress Nikta - In Combat - Cast 'Shadow Bolt'");
DELETE FROM `creature_equip_template` WHERE `CreatureID`=106827;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(106827,1,125647,0,0,0,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=106827;
DELETE FROM `creature_text` WHERE `CreatureID` = 106827;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(106827, 0, 0, 'Actually, sister, playtime has only begun!', 14, 0, 100, 0, 0, 62331, 0, 0, 'Pain Mistress Nikta to Player');
-- Thal'kiel
UPDATE `creature_template` SET `minlevel`=98, `maxlevel`=100 WHERE `entry`=106693;
-- go loot 249821 Skull of the Man'ari
DELETE FROM `gameobject_loot_template` WHERE `Entry` IN (249821, 65646);
INSERT INTO `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES 
(65646, 128943, 0, 100, 0, 1, 0, 1, 1, 'Skull of the Man\'ari');
DELETE FROM `gameobject_template` WHERE `Entry`= 249821;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `Data24`, `Data25`, `Data26`, `Data27`, `Data28`, `Data29`, `Data30`, `Data31`, `Data32`, `RequiredLevel`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES
(249821, 3, 180078, 'Skull of the Man\'ari', 'questinteract', 'Extract', '', 2.5, 1691, 65646, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23645, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 'go_skull_of_the_manari_249821', 26822);
DELETE FROM `gameobject_template_addon` WHERE `entry`=249821;
INSERT INTO `gameobject_template_addon` (`entry`, `faction`, `flags`) VALUES
(249821, 0, 2097152); -- Skull of the Man'ari
-- Creature Loot
DELETE FROM `creature_loot_template` WHERE `Entry` IN (106646, 106687, 106657, 106698, 106658, 106660, 106644, 106958, 106825, 106827);
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
/* Dreadguard Sentry 106646 */
(106646,132204,0,96,0,1,0,1,1,'Dreadguard Sentry: Sticky Volatile Substance'),
(106646,132199,0,4,0,1,0,1,1,'Dreadguard Sentry: Congealed Felblood'),
(106646,138781,0,2,0,1,0,1,1,'Dreadguard Sentry: Brief History of the Aeons'),
(106646,132200,0,0.07,0,1,0,1,1,'Dreadguard Sentry: Ashen Ring'),
/* Eredar Soul Binder 106687 */
(106687,132204,0,98,0,1,0,1,1,'Eredar Soul Binder: Sticky Volatile Substance'),
(106687,132199,0,2,0,1,0,1,1,'Eredar Soul Binder: Congealed Felblood'),
(106687,138781,0,0.3,0,1,0,1,1,'Eredar Soul Binder: Brief History of the Aeons'),
(106687,132231,0,1.8,0,1,0,1,1,'Eredar Soul Binder: Worn Hooked Claw'),
(106687,140225,0,0.03,0,1,0,1,1,'Eredar Soul Binder: Salvaged Armor'),
(106687,141035,0,0.06,1,1,0,1,1,'Eredar Soul Binder: Ashen Ring'),
/* Wrathguard Hellblade 106657 */
(106657,132204,0,96,0,1,0,1,1,'Wrathguard Hellblade: Sticky Volatile Substance'),
(106657,132199,0,4,0,1,0,1,1,'Wrathguard Hellblade: Congealed Felblood'),
(106657,132231,0,9,0,1,0,1,1,'Wrathguard Hellblade: Worn Hooked Claw'),
(106657,138781,0,0.01,0,1,0,1,1,'Wrathguard Hellblade: Brief History of the Aeons'),
(106657,138782,0,0.03,0,1,0,1,1,'Wrathguard Hellblade: Brief History of the Ages'),
(106657,132200,0,0.07,0,1,0,1,1,'Wrathguard Hellblade: Ashen Ring'),
(106657,153246,0,0.09,1,1,0,1,1,'Wrathguard Hellblade: Strangely-Flawed Gemstone'),
(106657,141035,0,0.03,1,1,0,1,1,'Wrathguard Hellblade: Technique: Glyph of Fel Wings'),
/* Eredar Doomweaver 106698 */
(106698,132204,0,98,0,1,0,1,1,'Eredar Doomweaver: Sticky Volatile Substance'),
(106698,132199,0,2,0,1,0,1,1,'Eredar Doomweaver: Congealed Felblood'),
(106698,132200,0,0.02,0,1,0,1,1,'Eredar Doomweaver: Ashen Ring'),
(106698,138781,0,0.12,0,1,0,1,1,'Eredar Doomweaver: Brief History of the Aeons'),
(106698,138782,0,0.02,0,1,0,1,1,'Eredar Doomweaver: Brief History of the Ages'),
(106698,153202,0,0.08,1,1,0,1,1,'Eredar Doomweaver: Argunite Cluster'),
(106698,141064,0,0.05,1,1,0,1,1,'Eredar Doomweaver: Technique Glyph of Shivarra'),
(106698,140222,0,0.05,1,1,0,1,1,'Eredar Doomweaver: Harvested Goods'),
(106698,140220,0,0.02,1,1,0,1,1,'Eredar Doomweaver: Scavenged Cloth'),
/* Wyrmtongue Servant 106658 */
(106658,132204,0,97,0,1,0,1,1,'Wyrmtongue Servant: Sticky Volatile Substance'),
(106658,132199,0,3,0,1,0,1,1,'Wyrmtongue Servant: Congealed Felblood'),
(106658,132200,0,0.06,0,1,0,1,1,'Wyrmtongue Servant: Ashen Ring'),
(106658,141064,0,0.03,1,1,0,1,1,'Wyrmtongue Servant: Technique Glyph of Shivarra'),
/* Fel Mongrel 106660 */
(106660,132204,0,5,0,1,0,1,1,'Fel Mongrel: Sticky Volatile Substance'),
(106660,132199,0,2,0,1,0,1,1,'Fel Mongrel: Congealed Felblood'),
(106660,132197,0,0.08,0,1,0,1,1,'Fel Mongrel: Fel Paw'),
(106660,138781,0,0.1,0,1,0,1,1,'Fel Mongrel: Brief History of the Aeons'),
(106660,132231,0,98,1,1,0,1,1,'Fel Mongrel: Worn Hooked Claw'),
(106660,141035,0,0.02,1,1,0,1,1,'Fel Mongrel: Technique: Glyph of Fel Wings'),
(106660,140227,0,0.01,1,1,0,1,1,'Fel Mongrel: Bloodhunters Quarry'),
(106660,144345,0,0.01,1,1,0,1,1,'Fel Mongrel: Pile of Pet Goodies'),
/* Felborn Overfiend 106644 */
(106644,132200,0,3,0,1,0,1,1,'Felborn Overfiend: Ashen Ring'),
/* Dreadfall Infernal 106958 */
(106958,132204,0,95,0,1,0,1,1,'Dreadfall Infernal: Sticky Volatile Substance'),
(106958,132199,0,3,0,1,0,1,1,'Dreadfall Infernal: Congealed Felblood'),
(106958,138781,0,0.04,0,1,0,1,1,'Dreadfall Infernal: Brief History of the Aeons'),
(106958,138782,0,0.15,0,1,0,1,1,'Dreadfall Infernal: Brief History of the Ages'),
(106958,132197,0,0.5,1,1,0,1,1,'Dreadfall Infernal: Fel Paw'),
/* Lady Tyrana 106825 */
(106825,132204,0,98,0,1,0,1,1,'Lady Tyrana: Sticky Volatile Substance'),
(106825,132199,0,2,0,1,0,1,1,'Lady Tyrana: Congealed Felblood'),
(106825,138781,0,0.02,0,1,0,1,1,'Lady Tyrana: Brief History of the Aeons'),
(106825,144345,0,0.02,0,1,0,1,1,'Lady Tyrana: Pile of Pet Goodies'),
(106825,141064,0,0.12,0,1,0,1,1,'Lady Tyrana: Technique: Glyph of the Shivarra'),
/* Pain Mistress Nikta 106827 */
(106827,132204,0,96,0,1,0,1,1,'Pain Mistress Nikta: Sticky Volatile Substance'),
(106827,132199,0,4,0,1,0,1,1,'Pain Mistress Nikta: Congealed Felblood'),
(106827,138781,0,0.02,0,1,0,1,1,'Pain Mistress Nikta: Brief History of the Aeons'),
(106827,132200,0,0.12,0,1,0,1,1,'Pain Mistress Nikta: Ashen Ring'),
(106827,140220,0,0.05,0,1,0,1,1,'Pain Mistress Nikta: Scavenged Cloth');
-- LFG Dungeons
DELETE FROM `lfg_dungeon_template` WHERE `dungeonId`=1250;
INSERT INTO `lfg_dungeon_template` (`dungeonId`, `name`, `position_X`, `position_y`, `position_z`, `orientation`, `requiredItemLevel`, `VerifiedBuild`) VALUES
(1250, 'Dark Whispers', 0, 0, 0, 0, 0, 26972);
-- Conversations
DELETE FROM `conversation_actor_template` WHERE `Id` IN (60437 /*Thalkiel*/, 60438 /*Mephistroth*/);
INSERT INTO `conversation_actor_template` (`Id`, `CreatureId`, `CreatureModelId`, `VerifiedBuild`) VALUES
(60437, 106762, 69686, 26972),
(60438, 106652, 67759, 26972);
DELETE FROM `conversation_actors` WHERE `ConversationId` IN (6819, 6820, 6821, 6822, 6823, 6824);
INSERT INTO `conversation_actors` (`ConversationId`, `ConversationActorId`, `ConversationActorGuid`, `Idx`, `VerifiedBuild`) VALUES
(6819, 60437, 0, 0, 26972),
(6820, 60437, 0, 0, 26972),
(6821, 60437, 0, 0, 26972),
(6822, 60437, 0, 0, 26972),
(6823, 60437, 0, 0, 26972),
(6824, 60438, 0, 0, 26972);
DELETE FROM `conversation_template` WHERE `Id` IN (6819, 6820, 6821, 6822, 6823, 6824);
INSERT INTO `conversation_template` (`Id`, `FirstLineId`, `LastLineEndTime`, `ScriptName`, `VerifiedBuild`) VALUES
(6819, 15699, 15120, '', 26972),
(6820, 15701, 6920, '', 26972),
(6821, 15702, 7920, '', 26972),
(6822, 15703, 4920, '', 26972),
(6823, 15705, 8920, '', 26972),
(6824, 15706, 12320, '', 26972);
DELETE FROM `conversation_line_template` WHERE `Id` BETWEEN 15699 AND 15706;
INSERT INTO `conversation_line_template` (`Id`, `StartTime`, `UiCameraID`, `ActorIdx`, `Flags`, `VerifiedBuild`) VALUES
(15699, 0, 669, 0, 0, 26972),
(15700, 6411, 669, 0, 0, 26972),
(15701, 0, 669, 0, 0, 26972),
(15702, 0, 669, 0, 0, 26972),
(15703, 0, 669, 0, 0, 26972),
(15704, 2120, 669, 0, 0, 26972),
(15705, 0, 669, 0, 0, 26972),
(15706, 0, 672, 0, 0, 26972);