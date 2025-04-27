#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "Event.h"

namespace dae
{
	class IObserver;
	class Component;

	class Subject final		//only works with components
	{
	public:
		Subject(Component* parentComponent);

		void AddObserver(IObserver* observer);
		void RemoveObserver(IObserver* observer);

		void NotifyObservers(Event event);

	private:
		Component* m_pParentComponent;

		std::vector<IObserver*> m_Observers;
	};
}

#endif // !SUBJECT_H