#ifndef RENDERSTRUCTS_H  
#define RENDERSTRUCTS_H  

#include <cstdint>
#include <string>

#include "TextureDefines.h"

namespace dae
{
	enum class HorizontalAlignment
	{
		left,
		center,
		right
	};

	enum class VerticalAlignment
	{
		top,
		center,
		bottom
	};

	struct Flip
	{
		bool horizontal{ false };
		bool vertical{ false };
	};

	struct Window
	{
		std::string title;
		int w;
		int h;
		float renderScale;   //affects total width and height of the window
	};

	struct Color
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};
}

#endif
