#ifndef OBJECTCONSTRUCTION_H
#define OBJECTCONSTUCTION_H

#include <Scene.h>

namespace bm
{
	//Full gameobject functions
	void MakeLevel(dae::Scene& scene);

	//Helpers
	std::unique_ptr<dae::GameObject> GOBJ(const dae::GobjID& name);
	std::unique_ptr<dae::GameObject> RenderGOBJ(const dae::GobjID& name);
	std::unique_ptr<dae::GameObject> SpriteGOBJ(const dae::GobjID& name);
}

#endif // !OBJECTCONSTRUCTION_H

