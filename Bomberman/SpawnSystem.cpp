#include "SpawnSystem.h"

#include <Scene.h>
#include <SceneManager.h>

#include "BMGameDefines.h"
#include "ObjectConstructions.h"
#include "FireComp.h"

void bm::SpawnSystem::SpawnLevelStructures(int walls, dae::Scene& scene)
{
	//todo implement
	walls;
	scene;
}

void bm::SpawnSystem::SpawnFire(glm::vec2 pos, std::vector<dae::GameObjectHandle> targets, Direction direction, int spreadAmount)
{
	auto* scene = dae::SceneManager::GetInstance().GetCurrentScene();
	if (!scene)
		return;

	auto go = bm::SpriteGOBJ(FIRE_GOBJID);
	auto* transform = go->GetComponent<dae::TransformComp>();
	transform->SetLocalPosition(pos);
	//todo, add collision comp
	go->AddComponent<bm::FireComp>(targets, direction, spreadAmount);

	scene->Add(std::move(go));
}
