#pragma once
#include "util/macro.h"
#include "util/predicate.h"

// [ ] eval - transform
namespace util {
	template<typename T, TRANSFORM ... Trans_Ts>
	struct eval;

	template<typename T, TRANSFORM ... Trans_Ts>
	using eval_t = typename eval<T, Trans_Ts...>::type;

	template<typename T>
	struct eval<T> : std::type_identity<T> { };

	template<typename T, TRANSFORM Trans_T, TRANSFORM ... Trans_Ts>
	struct eval<T, Trans_T, Trans_Ts...>
	 : eval<typename Trans_T<T>::type, Trans_Ts...> { };

	template<TRANSFORM ... Trans_Ts>
	struct eval_ { template<typename T> using type = eval<T, Trans_Ts...>; };



	template<typename T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T = eval_<>::type, typename=void>
	struct eval_if;

	template<typename T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T = eval_<>::type>
	using eval_if_t = typename eval_if<T, Pred_T, If_T, Else_T>::type;

	template<typename T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T>
	struct eval_if<T, Pred_T, If_T, Else_T, std::enable_if_t<Pred_T<T>::value>>
	 : If_T<T> { };

	template<typename T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T>
	struct eval_if<T, Pred_T, If_T, Else_T, std::enable_if_t<!Pred_T<T>::value>>
	 : Else_T<T> { };

	template<PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T = eval_<>::type>
	struct eval_if_
	{
		template<typename T> using type = eval_if<T, Pred_T, If_T, Else_T>;
		template<typename T> using inv =  eval_if<T, pred::negate_<Pred_T>::template type, If_T, Else_T>;
	};



	// if pred,  with If_T, if true, after
	template<typename T, TRANSFORM Trans_T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T = eval_<>::type>
	struct eval_post_if;

	template<typename T, TRANSFORM Trans_T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T> requires (Pred_T<T>::value)
	struct eval_post_if<T, Trans_T, Pred_T, If_T, Else_T> : If_T<typename Trans_T<T>::type> { };

	template<typename T, TRANSFORM Trans_T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T> requires (!Pred_T<T>::value)
	struct eval_post_if<T, Trans_T, Pred_T, If_T, Else_T> : Else_T<typename Trans_T<T>::type> { };

	template<TRANSFORM Trans_T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T = eval_<>::type>
	struct eval_post_if_ { 
		template<typename T> using type = eval_post_if<T, Trans_T, Pred_T, If_T, Else_T>;
		template<typename T> using inv =  eval_post_if<T, Trans_T, Pred_T, Else_T, If_T>;
	};

	template<typename T, TRANSFORM Trans_T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T = eval_<>::type>
	using eval_post_if_t = typename eval_post_if<T, Trans_T, Pred_T, If_T, Else_T>::type;



	template<typename Tup, TRANSFORM ... Trans_Ts>
	struct eval_each;

	template<typename Tup, TRANSFORM ... Trans_Ts>
	using eval_each_t = typename eval_each<Tup, Trans_Ts...>::type;

	template<CONTAINER Tup, typename ... Ts, TRANSFORM ... Trans_Ts>
	struct eval_each<Tup<Ts...>, Trans_Ts...>
	 : std::type_identity<Tup<typename eval<Ts, Trans_Ts...>::type...>> { };

	template<TRANSFORM ... Trans_Ts>
	struct eval_each_ { template<typename Tup> using type = eval_each<Tup, Trans_Ts...>; };



	struct eval_failure { };
	namespace details { 
		template<typename T, template<typename...> typename Eval_Tp, typename V, typename D, typename ... Arg_Ts> 
		struct eval_try { using type = D; };

		template<typename T, template<typename...> typename Eval_Tp, typename D, typename ... Arg_Ts> 
		struct eval_try<T, Eval_Tp, std::void_t<typename Eval_Tp<T, Arg_Ts...>::type>, D, Arg_Ts...> : Eval_Tp<T, Arg_Ts...> { };
	};
	
	template<typename T, template<typename...> typename Eval_Tp, typename D=eval_failure, typename ... Arg_Ts>
	using eval_try = details::eval_try<T, Eval_Tp, void, D, Arg_Ts...>;
	
	template<template<typename...> typename Eval_Tp, typename D=eval_failure> struct eval_try_ { template<typename T, typename ... Arg_Ts> 
	using type = eval_try<T, Eval_Tp, D, Arg_Ts...>; };
	
	template<typename T, template<typename...> typename Eval_Tp, typename D=eval_failure, typename ... Arg_Ts>
	using eval_try_t = typename eval_try<T, Eval_Tp, D, Arg_Ts...>::type;
}
