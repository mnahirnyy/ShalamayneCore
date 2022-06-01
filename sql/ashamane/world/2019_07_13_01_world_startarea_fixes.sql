-- Draenei Start Zone Quest Fixes
DELETE FROM `creature_text` WHERE `CreatureID`=17312 AND `GroupID` BETWEEN 0 AND 6;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(17312, 0, 0, 'Our house is this way, through the thicket.', 12, 0, 100, 0, 0, 0, 0, 0, 'magwin SAY_START'),
(17312, 1, 0, 'Help me!', 12, 0, 100, 0, 0, 0, 41763, 0, 'magwin SAY_AGGRO'),
(17312, 2, 0, 'My poor family. Everything has been destroyed.', 12, 0, 100, 0, 0, 0, 0, 0, 'magwin SAY_PROGRESS'),
(17312, 3, 0, 'Father! Father! You\'re alive!', 12, 0, 100, 0, 0, 0, 0, 0, 'magwin SAY_END1'),
(17312, 4, 0, 'You can thank $N for getting me back here safely, father.', 12, 0, 100, 0, 0, 0, 0, 0, 'magwin SAY_END2'),
(17312, 5, 0, '%s hugs her father.', 16, 0, 100, 0, 0, 0, 0, 0, 'magwin EMOTE_HUG'),
(17312, 6, 0, 'You can thank $N for getting me back here safely, father.', 12, 7, 100, 0, 0, 0, 13748, 0, 'magwin SAY_END2');
DELETE FROM `script_waypoint` WHERE `entry`=17312;
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES
(17312, 1, -4805.51, -11037.3, 3.04394, 0, ''),
(17312, 2, -4827.83, -11034.4, 1.74196, 0, ''),
(17312, 3, -4852.63, -11033.7, 2.20866, 0, ''),
(17312, 4, -4876.79, -11034.5, 3.17523, 0, ''),
(17312, 5, -4895.49, -11038.3, 9.39089, 0, ''),
(17312, 6, -4915.46, -11048.4, 12.3698, 0, ''),
(17312, 7, -4937.29, -11067, 13.858, 0, ''),
(17312, 8, -4966.58, -11067.5, 15.7548, 0, ''),
(17312, 9, -4993.8, -11056.5, 19.1753, 0, ''),
(17312, 10, -5017.84, -11052.6, 22.4766, 0, ''),
(17312, 11, -5039.71, -11058.5, 25.8316, 0, ''),
(17312, 12, -5057.29, -11045.5, 26.9725, 0, ''),
(17312, 13, -5078.83, -11037.6, 29.0534, 0, ''),
(17312, 14, -5104.16, -11039.2, 29.4402, 0, ''),
(17312, 15, -5120.78, -11039.5, 30.1421, 0, ''),
(17312, 16, -5140.83, -11039.8, 28.7881, 0, ''),
(17312, 17, -5161.2, -11040.1, 27.8795, 4000, ''),
(17312, 18, -5171.84, -11046.8, 27.1838, 0, ''),
(17312, 19, -5186, -11056.4, 20.2349, 0, ''),
(17312, 20, -5198.49, -11065.1, 18.8726, 0, ''),
(17312, 21, -5214.06, -11074.7, 19.2157, 0, ''),
(17312, 22, -5220.16, -11088.4, 19.8185, 0, ''),
(17312, 23, -5233.65, -11098.8, 18.3494, 0, ''),
(17312, 24, -5250.16, -11111.7, 16.439, 0, ''),
(17312, 25, -5268.19, -11125.6, 12.6683, 0, ''),
(17312, 26, -5286.27, -11130.7, 6.91225, 0, ''),
(17312, 27, -5317.45, -11137.4, 4.96345, 0, ''),
(17312, 28, -5334.85, -11154.4, 6.74266, 0, ''),
(17312, 29, -5353.87, -11171.6, 6.90391, 20000, ''),
(17312, 30, -5354.24, -11171.9, 6.89, 0, '');
DELETE FROM `creature_text` WHERE `CreatureID`=17318 AND `GroupID` BETWEEN 0 AND 3;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(17318, 0, 0, 'What\'s the big idea, Spark?', 12, 0, 100, 0, 0, 0, 0, 0, 'geezle GEEZLE_SAY_1'),
(17318, 1, 0, 'Relax, Spark! I have it all under control. We\'ll strip mine the Exodar right out from under \'em - making both you and I very, very rich in the process.', 12, 0, 100, 0, 0, 0, 13779, 0, 'geezle GEEZLE_SAY_4'),
(17318, 2, 0, 'Yes, sir. It won\'t happen again...', 12, 0, 100, 0, 0, 0, 13782, 0, 'geezle GEEZLE_SAY_7'),
(17318, 3, 0, 'What\'s the big idea, Spark? Why\'d you call for this meeting?', 12, 0, 100, 0, 0, 0, 13776, 0, 'geezle GEEZLE_SAY_1');
DELETE FROM `creature_text` WHERE `CreatureID`=17243 AND `GroupID` BETWEEN 0 AND 14;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(17243, 0, 0, 'Yes Master, all goes along as planned.', 12, 0, 100, 0, 0, 0, 14082, 0, 'engineer spark SAY_TEXT'),
(17243, 1, 0, '%s puts the shell to his ear.', 16, 0, 100, 0, 0, 0, 0, 0, 'engineer spark EMOTE_SHELL'),
(17243, 2, 0, 'Now I cut you!', 14, 0, 100, 0, 0, 0, 0, 0, 'engineer spark SAY_ATTACK'),
(17243, 3, 0, 'What\'s the big idea? You nearly blew my cover, idiot! I told you to put the compass and navigation maps somewhere safe - not out in the open for any fool to discover.', 12, 0, 100, 0, 0, 0, 13777, 0, 'geezle SPARK_SAY_2'),
(17243, 4, 0, 'The Master has gone to great lengths to secure information about the whereabouts of the Exodar. You could have blown the entire operation, including the cover of our spy on the inside.', 12, 0, 100, 0, 0, 0, 13778, 0, 'geezle SPARK_SAY_3'),
(17243, 5, 0, 'Relax? Do you know what Kael\'thas does to those that fail him, Geezle? Eternal suffering and pain... Do NOT screw this up, fool.', 12, 0, 100, 0, 0, 0, 13780, 0, 'geezle SPARK_SAY_5'),
(17243, 6, 0, 'Our Bloodmyst scouts have located our contact. The fool, Velen, will soon leave himself open and defenseless -- long enough for us to strike! Now get out of my sight before I vaporize you...', 12, 0, 100, 0, 0, 0, 13781, 0, 'geezle SPARK_SAY_6'),
(17243, 7, 0, 'picks up the naga flag.', 16, 0, 100, 0, 0, 0, 0, 0, 'geezle EMOTE_SPARK'),
(17243, 8, 0, 'Does it frighten you to know that there are those that would serve the Legion with such devotion as to remain unwavering citizens of your pointless civilizations until called upon?', 12, 0, 100, 0, 0, 0, 0, 0, 'spark text on fight'),
(17243, 9, 0, 'Live in fear, die by the will of Kael\'thas... It\'s all the same.', 12, 0, 100, 0, 0, 0, 0, 0, 'spark text on fight'),
(17243, 10, 0, 'And now, I cut you!', 12, 0, 100, 0, 0, 0, 0, 0, 'spark text on fight'),
(17243, 11, 0, 'DIE!', 12, 0, 100, 0, 0, 0, 0, 0, 'spark text on fight'),
(17243, 12, 0, 'I wonder if you can really hear the ocean in these things.', 12, 0, 100, 0, 0, 0, 0, 0, 'spark text on emote shell'),
(17243, 13, 0, '%s holds the shell up to his ear.', 16, 7, 100, 0, 0, 0, 14084, 0, 'engineer spark EMOTE_SHELL'),
(17243, 14, 0, '%s picks up the naga flag.', 16, 0, 100, 0, 0, 0, 13775, 0, 'geezle EMOTE_SPARK');
UPDATE `creature_template` SET `AIName`='', `ScriptName`='npc_geezle_17318' WHERE `entry`=17318;
UPDATE `creature_template` SET `AIName`='', `ScriptName`='npc_magwin_17312' WHERE `entry`=17312;
DELETE FROM `creature_queststarter` WHERE `id`='17311' AND `quest`='9528';

DELETE FROM `item_script_names` WHERE `Id`='24318';
INSERT INTO `item_script_names` (`Id`, `ScriptName`) VALUES (24318, 'item_water_sample_flask_24318');
DELETE FROM `spell_script_names` WHERE `spell_id`='31549';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (31549, 'spell_bloodmyst_water_sample');
UPDATE `gameobject` SET `spawntimesecs`=300 WHERE `guid`=49517;
UPDATE `quest_template_addon` SET `SpecialFlags` = '0' WHERE `ID` = '9625';
SET @ENTRY := 17824;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,62,0,100,0,7533,0,0,0,33,17974,0,0,0,0,0,7,0,0,0,0,0,0,0,"Captured Sunhawk - On Gossip - Kill Credit");
UPDATE `gameobject` SET `position_x` = '-2310.18' , `position_y` = '-11265.89' WHERE `guid` = '39406';
DELETE FROM `gameobject` WHERE `id` IN (SELECT `entry` FROM `gameobject_template` WHERE `name`='Bristlelimb Cage' AND `entry` <> 181714);
-- Razormaw (17592) SAI fixes quest 9689
SET @ENTRY  := 17592;
UPDATE `creature_template` SET `AIName`= 'SmartAI',`ScriptName`='' WHERE `entry`=@ENTRY;
DELETE FROM `creature_template_addon` WHERE `entry`=@ENTRY;
INSERT INTO `creature_template_addon` (`entry`,`bytes1`,`bytes2`) VALUES (@ENTRY,50331648,1);
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,6000,6000,7000,9000,11,31279,0,0,0,0,0,2,0,0,0,0,0,0,0,'Razormaw - Combat - Cast Swipe'),
(@ENTRY,0,1,0,0,0,100,0,26000,30000,26000,30000,11,8873,0,0,0,0,0,1,0,0,0,0,0,0,0,'Razormaw - Combat - Cast Flame Breath'),
(@ENTRY,0,2,0,0,0,50,0,12000,12000,12000,12000,11,14100,0,0,0,0,0,1,0,0,0,0,0,0,0,'Razormaw - Combat - Cast Terrifying Roar'),
(@ENTRY,0,3,0,11,0,100,0,0,0,0,0,53,1,1759200,0,0,0,0,1,0,0,0,0,0,0,0,'Razormaw - On spawn - Load Path'),
(@ENTRY,0,4,0,40,0,100,0,10,1759200,0,0,19,256,0,0,0,0,0,1,0,0,0,0,0,0,0,'Razormaw - On Reach waypoint - Remove unitflag');
-- Waypoints for Razormaw
DELETE FROM `waypoints` WHERE `entry` IN (1759200);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
(1759200,1,-1139.441,-12506.60,111.7433, 'Razormaw'),
(1759200,2,-1136.979,-12507.40,111.7433, 'Razormaw'),
(1759200,3,-1211.237,-12546.23,150.4277, 'Razormaw'),
(1759200,4,-1203.349,-12551.60,150.4277, 'Razormaw'),
(1759200,5,-1204.031,-12541.80,188.7888, 'Razormaw'),
(1759200,6,-1206.282,-12542.65,173.2891, 'Razormaw'),
(1759200,7,-1202.930,-12539.74,160.9559, 'Razormaw'),
(1759200,8,-1201.284,-12529.25,134.3167, 'Razormaw'),
(1759200,9,-1204.178,-12483.84,115.039, 'Razormaw'),
(1759200,10,-1204.349,-12465.61,104.7762, 'Razormaw'),
(1759200,11,-1206.812,-12456.89,93.81462, 'Razormaw');
SET @ENTRY := 49161;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 3, 49162, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Altered Beast - On Aggro - Morph'),
(@ENTRY, 0, 1, 0, 7, 0, 100, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Altered Beast - On Evade - DeMorph');
UPDATE `creature_template` SET `AIName`='', `ScriptName`='npc_uncorrupted_animal' WHERE `entry` IN (33023, 33024);
UPDATE `gameobject_template` SET `AIName`='', `ScriptName`='go_secure_animal_cage' WHERE `entry` IN (194124, 194133);
UPDATE `creature` SET `spawndist`=0, `MovementType`=0 WHERE `id`=33023;
-- flight master in Blood Watch
UPDATE `creature_template` SET `npcflag` = '8193' WHERE `entry` = '17554';
UPDATE `gossip_menu_option` SET `OptionType` = 4, `OptionNpcFlag` = 8192 WHERE `MenuId` = 7470;
-- first aid trainer in Blood Watch
DELETE FROM `npc_trainer` WHERE `ID` = 17424;
INSERT INTO `npc_trainer` (`ID`, `SpellID`, `MoneyCost`, `ReqSkillLine`, `ReqSkillRank`, `ReqLevel`, `Index`) VALUES
(17424,-202007,0,0,0,0,0),
(17424,3273,100,0,0,0,0),
(17424,3274,500,129,50,0,0),
(17424,3276,100,129,40,0,0),
(17424,3277,250,129,80,0,0),
(17424,3278,1000,129,115,0,0),
(17424,7924,1000,129,125,0,0),
(17424,7928,5000,129,150,0,0),
(17424,7929,5000,129,180,0,0),
(17424,7934,250,129,80,0,0),
(17424,10840,10000,129,210,0,0),
(17424,10841,10000,129,240,0,0),
(17424,10846,25000,129,225,0,0),
(17424,18629,20000,129,260,0,0),
(17424,18630,20000,129,290,0,0),
(17424,27028,100000,129,275,0,0),
(17424,27032,20000,129,300,0,0),
(17424,27033,40000,129,330,0,0),
(17424,45542,150000,129,350,0,0),
(17424,45545,40000,129,350,0,0),
(17424,45546,60000,129,390,0,0),
(17424,74556,60000,129,425,0,0),
(17424,74557,80000,129,475,0,0),
(17424,74558,15000,129,525,0,0),
(17424,74559,250000,129,425,0,0),
(17424,88893,80000,129,525,0,0),
(17424,102697,90000,129,500,0,0),
(17424,102698,110000,129,550,0,0),
(17424,110406,300000,129,500,0,0);
UPDATE `gossip_menu_option` SET `OptionType` = '5' , `OptionNpcFlag` = '16' WHERE `MenuId` = '7455' AND `OptionIndex` = '0';