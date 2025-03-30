#ifndef OBSERVER_H
#define OBSERVER_H

#include "Event.h"

class Component;

class IObserver	//only works with component
{
public:
	virtual ~IObserver() = default;
	virtual void Notify(Event event, Component* comp) = 0;
};

#endif // !OBSERVER_H