#ifndef LEVELCOMP_H
#define LEVELCOMP_H

#include "Component.h"

#include <array>

#include "BMGameDefines.h"

namespace bm
{
	class TileComp;

	class LevelComp final : public dae::Component	//Args: 
	{
	public:
		LevelComp(dae::GameObject& parent);

		
		LevelComp(const LevelComp& other) = default;
		LevelComp(LevelComp&& other) noexcept = default;
		LevelComp& operator=(const LevelComp& other) = default;
		LevelComp& operator=(LevelComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		//void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		//void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//--------------------------



	private:

		std::array<TileComp*, LEVELTILES_TOTAL> m_Tiles{};


	};
}
#endif // !LEVELCOMP_H