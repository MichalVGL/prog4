#ifndef DOORCOMP_H
#define DOORCOMP_H

#include "Component.h"

#include <Subject.h>
#include <IObserver.h>
#include <Sound.h>
#include <EngineComponents.h>

#include "TileCollisionComp.h"
#include "TileMod.h"


namespace bm
{
	class DoorComp final : public dae::Component, public TileMod, public dae::IObserver	//Args: 
	{
	public:
		DoorComp(dae::GameObject& parent);

		DoorComp(const DoorComp& other) = default;
		DoorComp(DoorComp&& other) noexcept = default;
		DoorComp& operator=(const DoorComp& other) = default;
		DoorComp& operator=(DoorComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//void OnDestroy() override;
		//--------------------------

		// Inherited via TileMod
		bool IsWalkable() const override;
		// Inherited via IObserver
		void Notify(dae::Event event, const std::any& data) override;

		dae::Subject& OnPlayerEscaped();

		static constexpr dae::Event s_PlayerEscaped = dae::Event("PlayerEscaped");

	private:

		static constexpr dae::SoundEntry s_DoorOpenSoundEntry{ "Sounds/DoorOpen.wav" };
		static constexpr dae::TextureEntry s_DoorTextureEntry{ "Textures/Door.png" };

		dae::ReqComp<bm::TileCollisionComp> m_TileCollisionComp{};
		dae::ReqComp<dae::RenderComp> m_RenderComp{};

		std::vector<dae::GameObjectHandle> m_Enemies{};
		bool m_DoorOpen{ false };
		dae::Subject m_PlayerEscapedSubject{s_PlayerEscaped};

		dae::SoundToken m_DoorOpenSoundToken{ s_DoorOpenSoundEntry };
	};
}
#endif // !COMP_H