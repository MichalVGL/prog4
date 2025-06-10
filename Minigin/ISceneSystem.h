#ifndef ISCENESYSTEM_H
#define ISCENESYSTEM_H

#include "Scene.h"

namespace dae
{
	class ISceneSystem
	{
	public:
		virtual ~ISceneSystem() = default;

		virtual Scene* GetCurrentScene() const = 0;

		virtual void LoadScene() = 0;	//only called once when run() is called in minigin.cpp (to make sure the load() function has access to a fully loaded engine), new scenes after the first one will automatically call this

		virtual void Start() = 0;
		virtual void FixedUpdate(float deltaFixedTime) = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void LateUpdate(float deltaTime) = 0;
		virtual void Render() const = 0;

		virtual void UpdateImGui() = 0;
	};
}

#endif // !ISCENESYSTEM_H

