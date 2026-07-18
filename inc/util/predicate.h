#pragma once
#include "util/macro.h"
#include <type_traits>

namespace TUPLE_UTIL_NAMESPACE::pred {
	template<TUPLE_UTIL_PREDICATE Pred_T>
	struct negate_ {
		template<typename T> using type = std::negation<Pred_T<T>>;
	};

	template<typename T, TUPLE_UTIL_PREDICATE ... Pred_Ts>
	using disj = std::disjunction<Pred_Ts<T>...>;

	template<TUPLE_UTIL_PREDICATE ... Pred_Ts>
	struct disj_ {
		template<typename T> using type = std::disjunction<Pred_Ts<T>...>;
		template<typename T> using inv =  std::negation<type<T>>;
	};

	template<typename T, TUPLE_UTIL_PREDICATE ... Pred_Ts>
	static constexpr bool disj_v = std::disjunction_v<Pred_Ts<T>...>;

	template<typename T, TUPLE_UTIL_PREDICATE ... Pred_Ts>
	using conj = std::conjunction<Pred_Ts<T>...>;

	template<TUPLE_UTIL_PREDICATE ... Pred_Ts>
	struct conj_ {
		template<typename T> using type = std::conjunction<Pred_Ts<T>...>;
		template<typename T> using inv =  std::negation<type<T>>;
	};

	template<typename T, TUPLE_UTIL_PREDICATE ... Pred_Ts>
	static constexpr bool conj_v = std::conjunction_v<Pred_Ts<T>...>;

	template<typename Tup, TUPLE_UTIL_PREDICATE Pred_T>
	struct anyof;

	template<TUPLE_UTIL_CONTAINER Tup, typename ... Ts, TUPLE_UTIL_PREDICATE Pred_T>
	struct anyof<Tup<Ts...>, Pred_T> : std::disjunction<Pred_T<Ts>...> { };

	template<TUPLE_UTIL_PREDICATE Pred_T>
	struct anyof_ { 
		template<typename Tup> using type = anyof<Tup, Pred_T>;
		template<typename T> using inv =  std::negation<type<T>>;
	};

	template<typename Tup, TUPLE_UTIL_PREDICATE Pred_T>
	static constexpr bool anyof_v = anyof<Tup, Pred_T>::value;

	template<typename Tup, TUPLE_UTIL_PREDICATE Pred_T>
	struct allof;

	template<TUPLE_UTIL_CONTAINER Tup, typename ... Ts, TUPLE_UTIL_PREDICATE Pred_T>
	struct allof<Tup<Ts...>, Pred_T> : std::conjunction<Pred_T<Ts>...> { };

	template<TUPLE_UTIL_PREDICATE Pred_T>
	struct allof_ { 
		template<typename Tup> using type = allof<Tup, Pred_T>;
		template<typename Tup> using inv =  std::negation<type<Tup>>;
	};

	template<typename Tup, TUPLE_UTIL_PREDICATE Pred_T>
	static constexpr bool allof_v = allof<Tup, Pred_T>::value;


	// pred against a transformed T
	template<typename T, TUPLE_UTIL_PREDICATE Pred_T, TUPLE_UTIL_TRANSFORM Trans_T> requires requires { typename Trans_T<T>::type; }
	struct evaled : Pred_T<typename Trans_T<T>::type> { };

	template<typename T, TUPLE_UTIL_PREDICATE Pred_T, TUPLE_UTIL_TRANSFORM Trans_T>
	static constexpr bool evaled_v = evaled<T, Pred_T, Trans_T>::value;

	template<TUPLE_UTIL_PREDICATE Pred_T, TUPLE_UTIL_TRANSFORM Trans_T> struct evaled_ {
		template<typename T> using type = evaled<T, Pred_T, Trans_T>;
		template<typename T> using inv =  std::negation<type<T>>; 
	};
}

namespace TUPLE_UTIL_NAMESPACE {
	template<typename T, TUPLE_UTIL_PREDICATE Pred_T>
	struct util_assert { using type = T; static_assert(Pred_T<T>::value); };
	template<TUPLE_UTIL_PREDICATE Pred_T>
	struct assert_ { template<typename T> using type = util_assert<T, Pred_T>; };
}