#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <any>

#include "Event.h"

namespace dae
{
	class Component;

	class IObserver
	{
	public:
		virtual ~IObserver() = default;
		virtual void Notify(Event event, const std::any& data) = 0;
	};
}

#endif // !IOBSERVER_H