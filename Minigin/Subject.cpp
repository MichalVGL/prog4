#include <cassert>
#include <algorithm>
#include <iostream>

#include "Subject.h"
#include "IObserver.h"

using namespace dae;

Subject::Subject(Event event)
	: m_Event{ event }
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

void Subject::NotifyObservers()
{
	for (auto observer : m_Observers)
		observer->Notify(m_Event);
}
