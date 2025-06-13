#ifndef ISELECTABLEUI_H
#define ISELECTABLEUI_H

#include <Component.h>
#include <EngineComponents.h>
#include <glm.hpp>

namespace bm
{
	class UIComp : public dae::Component
	{
	public:

		UIComp(dae::GameObject& parent);

		virtual ~UIComp() = default;

		virtual void PrimaryInteract() {};
		virtual void SecondaryInteract() {};

		void Select();
		void UnSelect();

		glm::vec2 GetTextureSize() const;

	protected:

		dae::ReqComp<dae::RenderComp> m_RenderComp{};	//required render component for UI
		dae::ReqComp<dae::TextComp> m_TextComp{};		//required text component for UI

	private:

		static constexpr dae::Color s_SelectedColor{ .r = 0, .g = 255, .b = 0, .a = 255 };		//green
		static constexpr dae::Color s_NormalColor{ .r = 255, .g = 255, .b = 255, .a = 255 };	//white

	};
}
#endif // !ISELECTABLEUI_H
