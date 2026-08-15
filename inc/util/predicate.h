#pragma once
#include "util/macro.h"

namespace TUPLE_UTIL_NAMESPACE::pred {
	template<typename T, TUPLE_UTIL_PREDICATE Pred_T>
	struct negate {
		static constexpr bool value = !Pred_T<T>::value;
	};
	
	template<TUPLE_UTIL_PREDICATE Pred_T>
	struct negate_ {
		template<typename T> using type = negate<T, Pred_T>;
	};

	template<typename T, TUPLE_UTIL_PREDICATE ... Pred_Ts>
	struct disj {
		static constexpr bool value = (Pred_Ts<T>::value || ...);
	};
	template<TUPLE_UTIL_PREDICATE ... Pred_Ts>
	struct disj_ {
		template<typename T> using type = disj<Pred_Ts<T>...>;
		template<typename T> using inv =  negate<T, type>;
	};
	template<typename T, TUPLE_UTIL_PREDICATE ... Pred_Ts>
	static constexpr bool disj_v = disj<T, Pred_Ts...>::value;

	template<typename T, TUPLE_UTIL_PREDICATE ... Pred_Ts>
	struct conj {
		static constexpr bool value = (Pred_Ts<T>::value && ...);
	};
	template<TUPLE_UTIL_PREDICATE ... Pred_Ts>
	struct conj_ {
		template<typename T> using type = conj<Pred_Ts<T>...>;
		template<typename T> using inv =  negate<T, type>;
	};
	template<typename T, TUPLE_UTIL_PREDICATE ... Pred_Ts>
	static constexpr bool conj_v = disj<T, Pred_Ts...>::value;

	template<typename Tup, TUPLE_UTIL_PREDICATE Pred_T>
	struct anyof;

	template<TUPLE_UTIL_CONTAINER Tup, typename ... Ts, TUPLE_UTIL_PREDICATE Pred_T>
	struct anyof<Tup<Ts...>, Pred_T> { 
		static constexpr bool value = (Pred_T<Ts>::value || ...);
	};
	template<TUPLE_UTIL_PREDICATE Pred_T>
	struct anyof_ { 
		template<typename Tup> using type = anyof<Tup, Pred_T>;
		template<typename Tup> using inv =  negate<Tup, type>;
	};
	template<typename Tup, TUPLE_UTIL_PREDICATE Pred_T>
	static constexpr bool anyof_v = anyof<Tup, Pred_T>::value;

	template<typename Tup, TUPLE_UTIL_PREDICATE Pred_T>
	struct allof;

	template<TUPLE_UTIL_CONTAINER Tup, typename ... Ts, TUPLE_UTIL_PREDICATE Pred_T>
	struct allof<Tup<Ts...>, Pred_T> {
		static constexpr bool value = (Pred_T<Ts>::value && ...);
	};
	template<TUPLE_UTIL_PREDICATE Pred_T>
	struct allof_ { 
		template<typename Tup> using type = allof<Tup, Pred_T>;
		template<typename Tup> using inv =  negate<Tup, type>;
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
		template<typename T> using inv =  negate<T, type>; 
	};
}

namespace TUPLE_UTIL_NAMESPACE {
	template<typename T, TUPLE_UTIL_PREDICATE Pred_T>
	struct util_assert { using type = T; static_assert(Pred_T<T>::value); };
	template<TUPLE_UTIL_PREDICATE Pred_T>
	struct assert_ { template<typename T> using type = util_assert<T, Pred_T>; };
}