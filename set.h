#pragma once
#include "macro.h"
#include "compare.h"
#include "predicate.h"
#include "decorators.h"

namespace util {
	template<typename Tup>
	struct concat;

	template<typename Tup>
	using concat_t = typename concat<Tup>::type;

	template<CONTAINER Set_T, CONTAINER Tup1, typename ... T1s, CONTAINER Tup2, typename ... T2s, typename ... Tups>
	struct concat<Set_T<Tup1<T1s...>, Tup2<T2s...>, Tups...>> : concat<Set_T<Tup1<T1s..., T2s...>, Tups...>> { };

	template<CONTAINER Set_T, CONTAINER Tup, typename ... Ts>
	struct concat<Set_T<Tup<Ts...>>> : std::type_identity<Tup<Ts...>> { };

	template<CONTAINER Set_T>
	struct concat<Set_T<>> : std::type_identity<Set_T<>> { };



	template<typename Tup>
	struct reverse;

	template<typename Tup>
	using reverse_t = typename reverse<Tup>::type;

	template<CONTAINER Tup, typename ... Ts, typename T>
	struct reverse<Tup<Ts..., T>> : concat<std::tuple<Tup<T>, typename reverse<Ts...>::type>> { };

	template<CONTAINER Tup>
	struct reverse<Tup<>> : std::type_identity<Tup<>> { };



	template<typename Tup, typename T>
	using append = concat<std::tuple<Tup, std::tuple<T>>>;

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
	struct pop_front : copy_cvref<typename pop_front<std::remove_cvref_t<Tup>>::type, Tup> { };

	template<CONTAINER Tup, typename T, typename ... Ts>
	struct pop_front<Tup<T, Ts...>> { using type = Tup<Ts...>; };
	
	template<CONTAINER Tup>
	struct pop_front<Tup<>> : std::type_identity<void> { };

	template<typename Tup>
	using pop_front_t = typename pop_front<Tup>::type;



	template<typename Tup>
	struct pop_back : copy_cvref<typename pop_back<std::remove_cvref_t<Tup>>::type, Tup> { };

	template<CONTAINER Tup, typename T>
	struct pop_back<Tup<T>> { using type = std::tuple<>; };

	template<CONTAINER Tup, typename T, typename ... Ts>
	struct pop_back<Tup<T, Ts...>> { using type = append<T, pop_back<Ts...>>; };

	template<CONTAINER Tup>
	struct pop_back<Tup<>> : std::type_identity<void> { };

	template<typename Tup>
	using pop_back_t = typename pop_back<Tup>::type;



	template<typename Tup>
	struct get_front : get_front<std::remove_cvref_t<Tup>> { };

	template<CONTAINER Tup, typename T, typename ... Ts>
	struct get_front<Tup<T, Ts...>> { using type = T; };

	template<CONTAINER Tup>
	struct get_front<Tup<>> : std::type_identity<void> { };

	template<typename Tup>
	using get_front_t = typename get_front<Tup>::type;



	template<typename Tup>
	struct get_back : get_back<std::remove_cvref_t<Tup>> { };

	template<CONTAINER Tup, typename T>
	struct get_back<Tup<T>> { using type = T; };

	template<CONTAINER Tup, typename ... Ts, typename T>
	struct get_back<Tup<T, Ts...>> : get_back<Tup<Ts...>> { };
	
	template<CONTAINER Tup>
	struct get_back<Tup<>> : std::type_identity<void> { };

	template<typename Tup>
	using get_back_t = typename get_back<Tup>::type;



	template<typename Tup, PREDICATE Pred_T>
	struct filter : copy_cvref<typename filter<std::remove_cvref_t<Tup>, Pred_T>::type, Tup> { };

	template<typename Tup, PREDICATE Pred_T>
	using filter_t = typename filter<Tup, Pred_T>::type;

	template<CONTAINER Tup, typename ... Ts, PREDICATE Pred_T>
	struct filter<Tup<Ts...>, Pred_T>
	 : concat<std::tuple<Tup<>, std::conditional_t<Pred_T<Ts>::value, Tup<Ts>, Tup<>>...>> { };

	template<PREDICATE Pred_T>
	struct filter_
	{ 
		template<typename Tup> using type = filter<Tup, Pred_T>;
		template<typename Tup> using inverse = filter<Tup, util::pred::negate_<Pred_T>::template type>;
	};



	template<typename Tup, PREDICATE Pred_T, unsigned int I=0, typename=std::void_t<>>
	struct find : copy_cvref<typename find<std::remove_cv_t<Tup>, Pred_T, I>::type, Tup> { };

	template<typename Tup, PREDICATE Pred_T>
	using find_t = typename find<Tup, Pred_T>::type;

	template<typename Tup, PREDICATE Pred_T>
	static constexpr unsigned int find_v = find<Tup, Pred_T>::value;

	template<CONTAINER Tup, typename T, typename ... Ts, PREDICATE Pred_T, unsigned int I>
	struct find<Tup<T, Ts...>, Pred_T, I, std::enable_if_t<Pred_T<T>::value>> : std::type_identity<T>, std::integral_constant<unsigned int, I> { };

	template<CONTAINER Tup, typename T, typename ... Ts, PREDICATE Pred_T, unsigned int I>
	struct find<Tup<T, Ts...>, Pred_T, I, std::enable_if_t<!Pred_T<T>::value>> : find<Tup<Ts...>, Pred_T, I + 1> { };

	template<CONTAINER Tup, PREDICATE Pred_T, unsigned int I>
	struct find<Tup<>, Pred_T, I, void> : std::type_identity<void>, std::integral_constant<unsigned int, I> { };

	template<PREDICATE Pred_T>
	struct find_ { template<typename Tup> using type = find<Tup, Pred_T>; };



	template<typename Tup, COMPARE Cmp_T, typename=void>
	struct find_most : copy_cvref<typename find_most<std::remove_cvref_t<Tup>, Cmp_T>::type, Tup> { };

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
	struct find_min : copy_cvref<typename find_min<std::remove_cvref_t<Tup>, Get_T>::type, Tup> { };

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
	struct find_max : copy_cvref<typename find_max<std::remove_cvref_t<Tup>, Get_T>::type, Tup> { };

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
	struct sort : copy_cvref<typename sort<std::remove_cvref_t<Tup>, LT_T>::type, Tup> { };

	template<typename Tup, COMPARE LT_T>
	using sort_t = typename sort<Tup, LT_T>::type;

	template<CONTAINER Tup, typename Pivot_T, typename ... Ts, COMPARE Cmp_T>
	struct sort<Tup<Pivot_T, Ts...>, Cmp_T> : concat<std::tuple<
		sort_t<filter_t<Tup<Ts...>, cmp::to_<Pivot_T, Cmp_T>::template inverse>, Cmp_T>, Tup<Pivot_T>, // not less than
		sort_t<filter_t<Tup<Ts...>, cmp::to_<Pivot_T, Cmp_T>::template type>, Cmp_T>>> // less than
	{ };

	template<CONTAINER Tup, COMPARE Cmp_T>
	struct sort<Tup<>, Cmp_T> {
		using type = Tup<>;
	};

	template<COMPARE LT_T>
	struct sort_ { template<typename Tup> using type = sort<Tup, LT_T>; };

	template<typename Tup, ATTRIBUTER ... Get_Ts>
	using sort_by = sort<Tup, cmp::attrib_<Get_Ts...>::template type>;

	template<typename Tup, ATTRIBUTER ... Get_Ts>
	using sort_by_t = typename sort<Tup, cmp::attrib_<Get_Ts...>::template type>::type;

	template<ATTRIBUTER ... Get_Ts>
	using sort_by_ = sort_<cmp::attrib_<Get_Ts...>::template type>;



	template<typename Tup, COMPARE Same_T=std::is_same>
	struct unique : copy_cvref<typename unique<std::remove_cvref_t<Tup>, Same_T>::type, Tup> { };

	template<typename Tup, COMPARE Same_T=std::is_same>
	using unique_t = typename unique<Tup, Same_T>::type;

	template<CONTAINER Tup, typename T, typename ... Ts, COMPARE Same_T>
	struct unique<Tup<T, Ts...>, Same_T> : concat<std::tuple<Tup<T>, typename unique<filter_t<std::tuple<Ts...>,
		cmp::to_<T, Same_T>::template inverse>, Same_T>::type>>
	{ };

	template<CONTAINER Tup, COMPARE Same_T>
	struct unique<Tup<>, Same_T> { using type = Tup<>; };

	template<COMPARE Same_T=std::is_same>
	struct unique_ { template<typename Tup> using type = unique<Tup, Same_T>; };



	template<typename Tup, COMPARE Same_T, COMPARE Priority_T>
	struct unique_priority : unique<sort_t<Tup, Priority_T>, Same_T> { };

	template<typename Tup, COMPARE Same_T, COMPARE Priority_T>
	using unique_priority_t = typename unique_priority<Tup, Same_T, Priority_T>::type;

	template<COMPARE Same_T, COMPARE Priority_T>
	struct unique_priority_ { template<typename Tup> using type = unique_priority<Tup, Same_T, Priority_T>; };



	// TODO integrate unique into set_union
	template<typename Tup1, typename Tup2 = std::tuple<>, COMPARE Same_T = std::is_same>
	struct set_union;

	template<typename Tup, typename Set_T, COMPARE Same_T = std::is_same>
	using set_union_t = typename set_union<Tup, Set_T, Same_T>::type;

	template<typename Tup1, typename Tup2, COMPARE Same_T>
	struct set_union : unique<concat_t<std::tuple<Tup1, Tup2>>, Same_T> { };

	template<typename Set_T, COMPARE Same_T = std::is_same>
	struct set_union_ { template<typename Tup> using type = set_union<Tup, Set_T, Same_T>; };



	// TODO doesnt remove duplicate
	template<typename Tup1, typename Tup2, COMPARE Same_T = std::is_same>
	struct set_intersect;

	template<typename Tup, typename Set_T, COMPARE Same_T = std::is_same>
	using set_intersect_t = typename set_intersect<Tup, Set_T, Same_T>::type;

	template<typename Tup1, typename Tup2, COMPARE Same_T>
	struct set_intersect : filter<set_union_t<Tup1, Tup2, Same_T>,	pred::conj_<
		pred::element_of_<Tup1, Same_T>::template type,
		pred::element_of_<Tup2, Same_T>::template type
	>::template type> { };

	template<COMPARE Same_T, typename Set_T>
	struct set_intersect_ {
		template<typename Tup> using type = set_intersect<Tup, Set_T, Same_T>;
		template<typename Tup> using inverse = set_intersect<Tup, Set_T, cmp::negate_<Same_T>::template type>;
	};
}

// [ ] subset - pred set
namespace util::pred {
	template<typename SubSet_T, typename SuperSet_T, COMPARE Same_T=std::is_same>
	struct is_subset : allof<SubSet_T, element_of_<SuperSet_T, Same_T>::template type> { };
	template<typename SubSet_T, typename SuperSet_T, COMPARE Same_T=std::is_same>
	static constexpr bool is_subset_v = is_subset<SubSet_T, SuperSet_T, Same_T>::value;
	template<typename SuperSet_T, COMPARE Same_T=std::is_same>
	struct is_subset_ {
		template<typename SubSet_T> using type = is_subset<SubSet_T, SuperSet_T, Same_T>;
		template<typename SubSet_T> using inverse = std::negation<type<SubSet_T>>;
	};
}