DELETE from spell_script_names where spell_id in(85948);
INSERT INTO spell_script_names (`spell_id`, `ScriptName`) VALUES (85948, 'spell_dk_festering');


delete from achievement_criteria_data where criteria_id = 5829;
insert into achievement_criteria_data (criteria_id, scriptname) VALUES (5829, 'achievement_bucket_list');

update creature_template set scriptname = 'boss_shannox' where entry = 53691;
update creature_template set scriptname = 'npc_riplimb' where entry = 53694;
update creature_template set scriptname = 'npc_rageface' where entry = 53695;
update creature_template set scriptname = 'npc_shannox_spear' where entry = 53752;
update creature_template set scriptname = 'npc_shannox_crystal_prison' where entry = 53819;
update creature_template set scriptname = 'npc_shannox_crystal_prison_trap' where entry = 53713;
update creature_template set scriptname = 'npc_shannox_immolation_trap' where entry = 53724;
delete from creature where id in(53694, 53695);