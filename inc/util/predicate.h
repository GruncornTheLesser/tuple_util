#pragma once
#include "util/macro.h"

namespace util {
	template<CONTAINER Pred_T, typename ... Ts>
	struct pred_ {
		template<typename T> using type = Pred_T<T, Ts...>;
		template<typename T> using inv  = std::negation<Pred_T<T, Ts...>>;
	};
}

namespace util::pred {
	template<PREDICATE Pred_T>
	struct negate_ {
		template<typename T> using type = std::negation<Pred_T<T>>;
	};

	template<typename T, PREDICATE ... Pred_Ts>
	using disj = std::disjunction<Pred_Ts<T>...>;

	template<PREDICATE ... Pred_Ts>
	struct disj_ {
		template<typename T> using type = std::disjunction<Pred_Ts<T>...>;
		template<typename T> using inv =  std::negation<type<T>>;
	};

	template<typename T, PREDICATE ... Pred_Ts>
	static constexpr bool disj_v = std::disjunction_v<Pred_Ts<T>...>;

	template<typename T, PREDICATE ... Pred_Ts>
	using conj = std::conjunction<Pred_Ts<T>...>;

	template<PREDICATE ... Pred_Ts>
	struct conj_ {
		template<typename T> using type = std::conjunction<Pred_Ts<T>...>;
		template<typename T> using inv =  std::negation<type<T>>;
	};

	template<typename T, PREDICATE ... Pred_Ts>
	static constexpr bool conj_v = std::conjunction_v<Pred_Ts<T>...>;

	template<typename Tup, PREDICATE Pred_T>
	struct anyof;

	template<CONTAINER Tup, typename ... Ts, PREDICATE Pred_T>
	struct anyof<Tup<Ts...>, Pred_T> : std::disjunction<Pred_T<Ts>...> { };

	template<PREDICATE Pred_T>
	struct anyof_ { 
		template<typename Tup> using type = anyof<Tup, Pred_T>;
		template<typename T> using inv =  std::negation<type<T>>;
	};

	template<typename Tup, PREDICATE Pred_T>
	static constexpr bool anyof_v = anyof<Tup, Pred_T>::value;

	template<typename Tup, PREDICATE Pred_T>
	struct allof;

	template<CONTAINER Tup, typename ... Ts, PREDICATE Pred_T>
	struct allof<Tup<Ts...>, Pred_T> : std::conjunction<Pred_T<Ts>...> { };

	template<PREDICATE Pred_T>
	struct allof_ { 
		template<typename Tup> using type = allof<Tup, Pred_T>;
		template<typename Tup> using inv =  std::negation<type<Tup>>;
	};

	template<typename Tup, PREDICATE Pred_T>
	static constexpr bool allof_v = allof<Tup, Pred_T>::value;


	// pred against a transformed T
	template<typename T, PREDICATE Pred_T, TRANSFORM Trans_T>
	struct evaled : Pred_T<typename Trans_T<T>::type> { };

	template<typename T, PREDICATE Pred_T, TRANSFORM Trans_T>
	using evaled_v = evaled<T, Pred_T, Trans_T>::value;

	template<PREDICATE Pred_T, TRANSFORM Trans_T> struct evaled_ {
		template<typename T> using type = Pred_T<typename evaled<T, Pred_T, Trans_T>::type>;
		template<typename T> using inv =  std::negation<type<T>>; 
	};
}

// [ ] element of/contains - pred set
namespace util::pred {
	template<typename T, typename Tup, COMPARE Same_T=std::is_same>
	struct element_of;

	template<typename T, CONTAINER Tup, typename ... Ts, COMPARE Same_T>
	struct element_of<T, Tup<Ts...>, Same_T> : std::disjunction<Same_T<T, Ts>...> { };

	template<typename Tup, COMPARE Cmp_T = std::is_same>
	struct element_of_ {
		template<typename T> using type = element_of<T, Tup, Cmp_T>;
		template<typename T> using inv =  std::negation<type<T>>;
	};

	template<typename T, COMPARE Cmp_T = std::is_same>
	struct contains_ {
		template<typename Tup> using type = element_of<T, Tup>;
		template<typename Tup> using inv =  std::negation<type<Tup>>;
	};

	template<typename T, typename Tup, COMPARE Same_T = std::is_same>
	static constexpr bool element_of_v = element_of<T, Tup, Same_T>::value;

	template<typename Tup, typename T, COMPARE Same_T = std::is_same>
	static constexpr bool contains_v = element_of<T, Tup, Same_T>::value;
}

namespace util {
	template<typename T, PREDICATE Pred_T>
	struct util_assert { using type = T; static_assert(Pred_T<T>::value); };
	template<PREDICATE Pred_T>
	struct assert_ { template<typename T> using type = util_assert<T, Pred_T>; };
}