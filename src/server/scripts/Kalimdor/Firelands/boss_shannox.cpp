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
/*
ScriptData 50%

Needs fixing on Hurl Spear, Magma Rupture, Crystal Prison Trap, Immolation Trap, and some other things.

*/
#include "GridNotifiers.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Player.h"
#include "firelands.h"

enum Spells
{
	SPELL_BERSERK = 26662,
	SPELL_ARCING_SLASH = 99931,
	SPELL_HURL_SPEAR_AOE = 100031,
	SPELL_HURL_SPEAR_SUMMON = 99978,
	SPELL_HURL_SPEAR_DMG = 100002,
	SPELL_SPEAR_TARGET = 99988,
	SPELL_SPEAR_VISUAL = 100005,
	SPELL_FETCH_SPEAR = 100026,
	SPELL_MAGMA_RUPTURE = 99840,
	SPELL_MAGMA_RUPTURE_MISSILE = 99841,
	SPELL_MAGMA_FLARE = 100495,
	SPELL_FRENZY = 100522,
	SPELL_THROW_IMMOLATION_TRAP = 99839,
	SPELL_IMMOLATION_TRAP_DMG = 99838,
	SPELL_THROW_CRYSTAL_PRISON_TRAP = 99836,
	SPELL_CRYSTAL_PRISON_TRAP = 99837,

	// Riplimb
	SPELL_LIMB_RIP = 99832,
	SPELL_DOGGED_DETERMINATION = 101111,

	// Rageface
	SPELL_FACE_RAGE = 99945,
	SPELL_FACE_RAGE1 = 99947,
	SPELL_FACE_RAGE_DUMMY = 100129,
	SPELL_RAGE = 100415,

	//Shared Spells
	SPELL_SEPARATION_ANXIETY = 99835,
	SPELL_FEEDING_FRENZY = 100655,
	SPELL_FRENZIED_DEVOTION = 100064,
	SPELL_WARRY = 100167,
	SPELL_WARRY_25 = 101215,
	SPELL_WARRY_10H = 101216,
	SPELL_WARRY_25H = 101217,



	SPELL_SMOULDERING = 101093,


};

enum Events
{
	EVENT_BERSERK = 1,
	EVENT_ARCING_SLASH = 2,
	EVENT_IMMOLATION_TRAP = 3,
	EVENT_CRYSTAL_PRISON_TRAP = 4,
	EVENT_HURL_SPEAR = 5,
	EVENT_MAGMA_RUPTURE = 6,
	EVENT_LIMB_RIP = 7,
	EVENT_FETCH_SPEAR = 8,
	EVENT_SEPARATION_ANXIETY = 9,
	EVENT_CHANGE_TARGET = 10,
	EVENT_FACE_RAGE = 11,
	EVENT_RESURRECT = 12,
	EVENT_MAGMA_RUPTURE_2 = 13,
	EVENT_UNIT_IN_LOS = 14,
	EVENT_CHECK_COMBAT = 15,
};
enum Adds
{
	NPC_SPEAR_OF_SHANNOX_1 = 53752, 
	NPC_SPEAR_OF_SHANNOX_2 = 54112, //?
	NPC_CRYSTAL_PRISON_TRAP = 53713,
	NPC_CRYSTAL_PRISON = 53819,
	NPC_IMMOLATION_TRAP = 53724,
};

enum Emotes
{
};

enum Misc
{
	ACTION_HURL_SPEAR = 1,
	ACTION_RESURRECT = 2,
	POINT_SPEAR_OF_SHANNOX = 3,
	DATA_TRAPPED_PLAYER = 4,
	DATA_TRAPPED_DOG = 5,
};
enum BucketListAreaIds
{
	AREA_1 = 5764, //Beth'tilac's Lair
	AREA_2 = 5821, //Path of Corruption
	AREA_3 = 5766, //Shatterstone
	AREA_4 = 5791, //Ridge of Ancient Flame
	AREA_5 = 5765, //Flamebreach
};
const Position dogPos[2] =
{
	{ 29.158001f, -73.9114999f, 54.783500f, 3.15f}, // Riplimb
	{ 29.515600f, -65.701401f, 54.585499f, 3.15f }  // Rageface
};
class boss_shannox: public CreatureScript
{
public:
	boss_shannox() : CreatureScript("boss_shannox") { }

	struct boss_shannoxAI : public BossAI
	{
		boss_shannoxAI(Creature* creature) : BossAI(creature, DATA_SHANNOX) { Initialize(); }

		void Initialize()
		{
			me->LoadPath(4599104);
			me->Yell("Yes... I smell them too, Riplimb. Outsiders encroach on the Firelord's private grounds. Find their trail, find them for me, that I may dispense punishment!", LANG_UNIVERSAL);
				
			me->PlayDistanceSound(24584);
		}

		void Reset() override
		{
			_Reset();


			if (Creature * riplimb = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_RIPLIMB)))
				riplimb->DespawnOrUnsummon();
			if (Creature * rageface = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_RAGEFACE)))
				rageface->DespawnOrUnsummon();


			me->SummonCreature(NPC_RIPLIMB, dogPos[0]);
			me->SummonCreature(NPC_RAGEFACE, dogPos[1]);

			for (int i = 0; i < 5; i++)
				areas[i] = false;  //If wipe reset achievment
		}

		bool AllowAchieve()
		{
			for (uint8 i = 0; i < 5; i++)
				if (!areas[i])
					return false;
			return true;
		}
		

		void EnterCombat(Unit* /*target*/) override
		{
			instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
			me->Yell("Aha! The interlopers... Kill them! EAT THEM!", LANG_UNIVERSAL);
			me->PlayDirectSound(24565);
			RiplimbDead = false;
			RagefaceDead = false;


			for (int i = 0; i < 5; i++)
				areas[i] = false; 


			if (Creature* riplimb = me->FindNearestCreature(NPC_RIPLIMB, 1000.0f, true))

				DoZoneInCombat(riplimb);
			else
				_Reset();//Riplimb is missing, Reset
			if (Creature* rageface = me->FindNearestCreature(NPC_RAGEFACE, 1000.0f, true))
				DoZoneInCombat(rageface);
			else
				_Reset();//Rageface is missing, Reset

			events.ScheduleEvent(EVENT_BERSERK, 10 * MINUTE * IN_MILLISECONDS);
			events.ScheduleEvent(EVENT_HURL_SPEAR, 15000);
			events.ScheduleEvent(EVENT_SEPARATION_ANXIETY, 2000);

			events.ScheduleEvent(EVENT_IMMOLATION_TRAP, urand(10000, 20000));
			events.ScheduleEvent(EVENT_CRYSTAL_PRISON_TRAP, urand(10000, 25500));
			events.ScheduleEvent(EVENT_ARCING_SLASH, urand(10000, 12000));
			events.ScheduleEvent(EVENT_CHECK_COMBAT, 5000);

			DoZoneInCombat();
			_EnterCombat();
		}

		void KilledUnit(Unit* who) override
		{
			int killed = urand(1, 4);
			switch (killed)
			{
			case 1:
				me->Yell("Yes... oh yes!", LANG_UNIVERSAL);
				me->PlayDirectSound(24581);
				break;
			case 2:
				me->Yell("The Firelord will be most pleased!", LANG_UNIVERSAL);
				me->PlayDirectSound(24580);
				break;
			case 3:
				me->Yell("Now you stay dead!", LANG_UNIVERSAL);
				me->PlayDirectSound(24579);
				break;
			case 4:
				me->Yell("Dog food!", LANG_UNIVERSAL);
				me->PlayDirectSound(24578);
				break;
			}
		}

		void JustDied(Unit* /*killer*/) override
		{
			_JustDied();
			instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
			me->Yell("The pain... Lord of fire, it hurts...", LANG_UNIVERSAL);

			me->PlayDirectSound(24568);
			if (Creature * riplimb = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_RIPLIMB)))
				riplimb->DespawnOrUnsummon();
			if (Creature * rageface = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_RAGEFACE)))
				rageface->DespawnOrUnsummon();

			Map::PlayerList const& playerList = me->GetMap()->GetPlayers();
			for (auto const& playerRef : playerList)
			{
				Player* player = playerRef.GetSource();
				if (player->HasQuestForItem(69848))
				{
					DoCastAOE(SPELL_SMOULDERING);
					break;
				}
			}
			
		}

		void EnterEvadeMode(EvadeReason /*why*/) override
		{
			_Reset();
			events.Reset();
			me->DespawnOrUnsummon();
		}


		void UpdateAI(uint32 diff) override
		{
			if (!UpdateVictim())
				return;

			// Bucket List
			switch (me->GetAreaId())
			{
			case AREA_1:
				if (!areas[0])
					areas[0] = true;
				break;
			case AREA_2:
				if (!areas[1])
					areas[1] = true;
				break;
			case AREA_3:
				if (!areas[2])
					areas[2] = true;
				break;
			case AREA_4:
				if (!areas[3])
					areas[3] = true;
				break;
			case AREA_5:
				if (!areas[4])
					areas[4] = true;
				break;
			}

			events.Update(diff);

			if (!IsHeroic() && !frenzy && me->HealthBelowPct(30))
			{
				frenzy = true;
				if (Creature* riplimb = me->FindNearestCreature(NPC_RIPLIMB, 1000.0f, true))
						riplimb->CastSpell(riplimb, SPELL_FRENZIED_DEVOTION, true);
				if (Creature* rageface = me->FindNearestCreature(NPC_RAGEFACE, 1000.0f, true))
					rageface->CastSpell(rageface, SPELL_FRENZIED_DEVOTION, true);
			}

			if (me->HasUnitState(UNIT_STATE_CASTING))
				return;

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_CHECK_COMBAT:
					if (me->IsInCombat())
					{
						if (Creature* riplimb = me->FindNearestCreature(NPC_RIPLIMB, 1000.0f, true))
							if (riplimb->IsInCombat() && !riplimb->IsInEvadeMode())
									DoZoneInCombat(riplimb);

						if (Creature* rageface = me->FindNearestCreature(NPC_RAGEFACE, 1000.0f, true))
							if (rageface->IsInCombat() && !rageface->IsInEvadeMode())
								DoZoneInCombat(rageface);

					}
					break;

				case EVENT_SEPARATION_ANXIETY:

					if (Creature* riplimb = me->FindNearestCreature(NPC_RIPLIMB, 1000.0f, true))
						if(riplimb->IsAlive())
							if ( !me->IsWithinDist(riplimb, 80.0f) && !me->HasAura(SPELL_SEPARATION_ANXIETY))
							DoCast(me, SPELL_SEPARATION_ANXIETY, true);

					if (Creature* rageface = me->FindNearestCreature(NPC_RAGEFACE, 1000.0f, true))
						if(rageface->IsAlive())
							if ( !me->IsWithinDist(rageface, 80.0f) && !me->HasAura(SPELL_SEPARATION_ANXIETY))
							DoCast(me, SPELL_SEPARATION_ANXIETY, true);


					events.ScheduleEvent(EVENT_SEPARATION_ANXIETY, 2000);
					break;

				case EVENT_BERSERK:
					DoCast(me, SPELL_BERSERK);
					break;

				case EVENT_ARCING_SLASH:
					DoCastVictim(SPELL_ARCING_SLASH);
					events.ScheduleEvent(EVENT_ARCING_SLASH, urand(18000, 22000));
					break;

				case EVENT_HURL_SPEAR:
					if (Creature* riplimb = me->FindNearestCreature(NPC_RIPLIMB, 300.0f))
						DoCast(riplimb, SPELL_HURL_SPEAR_SUMMON, true);
					events.ScheduleEvent(EVENT_HURL_SPEAR, 42000);
					break;

				case EVENT_IMMOLATION_TRAP:
					if (Unit* rTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
						DoCast(rTarget, SPELL_THROW_IMMOLATION_TRAP);
					events.ScheduleEvent(EVENT_IMMOLATION_TRAP, urand(23000, 30000));
					break;
				case EVENT_CRYSTAL_PRISON_TRAP:
					if (Unit* rTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
						DoCast(rTarget, SPELL_THROW_CRYSTAL_PRISON_TRAP);
					events.ScheduleEvent(EVENT_CRYSTAL_PRISON_TRAP, 25500);
					break;
				case EVENT_MAGMA_RUPTURE:
					DoCast(me, SPELL_MAGMA_RUPTURE);
					events.ScheduleEvent(EVENT_MAGMA_RUPTURE_2, 1500);
					events.ScheduleEvent(EVENT_MAGMA_RUPTURE, 20000);
					break;
				case EVENT_MAGMA_RUPTURE_2:
					// There will be a spiral, 3 "circles", 20 points per circle
					Position pos;
					for (uint8 i = 0; i < 60; ++i)
					{
						me->GetNearPosition( 15.0f + i * 0.75f, (M_PI * i) / 10);
						pos.m_positionZ = me->GetMap()->GetHeight(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), true, MAX_HEIGHT);
						me->CastSpell(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), SPELL_MAGMA_RUPTURE_MISSILE, true);
					}
					break;
						

				}
			}

			DoMeleeAttackIfReady();
		}

	

	private:
		uint32 Phase;
		bool RiplimbDead = false;
		bool RagefaceDead = false;
		bool areas[5];
		bool frenzy = false;
		

	};

	CreatureAI* GetAI(Creature* creature) const override
	{
		return GetFirelandsAI<boss_shannoxAI>(creature);
	}
};

class npc_riplimb : public CreatureScript
{
public:
	npc_riplimb() : CreatureScript("npc_riplimb") {}

	struct npc_riplimbAI : public CreatureAI
	{
		npc_riplimbAI(Creature* creature) : CreatureAI(creature) { Initialize();  }

		void Initialize()
		{
			if(Creature* shannox = me->FindNearestCreature(NPC_SHANNOX, 500.0f, true))

				me->GetMotionMaster()->MoveFollow(shannox, 0.0f, 0.0f);
		}

		void Reset() override
		{
			fetch = false;
			dead = false;

			if (me->GetMap()->IsHeroic())
				DoCast(me, SPELL_FEEDING_FRENZY, true);
		}

		void EnterEvadeMode(EvadeReason /*why*/) override
		{
			me->DespawnOrUnsummon();
		}
		void JustDied(Unit* /*killer*/)
		{

			if (Creature* shannox = me->FindNearestCreature(NPC_SHANNOX, 1000.0f))
			{
				shannox->Yell("Riplimb! No... no! Oh, you terrible little beasts! HOW COULD YOU?!", LANG_UNIVERSAL);
				shannox->PlayDirectSound(24574);
				shannox->AddAura(SPELL_FRENZY, shannox);
			}
		}

		void EnterCombat(Unit* /*target*/) override
		{
			if (Creature* shannox = me->FindNearestCreature(NPC_SHANNOX, 1000.0f))
				DoZoneInCombat(shannox);
			else
				me->DespawnOrUnsummon();//Shannox is not there? Despawn

			DoZoneInCombat();
		}
		void DamageTaken(Unit* attacker, uint32& damage) override
		{
			if (!me->GetMap()->IsHeroic())
				return;

			if (damage >= me->GetHealth() && !dead)
			{
				dead = true;
				damage = 0;
				me->SetReactState(REACT_PASSIVE);
				me->AttackStop();
				events.Reset();
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
				me->SetStandState(UNIT_STAND_STATE_DEAD);
				me->RemoveAllAuras();
				events.ScheduleEvent(EVENT_RESURRECT, 30000);
			}
		}
		
		void DoAction(int32 action) override
		{
			switch (action)
			{
				case ACTION_HURL_SPEAR:
					if (dead)
					{
						if (Creature* spear = me->FindNearestCreature(NPC_SPEAR_OF_SHANNOX_1, 300.0f))
							spear->DespawnOrUnsummon();
						return;
					}
					events.Reset();
					me->SetReactState(REACT_PASSIVE);
					me->AttackStop();
					me->RemoveMovementImpairingAuras();
					me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SNARE, false);
					DoCast(me, SPELL_DOGGED_DETERMINATION, true);
					break;
				
			}
		}
		void MovementInform(uint32 type, uint32 id) override
		{
			if (type == POINT_MOTION_TYPE)
			{
				if (id == POINT_SPEAR_OF_SHANNOX)
				{
					if (Creature* spear = me->FindNearestCreature(NPC_SPEAR_OF_SHANNOX_1, 300.0f))
						spear->DespawnOrUnsummon();
					DoCast(me, SPELL_FETCH_SPEAR, true);
					events.ScheduleEvent(EVENT_FETCH_SPEAR, 500);
				}
			}
		}

		void UpdateAI(uint32 diff) override
		{
			if (fetch)
			{
				if (Creature* pShannox = me->FindNearestCreature(NPC_SHANNOX, 1.0f))
				{
					fetch = false;
					me->RemoveAurasDueToSpell(SPELL_DOGGED_DETERMINATION);
					me->RemoveAurasDueToSpell(SPELL_FETCH_SPEAR);
					me->GetMotionMaster()->MovementExpired();
					me->RemoveMovementImpairingAuras();
					me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SNARE, true);
					me->SetReactState(REACT_AGGRESSIVE);
					events.ScheduleEvent(EVENT_LIMB_RIP, 5000);
					if (me->GetVictim())
						AttackStart(me->GetVictim());
					else
					{
						if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0.0f, 0.0f, true))
							AttackStart(pTarget);
					}
				}
				return;
			}

			if (!UpdateVictim() && !dead)
				return;

			events.Update(diff);

			if (me->HasUnitState(UNIT_STATE_CASTING))
				return;

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_CHECK_COMBAT:
					if (me->IsInCombat())
					{

						if (Creature* shannox = me->FindNearestCreature(NPC_SHANNOX, 1000.0f, true))
							if (shannox->IsInCombat() && !shannox->IsInEvadeMode())
								DoZoneInCombat(shannox);

						if (Creature* rageface = me->FindNearestCreature(NPC_RAGEFACE, 1000.0f, true))
							if (rageface->IsInCombat() && !rageface->IsInEvadeMode())
								DoZoneInCombat(rageface);
					}
					events.ScheduleEvent(EVENT_CHECK_COMBAT, 5000);
					break;
				case EVENT_SEPARATION_ANXIETY:
					if (!me->FindNearestCreature(NPC_SHANNOX, 80.0f) && !me->HasAura(SPELL_SEPARATION_ANXIETY))
						DoCast(me, SPELL_SEPARATION_ANXIETY, true);
					events.ScheduleEvent(EVENT_SEPARATION_ANXIETY, 2000);
					break;
				case EVENT_FETCH_SPEAR:
					if (Creature* pShannox = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_SHANNOX)))
					{
						fetch = true;
						me->GetMotionMaster()->MovementExpired(false);
						me->GetMotionMaster()->MoveFollow(pShannox, 0.0f, 0.0f);
					}
					break;
				case EVENT_LIMB_RIP:
					DoCastVictim(SPELL_LIMB_RIP);
					events.ScheduleEvent(EVENT_LIMB_RIP, urand(20000, 22000));
					break;
				case EVENT_RESURRECT:
					me->SetReactState(REACT_AGGRESSIVE);

					me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
					me->SetStandState(UNIT_STAND_STATE_STAND);
					me->SetHealth(me->GetMaxHealth());
					me->GetMotionMaster()->MoveChase(me->GetVictim());
					if (instance)
						if (Unit* pShannox = ObjectAccessor::GetUnit(*me, instance->GetGuidData(DATA_SHANNOX)))
							pShannox->GetAI()->DoAction(ACTION_RESURRECT);
					break;
				}
			}
			
			DoMeleeAttackIfReady();


		}
	private:
		bool fetch;
		bool dead;
		EventMap events;
		InstanceScript* instance = me->GetInstanceScript();

	};


	CreatureAI* GetAI(Creature* creature) const override
	{
		return GetFirelandsAI<npc_riplimbAI>(creature);
	}
};

class npc_rageface: public CreatureScript
{
public:
	npc_rageface() : CreatureScript("npc_rageface") {}

	struct npc_ragefaceAI : public CreatureAI
	{
		npc_ragefaceAI(Creature* creature) : CreatureAI(creature) { Initialize(); }

		void Initialize()
		{
			if (Creature* shannox = me->FindNearestCreature(NPC_SHANNOX, 500.0f, true))

				me->GetMotionMaster()->MoveFollow(shannox, 0.0f, 0.0f);
		}
		void Reset() override
		{
			events.Reset();
			if (me->GetMap()->IsHeroic())
				DoCast(me, SPELL_FEEDING_FRENZY, true);
		}

		void EnterEvadeMode(EvadeReason /*why*/) override
		{
			me->DespawnOrUnsummon();
		}
		void JustDied(Unit* /*killer*/)
		{

			if (Creature* shannox = me->FindNearestCreature(NPC_SHANNOX, 1000.0f))
			{
			shannox->Yell("You murderers! Why... why would you kill such a noble animal?!", LANG_UNIVERSAL);
			shannox->PlayDirectSound(24575);
				shannox->AddAura(SPELL_FRENZY,  shannox);
			}
		}

		void EnterCombat(Unit* /*target*/) override
		{
			if (Creature* shannox = me->FindNearestCreature(NPC_SHANNOX, 1000.0f))
				DoZoneInCombat(shannox);
			else
				me->DespawnOrUnsummon();//Shannox is not there? Despawn

		}
		void DamageTaken(Unit* attacker, uint32 &damage) override
		{
			if (attacker->GetTypeId() != TYPEID_PLAYER)
				return;

			if (AuraEffect* const aurEff = me->GetAuraEffect((100129, 101212, 101213, 101214), EFFECT_1))
			{
				if (int32(damage) >= aurEff->GetAmount())
				{
					me->InterruptSpell(CURRENT_CHANNELED_SPELL, false);
					//me->GetAI()->DoResetThreat();
					DoCast(attacker, SPELL_RAGE, true);
					me->AddThreat(attacker, 10000000.0f);
					AttackStart(attacker);
					me->RemoveAurasDueToSpell((100129, 101212, 101213, 101214));
				}
			}
		}

		void MovementInform(uint32 type, uint32 id) override
		{

			if (id == EVENT_JUMP)
			{
				if (Unit* pTarget = me->GetVictim())
					DoCast(pTarget, SPELL_FACE_RAGE1, true);
			}
		}

		void UpdateAI(uint32 diff) override
		{
			
			if (!UpdateVictim())
				return;

			events.Update(diff);

			if (me->HasUnitState(UNIT_STATE_CASTING))
				return;

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_CHECK_COMBAT:
					if (me->IsInCombat())
					{
						if (Creature* shannox = me->FindNearestCreature(NPC_SHANNOX, 1000.0f, true))
							if (shannox->IsInCombat() && !shannox->IsInEvadeMode())
								DoZoneInCombat(shannox);

						if (Creature* riplimb = me->FindNearestCreature(NPC_RIPLIMB, 1000.0f, true))
							if (riplimb->IsInCombat() && !riplimb->IsInEvadeMode())
								DoZoneInCombat(riplimb);
					}
					events.ScheduleEvent(EVENT_CHECK_COMBAT, 5000);
					break;
				case EVENT_SEPARATION_ANXIETY:
					if (!me->FindNearestCreature(NPC_SHANNOX, 80.0f) && !me->HasAura(SPELL_SEPARATION_ANXIETY))
						DoCast(me, SPELL_SEPARATION_ANXIETY, true);
					events.ScheduleEvent(EVENT_SEPARATION_ANXIETY, 2000);
					break;
				case EVENT_FACE_RAGE:
					if (instance)
						if (Creature* shannox = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_SHANNOX)))
							shannox->Yell("Go for the throat!", LANG_UNIVERSAL);
					DoCastVictim(SPELL_FACE_RAGE);
					events.ScheduleEvent(EVENT_FACE_RAGE, 27000);
					break;
				case EVENT_CHANGE_TARGET:
					if (instance && !(me->GetVictim() && me->GetVictim()->HasAura(SPELL_RAGE)) && !me->HasAura(SPELL_FACE_RAGE_DUMMY))
					{
						if (Creature* shannox = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_SHANNOX)))
						{
							if (Unit* rTarget = shannox->AI()->SelectTarget(SELECT_TARGET_RANDOM, 1, 0.0f, true))
							{
								me->AddThreat(rTarget, 10000000.0f);
								AttackStart(rTarget);
							}
						}
						else
						{
							if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 0.0f, true))
							{

								me->AddThreat(pTarget, 10000000.0f);
								AttackStart(pTarget);
							}
						}
					}
					events.ScheduleEvent(EVENT_CHANGE_TARGET, 7000);
					break;
				}
			}
			DoMeleeAttackIfReady();

		}
	private:
		EventMap events;
		InstanceScript* instance = me->GetInstanceScript();

	};


	CreatureAI* GetAI(Creature* creature) const override
	{
		return GetFirelandsAI<npc_ragefaceAI>(creature);
	}
};

class npc_shannox_spear : public CreatureScript
{
public:
	npc_shannox_spear() : CreatureScript("npc_shannox_spear") {}

	struct npc_shannox_spearAI : public CreatureAI
	{
		npc_shannox_spearAI(Creature* creature) : CreatureAI(creature) { }

	
		void Reset() override
		{
			DoCast(me, SPELL_SPEAR_TARGET, true);
		}	
		void InitializeAI() override
		{
			me->SetReactState(REACT_PASSIVE);
		}
		void SpellHit(Unit* caster, SpellInfo const* spell) override
		{

			if (spell->Id == SPELL_HURL_SPEAR_DMG)
			{

				std::list<Creature*> creatureList;
				me->GetCreatureListWithEntryInGrid(creatureList, NPC_DULL_EMBERSTONE_FOCUS, 50.0f);
				if (!creatureList.empty())
				{
					for (std::list<Creature*>::const_iterator itr = creatureList.begin(); itr != creatureList.end(); ++itr)
					{
						if (Creature* pFocus = (*itr)->ToCreature())
						{
							pFocus->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
							pFocus->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
							pFocus->CastSpell(pFocus, SPELL_TRANSFORM_CHARGED_EMBERSTONE_FOCUS, true);
						}
					}
				}

				me->RemoveAurasDueToSpell(SPELL_SPEAR_TARGET);
				DoCast(me, SPELL_MAGMA_FLARE, true);
				DoCast(me, SPELL_SPEAR_VISUAL, true);

				if (instance)
				{
					if (Creature* shannox = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_SHANNOX)))
					{
						// There will be a spiral, 3 "circles", 20 points per circle
						Position pos;
						for (uint8 i = 0; i < 60; ++i)
						{
							me->GetNearPosition(15.0f + i * 0.75f, (M_PI * i) / 10);
							pos.m_positionZ = me->GetMap()->GetHeight(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), true, MAX_HEIGHT);
							shannox->CastSpell(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), SPELL_MAGMA_RUPTURE_MISSILE, true);
						}
					}
				}

				if (Creature* riplimb = me->FindNearestCreature(NPC_RIPLIMB, 300.0f))
				{
					riplimb->AI()->DoAction(ACTION_HURL_SPEAR);
					riplimb->GetMotionMaster()->MovePoint(POINT_SPEAR_OF_SHANNOX, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
				}
			}
		}
	

		void UpdateAI(uint32 diff) override
		{

			if (!UpdateVictim())
				return;

			events.Update(diff);

			if (me->HasUnitState(UNIT_STATE_CASTING))
				return;
		}
	private:
		EventMap events;
		InstanceScript* instance = me->GetInstanceScript();

	};


	CreatureAI* GetAI(Creature* creature) const override
	{
		return GetFirelandsAI<npc_shannox_spearAI>(creature);
	}
};

class npc_shannox_immolation_trap : public CreatureScript
{
public:
	npc_shannox_immolation_trap() : CreatureScript("npc_shannox_immolation_trap") {}

	struct npc_shannox_immolation_trapAI : public CreatureAI
	{

		npc_shannox_immolation_trapAI(Creature* creature) : CreatureAI(creature) { }

		void InitializeAI() override
		{
			me->SetReactState(REACT_PASSIVE);
			bReady = false;
			bExplode = false;
			uiReadyTimer = 3000;
		}


		void UpdateAI(uint32 diff) override
		{
			if (!bReady)
			{
				if (uiReadyTimer <= diff)
					bReady = true;
				else
					uiReadyTimer -= diff;
			}
			else if (bReady && !bExplode)
			{
				if (Player* player = me->SelectNearestPlayer(0.1f))
				{
					bExplode = true;
					player->CastSpell(player, SPELL_IMMOLATION_TRAP_DMG, true);
					me->DespawnOrUnsummon(1000);
				}
				else if (Creature* pRiplimb = me->FindNearestCreature(NPC_RIPLIMB, 0.1f))
				{
					if (!pRiplimb->HasAura(SPELL_WARRY) &&
						!pRiplimb->HasAura(SPELL_WARRY_25) &&
						!pRiplimb->HasAura(SPELL_WARRY_10H) &&
						!pRiplimb->HasAura(SPELL_WARRY_25H))
					{
						bExplode = true;
						pRiplimb->CastSpell(pRiplimb, SPELL_IMMOLATION_TRAP_DMG, true);
						me->DespawnOrUnsummon(500);
					}
				}
				else if (Creature* pRageface = me->FindNearestCreature(NPC_RAGEFACE, 0.1f))
				{
					if (!pRageface->HasAura(SPELL_WARRY) &&
						!pRageface->HasAura(SPELL_WARRY_25) &&
						!pRageface->HasAura(SPELL_WARRY_10H) &&
						!pRageface->HasAura(SPELL_WARRY_25H))
					{
						bExplode = true;
						pRageface->CastSpell(pRageface, SPELL_IMMOLATION_TRAP_DMG, true);
						me->DespawnOrUnsummon(500);
					}
				}
			}
		}
	private:
		EventMap events;
		InstanceScript* instance = me->GetInstanceScript();
		bool bReady;
		bool bExplode;
		uint32 uiReadyTimer;

	};


	CreatureAI* GetAI(Creature* creature) const override
	{
		return GetFirelandsAI<npc_shannox_immolation_trapAI>(creature);
	}
};
class npc_shannox_crystal_prison_trap : public CreatureScript
{
public:
	npc_shannox_crystal_prison_trap() : CreatureScript("npc_shannox_crystal_prison_trap") {}

	struct npc_shannox_crystal_prison_trapAI : public CreatureAI
	{

		npc_shannox_crystal_prison_trapAI(Creature* creature) : CreatureAI(creature) { }

		void InitializeAI() override
		{
			me->SetReactState(REACT_PASSIVE);
			bReady = false;
			bExplode = false;
			uiReadyTimer = 3000;
		}


		void UpdateAI(uint32 diff) override
		{
			if (!bReady)
			{
				if (uiReadyTimer <= diff)
					bReady = true;
				else
					uiReadyTimer -= diff;
			}
			else if (bReady && !bExplode)
			{
				if (Player* pPlayer = me->SelectNearestPlayer(0.1f))
				{
					bExplode = true;
					pPlayer->CastSpell(pPlayer, SPELL_CRYSTAL_PRISON_TRAP, true);
					me->DespawnOrUnsummon(500);
				}
				else if (Creature* pRiplimb = me->FindNearestCreature(NPC_RIPLIMB, 0.1f))
				{
					if (!pRiplimb->HasAura(SPELL_WARRY) &&
						!pRiplimb->HasAura(SPELL_WARRY_25) &&
						!pRiplimb->HasAura(SPELL_WARRY_10H) &&
						!pRiplimb->HasAura(SPELL_WARRY_25H))
					{
						bExplode = true;
						pRiplimb->CastSpell(pRiplimb, SPELL_CRYSTAL_PRISON_TRAP, true);
						me->DespawnOrUnsummon(500);
					}
				}
				else if (Creature* pRageface = me->FindNearestCreature(NPC_RAGEFACE, 0.1f))
				{
					if (!pRageface->HasAura(SPELL_WARRY) &&
						!pRageface->HasAura(SPELL_WARRY_25) &&
						!pRageface->HasAura(SPELL_WARRY_10H) &&
						!pRageface->HasAura(SPELL_WARRY_25H))
					{
						bExplode = true;
						pRageface->CastSpell(pRageface, SPELL_CRYSTAL_PRISON_TRAP, true);
						me->DespawnOrUnsummon(500);
					}
				}
			
			}
		}
	private:
		EventMap events;
		InstanceScript* instance = me->GetInstanceScript();
		bool bReady;
		bool bExplode;
		uint32 uiReadyTimer;

	};


	CreatureAI* GetAI(Creature* creature) const override
	{
		return GetFirelandsAI<npc_shannox_crystal_prison_trapAI>(creature);
	}
};

class npc_shannox_crystal_prison : public CreatureScript
{
public:
	npc_shannox_crystal_prison() : CreatureScript("npc_shannox_crystal_prison") {}

	struct npc_shannox_crystal_prisonAI : public CreatureAI
	{

		npc_shannox_crystal_prisonAI(Creature* creature) : CreatureAI(creature) { }

		void InitializeAI() override
		{
			trappedUnit = 0;
			tDog = false;
		}

		void SetGUID(ObjectGuid guid, int32 data) override
		{
			trappedUnit = guid;
			existenceCheckTimer = 1000;

			if (data == DATA_TRAPPED_DOG)
			{
				tDog = true;
				dogTimer = 10000;
			}

		}  
		void JustDied(Unit* /*killer*/)
		{
			if (!tDog)
				DoCast(me, SPELL_CREATE_EMBERSTONE_FRAGMENT, true);
			tDog = false;
			if (Unit* unit = ObjectAccessor::GetUnit(*me, instance->GetGuidData(trappedUnit)))
			{
				trappedUnit = 0;
				unit->RemoveAurasDueToSpell(SPELL_CRYSTAL_PRISON_TRAP);
			}
			me->DespawnOrUnsummon(800);
		}

		void UpdateAI(uint32 diff) override
		{
			if (!trappedUnit)
				return;

			if (existenceCheckTimer <= diff)
			{
				Unit* unit = ObjectAccessor::GetUnit(*me, instance->GetGuidData(trappedUnit));
				if (!unit || unit->isDead() || !unit->HasAura(SPELL_CRYSTAL_PRISON_TRAP))
				{
					JustDied(me);
					return;
				}
			}
			else
				existenceCheckTimer -= diff;

			if (tDog)
			{
				if (dogTimer <= diff)
					JustDied(me);
				else
					dogTimer -= diff;
			}
		}
	private:

		InstanceScript* instance = me->GetInstanceScript();
		uint64 trappedUnit;
		uint32 existenceCheckTimer;
		bool tDog;
		uint32 dogTimer;

	};


	CreatureAI* GetAI(Creature* creature) const override
	{
		return GetFirelandsAI<npc_shannox_crystal_prisonAI>(creature);
	}
};


typedef boss_shannox::boss_shannoxAI ShannoxAI;
class achievement_bucket_list : public AchievementCriteriaScript
{
public:
	achievement_bucket_list() : AchievementCriteriaScript("achievement_bucket_list") { }

	bool OnCheck(Player* source, Unit* target)
	{
		if (!target)
			return false;

		if (ShannoxAI* shannoxAI = CAST_AI(ShannoxAI, target->GetAI()))
			return shannoxAI->AllowAchieve();

		return false;
	}
};

void AddSC_boss_shannox()
{
	new achievement_bucket_list();
	new boss_shannox();
	new npc_riplimb();
	new npc_rageface();
	new npc_shannox_crystal_prison();
	new npc_shannox_crystal_prison_trap();
	new npc_shannox_immolation_trap();
	new npc_shannox_spear();
};
