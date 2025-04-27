#ifndef EVENT_H
#define EVENT_H

namespace dae
{
	using EventId = unsigned int;

	struct Event {
		const EventId id;

		explicit Event(EventId _id) : id{ _id } {}\
	};
}

#endif // !EVENT_H