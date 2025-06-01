#ifndef IOBSERVER_H
#define IOBSERVER_H

#include "Event.h"

namespace dae
{
	class Component;

	//todo: make it a template
	class IObserver	//only works with component;
	{
	public:
		virtual ~IObserver() = default;
		virtual void Notify(Event event) = 0;
	};
}

#endif // !IOBSERVER_H