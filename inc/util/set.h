#pragma once
#include "util/eval.h"
#include "util/macro.h"
#include "util/predicate.h"
#include "util/compare.h"
#include <utility>

namespace TUPLE_UTIL_NAMESPACE::pred {
	template<typename T, typename Tup, TUPLE_UTIL_COMPARE Same_T=TUPLE_UTIL_DEFAULT_COMPARE>
	struct element_of;

	template<typename T, TUPLE_UTIL_CONTAINER Tup, typename ... Ts, TUPLE_UTIL_COMPARE Same_T>
	struct element_of<T, Tup<Ts...>, Same_T> { 
		static constexpr bool value = (Same_T<T, Ts>::value || ...);
	};

	template<typename Tup, TUPLE_UTIL_COMPARE Cmp_T = TUPLE_UTIL_DEFAULT_COMPARE>
	struct element_of_ {
		template<typename T> using type = element_of<T, Tup, Cmp_T>;
		template<typename T> using inv =  negate<T, type>;
	};

	template<typename T, TUPLE_UTIL_COMPARE Cmp_T = TUPLE_UTIL_DEFAULT_COMPARE>
	struct contains_ {
		template<typename Tup> using type = element_of<T, Tup>;
		template<typename Tup> using inv =  negate<T, type>;
	};

	template<typename T, typename Tup, TUPLE_UTIL_COMPARE Same_T = TUPLE_UTIL_DEFAULT_COMPARE>
	static constexpr bool element_of_v = element_of<T, Tup, Same_T>::value;

	template<typename Tup, typename T, TUPLE_UTIL_COMPARE Same_T = TUPLE_UTIL_DEFAULT_COMPARE>
	static constexpr bool contains_v = element_of<T, Tup, Same_T>::value;
}


namespace TUPLE_UTIL_NAMESPACE {
	template<typename Tup> 
	struct count;

	template<typename Tup> 
	static constexpr std::size_t count_v = count<Tup>::value;

	template<TUPLE_UTIL_CONTAINER Tup, typename ... Ts> 
	struct count<Tup<Ts...>> { static constexpr std::size_t value = sizeof...(Ts); };

	

	template<typename Tup, TUPLE_UTIL_CONTAINER Pred_Tp>
	struct count_if;

	template<typename Tup, TUPLE_UTIL_CONTAINER Pred_Tp>
	static constexpr std::size_t count_if_v = count_if<Tup, Pred_Tp>::value;

	template<TUPLE_UTIL_CONTAINER Pred_Tp>
	struct count_if_ {
		template<typename Tup> using type = count_if<Tup, Pred_Tp>;
		template<typename Tup> using inv = count_if<Tup, pred::negate_<Pred_Tp>::template type>;
	};

	template<TUPLE_UTIL_CONTAINER Tup, typename ... Ts, TUPLE_UTIL_CONTAINER Pred_Tp>
	struct count_if<Tup<Ts...>, Pred_Tp> {
		static constexpr std::size_t value = (Pred_Tp<Ts>::value + ...);
	};

	
	
	template<std::size_t N, typename Tup> 
	struct at;

	template<std::size_t N>
	struct at_ { template<typename Tup> using type = at<N, Tup>; };

	template<std::size_t N, typename Tup> 
	using at_t = typename at<N, Tup>::type;

	template<std::size_t N, TUPLE_UTIL_CONTAINER Tup, typename T, typename ... Ts>
	struct at<N, Tup<T, Ts...>> : at<N - 1u, Tup<Ts...>> { };

	template<TUPLE_UTIL_CONTAINER Tup, typename T, typename ... Ts>
	struct at<0, Tup<T, Ts...>> { using type = T; };

	
	template<typename Tup>
	using front = at<0, Tup>;

	template<typename Tup>
	using front_t = typename front<Tup>::type;


	template<typename Tup>
	using back = at<count_v<Tup> - 1, Tup>;

	template<typename Tup>
	using back_t = typename back<Tup>::type;



	template<typename Tup>
	struct clear;

	template<TUPLE_UTIL_CONTAINER Tup, typename ... Ts>
	struct clear<Tup<Ts...>> {
		using type = Tup<>;
	};

	template<typename Tup>
	using clear_t = typename clear<Tup>::type;




	template<typename Tup, typename Ind>
	struct subset;

	template<typename Ind>
	struct subset_ { template<typename Tup> using type = subset<Tup, Ind>; };

	template<typename Tup, typename Ind>
	using subset_t = typename subset<Tup, Ind>::type;

	template<TUPLE_UTIL_CONTAINER Tup, typename ... Ts, std::size_t ... Is>
	struct subset<Tup<Ts...>, std::index_sequence<Is...>> {
		using type = Tup<at_t<Is, Tup<Ts...>>...>;
	};



	namespace details {
		template<auto arr, typename Ind>
		struct index_sequence_from;
		
		template<auto arr, std::size_t ... Is>
		struct index_sequence_from<arr, std::index_sequence<Is...>> {
			using type = std::index_sequence<arr[Is]...>;
		};
	}

	template<auto arr, std::size_t N=arr.size()>
	using index_sequence_from = details::index_sequence_from<arr, std::make_index_sequence<N>>;

	template<auto arr, std::size_t N=arr.size()>
	using index_sequence_from_t = typename index_sequence_from<arr, N>::type;

	


	template<typename Tup>
	struct concat;

	template<typename Tup>
	using concat_t = typename concat<Tup>::type;

	template<TUPLE_UTIL_CONTAINER Set_T, TUPLE_UTIL_CONTAINER Tup1, typename ... T1s, TUPLE_UTIL_CONTAINER Tup2, typename ... T2s, typename ... Tups>
	struct concat<Set_T<Tup1<T1s...>, Tup2<T2s...>, Tups...>> : concat<Set_T<Tup1<T1s..., T2s...>, Tups...>> { };

	template<TUPLE_UTIL_CONTAINER Set_T, TUPLE_UTIL_CONTAINER Tup, typename ... Ts>
	struct concat<Set_T<Tup<Ts...>>> : std::type_identity<Tup<Ts...>> { };

	template<TUPLE_UTIL_CONTAINER Set_T>
	struct concat<Set_T<>> : std::type_identity<Set_T<>> { };


	
	namespace details {
		template<typename TupIn, typename TupOut>
		struct reverse;

		template<TUPLE_UTIL_CONTAINER In, typename In_T, typename ... In_Ts, TUPLE_UTIL_CONTAINER Out, typename ... Out_Ts>
		struct reverse<In<In_T, In_Ts...>, Out<Out_Ts...>> : reverse<In<In_Ts...>, Out<In_T, Out_Ts...>> { };

		template<TUPLE_UTIL_CONTAINER In, TUPLE_UTIL_CONTAINER Out, typename ... Out_Ts>
		struct reverse<In<>, Out<Out_Ts...>> { 
			using type = Out<Out_Ts...>;
		};
	}
	
	template<typename Tup>
	using reverse = details::reverse<Tup, clear_t<Tup>>;

	template<typename Tup>
	using reverse_t = typename reverse<Tup>::type;



	template<typename Tup, typename ... Ts>
	struct push_back;

	template<TUPLE_UTIL_CONTAINER Tup, typename ... Us, typename ... Ts>
	struct push_back<Tup<Us...>, Ts...> { using type = Tup<Us..., Ts...>; };

	template<typename ... Ts> struct push_back_ { 
		template<typename Tup> using type = push_back<Tup, Ts...>; 
	};

	template<typename Tup, typename ... Ts>
	using push_back_t = typename push_back<Tup, Ts...>::type;



	template<typename Tup, typename ... Ts>
	struct push_front;

	template<TUPLE_UTIL_CONTAINER Tup, typename ... Us, typename ... Ts>
	struct push_front<Tup<Us...>, Ts...> { using type = Tup<Ts..., Us...>; };

	template<typename ... Ts> struct push_front_ { 
		template<typename Tup> using type = push_front<Tup, Ts...>; 
	};

	template<typename Tup, typename ... Ts>
	using push_front_t = typename push_front<Tup, Ts...>::type;



	template<typename Tup1, typename Tup2, TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	struct append_range : append_range<Tup1, eval_t<Tup1, Trans_Tps...>> { };

	template<TUPLE_UTIL_CONTAINER Tp1, typename ... Ts1, TUPLE_UTIL_CONTAINER Tp2, typename ... Ts2>
	struct append_range<Tp1<Ts1...>, Tp2<Ts2...>> { 
		using type = Tp1<Ts1..., Ts2...>;
	};

	template<typename Tup2, TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	struct append_range_ {
		template<typename Tup1> using type = append_range<Tup1, Tup2, Trans_Tps...>;
	};

	template<typename Tup1, typename Tup2, TUPLE_UTIL_TRANSFORM ... Trans_Tps>
	using append_range_t = typename append_range<Tup1, Tup2, Trans_Tps...>::type;



	template<typename Tup1, typename Tup2>
	struct prepend_range;

	template<TUPLE_UTIL_CONTAINER Tp1, typename ... Ts1, TUPLE_UTIL_CONTAINER Tp2, typename ... Ts2>
	struct prepend_range<Tp1<Ts1...>, Tp2<Ts2...>> { 
		using type = Tp1<Ts2..., Ts1...>;
	};

	template<typename Tup2>
	struct prepend_range_ {
		template<typename Tup1> using type = prepend_range<Tup1, Tup2>;
	};

	template<typename Tup1, typename Tup2>
	using prepend_range_t = typename prepend_range<Tup1, Tup2>::type;





	namespace details {
		template<typename T, std::size_t I, std::size_t J, TUPLE_UTIL_TRANSFORM Trans_T>
		struct eval_at_element { using type = T; };

		template<typename T, std::size_t I, TUPLE_UTIL_TRANSFORM Trans_T>
		struct eval_at_element<T, I, I, Trans_T> : Trans_T<T> { };
		
		template<typename Tup, std::size_t I, TUPLE_UTIL_TRANSFORM Trans_T, typename Ind=std::make_index_sequence<count_v<Tup>>>
		struct eval_at;

		template<TUPLE_UTIL_CONTAINER Tp, typename ... Ts, std::size_t I, TUPLE_UTIL_TRANSFORM Trans_T, std::size_t ... Is>
		struct eval_at<Tp<Ts...>, I, Trans_T, std::index_sequence<Is...>> {
			using type = Tp<typename eval_at_element<Ts, I, Is, Trans_T>::type...>;
		};
	}

	template<typename Tup, std::size_t I, TUPLE_UTIL_TRANSFORM ... Trans_Ts>
	using eval_at = details::eval_at<Tup, I, eval_<Trans_Ts...>::template type>;

	template<typename Tup, std::size_t N, TUPLE_UTIL_TRANSFORM ... Trans_Ts>
	using eval_at_t = typename eval_at<Tup, N, Trans_Ts...>::type; 
	
	template<std::size_t N, TUPLE_UTIL_TRANSFORM ... Trans_Ts>
	struct eval_at_ { template<typename Tup> using type = eval_at<Tup, N, Trans_Ts...>; };



	template<typename Tup>
	struct pop_front;

	template<TUPLE_UTIL_CONTAINER Tup, typename T, typename ... Ts>
	struct pop_front<Tup<T, Ts...>> { using type = Tup<Ts...>; };
	
	template<typename Tup>
	using pop_front_t = typename pop_front<Tup>::type;



	template<typename Tup>
	struct pop_back;

	template<typename Tup>
	struct pop_back : subset<Tup, std::make_index_sequence<count_v<Tup> - 1>> { };

	template<typename Tup>
	using pop_back_t = typename pop_back<Tup>::type;



	namespace details {
		template<typename In, TUPLE_UTIL_PREDICATE Pred_Tp, typename Out>
		struct filter;

		template<TUPLE_UTIL_CONTAINER Tup, typename In_T, typename ... In_Ts, TUPLE_UTIL_PREDICATE Pred_Tp, typename ... Out_Ts>
			requires (Pred_Tp<In_T>::value)
		struct filter<Tup<In_T, In_Ts...>, Pred_Tp, Tup<Out_Ts...>> : filter<Tup<In_Ts...>, Pred_Tp, Tup<Out_Ts..., In_T>> { };

		template<TUPLE_UTIL_CONTAINER Tup, typename In_T, typename ... In_Ts, TUPLE_UTIL_PREDICATE Pred_Tp, typename ... Out_Ts>
			requires (!Pred_Tp<In_T>::value)
		struct filter<Tup<In_T, In_Ts...>, Pred_Tp, Tup<Out_Ts...>> : filter<Tup<In_Ts...>, Pred_Tp, Tup<Out_Ts...>> { };

		template<TUPLE_UTIL_CONTAINER Tup, TUPLE_UTIL_PREDICATE Pred_Tp, typename ... Out_Ts>
		struct filter<Tup<>, Pred_Tp, Tup<Out_Ts...>> { using type = Tup<Out_Ts...>; };
	}

	template<typename Tup, TUPLE_UTIL_PREDICATE Pred_Tp>
	using filter = details::filter<Tup, Pred_Tp, clear_t<Tup>>;

	template<TUPLE_UTIL_PREDICATE Pred_Tp>
	struct filter_ { 
		template<typename Tup> using type = filter<Tup, Pred_Tp>;
		template<typename Tup> using inv =  filter<Tup, pred::negate_<Pred_Tp>::template type>;
	};
	
	template<typename Tup, TUPLE_UTIL_PREDICATE Pred_Tp>
	using filter_t = typename filter<Tup, Pred_Tp>::type;



	namespace details {
		template<typename In, typename LHS, typename RHS, TUPLE_UTIL_PREDICATE ... Pred_Tp>
		struct partition;

		template<TUPLE_UTIL_CONTAINER Tup, typename In_T, typename ... In_Ts, typename ... L_Ts, typename ... R_Ts, TUPLE_UTIL_PREDICATE Pred_Tp, TUPLE_UTIL_PREDICATE ... Pred_Tps>
			requires (Pred_Tp<In_T>::value)
		struct partition<Tup<In_T, In_Ts...>, Tup<L_Ts...>, Tup<R_Ts...>, Pred_Tp, Pred_Tps...> : partition<Tup<In_Ts...>, Tup<L_Ts..., In_T>, Tup<R_Ts...>, Pred_Tp, Pred_Tps...> { };

		template<TUPLE_UTIL_CONTAINER Tup, typename In_T, typename ... In_Ts, typename ... L_Ts, typename ... R_Ts, TUPLE_UTIL_PREDICATE Pred_Tp, TUPLE_UTIL_PREDICATE ... Pred_Tps>
			requires (!Pred_Tp<In_T>::value)
		struct partition<Tup<In_T, In_Ts...>, Tup<L_Ts...>, Tup<R_Ts...>, Pred_Tp, Pred_Tps...> : partition<Tup<In_Ts...>, Tup<L_Ts...>, Tup<R_Ts..., In_T>, Pred_Tp, Pred_Tps...> { };

		template<TUPLE_UTIL_CONTAINER Tup, typename ... L_Ts, typename ... R_Ts, TUPLE_UTIL_PREDICATE Pred_Tp, TUPLE_UTIL_PREDICATE ... Pred_Tps>
		struct partition<Tup<>, Tup<L_Ts...>, Tup<R_Ts...>, Pred_Tp, Pred_Tps...> : partition<Tup<R_Ts...>, Tup<L_Ts...>, Tup<>, Pred_Tps...> { };
		
		template<TUPLE_UTIL_CONTAINER Tup, typename ... L_Ts, typename ... R_Ts, TUPLE_UTIL_PREDICATE Pred_Tp>
		struct partition<Tup<>, Tup<L_Ts...>, Tup<R_Ts...>, Pred_Tp> { using type = Tup<L_Ts..., R_Ts...>; };
	}

	template<typename Tup, TUPLE_UTIL_PREDICATE ... Pred_Tps>
	using partition = details::partition<Tup, clear_t<Tup>, clear_t<Tup>, Pred_Tps...>;
	
	template<TUPLE_UTIL_PREDICATE ... Pred_Tps>
	struct partition_ { 
		template<typename Tup> using type = partition<Tup, Pred_Tps...>;
		template<typename Tup> using inv =  partition<Tup, pred::negate_<Pred_Tps>::template type...>;
	};
	
	template<typename Tup, TUPLE_UTIL_PREDICATE ... Pred_Tps>
	using partition_t = typename partition<Tup, Pred_Tps...>::type;



	namespace details {
		template<typename Tup, typename Out, TUPLE_UTIL_PREDICATE ... Pred_Tp>
		struct find_if;

		template<TUPLE_UTIL_CONTAINER Tup, typename T, typename ... Ts, typename ... Os, TUPLE_UTIL_PREDICATE Pred_Tp, TUPLE_UTIL_PREDICATE ... Pred_Tps>
			requires (!Pred_Tp<T>::value)
		struct find_if<Tup<T, Ts...>, Tup<Os...>, Pred_Tp, Pred_Tps...> : find_if<Tup<Ts...>, Tup<Os..., T>, Pred_Tp, Pred_Tps...> { };
	
		template<TUPLE_UTIL_CONTAINER Tup, typename T, typename ... Ts, typename ... Os, TUPLE_UTIL_PREDICATE Pred_Tp, TUPLE_UTIL_PREDICATE ... Pred_Tps>
			requires (Pred_Tp<T>::value)
		struct find_if<Tup<T, Ts...>, Tup<Os...>, Pred_Tp, Pred_Tps...> { using type = T; static constexpr std::size_t value = sizeof...(Os); };

		template<TUPLE_UTIL_CONTAINER Tup, typename ... Os, TUPLE_UTIL_PREDICATE Pred_Tp, TUPLE_UTIL_PREDICATE ... Pred_Tps>	
		struct find_if<Tup<>, Tup<Os...>, Pred_Tp, Pred_Tps...> : find_if<Tup<Os...>, Tup<>, Pred_Tps...> { };

		template<TUPLE_UTIL_CONTAINER Tup, typename ... Os, TUPLE_UTIL_PREDICATE Pred_Tp>	
		struct find_if<Tup<>, Tup<Os...>, Pred_Tp> { static constexpr std::size_t value = sizeof...(Os); };
	}
	
	template<typename Tup, TUPLE_UTIL_PREDICATE ... Pred_Tps>
	using find_if = details::find_if<Tup, clear_t<Tup>, Pred_Tps...>;
	
	template<TUPLE_UTIL_PREDICATE ... Pred_Tps>
	struct find_if_ { template<typename Tup> using type = find_if<Tup, Pred_Tps...>; };
	
	template<typename Tup, TUPLE_UTIL_PREDICATE ... Pred_Tps>
	using find_if_t = typename find_if<Tup, Pred_Tps...>::type;

	template<typename Tup, TUPLE_UTIL_PREDICATE ... Pred_Tps>
	static constexpr unsigned int find_if_v = find_if<Tup, Pred_Tps...>::value;
	


	template<typename Tup, typename T, TUPLE_UTIL_COMPARE Cmp_T=TUPLE_UTIL_DEFAULT_COMPARE>
	using find = details::find_if<Tup, clear_t<Tup>, cmp::to_<T, Cmp_T>::template type>;

	template<typename T, TUPLE_UTIL_COMPARE Cmp_T>
	struct find_ {
		template<typename Tup> using type = find<Tup, clear_t<Tup>, cmp::to_<T, Cmp_T>::template type>;
		template<typename Tup> using inv = details::find_if<Tup, clear_t<Tup>, cmp::to_<T, Cmp_T>::template inv>;
	};

	template<typename Tup, typename T, TUPLE_UTIL_COMPARE Cmp_T=TUPLE_UTIL_DEFAULT_COMPARE>
	using find_t = typename find<Tup, T, Cmp_T>::type;

	template<typename Tup, typename T, TUPLE_UTIL_COMPARE Cmp_T=TUPLE_UTIL_DEFAULT_COMPARE>
	static constexpr unsigned int find_v = find<Tup, T, Cmp_T>::value;
	


	namespace details {
		template<typename Tup, TUPLE_UTIL_ATTRIBUTER Get_Tp, typename M_type, std::size_t M_value, std::size_t N>
		struct min;

		template<TUPLE_UTIL_CONTAINER Tup, typename T, typename ... Ts, TUPLE_UTIL_ATTRIBUTER Get_Tp, typename M_type, std::size_t M_value, std::size_t N>
			requires(Get_Tp<T>::value < Get_Tp<M_type>::value)
		struct min<Tup<T, Ts...>, Get_Tp, M_type, M_value, N> : min<Tup<Ts...>, Get_Tp, T, N, N + 1> { };

		template<TUPLE_UTIL_CONTAINER Tup, typename T, typename ... Ts, TUPLE_UTIL_ATTRIBUTER Get_Tp, typename M_type, std::size_t M_value, std::size_t N>
			requires(!(Get_Tp<T>::value < Get_Tp<M_type>::value))
		struct min<Tup<T, Ts...>, Get_Tp, M_type, M_value, N> : min<Tup<Ts...>, Get_Tp, M_type, M_value, N + 1> { };

		template<TUPLE_UTIL_CONTAINER Tup, TUPLE_UTIL_ATTRIBUTER Get_Tp, typename M_type, std::size_t M_value, std::size_t N>
		struct min<Tup<>, Get_Tp, M_type, M_value, N> { using type = M_type; static constexpr auto value = M_value; };
	}
	template<typename Tup, TUPLE_UTIL_ATTRIBUTER Get_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	struct min;

	template<TUPLE_UTIL_CONTAINER Tup, typename T, typename ... Ts, TUPLE_UTIL_ATTRIBUTER Get_Tp>
	struct min<Tup<T, Ts...>, Get_Tp> : details::min<Tup<Ts...>, Get_Tp, T, 0, 1> { };

	template<TUPLE_UTIL_ATTRIBUTER Get_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	struct min_ { template<typename Tup> using type = min<Tup, Get_Tp>; };

	template<typename Tup, TUPLE_UTIL_ATTRIBUTER Get_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	using min_t = typename min<Tup, Get_Tp>::type;

	template<typename Tup, TUPLE_UTIL_ATTRIBUTER Get_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	static constexpr std::size_t min_v = min<Tup, Get_Tp>::value;



	namespace details {
		template<typename Tup, TUPLE_UTIL_ATTRIBUTER Get_Tp, typename M_type, std::size_t M_value, std::size_t N>
		struct max;

		template<TUPLE_UTIL_CONTAINER Tup, typename T, typename ... Ts, TUPLE_UTIL_ATTRIBUTER Get_Tp, typename M_type, std::size_t M_value, std::size_t N>
			requires(Get_Tp<T>::value > Get_Tp<M_type>::value)
		struct max<Tup<T, Ts...>, Get_Tp, M_type, M_value, N> : max<Tup<Ts...>, Get_Tp, T, N, N + 1> { };

		template<TUPLE_UTIL_CONTAINER Tup, typename T, typename ... Ts, TUPLE_UTIL_ATTRIBUTER Get_Tp, typename M_type, std::size_t M_value, std::size_t N>
			requires(!(Get_Tp<T>::value > Get_Tp<M_type>::value))
		struct max<Tup<T, Ts...>, Get_Tp, M_type, M_value, N> : max<Tup<Ts...>, Get_Tp, M_type, M_value, N + 1> { };

		template<TUPLE_UTIL_CONTAINER Tup, TUPLE_UTIL_ATTRIBUTER Get_Tp, typename M_type, std::size_t M_value, std::size_t N>
		struct max<Tup<>, Get_Tp, M_type, M_value, N> { using type = M_type; static constexpr auto value = M_value; };
	}
	template<typename Tup, TUPLE_UTIL_ATTRIBUTER Get_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	struct max;

	template<TUPLE_UTIL_CONTAINER Tup, typename T, typename ... Ts, TUPLE_UTIL_ATTRIBUTER Get_Tp>
	struct max<Tup<T, Ts...>, Get_Tp> : details::max<Tup<Ts...>, Get_Tp, T, 0, 1> { };

	template<TUPLE_UTIL_ATTRIBUTER Get_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	struct max_ { template<typename Tup> using type = max<Tup, Get_Tp>; };

	template<typename Tup, TUPLE_UTIL_ATTRIBUTER Get_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	using max_t = typename max<Tup, Get_Tp>::type;

	template<typename Tup, TUPLE_UTIL_ATTRIBUTER Get_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	static constexpr std::size_t max_v = max<Tup, Get_Tp>::value;
	



	template<typename Tup, TUPLE_UTIL_COMPARE LT_T>
	struct sort;

	template<typename Tup, TUPLE_UTIL_COMPARE LT_T>
	using sort_t = typename sort<Tup, LT_T>::type;

	template<TUPLE_UTIL_CONTAINER Tup, typename Pivot_T, typename ... Ts, TUPLE_UTIL_COMPARE Cmp_T>
	struct sort<Tup<Pivot_T, Ts...>, Cmp_T> : concat<TUPLE_UTIL_DEFAULT_CONTAINER<
		sort_t<filter_t<Tup<Ts...>, cmp::to_<Pivot_T, Cmp_T>::template inv>,  Cmp_T>, Tup<Pivot_T>, // not less than
		sort_t<filter_t<Tup<Ts...>, cmp::to_<Pivot_T, Cmp_T>::template type>, Cmp_T>>> 				// less than
	{ };

	template<TUPLE_UTIL_CONTAINER Tup, TUPLE_UTIL_COMPARE Cmp_T>
	struct sort<Tup<>, Cmp_T> {
		using type = Tup<>;
	};

	template<TUPLE_UTIL_COMPARE LT_T>
	struct sort_ { template<typename Tup> using type = sort<Tup, LT_T>; };

	template<typename Tup, TUPLE_UTIL_ATTRIBUTER ... Get_Ts>
	using sort_by = sort<Tup, cmp::attrib_<Get_Ts...>::template type>;

	template<typename Tup, TUPLE_UTIL_ATTRIBUTER ... Get_Ts>
	using sort_by_t = typename sort<Tup, cmp::attrib_<Get_Ts...>::template type>::type;

	template<TUPLE_UTIL_ATTRIBUTER ... Get_Ts>
	using sort_by_ = sort_<cmp::attrib_<Get_Ts...>::template type>;



	template<typename Tup, TUPLE_UTIL_COMPARE Same_T=TUPLE_UTIL_DEFAULT_COMPARE>
	struct unique;

	template<typename Tup, TUPLE_UTIL_COMPARE Same_T=TUPLE_UTIL_DEFAULT_COMPARE>
	using unique_t = typename unique<Tup, Same_T>::type;

	template<TUPLE_UTIL_CONTAINER Tup, typename T, typename ... Ts, TUPLE_UTIL_COMPARE Same_T>
	struct unique<Tup<T, Ts...>, Same_T> : concat<TUPLE_UTIL_DEFAULT_CONTAINER<Tup<T>, typename unique<filter_t<Tup<Ts...>, cmp::to_<T, Same_T>::template inv>, Same_T>::type>>
	{ };

	template<TUPLE_UTIL_CONTAINER Tup, TUPLE_UTIL_COMPARE Same_T>
	struct unique<Tup<>, Same_T> { using type = Tup<>; };

	template<TUPLE_UTIL_COMPARE Same_T=TUPLE_UTIL_DEFAULT_COMPARE>
	struct unique_ { template<typename Tup> using type = unique<Tup, Same_T>; };



	template<typename Tup, TUPLE_UTIL_COMPARE Same_T, TUPLE_UTIL_COMPARE Priority_T>
	struct unique_priority : unique<sort_t<Tup, Priority_T>, Same_T> { };

	template<typename Tup, TUPLE_UTIL_COMPARE Same_T, TUPLE_UTIL_COMPARE Priority_T>
	using unique_priority_t = typename unique_priority<Tup, Same_T, Priority_T>::type;

	template<TUPLE_UTIL_COMPARE Same_T, TUPLE_UTIL_COMPARE Priority_T>
	struct unique_priority_ { template<typename Tup> using type = unique_priority<Tup, Same_T, Priority_T>; };



	template<typename Tup1, typename Tup2, TUPLE_UTIL_COMPARE Same_T = TUPLE_UTIL_DEFAULT_COMPARE>
	struct set_union;

	template<typename Tup, typename Set_T, TUPLE_UTIL_COMPARE Same_T = TUPLE_UTIL_DEFAULT_COMPARE>
	using set_union_t = typename set_union<Tup, Set_T, Same_T>::type;

	template<typename Tup1, typename Tup2, TUPLE_UTIL_COMPARE Same_T>
	struct set_union : unique<concat_t<TUPLE_UTIL_DEFAULT_CONTAINER<Tup1, Tup2>>, Same_T> { };

	template<typename Set_T, TUPLE_UTIL_COMPARE Same_T = TUPLE_UTIL_DEFAULT_COMPARE>
	struct set_union_ { template<typename Tup> using type = set_union<Tup, Set_T, Same_T>; };



	
	template<typename Tup1, typename Tup2, TUPLE_UTIL_COMPARE Same_T = TUPLE_UTIL_DEFAULT_COMPARE>
	struct set_intersect;

	template<typename Tup, typename Set_T, TUPLE_UTIL_COMPARE Same_T = TUPLE_UTIL_DEFAULT_COMPARE>
	using set_intersect_t = typename set_intersect<Tup, Set_T, Same_T>::type;

	template<typename Tup1, typename Tup2, TUPLE_UTIL_COMPARE Same_T>
	struct set_intersect : filter<set_union_t<Tup1, Tup2, Same_T>, pred::conj_<
		pred::element_of_<Tup1, Same_T>::template type,
		pred::element_of_<Tup2, Same_T>::template type
	>::template type> { };

	template<typename Set_T, TUPLE_UTIL_COMPARE Same_T=TUPLE_UTIL_DEFAULT_COMPARE>
	struct set_intersect_ {
		template<typename Tup> using type = set_intersect<Tup, Set_T, Same_T>;
		template<typename Tup> using inv =  set_intersect<Tup, Set_T, cmp::negate_<Same_T>::template type>;
	};
}

// [ ] subset/superset
namespace TUPLE_UTIL_NAMESPACE::pred {
	template<typename SubSet_T, typename SuperSet_T, TUPLE_UTIL_COMPARE Same_T=TUPLE_UTIL_DEFAULT_COMPARE>
	struct is_subset : allof<SubSet_T, element_of_<SuperSet_T, Same_T>::template type> { };
	template<typename SubSet_T, typename SuperSet_T, TUPLE_UTIL_COMPARE Same_T=TUPLE_UTIL_DEFAULT_COMPARE>
	static constexpr bool is_subset_v = is_subset<SubSet_T, SuperSet_T, Same_T>::value;
	template<typename SuperSet_T, TUPLE_UTIL_COMPARE Same_T=TUPLE_UTIL_DEFAULT_COMPARE>
	struct is_subset_ {
		template<typename SubSet_T> using type = is_subset<SubSet_T, SuperSet_T, Same_T>;
		template<typename SubSet_T> using inv =  std::negation<type<SubSet_T>>;
	};

	template<typename SuperSet_T, typename SubSet_T, TUPLE_UTIL_COMPARE Same_T=TUPLE_UTIL_DEFAULT_COMPARE>
	struct is_superset : allof<SuperSet_T, element_of_<SubSet_T, Same_T>::template type> { };
	template<typename SuperSet_T, typename SubSet_T, TUPLE_UTIL_COMPARE Same_T=TUPLE_UTIL_DEFAULT_COMPARE>
	static constexpr bool is_superset_v = is_superset<SuperSet_T, SubSet_T, Same_T>::value;
	template<typename SubSet_T, TUPLE_UTIL_COMPARE Same_T=TUPLE_UTIL_DEFAULT_COMPARE>
	struct is_superset_ {
		template<typename SuperSet_T> using type = is_superset<SuperSet_T, SubSet_T, Same_T>;
		template<typename SuperSet_T> using inv =  std::negation<type<SuperSet_T>>;
	};
}

namespace TUPLE_UTIL_NAMESPACE::cmp {
	template<typename T1, typename T2, TUPLE_UTIL_COMPARE Cmp_T=TUPLE_UTIL_DEFAULT_COMPARE>
	struct is_same_set;
	template<typename T1, typename T2, TUPLE_UTIL_COMPARE Cmp_T=TUPLE_UTIL_DEFAULT_COMPARE>
	static constexpr bool is_same_set_v = is_same_set<T1, T2, Cmp_T>::value;

	template<TUPLE_UTIL_CONTAINER Tup1, typename ... T1s, TUPLE_UTIL_CONTAINER Tup2, typename ... T2s, TUPLE_UTIL_COMPARE Cmp_T>
	struct is_same_set<Tup1<T1s...>, Tup2<T2s...>, Cmp_T> {
		static constexpr bool value = (sizeof...(T1s) == sizeof...(T2s)) && (pred::element_of_v<T1s, Tup2<T2s...>, Cmp_T> && ...);
	};

	template<typename Tup1, TUPLE_UTIL_COMPARE Cmp_T=TUPLE_UTIL_DEFAULT_COMPARE>
	struct is_same_set_ {
		template<typename Tup2> using type = is_same_set<Tup1, Tup2, Cmp_T>;
		template<typename Tup2> using inv = std::negation<type<Tup2>>;
	};
}