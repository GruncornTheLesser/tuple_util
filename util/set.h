#pragma once
#include "tuple_util.h"
#include "compare.h"
#include "predicate.h"

namespace util {
	template<typename Tup> 
	struct concat;

	template<typename Tup> 
	using concat_t = typename concat<Tup>::type;
	
	template<CONTAINER TupleSet_T, CONTAINER Tup1, CONTAINER Tup2, typename ... T1s, typename ... T2s, typename ... Ts> 
	struct concat<TupleSet_T<Tup1<T1s...>, Tup2<T2s...>, Ts...>>
	 : concat<TupleSet_T<Tup1<T1s..., T2s...>, Ts...>> { };
	
	template<CONTAINER TupleSet_T, CONTAINER Tup, typename ... Ts> 
	struct concat<TupleSet_T<Tup<Ts...>>> { using type = Tup<Ts...>; };
	
	template<CONTAINER TupleSet_T> 
	struct concat<TupleSet_T<>> { using type = std::tuple<>; };



	template<typename Tup, typename T> 
	struct append;
	
	template<CONTAINER Tup, typename ... Ts, typename T> 
	struct append<Tup<Ts...>, T> { using type = Tup<Ts..., T>; };

	template<typename T> struct append_ 
	{ template<typename Tup> using type = append<Tup, T>; };

	template<typename Tup, typename T> 
	using append_t = typename append<Tup, T>::type;



	template<typename Tup, typename T> 
	using prepend = concat<std::tuple<std::tuple<T>, Tup>>;

	template<typename T> struct prepend_ 
	{ template<typename Tup> using type = prepend<Tup, T>; };

	template<typename Tup, typename T> 
	using prepend_t = typename prepend<Tup, T>::type;



	template<typename Tup> 
	struct pop_front;
	
	template<CONTAINER Tup, typename T, typename ... Ts>
	struct pop_front<Tup<T, Ts...>> { using type = Tup<Ts...>; };
	
	template<typename Tup> 
	using pop_front_t = typename pop_front<Tup>::type;



	template<typename Tup> 
	struct pop_back;
	
	template<CONTAINER Tup, typename T> 
	struct pop_back<Tup<T>> { using type = std::tuple<>; };

	template<CONTAINER Tup, typename T, typename ... Ts>
	struct pop_back<Tup<T, Ts...>> { using type = append<T, pop_back<Ts...>>; };
	
	template<typename Tup> 
	using pop_back_t = typename pop_back<Tup>::type;



	template<typename Tup> 
	struct get_front;
	
	template<CONTAINER Tup, typename T, typename ... Ts>
	struct get_front<Tup<T, Ts...>> { using type = T; };
	
	template<typename Tup> 
	using get_front_t = typename get_front<Tup>::type;



	template<typename Tup> 
	struct get_back;
	
	template<CONTAINER Tup, typename T> 
	struct get_back<Tup<T>> { using type = T; };
	
	template<CONTAINER Tup, typename ... Ts, typename T>
	struct get_back<Tup<T, Ts...>> : get_back<Tup<Ts...>> { };
	
	template<typename Tup> 
	using get_back_t = typename get_back<Tup>::type;



	template<typename Tup, PREDICATE Pred_T> 
	struct filter;
	
	template<PREDICATE Pred_T>
	struct filter_;
	
	template<typename Tup, PREDICATE Pred_T>
	using filter_t = typename filter<Tup, Pred_T>::type;
	
	template<CONTAINER Tup, typename ... Ts, PREDICATE Pred_T> 
	struct filter<Tup<Ts...>, Pred_T>
	 : concat<std::tuple<Tup<>, std::conditional_t<Pred_T<Ts>::value, Tup<Ts>, Tup<>>...>> { };
	
	template<PREDICATE Pred_T> 
	struct filter_ 
	{ template<typename Tup> using type = filter<Tup, Pred_T>; };



	template<typename Tup, PREDICATE Pred_T, int index=0, typename=void> 
	struct find;
	
	template<PREDICATE Pred_T>
	struct find_;

	template<typename Tup, PREDICATE Pred_T> 
	using find_t = typename find<Tup, Pred_T>::type;

	template<typename Tup, PREDICATE Pred_T> 
	static constexpr int find_v = find<Tup, Pred_T>::value;

	template<CONTAINER Tup, typename T, typename ... Ts, PREDICATE Pred_T, int index>
	struct find<Tup<T, Ts...>, Pred_T, index, std::enable_if_t<Pred_T<T>::value>>
	 : std::type_identity<T> { static constexpr int value = index; };

	template<CONTAINER Tup, typename T, typename ... Ts, PREDICATE Pred_T, int index>
	struct find<Tup<T, Ts...>, Pred_T, index, std::enable_if_t<!Pred_T<T>::value>>
	 : find<Tup<Ts...>, Pred_T, index + 1> { };

	template<CONTAINER Tup, PREDICATE Pred_T, int index>
	struct find<Tup<>, Pred_T, index, void>
	 : std::type_identity<void> { };

	template<PREDICATE Pred_T> 
	struct find_ { template<typename Tup> using type = find<Tup, Pred_T>; };



	template<typename Tup, COMPARE Cmp_T, typename=void>
	struct find_most;

	template<typename Tup, COMPARE Cmp_T, typename=void>
	using find_most_t = typename find_most<Tup, Cmp_T>::type;
	
	template<CONTAINER Tup, typename T1, typename T2, typename ... Ts, COMPARE Cmp_T>
	struct find_most<Tup<T1, T2, Ts...>, Cmp_T, std::enable_if_t<Cmp_T<T1, T2>::value>>
	 : find_most<Tup<T2, Ts...>, Cmp_T> { };

	template<CONTAINER Tup, typename T1, typename T2, typename ... Ts, COMPARE Cmp_T>
	struct find_most<Tup<T1, T2, Ts...>, Cmp_T, std::enable_if_t<!Cmp_T<T1, T2>::value>>
	 : find_most<Tup<T1, Ts...>, Cmp_T> { };

	template<CONTAINER Tup, typename T, COMPARE Cmp_T>
	struct find_most<Tup<T>, Cmp_T> : std::type_identity<T> { };
	
	template<COMPARE Cmp_T>
	struct find_most_ { template<typename Tup> using type = find_most<Tup, Cmp_T>; };



	template<typename Tup, TRANSFORM Get_T, typename=void>
	struct find_min;

	template<typename Tup, TRANSFORM Get_T, typename=void>
	using find_min_t = typename find_min<Tup, Get_T>::type;
	
	template<CONTAINER Tup, typename T1, typename T2, typename ... Ts, TRANSFORM Get_T>
	struct find_min<Tup<T1, T2, Ts...>, Get_T, std::enable_if_t<(Get_T<T1>::value > Get_T<T2>::value)>>
	 : find_min<Tup<T2, Ts...>, Get_T> { };

	template<CONTAINER Tup, typename T1, typename T2, typename ... Ts, TRANSFORM Get_T>
	struct find_min<Tup<T1, T2, Ts...>, Get_T, std::enable_if_t<(Get_T<T1>::value <= Get_T<T2>::value)>>
	 : find_min<Tup<T1, Ts...>, Get_T> { };

	template<CONTAINER Tup, typename T, TRANSFORM Get_T>
	struct find_min<Tup<T>, Get_T> : std::type_identity<T> { };
	
	template<TRANSFORM Get_T>
	struct find_min_ { template<typename Tup> using type = find_min<Tup, Get_T>; };

	

	template<typename Tup, TRANSFORM Get_T, typename=void>
	struct find_max;

	template<typename Tup, TRANSFORM Get_T, typename=void>
	using find_max_t = typename find_max<Tup, Get_T>::type;
	
	template<CONTAINER Tup, typename T1, typename T2, typename ... Ts, TRANSFORM Get_T>
	struct find_max<Tup<T1, T2, Ts...>, Get_T, std::enable_if_t<(Get_T<T1>::value < Get_T<T2>::value)>>
	 : find_max<Tup<T2, Ts...>, Get_T> { };

	template<CONTAINER Tup, typename T1, typename T2, typename ... Ts, TRANSFORM Get_T>
	struct find_max<Tup<T1, T2, Ts...>, Get_T, std::enable_if_t<(Get_T<T1>::value >= Get_T<T2>::value)>>
	 : find_max<Tup<T1, Ts...>, Get_T> { };

	template<CONTAINER Tup, typename T, TRANSFORM Get_T>
	struct find_max<Tup<T>, Get_T> : std::type_identity<T> { };
	
	template<TRANSFORM Get_T>
	struct find_max_ { template<typename Tup> using type = find_max<Tup, Get_T>; };



	template<typename Tup, COMPARE LT_T> 
	struct sort;
	
	template<COMPARE LT_T> 
	struct sort_;
	
	template<typename Tup, COMPARE LT_T> 
	using sort_t = typename sort<Tup, LT_T>::type;

	template<CONTAINER Tup, typename Pivot_T, typename ... Ts, COMPARE Cmp_T>
	struct sort<Tup<Pivot_T, Ts...>, Cmp_T> : concat<std::tuple<
		sort_t<filter_t<Tup<Ts...>, cmp::to_<Pivot_T, Cmp_T>::template negated>, Cmp_T>, Tup<Pivot_T>, // not less than
		sort_t<filter_t<Tup<Ts...>, cmp::to_<Pivot_T, Cmp_T>::template type>, Cmp_T>>> // less than
	{ };
	
	template<CONTAINER Tup, COMPARE Cmp_T>
	struct sort<Tup<>, Cmp_T> {
		using type = Tup<>;
	};

	template<COMPARE LT_T>
	struct sort_ { template<typename Tup> using type = sort<Tup, LT_T>; }; 


	
	template<typename Tup, COMPARE Same_T=std::is_same>
	struct unique;
	
	template<COMPARE Same_T=std::is_same>
	struct unique_;

	template<typename Tup, COMPARE Same_T=std::is_same>
	using unique_t = typename unique<Tup, Same_T>::type;

	template<CONTAINER Tup, typename T, typename ... Ts, COMPARE Same_T>
	struct unique<Tup<T, Ts...>, Same_T> : concat<std::tuple<Tup<T>, typename unique<filter_t<std::tuple<Ts...>, 
		cmp::to_<T, Same_T>::template negated>, Same_T>::type>>
	{ };

	template<CONTAINER Tup, COMPARE Same_T>
	struct unique<Tup<>, Same_T> { using type = Tup<>; };

	template<COMPARE Same_T>
	struct unique_ { template<typename Tup> using type = unique<Tup, Same_T>; };



	template<typename Tup, COMPARE Same_T, COMPARE Priority_T>
	struct unique_priority : unique<sort_t<Tup, Priority_T>, Same_T> { };

	template<COMPARE Same_T, COMPARE Priority_T>
	struct unique_priority_ { template<typename Tup> using type = unique_priority<Tup, Same_T, Priority_T>; };
	
	template<typename Tup, COMPARE Same_T, COMPARE Priority_T>
	using unique_priority_t = typename unique_priority<Tup, Same_T, Priority_T>::type;
	

	// TODO integrate unique into set_union
	template<typename Tup1, typename Tup2 = std::tuple<>, COMPARE Same_T = std::is_same> 
	struct set_union;
	
	template<typename Tup1, COMPARE Same_T>
	struct set_union_;

	template<typename Tup, typename Set_T, COMPARE Same_T = std::is_same> 
	using set_union_t = typename set_union<Tup, Set_T, Same_T>::type;
	
	template<typename Tup1, typename Tup2, COMPARE Same_T>
	struct set_union : unique<concat_t<std::tuple<Tup1, Tup2>>, Same_T> { };
	
	template<typename Set_T, COMPARE Same_T = std::is_same> 
	struct set_union_ { template<typename Tup> using type = set_union<Tup, Set_T, Same_T>; };



	// TODO doesnt remove duplicate
	template<typename Tup1, typename Tup2, COMPARE Same_T = std::is_same> 
	struct set_intersect;

	template<COMPARE Same_T, typename Set_T> 
	struct set_intersect_ { template<typename Tup> using type = set_intersect<Tup, Set_T, Same_T>; };
	
	template<typename Tup, typename Set_T, COMPARE Same_T = std::is_same> 
	using set_intersect_t = typename set_intersect<Tup, Set_T, Same_T>::type;
	
	template<typename Tup1, typename Tup2, COMPARE Same_T>
	struct set_intersect : filter<set_union_t<Tup1, Tup2, Same_T>,	pred::conj_<
		pred::element_of_<Tup1, Same_T>::template type, 
		pred::element_of_<Tup2, Same_T>::template type
	>::template type> { };

}

// [ ] subset - pred set
namespace util::pred {
	template<typename SubSet_T, typename SuperSet_T, COMPARE Cmp_T=std::is_same>
	struct is_subset : allof<SubSet_T, element_of_<SuperSet_T, Cmp_T>::template type> { };
	template<typename SubSet_T, typename SuperSet_T, COMPARE Cmp_T=std::is_same>
	static constexpr bool is_subset_v = is_subset<SubSet_T, SuperSet_T, Cmp_T>::value;
	template<typename SuperSet_T, COMPARE Cmp_T=std::is_same>
	struct is_subset_ { template<typename SubSet_T> using type = is_subset<SubSet_T, SuperSet_T, Cmp_T>; };
}