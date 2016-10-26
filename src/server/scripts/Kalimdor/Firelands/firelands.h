/*
* Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FIRELANDS_H_
#define FIRELANDS_H_

#include "Map.h"
#include "CreatureTextMgr.h"
#include "CreatureAI.h"
#include "ScriptedCreature.h"
#include "PassiveAI.h"

#define DataHeader "FL"
#define FirelandsScriptName "instance_firelands"

uint32 const EncounterCount = 7;

enum DataTypes
{
	DATA_BETH_TILAC = 0,
	DATA_LORD_RHYOLITH = 1,
	DATA_SHANNOX = 2,
	DATA_ALYSRAZOR = 3,
	DATA_BALEROC = 4,
	DATA_MAJORDOMO_STAGHELM = 5,
	DATA_RAGNAROS = 6,

	DATA_RAGNAROS_EMERGED = 7,
	DATA_RAGNAROS_FIRST_EMERGE = 8,


	DATA_RIPLIMB = 9,
	DATA_RAGEFACE = 10,
};

enum CreatureIds
{
	// Bosses
	NPC_SHANNOX = 53691,
	NPC_LORD_RHYOLITH = 52558,
	NPC_BETH_TILAC = 52498,
	NPC_ALYSRAZOR = 52530,
	NPC_BALEROC = 53494,
	NPC_MAJORDOMO_STAGHELM = 52571,
	NPC_RAGNAROS = 52409,
	//Shannox

	NPC_RAGEFACE = 53695,
	NPC_RIPLIMB = 53694,

	// Alysrazor
	NPC_BLAZING_MONSTROSITY_LEFT = 53786,
	NPC_BLAZING_MONSTROSITY_RIGHT = 53791,
	NPC_EGG_PILE = 53795,
	NPC_HARBINGER_OF_FLAME = 53793,
	NPC_MOLTEN_EGG_TRASH = 53914,
	NPC_SMOULDERING_HATCHLING = 53794,
	
	// Ragnaros
	NPC_RAGNAROS_MAGMA = 53729,
	NPC_MAGMA_TRAP = 53086,
	NPC_ENGULFING_FLAMES = 53485,
	NPC_SPLITTING_BLOW = 53393,
	NPC_SULFURAS_SMASH = 53268,
	NPC_SULFURAS_SMASH_TRIGGER = 53266,
	NPC_LAVA_WAVE = 53363,
	NPC_SULFURAS = 53420,
	NPC_SON_OF_FLAME = 53140,
	NPC_MOLTEN_ELEMENTAL = 53189,
	NPC_LAVA_SCION = 53231,
	NPC_RAGNAROS_LIVING_METEOR = 53500,
	NPC_RAGNAROS_LIVING_METEOR_25N = 53813,
	NPC_RAGNAROS_LIVING_METEOR_10H = 53814,
	NPC_RAGNAROS_LIVING_METEOR_25H = 53815,
	NPC_MOLTEN_SEED_CASTER = 53186,
	NPC_BLAZING_HEAT = 53473,

	NPC_CENARIUS = 53872,
	NPC_MALFURION_STORMRAGE = 53875,
	NPC_HAMUUL_RUNETOTEM = 53876,

	NPC_PLATFORM_STALKER = 53952,
	NPC_CLOUDBURST = 54147,
	NPC_BREADTH_OF_FROST = 53953,
	NPC_ENTRAPPING_ROOTS = 54074,
	NPC_DREADFLAME = 54127,
	NPC_DREADFLAME_SPAWN = 54203,

	// Other
	NPC_MAGMA_ORB = 54299,
	NPC_FIRELANDS_BRIDGE_STALKER = 42098,
	NPC_TELEPORT_TO_MAJORDOMO = 54348,
	NPC_TELEPORT_TO_FLAMEBREACH = 54367,
	NPC_SMOULDERING_ESSENCE_CREDIT = 54198,
};

enum GameobjectIds
{
	GO_RAGNAROS_DOOR = 209073,
	GO_RAGNAROS_PLATFORM = 208835,
};

enum FirelandsQuests
{
	QUEST_HEART_OF_FLAME_A = 29307,
	QUEST_HEART_OF_FLAME_H = 29308
};

enum FirelandsItems
{
	ITEM_HEART_OF_FLAME = 69848,
};

enum DungeonPhases
{
	PHASE_DUNGEON_ALTERNATE = 170,
};

enum QuestDefines
{
	// quest
	GO_BRANCH_OF_NORDRASSIL = 209100,

	// Cannot find rhyolith fragment, summon it manualy
	SPELL_CREATE_EMBERSTONE_FRAGMENT = 100518,
	SPELL_CREATE_CHITINOUS_FRAGMENT = 100520,
	SPELL_CREATE_PYRESHELL_FRAGMENT = 100519,

	SPELL_CHARGED_RHYOLITH_FOCUS = 100481,
	SPELL_CHARGED_EMBERSTONE_FOCUS = 100499,
	SPELL_CHARGED_CHITINOUS_FOCUS = 100501,
	SPELL_CHARGED_PYRESHELL_FOCUS = 100500,

	SPELL_TRANSFORM_CHARGED_RHYOLITH_FOCUS = 100477,
	SPELL_TRANSFORM_CHARGED_EMBERSTONE_FOCUS = 100496,
	SPELL_TRANSFORM_CHARGED_CHITINOUS_FOCUS = 100498,
	SPELL_TRANSFORM_CHARGED_PYRESHELL_FOCUS = 100497,

	GO_RHYOLITH_FRAGMENT = 209033,
	GO_EMBERSTONE_FRAGMENT = 209035,
	GO_PYRESHELL_FRAGMENT = 209036,
	GO_OBSIDIAN_FLECKED_CHITIN = 209037,

	NPC_DULL_RHYOLITH_FOCUS = 53951,
	NPC_DULL_EMBERSTONE_FOCUS = 53968,
	NPC_DULL_CHITINOUS_FOCUS = 53970,
	NPC_DULL_PYRESHELL_FOCUS = 53963,

	NPC_CHARGED_RHYOLITH_FOCUS = 53955,
	NPC_CHARGED_EMBERSTONE_FOCUS = 53969,
	NPC_CHARGED_CHITINOUS_FOCUS = 53971,
	NPC_CHARGED_PYRESHELL_FOCUS = 53967,

	EVENT_PORTALS = 28888,

	SPELL_LEGENDARY_PORTAL_OPENING = 101029,
	SPELL_BRANCH_OF_NORDRASSIL_WIN_COSMETIC = 100326,
	SPELL_SMOLDERING_AURA = 101093,
	SPELL_SIPHON_ESSENCE_CREDIT = 101149,
	SPELL_HEART_OF_RAGNAROS_CREATE = 101125,

	QUEST_HEART_OF_FLAME_ALLIANCE = 29307,
	QUEST_HEART_OF_FLAME_HORDE = 29308,
};

class DelayedAttackStartEvent : public BasicEvent
{
public:
	DelayedAttackStartEvent(Creature* owner) : _owner(owner) { }

	bool Execute(uint64 /*e_time*/, uint32 /*p_time*/) override
	{
		_owner->AI()->DoZoneInCombat(_owner, 200.0f);
		return true;
	}

private:
	Creature* _owner;
};


class PlayerCheck
{
public:
	bool operator()(WorldObject* object) const
	{
		return object->GetTypeId() != TYPEID_PLAYER;
	}
};

template<class AI>
CreatureAI* GetFirelandsAI(Creature* creature)
{
	if (InstanceMap* instance = creature->GetMap()->ToInstanceMap())
		if (instance->GetInstanceScript())
			if (instance->GetScriptId() == sObjectMgr->GetScriptId(FirelandsScriptName))
				return new AI(creature);
	return NULL;
}

#endif // FIRELANDS_H_