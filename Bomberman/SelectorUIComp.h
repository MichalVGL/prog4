#ifndef SELECTORUICOMP_H
#define SELECTORUICOMP_H

#include <vector>
#include <tuple>

#include "UIComp.h"

namespace bm
{
	template<typename T>
	class SelectorUIComp final : public bm::UIComp	//Args:  std::vector<std::pair<T, std::string>>&& elements
	{
	public:
		SelectorUIComp(dae::GameObject& parent, std::vector<std::pair<T, std::string>>&& elements)
			:UIComp(parent)
			, m_Elements(std::move(elements))
		{
			UpdateText();
		}

		SelectorUIComp(const SelectorUIComp& other) = default;
		SelectorUIComp(SelectorUIComp&& other) noexcept = default;
		SelectorUIComp& operator=(const SelectorUIComp& other) = default;
		SelectorUIComp& operator=(SelectorUIComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		//void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		//void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//void OnDestroy() override;
		//--------------------------

		void PrimaryInteract() override
		{
			m_SelectedIndex++;
			if (m_SelectedIndex >= static_cast<int>(m_Elements.size()))
			{
				m_SelectedIndex = 0;	//loop back to the first element
			}
			UpdateText();
		}

		void SecondaryInteract() override
		{
			m_SelectedIndex--;
			if (m_SelectedIndex < 0)
			{
				m_SelectedIndex = static_cast<int>(m_Elements.size()) - 1;	//loop back to the last element
			}
			UpdateText();
		}

		void UpdateText()
		{
			m_TextComp->SetText(m_Elements.at(m_SelectedIndex).second);
		}

		const T& GetSelectedElement() const
		{
			return m_Elements.at(m_SelectedIndex).first;
		}

	private:


		int m_SelectedIndex{ 0 };	//index of the currently selected element
		std::vector<std::pair<T, std::string>> m_Elements;	//elements to select

	};
}
#endif // !SELECTORUICOMP_H