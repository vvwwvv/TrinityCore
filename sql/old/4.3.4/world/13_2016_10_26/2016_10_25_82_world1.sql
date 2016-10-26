DELETE FROM `areatrigger_scripts` WHERE `entry`=6845;
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES (6845, 'at_sulfuron_keep');

-- Remove Lava Scion, Son of Flame, Splitting Blow, Engulfing Flames, Magma, Cenarius, Malfurion Stormrage and Arch Druid Hamuul Runetotem sniff spawns
DELETE FROM creature WHERE id IN (53231,53140,53393,53485,53729,53872,53875,53876);

-- Fix Lava Wielder sniff spawn position
UPDATE `creature` SET `position_x`=765.467, `position_y`=-59.48264, `position_z`=86.39432, `orientation`=3.193953 WHERE `guid`=338816;

-- Heroic Ragnaros last phase weapon swap
DELETE FROM `creature_equip_template` WHERE `CreatureID`=52409 AND `ID`=2;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`, `VerifiedBuild`) VALUES (52409, 2, 71036, 0, 0, 0);

-- Heroic Ragnaros model fix
UPDATE `creature_model_info` SET `BoundingRadius`=0.75, `CombatReach`=21 WHERE  `DisplayID`=38570;

-- Magma, west, middle and east splitting bow, near, middle and far Engulfing Flames, Lava Scions, heroic difficulty player helpers, 
DELETE FROM `creature_summon_groups` WHERE `summonerId`=52409;
INSERT INTO `creature_summon_groups` (`summonerId`, `summonerType`, `groupId`, `entry`, `position_x`, `position_y`, `position_z`, `orientation`, `summonType`, `summonTime`) VALUES
(52409, 0, 0, 53729, 1078.43, -57.5295, 52.8818, 0, 8, 0),
(52409, 0, 0, 53729, 1088.52, -57.2986, 52.8818, 0, 8, 0),
(52409, 0, 1, 53393, 1035.45, -25.3646, 55.4924, 2.49582, 8, 0),
(52409, 0, 2, 53393, 1023.55, -57.158, 55.4215, 3.12414, 8, 0),
(52409, 0, 3, 53393, 1036.27, -89.2396, 55.5098, 3.83972, 8, 0),
(52409, 0, 4, 53485, 1033.93, -57.092, 55.4225, 6.26573, 8, 0),
(52409, 0, 4, 53485, 1034.76, -63.9583, 55.4397, 6.26573, 8, 0),
(52409, 0, 4, 53485, 1036.34, -69.8281, 55.4425, 0.314159, 8, 0),
(52409, 0, 4, 53485, 1036.82, -44.3385, 55.4425, 6.02139, 8, 0),
(52409, 0, 4, 53485, 1041.26, -81.434, 55.424, 0.575959, 8, 0),
(52409, 0, 4, 53485, 1042.34, -32.1059, 55.4254, 5.68977, 8, 0),
(52409, 0, 4, 53485, 1049.27, -90.6892, 55.4259, 0.890118, 8, 0),
(52409, 0, 4, 53485, 1051.8, -24.0903, 55.4258, 5.41052, 8, 0),
(52409, 0, 4, 53485, 1063.59, -97.0573, 55.4934, 1.23918, 8, 0),
(52409, 0, 4, 53485, 1065.44, -17.7049, 55.425, 5.0091, 8, 0),
(52409, 0, 4, 53485, 1078.01, -97.776, 55.4227, 1.5708, 8, 0),
(52409, 0, 4, 53485, 1079.15, -15.5312, 55.423, 4.71239, 8, 0),
(52409, 0, 4, 53485, 1086.23, -96.1927, 55.4226, 4.71239, 8, 0),
(52409, 0, 4, 53485, 1086.42, -96.7812, 55.4226, 1.5708, 8, 0),
(52409, 0, 4, 53485, 1086.55, -18.0885, 55.4228, 1.5708, 8, 0),
(52409, 0, 4, 53485, 1087.91, -18.6493, 55.4237, 4.71239, 8, 0),
(52409, 0, 4, 53485, 1091.83, -21.9254, 55.4241, 4.71239, 8, 0),
(52409, 0, 4, 53485, 1092.52, -92.3924, 55.4241, 4.71239, 8, 0),
(52409, 0, 5, 53485, 1016.99, -57.5642, 55.4133, 0, 8, 0),
(52409, 0, 5, 53485, 1018.29, -70.1875, 55.4231, 0, 8, 0),
(52409, 0, 5, 53485, 1018.47, -43.7674, 55.4218, 0, 8, 0),
(52409, 0, 5, 53485, 1021.49, -79.6076, 55.4261, 0, 8, 0),
(52409, 0, 5, 53485, 1021.84, -33.7483, 55.4239, 0, 8, 0),
(52409, 0, 5, 53485, 1025.29, -86.2326, 55.4071, 0, 8, 0),
(52409, 0, 5, 53485, 1025.34, -25.8472, 55.4069, 0, 8, 0),
(52409, 0, 5, 53485, 1030.22, -92.8403, 55.4344, 0, 8, 0),
(52409, 0, 5, 53485, 1036.9, -14.6181, 55.5715, 0, 8, 0),
(52409, 0, 5, 53485, 1038.53, -100.254, 55.6012, 0, 8, 0),
(52409, 0, 5, 53485, 1049.66, -104.906, 55.4556, 0, 8, 0),
(52409, 0, 5, 53485, 1049.98, -7.22396, 55.4537, 0, 8, 0),
(52409, 0, 5, 53485, 1057.03, -4.10417, 55.4258, 0, 8, 0),
(52409, 0, 5, 53485, 1062.13, -109.005, 55.4259, 0, 8, 0),
(52409, 0, 5, 53485, 1062.94, -4.34201, 55.5682, 0, 8, 0),
(52409, 0, 5, 53485, 1069.91, -109.651, 55.4277, 0, 8, 0),
(52409, 0, 5, 53485, 1069.66, -4.53993, 55.4308, 0, 8, 0),
(52409, 0, 5, 53485, 1075.01, -111.233, 55.8345, 0, 8, 0),
(52409, 0, 6, 53485, 989.866, -66.0868, 55.4331, 0, 8, 0),
(52409, 0, 6, 53485, 988.208, -50.3646, 55.4291, 0, 8, 0),
(52409, 0, 6, 53485, 985.18, -77.3785, 55.4409, 0, 8, 0),
(52409, 0, 6, 53485, 986.608, -37.7656, 55.4411, 0, 8, 0),
(52409, 0, 6, 53485, 991.738, -87.1632, 55.4445, 0, 8, 0),
(52409, 0, 6, 53485, 991.799, -25.0955, 55.4441, 0, 8, 0),
(52409, 0, 6, 53485, 980.927, -58.2656, 55.4542, 0, 8, 0),
(52409, 0, 6, 53485, 1002, -58.2396, 55.4331, 0, 8, 0),
(52409, 0, 6, 53485, 1002.21, -49.7049, 55.4075, 0, 8, 0),
(52409, 0, 6, 53485, 1003.07, -66.4913, 55.4067, 0, 8, 0),
(52409, 0, 6, 53485, 1002.72, -40.7431, 55.4063, 0, 8, 0),
(52409, 0, 6, 53485, 1003.44, -74.0243, 55.4063, 0, 8, 0),
(52409, 0, 6, 53485, 999.755, -98.4792, 55.4426, 0, 8, 0),
(52409, 0, 6, 53485, 1000.81, -14.5069, 55.4566, 0, 8, 0),
(52409, 0, 6, 53485, 1005.49, -86.4566, 55.4275, 0, 8, 0),
(52409, 0, 6, 53485, 1006.1, -27.3681, 55.4277, 0, 8, 0),
(52409, 0, 6, 53485, 1005.8, -8.81771, 55.4672, 0, 8, 0),
(52409, 0, 6, 53485, 1012.09, -97.5122, 55.457, 0, 8, 0),
(52409, 0, 6, 53485, 1009.56, -108.161, 55.4697, 0, 8, 0),
(52409, 0, 6, 53485, 1014.15, -17.3281, 55.4629, 0, 8, 0),
(52409, 0, 6, 53485, 1012.7, -4.83333, 55.605, 0, 8, 0),
(52409, 0, 6, 53485, 1018.29, -117.833, 55.4471, 0, 8, 0),
(52409, 0, 6, 53485, 1019.6, 7.7691, 55.447, 0, 8, 0),
(52409, 0, 6, 53485, 1024.45, -8.13889, 55.447, 0, 8, 0),
(52409, 0, 6, 53485, 1024.91, -106.852, 55.4471, 0, 8, 0),
(52409, 0, 6, 53485, 1023.05, -128.257, 55.4471, 0, 8, 0),
(52409, 0, 6, 53485, 1023.83, 12.9774, 55.447, 0, 8, 0),
(52409, 0, 6, 53485, 1035.56, -114.156, 55.4471, 0, 8, 0),
(52409, 0, 6, 53485, 1035.91, 0.909722, 55.447, 0, 8, 0),
(52409, 0, 6, 53485, 1032.48, 13.2708, 55.4469, 0, 8, 0),
(52409, 0, 6, 53485, 1035.17, -125.646, 55.4471, 0, 8, 0),
(52409, 0, 6, 53485, 1049.74, -118.396, 55.5661, 0, 8, 0),
(52409, 0, 6, 53485, 1049.33, 5.0434, 55.4633, 0, 8, 0),
(52409, 0, 6, 53485, 1052.59, -120.562, 55.4563, 0, 8, 0),
(52409, 0, 6, 53485, 1055.34, 5.06771, 55.4471, 0, 8, 0),
(52409, 0, 7, 53231, 1026.86, 5.89583, 55.357, 4.90448, 8, 0),
(52409, 0, 7, 53231, 1027.31, -121.746, 55.3708, 1.36127, 8, 0),
(52409, 0, 8, 53872, 787.639, -59.9396, 86.2755, 6.20131, 8, 0),
(52409, 0, 8, 53875, 787.285, -68.8034, 94.0955, 3.33302, 8, 0),
(52409, 0, 8, 53876, 788.131, -50.6921, 94.0005, 2.96047, 8, 0);

-- creature_template updates, VerifiedBuild set to 0 due to possible human errors
-- Ragnaros
UPDATE `creature_template` SET `difficulty_entry_1`=53797, `difficulty_entry_2`=53798, `difficulty_entry_3`=53799, `speed_walk`=0.357143, `InhabitType`=4, `ScriptName`='boss_ragnaros_firelands', `VerifiedBuild`=0 WHERE `entry`=52409;
-- Magma Trap
UPDATE `creature_template` SET `speed_walk`=0.428571, `speed_run`=0.428571, `unit_flags`=33554432, `unit_flags2`=2099200, `ScriptName`='npc_ragnaros_magma_trap', `VerifiedBuild`=0 WHERE `entry`=53086;
-- Son of Flame
UPDATE `creature_template` SET `difficulty_entry_1`=53800, `difficulty_entry_2`=53801, `difficulty_entry_3`=53802, `speed_walk`=0.357143, `unit_flags2`=2097152, `ScriptName`='npc_ragnaros_son_of_flame', `VerifiedBuild`=0 WHERE `entry`=53140;
-- Lava Scion
UPDATE `creature_template` SET `difficulty_entry_1`=53816, `difficulty_entry_2`=53817, `difficulty_entry_3`=53818, `speed_walk`=1.42857, `unit_flags2`=2099200, `ScriptName`='npc_ragnaros_lava_scion', `VerifiedBuild`=0 WHERE `entry`=53231;
-- Sulfuras Smash
UPDATE `creature_template` SET `speed_walk`=0.428571, `speed_run`=0.428571, `unit_flags`=33554432, `unit_flags2`=2099200, `InhabitType`=4, `flags_extra`=128, `ScriptName`='npc_sulfuras_smash_trigger', `VerifiedBuild`=0 WHERE `entry`=53266;
-- Sulfuras Smash
UPDATE `creature_template` SET `speed_walk`=0.428571, `speed_run`=0.428571, `unit_flags`=33554432, `unit_flags2`=2099200, `InhabitType`=4, `flags_extra`=128, `ScriptName`='npc_ragnaros_sulfuras_smash', `VerifiedBuild`=0 WHERE `entry`=53268;
-- Lava Wave
UPDATE `creature_template` SET `speed_walk`=2.14286, `speed_run`=2.14286,  `unit_flags`=33554432, `unit_flags2`=2099200, `InhabitType`=4, `flags_extra`=128, `ScriptName`='npc_ragnaros_lava_wave', `VerifiedBuild`=0 WHERE `entry`=53363;
-- Sulfuras, Hand of Ragnaros
UPDATE `creature_template` SET `speed_walk`=0.428571, `speed_run`=0.428571, `unit_flags`=33554432, `unit_flags2`=2129920, `InhabitType`=4, `flags_extra`=128, `ScriptName`='npc_ragnaros_sulfuras', `VerifiedBuild`=0 WHERE `entry`=53420;
-- Blazing Heat
UPDATE `creature_template` SET `speed_walk`=0.428571, `speed_run`=0.428571, `unit_flags`=33554432, `unit_flags2`=2099200, `AIName`='NullCreatureAI', `InhabitType`=4, `flags_extra`=128, `VerifiedBuild`=0 WHERE `entry`=53473;
-- Engulfing Flames
UPDATE `creature_template` SET `speed_walk`=0.428571, `unit_flags2`=2099200, `InhabitType`=4, `ScriptName`='npc_ragnaros_engulfing_flames', `VerifiedBuild`=0 WHERE `entry`=53485;
-- Magma
UPDATE `creature_template` SET `speed_walk`=0.428571, `unit_flags2`=2099200, `AIName`='NullCreatureAI', `InhabitType`=4, `VerifiedBuild`=0 WHERE `entry`=53729;
-- Cenarius
UPDATE `creature_template` SET `speed_walk`=0.428571, `unit_flags2`=4194304, `ScriptName`='npc_ragnaros_cenarius', `VerifiedBuild`=0 WHERE `entry`=53872;
-- Malfurion Stormrage
UPDATE `creature_template` SET `speed_walk`=0.357143, `unit_flags2`=4196352, `ScriptName`='npc_ragnaros_malfurion_stormrage', `VerifiedBuild`=0 WHERE `entry`=53875;
-- Arch Druid Hamuul Runetotem
UPDATE `creature_template` SET `speed_walk`=0.357143, `unit_flags2`=4196352, `ScriptName`='npc_ragnaros_hamuul_runetotem', `VerifiedBuild`=0 WHERE `entry`=53876;
-- Platform Stalker
UPDATE `creature_template` SET `speed_walk`=0.428571, `unit_flags2`=2099200, `InhabitType`=4, `ScriptName`='npc_fl_ragnaros_platform_stalker', `VerifiedBuild`=0 WHERE `entry`=53952;
-- Breadth of Frost
UPDATE `creature_template` SET `speed_walk`=0.428571, `speed_run`=0.428571, `unit_flags`=33554432, `unit_flags2`=2099200, `InhabitType`=4, `flags_extra`=128, `ScriptName`='npc_ragnaros_breadth_of_frost', `VerifiedBuild`=0 WHERE `entry`=53953;
-- Entrapping Roots
UPDATE `creature_template` SET `speed_walk`=0.428571, `speed_run`=0.428571, `unit_flags`=33554432, `unit_flags2`=2099200, `InhabitType`=4, `flags_extra`=128, `ScriptName`='npc_ragnaros_entrapping_roots', `VerifiedBuild`=0 WHERE `entry`=54074;
-- Dreadflame
UPDATE `creature_template` SET `speed_walk`=0.357143, `unit_flags`=33554432, `unit_flags2`=4196352, `InhabitType`=4, `flags_extra`=128, `ScriptName`='npc_ragnaros_dreadflame', `VerifiedBuild`=0 WHERE `entry`=54127;
-- Cloudburst
UPDATE `creature_template` SET `npcflag`=16777216, `speed_walk`=0.428571, `speed_run`=0.428571, `unit_flags2`=2099200, `InhabitType`=4, `ScriptName`='npc_ragnaros_cloudburst', `VerifiedBuild`=0 WHERE `entry`=54147;
-- Dreadflame Spawn
UPDATE `creature_template` SET `speed_walk`=0.357143, `unit_flags2`=2099200, `InhabitType`=4, `flags_extra`=128, `ScriptName`='npc_ragnaros_dreadflame_spawn', `VerifiedBuild`=0 WHERE `entry`=54203;

-- Ragnaros Texts
DELETE FROM `creature_text` WHERE `entry`=52409;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(52409, 0, 0, 'Mortal Insects! You dare trespass into MY domain?  Your arrogance will be purged in living flame.', 14, 0, 100, 0, 0, 24517, 52203, 1, 'Ragnaros - Intro'),
(52409, 1, 0, 'Die, insect!', 14, 0, 100, 0, 0, 24531, 52204, 1, 'Ragnaros - Kill'),
(52409, 1, 1, 'Pathetic.', 14, 0, 100, 0, 0, 24530, 52205, 1, 'Ragnaros - Kill'),
(52409, 1, 2, 'This is MY realm!', 14, 0, 100, 0, 0, 24529, 52206, 1, 'Ragnaros - Kill'),
(52409, 2, 0, 'Come forth, my servants! Defend your master!', 14, 0, 100, 0, 0, 24513, 52207, 1, 'Ragnaros - Splitting Blow Submerge'),
(52409, 2, 1, 'Minions of fire! Purge the outsiders!', 14, 0, 100, 0, 0, 24514, 52208, 1, 'Ragnaros - Splitting Blow Submerge'),
(52409, 2, 2, 'Denizens of flame, come to me!', 14, 0, 100, 0, 0, 24515, 52209, 1, 'Ragnaros - Splitting Blow Submerge'),
(52409, 2, 3, 'Arise, servants of fire, consume their flesh!', 14, 0, 100, 0, 0, 24516, 52210, 1, 'Ragnaros - Splitting Blow Submerge'),
(52409, 3, 0, 'By fire be purged!', 14, 0, 100, 0, 0, 24532, 52211, 1, 'Ragnaros - Wrath of Ragnaros'),
(52409, 4, 0, 'You will be crushed!', 14, 0, 100, 0, 0, 24520, 52212, 1, 'Ragnaros - Splitting Blow'),
(52409, 4, 1, 'Die!', 14, 0, 100, 0, 0, 24521, 52213, 1, 'Ragnaros - Splitting Blow'),
(52409, 4, 2, 'Your judgement has come!', 14, 0, 100, 0, 0, 24522, 52214, 1, 'Ragnaros - Splitting Blow'),
(52409, 5, 0, 'Enough! I will finish this.', 14, 0, 100, 0, 0, 24523, 52215, 1, 'Ragnaros - Splitting Blow Emerge'),
(52409, 5, 1, 'Fall to your knees, mortals!  This ends now.', 14, 0, 100, 0, 0, 24524, 52216, 1, 'Ragnaros - Splitting Blow Emerge'),
(52409, 5, 2, 'Sulfuras will be your end.', 14, 0, 100, 0, 0, 24525, 52217, 1, 'Ragnaros - Splitting Blow Emerge'),
(52409, 6, 0, 'Too soon! ... You have come too soon...', 14, 0, 100, 0, 0, 24519, 52218, 1, 'Ragnaros - Defeat'),
(52409, 7, 0, 'Too soon...', 14, 0, 100, 0, 0, 24528, 52219, 1, 'Ragnaros - Heroic Transition'),
(52409, 8, 0, 'Arrggh, outsiders - this is not your realm!', 14, 0, 100, 0, 0, 24527, 52220, 1, 'Ragnaros - Heroic Transition'),
(52409, 9, 0, 'When I finish this, your pathetic mortal world will burn with my vengeance!', 14, 0, 100, 0, 0, 24526, 52221, 1, 'Ragnaros - Heroic Transition'),
(52409, 10, 0, 'No, noooo- This was to be my hour of triumph...', 14, 0, 100, 0, 0, 24518, 52222, 1, 'Ragnaros - Death'),
(52409, 11, 0, 'Begone from my realm, insects.', 14, 0, 100, 0, 0, 24533, 52411, 1, 'Ragnaros - Aggro'),
(52409, 11, 1, 'I will see you all burn.', 14, 0, 100, 0, 0, 24534, 52412, 1, 'Ragnaros - Aggro'),
(52409, 11, 2, 'Be consumed by flame!', 14, 0, 100, 0, 0, 24535, 52413, 1, 'Ragnaros - Aggro'),
(52409, 11, 3, 'The realm of fire will consume you!', 14, 0, 100, 0, 0, 24536, 52414, 1, 'Ragnaros - Aggro'),
(52409, 12, 0, 'Deathwing has prepared me to face the vessel of Tarecgosa, your fools journey ends here!', 14, 0, 100, 0, 0, 25162, 52852, 1, 'Ragnaros - Rage of Ragnaros'),
(52409, 13, 0, '|TInterface\\Icons\\ability_mage_worldinflames.blp:20|t%s begins to cast |cFFFF6600|Hspell:99171|h[Engulfing Flames]|h|r!', 41, 0, 100, 0, 0, 0, 52084, 1, 'Ragnaros - Engulfing Flames'),
(52409, 14, 0, '|TInterface\\Icons\\spell_fire_ragnaros_splittingblow.blp:20|t%s begins to cast |cFFFF0000|Hspell:98951|h[Splitting Blow]|h|r!', 41, 0, 100, 0, 0, 0, 52114, 1, 'Ragnaros - Splitting Blow'),
(52409, 15, 0, '|TInterface\\Icons\\spell_fire_selfdestruct.blp:20|t%s casts |cFFFF6600|Hspell:98164|h[Magma Trap]|h|r!', 41, 0, 100, 0, 0, 0, 52115, 1, 'Ragnaros - Magma Trap'),
(52409, 16, 0, '|TInterface\\Icons\\spell_shaman_lavasurge.blp:20|t%s begins to cast |cFFFF0000|Hspell:98710|h[Sulfuras Smash]|h|r!', 41, 0, 100, 0, 0, 0, 52125, 1, 'Ragnaros - Sulfuras Smash'),
(52409, 17, 0, '|TInterface\\Icons\\ability_mage_worldinflames.blp:20|t%s begins to cast |cFFFF6600|Hspell:100171|h[World In Flames]|h|r!', 41, 0, 100, 0, 0, 0, 52450, 1, 'Ragnaros - World In Flames'),
(52409, 18, 0, '|TInterface\\Icons\\inv_mace_2h_sulfuras_d_01.blp:20|t%s begins to cast |cFFFF6600|Hspell:100604|h[Empower Sulfuras]|h|r!', 41, 0, 100, 0, 0, 0, 52709, 1, 'Ragnaros - Empower Sulfuras'),
(52409, 19, 0, '|TInterface\\Icons\\inv_elemental_mote_fire01.blp:16|tYou are about to burst into |cFFFF0000|Hspell:100460|h[Blazing Heat]|h|r!', 41, 0, 100, 0, 0, 0, 52819, 1, 'Ragnaros - Blazing Heat'),
(52409, 20, 0, '|TInterface\\Icons\\ability_warlock_inferno.blp:20|t%s begins to cast |cFFFF6600|Hspell:100777|h[Magma Geyser]|h|r at the cluster of enemies!', 41, 0, 100, 0, 0, 0, 52820, 1, 'Ragnaros - Magma Geyser'),
(52409, 21, 0, '|TInterface\\Icons\\ability_mage_firestarter.blp:20|t%s casts |cFFFF0000|Hspell:100675|h[Dreadflame]|h|r!', 41, 0, 100, 0, 0, 0, 52849, 1, 'Ragnaros - Dreadflame'),
(52409, 22, 0, '|TInterface\\Icons\\achievement_boss_ragnaros.blp:20|tYou are about to cast |cFFFF0000|Hspell:101109|h[Rage of Ragnaros]|h|r!', 41, 0, 100, 0, 0, 0, 52887, 1, 'Ragnaros - Rage of Ragnaros'),
(52409, 23, 0, '%s is about to |cFFFF0000Emerge|r!', 41, 0, 100, 0, 0, 0, 52594, 1, 'Ragnaros - Splitting Blow Emerge');
-- Cenarius Texts
DELETE FROM `creature_text` WHERE `entry`=53872;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(53872, 0, 0, 'No, fiend. Your time is NOW.', 14, 0, 100, 0, 0, 25159, 52569, 1, 'Cenarius - Ragnaros Heroic Phase'),
(53872, 1, 0, 'Perhaps...', 14, 0, 100, 0, 0, 25160, 52572, 1, 'Cenarius - Ragnaros Heroic Outro'),
(53872, 2, 0, 'Ragnaros has perished.  But the primal powers he represents can never be vanquished.  Another will rise to power, someday.', 14, 0, 100, 0, 0, 25158, 52574, 1, 'Cenarius - Ragnaros Heroic Outro'),
(53872, 3, 0, 'Indeed.', 14, 0, 100, 0, 0, 25161, 52576, 1, 'Cenarius - Ragnaros Heroic Outro');
-- Malfurion Stormrage Texts
DELETE FROM `creature_text` WHERE `entry`=53875;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(53875, 0, 0, 'Heroes! He is bound. Finish him!', 14, 0, 100, 0, 0, 25169, 52570, 1, 'Malfurion Stormrage - Ragnaros Heroic Phase'),
(53875, 1, 0, 'It is finished then!', 14, 0, 100, 0, 0, 25170, 52571, 1, 'Malfurion Stormrage - Ragnaros Heroic Outro'),
(53875, 2, 0, 'Heroes, the world owes you a great debt.', 14, 0, 100, 0, 0, 25171, 52573, 1, 'Malfurion Stormrage - Ragnaros Heroic Outro');
-- Arch Druid Hamuul Runetotem Texts
DELETE FROM `creature_text` WHERE `entry`=53876;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(53876, 0, 0, 'Yes Cenarius, we must maintain a constant vigil over this realm.  But let us celebrate this day and the great victory we have earned here.', 14, 0, 100, 0, 0, 25168, 52575, 1, 'Arch Druid Hamuul Runetotem - Ragnaros Heroic Outro');
-- Lava Scion
DELETE FROM `creature_text` WHERE `entry`=53231;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(53231, 0, 0, '|TInterface\\Icons\\inv_elemental_mote_fire01.blp:16|tYou are about to burst into |cFFFF0000|Hspell:100460|h[Blazing Heat]|h|r!', 42, 0, 100, 0, 0, 0, 52819, 0, 'Lava Scion - Blazing Heat Warning');

-- Add Deluge spell click to Cloudburst
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=54147;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES (54147, 100713, 3, 1);

-- Burning Wounds 5 second cooldown
DELETE FROM `spell_proc_event` WHERE `entry`=99399;
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `spellFamilyMask3`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES (99399, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5);

DELETE FROM `spell_script_names` WHERE `spell_id` IN
(98159,98171,98175,98259,98260,98473,98703,98708,98710,98928,98951,98952,
98953,98982,99012,99054,99125,99171,99172,99216,99217,99218,99235,99236,
100342,100344,100345,100459,100472,100476,100503,100567,100594,100604,
100605,100606,100606,100628,100644,100645,100653,100691,100695,100751,
100756,100823,100906,100907,100966,101088,101107,101110,108773);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(98159, 'spell_ragnaros_magma_trap'),
(98171, 'spell_ragnaros_magma_trap_dummy'),
(98175, 'spell_ragnaros_magma_trap_eruption'),
(98259, 'spell_ragnaros_wrath_of_ragnaros'),
(98260, 'spell_ragnaros_wrath_of_ragnaros'),
(98473, 'spell_ragnaros_burning_speed'),
(98703, 'spell_sulfuras_smash_player_trigger'),
(98708, 'spell_ragnaros_sulfuras_smash_damage'),
(98710, 'spell_ragnaros_sulfuras_smash'),
(98928, 'spell_ragnaros_lava_wave'),
(98951, 'spell_ragnaros_splitting_blow'),
(98952, 'spell_ragnaros_splitting_blow'),
(98953, 'spell_ragnaros_splitting_blow'),
(98982, 'spell_ragnaros_submerge'),
(99012, 'spell_ragnaros_splitting_blow_dummy'),
(99054, 'spell_ragnaros_invoke_sons'),
(99125, 'spell_fl_ragnaros_blazing_heat_spawn'),
(99171, 'spell_world_in_flames'),
(99172, 'spell_engulfing_flames'),
(99216, 'spell_engulfing_flames'),
(99217, 'spell_engulfing_flames'),
(99218, 'spell_engulfing_flames'),
(99235, 'spell_engulfing_flames'),
(99236, 'spell_engulfing_flames'),
(100342, 'spell_draw_out_firelord'),
(100344, 'spell_draw_out_firelord'),
(100345, 'spell_draw_out_firelord'),
(100459, 'spell_fl_ragnaros_blazing_heat_target_search'),
(100472, 'spell_ragnaros_breadth_of_frost_trigger'),
(100476, 'spell_fl_ragnaros_npc_helper_summon'),
(100503, 'spell_breadth_of_frost_player_aura'),
(100567, 'spell_breadth_of_frost_meteor_aura'),
(100594, 'spell_fl_ragnaros_superheated'),
(100604, 'spell_ragnaros_empower_sulfuras'),
(100605, 'spell_ragnaros_empower_sulfuras_aura_dummy'),
(100606, 'spell_empower_sulfuras_visual_missile'),
(100606, 'spell_ragnaros_empower_sulfuras_aura_dummy'),
(100628, 'spell_ragnaros_empower_sulfuras_aura'),
(100644, 'spell_fl_ragnaros_npc_helper_summon'),
(100645, 'spell_ragnaros_entrapping_roots_trigger'),
(100653, 'spell_ragnaros_entrapping_roots'),
(100691, 'spell_ragnaros_dreadflame_dummy'),
(100695, 'spell_dreadflame_spread_control_aura'),
(100751, 'spell_ragnaros_cloudburst'),
(100756, 'spell_fl_ragnaros_npc_helper_summon'),
(100823, 'spell_dreadflame_deluge_control_aura'),
(100906, 'spell_dreadflame_spawn_control_aura'),
(100907, 'spell_cenarius_meteor_freeze'),
(100966, 'spell_dreadflame_damage_control_aura'),
(101088, 'spell_ragnaros_lavalogged'),
(101107, 'spell_rage_of_ragnaros_dummy'),
(101110, 'spell_rage_of_ragnaros'),
(108773, 'spell_ragnaros_magma_knockup');

REPLACE INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `femaleName`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `HealthModifierExtra`, `ManaModifier`, `ManaModifierExtra`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES (52409, 53797, 53798, 53799, 0, 0, 37875, 0, 0, 0, 'Ragnaros', '', '', '', 0, 88, 88, 3, 0, 2234, 0, 0.357143, 1.42857, 1, 1, 0, 1500, 2000, 1, 1, 1, 0, 134219776, 0, 0, 0, 0, 0, 4, 268435564, 0, 52409, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 585, 1, 1, 1, 1, 1, 1, 0, 144, 1, 0, 1, 'boss_ragnaros_firelands', 0);
REPLACE INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `femaleName`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `HealthModifierExtra`, `ManaModifier`, `ManaModifierExtra`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES (53393, 0, 0, 0, 0, 0, 19963, 11686, 0, 0, 'Splitting Blow', '', '', '', 0, 88, 88, 3, 0, 35, 0, 1.2, 0.428571, 1, 0, 0, 2000, 2000, 1, 1, 1, 33554432, 2048, 0, 0, 0, 0, 0, 10, 16778276, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 0, 76, 1, 0, 0, '', 15595);
REPLACE INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `femaleName`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `HealthModifierExtra`, `ManaModifier`, `ManaModifierExtra`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES (53485, 0, 0, 0, 0, 0, 19963, 11686, 0, 0, 'Engulfing Flames', '', '', '', 0, 88, 88, 3, 0, 35, 0, 0.428571, 0.428571, 1, 0, 0, 2000, 2000, 1, 1, 1, 33554432, 2099200, 0, 0, 0, 0, 0, 10, 16778276, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 1, 1, 1, 1, 1, 1, 1, 0, 76, 1, 0, 128, 'npc_ragnaros_engulfing_flames', 0);
REPLACE INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `femaleName`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `HealthModifierExtra`, `ManaModifier`, `ManaModifierExtra`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES (53797, 0, 0, 0, 0, 0, 37875, 0, 0, 0, 'Ragnaros (1)', '', '', '', 0, 88, 88, 3, 0, 2234, 0, 0.356, 1.14286, 1, 1, 0, 2000, 2000, 1, 1, 1, 0, 134219776, 0, 0, 0, 0, 0, 4, 268435564, 0, 53797, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1755, 1, 1, 1, 1, 1, 1, 0, 144, 1, 0, 0, '', 15595);
REPLACE INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `femaleName`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `HealthModifierExtra`, `ManaModifier`, `ManaModifierExtra`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES (53798, 0, 0, 0, 0, 0, 37875, 0, 0, 0, 'Ragnaros (2)', '', '', '', 0, 88, 88, 3, 0, 2234, 0, 0.356, 1.14286, 1, 1, 0, 2000, 2000, 1, 1, 1, 0, 134219776, 0, 0, 0, 0, 0, 4, 268435564, 0, 53798, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 863.94, 1, 1, 1, 1, 1, 1, 0, 144, 1, 0, 0, '', 15595);
REPLACE INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `femaleName`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `HealthModifierExtra`, `ManaModifier`, `ManaModifierExtra`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES (53799, 0, 0, 0, 0, 0, 37875, 0, 0, 0, 'Ragnaros (3)', '', '', '', 0, 88, 88, 3, 0, 2234, 0, 0.356, 1.14286, 1, 1, 0, 2000, 2000, 1, 1, 1, 0, 134219776, 0, 0, 0, 0, 0, 4, 268435564, 0, 53799, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 2874.66, 1, 1, 1, 1, 1, 1, 0, 144, 1, 0, 0, '', 15595);
