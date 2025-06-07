#include "ObjectConstructions.h"

#include <EngineComponents.h>

#include "BMComponents.h"

//void bm::MakeLevel(dae::Scene& scene)
//{
//	auto pGo = scene.Add(std::move(RenderGOBJ("Level")));
//	pGo->AddComponent<LevelComp>();
//}

//=====================HELPERS======================================================

std::unique_ptr<dae::GameObject> bm::GOBJ(const dae::GobjID& name, dae::render_layer rLayer)
{
	return std::make_unique<dae::GameObject>(name, rLayer);
}

std::unique_ptr<dae::GameObject> bm::RenderGOBJ(const dae::GobjID& name, dae::render_layer rLayer)
{
	auto go = GOBJ(name, rLayer);
	go->AddComponent<dae::RenderComp>();
	return go;
}

std::unique_ptr<dae::GameObject> bm::SpriteGOBJ(const dae::GobjID& name, dae::render_layer rLayer)
{
	auto go = RenderGOBJ(name, rLayer);
	go->AddComponent<dae::SpriteComp>();
	return go;
}