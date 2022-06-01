-- "Into the Mists" 26960
UPDATE `creature_template` SET `AIName`= '', `ScriptName`= 'npc_general_nazgrim_55054' WHERE `entry`= 54870;
DELETE FROM `gossip_menu` WHERE `MenuId`= 54870;;
INSERT INTO `gossip_menu` (`MenuId`,`TextId`,`VerifiedBuild`) VALUES
(54870,0,22423);
DELETE FROM `gossip_menu_option` WHERE `MenuId`= 54870;
INSERT INTO `gossip_menu_option` (`MenuId`,`OptionIndex`,`OptionIcon`, `OptionText`, `OptionBroadcastTextId`, `OptionType`, `OptionNpcFlag`, `VerifiedBuild`) VALUES
(54870,0,0,'I\'m ready to go, General.',0,1,1,22423);
DELETE FROM `gossip_menu_option_action` WHERE `MenuId`= 54870;
INSERT INTO `gossip_menu_option_action` (`MenuId`,`OptionIndex`,`ActionMenuId`, `ActionPoiId`) VALUES
(54870,0,0,0);;

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=54870;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(15,54870,0,0,9,29690,0,0,0,'','Show gossip option 0 if player has Quest 29690 "Into the Mists"');

DELETE FROM `creature_addon` WHERE `guid`= 10642734;
INSERT INTO `creature_addon` (`guid`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES
(10642734, 0, 0x0, 0x1, '169384');

-- DB Errors
DELETE FROM `gameobject_addon` WHERE `guid` IN (44064, 44065, 44066, 51014376, 51014375, 167118, 167119, 167120, 167121, 167175, 167176, 167177, 167178, 167179, 167180, 167181, 167182, 167183, 167184, 20373837, 20373116, 20373163);
UPDATE `creature` SET `equipment_id`= 0 WHERE `id`= 17014;
UPDATE `creature` SET `equipment_id`= 0 WHERE `id`= 19527;
UPDATE `creature` SET `equipment_id`= 0 WHERE `id`= 18976;
UPDATE `creature` SET `equipment_id`= 0 WHERE `id`= 23029;
UPDATE `creature` SET `equipment_id`= 0 WHERE `id`= 22323;
UPDATE `creature_equip_template` SET `ItemID1`= 50049 WHERE `CreatureID`= 126062;
DELETE FROM `creature_equip_template` WHERE `CreatureID`= 106652 AND `ID`= 1;
UPDATE `creature` SET `equipment_id`= 0 WHERE `id`= 106652;
-- missing quests
DELETE FROM `quest_details` WHERE `ID` IN (792, 25189);
DELETE FROM `quest_offer_reward` WHERE `ID` IN (792, 25189);
DELETE FROM `quest_request_items` WHERE `ID`= 792;
DELETE FROM `quest_greeting_locale` WHERE `ID` IN (94318, 97480, 91531, 97270, 93446, 91249, 91519, 243836, 90866);
