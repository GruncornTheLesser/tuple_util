#pragma once
#include "util/eval.h"
#include "util/macro.h"
#include "util/predicate.h"
#include "util/compare.h"
#include <array>
#include <algorithm>

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
	template<typename Tup> 
	struct arg_count;

	template<typename Tup> 
	static constexpr std::size_t arg_count_v = arg_count<Tup>::value;

	template<CONTAINER Tup, typename ... Ts> 
	struct arg_count<Tup<Ts...>> { static constexpr std::size_t value = sizeof...(Ts); };


	
	template<std::size_t N, typename Tup> 
	struct arg_at;

	template<std::size_t N>
	struct arg_at_ { template<typename Tup> using type = arg_at<N, Tup>; };

	template<std::size_t N, typename Tup> 
	using arg_at_t = typename arg_at<N, Tup>::type;

	template<std::size_t N, CONTAINER Tp, typename T, typename ... Ts>
	struct arg_at<N, Tp<T, Ts...>> : arg_at<N - 1u, Tp<Ts...>> { };

	template<CONTAINER Tp, typename T, typename ... Ts>
	struct arg_at<0, Tp<T, Ts...>> { using type = T; };

	
	template<typename Tup>
	using arg_front = arg_at<0, Tup>;

	template<typename Tup>
	using arg_front_t = typename arg_front<Tup>::type;


	template<typename Tup>
	using arg_back = arg_at<arg_count_v<Tup> - 1, Tup>;

	template<typename Tup>
	using arg_back_t = typename arg_back<Tup>::type;



	template<typename Tup, typename Ind>
	struct subset;

	template<typename Ind>
	struct subset_ { template<typename Tup> using type = subset<Tup, Ind>; };

	template<typename Tup, typename Ind>
	using subset_t = typename subset<Tup, Ind>::type;

	template<CONTAINER Tup, typename ... Ts, std::size_t ... Is>
	struct subset<Tup<Ts...>, std::index_sequence<Is...>> {
		using type = Tup<arg_at_t<Is, Tup<Ts...>>...>;
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

	template<CONTAINER Set_T, CONTAINER Tup1, typename ... T1s, CONTAINER Tup2, typename ... T2s, typename ... Tups>
	struct concat<Set_T<Tup1<T1s...>, Tup2<T2s...>, Tups...>> : concat<Set_T<Tup1<T1s..., T2s...>, Tups...>> { };

	template<CONTAINER Set_T, CONTAINER Tup, typename ... Ts>
	struct concat<Set_T<Tup<Ts...>>> : std::type_identity<Tup<Ts...>> { };

	template<CONTAINER Set_T>
	struct concat<Set_T<>> : std::type_identity<Set_T<>> { };


	
	namespace details {
		template<typename Tup, typename Ind = std::make_index_sequence<arg_count_v<Tup>>>
		struct reverse;

		template<CONTAINER Tup, typename ... Ts, std::size_t ... Is>
		struct reverse<Tup<Ts...>, std::index_sequence<Is...>>{ 
			using type = Tup<arg_at_t<arg_count_v<Tup<Ts...>> - Is - 1, Tup<Ts...>>...>; 
		};
	}
	
	template<typename Tup>
	using reverse = details::reverse<Tup>;

	template<typename Tup>
	using reverse_t = typename reverse<Tup>::type;



	template<typename Tup, typename ... Ts>
	struct push_back;

	template<CONTAINER Tup, typename ... Us, typename ... Ts>
	struct push_back<Tup<Us...>, Ts...> { using type = Tup<Us..., Ts...>; };

	template<typename ... Ts> struct push_back_ { 
		template<typename Tup> using type = push_back<Tup, Ts...>; 
	};

	template<typename Tup, typename ... Ts>
	using push_back_t = typename push_back<Tup, Ts...>::type;



	template<typename Tup, typename ... Ts>
	struct push_front;

	template<CONTAINER Tup, typename ... Us, typename ... Ts>
	struct push_front<Tup<Us...>, Ts...> { using type = Tup<Ts..., Us...>; };

	template<typename ... Ts> struct push_front_ { 
		template<typename Tup> using type = push_front<Tup, Ts...>; 
	};

	template<typename Tup, typename ... Ts>
	using push_front_t = typename push_front<Tup, Ts...>::type;



	template<typename Tup, std::size_t N, TRANSFORM ... Trans_Ts>
	struct eval_at;

	template<CONTAINER Tup, typename T, typename ... Ts, std::size_t N, TRANSFORM ... Trans_Ts>
	struct eval_at<Tup<T, Ts...>, N, Trans_Ts...> { 
		using type = typename util::push_front<typename eval_at<Tup<Ts...>, N - 1, Trans_Ts...>::type, T>::type;
	};

	template<CONTAINER Tup, typename T, typename ... Ts, TRANSFORM ... Trans_Ts>
	struct eval_at<Tup<T, Ts...>, 0, Trans_Ts...> { 
		using type = Tup<eval_t<T, Trans_Ts...>, Ts...>;
	};

	template<typename Tup, std::size_t N, TRANSFORM ... Trans_Ts>
	using eval_at_t = typename eval_at<Tup, N, Trans_Ts...>::type; 
	
	template<std::size_t N, TRANSFORM ... Trans_Ts>
	struct eval_at_ { template<typename Tup> using type = eval_at<Tup, N, Trans_Ts...>; };



	template<typename Tup>
	struct pop_front;

	template<CONTAINER Tup, typename T, typename ... Ts>
	struct pop_front<Tup<T, Ts...>> { using type = Tup<Ts...>; };
	
	template<typename Tup>
	using pop_front_t = typename pop_front<Tup>::type;



	template<typename Tup>
	struct pop_back : subset<Tup, std::make_index_sequence<arg_count_v<Tup> - 1>> { };

	template<typename Tup>
	using pop_back_t = typename pop_back<Tup>::type;



	namespace details {
		template<typename Tup, PREDICATE Pred_Tp, typename Ind>
		struct filter;

		template<CONTAINER Tup, typename ... Ts, PREDICATE Pred_Tp, std::size_t ... Is>
		struct filter<Tup<Ts...>, Pred_Tp, std::index_sequence<Is...>> {
		private:
			static constexpr std::pair<std::array<std::size_t, sizeof...(Ts)>, std::size_t> subrange = []{
				std::array<std::size_t, sizeof...(Ts)> indices { Is... };
				std::array<bool, sizeof...(Ts)> values { Pred_Tp<Ts>::value... };
				return std::pair{ indices, std::remove_if(indices.begin(), indices.end(), 
					[&](std::size_t i) { return !values[i]; }) - indices.begin() 
				};
			}();
		public:
			using type = subset_t<Tup<Ts...>, index_sequence_from_t<subrange.first, subrange.second>>;
		};
	}

	template<typename Tup, PREDICATE Pred_Tp>
	using filter = details::filter<Tup, Pred_Tp, std::make_index_sequence<arg_count_v<Tup>>>;

	template<PREDICATE Pred_Tp>
	struct filter_ { 
		template<typename Tup> using type = filter<Tup, Pred_Tp>;
		template<typename Tup> using inv =  filter<Tup, util::pred::negate_<Pred_Tp>::template type>;
	};



	template<typename Tup, PREDICATE Pred_Tp>
	using filter_t = typename filter<Tup, Pred_Tp>::type;



	template<typename Tup, PREDICATE Pred_Tp>
	struct find;

	template<CONTAINER Tup, typename ... Ts, PREDICATE Pred_Tp>
	struct find<Tup<Ts...>, Pred_Tp> { 
	private:
		static constexpr std::array<bool, sizeof...(Ts)> values { Pred_Tp<Ts>::value... };
	public:
		static constexpr std::size_t value = std::find(values.begin(), values.end(), true) - values.begin();
		using type = typename arg_at<value, Tup<Ts...>>::type;
	};
	
	template<PREDICATE Pred_Tp>
	struct find_ { template<typename Tup> using type = find<Tup, Pred_Tp>; };
	
	template<typename Tup, PREDICATE Pred_Tp>
	using find_t = typename find<Tup, Pred_Tp>::type;

	template<typename Tup, PREDICATE Pred_Tp>
	static constexpr unsigned int find_v = find<Tup, Pred_Tp>::value;




	template<typename Tup, ATTRIBUTER Get_Tp=get_value>
	struct find_min;

	template<ATTRIBUTER Get_Tp=get_value>
	struct find_min_ { template<typename Tup> using type = find_min<Tup, Get_Tp>; };

	template<typename Tup, ATTRIBUTER Get_Tp=get_value>
	using find_min_t = typename find_min<Tup, Get_Tp>::type;

	template<CONTAINER Tup, typename ... Ts, ATTRIBUTER Get_Tp>
	struct find_min<Tup<Ts...>, Get_Tp> {
	private:
		using value_type = decltype(Get_Tp<std::tuple_element_t<0, std::tuple<Ts...>>>::value);
		static constexpr std::array<value_type, sizeof...(Ts)> values { Get_Tp<Ts>::value... };
	public:
		static constexpr std::size_t value = std::ranges::min_element(values) - values.begin();
	};



	template<typename Tup, ATTRIBUTER Get_Tp=get_value>
	struct find_max;

	template<ATTRIBUTER Get_Tp=get_value>
	struct find_max_ { template<typename Tup> using type = find_max<Tup, Get_Tp>; };

	template<typename Tup, ATTRIBUTER Get_Tp=get_value>
	using find_max_t = typename find_max<Tup, Get_Tp>::type;

	template<CONTAINER Tup, typename ... Ts, ATTRIBUTER Get_Tp>
	struct find_max<Tup<Ts...>, Get_Tp> {
	private:
		using value_type = decltype(Get_Tp<std::tuple_element_t<0, std::tuple<Ts...>>>::value);
		static constexpr std::array<value_type, sizeof...(Ts)> values { Get_Tp<Ts>::value... };
	public:
		static constexpr std::size_t value = std::ranges::max_element(values) - values.begin();
	};
	



	template<typename Tup, COMPARE LT_T>
	struct sort;

	template<typename Tup, COMPARE LT_T>
	using sort_t = typename sort<Tup, LT_T>::type;

	template<CONTAINER Tup, typename Pivot_T, typename ... Ts, COMPARE Cmp_T>
	struct sort<Tup<Pivot_T, Ts...>, Cmp_T> : concat<std::tuple<
		sort_t<filter_t<Tup<Ts...>, cmp::to_<Pivot_T, Cmp_T>::template inv>,  Cmp_T>, Tup<Pivot_T>, // not less than
		sort_t<filter_t<Tup<Ts...>, cmp::to_<Pivot_T, Cmp_T>::template type>, Cmp_T>>> 				// less than
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
	struct unique;

	template<typename Tup, COMPARE Same_T=std::is_same>
	using unique_t = typename unique<Tup, Same_T>::type;

	template<CONTAINER Tup, typename T, typename ... Ts, COMPARE Same_T>
	struct unique<Tup<T, Ts...>, Same_T> : concat<std::tuple<Tup<T>, typename unique<
		filter_t<std::tuple<Ts...>, cmp::to_<T, Same_T>::template inv>, Same_T>::type>>
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


	template<typename Tup1, typename Tup2 = std::tuple<>, COMPARE Same_T = std::is_same>
	struct set_union;

	template<typename Tup, typename Set_T, COMPARE Same_T = std::is_same>
	using set_union_t = typename set_union<Tup, Set_T, Same_T>::type;

	template<typename Tup1, typename Tup2, COMPARE Same_T>
	struct set_union : unique<concat_t<std::tuple<Tup1, Tup2>>, Same_T> { };

	template<typename Set_T, COMPARE Same_T = std::is_same>
	struct set_union_ { template<typename Tup> using type = set_union<Tup, Set_T, Same_T>; };



	
	template<typename Tup1, typename Tup2, COMPARE Same_T = std::is_same>
	struct set_intersect;

	template<typename Tup, typename Set_T, COMPARE Same_T = std::is_same>
	using set_intersect_t = typename set_intersect<Tup, Set_T, Same_T>::type;

	template<typename Tup1, typename Tup2, COMPARE Same_T>
	struct set_intersect : filter<set_union_t<Tup1, Tup2, Same_T>, pred::conj_<
		pred::element_of_<Tup1, Same_T>::template type,
		pred::element_of_<Tup2, Same_T>::template type
	>::template type> { };

	template<COMPARE Same_T, typename Set_T>
	struct set_intersect_ {
		template<typename Tup> using type = set_intersect<Tup, Set_T, Same_T>;
		template<typename Tup> using inv =  set_intersect<Tup, Set_T, cmp::negate_<Same_T>::template type>;
	};
}

// [ ] subset/superset
namespace util::pred {
	template<typename SubSet_T, typename SuperSet_T, COMPARE Same_T=std::is_same>
	struct is_subset : allof<SubSet_T, element_of_<SuperSet_T, Same_T>::template type> { };
	template<typename SubSet_T, typename SuperSet_T, COMPARE Same_T=std::is_same>
	static constexpr bool is_subset_v = is_subset<SubSet_T, SuperSet_T, Same_T>::value;
	template<typename SuperSet_T, COMPARE Same_T=std::is_same>
	struct is_subset_ {
		template<typename SubSet_T> using type = is_subset<SubSet_T, SuperSet_T, Same_T>;
		template<typename SubSet_T> using inv =  std::negation<type<SubSet_T>>;
	};

	template<typename SuperSet_T, typename SubSet_T, COMPARE Same_T=std::is_same>
	struct is_superset : allof<SuperSet_T, element_of_<SubSet_T, Same_T>::template type> { };
	template<typename SuperSet_T, typename SubSet_T, COMPARE Same_T=std::is_same>
	static constexpr bool is_superset_v = is_superset<SuperSet_T, SubSet_T, Same_T>::value;
	template<typename SubSet_T, COMPARE Same_T=std::is_same>
	struct is_superset_ {
		template<typename SuperSet_T> using type = is_superset<SuperSet_T, SubSet_T, Same_T>;
		template<typename SuperSet_T> using inv =  std::negation<type<SuperSet_T>>;
	};
}

namespace util::cmp {
	template<typename T1, typename T2, COMPARE Cmp_T=std::is_same>
	struct is_same_set;
	template<typename T1, typename T2, COMPARE Cmp_T=std::is_same>
	static constexpr bool is_same_set_v = is_same_set<T1, T2, Cmp_T>::value;

	template<CONTAINER Tup1, typename ... T1s, CONTAINER Tup2, typename ... T2s, COMPARE Cmp_T>
	struct is_same_set<Tup1<T1s...>, Tup2<T2s...>, Cmp_T> {
		static constexpr bool value = (sizeof...(T1s) == sizeof...(T2s)) && (pred::element_of_v<T1s, Tup2<T2s...>, Cmp_T> && ...);
	};

	template<typename Tup1, COMPARE Cmp_T=std::is_same>
	struct is_same_set_ {
		template<typename Tup2> using type = is_same_set<Tup1, Tup2, Cmp_T>;
		template<typename Tup2> using inv = std::negation<type<Tup2>>;
	};
}