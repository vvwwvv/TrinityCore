-- Corborus 
DELETE FROM spell_script_names WHERE scriptname='spell_crystal_barrage';
INSERT INTO spell_script_names VALUES
(81638,'spell_crystal_barrage'),
(92648,'spell_crystal_barrage');

UPDATE creature_template SET scriptname="npc_crystal_shard" WHERE entry=49267;