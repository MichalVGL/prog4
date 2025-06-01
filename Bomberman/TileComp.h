#ifndef TILECOMP_H
#define TILECOMP_H

#include "Component.h"

#include <glm.hpp>
#include <Texture.h>
#include <EngineComponents.h>

namespace bm
{

	enum class TileType
	{
		Ground,
		Wall
	};

	class TileComp final : public dae::Component	//Args: TileType type, ivec2 indexPos
	{
	public:
		TileComp(dae::GameObject& parent, TileType type, glm::ivec2 indexPos);

		~TileComp() = default;
		TileComp(const TileComp& other) = default;
		TileComp(TileComp&& other) noexcept = default;
		TileComp& operator=(const TileComp& other) = default;
		TileComp& operator=(TileComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		//void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		//void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//--------------------------

		glm::vec2 GetPosition();
		glm::ivec2 GetIndexPosition();

	private:


		//========================================================================

		static constexpr dae::TextureEntry s_GroundTexture{"EmptyTile.png"};
		static constexpr dae::TextureEntry s_WallTexture{"IndestructableWall.png"};

		dae::ReqComp<dae::TransformComp> m_TransformComp;
		dae::ReqComp<dae::RenderComp> m_RenderComp;

		const glm::ivec2 m_IndexPos;
		const glm::vec2 m_Pos{};

		TileComp* m_pUpTile{};
		TileComp* m_pRightTile{};
		TileComp* m_pDownTile{};
		TileComp* m_pLeftTile{};

	};
}
#endif // !TILECOMP_H