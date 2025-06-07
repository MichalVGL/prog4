#ifndef UPGRADESYSTEM_H
#define UPGRADESYSTEM_H

#include "IUpgradeSystem.h"

namespace bm
{
	class UpgradeSystem final : public IUpgradeSystem
	{
	public:

		void AddUpgrade(UpgradeType type) override;
		void ResetUpgrades() override;

		int GetMaxBombs() const override;
		int GetBombRange() const override;
		bool IsRemoteActive() const override;

	private:

		int m_MaxBombs{ 1 };
		int m_BombRange{ 1 };
		bool m_RemoteActive{ false };
	};
}
#endif // !UPGRADESYSTEM_H
