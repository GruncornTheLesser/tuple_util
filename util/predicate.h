#pragma once
#include "tuple_util.h"
#include "compare.h"

namespace util::pred {
	template<PREDICATE Pred_T> 
	struct negate_
	 { template<typename T> using type = std::negation<Pred_T<T>>; };

	template<PREDICATE ... Pred_Ts>
	struct disjunction_ { 
		template<typename T> using type = std::disjunction<Pred_Ts<T>...>; 
		template<typename T> using negated = std::negation<type<T>>;
	};
	template<PREDICATE ... Pred_Ts>
	struct conjunction_ { 
		template<typename T> using type = std::conjunction<Pred_Ts<T>...>; 
		template<typename T> using negated = std::negation<type<T>>;
	};

	template<typename Tup, PREDICATE Pred_T> 
	struct anyof;

	template<CONTAINER Tup, typename ... Ts, PREDICATE Pred_T>
	struct anyof<Tup<Ts...>, Pred_T> : std::disjunction<Pred_T<Ts>...> { };
	
	template<PREDICATE Pred_T>
	struct anyof_ { template<typename Tup> using type = anyof<Tup, Pred_T>; };
	
	template<typename Tup, PREDICATE Pred_T> 
	static constexpr bool anyof_v = anyof<Tup, Pred_T>::value;

	template<typename Tup, PREDICATE Pred_T> 
	struct allof;

	template<CONTAINER Tup, typename ... Ts, PREDICATE Pred_T>
	struct allof<Tup<Ts...>, Pred_T> : std::conjunction<Pred_T<Ts>...> { };
	
	template<PREDICATE Pred_T>
	struct allof_ { template<typename Tup> using type = allof<Tup, Pred_T>; };
	
	template<typename Tup, PREDICATE Pred_T> 
	static constexpr bool allof_v = allof<Tup, Pred_T>::value;
}



// [ ] pred transformed - pred
namespace util::pred {
	template<typename T, PREDICATE Pred_T, TRANSFORM Trans_T> struct transformed : Pred_T<typename Trans_T<T>::type> { };
	template<typename T, PREDICATE Pred_T, TRANSFORM Trans_T> using transformed_v = transformed<T, Pred_T, Trans_T>::value;
	template<PREDICATE Pred_T, TRANSFORM Trans_T> struct transformed_ { 
		template<typename T> using type = Pred_T<typename transformed<T, Pred_T, Trans_T>::type>; 
		template<typename T> using negated = std::negation<type<T>>; };
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
		template<typename T> using negated = std::negation<type<T>>;
	};
	
	template<typename T, COMPARE Cmp_T = std::is_same>
	struct contains_ {
		template<typename Tup> using type = element_of<T, Tup>; 
		template<typename Tup> using negated = std::negation<type<Tup>>;
	};

	template<typename T, typename Tup, COMPARE Same_T = std::is_same>
	static constexpr bool element_of_v = element_of<T, Tup, Same_T>::value;

	template<typename Tup, typename T, COMPARE Same_T = std::is_same>
	static constexpr bool contains_v = element_of<T, Tup, Same_T>::value;
}


