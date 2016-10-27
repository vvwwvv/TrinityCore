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

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "firelands.h"
//#include <minwindef.h>

BossBoundaryData const bounderies =
{
	{ DATA_RAGNAROS, new CircleBoundary(Position(1040.0f, -57.0f), 80) },
};

DoorData const doorData[] =
{
	{ GO_RAGNAROS_DOOR,         DATA_RAGNAROS,              DOOR_TYPE_ROOM },
	{ 0,                        0,                          DOOR_TYPE_ROOM } //END
};

class instance_firelands : public InstanceMapScript
{
public:
	instance_firelands() : InstanceMapScript(FirelandsScriptName, 720) { }

	struct instance_firelands_InstanceScript : public InstanceScript
	{
		instance_firelands_InstanceScript(InstanceMap* map) : InstanceScript(map)
		{
			SetHeaders(DataHeader);
			SetBossNumber(EncounterCount);
			LoadBossBoundaries(bounderies);
			LoadDoorData(doorData);

			RagnarosEmerged = false;
			RagnarosFirstEmerge = false;
		}

		void OnCreatureCreate(Creature* creature) override
		{
			switch (creature->GetEntry())
			{
			case NPC_SMOULDERING_HATCHLING:
				// Cannot directly start attacking here as the creature is not yet on map
				creature->m_Events.AddEvent(new DelayedAttackStartEvent(creature), creature->m_Events.CalculateTime(500));
				break;
			case NPC_RAGNAROS:
				RagnarosGUID = creature->GetGUID();
				break;
			case NPC_SULFURAS:
				SulfurasGUID = creature->GetGUID();
				break;
			case NPC_CENARIUS:
				CenariusGUID = creature->GetGUID();
				break;
			case NPC_HAMUUL_RUNETOTEM:
				HamuulGUID = creature->GetGUID();
				break;
			case NPC_MALFURION_STORMRAGE:
				MalfurionGUID = creature->GetGUID();
				break;
			case NPC_DREADFLAME:
				DreadflameGUID = creature->GetGUID();
				break;
			default:
				break;
			}
		}

		void OnGameObjectCreate(GameObject* go) override
		{
			/*if ((go->GetAreaId() == AREA_SULFURON_KEEP_COURTYARD || go->GetAreaId() == AREA_SULFURON_KEEP) && !CourtyardDefeated() && go->GetEntry() != GO_RAGNAROS_PLATFORM)
			{
			go->SetInPhase(PHASE_DUNGEON_ALTERNATE, true, true);
			}*/

			switch (go->GetEntry())
			{
			case GO_RAGNAROS_DOOR:
				AddDoor(go, true);
				break;
			case GO_RAGNAROS_PLATFORM:
				RagnarosPlatformGUID = go->GetGUID();
				break;
			default:
				break;
			}
		}

		void OnGameObjectRemove(GameObject* go) override
		{
			switch (go->GetEntry())
			{
			case GO_RAGNAROS_DOOR:
				AddDoor(go, false);
				break;
			default:
				break;
			}

			InstanceScript::OnGameObjectRemove(go);
		}

		bool SetBossState(uint32 type, EncounterState state) override
		{
			if (!InstanceScript::SetBossState(type, state))
				return false;

			switch (type)
			{
			case DATA_RAGNAROS:
				if (state == FAIL)
				{
					scheduler.Schedule(Seconds(35), [this](TaskContext)
					{
						instance->SummonCreature(NPC_RAGNAROS, { 1075.201f, -57.84896f, 55.42427f, 3.159046f });
					});
				}
				break;
			}

			return true;
		}

		void SetData(uint32 data, uint32 value) override
		{
			switch (data)
			{
			case DATA_RAGNAROS_EMERGED:
				RagnarosEmerged = value == true;
				if (RagnarosEmerged && !GetCreature(NPC_RAGNAROS))
					instance->SummonCreature(NPC_RAGNAROS, { 1075.201f, -57.84896f, 55.42427f, 3.159046f });
				break;
			case DATA_RAGNAROS_FIRST_EMERGE:
				RagnarosFirstEmerge = value == true;
				break;
			}
		}

		uint32 GetData(uint32 data) const override
		{
			switch (data)
			{
			case DATA_RAGNAROS_EMERGED:
				return RagnarosEmerged ? true : false;
			case DATA_RAGNAROS_FIRST_EMERGE:
				return RagnarosFirstEmerge ? true : false;
			}

			return 0;
		}

		ObjectGuid GetGuidData(uint32 type) const override
		{
			switch (type)
			{
			case NPC_RAGNAROS:
				return RagnarosGUID;
			case NPC_SULFURAS:
				return SulfurasGUID;
			case NPC_CENARIUS:
				return CenariusGUID;
			case NPC_HAMUUL_RUNETOTEM:
				return HamuulGUID;
			case NPC_MALFURION_STORMRAGE:
				return MalfurionGUID;
			case NPC_DREADFLAME:
				return DreadflameGUID;

			case GO_RAGNAROS_PLATFORM:
				return RagnarosPlatformGUID;
			}

			return ObjectGuid::Empty;
		}

		void Update(uint32 diff) override
		{
			InstanceScript::Update(diff);

			scheduler.Update(diff);
		}

	protected:
		bool RagnarosEmerged;
		bool RagnarosFirstEmerge;

		// Creatures
		ObjectGuid RagnarosGUID;
		ObjectGuid SulfurasGUID;
		ObjectGuid CenariusGUID;
		ObjectGuid HamuulGUID;
		ObjectGuid MalfurionGUID;
		ObjectGuid DreadflameGUID;

		// GameObjects
		ObjectGuid RagnarosPlatformGUID;

		TaskScheduler scheduler;
	};

	InstanceScript* GetInstanceScript(InstanceMap* map) const override
	{
		return new instance_firelands_InstanceScript(map);
	}
};

void AddSC_instance_firelands()
{
	new instance_firelands();
}
