-- TrinityCore SAI/DB fixes
-- Eldara Dawnrunner
DELETE FROM `creature_text` WHERE `CreatureID`=25032;
INSERT INTO `creature_text` (`CreatureID`,`GroupID`,`ID`,`Text`,`Type`,`Language`,`Probability`,`Emote`,`Duration`,`Sound`,`BroadcastTextId`,`TextRange`,`comment`) VALUES
(25032,0,0,"$p, it's very good to see you again!",                                                                                             12,0,100,0,0,0,24086,0,'Eldara Dawnrunner'),
(25032,0,1,"Everyone look, it's $p!",                                                                                                          12,0,100,0,0,0,24087,0,'Eldara Dawnrunner'),
(25032,0,2,"Dawnblade, demons and naga beware, $p is back.",                                                                                   12,0,100,0,0,0,24088,0,'Eldara Dawnrunner'),
(25032,0,3,"$G Milord : Milady;, $p, we are fortunate to have you here with us.",                                                              12,0,100,0,0,0,24089,0,'Eldara Dawnrunner'),
(25032,0,4,"The Shattered Sun Offensive is lucky to have $n on our side.",                                                                     12,0,100,0,0,0,24098,0,'Eldara Dawnrunner'),
(25032,0,5,"If it weren't for $p, we'd all be long dead.",                                                                                     12,0,100,0,0,0,24099,0,'Eldara Dawnrunner'),
(25032,0,6,"$p, thank you again for helping us. We couldn't have achieved any of this without you.",                                           12,0,100,0,0,0,24100,0,'Eldara Dawnrunner'),
(25032,0,7,"$Three cheers for $p!",                                                                                                            12,0,100,0,0,0,24102,0,'Eldara Dawnrunner'),
(25032,0,8,"It's an honor to serve with you, $p.",                                                                                             12,0,100,0,0,0,24103,0,'Eldara Dawnrunner'),
(25032,0,9,"If I were one of those Dawnblade blood elves, I'd be swimming away from the island now that $p is here.",                          12,0,100,0,0,0,24106,0,'Eldara Dawnrunner'),
(25032,0,10,"How many wretched do you think $n has put out of their misery?",                                                                  12,0,100,0,0,0,24107,0,'Eldara Dawnrunner'),
(25032,0,11,"Snap to attention, $p, one of our finest, is here!",                                                                              12,0,100,0,0,0,24108,0,'Eldara Dawnrunner'),
(25032,0,12,"Welcome back, $p.",                                                                                                               12,0,100,0,0,0,24110,0,'Eldara Dawnrunner'),
(25032,0,13,"There's our $g hero : heroine; right there! How are you doing, $p?",                                                              12,0,100,0,0,0,24111,0,'Eldara Dawnrunner'),
(25032,0,14,"I guarantee that without $p, this whole offensive would have been a failure.",                                                    12,0,100,0,0,0,24112,0,'Eldara Dawnrunner'),
(25032,0,15,"No matter what, your efforts will always be exalted here, $p!",                                                                   12,0,100,0,0,0,24113,0,'Eldara Dawnrunner'),
(25032,0,16,"Lay waste to the demons on the Dead Scar lately, $p?",                                                                            12,0,100,0,0,0,24115,0,'Eldara Dawnrunner'),
(25032,0,17,"$p, one of these days I want to buy you a drink.",                                                                                12,0,100,0,0,0,24116,0,'Eldara Dawnrunner'),
(25032,0,18,"$p, you have no idea what a relief it is to see you!",                                                                            12,0,100,0,0,0,24119,0,'Eldara Dawnrunner'),
(25032,0,19,"What a coincidence... we were just talking about you, $p!",                                                                       12,0,100,0,0,0,24120,0,'Eldara Dawnrunner'),
(25032,0,20,"Who needs sentries? $p is here!",                                                                                                 12,0,100,0,0,0,24121,0,'Eldara Dawnrunner'),
(25032,0,21,"Hey, $p, try to leave some of the glory for us, would ya?",                                                                       12,0,100,0,0,0,24122,0,'Eldara Dawnrunner'),
(25032,0,22,"Do not fight the enemy unprepared, $n.  I can provide you with very powerful items... provided you have proven yourself to us.",  12,0,100,0,0,0,24302,0,'Eldara Dawnrunner'),
(25032,0,23,"I don't even want to think about what'll happen here if $p ever decides not to come back.",                                       12,0,100,0,0,0,24117,0,'Eldara Dawnrunner');

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry`=25032;
DELETE FROM `smart_scripts` WHERE (`source_type`=0 AND `entryorguid`=25032);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(25032,0,0,0,10,0,100,0,1,20,120000,120000,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Eldara Dawnrunner - OOC LOS - Say Line');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND `SourceEntry`=25032;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(22, 1, 25032, 0, 0, 5, 0, 1077, 128, 0, 0, 0, 0, '', 'Smart event 0 for Eldara Dawnrunner will execute if the payer is exalted with Shattered Sun');

-- Crimson Crysal Shard is a guaranteed drop
UPDATE `creature_loot_template` SET `Chance` = 100 WHERE `Entry` = 19188 AND `Item` = 29476;

-- Diaphanous wing droprate
UPDATE `creature_loot_template` SET `Chance` = 40 WHERE `Item` = 24372 AND `Entry` IN (18132, 18133, 20197, 20198, 18283);

-- Greater and Young Sporebat also drop eyes.
DELETE FROM `creature_loot_template` WHERE `Entry` IN (20387, 18129) AND `Item` = 24426;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`) VALUES
(18129,24426,20),
(20387,24426,20);

-- Drop chance howling wind
UPDATE `creature_loot_template` SET `Chance` = 20 WHERE `Item` = 24504 AND `Entry` IN (17158,17159,17160);

-- Scripts/Northrend: talk event for quest A Suitable Test Subject (#20462)
-- When using the quest item for A Suitable Test Subject and the spell aura vanishes,
-- Bloodmage Laurith should turn toward the player and whisper a line.
-- This is handled via spell event for Bloodspore Ruination (45997)
DELETE FROM `spell_script_names` WHERE `ScriptName`="spell_q11719_bloodspore_ruination_45997";
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(45997, "spell_q11719_bloodspore_ruination_45997");

UPDATE `creature_template` SET `ScriptName`="npc_bloodmage_laurith" WHERE `entry`=25381;

DELETE FROM `creature_text` WHERE `CreatureID`=25381;
INSERT INTO `creature_text` (`CreatureID`,`GroupID`,`ID`,`Text`,`Type`,`Language`,`Probability`,`Emote`,`Duration`,`Sound`,`BroadcastTextId`,`TextRange`,`comment`) VALUES
(25381, 0, 0, "How positively awful! You were totally incapacitated? Weak? Hot flashes?", 15, 0, 100, 21, 0, 0, 24992, 0, "Bloodmage Laurith");

-- DB/Creature: Set correct unit flag to Rin'ji
UPDATE `creature_template` SET `unit_flags`=`unit_flags`|768 WHERE `entry`=7780;

-- Underlight Mines
SET @PATHID_1 := 826050;
SET @PATHID_2 := 825820;

UPDATE `creature` SET `MovementType`=2 WHERE `guid` IN (82605, 82582);
DELETE FROM `creature_addon` WHERE `guid` IN (82605, 82582);
INSERT INTO `creature_addon` (`guid`, `path_id`, `bytes2`) VALUES 
(82605, @PATHID_1, 4097),
(82582, @PATHID_2, 4097);

-- Add waypoints
DELETE FROM `waypoint_data` WHERE `id` IN (@PATHID_1, @PATHID_2);
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
-- Blackpaw Shaman #1
(@PATHID_1,  1, 7126.29, -6221.997, 21.801),
(@PATHID_1,  2, 7110.97, -6227.314, 21.194),
(@PATHID_1,  3, 7105.31, -6209.855, 21.509),
(@PATHID_1,  4, 7081.72, -6205.795, 21.952),
(@PATHID_1,  5, 7071.54, -6199.641, 22.810),
(@PATHID_1,  6, 7071.65, -6189.511, 21.062),
(@PATHID_1,  7, 7071.54, -6199.641, 22.810),
(@PATHID_1,  8, 7077.39, -6207.805, 22.138),
(@PATHID_1,  9, 7076.12, -6218.441, 23.908),
(@PATHID_1, 10, 7068.51, -6227.06,  23.479),
(@PATHID_1, 11, 7061.94, -6227.88,  22.943),
(@PATHID_1, 12, 7068.51, -6227.06,  23.479),
(@PATHID_1, 13, 7076.12, -6218.44,  23.908),
(@PATHID_1, 14, 7077.39, -6207.80,  22.138),
(@PATHID_1, 15, 7071.54, -6199.64,  22.810),
(@PATHID_1, 16, 7071.65, -6189.51,  21.062),
(@PATHID_1, 17, 7071.54, -6199.64,  22.810),
(@PATHID_1, 18, 7081.72, -6205.79,  21.952),
(@PATHID_1, 19, 7105.31, -6209.85,  21.509),
(@PATHID_1, 20, 7110.97, -6227.31,  21.194),
(@PATHID_1, 21, 7126.29, -6221.99,  21.801),
-- Blackpaw Shaman #2
(@PATHID_2,  1, 7001.19, -6262.55,  6.511),
(@PATHID_2,  2, 7009.89, -6270.94,  5.008),
(@PATHID_2,  3, 7022.81, -6275.65,  7.483),
(@PATHID_2,  4, 7039.36, -6277.72,  8.733),
(@PATHID_2,  5, 7054.01, -6276.99, 12.318),
(@PATHID_2,  6, 7069.66, -6269.71, 15.899),
(@PATHID_2,  7, 7076.94, -6260.30, 17.073),
(@PATHID_2,  8, 7072.61, -6244.68, 19.408),
(@PATHID_2,  9, 7068.06, -6234.58, 22.018),
(@PATHID_2, 10, 7072.61, -6244.68, 19.408),
(@PATHID_2, 11, 7076.94, -6260.30, 17.073),
(@PATHID_2, 12, 7069.66, -6269.71, 15.899),
(@PATHID_2, 13, 7054.01, -6276.99, 12.318),
(@PATHID_2, 14, 7039.36, -6277.72,  8.733),
(@PATHID_2, 15, 7022.81, -6275.65,  7.483),
(@PATHID_2, 16, 7009.89, -6270.94,  5.008),
(@PATHID_2, 17, 7001.19, -6262.55,  6.511),
(@PATHID_2, 18, 7006.29, -6247.67,  6.112);

-- Add correct weapons to specific Blackpaw Gnolls and Blackpaw Scavengers
DELETE FROM `creature_equip_template` WHERE `CreatureID` IN (16334, 16335) AND `id`=2;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`) VALUES
(16334, 2, 2901), -- This weapon isn't sniffed, but looks exactly like the one used in retail. If someone has the sniffed weapon I can update the SQL
(16335, 2, 2901);

UPDATE `creature` SET `equipment_id`=2 WHERE `guid` IN (82576, 82580, 82583, 82584, 82586, 82587, 82591, 82593, 82594, 82595, 82596, 82598, 82601, 82644);

-- Blackpaw Shaman SAI
SET @ENTRY := 16337;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3000,4500,11,20802,64,0,0,0,0,2,0,0,0,0,0,0,0,"Blackpaw Shaman - In Combat CMC - Cast 'Lightning Bolt'"),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,28902,1,0,0,0,0,1,0,0,0,0,0,0,0,"Blackpaw Shaman - Between 0-30% Health - Cast 'Bloodlust' (No Repeat)"),
(@ENTRY,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,0,0,0,0,0,0,0,0,"Blackpaw Shaman - Between 0-15% Health - Flee For Assist (No Repeat)");

-- DB/Creature: Commander Hobb model fix
UPDATE `creature_model_info` SET `DisplayID_Other_Gender`=0 WHERE `DisplayID` IN (21505);

-- DB/SAI: Miles Sidney trigger los event only for players
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND `SourceEntry`=28347;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(22, 2, 28347, 0, 0, 31, 0, 4, 0, 0, 0, 0, 0, "", "Execute SAI only if invoker is a player");

-- Attach touch of the magi aura script
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_mage_touch_of_the_magi_aura';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(210824,'spell_mage_touch_of_the_magi_aura');

-- Core/Scripts Fix issues with Midsummer's Ribbon Pole
DELETE FROM `spell_script_names` WhERE `ScriptName` IN
('spell_midsummer_torch_target_picker',
'spell_midsummer_torch_toss_land',
'spell_midsummer_test_ribbon_pole_channel',
'spell_gen_ribbon_pole_dancer_check',
'spell_midsummer_ribbon_pole_periodic_visual');
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(45907,'spell_midsummer_torch_target_picker'),
(46054,'spell_midsummer_torch_toss_land'),
(29705,'spell_midsummer_test_ribbon_pole_channel'),
(29726,'spell_midsummer_test_ribbon_pole_channel'),
(29727,'spell_midsummer_test_ribbon_pole_channel'),
(45406,'spell_midsummer_ribbon_pole_periodic_visual');

-- UPDATE `spell_dbc` SET `Effect1`=3, `EffectImplicitTargetA1`=1 WHERE `Id`=58934;
DELETE FROM `spelleffect_dbc` WHERE `Id`=155919;
INSERT INTO `spelleffect_dbc` (`Id`, `Effect`, `EffectValueMultiplier`, `EffectApplyAuraName`, `EffectAmplitude`, `EffectBasePoints`, `EffectBonusMultiplier`, `EffectDamageMultiplier`, `EffectChainTarget`, `EffectDieSides`, `EffectItemType`, `EffectMechanic`, `EffectMiscValue`, `EffectMiscValueB`, `EffectRadiusIndex`, `EffectRadiusIndexMax`, `EffectRealPointsPerLevel`, `EffectSpellClassMaskA`, `EffectSpellClassMaskB`, `EffectSpellClassMaskC`, `EffectTriggerSpell`, `EffectImplicitTargetA`, `EffectImplicitTargetB`, `EffectSpellId`, `EffectIndex`) VALUES
(155919, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 58934, 0);

UPDATE `creature_template` SET `AIName`='' WHERE `entry`=25535;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=25535;

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=29726;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=45723 AND `spell_effect`=43313;
DELETE FROM `disables` WHERE `sourceType`=0 AND `entry` IN(45724);
INSERT INTO `disables` (`sourceType`, `entry`, `flags`, `params_0`, `params_1`, `comment`) VALUES
(0,45724,64,0,0,'Disable LoS for spell Braziers Hit');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry` IN (45907,46054,45732,29705,29727);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition` ,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(13,1,45907,0,0,31,0,3,25535,0,0,0,'','Spell \'Torch Target Picker\' targets [DNT] Torch Tossing Target Bunny'),
(13,1,45907,0,0,1,0,45723,0,0,1,0,'','Spell \'Torch Target Picker\' can not hit targets with Aura \'Target Indicator (Rank 1)\''),
(13,1,45732,0,0,1,0,45723,0,0,0,0,'','Spell \'Torch Toss\' can only hit targets with Aura \'Target Indicator\''),
(13,1,46054,0,0,1,0,45723,0,0,0,0,'','Spell \'Torch Toss\' can only hit targets with Aura \'Target Indicator\''),
(13,1,46054,0,0,31,0,3,25535,0,0,0,'','Spell \'Torch Target Picker\' targets [DNT] Torch Tossing Target Bunny'),
(13,1,45732,0,0,31,0,3,25535,0,0,0,'','Spell \'Torch Target Picker\' targets [DNT] Torch Tossing Target Bunny'),
(13,1,29705,0,0,31,0,3,17066,0,0,0,'','Spell \'Test Ribbon Pole Channel\' targets Ribbon Pole Debug Target'),
(13,1,29727,0,0,31,0,3,17066,0,0,0,'','Spell \'Test Ribbon Pole Channel\' targets Ribbon Pole Debug Target');

-- Delete the following spells from the trainer: Artisan Riding, Cold Weather Flying, Flight Masters License
DELETE FROM `trainer_spell` WHERE `SpellId` IN (34093, 54198, 90269);

-- Apprentice riding skill
UPDATE `trainer_spell` SET `MoneyCost` = 10000, `ReqLevel` = 10 WHERE `SpellId` = 33389;

-- Journeyman riding skill
UPDATE `trainer_spell` SET `MoneyCost` = 500000, `ReqLevel` = 20 WHERE `SpellId` = 33392;

-- Expert riding skill
UPDATE `trainer_spell` SET `MoneyCost` = 2500000, `ReqLevel` = 30 WHERE `SpellId` = 34092;

-- Master riding skill
UPDATE `trainer_spell` SET `MoneyCost` = 50000000, `ReqLevel` = 40, `ReqAbility1` = 34090 WHERE `SpellId` = 90266;


-- Formula: Enchant Weapon - Superior Striking
DELETE FROM `creature_loot_template` WHERE `item` = 16250;
INSERT INTO `creature_loot_template` (`Entry`,`Item`,`Chance`,`GroupId`,`MinCount`,`MaxCount`,`Reference`) VALUES 
-- Bosses
(10363, 16250, 2, 0, 1, 1, 0),
(10220, 16250, 2, 0, 1, 1, 0),
(9816, 16250, 2, 0, 1, 1, 0),
(10899, 16250, 2, 0, 1, 1, 0),
(10430, 16250, 2, 0, 1, 1, 0),
(9196, 16250, 2, 0, 1, 1, 0),
(9236, 16250, 2, 0, 1, 1, 0),
(9219, 16250, 2, 0, 1, 1, 0),
(10376, 16250, 2, 0, 1, 1, 0),
(9736, 16250, 2, 0, 1, 1, 0),
(9568, 16250, 2, 0, 1, 1, 0),
(9237, 16250, 2, 0, 1, 1, 0),
(9596, 16250, 2, 0, 1, 1, 0),
(10509, 16250, 2, 0, 1, 1, 0),
(9718, 16250, 2, 0, 1, 1, 0),
(10596, 16250, 2, 0, 1, 1, 0),
-- Trash
(10371, 16250, 1, 0, 1, 1, 0),
(10318, 16250, 1, 0, 1, 1, 0),
(10317, 16250, 1, 0, 1, 1, 0),
(10083, 16250, 1, 0, 1, 1, 0),
(9817, 16250, 1, 0, 1, 1, 0),
(9692, 16250, 1, 0, 1, 1, 0),
(9717, 16250, 1, 0, 1, 1, 0),
(9693, 16250, 1, 0, 1, 1, 0),
(9716, 16250, 7, 0, 1, 1, 0),
(9583, 16250, 1, 0, 1, 1, 0),
(10374, 16250, 1, 0, 1, 1, 0),
(9263, 16250, 1, 0, 1, 1, 0),
(9264, 16250, 1, 0, 1, 1, 0),
(9260, 16250, 1, 0, 1, 1, 0),
(9262, 16250, 1, 0, 1, 1, 0),
(9261, 16250, 1, 0, 1, 1, 0),
(9266, 16250, 1, 0, 1, 1, 0),
(9268, 16250, 1, 0, 1, 1, 0),
(9241, 16250, 1, 0, 1, 1, 0),
(9265, 16250, 1, 0, 1, 1, 0),
(9269, 16250, 1, 0, 1, 1, 0),
(9239, 16250, 1, 0, 1, 1, 0),
(9267, 16250, 1, 0, 1, 1, 0),
(9217, 16250, 1, 0, 1, 1, 0),
(9197, 16250, 1, 0, 1, 1, 0),
(9216, 16250, 1, 0, 1, 1, 0),
(9198, 16250, 1, 0, 1, 1, 0),
(9200, 16250, 1, 0, 1, 1, 0),
(9199, 16250, 1, 0, 1, 1, 0),
(9258, 16250, 1, 0, 1, 1, 0),
(9045, 16250, 1, 0, 1, 1, 0),
(9098, 16250, 1, 0, 1, 1, 0),
(9257, 16250, 1, 0, 1, 1, 0),
(9097, 16250, 1, 0, 1, 1, 0),
(10319, 16250, 1, 0, 1, 1, 0),
(10366, 16250, 1, 0, 1, 1, 0),
(10762, 16250, 1, 0, 1, 1, 0),
(10372, 16250, 1, 0, 1, 1, 0),
(9096, 16250, 1, 0, 1, 1, 0),
(9819, 16250, 1, 0, 1, 1, 0),
(9818, 16250, 1, 0, 1, 1, 0),
(9240, 16250, 1, 0, 1, 1, 0);

-- DB: Change of the "Silithus" map to "Silithus: The Wound" upon reaching level 110
DELETE FROM `terrain_swap_defaults` WHERE `TerrainSwapMap` = 1817;
INSERT INTO `terrain_swap_defaults` (`MapId`, `TerrainSwapMap`, `Comment`) VALUES 
(1, 1817, 'Silithus: The Wound');

DELETE FROM `terrain_worldmap` WHERE `TerrainSwapMap` = 1817;
INSERT INTO `terrain_worldmap` (`TerrainSwapMap`, `WorldMapArea`, `Comment`) VALUES 
(1817, 9491, 'Silithus: The Wound');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceEntry` = 1817;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 0, 1817, 0, 0, 27, 0, 110, 3, 0, 0, 0, 0, '', 'TerrainSwap 1817 only when player has level 110');