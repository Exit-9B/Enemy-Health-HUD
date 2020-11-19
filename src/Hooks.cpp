#include "Hooks.h"
#include "EnemyHealthManager.h"

namespace Hooks
{
	void Install()
	{
		EnemyHealthManager::InstallHooks();
		logger::info("Installed all hooks");
	}
}