#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <any>

#include "Event.h"

namespace dae
{
	class IObserver;
	class Component;

	class Subject final	
	{
	public:
		Subject(Event event);

		void AddObserver(IObserver* observer);
		void RemoveObserver(IObserver* observer);

		void NotifyObservers(const std::any& data = std::any{});

	private:
		//Component* m_pParentComponent;

		Event m_Event;

		std::vector<IObserver*> m_Observers;
	};
}

#endif // !SUBJECT_H