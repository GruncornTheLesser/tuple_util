#pragma once
#include "tuple_util.h"


// [ ] eval - transform
namespace util {
	template<typename T, TRANSFORM ... Trans_Ts> 
	struct eval;

	template<TRANSFORM ... Trans_Ts> 
	struct eval_;

	template<typename T, TRANSFORM ... Trans_Ts> 
	using eval_t = typename eval<T, Trans_Ts...>::type;

	template<typename T, TRANSFORM Trans_T, TRANSFORM ... Trans_Ts> 
	struct eval<T, Trans_T, Trans_Ts...>
	 : eval<typename Trans_T<T>::type, Trans_Ts...> { };
	
	template<typename T> 
	struct eval<T> : std::type_identity<T> { };

	template<TRANSFORM ... Trans_Ts> struct eval_ 
	{ template<typename T> using type = eval<T, Trans_Ts...>; };

	template<typename T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T = eval_<>::type, typename=void> 
	struct eval_if;

	template<PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T = std::type_identity> 
	struct eval_if_;

	template<typename T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T = eval_<>::type> 
	using eval_if_t = typename eval_if<T, Pred_T, If_T, Else_T>::type;

	template<typename T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T> 
	struct eval_if<T, Pred_T, If_T, Else_T, std::enable_if_t<Pred_T<T>::value>>
	 : If_T<T> { };

	template<typename T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T> 
	struct eval_if<T, Pred_T, If_T, Else_T, std::enable_if_t<!Pred_T<T>::value>>
	 : Else_T<T> { };

	template<PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T> struct eval_if_ 
	{ 
		template<typename T> using type = eval_if<T, Pred_T, If_T, Else_T>; 
		template<typename T> using negated = eval_if<T, pred::negate_<Pred_T>::template type, If_T, Else_T>;
	};



	// if pred,  with If_T, if true, after 
	template<typename T, TRANSFORM Trans_T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T = eval_<>::type, typename=void>
	struct post_eval_if;

	template<typename T, TRANSFORM Trans_T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T = eval_<>::type>
	using post_eval_if_t = typename post_eval_if<T, Trans_T, Pred_T, If_T, Else_T>::type;

	template<typename T, TRANSFORM Trans_T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T>
	struct post_eval_if<T, Trans_T, Pred_T, If_T, Else_T, std::enable_if_t<Pred_T<T>::value>> { using type = typename If_T<typename Trans_T<T>::type>::type; };
	
	template<typename T, TRANSFORM Trans_T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T>
	struct post_eval_if<T, Trans_T, Pred_T, If_T, Else_T, std::enable_if_t<!Pred_T<T>::value>> { using type = typename Else_T<typename Trans_T<T>::type>::type; };

	template<TRANSFORM Trans_T, PREDICATE Pred_T, TRANSFORM If_T, TRANSFORM Else_T = eval_<>::type>
	struct post_eval_if_ { template<typename T> using type = post_eval_if<T, Trans_T, Pred_T, If_T, Else_T>; };



	template<typename Tup, TRANSFORM Trans_T> 
	struct eval_each;
	
	template<TRANSFORM Trans_T> 
	struct eval_each_;

	template<typename Tup, TRANSFORM Trans_T> 
	using eval_each_t = typename eval_each<Tup, Trans_T>::type;
	
	template<CONTAINER Tup, typename ... Ts, TRANSFORM Trans_T> 
	struct eval_each<Tup<Ts...>, Trans_T>
	 : std::type_identity<Tup<typename Trans_T<Ts>::type...>>{ };

	template<TRANSFORM Trans_T>
	struct eval_each_
	 { template<typename Tup> using type = eval_each<Tup, Trans_T>; };


	
	template<typename T, TRANSFORM ... Trans_Ts>
	struct eval_branch { using type = std::tuple<typename Trans_Ts<T>::type...>; };

	template<TRANSFORM ... Trans_Ts>
	struct eval_branch_ { template<typename T> using type = eval_branch<T, Trans_Ts...>; };

	template<typename T, TRANSFORM ... Trans_Ts>
	using eval_branch_t = typename eval_branch<T, Trans_Ts...>::type;



	template<TRANSFORM Trans_T, typename ... Arg_Ts>
	struct add_type_args_ { 
		template<typename ... Ts> using type = Trans_T<Ts..., Arg_Ts...>;
	};
}
