#ifndef IEVENTSYSTEM
#define IEVENTSYSTEM

namespace bm
{
	class IEventSystem
	{
	public:
		virtual ~IEventSystem() = default;
		//virtual void RegisterListener(const std::string& eventName, std::function<void()> listener) = 0;
		//virtual void UnregisterListener(const std::string& eventName, std::function<void()> listener) = 0;
		//virtual void Notify(const std::string& eventName) = 0;
	};
}
#endif // !IEVENTSYSTEM