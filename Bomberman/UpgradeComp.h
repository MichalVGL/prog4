#ifndef UPGRADECOMP_H
#define UPGRADECOMP_H

#include "Component.h"

#include <IObserver.h>
#include <EngineComponents.h>
#include <Texture.h>

#include "TileMod.h"
#include "TileCollisionComp.h"

namespace bm
{
	enum class UpgradeType
	{
		remoteDetonator,
		bombCount,
		bombRange,
	};

	class UpgradeComp final : public dae::Component, public TileMod, public dae::IObserver	//Args: UpgradeType type
	{
	public:
		UpgradeComp(dae::GameObject& parent, UpgradeType type);

		UpgradeComp(const UpgradeComp& other) = default;
		UpgradeComp(UpgradeComp&& other) noexcept = default;
		UpgradeComp& operator=(const UpgradeComp& other) = default;
		UpgradeComp& operator=(UpgradeComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		//void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		//void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		void OnDestroy() override;
		//--------------------------

		// Inherited via TileMod
		bool IsWalkable() const override;

		// Inherited via IObserver
		void Notify(dae::Event event, const std::any& data) override;

		static constexpr dae::TextureEntry s_FireUpTextureEntry{ "Textures/FireUp.png" };
		static constexpr dae::TextureEntry s_PowerUpTextureEntry{ "Textures/PowerUp.png" };
		static constexpr dae::TextureEntry s_RemoteControlTextureEntry{ "Textures/RemoteControl.png" };

	private:

		dae::ReqComp<bm::TileCollisionComp> m_TileCollisionComp{};
		dae::ReqComp<dae::RenderComp> m_RenderComp{};
		dae::RenderKey m_RenderKey{};

		UpgradeType m_Type;

	};
}
#endif // !UPGRADECOMP_H