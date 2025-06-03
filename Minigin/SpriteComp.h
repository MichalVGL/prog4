#ifndef SPRITECOMP_H
#define SPRITECOMP_H

#include <string_view>
#include <vector>

#include "Component.h"
#include "Texture.h"
#include "RenderComp.h"
#include "sdbmHash.h"

namespace dae
{
	using sprite_id = unsigned int;

	template <size_t N>
	constexpr sprite_id SpriteId(const char(&spriteName)[N]) {
		return make_sdbm_hash(spriteName);
	}

	struct SpriteEntry final
	{
		template <size_t N>
		constexpr SpriteEntry(const char(&spriteName)[N], const Rect& srcRect, int cols, int rows, bool loop = true)
			//: name{spriteName}
			: id{make_sdbm_hash(spriteName)}
			, srcRect{srcRect}
			, cols{cols}
			, rows{rows}
			, loop{loop}
		{
		}

		//const std::string_view name;
		sprite_id id;

		Rect srcRect;
		int cols;
		int rows;
		bool loop;
	};

	//=================================================================================================================

	class SpriteComp final : public dae::Component	//Args: 
	{
	public:
		SpriteComp(dae::GameObject& parent);

		SpriteComp(const SpriteComp& other) = default;
		SpriteComp(SpriteComp&& other) noexcept = default;
		SpriteComp& operator=(const SpriteComp& other) = default;
		SpriteComp& operator=(SpriteComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// ------------------------- 
		//void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//--------------------------

		void LoadTexture(const dae::TextureEntry& entry, bool keepExistingSpriteEntries = false);

		void AddSpriteEntry(SpriteEntry entry);
		void DeleteSpriteEntry(sprite_id id);
		void SetSpriteEntry(sprite_id id);	//use SpriteId() to get the entry based on the name
		const SpriteEntry* GetSpriteEntry(sprite_id id) const;	//use SpriteId() to get the entry based on the name

		void SetFPS(float fps);
		void Pause();
		void Resume();
		void SetFrame(int frame);
		void FlipHorizontal(bool flip);
		void FlipVertical(bool flip);

		bool IsLoopComplete() const;

	private:

		void ValidateEntry(SpriteEntry& entry);	//Any abnormalities will be printed in console and set to a default value.
		void ResetLooping();
		void SetCurrentFrame();

		ReqComp<RenderComp> m_RenderComp{};
		RenderKey m_RenderKey{};

		std::vector<SpriteEntry> m_Entries{};
		SpriteEntry* m_pActiveEntry{};

		float m_Timer{};
		float m_SecondsPerFrame{0.1f};
		int m_FrameIndex{};
		bool m_LoopComplete{ false };	//only used when the spriteEntry has no looping
		bool m_Paused{ false };

		//prevent any setentry() before start() is called to crash the game due to render* not being set (which happens in start)  
		//bool m_FlagSpriteEntryChanged{false};
		//bool m_FlagTextureEntryChanged{false};
	};
}
#endif // !COMP_H