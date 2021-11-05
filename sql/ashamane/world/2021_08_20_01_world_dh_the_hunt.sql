-- "The Twinblades of the Deceiver" Artifact Scenario
UPDATE `instance_template` SET `script`='scenario_artifact_suramar_acquisition', `parent`=1220, `insideResurrection`=1 WHERE `map`=1498;
DELETE FROM `scenarios` WHERE `map` = '1498' AND `scenario_A`='900';
INSERT INTO `scenarios` (`map`, `difficulty`, `scenario_A`, `scenario_H`) VALUES
('1498', '12', '900', '900');
/* The Twinblades of the Deceiver Scenario spawns */
SET @CGUID := 280001139;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+70;
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `unit_flags2`, `unit_flags3`, `dynamicflags`, `ScriptName`, `VerifiedBuild`) VALUES
(@CGUID+0,95313,1498,7637,7768,12,0,0,522,-1,0,0,1064.09,5146.94,57.9364,3.10926,900,0,0,0,0,0,0,768,0,0,0,'',25549), -- Felsoul Chaosweaver (ability: 183345)
(@CGUID+1,95313,1498,7637,7768,12,0,0,522,-1,0,0,1052.9,5109.51,57.0457,2.62376,900,0,0,0,0,0,0,768,0,0,0,'',25549), -- Felsoul Chaosweaver (ability: 183345)
(@CGUID+2,95899,1498,7637,7768,12,0,0,522,-1,0,0,979.793,4852.98,42.5688,1.13435,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Infinite AOI Bunny - GJC [INSTANCES ONLY - SPECIAL CASE USE ONLY]
(@CGUID+3,101906,1498,7637,7768,12,0,0,522,-1,0,0,970.715,4906.96,60.9847,0.584905,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Universal Bunny
(@CGUID+4,101695,1498,7637,7768,12,0,0,522,-1,0,0,1099.81,4901.87,61.8493,0.91476,900,0,0,0,0,0,0,0,0,0,0,'npc_felsoul_obliterator_101695',25549), -- Felsoul Obliterator (abilities: 191669, 202211)
(@CGUID+5,95899,1498,7637,7768,12,0,0,522,-1,0,0,1096.89,4961.00,49.1263,0.36076,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Infinite AOI Bunny - GJC [INSTANCES ONLY - SPECIAL CASE USE ONLY]
(@CGUID+6,101906,1498,7637,7768,12,0,0,522,-1,0,0,1216.74,5003.82,86.3502,2.57561,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Universal Bunny
(@CGUID+7,95899,1498,7637,7768,12,0,0,522,-1,0,0,1091.08,5140.42,89.8238,0.349389,900,0,0,0,0,0,0,0,0,0,0,'npc_suramar_second_AOIbunny',25549), -- Infinite AOI Bunny - GJC [INSTANCES ONLY - SPECIAL CASE USE ONLY]
(@CGUID+8,101906,1498,7637,7768,12,0,0,522,-1,0,0,1055.25,5091.42,80.0833,0.45281,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Universal Bunny
(@CGUID+9,95899,1498,7637,7768,12,0,0,522,-1,0,0,1258.78,5236.05,130.786,0.349389,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Infinite AOI Bunny - GJC [INSTANCES ONLY - SPECIAL CASE USE ONLY]
(@CGUID+10,101763,1498,7637,7768,12,0,0,522,-1,0,0,936.345,4882.26,131.293,2.07462,900,20,0,0,0,1,0,0,0,0,0,'',25549), -- Felsoul Swarmer
(@CGUID+11,101763,1498,7637,7768,12,0,0,522,-1,0,0,1004.57,5014.33,130.979,5.93877,900,20,0,0,0,1,0,0,0,0,0,'',25549), -- Felsoul Swarmer
(@CGUID+12,101763,1498,7637,7768,12,0,0,522,-1,0,0,970.291,4989.14,135.664,4.54916,900,20,0,0,0,1,0,0,0,0,0,'',25549), -- Felsoul Swarmer
(@CGUID+13,95329,1498,7637,7768,12,0,0,522,-1,0,0,1207.27,4976.65,57.7924,0.60798,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Fleshcarver
(@CGUID+14,95922,1498,7637,7768,12,0,0,522,-1,0,0,970.566,4906.9,36.1507,0.580077,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Generic Bunny
(@CGUID+15,101763,1498,7637,7768,12,0,0,522,-1,0,0,1094.64,5064.25,139.405,4.41542,900,20,0,0,0,1,0,0,0,0,0,'',25549), -- Felsoul Swarmer
(@CGUID+16,101763,1498,7637,7768,12,0,0,522,-1,0,0,1062.27,4983.62,133.57,2.39036,900,20,0,0,0,1,0,0,0,0,0,'',25549), -- Felsoul Swarmer
(@CGUID+17,101695,1498,7637,7768,12,0,0,522,-1,0,0,1270.28,5253.43,93.9493,4.2859,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Obliterator (abilities: 191669, 202211)
(@CGUID+18,101764,1498,7637,7768,12,0,0,522,-1,0,0,1099.84,5009.24,126.758,3.58149,900,20,0,0,0,1,0,0,0,0,0,'',25549), -- Felsoul Doomlord
(@CGUID+19,101763,1498,7637,7768,12,0,0,522,-1,0,0,1169.72,5139.56,130.979,4.33128,900,20,0,0,0,1,0,0,0,0,0,'',25549), -- Felsoul Swarmer
(@CGUID+20,101764,1498,7637,7768,12,0,0,522,-1,0,0,1106.73,5044.1,135.439,4.05676,900,20,0,0,0,1,0,0,0,0,0,'',25549), -- Felsoul Doomlord
(@CGUID+21,101764,1498,7637,7768,12,0,0,522,-1,0,0,1155.88,5061.14,143.361,3.73965,900,20,0,0,0,1,0,0,0,0,0,'',25549), -- Felsoul Doomlord
(@CGUID+22,101770,1498,7637,7768,12,0,0,522,-1,0,0,1253.03,5254.09,106.522,4.57183,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Doomlord
(@CGUID+23,101770,1498,7637,7768,12,0,0,522,-1,0,0,1283.03,5249.42,108.391,4.02794,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Doomlord
(@CGUID+24,95313,1498,7637,7768,12,0,0,522,-1,0,0,997.72,4978.12,37.4653,4.14846,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Chaosweaver
(@CGUID+25,95899,1498,7637,7768,12,0,0,522,-1,0,0,1117.88,5185.47,66.8023,0.79537,900,0,0,0,0,0,0,0,0,0,0,'npc_suramar_first_AOIbunny',25549), -- Infinite AOI Bunny - GJC [INSTANCES ONLY - SPECIAL CASE USE ONLY]
(@CGUID+26,101867,1498,7637,7768,12,0,0,522,-1,0,0,976.986,5148.53,69.9649,2.99324,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Gateway
(@CGUID+27,54638,1498,7637,7768,12,0,0,522,-1,0,0,1192.05,5250.71,79.632,0.424421,1,0,0,0,0,0,0,0,0,0,0,'npc_fel_spike_bunny',25549), -- Generic Bunny (abilities: 211742)
(@CGUID+28,54638,1498,7637,7768,12,0,0,522,-1,0,0,1103.25,5186.29,65.4488,0.620403,1,0,0,0,0,0,0,0,0,0,0,'npc_fel_spike_bunny',25549), -- Generic Bunny (abilities: 211742)
(@CGUID+29,54638,1498,7637,7768,12,0,0,522,-1,0,0,1105.57,5180.24,64.259,0.78054,1,0,0,0,0,0,0,0,0,0,0,'npc_fel_spike_bunny',25549), -- Generic Bunny (abilities: 211742)
(@CGUID+30,54638,1498,7637,7768,12,0,0,522,-1,0,0,1118.65,5171.46,65.7147,1.06036,1,0,0,0,0,0,0,0,0,0,0,'npc_fel_spike_bunny',25549), -- Generic Bunny (abilities: 211742)
(@CGUID+31,54638,1498,7637,7768,12,0,0,522,-1,0,0,1130.63,5166.3,67.7482,1.1575,1,0,0,0,0,0,0,0,0,0,0,'npc_fel_spike_bunny',25549), -- Generic Bunny (abilities: 211742)
(@CGUID+32,54638,1498,7637,7768,12,0,0,522,-1,0,0,1125.47,5170.15,67.2623,1.21732,1,0,0,0,0,0,0,0,0,0,0,'npc_fel_spike_bunny',25549), -- Generic Bunny (abilities: 211742)
(@CGUID+33,95922,1498,7637,7768,12,0,0,522,-1,0,0,1055.16,5091.29,55.3546,0.45281,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Generic Bunny
(@CGUID+34,54638,1498,7637,7768,12,0,0,522,-1,0,0,1150.35,5231.76,70.9866,0.81895,1,0,0,0,0,0,0,0,0,0,0,'npc_fel_spike_bunny',25549), -- Generic Bunny (abilities: 211742)
(@CGUID+35,73985,1498,7637,7768,12,0,0,522,-1,0,0,972.177,4952.98,49.1648,5.7127,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Large AOI Bunny - GJC (auras: 265123)
(@CGUID+36,54638,1498,7637,7768,12,0,0,522,-1,0,0,1086.704,4941.24,49.7059,6.10013,1,0,0,0,0,0,0,0,0,0,0,'npc_fel_spike_bunny',25549), -- Generic Bunny (abilities: 211742)
(@CGUID+37,54638,1498,7637,7768,12,0,0,522,-1,0,0,1065.38,4971.16,44.8989,5.57757,1,0,0,0,0,0,0,0,0,0,0,'npc_fel_spike_bunny',25549), -- Generic Bunny (abilities: 211742)
(@CGUID+38,54638,1498,7637,7768,12,0,0,522,-1,0,0,1064.64,4943.56,48.257,0.20963,1,0,0,0,0,0,0,0,0,0,0,'npc_fel_spike_bunny',25549), -- Generic Bunny (abilities: 211742)
(@CGUID+39,102966,1498,7637,7768,12,0,0,522,-1,0,0,1004.21,4931.21,43.3358,0.800601,900,0,0,0,0,2,0,0,0,0,0,'',25549), -- Invisible Stalker
(@CGUID+40,54638,1498,7637,7768,12,0,0,522,-1,0,0,1026.34,4973.94,38.9889,6.10011,1,0,0,0,0,0,0,0,0,0,0,'npc_fel_spike_bunny',25549), -- Generic Bunny (abilities: 211742)
(@CGUID+41,95452,1498,7637,7768,12,0,0,522,-1,0,0,1130.33,4974.91,50.1715,0.363882,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Crusher
(@CGUID+42,95922,1498,7637,7768,12,0,0,522,-1,0,0,1216.84,5003.89,62.0476,2.58232,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Generic Bunny
(@CGUID+43,95464,1498,7637,7768,12,0,0,522,-1,0,0,982.17,4879.24,32.3454,0.558073,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Gigantic AOI Bunny - GJC [INSTANCES ONLY]
(@CGUID+44,95464,1498,7637,7768,12,0,0,522,-1,0,0,993.337,4876.76,32.2556,0.558073,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Gigantic AOI Bunny - GJC [INSTANCES ONLY]
(@CGUID+45,95464,1498,7637,7768,12,0,0,522,-1,0,0,998.892,4876.26,32.1876,0.558073,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Gigantic AOI Bunny - GJC [INSTANCES ONLY]
(@CGUID+46,95464,1498,7637,7768,12,0,0,522,-1,0,0,975.722,4866.96,32.1424,0.558073,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Gigantic AOI Bunny - GJC [INSTANCES ONLY]
(@CGUID+47,95464,1498,7637,7768,12,0,0,522,-1,0,0,984.99,4854.77,32.2291,0.558073,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Gigantic AOI Bunny - GJC [INSTANCES ONLY]
(@CGUID+48,95464,1498,7637,7768,12,0,0,522,-1,0,0,992.911,4862.37,32.251,0.558073,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Gigantic AOI Bunny - GJC [INSTANCES ONLY]
(@CGUID+49,95464,1498,7637,7768,12,0,0,522,-1,0,0,977.141,4855.65,32.2291,0.558073,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Gigantic AOI Bunny - GJC [INSTANCES ONLY]
(@CGUID+50,95464,1498,7637,7768,12,0,0,522,-1,0,0,981.135,4866.82,32.2052,0.558073,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Gigantic AOI Bunny - GJC [INSTANCES ONLY]
(@CGUID+51,95464,1498,7637,7768,12,0,0,522,-1,0,0,987.154,4875.05,32.2052,0.558073,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Gigantic AOI Bunny - GJC [INSTANCES ONLY]
(@CGUID+52,95464,1498,7637,7768,12,0,0,522,-1,0,0,987.427,4866.53,32.2109,0.558073,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Gigantic AOI Bunny - GJC [INSTANCES ONLY]
(@CGUID+53,95313,1498,7637,7768,12,0,0,522,-1,0,0,1106.11,5162.37,62.4132,0.772932,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Chaosweaver (abilities: 183345)
(@CGUID+54,95313,1498,7637,7768,12,0,0,522,-1,0,0,1097.54,5160.78,61.0519,0.763566,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Chaosweaver (abilities: 183345)
(@CGUID+55,95314,1498,7637,7768,12,0,0,522,-1,0,0,1145.56,5225.91,70.3035,0.849695,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Stalker (abilities: 182566, 204337)
(@CGUID+56,95314,1498,7637,7768,12,0,0,522,-1,0,0,1107.46,5158.2,62.2113,0.771014,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Stalker (abilities: 182566, 204337)
(@CGUID+57,95314,1498,7637,7768,12,0,0,522,-1,0,0,1156.65,5219.11,70.9498,1.15993,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Stalker (abilities: 182566, 204337)
(@CGUID+58,6491,1498,7637,7768,12,0,0,522,-1,0,0,753.85,4963.45,138.2,3.41,120,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Ritualist (abilities: 183345)
(@CGUID+59,95848,1498,7637,7768,12,0,0,522,-1,0,0,1076.42,4946.62,48.6052,0.19315,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Ritualist (abilities: 183345)
(@CGUID+60,95848,1498,7637,7768,12,0,0,522,-1,0,0,1076.66,4954.06,47.5632,0.33530,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Ritualist (abilities: 183345)
(@CGUID+61,6491,1498,7637,7768,12,0,0,522,-1,0,0,998.093,4894.58,36.354,2.45279,120,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Ritualist (abilities: 183345)
(@CGUID+62,95848,1498,7637,7768,12,0,0,522,-1,0,0,1079.77,4989.49,49.8667,0.35490,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Ritualist (abilities: 183345)
(@CGUID+63,6491,1498,7637,7768,12,0,0,522,-1,0,0,1264.29,5236.38,93.5313,1.47915,120,0,0,0,0,0,0,0,0,0,0,'',25549), -- Spirit Healer
(@CGUID+64,95329,1498,7637,7768,12,0,0,522,-1,0,0,1070.59,5119.97,57.3696,0.891316,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Fleshcarver (abilities: 204114, 205818)
(@CGUID+65,95329,1498,7637,7768,12,0,0,522,-1,0,0,1163.74,5226.07,73.0995,1.16385,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Fleshcarver (abilities: 204114, 205818)
(@CGUID+66,95329,1498,7637,7768,12,0,0,522,-1,0,0,1155.84,5230.14,71.6007,0.84577,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Fleshcarver (abilities: 204114, 205818)
(@CGUID+67,95429,1498,7637,7768,12,0,0,522,-1,0,0,1004.116,4931.888,36.2755,0.67523,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Fist of the Deceiver
(@CGUID+68,95285,1498,7637,7768,12,0,0,522,-1,0,0,1201.0,4994.28,57.8075,1.96338,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Fel Commander Igrius (abilities: 193906, 199094, 205817, 216681)
(@CGUID+69,95423,1498,7637,7768,12,0,0,522,-1,0,0,1037.51,5131.58,58.582,5.61795,900,0,0,0,0,0,0,0,0,0,0,'',25549), -- Felsoul Berserker
(@CGUID+70,95423,1498,7637,7768,12,0,0,522,-1,0,0,1039.46,5134.89,58.486,5.4805,900,0,0,0,0,0,0,0,0,0,0,'',25549); -- Felsoul Berserker
/* Felsoul Hold objects spawn */
SET @GOGUID := 51014704;
DELETE FROM `gameobject` WHERE `guid` BETWEEN @GOGUID+0 AND @GOGUID+6;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `isActive`, `ScriptName`, `VerifiedBuild`) VALUES
(@GOGUID+0,243428,1498,7637,7768,12,0,0,522,-1,1055.15,5091.44,55.2713,0.452808,-0,-0,-0,1,7200,255,1,1,'',22423), -- Felshield Ward (triggers: 190275)
(@GOGUID+1,243472,1498,7637,7768,12,0,0,522,-1,1213.633,5026.272,60.0546,2.58231,-0,-0,-0,1,7200,255,1,1,'',22423), -- Felshield Ward (triggers: 190275)
(@GOGUID+2,243473,1498,7637,7768,12,0,0,522,-1,970.566,4906.9,36.0674,0.580076,-0,-0,-0,1,7200,255,1,1,'',22423), -- Felshield Ward (triggers: 190275)
(@GOGUID+3,246288,1498,7637,7768,12,0,0,522,-1,1263.05,5237.32,93.5311,2.25552,0,0,0,1,7200,255,0,1,'',22423), -- Rune
(@GOGUID+4,243679,1498,7637,7768,12,0,0,522,-1,972.904,4953.49,36.0268,5.8367,0,0,0,1,7200,255,0,1,'',22423), -- Ritual Portal
(@GOGUID+5,246316,1498,7637,7768,12,0,0,522,-1,976.986,5148.53,69.8816,2.99322,0,0,0,1,7200,255,0,1,'',22423), -- Ritual Portal
(@GOGUID+6,243468,1498,7637,7768,12,0,0,522,-1,987.344,4869.25,31.0751,5.95153,0,0,0,1,7200,255,0,1,'',22423); -- Ritual Portal
-- Felsoul Fleshcarver 95329
UPDATE `creature_template` SET `lootid`=95314, `AIName`="SmartAI", `minlevel`=100, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=1 WHERE `entry`=95329;
DELETE FROM `smart_scripts` WHERE `entryorguid`=95329 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(95329,0,0,0,0,0,100,0,5000,8000,12000,15000,11,204114,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felsoul Fleshcarver - In Combat - Cast 'Emblazoned Swipe'"),
(95329,0,1,0,0,0,100,0,10000,12000,18000,22000,11,205818,0,0,0,0,0,1,0,0,0,0,0,0,0,"Felsoul Fleshcarver - In Combat - Cast 'Fel Strike'");
DELETE FROM `creature_equip_template` WHERE `CreatureID`=95329;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(95329,1,126434,0,0,0,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=95329;
-- Felsoul Stalker 95314
UPDATE `creature_template` SET `lootid`=95314, `AIName`="SmartAI", `minlevel`=100, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=1 WHERE `entry`=95314;
DELETE FROM `smart_scripts` WHERE `entryorguid`=95314 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(95314,0,0,0,0,0,100,0,5000,8000,12000,15000,11,204337,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felsoul Stalker - In Combat - Cast 'Mana Rage'"),
(95314,0,1,0,0,0,100,0,10000,10000,10000,25000,11,182566,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felsoul Stalker - In Combat - Cast 'Arcane Bite'");
-- Felsoul Chaosweaver 95313
UPDATE `creature_template` SET `lootid`=95313, `AIName`="SmartAI", `minlevel`=100, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=1 WHERE `entry`=95313;
DELETE FROM `smart_scripts` WHERE `entryorguid`=95313 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(95313,0,0,0,0,0,100,0,0,0,3400,4700,11,183345,64,0,0,0,0,2,0,0,0,0,0,0,0,"Felsoul Chaosweaver - In Combat - Cast 'Shadow Bolt'");
DELETE FROM `creature_equip_template` WHERE `CreatureID`=95313;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(95313,1,128199,0,0,0,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=95313;
-- Felsoul Ritualist 95848
UPDATE `creature_template` SET `lootid`=95848, `AIName`="SmartAI", `minlevel`=100, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=1 WHERE `entry`=95848;
DELETE FROM `smart_scripts` WHERE `entryorguid`=95848 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(95848,0,0,0,0,0,100,0,0,0,3400,4700,11,183345,64,0,0,0,0,2,0,0,0,0,0,0,0,"Felsoul Ritualist - In Combat - Cast 'Shadow Bolt'");
DELETE FROM `creature_equip_template` WHERE `CreatureID`=95848;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(95848,1,128199,0,0,0,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=95848;
-- Felsoul Crusher 95452
UPDATE `creature_template` SET `lootid`=95452, `AIName`="SmartAI", `minlevel`=100, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=1.5 WHERE `entry`=95452;
DELETE FROM `smart_scripts` WHERE `entryorguid`=95452 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(95452,0,0,0,0,0,100,0,5000,8000,12000,15000,11,190086,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felsoul Crusher - In Combat - Cast 'Fel Streak'"),
(95452,0,1,0,2,0,100,1,0,30,0,0,11,181190,0,0,0,0,0,1,0,0,0,0,0,0,0,"Felsoul Crusher - Between 0-30% Health - Cast 'Fel Streak' (No Repeat)");
-- Felsoul Berserker 95423
UPDATE `creature_template` SET `lootid`=95423, `AIName`="SmartAI", `minlevel`=100, `maxlevel`=100, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=1 WHERE `entry`=95423;
DELETE FROM `smart_scripts` WHERE `entryorguid`=95423 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(95423,0,0,0,0,0,100,0,1000,2000,8000,9000,11,196808,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felsoul Berserker - In Combat - Cast 'Mo''arg Smash'"),
(95423,0,1,0,0,0,100,0,10000,12000,18000,22000,11,196814,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felsoul Berserker - In Combat - Cast 'Death Breath'");
DELETE FROM `creature_equip_template` WHERE `CreatureID`=95423;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(95423,1,128519,0,0,0,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=95423;
-- Fist of the Deceiver 95429
UPDATE `creature_template` SET `lootid`=95429, `AIName`="SmartAI", `minlevel`=102, `maxlevel`=102, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=2.0 WHERE `entry`=95429;
DELETE FROM `smart_scripts` WHERE `entryorguid`=95429 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(95429,0,0,0,54,0,100,0,0,0,0,0,11,189447,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fist of the Deceiver - JustSpawned - CastSpell 'Legion- Spawn from Portal'"),
(95429,0,1,0,0,0,100,0,5000,8000,12000,15000,11,190697,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fist of the Deceiver - In Combat - Cast 'Fel Crash'"),
(95429,0,2,0,0,0,100,0,10000,10000,18000,25000,11,182146,0,0,0,0,0,2,0,0,0,0,0,0,0,"Fist of the Deceiver - In Combat - Cast 'Legion Slash'"),
(95429,0,3,0,6,0,100,0,0,0,0,0,205,92,54742,0,0,0,0,21,50,0,0,0,0,0,0,"Fist of the Deceiver - On Death - CSC");
DELETE FROM `creature_equip_template` WHERE `CreatureID`=95429;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(95429,1,133351,0,0,133351,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=95429;
-- Fel Commander Igrius 95285
UPDATE `creature_template` SET `lootid`=95285, `AIName`="", `ScriptName`='npc_fel_commander_igrius_95285', `minlevel`=102, `maxlevel`=102, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=2.0 WHERE `entry`=95285;
DELETE FROM `creature_equip_template` WHERE `CreatureID`=95285;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(95285,1,128279,0,0,0,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=95285;
DELETE FROM `creature_text` WHERE `CreatureID` = 95285;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(95285, 0, 0, 'Bathe them in hellfire! Halt their advance! ', 14, 0, 100, 0, 0, 52047, 0, 0, 'Fel Commander Igrius to Player'),
(95285, 1, 0, 'DIE!', 14, 0, 100, 0, 0, 52046, 0, 0, 'Fel Commander Igrius to Player'),
(95285, 2, 0, 'Do you crave death, elf? Do you dare face my lord\'s wrath alone?', 14, 0, 100, 0, 0, 52010, 0, 0, 'Fel Commander Igrius to Player'),
(95285, 3, 0, 'Mo\'arg, to the front! This has gone on long enough.', 14, 0, 100, 0, 0, 52048, 0, 0, 'Fel Commander Igrius to Player'),
(95285, 4, 0, 'You have gone far enough, mortal. This ends here.', 12, 0, 100, 0, 0, 52022, 0, 0, 'Fel Commander Igrius to Player'),
(95285, 5, 0, 'Your life is forfeit!', 12, 0, 100, 0, 0, 58251, 0, 0, 'Fel Commander Igrius to Player'),
(95285, 6, 0, 'Master... I have... failed...', 12, 0, 100, 0, 0, 52037, 0, 0, 'Fel Commander Igrius to Player');
-- Varedis Felsoul 94836
UPDATE `creature_template` SET `unit_class`=2, `AIName`='', `ScriptName`='npc_varedis_felsoul_94836', `minlevel`=102, `maxlevel`=102, `faction`=16, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=32832, `HealthModifier`=2.5 WHERE `entry`=94836;
DELETE FROM `creature_equip_template` WHERE `CreatureID`=94836;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(94836,1,127829,0,0,127830,0,0,0,0,0,25549);
UPDATE `creature` SET `equipment_id`=1 WHERE `id`=94836;
DELETE FROM `creature_text` WHERE `CreatureID` = 94836;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(94836, 0, 0, 'Behold the infinite power of the Twinblades!', 12, 0, 100, 0, 0, 52044, 143456, 3, 'Varedis Felsoul to Player'),
(94836, 1, 0, 'So, Illidari, you seek my head, that you might take the Twinblades as your own? Allow me to introduce you to their power... personally.', 12, 0, 100, 0, 0, 52021, 143455, 3, 'Varedis Felsoul to Player'),
(94836, 2, 0, 'Join me! Unleash your true power. Do not let the weak hold you back!', 14, 0, 100, 0, 0, 52016, 0, 0, 'Varedis Felsoul to Player'),
(94836, 3, 0, 'Behold the might of the Deceiver! Behold the glory of the demon within!', 14, 0, 100, 0, 0, 52027, 0, 0, 'Varedis Felsoul to Player'),
(94836, 4, 0, 'I am a GOD! KNEEL BEFORE ME!', 14, 0, 100, 0, 0, 58252, 0, 0, 'Varedis Felsoul to Player'),
(94836, 5, 0, 'I am through with this charade! Your soul will feed the Twinblades.', 14, 0, 100, 0, 0, 52026, 0, 0, 'Varedis Felsoul to Player'),
(94836, 6, 0, 'I have no need for mortal armaments!', 12, 0, 100, 0, 0, 64632, 0, 0, 'Varedis Felsoul to Player'),
(94836, 7, 0, 'This is not over... Illidari.', 12, 0, 100, 0, 0, 64633, 0, 0, 'Varedis Felsoul to Player'),
(94836, 8, 0, 'Gladly, my master.', 12, 0, 100, 0, 0, 58253, 0, 0, 'Varedis Felsoul to Player');
-- Felsoul Obliterator 101695
UPDATE `creature_template` SET `AIName`="", `ScriptName`='', `minlevel` = 100, `maxlevel` = 100, `faction`=16, `unit_flags`=65536 WHERE `entry`=101695;
-- Felsoul Swarmer (101763) Felsoul Doomlord (101764)
UPDATE `creature_template` SET `InhabitType`='4' WHERE `entry` in ('101763', '101764');
-- Creature Loot
DELETE FROM `creature_loot_template` WHERE `Entry` IN (95329, 95314, 95313, 95848, 95452, 95423, 95429, 95285);
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
/* Felsoul Fleshcarver 95329 */
(95329,132204,0,98,0,1,0,1,1,'Felsoul Fleshcarver: Sticky Volatile Substance'),
(95329,132199,0,2,0,1,0,1,1,'Felsoul Fleshcarver: Congealed Felblood'),
(95329,137677,0,3,1,1,0,1,1,'Felsoul Fleshcarver: Fel Blood'),
(95329,138782,0,0.1,0,1,0,1,1,'Felsoul Fleshcarver: Brief History of the Ages'),
(95329,138781,0,0.4,0,1,0,1,1,'Felsoul Fleshcarver: Brief History of the Aeons'),
(95329,140220,0,0.02,0,1,0,1,1,'Felsoul Fleshcarver: Scavenged Cloth'),
(95329,132231,0,5,0,1,0,1,1,'Felsoul Fleshcarver: Worn Hooked Claw'),
(95329,132200,0,0.02,0,1,0,1,1,'Felsoul Fleshcarver: Ashen Ring'),
/* Felsoul Stalker 95314 */
(95314,132204,0,4,0,1,0,1,1,'Felsoul Stalker: Sticky Volatile Substance'),
(95314,132199,0,0.9,0,1,0,1,1,'Felsoul Stalker: Congealed Felblood'),
(95314,138781,0,0.05,0,1,0,1,1,'Felsoul Stalker: Brief History of the Aeons'),
(95314,132231,0,99,0,1,0,1,1,'Felsoul Stalker: Worn Hooked Claw'),
(95314,132197,0,0.04,0,1,0,1,1,'Felsoul Stalker: Fel Paw'),
(95314,141035,0,0.01,1,1,0,1,1,'Felsoul Stalker: Technique Glyph of Fel Wings'),
(95314,137677,0,3,1,1,0,1,1,'Felsoul Stalker: Fel Blood'),
/* Felsoul Chaosweaver 95313 */
(95313,132204,0,98,0,1,0,1,1,'Felsoul Chaosweaver: Sticky Volatile Substance'),
(95313,132199,0,1.9,0,1,0,1,1,'Felsoul Chaosweaver: Congealed Felblood'),
(95313,132231,0,3,0,1,0,1,1,'Felsoul Chaosweaver: Worn Hooked Claw'),
(95313,138781,0,0.02,0,1,0,1,1,'Felsoul Chaosweaver: Brief History of the Aeons'),
(95313,132200,0,0.06,0,1,0,1,1,'Felsoul Chaosweaver: Ashen Ring'),
(95313,137677,0,3,1,1,0,1,1,'Felsoul Chaosweaver: Fel Blood'),
/* Felsoul Ritualist 95848 */
(95848,132204,0,99,0,1,0,1,1,'Felsoul Ritualist: Sticky Volatile Substance'),
(95848,132199,0,1.3,0,1,0,1,1,'Felsoul Ritualist: Congealed Felblood'),
(95848,132200,0,0.05,0,1,0,1,1,'Felsoul Ritualist: Ashen Ring'),
(95848,138781,0,0.02,0,1,0,1,1,'Felsoul Ritualist: Brief History of the Aeons'),
(95848,137677,0,4,1,1,0,1,1,'Felsoul Ritualist: Fel Blood'),
(95848,141064,0,0.01,1,1,0,1,1,'Felsoul Ritualist: Technique Glyph of Shivarra'),
/* Felsoul Crusher 95452 */
(95452,132204,0,96,0,1,0,1,1,'Felsoul Crusher: Sticky Volatile Substance'),
(95452,132199,0,3,0,1,0,1,1,'Felsoul Crusher: Congealed Felblood'),
(95452,132197,0,0.16,0,1,0,1,1,'Felsoul Crusher: Fel Claw'),
(95452,137677,0,3,1,1,0,1,1,'Felsoul Crusher: Fel Blood'),
/* Felsoul Berserker 95423 */
(95423,132204,0,99,0,1,0,1,1,'Felsoul Berserker: Sticky Volatile Substance'),
(95423,132199,0,1.5,0,1,0,1,1,'Felsoul Berserker: Congealed Felblood'),
(95423,132200,0,0.01,0,1,0,1,1,'Felsoul Berserker: Ashen Ring'),
(95423,138781,0,0.06,0,1,0,1,1,'Felsoul Berserker: Brief History of the Aeons'),
(95423,137677,0,3,1,1,0,1,1,'Felsoul Berserker: Fel Blood'),
/* Fist of the Deceiver 95429 */
(95429,132204,0,96,0,1,0,1,1,'Fist of the Deceiver: Sticky Volatile Substance'),
(95429,132199,0,4,0,1,0,1,1,'Fist of the Deceiver: Congealed Felblood'),
(95429,132200,0,3,0,1,0,1,1,'Fist of the Deceiver: Ashen Ring'),
(95429,140227,0,0.02,0,1,0,1,1,'Fist of the Deceiver: Bloodhunters Quarry'),
(95429,138781,0,0.1,0,1,0,1,1,'Fist of the Deceiver: Brief History of the Aeons'),
(95429,137677,0,4,1,1,0,1,1,'Fist of the Deceiver: Fel Blood'),
/* Fel Commander Igrius 95285 */
(95285,132204,0,98,0,1,0,1,1,'Fel Commander Igrius: Sticky Volatile Substance'),
(95285,132199,0,1.9,0,1,0,1,1,'Fel Commander Igrius: Congealed Felblood'),
(95285,138781,0,1.6,0,1,0,1,1,'Fel Commander Igrius: Brief History of the Aeons'),
(95285,132200,0,0.01,0,1,0,1,1,'Fel Commander Igrius: Ashen Ring'),
(95285,141064,0,0.01,0,1,0,1,1,'Fel Commander Igrius: Technique: Glyph of the Shivarra'),
(95285,137677,0,3,1,1,0,1,1,'Fel Commander Igrius: Fel Blood');
-- go loot 251878 twinblades of the deceiver
DELETE FROM `gameobject_loot_template` WHERE `Entry` IN (251878, 65645);
INSERT INTO `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES 
(65645, 127829, 0, 100, 0, 1, 0, 1, 1, 'twinblades of the deceiver');
DELETE FROM `gameobject_template` WHERE `Entry`= 251878;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `Data24`, `Data25`, `Data26`, `Data27`, `Data28`, `Data29`, `Data30`, `Data31`, `Data32`, `RequiredLevel`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES
(251878, 3, 9806, 'Twinblades of the Deceiver', 'questinteract', 'Wielding', '', 2.5, 43, 65645, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 107711, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 'go_twinblades_of_the_deceiver_251878', 26822);
DELETE FROM `gameobject_template_addon` WHERE `entry`=251878;
INSERT INTO `gameobject_template_addon` (`entry`, `faction`, `flags`) VALUES
(251878, 0, 2097152); -- Twinblades of the Deceiver
-- Fel Spike 100996
UPDATE `creature_template` SET `AIName`="SmartAI", `faction`=16, `type_flags`=1048576, `type_flags2`=0, `type`=10, `family`=0, `minlevel`=1, `maxlevel`=1 WHERE `entry`=100996;
DELETE FROM `smart_scripts` WHERE `entryorguid`=100996 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(100996,0,0,0,60,0,100,1,3000,3000,52000,53000,11,199188,0,0,0,0,0,1,0,0,0,0,0,0,0,'arts'),
(100996,0,1,0,60,0,100,1,7000,7000,52000,53000,11,199104,0,0,0,0,0,1,0,0,0,0,0,0,0,'arts'),
(100996,0,2,0,60,0,100,0,10000,10000,10000,10000,11,199062,0,0,0,0,0,1,0,0,0,0,0,0,0,'arts');
-- Creature Addon corrections
DELETE FROM `creature_addon` WHERE `guid` IN (280001139, 280001140, 280001157);
INSERT INTO `creature_addon` (`guid`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES
(280001139, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(280001140, 0, 0x0, 0x1, '29266'), -- 25680 - 29266 - 29266
(280001157, 0, 0x0, 0x1, '29266'); -- 25680 - 29266 - 29266
DELETE FROM `gameobject_template_addon` WHERE `entry` IN (243472, 243428, 243473);
INSERT INTO `gameobject_template_addon` (`entry`, `faction`, `flags`, `mingold`, `maxgold`, `WorldEffectId`) VALUES
(243472, 0, 262176, 0, 0, 0),
(243428, 0, 262176, 0, 0, 0),
(243473, 0, 262176, 0, 0, 0);
-- LFG Dungeons
DELETE FROM `lfg_dungeon_template` WHERE `dungeonId` IN (1165, 1166);
INSERT INTO `lfg_dungeon_template` (`dungeonId`, `name`, `position_X`, `position_y`, `position_z`, `orientation`, `requiredItemLevel`, `VerifiedBuild`) VALUES
(1165, 'The Twinblades of the Deceiver', 1264.29, 5236.38, 93.5313, 1.4791, 0, 26972),
(1166, 'The Aldrachi Warblades', 0, 0, 0, 0, 0, 26972);
-- Conversations
-- Kiljaeden
DELETE FROM `conversation_actor_template` WHERE `Id`=60434;
INSERT INTO `conversation_actor_template` (`Id`, `CreatureId`, `CreatureModelId`, `VerifiedBuild`) VALUES
(60434, 122044, 76011, 26972);
DELETE FROM `conversation_actors` WHERE `ConversationId` IN (6805, 6806);
INSERT INTO `conversation_actors` (`ConversationId`, `ConversationActorId`, `ConversationActorGuid`, `Idx`, `VerifiedBuild`) VALUES
(6805, 60434, 0, 0, 26972),
(6806, 60434, 0, 0, 26972);
DELETE FROM `conversation_template` WHERE `Id` IN (6805, 6806);
INSERT INTO `conversation_template` (`Id`, `FirstLineId`, `LastLineEndTime`, `ScriptName`, `VerifiedBuild`) VALUES
(6805, 15688, 7120, '', 26972),
(6806, 15690, 4920, '', 26972);
DELETE FROM `conversation_line_template` WHERE `Id` BETWEEN 15688 AND 15690;
INSERT INTO `conversation_line_template` (`Id`, `StartTime`, `UiCameraID`, `ActorIdx`, `Flags`, `VerifiedBuild`) VALUES
(15688, 0, 989, 0, 0, 26972),
(15689, 3411, 989, 0, 0, 26972),
(15690, 0, 989, 0, 0, 26972);
-- Kayn and Altruis on Felbat
DELETE FROM `conversation_actors` WHERE `ConversationId` IN (6807, 6808);
INSERT INTO `conversation_actors` (`ConversationId`, `ConversationActorId`, `ConversationActorGuid`, `Idx`, `VerifiedBuild`) VALUES
(6807, 60432, 0, 0, 26972), -- kayn
(6808, 60433, 0, 0, 26972); -- Altruis
DELETE FROM `conversation_template` WHERE `Id` IN (6807, 6808);
INSERT INTO `conversation_template` (`Id`, `FirstLineId`, `LastLineEndTime`, `ScriptName`, `VerifiedBuild`) VALUES
(6807, 15675, 4120, '', 26972),
(6808, 15691, 4320, '', 26972);
DELETE FROM `conversation_line_template` WHERE `Id` IN (15675, 15691);
INSERT INTO `conversation_line_template` (`Id`, `StartTime`, `UiCameraID`, `ActorIdx`, `Flags`, `VerifiedBuild`) VALUES
(15675, 0, 82, 0, 0, 26972),
(15691, 0, 99, 0, 0, 26972);
-- Igrius
DELETE FROM `conversation_actor_template` WHERE `Id`=60435; -- Fel Commander Igrius
INSERT INTO `conversation_actor_template` (`Id`, `CreatureId`, `CreatureModelId`, `VerifiedBuild`) VALUES
(60435, 95285, 65980, 26972);
DELETE FROM `conversation_actors` WHERE `ConversationId` IN (6809, 6810, 6811, 6812);
INSERT INTO `conversation_actors` (`ConversationId`, `ConversationActorId`, `ConversationActorGuid`, `Idx`, `VerifiedBuild`) VALUES
(6809, 60435, 0, 0, 26972), -- To arms! Lord Felsoul must not be disturbed.
(6810, 60435, 0, 0, 26972), -- Do you crave death, elf? Do you dare face my lords wrath alone?
(6811, 60435, 0, 0, 26972), -- Moarg to the front! This has gone on long enough.
(6812, 60435, 0, 0, 26972); -- Bathe them in hellfire! Halt their advance!
DELETE FROM `conversation_template` WHERE `Id` IN (6809, 6810, 6811, 6812);
INSERT INTO `conversation_template` (`Id`, `FirstLineId`, `LastLineEndTime`, `ScriptName`, `VerifiedBuild`) VALUES
(6809, 15680, 4620, '', 26972),
(6810, 15681, 9920, '', 26972),
(6811, 15683, 5720, '', 26972),
(6812, 15684, 6820, '', 26972);
DELETE FROM `conversation_line_template` WHERE `Id` BETWEEN 15680 AND 15684;
INSERT INTO `conversation_line_template` (`Id`, `StartTime`, `UiCameraID`, `ActorIdx`, `Flags`, `VerifiedBuild`) VALUES
(15680, 0, 820, 0, 0, 26972),
(15681, 0, 820, 0, 0, 26972),
(15682, 5771, 820, 0, 0, 26972),
(15683, 0, 820, 0, 0, 26972),
(15684, 0, 820, 0, 0, 26972);
-- Varedis
DELETE FROM `conversation_actor_template` WHERE `Id`=60436; -- Varedis
INSERT INTO `conversation_actor_template` (`Id`, `CreatureId`, `CreatureModelId`, `VerifiedBuild`) VALUES
(60436, 105190, 71716, 26972);
DELETE FROM `conversation_actors` WHERE `ConversationId` IN (6813, 6814);
INSERT INTO `conversation_actors` (`ConversationId`, `ConversationActorId`, `ConversationActorGuid`, `Idx`, `VerifiedBuild`) VALUES
(6813, 60436, 0, 0, 26972), -- Its been years. You should know better than to stand against me.
(6814, 60436, 0, 0, 26972); -- Pity your allies had to die. But dont worry. Ill put their souls to good use.
DELETE FROM `conversation_template` WHERE `Id` IN (6813, 6814);
INSERT INTO `conversation_template` (`Id`, `FirstLineId`, `LastLineEndTime`, `ScriptName`, `VerifiedBuild`) VALUES
(6813, 15685, 14620, '', 26972),
(6814, 15687, 8920, '', 26972);
DELETE FROM `conversation_line_template` WHERE `Id` BETWEEN 15685 AND 15687;
INSERT INTO `conversation_line_template` (`Id`, `StartTime`, `UiCameraID`, `ActorIdx`, `Flags`, `VerifiedBuild`) VALUES
(15685, 0, 669, 0, 0, 26972),
(15686, 6921, 669, 0, 0, 26972),
(15687, 0, 669, 0, 0, 26972);
-- Kayn and Altruis
DELETE FROM `conversation_actors` WHERE `ConversationId` IN (6815, 6816);
INSERT INTO `conversation_actors` (`ConversationId`, `ConversationActorId`, `ConversationActorGuid`, `Idx`, `VerifiedBuild`) VALUES
(6815, 60432, 0, 0, 26972), -- kayn
(6816, 60433, 0, 0, 26972); -- Altruis
DELETE FROM `conversation_template` WHERE `Id` IN (6815, 6816);
INSERT INTO `conversation_template` (`Id`, `FirstLineId`, `LastLineEndTime`, `ScriptName`, `VerifiedBuild`) VALUES
(6815, 15676, 4120, '', 26972), -- The demons underestimate your power. Punish them for their hubris.
(6816, 15695, 4320, '', 26972); -- The fools think they can stand against you. Show them the price of their arrogance!
DELETE FROM `conversation_line_template` WHERE `Id` IN (15676, 15695);
INSERT INTO `conversation_line_template` (`Id`, `StartTime`, `UiCameraID`, `ActorIdx`, `Flags`, `VerifiedBuild`) VALUES
(15676, 0, 82, 0, 0, 26972),
(15695, 0, 99, 0, 0, 26972);
-- Kayn and Altruis when Varedis defeated
DELETE FROM `conversation_actors` WHERE `ConversationId` IN (6817, 6818);
INSERT INTO `conversation_actors` (`ConversationId`, `ConversationActorId`, `ConversationActorGuid`, `Idx`, `VerifiedBuild`) VALUES
(6817, 60432, 0, 0, 26972), -- Kayn
(6818, 60433, 0, 0, 26972); -- Altruis
DELETE FROM `conversation_line_template` WHERE `Id` IN (15696, 15697, 15698);
INSERT INTO `conversation_line_template` (`Id`, `StartTime`, `UiCameraID`, `ActorIdx`, `Flags`, `VerifiedBuild`) VALUES
(15696, 0, 99, 0, 0, 26972),
(15697, 3720, 99, 0, 0, 26972),
(15698, 0, 82, 0, 0, 26972);
DELETE FROM `conversation_template` WHERE `Id` IN (6817, 6818);
INSERT INTO `conversation_template` (`Id`, `FirstLineId`, `LastLineEndTime`, `ScriptName`, `VerifiedBuild`) VALUES
(6817, 15698, 5620, '', 26972), -- Well done. We managed to clear the skies while you dealt with Varedis.
(6818, 15696, 8920, '', 26972); -- The Legion wont soon forget this day.
-- Creature fixes
UPDATE `creature_template` SET `minlevel`=100, `maxlevel`=100, `VehicleId`= 4275, `type`= 7, `spell1`= 0, `unit_flags2`= 2048 WHERE `entry`=94324;
UPDATE `creature_template` SET `minlevel`=100, `maxlevel`=100, `VehicleId`= 4275, `type`= 7, `ScriptName`= 'npc_illidari_felbat_101902' WHERE `entry`=101902;
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=101902;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES (101902, 46598, 1, 0);
UPDATE `gameobject_template` SET `castBarCaption`='Reigniting' WHERE `entry`=239985;
UPDATE `scene_template` SET `ScriptName`='scene_varedis_reveal' WHERE `ScriptPackageId`= 1452; -- Varedis Felsoul reveal
UPDATE `scene_template` SET `ScriptName`='scene_twinblades_looted' WHERE `ScriptPackageId`= 1462; -- Twinblades of the Deceiver Looted
UPDATE `scene_template` SET `ScriptName`='scene_camp_explosion' WHERE `ScriptPackageId`= 1411; -- Camp Explosion
-- Graveyards
DELETE FROM `graveyard_zone` WHERE `GhostZone` IN (7637, 7502);
INSERT INTO `graveyard_zone` (`ID`, `GhostZone`, `Faction`, `Comment`) VALUES
(5097, 7637, 0, '7.0 Artifacts - Havoc DH Acquisition Graveyard - GJC'),
(5313, 7637, 0, '7.0 Artifacts - Havoc Demon Hunter Scenario - Start'),
(5362, 7637, 0, '7.0 Artifacts - Havoc DH Acquisition GY - Stage 4 - GJC'),
(5376, 7502, 0, '1498 - Artifact - Havoc Acquisition');
-- Phase WIP
DELETE FROM `phase_area` WHERE `AreaId`=7768 AND `PhaseId`=251;
DELETE FROM `phase_area` WHERE `AreaId`=7768 AND `PhaseId`=280;
INSERT INTO `phase_area` (`AreaId`, `PhaseId`, `Comment`) VALUES
(7768, 280, 'PHASE - CONDITION_QUESTSTATE');
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=26 AND `ConditionTypeOrReference`=47 AND `SourceGroup`=251 AND `SourceEntry`=7768 AND `ConditionValue1`=39247;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=26 AND `ConditionTypeOrReference`=47 AND `SourceGroup`=280 AND `SourceEntry`=7768 AND `ConditionValue1`=39247;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
('26', '280', '7768', '0', '0', '47', '0', '39247', '8', '0', '0', '0', '0', '', 'Phase 280 on Felsoul Hold when quest 39247 taken');
DELETE FROM `phase_area` WHERE `AreaId`=7768 AND `PhaseId`=281;
INSERT INTO `phase_area` (`AreaId`, `PhaseId`, `Comment`) VALUES
(7768, 281, 'PHASE - CONDITION_QUESTSTATE');
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=26 AND `ConditionTypeOrReference`=47 AND `SourceGroup`=251 AND `SourceEntry`=7768 AND `ConditionValue1`=41119;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=26 AND `ConditionTypeOrReference`=47 AND `SourceGroup`=281 AND `SourceEntry`=7768 AND `ConditionValue1`=41119;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
('26', '281', '7768', '0', '0', '47', '0', '41119', '8', '0', '0', '0', '0', '', 'Phase 281 on Felsoul Hold when quest 41119 taken');
DELETE FROM `phase_area` WHERE `AreaId`=7768 AND `PhaseId`=252;
DELETE FROM `phase_area` WHERE `AreaId`=7768 AND `PhaseId`=282;
INSERT INTO `phase_area` (`AreaId`, `PhaseId`, `Comment`) VALUES
(7768, 282, 'PHASE - CONDITION_QUESTSTATE');
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=26 AND `ConditionTypeOrReference`=47 AND `SourceGroup`=252 AND `SourceEntry`=7768 AND `ConditionValue1`=42125;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=26 AND `ConditionTypeOrReference`=47 AND `SourceGroup`=282 AND `SourceEntry`=7768 AND `ConditionValue1`=42125;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
('26', '282', '7768', '0', '0', '47', '0', '42125', '8', '0', '0', '0', '0', '', 'Phase 252 on Felsoul Hold when quest 42125 taken');
DELETE FROM `phase_area` WHERE `AreaId`=7768 AND `PhaseId`=169;

