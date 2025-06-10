#include "ObjectConstructions.h"

#include <EngineComponents.h>

#include "BMComponents.h"

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

std::unique_ptr<dae::GameObject> bm::TextGOBJ(const dae::GobjID& name, dae::render_layer rLayer)
{
	auto go = RenderGOBJ(name, rLayer);
	go->AddComponent<dae::TextComp>();
	return go;
}

//=====================HELPERS======================================================

