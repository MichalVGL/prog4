#ifndef RESOURCEENRTY_H
#define RESOURCEENRTY_H

#include <string_view>

#include "sdbmHash.h"
//todo determine wether to use this or just soundentry
namespace dae
{
	template<typename idType>
	struct ResourceEntry
	{
		std::string_view path;
		idType id;

		template <size_t N>
		constexpr ResourceEntry(const char(&path)[N])
			:path{ path }
			, id{ make_sdbm_hash(path) }
		{
		}
	};
}
#endif // !RESOURCEENRTY_H