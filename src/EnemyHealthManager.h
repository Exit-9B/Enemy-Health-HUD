#pragma once

class EnemyHealthManager
{
public:
	static void InstallHooks();

private:
	EnemyHealthManager() = default;

	static float GetEnemyHealthPercent(RE::Character* a_enemy);
};
