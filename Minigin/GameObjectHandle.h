#ifndef GAMEOBJECTHANDLE_H
#define GAMEOBJECTHANDLE_H

namespace dae
{
	class GameObject;

	class GameObjectHandle final
	{
	public:
		GameObjectHandle(GameObject* pGameObject = nullptr);

		~GameObjectHandle();
		GameObjectHandle(const GameObjectHandle& other);
		GameObjectHandle(GameObjectHandle&& other) noexcept;
		GameObjectHandle& operator=(const GameObjectHandle& other);
		GameObjectHandle& operator=(GameObjectHandle&& other) noexcept;

		GameObject* Get() const;
		GameObject* operator->() const;
		operator bool() const noexcept;

	private:

		friend class GameObject;
		void Invalidate();

		GameObject* m_pGameObject;
	};
}

#endif // !GAMEOBJECTHANDLE_H