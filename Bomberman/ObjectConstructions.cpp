#include "ObjectConstructions.h"

#include <EngineComponents.h>

#include "BMComponents.h"

//void bm::MakeLevel(dae::Scene& scene)
//{
//	auto pGo = scene.Add(std::move(RenderGOBJ("Level")));
//	pGo->AddComponent<LevelComp>();
//}

//=====================HELPERS======================================================

std::unique_ptr<dae::GameObject> bm::GOBJ(const dae::GobjID& name)
{
	return std::make_unique<dae::GameObject>(name);
}

std::unique_ptr<dae::GameObject> bm::RenderGOBJ(const dae::GobjID& name)
{
	auto go = GOBJ(name);
	go->AddComponent<dae::RenderComp>();
	return go;
}

std::unique_ptr<dae::GameObject> bm::SpriteGOBJ(const dae::GobjID& name)
{
	auto go = RenderGOBJ(name);
	go->AddComponent<dae::SpriteComp>();
	return go;
}