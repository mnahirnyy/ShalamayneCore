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