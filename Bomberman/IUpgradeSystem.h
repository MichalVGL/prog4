#ifndef IUPGRADESYSTEM
#define IUPGRADESYSTEM

#include "UpgradeComp.h"

namespace bm
{
	//Interface for the UpgradeSystem, which handles upgrades for the player
	class IUpgradeSystem
	{
	public:
		virtual ~IUpgradeSystem() = default;
		virtual void AddUpgrade(UpgradeType type) = 0;	//add an upgrade to the player
		virtual void ResetUpgrades() = 0;	//reset all upgrades for the player

		virtual int GetMaxBombs() const = 0;
		virtual int GetBombRange() const = 0;
		virtual bool IsRemoteActive() const = 0;
	};
}
#endif // !IUPGRADESYSTEM