#pragma once
#include "tuple_util.h"


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



	template<typename Tup, TRANSFORM ... Trans_Ts>
	struct eval_each;

	template<typename Tup, TRANSFORM ... Trans_Ts>
	using eval_each_t = typename eval_each<Tup, Trans_Ts...>::type;

	template<CONTAINER Tup, typename ... Ts, TRANSFORM ... Trans_Ts>
	struct eval_each<Tup<Ts...>, Trans_Ts...>
	 : std::type_identity<Tup<typename eval<Ts, Trans_Ts...>::type...>> { };

	template<TRANSFORM ... Trans_Ts>
	struct eval_each_ { template<typename Tup> using type = eval_each<Tup, Trans_Ts...>; };



	template<typename T, TRANSFORM ... Trans_Ts>
	struct eval_split { using type = std::tuple<typename Trans_Ts<T>::type...>; };

	template<typename T, TRANSFORM ... Trans_Ts>
	using eval_split_t = typename eval_split<T, Trans_Ts...>::type;

	template<TRANSFORM ... Trans_Ts>
	struct eval_split_ { template<typename T> using type = eval_split<T, Trans_Ts...>; };



	// TODO wrappers with specializations per type
	// not entirely convinced this would work but like ??? might be fun to try
	// or perhaps I could reconfigure everything else into this
	// -> would mean no more 'template type' but instead arg::cmp<std::is_same>
	// -> would allow more dynamic passing of types which would allow stack execution
	// -> could create
	/*
	namespace arg {
		struct T { };
		struct LHS_T { };
		struct RHS_T { };
		template<TRANSFORM trans_T> struct transform { };
		template<ATTRIBUTER attrib_T> struct attributer { };
		template<CONTAINER cont_T> struct container{ };
		template<COMPARE cmp_T> struct compare { };
		template<PREDICATE pred_T> struct predicate { };

	};
	*/
	template<CONTAINER Trans_T, typename ... Arg_Ts>
	struct add_arg_
	{ template<typename ... Ts> using type = Trans_T<Ts..., Arg_Ts...>; };
}
