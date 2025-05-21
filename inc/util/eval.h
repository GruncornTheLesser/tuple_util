#pragma once
#include "util/macro.h"
#include "util/predicate.h"
#include <type_traits>

// [ ] eval - transform
namespace util {
	template<typename T, TRANSFORM ... Trans_Ts>
	struct eval;

	template<typename T, TRANSFORM ... Trans_Ts>
	using eval_t = typename eval<T, Trans_Ts...>::type;

	template<typename T>
	struct eval<T> : std::type_identity<T> { };

	template<typename T, TRANSFORM Trans_T, TRANSFORM ... Trans_Ts> requires requires { typename Trans_T<T>::type; }
	struct eval<T, Trans_T, Trans_Ts...>
	 : eval<typename Trans_T<T>::type, Trans_Ts...> { };

	template<TRANSFORM ... Trans_Ts>
	struct eval_ { template<typename T> using type = eval<T, Trans_Ts...>; };



	template<typename T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T = eval_<>::type, typename=void>
	struct eval_if;

	template<typename T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T = eval_<>::type>
	using eval_if_t = typename eval_if<T, Pred_T, If_T, Else_T>::type;

	template<typename T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T> requires requires { typename If_T<T>::type; }
	struct eval_if<T, Pred_T, If_T, Else_T, std::enable_if_t<Pred_T<T>::value>>
	 : If_T<T> { };

	template<typename T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T> requires requires { typename Else_T<T>::type; }
	struct eval_if<T, Pred_T, If_T, Else_T, std::enable_if_t<!Pred_T<T>::value>>
	 : Else_T<T> { };

	template<PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T = eval_<>::type>
	struct eval_if_
	{
		template<typename T> using type = eval_if<T, Pred_T, If_T, Else_T>;
		template<typename T> using inv =  eval_if<T, pred::negate_<Pred_T>::template type, If_T, Else_T>;
	};



	template<typename Tup, TRANSFORM ... Trans_Ts>
	struct eval_each;

	template<typename Tup, TRANSFORM ... Trans_Ts>
	using eval_each_t = typename eval_each<Tup, Trans_Ts...>::type;

	template<CONTAINER Tup, typename ... Ts, TRANSFORM ... Trans_Ts>
	struct eval_each<Tup<Ts...>, Trans_Ts...> : std::type_identity<Tup<typename eval<Ts, Trans_Ts...>::type...>> { };

	template<TRANSFORM ... Trans_Ts>
	struct eval_each_ { template<typename Tup> using type = eval_each<Tup, Trans_Ts...>; };


	
	template<typename T, PREDICATE Pred_T, TRANSFORM ... Trans_Ts>
	struct eval_while { using type = T; };

	template<typename T, PREDICATE Pred_T, TRANSFORM ... Trans_Ts> requires (Pred_T<T>::value)
	struct eval_while<T, Pred_T, Trans_Ts...> : eval_while<eval_t<T, Trans_Ts...>, Pred_T, Trans_Ts...> { };

	template<typename T, PREDICATE Pred_T, TRANSFORM ... Trans_Ts>
	using eval_while_t = typename eval_while<T, Pred_T, Trans_Ts...>::type;

	template<PREDICATE Pred_T, TRANSFORM ... Trans_Ts>
	struct eval_while_ { template<typename T> using type = eval_while<T, Pred_T, Trans_Ts...>; };



	struct eval_failure { };
	namespace details { 
		template<typename T, TRANSFORM Trans_T, typename V, typename D> 
		struct eval_try { using type = D; };

		template<typename T, TRANSFORM Trans_T, typename D> 
		struct eval_try<T, Trans_T, std::void_t<typename Trans_T<T>::type>, D> : Trans_T<T> { };
	};
	
	template<typename T, TRANSFORM Trans_T, typename D=eval_failure>
	using eval_try = details::eval_try<T, Trans_T, void, D>;
	
	template<TRANSFORM Trans_T, typename D=eval_failure> struct eval_try_ { template<typename T> 
	using type = eval_try<T, Trans_T, D>; };
	
	template<typename T, TRANSFORM Trans_T, typename D=eval_failure>
	using eval_try_t = typename eval_try<T, Trans_T, D>::type;
}