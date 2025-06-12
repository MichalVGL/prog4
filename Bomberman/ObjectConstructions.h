#ifndef OBJECTCONSTRUCTION_H
#define OBJECTCONSTUCTION_H

#include <Scene.h>

namespace bm
{
	std::unique_ptr<dae::GameObject> GOBJ(const dae::GobjID& name, dae::render_layer rLayer = 0);
	std::unique_ptr<dae::GameObject> RenderGOBJ(const dae::GobjID& name, dae::render_layer rLayer = 0);
	std::unique_ptr<dae::GameObject> SpriteGOBJ(const dae::GobjID& name, dae::render_layer rLayer = 0);
	std::unique_ptr<dae::GameObject> TextGOBJ(const dae::GobjID& name, dae::render_layer rLayer = 0);
}

#endif // !OBJECTCONSTRUCTION_H

