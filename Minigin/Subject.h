#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "Event.h"

class Observer;
class Component;

class Subject	//only works with components
{
public:
	Subject(Component* parentComponent);

	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);

	void NotifyObservers(Event event);

private:
	Component* m_pParentComponent;

	std::vector<Observer*> m_Observers;
};

#endif // !SUBJECT_H