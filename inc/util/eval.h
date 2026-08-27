#pragma once
#include "util/macro.h"
#include <type_traits>
#include <utility>

// [ ] eval - transform
namespace TUPLE_UTIL_NAMESPACE {
	struct eval_failure { };

	template<typename T>
	struct eval_none {
		using type = T;
	};
	template<typename T>
	using eval_none_t = T;
	


	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	struct eval;

	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	using eval_t = typename eval<T, Trans_Tps...>::type;

	template<typename T>
	struct eval<T> { using type = T; };

	template<typename T, TUPLE_UTIL_TRANSFORM Trans_Tp, TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	struct eval<T, Trans_Tp, Trans_Tps...> : eval<typename Trans_Tp<T>::type, Trans_Tps...> { };

	template<TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	struct eval_ { 
		template<typename T> using type = eval<T, Trans_Tps...>;
	};



	template<typename T, TUPLE_UTIL_PREDICATE Pred_Tp, TUPLE_UTIL_TRANSFORM If_Tp, TUPLE_UTIL_TRANSFORM Else_Tp = eval_none>
	struct eval_if;

	template<typename T, TUPLE_UTIL_PREDICATE Pred_Tp, TUPLE_UTIL_TRANSFORM If_Tp, TUPLE_UTIL_TRANSFORM Else_Tp = eval_none>
	using eval_if_t = typename eval_if<T, Pred_Tp, If_Tp, Else_Tp>::type;

	template<typename T, TUPLE_UTIL_PREDICATE Pred_Tp, TUPLE_UTIL_TRANSFORM If_Tp, TUPLE_UTIL_TRANSFORM Else_Tp>
		requires (Pred_Tp<T>::value)
	struct eval_if<T, Pred_Tp, If_Tp, Else_Tp> : If_Tp<T> { };

	template<typename T, TUPLE_UTIL_PREDICATE Pred_Tp, TUPLE_UTIL_TRANSFORM If_Tp, TUPLE_UTIL_TRANSFORM Else_Tp>
		requires (!Pred_Tp<T>::value)
	struct eval_if<T, Pred_Tp, If_Tp, Else_Tp> : Else_Tp<T> { };

	template<TUPLE_UTIL_PREDICATE Pred_Tp, TUPLE_UTIL_TRANSFORM If_Tp, TUPLE_UTIL_TRANSFORM Else_Tp = eval_<>::type>
	struct eval_if_ {
		template<typename T> using type = eval_if<T, Pred_Tp, If_Tp, Else_Tp>;
		template<typename T> using inv =  eval_if<T, Pred_Tp, Else_Tp, If_Tp>;
	};



	template<typename Tup, TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	struct eval_each;
	
	template<TUPLE_UTIL_CONTAINER Tup, typename ... Ts, TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	struct eval_each<Tup<Ts...>, Trans_Tps...> {
		using type = Tup<typename eval<Ts, Trans_Tps...>::type...>;
	};
	
	template<TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	struct eval_each_ { template<typename Tup> using type = eval_each<Tup, Trans_Tps...>; };
	
	template<typename Tup, TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	using eval_each_t = typename eval_each<Tup, Trans_Tps...>::type;



	template<typename T, TUPLE_UTIL_CONTAINER Tp, TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	struct eval_invoke {
		using type = typename Tp<typename Trans_Tps<T>::type...>::type;
	};

	template<TUPLE_UTIL_CONTAINER Tp, TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	struct eval_invoke_ {
		template<typename T> using type = eval_invoke<T, Tp, Trans_Tps...>;
	};

	template<typename T, TUPLE_UTIL_CONTAINER Tp, TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	using eval_invoke_t = typename eval_invoke<T, Tp, Trans_Tps...>::type;


	
	template<typename T, TUPLE_UTIL_PREDICATE Pred_T, TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	struct eval_while { using type = T; };

	template<typename T, TUPLE_UTIL_PREDICATE Pred_T, TUPLE_UTIL_TRANSFORM ... Trans_Tps> requires (Pred_T<T>::value)
	struct eval_while<T, Pred_T, Trans_Tps...> : eval_while<eval_t<T, Trans_Tps...>, Pred_T, Trans_Tps...> { };

	template<typename T, TUPLE_UTIL_PREDICATE Pred_T, TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	using eval_while_t = typename eval_while<T, Pred_T, Trans_Tps...>::type;

	template<TUPLE_UTIL_PREDICATE Pred_T, TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	struct eval_while_ { template<typename T> using type = eval_while<T, Pred_T, Trans_Tps...>; };
	


	namespace details { 
		template<typename T, TUPLE_UTIL_TRANSFORM Trans_T, typename V, typename D> 
		struct eval_try { using type = D; };

		template<typename T, TUPLE_UTIL_TRANSFORM Trans_T, typename D> 
		struct eval_try<T, Trans_T, std::void_t<typename Trans_T<T>::type>, D> : Trans_T<T> { };
	};
	
	template<typename T, TUPLE_UTIL_TRANSFORM Trans_T, typename D=eval_failure>
	using eval_try = details::eval_try<T, Trans_T, void, D>;
	
	template<TUPLE_UTIL_TRANSFORM Trans_T, typename D=eval_failure> struct eval_try_ { template<typename T> 
	using type = eval_try<T, Trans_T, D>; };
	
	template<typename T, TUPLE_UTIL_TRANSFORM Trans_T, typename D=eval_failure>
	using eval_try_t = typename eval_try<T, Trans_T, D>::type;



	template<typename T, typename D, TUPLE_UTIL_TRANSFORM ... Trans_Ts>
	using put = eval<D, Trans_Ts...>;
	
	template<typename T, typename D, TUPLE_UTIL_TRANSFORM ... Trans_Ts>
	using put_t = eval_t<D, Trans_Ts...>;

	template<typename D, TUPLE_UTIL_TRANSFORM ... Trans_Ts>
	struct put_ { 
		template<typename T> using type = eval<D, Trans_Ts...>;
	};
}