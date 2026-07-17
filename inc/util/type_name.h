#pragma once
#include "util/macro.h"
#include <string_view>


#if defined(__clang__)
	#define PF_CMD __PRETTY_FUNCTION__
	#define PF_PREFIX "std::basic_string_view<char> ::type_name() [T = "
	#define PF_SUFFIX "]"
#elif defined(__GNUC__) && !defined(__clang__)
	#define PF_CMD __PRETTY_FUNCTION__
	#define PF_PREFIX "constexpr std::basic_string_view<char> ::type_name() [with T = "
	#define PF_SUFFIX "]"
#elif defined(_MSC_VER)
	#define PF_CMD __FUNCSIG__
	#define PF_PREFIX "struct std::basic_string_view<char> __cdecl ::type_name<"
	#define PF_SUFFIX ">(void)"
#else
	#error "No support for this compiler."
#endif

#define STRINGIFY_IMPL(X) #X
#define STRINGIFY(X) STRINGIFY_IMPL(X)

namespace TUPLE_UTIL_NAMESPACE { // NOTE: when changing the namespace of this func you must update the macros for pretty function
	template<typename T> constexpr std::basic_string_view<char> type_name() {
		std::size_t prefix_length = sizeof(STRINGIFY(TUPLE_UTIL_NAMESPACE)) - 1 + sizeof(PF_PREFIX) - 1;
		std::size_t suffix_length = sizeof(PF_SUFFIX) - 1;

		return { PF_CMD + prefix_length, sizeof(PF_CMD) - prefix_length - suffix_length - 1 };
	}
	template<typename T> struct get_type_name { static constexpr std::basic_string_view<char> value = type_name<T>(); };
}
#undef PF_CMD
#undef PF_PREFIX
#undef PF_SUFFIX
#undef STRINGIFY
#undef STRINGIFY_IMPL