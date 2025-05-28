#ifndef FONTDEFINES_H
#define FONTDEFINES_H

#include <functional>

namespace dae
{
	using font_id = unsigned int;
	using font_size = unsigned int;

	struct FontFullID	//required because fonts are loaded with a path and size (unlike textures or sounds)
	{
		font_id id;
		font_size size;

		bool operator==(const FontFullID& other) const
		{
			return id == other.id && size == other.size;
		}
	};
}

//so it can be used in std::unordered_map as a key (in fontsystem)
namespace std {
	template<>
	struct hash<dae::FontFullID>
	{
		std::size_t operator()(const dae::FontFullID& k) const noexcept
		{
			std::size_t h1 = std::hash<dae::font_id>{}(k.id);
			std::size_t h2 = std::hash<dae::font_size>{}(k.size);
			return h1 ^ (h2 << 1); 
		}
	};
}

#endif // !FONTDEFINES_H