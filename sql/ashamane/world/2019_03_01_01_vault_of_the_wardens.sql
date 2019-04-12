-- Quest id: 38727 - "Stop the Bombardment" - Add missing banner
DELETE FROM `gameobject` WHERE `guid` = 20375675;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(20375675, 243965, 1481, 7705, 7747, 0, 0, 0, 1813.36, 1543.43, 88.3732, 5.74205, 0, 0, 0.267278, -0.963619, 7200, 255, 1, 22423);

DELETE FROM `creature_queststarter` WHERE `id` IN (92718, 92980, 92986, 92984, 97643, 96675, 97644, 97978);
INSERT INTO `creature_queststarter` (`id`, `quest`) VALUES  
(92718, 38672), -- breaking out
(92980, 38690), -- rise of the illidari
(92986, 38689), -- fel infusion
(92718, 38723), -- stop guldan (Havoc) (https://www.wowhead.com/search?q=stop+gul%27dan)
(92718, 40253), -- stop guldan (Vengeance)
(92984, 39682), -- grand theft felbat
(97643, 39685), -- frozen in time
(97643, 39684), -- beam me up
(96675, 39683), -- forged in fire (Havoc)
(96675, 40254), -- forged in fire (Vengeance)
(96675, 39686), -- all the way up
(97644, 40373), -- -- a new direction (https://www.wowhead.com/search?q=A+New+Direction)
(97644, 39694), -- between us and freedom (havoc H)
(97644, 39688), -- between us and freedom (havoc A)
(97644, 40255), -- between us and freedom (vengeance A)
(97644, 40256), -- between us and freedom (vengeance H)
(97978, 39689), -- Illidari we are leaving (A)
(97978, 39690); -- Illidari we are leaving (H)

DELETE FROM `creature_questender` WHERE `quest` IN (40253, 38723);
INSERT INTO `creature_questender` (`id`,`quest`) VALUES (92984, 40253), (92984, 38723);

UPDATE `creature_template` SET `ScriptName` = 'npc_kayn_3' WHERE `entry` = 96665;
UPDATE `creature_template` SET `ScriptName` = 'npc_altruis' WHERE `entry` = 92986;
UPDATE `creature_template` SET `ScriptName` = 'npc_fel_infusion' WHERE `entry` = 92776;
UPDATE `creature_template` SET `ScriptName` = 'npc_fel_infusion' WHERE `entry` = 92782;
UPDATE `creature_template` SET `ScriptName` = 'npc_kayn_cell' WHERE `entry` = 103658;
UPDATE `creature_template` SET `ScriptName` = 'npc_altruis_cell' WHERE `entry` = 103655;
UPDATE `creature_template` SET `ScriptName` = 'npc_korvas_bloodthorn' WHERE `entry` = 97644;
UPDATE `creature_template` SET `ScriptName` = 'npc_khadgar' WHERE `entry` = 97978;
UPDATE `creature_template` SET `ScriptName` = 'npc_maiev_shadowsong' WHERE `entry` = 92718;
UPDATE `creature_template` SET `ScriptName` = 'npc_sledge' WHERE `entry` = 92990;
UPDATE `creature_template` SET `ScriptName` = 'npc_crusher' WHERE `entry` = 97632;
UPDATE `creature_template` SET `ScriptName` = 'npc_vow_immolanth' WHERE `entry` = 96682;
UPDATE `creature_template` SET `ScriptName` = 'npc_vow_ashgolm' WHERE `entry` = 96681;
UPDATE `creature_template` SET `ScriptName` = 'npc_bastillax' WHERE `entry` = 96783;
UPDATE `creature_template` SET `ScriptName` = 'npc_legion_portal' WHERE `entry` = 99501;

UPDATE `gameobject_template` SET `ScriptName` = 'go_reflective_mirror' WHERE `entry` = 244449;
UPDATE `gameobject_template` SET `ScriptName` = 'go_pool_of_judgements' WHERE `entry` = 244455;
UPDATE `gameobject_template` SET `ScriptName` = 'go_warden_ascent' WHERE `entry` = 244644;

UPDATE `creature_template` SET `speed_walk` = 1, `speed_run` = 1 WHERE `entry` = 99632;
UPDATE `creature_template` SET `speed_walk` = 1, `speed_run` = 1 WHERE `entry` = 99631;
UPDATE `creature_template` SET `npcflag` = 3 WHERE `entry` IN (92980, 92984);
UPDATE `creature_template` SET `npcflag` = 1 WHERE `entry` IN (103658, 103655);
UPDATE `creature_template` SET `HealthModifier` = 20 WHERE `entry` = 96682;

UPDATE `quest_template_addon` SET `PrevQuestID` = 38672 WHERE `ID` = 38690; -- Rise of the Illidari
UPDATE `quest_template_addon` SET `PrevQuestID` = 38672, `ScriptName` = 'q_fel_infusion' WHERE `ID` = 38689; -- Fel Infusion
UPDATE `quest_template_addon` SET `ScriptName` = 'q_frozen_in_time' WHERE `ID` = 39685; -- Frozen In Time test script
UPDATE `quest_template_addon` SET `PrevQuestID` = 38690, `NextQuestID` = 39682, `ExclusiveGroup` = 38723 WHERE `ID` = 38723; -- Stop Guldan
UPDATE `quest_template_addon` SET `PrevQuestID` = 38690, `NextQuestID` = 39682, `ExclusiveGroup` = 38723 WHERE `ID` = 40253; -- Stop Guldan

UPDATE `quest_template_addon` SET `PrevQuestID` = 39682, `NextQuestID` = 39686, `ExclusiveGroup` = -39685 WHERE `ID` = 39685; -- Frozen In Time
UPDATE `quest_template_addon` SET `PrevQuestID` = 39682, `NextQuestID` = 39686, `ExclusiveGroup` = -39685 WHERE `ID` = 39684; -- Beam Me Up

UPDATE `quest_template_addon` SET `PrevQuestID` = 39682, `NextQuestID` = 39686, `ExclusiveGroup` = 39683 WHERE `ID` = 39683; -- Forged In Fire
UPDATE `quest_template_addon` SET `PrevQuestID` = 39682, `NextQuestID` = 39686, `ExclusiveGroup` = 39683 WHERE `ID` = 40254; -- Forged In Fire

UPDATE `quest_template_addon` SET `PrevQuestID` = 39686 WHERE `ID` = 40373; -- A New Direction

UPDATE `quest_template_addon` SET `PrevQuestID` = 40373, `NextQuestID` = 39690, `ExclusiveGroup` = 39694 WHERE `ID` = 39694; -- between us and freedom
UPDATE `quest_template_addon` SET `PrevQuestID` = 40373, `NextQuestID` = 39689, `ExclusiveGroup` = 39694 WHERE `ID` = 39688; -- between us and freedom
UPDATE `quest_template_addon` SET `PrevQuestID` = 40373, `NextQuestID` = 39689, `ExclusiveGroup` = 39694 WHERE `ID` = 40255; -- between us and freedom
UPDATE `quest_template_addon` SET `PrevQuestID` = 40373, `NextQuestID` = 39690, `ExclusiveGroup` = 39694 WHERE `ID` = 40256; -- between us and freedom

UPDATE `creature_loot_template` SET `Chance` = 82, `QuestRequired` = 0, `LootMode` = 1, `GroupId` = 0, `MinCount` = 1, `MaxCount` = 1 WHERE `Entry` = 97370 AND `Item` = 133313;

DELETE FROM `spell_script_names` WHERE `spell_id` = 204588; -- activate countermeasures
DELETE FROM `npc_spellclick_spells` WHERE `spell_id` = 204588;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (204588, 'spell_activate_countermeasure');
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES (99709, 204588, 1, 0), (99731, 204588, 1, 0), (99732, 204588, 1, 0);

DELETE FROM `gameobject` WHERE `guid` = 210120188; -- Vault of Silence door
DELETE FROM `gameobject` WHERE `guid` = 20373116; -- small chest
DELETE FROM `gameobject` WHERE `guid` = 20373163; -- small chest
INSERT INTO `gameobject` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnDifficulties`,`phaseUseFlags`,`PhaseId`,`PhaseGroup`,`terrainSwapMap`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`,`isActive`,`ScriptName`,`VerifiedBuild`) VALUES
(210120188, 244925, 1468, 7814, 7814, 0, 0, 0, 0, -1, 4325.66, -576.49, -281.783, 4.65537, -0, -0, -0.726975, 0.686664, 300, 255, 1, 0, '', 22423);
DELETE FROM `gameobject` WHERE `guid` IN (20373129, 20373134); -- Vault of Betrayer doors
UPDATE `gameobject` SET `state` = 1 WHERE `guid` IN (20373013, 20373001, 20373016, 20373071, 20373066, 20373082, 20372994, 20373064);
DELETE FROM `creature` WHERE `guid` IN (20542659, 20542665);

DELETE FROM `creature_sparring_template` WHERE `AttackerEntry` IN (92984, 92985);
INSERT INTO `creature_sparring_template` (`AttackerEntry`, `VictimEntry`, `HealthLimitPct`) VALUES
(92984, 97632, 100),
(92985, 92990, 100);

DELETE FROM `creature_text` WHERE `CreatureID` IN (92718, 99632, 99631, 96682);
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `Comment`) VALUES
(92718, 0, 0, 'I will need your help to stop Gul\'dan. Free the other Illidari, quickly!', 12, 0, 100, 0, 0, 57338, 0, 0, 'Maiev to Player'),
(99632, 0, 0, 'How many years were wasted in that cell?', 12, 0, 100, 0, 0, 57343, 0, 0, 'Altruis on freed'),
(99631, 0, 0, 'I am awake? How is this possible?', 12, 0, 100, 0, 0, 57294, 0, 0, 'Kayn on freed'),
(99631, 1, 0, 'Why did you let THAT one free? He opposed Lord Illidan!', 12, 0, 100, 0, 0, 57320, 0, 0, 'Kayn\'s response of Altruis freed'),
(99632, 1, 0, 'It has been a long time, Kayn. I still believe in the cause. But, I do not blindly follow anyone... even Illidan.', 12, 0, 100, 0, 0, 57285, 0, 0, 'Altruis to Kayn'),
(99631, 2, 0, 'Why would Maiev free us? There could only be one reason...', 12, 0, 100, 0, 0, 57387, 0, 0, 'Kayns to Player when quest rewarded'),
(96682, 0, 0, 'Join me, demon hunters. I will increase your power beyond imagining!', 12, 0, 100, 0, 0, 57358, 0, 0, 'Immolanth on 60 pct'),
(96682, 1, 0, 'The wardens would keep us rotting here forever. Why do you fight on their side?', 12, 0, 100, 0, 0, 57359, 0, 0, 'Immolanth on 20 pct');

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=92718;
DELETE FROM `smart_scripts` WHERE `entryorguid`=92718 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(92718,0,0,0,19,0,100,0,38672,0,0,0,66,0,0,0,0,0,0,21,5,0,0,0,0,0,0,"Maiev - On Quest 'Breaking Out' Taken - Set Orientation Closest Player"),
(92718,0,1,0,19,0,100,0,38672,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0,0,0,0,"Maiev - On Quest 'Breaking Out' Taken - Say Line 0");

UPDATE `quest_template_addon` SET `ScriptName`='q_breaking_out' WHERE `ID`=38672;
UPDATE `creature_template` SET `ScriptName`='' WHERE `entry`=92718;

-- Wrath Lord Lekos SAI
SET @LORD_LEKOS := 97069;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@LORD_LEKOS;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@LORD_LEKOS AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@LORD_LEKOS,0,0,0,0,0,100,1,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0,0,0,0,"Wrath-Lord Lekos - In Combat - Say Line 0 (No Repeat)"),
(@LORD_LEKOS,0,1,0,0,0,100,0,5000,8000,12000,15000,11,200918,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wrath-Lord Lekos - In Combat - Cast 'Fel Shield Blast'"),
(@LORD_LEKOS,0,2,0,0,0,100,0,10000,10000,10000,25000,11,200929,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wrath-Lord Lekos - In Combat - Cast 'Furious Roar'"),
(@LORD_LEKOS,0,3,0,2,0,100,0,0,40,22000,25000,11,200936,2,0,0,0,0,1,0,0,0,0,0,0,0,"Wrath-Lord Lekos - Between 0-40% Health - Cast 'Spiked Bulwark'");

DELETE FROM `creature_text` WHERE `CreatureID` = 97069;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(97069, 0, 0, 'Lord Gul\'dan will lead us to victory. You cannot stop us.', 12, 0, 100, 0, 0, 57312, 0, 0, 'Wrath Lord Lekos to Player'),
(97069, 0, 1, 'Your world is the last standing. It, too, will be purged.', 12, 0, 100, 0, 0, 57298, 0, 0, 'Wrath Lord Lekos to Player'),
(97069, 0, 2, 'All goes according to HIS plan.', 12, 0, 100, 0, 0, 57392, 0, 0, 'Wrath Lord on Death');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 19 AND `SourceGroup` =0 AND `SourceEntry` IN (38723, 40253, 39683, 40254, 39694, 39688, 40255, 40256) AND `ConditionValue1` IN (212612, 212613);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
('19', '0', '38723', '0', '0', '1', '0', '212612', '0', '0', '0', '0', '0', '', 'Allow Quest "Stop Guldan" 38723 only for Havoc DH'),
('19', '0', '40253', '0', '0', '1', '0', '212613', '0', '0', '0', '0', '0', '', 'Allow Quest "Stop Guldan" only for Vengeance DH'),
('19', '0', '39683', '0', '0', '1', '0', '212612', '0', '0', '0', '0', '0', '', 'Allow Quest "Forged In Fire" only for Havoc DH'),
('19', '0', '40254', '0', '0', '1', '0', '212613', '0', '0', '0', '0', '0', '', 'Allow Quest "Forged In Fire" only for Vengeance DH'),
('19', '0', '39694', '0', '0', '1', '0', '212612', '0', '0', '0', '0', '0', '', 'Allow Quest "Between Us And Freedom" only for Havoc DH'),
('19', '0', '39688', '0', '0', '1', '0', '212612', '0', '0', '0', '0', '0', '', 'Allow Quest "Between Us And Freedom" only for Havoc DH'),
('19', '0', '40255', '0', '0', '1', '0', '212613', '0', '0', '0', '0', '0', '', 'Allow Quest "Between Us And Freedom" only for Vengeance DH'),
('19', '0', '40256', '0', '0', '1', '0', '212613', '0', '0', '0', '0', '0', '', 'Allow Quest "Between Us And Freedom" only for Vengeance DH');

-- Kethrazor SAI
SET @KETHRAZOR := 96997;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@KETHRAZOR;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@KETHRAZOR AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@KETHRAZOR,0,0,0,0,0,100,1,0,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0,0,0,0,"Kethrazor - In Combat - Say Line 0 (No Repeat)"),
(@KETHRAZOR,0,1,0,0,0,100,0,5000,5000,12000,15000,11,201038,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kethrazor - In Combat - Cast 'Mind Spike'"),
(@KETHRAZOR,0,2,0,0,0,100,0,10000,10000,18000,25000,11,201033,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kethrazor - In Combat - Cast 'Seeping Eyes of Kethrazor'"),
(@KETHRAZOR,0,3,0,0,0,100,0,20000,22000,30000,32000,11,200999,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kethrazor - In Combat - Cast 'Explosive Eyes of Kethrazor'"),
(@KETHRAZOR,0,4,0,6,0,100,0,0,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0,0,0,0,"Kethrazor - On Just Died - Say Line 1");

DELETE FROM `creature_text` WHERE `CreatureID` = 96997;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
('96997', '0', '0', 'Your efforts are fruitless, demon hunter. Lord Gul\'dan sees all.', '14', '0', '100', '0', '0', '57341', '0', '0', 'Kethrazor to Player'),
('96997', '1', '0', 'In the end, you will all succumb to the Legion...', '14', '0', '100', '0', '0', '57368', '0', '0', 'Kethrazor to Player');

-- Seeping Inquisitor Eye SAI
SET @SEEPING_EYE := 101907;
UPDATE `creature_template` SET `faction`=90, `AIName`="SmartAI" WHERE `entry`=@SEEPING_EYE;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@SEEPING_EYE AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@SEEPING_EYE,0,0,0,0,0,100,0,0,0,0,0,11,201035,0,0,0,0,0,2,0,0,0,0,0,0,0,"Seeping Inquisitor Eye - In Combat - Cast 'Some Aura'");

-- Explosive Inquisitor Eye SAI
SET @EXPLOSIVE_EYE := 101901;
UPDATE `creature_template` SET `faction`=90, `AIName`="SmartAI" WHERE `entry`=@EXPLOSIVE_EYE;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@EXPLOSIVE_EYE AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@EXPLOSIVE_EYE,0,0,0,0,0,100,1,0,0,0,0,11,201028,0,0,0,0,0,1,0,0,0,0,0,0,0,"Explosive Inquisitor Eye - In Combat - Cast 'Explosive Shadows' (No Repeat)"),
(@EXPLOSIVE_EYE,0,1,0,0,0,100,1,0,0,0,0,11,201015,0,0,0,0,0,1,0,0,0,0,0,0,0,"Explosive Inquisitor Eye - In Combat - Cast 'Fixate' (No Repeat)");

-- Glazer SAI
SET @GLAZER := 96680;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@GLAZER;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@GLAZER AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@GLAZER,0,0,0,1,0,100,1,1000,1000,1000,1000,11,191915,2,0,0,0,0,1,0,0,0,0,0,0,0,"Glazer - Out of Combat - Cast 'Focusing' (No Repeat)"),
(@GLAZER,0,1,0,1,0,100,0,2000,2000,15000,17000,11,196460,2,0,0,0,0,1,0,0,0,0,0,0,0,"Glazer - Out of Combat - Cast 'Lingering Gaze' (No Repeat)"),
(@GLAZER,0,2,0,1,0,100,0,3000,4000,20000,21000,11,196462,2,0,0,0,0,1,0,0,0,0,0,0,0,"Glazer - Out of Combat - Cast 'Pulse'");

-- Altruis near Glazer SAI
SET @ALTRUIS := 102391;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ALTRUIS;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ALTRUIS AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ALTRUIS,0,0,0,10,0,100,1,1,30,0,0,1,0,10000,0,0,0,0,18,30,0,0,0,0,0,0,"Altruis - Within 1-30 Range Out of Combat LoS - Say Line 0 (No Repeat)"),
(@ALTRUIS,0,1,0,20,0,100,0,39684,0,0,0,1,1,10000,0,0,0,0,1,0,0,0,0,0,0,0,"Altruis - On Quest 'Beam Me Up' Completed - Say Line 1");

DELETE FROM `creature_text` WHERE `CreatureID` = @ALTRUIS;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `Comment`) VALUES
(@ALTRUIS,0,0,'$n, the creature\'s destructive beam is focused upon me. Redirect the final mirror to shatter its shield!',12,0,100,0,0,57332,0,0,'Altruis to Player'),
(@ALTRUIS,1,0,'The shield is broken! Quickly, everyone out while the creature is stunned!',12,0,100,0,0,57333,0,0,'Altruis to Player');

-- Mirana Starlight SAI
SET @MIRANA := 99451;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@MIRANA;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@MIRANA AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@MIRANA,0,0,0,0,0,100,0,0,0,3400,4700,11,195783,64,0,0,0,0,2,0,0,0,0,0,0,0,"Mirana - In Combat - Cast 'Fan of Blades'"),
(@MIRANA,0,1,0,0,0,100,0,5000,8000,12000,15000,11,191026,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mirana - In Combat - Cast 'Throwing Blade'");

-- Drelanin Whisperwind SAI
SET @DRELANIN := 96847;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@DRELANIN;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@DRELANIN AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@DRELANIN,0,0,0,10,0,100,1,1,15,0,0,1,0,10000,0,0,0,0,18,15,0,0,0,0,0,0,"Drelanin - Within 1-15 Range Out of Combat LoS - Say Line 0 (No Repeat)"),
(@DRELANIN,0,1,0,0,0,100,0,5000,8000,18000,22000,11,189469,0,0,0,0,0,2,0,0,0,0,0,0,0,"Drelanin - In Combat - Cast 'Turn Kick'"),
(@DRELANIN,0,2,0,0,0,100,0,2000,5000,12000,15000,11,195783,0,0,0,0,0,2,0,0,0,0,0,0,0,"Drelanin - In Combat - Cast 'Fan of Blades'");

DELETE FROM `creature_text` WHERE `CreatureID` = @DRELANIN;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `Comment`) VALUES
(@DRELANIN,0,0,'I hope Maiev was right about freeing you, demon hunter. Go on - I will hold the line.',12,0,100,0,0,57291,0,0,'Drelanin to Player');

SET @JACE := 96653;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@JACE;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@JACE AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@JACE,0,0,0,10,0,100,1,1,30,0,0,1,0,10000,0,0,0,0,18,30,0,0,0,0,0,0,"Jace Darkweaver - Within 1-30 Range Out of Combat LoS - Say Line 0 (No Repeat)");

DELETE FROM `creature_text` WHERE `CreatureID` = @JACE;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `Comment`) VALUES
(@JACE,0,0,'Kayn and Altruis have already gone ahead. Take this felbat and join them.',12,0,100,0,0,57299,0,0,'Jace Darkweaver to Player');

SET @KORVAS_1 := 97643;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@KORVAS_1;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@KORVAS_1 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@KORVAS_1,0,0,0,10,0,100,1,1,15,0,0,1,0,10000,0,0,0,0,18,15,0,0,0,0,0,0,"Korvas Bloodthorn - Within 1-15 Range Out of Combat LoS - Say Line 0 (No Repeat)"),
(@KORVAS_1,0,1,0,19,0,100,0,39685,0,0,0,1,1,10000,0,0,0,0,1,0,0,0,0,0,0,0,"Korvas Bloodthorn - On Quest 'Frozen In Time' Taken - Say Line 1"),
(@KORVAS_1,0,2,1,52,0,100,0,1,@KORVAS_1,0,0,1,2,5000,0,0,0,0,1,0,0,0,0,0,0,0,"Korvas Bloodthorn - On Text 1 Over - Say Line 2");

DELETE FROM `creature_text` WHERE `CreatureID` = @KORVAS_1;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `Comment`) VALUES
(@KORVAS_1,0,0,'This is sheer madness! The Wardens have lost control of their prison',12,0,100,0,0,57323,0,0,'Korvas Bloodthorn to Player'),
(@KORVAS_1,1,0,'Aside from us, the most powerful prisoners were sealed on this level. WERE being the operative word.',12,0,100,0,0,57324,0,0,'Korvas Bloodthorn to Player'),
(@KORVAS_1,2,0,'We cannot afford to lose Kayn and Altruis here. Waste no time and help them, quickly!',12,0,100,0,0,57397,0,0,'Korvas Bloodthorn to Player');

-- Cyana near Immolanth SAI
SET @CYANA := 96672;
DELETE FROM `creature_text` WHERE `CreatureID` = @CYANA;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `Comment`) VALUES
(@CYANA,0,0,'That was to0 close for my liking. $n, the demon\'s power is yours.',12,0,100,0,0,55229,0,0,'Cyana to Player');

-- Kayn near Ashgolm SAI
SET @KAYN_1 := 102393;
DELETE FROM `creature_text` WHERE `CreatureID` = @KAYN_1;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `Comment`) VALUES
(@KAYN_1,0,0,'Well done! The monster is contained. Let\'s meet up with the others.',12,0,100,0,0,55229,0,0,'Kayn to Player');

SET @ALLARI_1 := 96675;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ALLARI_1;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ALLARI_1 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ALLARI_1,0,0,0,19,0,100,0,39686,0,0,0,1,1,10000,0,0,0,0,1,0,0,0,0,0,0,0,"Allari the Souleater - On Quest 'All the way Up' Taken - Say Line 0");

DELETE FROM `creature_text` WHERE `CreatureID` = @ALLARI_1;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `Comment`) VALUES
(@ALLARI_1,0,0,'The elevator will be here shortly. The others are waiting for you above.',12,0,100,0,0,57356,0,0,'Allari the Souleater to Player');

SET @KORVAS_2 := 97644;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@KORVAS_2;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@KORVAS_2 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@KORVAS_2,0,0,0,10,0,100,1,1,15,0,0,1,0,10000,0,0,0,0,18,15,0,0,0,0,0,0,"Korvas Bloodthorn - Within 1-15 Range Out of Combat LoS - Say Line 0 (No Repeat)"),
(@KORVAS_2,0,1,0,19,0,100,0,39694,0,0,0,1,1,10000,0,0,0,0,1,0,0,0,0,0,0,0,"Korvas Bloodthorn - On Quest 'Between Us And Freedom - Say Line 1"),
(@KORVAS_2,0,2,0,19,0,100,0,39688,0,0,0,1,1,10000,0,0,0,0,1,0,0,0,0,0,0,0,"Korvas Bloodthorn - On Quest 'Between Us And Freedom - Say Line 1"),
(@KORVAS_2,0,3,0,19,0,100,0,40255,0,0,0,1,1,10000,0,0,0,0,1,0,0,0,0,0,0,0,"Korvas Bloodthorn - On Quest 'Between Us And Freedom - Say Line 1"),
(@KORVAS_2,0,4,0,19,0,100,0,40256,0,0,0,1,1,10000,0,0,0,0,1,0,0,0,0,0,0,0,"Korvas Bloodthorn - On Quest 'Between Us And Freedom - Say Line 1");

DELETE FROM `creature_text` WHERE `CreatureID` = @KORVAS_2;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `Comment`) VALUES
(@KORVAS_2,0,0,'Stop this foolish bickering. We do not have time for this!',12,0,100,0,0,57295,0,0,'Korvas Bloodthorn to Player'),
(@KORVAS_2,1,0,'Let\'s keep moving. The others are in the chamber just ahead.',12,0,100,0,0,57361,0,0,'Korvas Bloodthorn to Player');

SET @KHADGAR_1 := 97978;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@KHADGAR_1;
DELETE FROM `creature_text` WHERE `CreatureID` = @KHADGAR_1;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `Comment`) VALUES
(@KHADGAR_1,0,0,'I am Arhmage Khadgar, leader of the Kirin Tor.',12,0,100,0,0,57302,0,0,'Khadgar to Player'),
(@KHADGAR_1,1,0,'Demon Hunters, Azeroth needs your help.',12,0,100,0,0,57364,0,0,'Khadgar to Player');

-- Stop Guldan Scene
DELETE FROM `scene_template` WHERE `SceneId`=1016 AND `ScriptPackageID`=1423;
INSERT INTO `scene_template` (`SceneId`,`Flags`,`ScriptPackageID`,`ScriptName`) VALUES
(1016,26,1423,'scene_guldan_stealing_illidan_corpse');

DELETE FROM `gameobject_template` WHERE `entry` IN (246559, 246560, 246562, 246561, 246557, 246556, 246555, 246558);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `Data24`, `Data25`, `Data26`, `Data27`, `Data28`, `Data29`, `Data30`, `Data31`, `Data32`, `RequiredLevel`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES
('246559','3','33263','Small Treasure Chest','','Opening','','1','57','246559','1','0','0','0','0','0','0','0','0','0','0','1','21400','0','0','0','110','3','0','0','0','0','0','0','0','0','0','0','64310','0','0','98','','','22423'),
('246560','3','33263','Small Treasure Chest','','Opening','','1','57','246560','1','0','0','0','0','0','0','0','0','0','0','1','21400','0','0','0','110','3','0','0','0','0','0','0','0','0','0','0','64311','0','0','98','','','22423'),
('246562','3','33263','Small Treasure Chest','','Opening','','1','57','246562','1','0','0','0','0','0','0','0','0','0','0','1','21400','0','0','0','110','3','0','0','0','0','0','0','0','0','0','0','64313','0','0','98','','','22423'),
('246561','3','33263','Small Treasure Chest','','Opening','','1','57','246561','1','0','0','0','0','0','0','0','0','0','0','1','21400','0','0','0','110','3','0','0','0','0','0','0','0','0','0','0','64312','0','0','98','','','22423'),
('246557','3','33263','Small Treasure Chest','','Opening','','1','57','246557','1','0','0','0','0','0','0','0','0','0','0','1','21400','0','0','0','110','3','0','0','0','0','0','0','0','0','0','0','64308','0','0','98','','','22423'),
('246556','3','33263','Small Treasure Chest','','Opening','','1','57','246556','1','0','0','0','0','0','0','0','0','0','0','1','21400','0','0','0','110','3','0','0','0','0','0','0','0','0','0','0','64307','0','0','98','','','22423'),
('246555','3','33263','Small Treasure Chest','','Opening','','1','57','246555','1','0','0','0','0','0','0','0','0','0','0','1','21400','0','0','0','110','3','0','0','0','0','0','0','0','0','0','0','64306','0','0','98','','','22423'),
('246558','3','33263','Small Treasure Chest','','Opening','','1','57','246558','1','0','0','0','0','0','0','0','0','0','0','1','21400','0','0','0','110','3','0','0','0','0','0','0','0','0','0','0','64309','0','0','98','','','22423');

DELETE FROM `gameobject_loot_template` WHERE `entry` IN (246559, 246560, 246562, 246561, 246557, 246556, 246555, 246558);
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `reference`, `chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
('246560', '129196', '0', '100', '0', '1', '1', '2', '3', 'Legion Heartstone'),
('246560', '129210', '0', '99', '0', '1', '0', '2', '2', 'Fel Crystal Fragments'),
('246562', '129210', '0', '100', '0', '1', '0', '2', '3', 'Fel Crystal Fragments'),
('246559', '129196', '0', '100', '0', '1', '0', '2', '4', 'Legion Heartstone'),
('246561', '129196', '0', '100', '0', '1', '1', '2', '3', 'Legion Heartstone'),
('246561', '129210', '0', '99', '0', '1', '0', '2', '2', 'Fel Crystal Fragments'),
('246557', '129196', '0', '100', '0', '1', '1', '2', '3', 'Legion Heartstone'),
('246557', '129210', '0', '99', '0', '1', '0', '2', '2', 'Fel Crystal Fragments'),
('246555', '129210', '0', '100', '0', '1', '0', '2', '3', 'Fel Crystal Fragments'),
('246558', '129196', '0', '100', '0', '1', '1', '2', '3', 'Legion Heartstone'),
('246558', '129210', '0', '99', '0', '1', '0', '2', '2', 'Fel Crystal Fragments'),
('246556', '129210', '0', '100', '0', '1', '0', '2', '3', 'Fel Crystal Fragments');

UPDATE `gameobject_template` SET `name`='Small Treasure Chest', `castBarCaption`='Opening' WHERE `entry` IN (244689, 246309, 246353);
UPDATE `creature` SET `spawntimesecs`=120 WHERE `id`=92776 AND `map`=1468;
UPDATE `creature` SET `spawntimesecs`=120 WHERE `id`=92782 AND `map`=1468;

DELETE FROM `graveyard_zone` WHERE `GhostZone` IN (7871, 7866, 7864, 7819, 7873);
INSERT INTO `graveyard_zone` (`ID`, `GhostZone`, `Faction`, `Comment`) VALUES
(5135, 7871, 0, 'TombOfThePenitent'),
(5136, 7866, 0, 'TheDemonWard'),
(5137, 7864, 0, 'ChamberOfNight'),
(5344, 7819, 0, 'VaultOfTheBetrayer - Corpse Catcher 1'),
(5345, 7819, 0, 'VaultOfTheBetrayer - Corpse Catcher 2'),
(5346, 7819, 0, 'VaultOfTheBetrayer - Corpse Catcher 3'),
(5347, 7819, 0, 'VaultOfTheBetrayer - Corpse Catcher 4'),
(5348, 7819, 0, 'VaultOfTheBetrayer - Corpse Catcher 5'),
(5349, 7819, 0, 'VaultOfTheBetrayer - Corpse Catcher 6'),
(5350, 7819, 0, 'VaultOfTheBetrayer - Corpse Catcher 7'),
(5356, 7873, 0, 'VaultOfSilence');

SET @CGUID := 280000000;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+250 AND @CGUID+260;
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `VerifiedBuild`) VALUES
(@CGUID+250, 39660, 1468, 7814, 7871, 0, 0, 0, 0, 0, 4330.025, -315.0139, -283.7572, 5.090357, 120, 0, 0, 0, 0, 0, 0, 0, 0, 25549), -- Spirit Healer (Area: VotW: TombOfThePenitent - Difficulty: 0)
(@CGUID+251, 39660, 1468, 7814, 7873, 0, 0, 0, 0, 0, 4326.024, -598.0903, -281.8333, 5.090357, 120, 0, 0, 0, 0, 0, 0, 0, 0, 25549), -- Spirit Healer (Area: VotW: VaultOfSilence - Difficulty: 0)
(@CGUID+252, 39660, 1468, 7814, 7866, 0, 0, 0, 0, 0, 4442.008, -392.8559, 125.8984, 5.090357, 120, 0, 0, 0, 0, 0, 0, 0, 0, 25549), -- Spirit Healer (Area: VotW: TheDemonWard - Difficulty: 0)
(@CGUID+253, 39660, 1468, 7814, 7864, 0, 0, 0, 0, 0, 4184.598, -442.408, 269.8069, 5.090357, 120, 0, 0, 0, 0, 0, 0, 0, 0, 25549), -- Spirit Healer (Area: VotW: ChamberOfNight - Difficulty: 0)
(@CGUID+254, 39660, 1468, 7814, 7819, 0, 0, 0, 0, 0, 4079.568, -326.8594, -281.1126, 5.090357, 120, 0, 0, 0, 0, 0, 0, 0, 0, 25549), -- Spirit Healer (Area: VotW: VaultOfTheBetrayer - Catcher1 - Difficulty: 0)
(@CGUID+255, 39660, 1468, 7814, 7819, 0, 0, 0, 0, 0, 4050.474, -328.2865, -281.46, 5.090357, 120, 0, 0, 0, 0, 0, 0, 0, 0, 25549), -- Spirit Healer (Area: VotW: VaultOfTheBetrayer - Catcher2 - Difficulty: 0)
(@CGUID+256, 39660, 1468, 7814, 7819, 0, 0, 0, 0, 0, 4021.382, -327.4861, -281.1126, 5.090357, 120, 0, 0, 0, 0, 0, 0, 0, 0, 25549), -- Spirit Healer (Area: VotW: VaultOfTheBetrayer - Catcher3 - Difficulty: 0)
(@CGUID+257, 39660, 1468, 7814, 7819, 0, 0, 0, 0, 0, 4020.778, -297.4115, -281.46, 5.090357, 120, 0, 0, 0, 0, 0, 0, 0, 0, 25549), -- Spirit Healer (Area: VotW: VaultOfTheBetrayer - Catcher4 - Difficulty: 0)
(@CGUID+258, 39660, 1468, 7814, 7819, 0, 0, 0, 0, 0, 4023.035, -270.283, -281.1126, 5.090357, 120, 0, 0, 0, 0, 0, 0, 0, 0, 25549), -- Spirit Healer (Area: VotW: VaultOfTheBetrayer - Catcher5 - Difficulty: 0)
(@CGUID+259, 39660, 1468, 7814, 7819, 0, 0, 0, 0, 0, 4050.985, -268.4618, -281.4599, 5.090357, 120, 0, 0, 0, 0, 0, 0, 0, 0, 25549), -- Spirit Healer (Area: VotW: VaultOfTheBetrayer - Catcher6 - Difficulty: 0)
(@CGUID+260, 39660, 1468, 7814, 7819, 0, 0, 0, 0, 0, 4079.085, -269.4063, -281.1126, 5.090357, 120, 0, 0, 0, 0, 0, 0, 0, 0, 25549); -- Spirit Healer (Area: VotW: VaultOfTheBetrayer - Catcher7 - Difficulty: 0)
UPDATE `creature` SET `npcflag`=16384 WHERE `guid` BETWEEN @CGUID+250 AND @CGUID+260;

DELETE FROM `creature_sparring_template` WHERE `AttackerEntry` IN (92984, 92985, 97632, 92990);
INSERT INTO `creature_sparring_template` (`AttackerEntry`, `VictimEntry`, `HealthLimitPct`) VALUES
(92984, 92990, 45),
(92990, 92984, 35),
(92985, 97632, 45),
(97632, 92985, 35);

-- UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` IN (92984, 92985);
UPDATE `creature_template` SET `AIName` = "" WHERE `entry` IN (92984, 92985);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (92984, 92985) AND `source_type` = 0;
-- INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
-- (92984, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 19, 92990, 15, 0, 0, 0, 0, 0, "Kayn Sunfury - On Reset - Start Attack (Creature ID: 92990, 15 Yards)"),
-- (92984, 0, 1, 0, 1, 0, 100, 0, 10000, 10000, 10000, 10000, 49, 0, 0, 0, 0, 0, 0, 19, 92990, 15, 0, 0, 0, 0, 0, "Kayn Sunfury - OOC (10000 - 10000) - Start Attack (Creature ID: 92990, 15 Yards)"),
-- (92985, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 19, 97632, 15, 0, 0, 0, 0, 0, "Altruis the Sufferer - On Reset - Start Attack (Creature ID: 97632, 15 Yards)"),
-- (92985, 0, 1, 0, 1, 0, 100, 0, 10000, 10000, 10000, 10000, 49, 0, 0, 0, 0, 0, 0, 19, 97632, 15, 0, 0, 0, 0, 0, "Altruis the Sufferer - OOC (10000 - 10000) - Start Attack (Creature ID: 97632, 15 Yards)");
UPDATE `creature` SET `npcflag`=0 WHERE `guid`=20542913;

-- Altruis the Sufferer 3 SAI
SET @ALRTUIS_FEL_INFUSION := 92986;
UPDATE `creature` SET `spawntimesecs`=15 WHERE `guid`=20542724 AND `id`=@ALRTUIS_FEL_INFUSION;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ALRTUIS_FEL_INFUSION;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ALRTUIS_FEL_INFUSION AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ALRTUIS_FEL_INFUSION,0,0,0,10,0,100,1,1,15,25000,25000,1,0,10000,0,0,0,0,18,15,0,0,0,0,0,0,"Altruis the Sufferer - Within 1-15 Range Out of Combat LoS - Say Line 1 (No Repeat)"),
(@ALRTUIS_FEL_INFUSION,0,1,0,19,0,100,0,38689,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0,0,0,0,"Altruis the Sufferer - On Quest 'Fel Infusion' Taken - Say Line 0"),
(@ALRTUIS_FEL_INFUSION,0,2,2,52,0,100,0,0,@ALRTUIS_FEL_INFUSION,0,0,12,@ALRTUIS_FEL_INFUSION*100+00,6,0,0,0,0,8,0,0,0,4321.75,-547.861,-281.497,1.68118,"Altruis the Sufferer - On Text 0 Over - Summon Creature 'Altruis the Sufferer'"),
(@ALRTUIS_FEL_INFUSION,0,3,0,61,0,100,0,0,@ALRTUIS_FEL_INFUSION,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Altruis the Sufferer - On Text 0 Over - Despawn Instant");

DELETE FROM `creature_text` WHERE `CreatureID` = 92986;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES 
('92986', '0', '0', 'Time for answers later. There are demons to kill', '12', '0', '100', '0', '0', '57339', '0', '0', 'Altruis the Sufferer to Player'),
('92986', '0', '1', 'The Legion is here.', '12', '0', '100', '0', '0', '57388', '0', '0', 'Altruis the Sufferer to Player');

-- Altruis the Sufferer Summon SAI
SET @ALTRUIS_2_SUMMON := 9298600; -- 909992
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ALTRUIS_2_SUMMON;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ALTRUIS_2_SUMMON AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ALTRUIS_2_SUMMON,0,0,0,61,0,100,0,0,0,0,0,53,1,9298600,0,0,0,0,1,0,0,0,0,0,0,0,'Altruis the Sufferer - On Reset - Start Waypoint'),
(@ALTRUIS_2_SUMMON,0,1,0,54,0,100,0,0,0,0,0,53,1,9298600,0,0,0,0,1,0,0,0,0,0,0,0,'Altruis the Sufferer - Just Spawned - Start WP'),
(@ALTRUIS_2_SUMMON,0,2,0,40,0,100,0,4,9298600,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Altruis the Sufferer - On Waypoint 4 Reached - Despawn Instant');

DELETE FROM `creature_template` WHERE `entry`=@ALTRUIS_2_SUMMON;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `femaleName`, `subname`, `TitleAlt`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `HealthScalingExpansion`, `RequiredExpansion`, `VignetteID`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `unit_flags3`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `HealthModifierExtra`, `ManaModifier`, `ManaModifierExtra`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES 
(@ALTRUIS_2_SUMMON,'0','0','0','0','0','63985','0','0','0','Altruis the Sufferer','','Illidari',NULL,NULL,'0','100','100','5','0','0','2839','2','1','1.14286','1','1','0','1000','2000','1','1','1','33536','2048','0','0','0','0','0','0','7','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','SmartAI','0','3','1','10','1','5','1','1','1','1','0','0','1','0','0','','25549');

DELETE FROM `creature_template_addon` WHERE `entry`=@ALTRUIS_2_SUMMON;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `auras`) VALUES 
(@ALTRUIS_2_SUMMON, '0', '0', '0', '1', '0', '0', '0', '0', NULL);

DELETE FROM `creature_equip_template` WHERE `CreatureID`=@ALTRUIS_2_SUMMON;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES 
(@ALTRUIS_2_SUMMON, '1', '128360', '0', '0', '128370', '0', '0', '0', '0', '0', '0');

DELETE FROM `waypoints` WHERE `entry`=9298600;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(9298600, 1, 4323.121, -541.476, -282.968, 'Altruis move'),
(9298600, 2, 4323.689, -538.507, -283.827, 'Altruis move'),
(9298600, 3, 4323.789, -525.309, -287.583, 'Altruis move'),
(9298600, 4, 4322.914, -516.714, -287.720, 'Altruis Despawn');

-- Kayn Sunfury 3 SAI
SET @KAYN_RISE := 92980;
UPDATE `creature` SET `spawntimesecs`=15 WHERE `guid`=20542693 AND `id`=@KAYN_RISE;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@KAYN_RISE;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@KAYN_RISE AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@KAYN_RISE,0,0,0,19,0,100,0,38690,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0,0,0,0,"Kayn Sunfury - On Quest 'Rise of Illidari' Taken - Say Line 0"),
(@KAYN_RISE,0,1,2,52,0,100,0,0,@KAYN_RISE,0,0,12,@KAYN_RISE*100+00,6,0,0,0,0,8,0,0,0,4330.08,-548.288,-281.751,1.67951,"Kayn Sunfury - On Text 0 Over - Summon Creature 'Kayn Sunfury'"),
(@KAYN_RISE,0,2,0,61,0,100,0,0,@KAYN_RISE,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kayn Sunfury - On Text 0 Over - Despawn Instant");

DELETE FROM `creature_text` WHERE `CreatureID` = 92980;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES 
('92980', '0', '0', 'The demons aim to destroy our world. We need to release our alies.', '12', '0', '100', '0', '0', '55352', '0', '0', 'Kayn Sunfury to Player');

-- Kayn Sunfury Summon SAI
SET @KAYN_2_SUMMON := 9298000;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@KAYN_2_SUMMON;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@KAYN_2_SUMMON AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@KAYN_2_SUMMON,0,0,0,61,0,100,0,0,0,0,0,53,1,9298000,0,0,0,0,1,0,0,0,0,0,0,0,'Kayn Sunfury - On Reset - Start WP'),
(@KAYN_2_SUMMON,0,1,0,54,0,100,0,0,0,0,0,53,1,9298000,0,0,0,0,1,0,0,0,0,0,0,0,'Kayn Sunfury - Just Spawned - Start WP'),
(@KAYN_2_SUMMON,0,2,0,40,0,100,0,4,9298000,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Kayn Sunfury - On Waypoint 4 Reached - Despawn Instant');

DELETE FROM `creature_template` WHERE `entry`=@KAYN_2_SUMMON;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `femaleName`, `subname`, `TitleAlt`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `HealthScalingExpansion`, `RequiredExpansion`, `VignetteID`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `unit_flags3`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `HealthModifierExtra`, `ManaModifier`, `ManaModifierExtra`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES 
(@KAYN_2_SUMMON,'0','0','0','0','0','61698','0','0','0','Kayn Sunfury','','Illidari',NULL,NULL,'0','100','100','5','0','0','2839','3','1','1.14286','1','1','0','1000','2000','1','1','1','32832','2048','0','0','0','0','0','0','7','4096','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','SmartAI','0','3','1','10','1','5','1','1','1','1','0','0','1','0','0','','25549');

DELETE FROM `creature_template_addon` WHERE `entry`=@KAYN_2_SUMMON;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `auras`) VALUES 
(@KAYN_2_SUMMON, '0', '0', '0', '1', '0', '0', '0', '0', NULL);

DELETE FROM `creature_equip_template` WHERE `CreatureID`=@KAYN_2_SUMMON;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES 
(@KAYN_2_SUMMON, '1', '128359', '0', '0', '128371', '0', '0', '0', '0', '0', '0');

DELETE FROM `waypoints` WHERE `entry`=9298000;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(9298000, 1, 4328.037, -540.687, -283.179, 'Kayn move'),
(9298000, 2, 4328.187, -529.856, -286.617, 'Kayn move'),
(9298000, 3, 4328.747, -518.079, -287.721, 'Kayn move'),
(9298000, 4, 4332.642, -506.923, -288.638, 'Kayn Despawn');

UPDATE `creature_template` SET `minlevel`=99, `maxlevel`=99, `faction`=2395, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `unit_flags`=33587720, `unit_flags2`=2048, `VehicleId`=4197, `MovementId` = 150, `AIName`='SmartAI', `InhabitType`=4 WHERE `entry`=99443;
DELETE FROM `smart_scripts` WHERE `entryorguid`=99443 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(99443, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 85, 46598, 2, 0, 0, 0, 0, 1, 0, 0, 0, 4063.51, -296.51, -281.58, 0, 'Vampiric Felbat - Just Spawned - Invoker Cast Ride Vehicle Hardcoded'),
(99443, 0, 1, 0, 27, 0, 100, 0, 0, 0, 0, 0, 53, 1, 99443, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Vampiric Felbat - Passenger Boarded - Start WP'),
(99443, 0, 2, 3, 58, 0, 100, 0, 13, 99443, 0, 0, 11, 68576, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Vampiric Felbat - WP Ended - Cast Eject All Passengers'),
(99443, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Vampiric Felbat - WP Ended - Despawn');

DELETE FROM `waypoints` WHERE `entry`=99443;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(99443, 1, 4435.54, -289.252, -247.127, 'Vampiric Felbat1'),
(99443, 2, 4445.98, -299.189, -234.631, 'Vampiric Felbat2'),
(99443, 3, 4450.8, -320.845, -223.82, 'Vampiric Felbat3'),
(99443, 4, 4450.8, -320.845, -171.81, 'Vampiric Felbat4'),
(99443, 5, 4451.2, -321.103, -101.486, 'Vampiric Felbat5'),
(99443, 6, 4451.2, -321.103, -30.4712, 'Vampiric Felbat6'),
(99443, 7, 4451.2, -321.103, 5.68376, 'Vampiric Felbat7'),
(99443, 8, 4451.2, -321.103, 42.8748, 'Vampiric Felbat8'),
(99443, 9, 4451.2, -321.103, 78.3228, 'Vampiric Felbat9'),
(99443, 10, 4451.2, -321.103, 129.983, 'Vampiric Felbat10'),
(99443, 11, 4447.17, -323.197, 140.234, 'Vampiric Felbat11'),
(99443, 12, 4449.52, -341.185, 129.249, 'Vampiric Felbat12'),
(99443, 13, 4451.74, -359.885, 130.354, 'Vampiric Felbat13 - Despawn');

UPDATE `creature_template` SET `unit_flags`=768, `npcflag`=1 WHERE `entry`=99501;
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=99501;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(99501, 202064, 1, 0);

SET @CGUID := 280000000;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+261 AND @CGUID+268;
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `unit_flags2`, `unit_flags3`, `dynamicflags`, `ScriptName`, `VerifiedBuild`) VALUES
(@CGUID+261,96656,1468,0,0,0,0,0,0,-1,0,1,4392.36,-513.713,-281.484,2.7597,300,0,0,1266732,0,0,0,0,0,0,0,'',25549),
(@CGUID+262,96656,1468,0,0,0,0,0,0,-1,0,1,4361.92,-529.656,-274.719,2.26568,300,0,0,1304724,0,0,0,0,0,0,0,'',25549),
(@CGUID+263,96656,1468,0,0,0,0,0,0,-1,0,1,4305.08,-559.763,-281.487,1.12057,300,0,0,1266732,0,0,0,0,0,0,0,'',25549),
(@CGUID+264,96656,1468,0,0,0,0,0,0,-1,0,1,4346.46,-427.373,-281.485,4.42082,300,0,0,1266732,0,0,0,0,0,0,0,'',25549),
(@CGUID+265,96656,1468,0,0,0,0,0,0,-1,0,1,4280.47,-457.641,-287.566,4.61166,300,0,0,1266732,0,0,0,0,0,0,0,'',25549),
(@CGUID+266,96656,1468,0,0,0,0,0,0,-1,0,1,4280.5,-528.708,-274.754,1.61223,300,0,0,1266732,0,0,0,0,0,0,0,'',25549),
(@CGUID+267,96656,1468,0,0,0,0,0,0,-1,0,1,4289.63,-457.4,-274.719,5.52037,300,0,0,1304724,0,0,0,0,0,0,0,'',25549),
(@CGUID+268,96656,1468,0,0,0,0,0,0,-1,0,1,4362.25,-457.504,-274.719,3.95586,300,0,0,1266732,0,0,0,0,0,0,0,'',25549);

UPDATE `creature` SET `spawntimesecs`=60 WHERE `guid` IN (20542822, 20542748, 20542855, 20542737);
UPDATE `creature` SET `spawntimesecs`=30 WHERE `guid` IN (20542615, 20542616);
UPDATE `creature_template` SET `unit_flags`=384 WHERE (entry = 100717);

UPDATE `creature_template_addon` SET `path_id`=99631 WHERE `entry`=99631;
UPDATE `creature_template` SET `MovementType`=2 WHERE `entry`=99631;
DELETE FROM `waypoints` WHERE `entry`=99631;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(99631,1,4334.12,-590.217,-281.922,''),
(99631,2,4331.97,-589.663,-281.922,''),
(99631,3,4331.98,-589.172,-281.922,''),
(99631,4,4332.24,-588.301,-281.922,''),
(99631,5,4332.14,-587.541,-281.922,''),
(99631,6,4331.09,-584.03,-281.925,''),
(99631,7,4330.39,-583.545,-281.924,''),
(99631,8,4328.46,-583.66,-281.841,'');
DELETE FROM `waypoint_data` WHERE `id`=99631;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES
(99631,1,4334.12,-590.217,-281.922,0,0,0,0,100,0),
(99631,2,4331.97,-589.663,-281.922,0,0,0,0,100,0),
(99631,3,4331.98,-589.172,-281.922,0,0,0,0,100,0),
(99631,4,4332.24,-588.301,-281.922,0,0,0,0,100,0),
(99631,5,4332.14,-587.541,-281.922,0,0,0,0,100,0),
(99631,6,4331.09,-584.03,-281.925,0,0,0,0,100,0),
(99631,7,4330.39,-583.545,-281.924,0,0,0,0,100,0),
(99631,8,4328.46,-583.66,-281.841,0,0,0,0,100,0);

UPDATE `creature` SET `PhaseId` = 993 WHERE `guid` = 20542908;
UPDATE `creature` SET `PhaseId` = 993 WHERE `guid` = 20542909;
UPDATE `creature` SET `PhaseId` = 543 WHERE `guid` = 20542912;
UPDATE `creature` SET `PhaseId` = 543 WHERE `guid` = 20542915;
UPDATE `creature` SET `PhaseId` = 543 WHERE `guid` = 20542913;
UPDATE `creature` SET `PhaseId` = 543 WHERE `guid` = 20542914;

DELETE FROM `creature_text` WHERE `CreatureID` = 92985;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `Comment`) VALUES
(92985,0,0,'Just like old times, eh Kayn?',12,0,100,0,0,57329,0,0,'Altruis the Sufferer to Kayn Sunfury'),
(92985,1,0,'After ten-thousand years of imprisonment, Illidan succumbed to the fel energy within. When he was freed, he was not in his right mind.',12,0,100,0,0,57284,0,0,'Altruis the Sufferer to Kayn Sunfury'),
(92985,2,0,'You followed Illidan blindly, like a dog. Even when he lost his way.',12,0,100,0,0,57326,0,0,'Altruis the Sufferer to Kayn Sunfury'),
(92985,3,0,'I fought as hard as the rest of you! But I did not murder thousands of innocents.',12,0,100,0,0,57386,0,0,'Altruis the Sufferer to Kayn Sunfury'),
(92985,4,0,'Fool! You would trust the warden? She hates us almost as much as the Legion.',12,0,100,0,0,57389,0,0,'Altruis the Sufferer to Kayn Sunfury');

DELETE FROM `creature_text` WHERE `CreatureID` = 92984;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `Comment`) VALUES
(92984,0,0,'Do not speak to me of old times, Altruis. You betrayed Illidan. You betrayed us all!',12,0,100,0,0,57345,0,0,'Kayn Sunfury to Altruis the Sufferer'),
(92984,1,0,'He was fighting it, as we all do. He needed us to have faith in him, Altruis.',12,0,100,0,0,57325,0,0,'Kayn Sunfury to Altruis the Sufferer'),
(92984,2,0,'He made the hard choices. He sacrificed EVERYTHING. What did you give?',12,0,100,0,0,57321,0,0,'Kayn Sunfury to Altruis the Sufferer'),
(92984,3,0,'You heard the Warden. We are the only ones who can defeat the Legion. We MUST survive this place.',12,0,100,0,0,57322,0,0,'Kayn Sunfury to Altruis the Sufferer'),
(92984,4,0,'You trust no one and believe in nothing, Altruis. You are a leader with no followers.',12,0,100,0,0,57390,0,0,'Kayn Sunfury to Altruis the Sufferer');




