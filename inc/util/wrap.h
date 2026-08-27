#pragma once
#include "util/macro.h"
#include <type_traits>
#include <utility>

namespace TUPLE_UTIL_NAMESPACE {
	template<typename T, TUPLE_UTIL_CONTAINER Tup>
	struct rewrap;

	template<TUPLE_UTIL_CONTAINER Tup>
	struct rewrap_ { template<typename T> using type = rewrap<T, Tup>; };

	template<typename T, TUPLE_UTIL_CONTAINER Tup> using rewrap_t = typename rewrap<T, Tup>::type;

	template<TUPLE_UTIL_CONTAINER Tup1, typename ... Ts, TUPLE_UTIL_CONTAINER Tup2>
	struct rewrap<Tup1<Ts...>, Tup2> { using type = Tup2<Ts...>; };

	namespace details {
		template<std::size_t N, typename T>
		struct identity_at { using type = T; };
		
		template<typename T, TUPLE_UTIL_CONTAINER Tup, typename Ind>
		struct wrap;

		template<typename T, TUPLE_UTIL_CONTAINER Tup, std::size_t ... Is>
		struct wrap<T, Tup, std::index_sequence<Is...>> {
			using type = Tup<typename identity_at<Is, T>::type...>;
		};
	}

	template<typename T, TUPLE_UTIL_CONTAINER Tup=TUPLE_UTIL_DEFAULT_CONTAINER, std::size_t N=1>
	struct wrap : details::wrap<T, Tup, std::make_index_sequence<N>> { };

	template<typename T, TUPLE_UTIL_CONTAINER Tup>
	struct wrap<T, Tup, 1> { using type = Tup<T>; };

	template<TUPLE_UTIL_CONTAINER Tup=TUPLE_UTIL_DEFAULT_CONTAINER, std::size_t N=1>
	struct wrap_ { template<typename T> using type = wrap<T, Tup, N>; };

	template<typename T, TUPLE_UTIL_CONTAINER Tup=TUPLE_UTIL_DEFAULT_CONTAINER, std::size_t N=1>
	using wrap_t = typename wrap<T, Tup, N>::type;



	template<typename T, TUPLE_UTIL_CONTAINER Tp, TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	struct wrap_each {
		using type = Tp<typename Trans_Tps<T>::type...>;
	};

	template<TUPLE_UTIL_CONTAINER Tp, TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	struct wrap_each_ {
		template<typename T> using type = wrap_each<T, Tp, Trans_Tps...>;
	};

	template<typename T, TUPLE_UTIL_CONTAINER Tp, TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	using wrap_each_t = typename wrap_each<T, Tp, Trans_Tps...>::type;




	template<typename T>
	struct unwrap;

	template<TUPLE_UTIL_CONTAINER Tup, typename T>
	struct unwrap<Tup<T>> : std::type_identity<T> { };

	template<typename T>
	using unwrap_t = typename unwrap<T>::type;


	namespace details {
		template<typename T, std::size_t N>
		struct duplicate;

		template<typename T, std::size_t N>
		struct duplicate;
	}
}

namespace TUPLE_UTIL_NAMESPACE::pred {
	template<typename T, TUPLE_UTIL_CONTAINER Tup>
	struct is_wrapped_by : std::false_type { };

	template<typename ... Ts, TUPLE_UTIL_CONTAINER Tup>
	struct is_wrapped_by<Tup<Ts...>, Tup> : std::true_type { };

	template<TUPLE_UTIL_CONTAINER Tup>
	struct is_wrapped_by_ { template<typename T> using type = is_wrapped_by<T, Tup>; };

	template<typename T, TUPLE_UTIL_CONTAINER Tup>
	static constexpr bool is_wrapped_by_v = is_wrapped_by<T, Tup>::value;



	template <typename T>
	struct is_wrapped : std::false_type { };

	template<template<typename...> typename Tp, typename ... Ts> 
	struct is_wrapped<Tp<Ts...>> : std::true_type { };

	template <typename T>
	static constexpr bool is_wrapped_v = is_wrapped<T>::value;
}