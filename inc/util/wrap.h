#pragma once
#include "util/macro.h"
#include <type_traits>

namespace util {
	template<typename T, CONTAINER Tup>
	struct rewrap;

	template<CONTAINER Tup>
	struct rewrap_ { template<typename T> using type = rewrap<T, Tup>; };

	template<typename T, CONTAINER Tup> using rewrap_t = typename rewrap<T, Tup>::type;

	template<CONTAINER Tup1, typename ... Ts, CONTAINER Tup2>
	struct rewrap<Tup1<Ts...>, Tup2> { using type = Tup2<Ts...>; };

	template<typename T, CONTAINER Tup>
	struct wrap { using type = Tup<T>; };

	template<CONTAINER Tup>
	struct wrap_ { template<typename T> using type = wrap<T, Tup>; };

	template<typename T, CONTAINER ... Tups>
	using wrap_t = typename wrap<T, Tups...>::type;


	template<typename T>
	struct unwrap;

	template<CONTAINER Tup, typename T>
	struct unwrap<Tup<T>> : std::type_identity<T> { };

	template<typename T>
	using unwrap_t = typename unwrap<T>::type;
}

namespace util::pred {
	template<typename T, CONTAINER Tup>
	struct is_wrapped_by : std::false_type { };

	template<typename ... Ts, CONTAINER Tup>
	struct is_wrapped_by<Tup<Ts...>, Tup> : std::true_type { };

	template<CONTAINER Tup>
	struct is_wrapped_by_ { template<typename T> using type = is_wrapped_by<T, Tup>; };

	template<typename T, CONTAINER Tup>
	static constexpr bool is_wrapped_by_v = is_wrapped_by<T, Tup>::value;



	template <typename T>
	struct is_wrapped : std::false_type { };

	template<template<typename...> typename Tp, typename ... Ts> 
	struct is_wrapped<Tp<Ts...>> : std::true_type { };

	template <typename T>
	static constexpr bool is_wrapped_v = is_wrapped<T>::value;
}