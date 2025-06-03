#ifndef EVENT_H
#define EVENT_H

#include "sdbmHash.h"

namespace dae
{
	using event_id = unsigned int;

	struct Event {
		const event_id id;

		template <size_t N>
		constexpr explicit Event(const char(&path)[N])
			: id{ make_sdbm_hash(path) }
		{
		}
	};
}

#endif // !EVENT_H