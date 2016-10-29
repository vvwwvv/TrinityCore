delete from spell_script_names where spell_id in(101111, 99837, 99838);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(101111, 'spell_shannox_riplimb_dogged_determination'),
(99837, 'spell_shannox_crystal_prison_trap'),
 (99838, 'spell_shannox_immolation_trap');

update creature_template set flags_extra = 128 where entry = 53393;



