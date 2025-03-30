#include <cassert>
#include <algorithm>

#include "Subject.h"
#include "Observer.h"

Subject::Subject(Component* parentComponent)
	: m_pParentComponent{parentComponent}
	, m_Observers{}
{
}

void Subject::AddObserver(IObserver* observer)
{
	assert(observer != nullptr && "Attempted to add nullptr to observers (In Subject class)");

	m_Observers.emplace_back(observer);
}

void Subject::RemoveObserver(IObserver* observer)
{
	assert(observer != nullptr && "Attempted to remove nullptr from observers (In Subject class)");

	std::erase(m_Observers, observer);
}

void Subject::NotifyObservers(Event event)
{
	for (auto observer : m_Observers)
		observer->Notify(event, m_pParentComponent);
}
