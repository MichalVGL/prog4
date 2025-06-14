#ifndef BOMBERMANCOMP_H
#define BOMBERMANCOMP_H

#include "Component.h"

#include <Sound.h>

#include "EntityComp.h"

namespace bm
{
	class BombermanComp final : public dae::Component	//Args: 
	{
	public:
		BombermanComp(dae::GameObject& parent);

		BombermanComp(const BombermanComp& other) = default;
		BombermanComp(BombermanComp&& other) noexcept = default;
		BombermanComp& operator=(const BombermanComp& other) = default;
		BombermanComp& operator=(BombermanComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		//void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//void OnDestroy() override;
		//--------------------------

	private:

		static constexpr dae::SoundEntry s_WalkSoundEntry{ "Sounds/Walk.wav" };

		dae::ReqComp<bm::EntityComp> m_EntityComp{};

		dae::SoundToken m_WalkSoundToken{ s_WalkSoundEntry };
	};
}
#endif // !BOMBERMANCOMP_H