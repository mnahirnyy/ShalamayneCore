DELETE FROM `gameobject` WHERE `guid` BETWEEN 51014366 AND 51014370;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `isActive`, `ScriptName`, `VerifiedBuild`) VALUES
(51014366,246994,1494,0,0,12,0,0,0,-1,4698.6,3996.12,96.72,4.37254,0,0,-0.8165,0.577346,7200,255,1,0,'',22423),
(51014367,246993,1494,0,0,12,0,0,0,-1,4701.84,4014.68,96.72,4.67504,0,0,-0.720187,0.69378,7200,255,1,0,'',22423),
(51014368,246992,1494,0,0,12,0,0,0,-1,4699.06,4033.99,96.72,5.01651,0,0,-0.591837,0.806058,7200,255,1,0,'',22423),
(51014369,247544,1494,0,0,12,0,0,0,-1,4646.22,4038.95,77.6499,3.14159,0,0,-1,0,7200,255,1,0,'',22423),
(51014370,247385,1494,0,0,12,0,0,0,-1,4681.17,3967.49,76.2686,3.97984,0,0,-0.913445,0.406961,7200,255,1,0,'',22423);

-- availbale ones
DELETE FROM `gameobject` WHERE `guid` in (51014371, 51014372, 51014373, 51014374);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `isActive`, `ScriptName`, `VerifiedBuild`) VALUES
(51014371,193019,1220,7502,7592,0,0,171,0,-1,-960.317,4325.154,740.212,0.890117,0,0,0.430511,0.902586,300,100,1,0,'',22423),
(51014372,193609,1220,7502,7592,0,0,171,0,-1,-969.812,4314.12,742.18,0.908608,0,0,0.438837,0.898567,180,0,1,0,'go_violethold_entrance_portal',22423),
(51014373,193020,1220,7502,7592,0,0,171,0,-1,-970.863,4317.45,739.721,0.890117,0,0,0.430511,0.902586,180,0,1,0,'',22423),
(51014374,193609,1494,0,0,12,0,0,0,-1,1245.352,-262.682,44.363,3.16211,0,0,0.430511,0.902586,180,0,1,0,'go_violethold_exit_portal',22423);

-- creatures for special violet hold
DELETE FROM `creature` WHERE `guid` in (280000402, 280000403);
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `unit_flags2`, `unit_flags3`, `dynamicflags`, `ScriptName`, `VerifiedBuild`) VALUES
(280000402,99473,1494,0,0,12,0,0,0,-1,0,0,1290.730,-264.305,44.364,0.06528,120,0,0,0,0,0,0,0,0,0,0,'npc_warden_alturas_vh',25549), -- Alturas
(280000403,103156,1494,0,0,12,0,0,0,-1,0,0,1300.655,-259.887,44.272,0.05115,120,0,0,800,0,0,2,0,0,0,0,'',25549); -- Altruis
