#include "EnemyHealthManager.h"
#include "Offsets.h"

void EnemyHealthManager::InstallHooks()
{
	static REL::Relocation<std::uintptr_t> hook{ Offset::EnemyHealth_Update, 0xE1 };

	auto& trampoline = SKSE::GetTrampoline();
	_GetActorValuePercent = trampoline.write_call<5>(hook.address(), GetEnemyHealthPercent);
}

float EnemyHealthManager::GetEnemyHealthPercent(RE::Character* a_enemy, RE::ActorValue a_actorValue)
{
	auto healthPercent = _GetActorValuePercent(a_enemy, a_actorValue);

	if (a_actorValue != RE::ActorValue::kHealth)
	{
		logger::critical("Expected health query but got AV {} instead", a_actorValue);
		return healthPercent;
	}

	auto baseHealth = a_enemy->GetPermanentActorValue(RE::ActorValue::kHealth);
	auto healthMod = a_enemy->healthModifiers.modifiers[RE::ACTOR_VALUE_MODIFIERS::kTemporary];
	auto currentHealth = a_enemy->GetActorValue(RE::ActorValue::kHealth);

	return currentHealth / (baseHealth + healthMod);
}