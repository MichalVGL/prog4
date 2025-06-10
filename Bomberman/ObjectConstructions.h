#ifndef OBJECTCONSTRUCTION_H
#define OBJECTCONSTUCTION_H

#include <Scene.h>

namespace bm
{
	std::unique_ptr<dae::GameObject> GOBJ(const dae::GobjID& name, dae::render_layer rLayer = 0);
	std::unique_ptr<dae::GameObject> RenderGOBJ(const dae::GobjID& name, dae::render_layer rLayer = 0);
	std::unique_ptr<dae::GameObject> SpriteGOBJ(const dae::GobjID& name, dae::render_layer rLayer = 0);
	std::unique_ptr<dae::GameObject> TextGOBJ(const dae::GobjID& name, dae::render_layer rLayer = 0);

	//Helpers
	//void AddPlayerSimpleCollision(dae::GameObject& go, float radius);	//adds collision detection to the gameobject detecting the player
}

#endif // !OBJECTCONSTRUCTION_H

