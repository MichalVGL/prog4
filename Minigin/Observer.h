#ifndef OBSERVER_H
#define OBSERVER_H

#include "Event.h"

class Component;

class Observer	//only works with component
{
public:
	virtual ~Observer() = default;
	virtual void Notify(Event event, Component* comp) = 0;
};

#endif // !OBSERVER_H