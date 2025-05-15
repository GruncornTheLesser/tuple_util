#pragma once
#include "util/macro.h"

// inverse operations on cmp or pred args are equivalent to std::negation

namespace util::cmp {
	template<COMPARE Cmp_T>
	struct negate_ {
		template<typename LHS_T, typename RHS_T> using type = std::negation<Cmp_T<LHS_T, RHS_T>>;
	};

	template<typename LHS_T, typename RHS_T, COMPARE ... Cmp_Ts>
	using disj = std::disjunction<Cmp_Ts<LHS_T, RHS_T>...>;

	template<typename LHS_T, typename RHS_T, COMPARE ... Cmp_Ts>
	static constexpr bool disj_v = disj<LHS_T, RHS_T, Cmp_Ts...>::value;

	template<COMPARE ... Cmp_Ts>
	struct disj_ {
		template<typename LHS_T, typename RHS_T> using type = std::disjunction<Cmp_Ts<LHS_T, RHS_T>...>;
		template<typename LHS_T, typename RHS_T> using inv =  std::negation<type<LHS_T, RHS_T>>;
	};


	template<typename LHS_T, typename RHS_T, COMPARE ... Cmp_Ts>
	using conj = std::conjunction<Cmp_Ts<LHS_T, RHS_T>...>;

	template<typename LHS_T, typename RHS_T, COMPARE ... Cmp_Ts>
	static constexpr bool conj_v = conj<LHS_T, RHS_T, Cmp_Ts...>::value;

	template<COMPARE ... Cmp_Ts>
	struct conj_ {
		template<typename LHS_T, typename RHS_T> using type = std::conjunction<Cmp_Ts<LHS_T, RHS_T>...>;
		template<typename LHS_T, typename RHS_T> using inv =  std::negation<type<LHS_T, RHS_T>>;
	};

	template<typename LHS_T, COMPARE Cmp_T=std::is_same, TRANSFORM Trans_T=std::type_identity>
	struct to_
	{
		template<typename RHS_T> using type = Cmp_T<LHS_T, typename Trans_T<RHS_T>::type>;
		template<typename RHS_T> using inv =  std::negation<type<RHS_T>>;
	};
}

namespace util {
	// default Attributer_T
	template<typename T>
	struct get_value { static constexpr auto value = T::value; };
}

// compare attribs
namespace util::cmp {
	template<typename LHS, typename RHS, ATTRIBUTER Attributer_T=get_value>
	struct lt : std::bool_constant<(Attributer_T<LHS>::value < Attributer_T<RHS>::value)> { };

	template<typename LHS, typename RHS, ATTRIBUTER Attributer_T=get_value>
	static constexpr bool lt_v = lt<LHS, RHS, Attributer_T>::value;

	template<ATTRIBUTER Attributer_T=get_value>
	struct lt_ { 
		template<typename LHS, typename RHS> using type = cmp::lt<LHS, RHS, Attributer_T>;
		template<typename LHS, typename RHS> using inv =  cmp::lt<RHS, LHS, Attributer_T>;
	};

	template<typename LHS, typename RHS, ATTRIBUTER Attributer_T=get_value>
	struct lt_eq : std::bool_constant<(Attributer_T<LHS>::value <= Attributer_T<RHS>::value)> { };

	template<typename LHS, typename RHS, ATTRIBUTER Attributer_T=get_value>
	static constexpr bool lt_eq_v = lt_eq<LHS, RHS, Attributer_T>::value;

	template<ATTRIBUTER Attributer_T=get_value>
	struct lt_eq_ { 
		template<typename LHS, typename RHS> using type = cmp::lt_eq<LHS, RHS, Attributer_T>;
		template<typename LHS, typename RHS> using inv =  cmp::lt_eq<RHS, LHS, Attributer_T>;
	};

	template<typename LHS, typename RHS, ATTRIBUTER Attributer_T=get_value>
	struct gt : std::bool_constant<(Attributer_T<LHS>::value > Attributer_T<RHS>::value)> { };

	template<typename LHS, typename RHS, ATTRIBUTER Attributer_T=get_value>
	static constexpr bool gt_v = gt<LHS, RHS, Attributer_T>::value;

	template<ATTRIBUTER Attributer_T=get_value>
	struct gt_ { 
		template<typename LHS, typename RHS> using type = cmp::gt<LHS, RHS, Attributer_T>;
		template<typename LHS, typename RHS> using inv =  cmp::gt<RHS, LHS, Attributer_T>;
	};

	template<typename LHS, typename RHS, ATTRIBUTER Attributer_T=get_value>
	struct gt_eq : std::bool_constant<(Attributer_T<LHS>::value >= Attributer_T<RHS>::value)> { };

	template<typename LHS, typename RHS, ATTRIBUTER Attributer_T=get_value>
	static constexpr bool gt_eq_v = gt_eq<LHS, RHS, Attributer_T>::value;

	template<ATTRIBUTER Attributer_T=get_value>
	struct gt_eq_ { 
		template<typename LHS, typename RHS> using type = cmp::gt_eq<LHS, RHS, Attributer_T>;
		template<typename LHS, typename RHS> using inv =  cmp::gt_eq<RHS, LHS, Attributer_T>; 
	};

	template<typename LHS, typename RHS, ATTRIBUTER Attributer_T=get_value>
	struct eq : std::bool_constant<(Attributer_T<LHS>::value == Attributer_T<RHS>::value)> { };

	template<typename LHS, typename RHS, ATTRIBUTER Attributer_T=get_value>
	static constexpr bool eq_v = eq<LHS, RHS, Attributer_T>::value;

	template<ATTRIBUTER Attributer_T=get_value>
	struct eq_ { 
		template<typename LHS, typename RHS> using type = cmp::eq<LHS, RHS, Attributer_T>;
		template<typename LHS, typename RHS> using inv =  cmp::eq<RHS, LHS, Attributer_T>;
	};

	template<typename LHS, typename RHS, ATTRIBUTER Attributer_T=get_value>
	struct n_eq : std::bool_constant<(Attributer_T<LHS>::value != Attributer_T<RHS>::value)> { };

	template<typename LHS, typename RHS, ATTRIBUTER Attributer_T=get_value>
	static constexpr bool n_eq_v = n_eq<LHS, RHS, Attributer_T>::value;

	template<ATTRIBUTER Attributer_T=get_value>
	struct neq_ { template<typename LHS, typename RHS> using type = cmp::n_eq<LHS, RHS, Attributer_T>; };
}

namespace util::cmp {
	template<typename LHS, typename RHS, COMPARE ... Cmp_Ts>
	struct priority;

	template<typename LHS, typename RHS, COMPARE Cmp_T, COMPARE ... Cmp_Ts>
	struct priority<LHS, RHS, Cmp_T, Cmp_Ts...>
	 : std::disjunction<Cmp_T<LHS, RHS>, std::conjunction<eq<Cmp_T<LHS, RHS>, Cmp_T<RHS, LHS>>, priority<LHS, RHS, Cmp_Ts...>>> { };

	template<typename LHS, typename RHS, COMPARE Cmp_T>
	struct priority<LHS, RHS, Cmp_T>
	 : Cmp_T<LHS, RHS> { };

	template<typename LHS, typename RHS, COMPARE ... Cmp_Ts>
	static constexpr bool priority_v = priority<LHS, RHS, Cmp_Ts...>::value;

	template<COMPARE ... Cmp_Ts>
	struct priority_ { template<typename LHS, typename RHS> using type = priority<LHS, RHS, Cmp_Ts...>; };

	template<ATTRIBUTER ... attribs>
	struct attrib_ { template<typename LHS, typename RHS> using type = priority<LHS, RHS, cmp::lt_<attribs>::template type...>; };
}

// compare attribute types
namespace util::cmp {
	template<typename LHS_T, typename RHS_T, COMPARE Cmp_T, TRANSFORM LHS_Trans_T, TRANSFORM RHS_Trans_T=LHS_Trans_T>
	struct lhs_rhs : Cmp_T<typename LHS_Trans_T<LHS_T>::type, typename RHS_Trans_T<RHS_T>::type> { };

	template<COMPARE Cmp_T, TRANSFORM LHS_Trans_T, TRANSFORM RHS_Trans_T=LHS_Trans_T>
	struct lhs_rhs_ {
		template<typename LHS_T, typename RHS_T> using type = cmp::lhs_rhs<LHS_T, RHS_T, Cmp_T, LHS_Trans_T, RHS_Trans_T>;
		template<typename LHS_T, typename RHS_T> using inv =  std::negation<type<LHS_T, RHS_T>>;
	};

	template<typename LHS_T, typename RHS_T, COMPARE Cmp_T, TRANSFORM LHS_Trans_T, TRANSFORM RHS_Trans_T=LHS_Trans_T>
	static constexpr bool lhs_rhs_v = lhs_rhs<LHS_T, RHS_T, Cmp_T, LHS_Trans_T, RHS_Trans_T>::value;



	template<typename LHS_T, typename RHS_T, COMPARE Cmp_T, TRANSFORM RHS_Trans_T>
	struct rhs : lhs_rhs<LHS_T, RHS_T, Cmp_T, std::type_identity, RHS_Trans_T> { };

	template<COMPARE Cmp_T, TRANSFORM RHS_Trans_T>
	struct rhs_ : lhs_rhs_<Cmp_T, std::type_identity, RHS_Trans_T> { };

	template<typename LHS_T, typename RHS_T, COMPARE Cmp_T, TRANSFORM RHS_Trans_T>
	static constexpr bool rhs_v = rhs<LHS_T, RHS_T, Cmp_T, RHS_Trans_T>::value;



	template<typename LHS_T, typename RHS_T, COMPARE Cmp_T, TRANSFORM LHS_Trans_T>
	struct lhs : lhs_rhs<LHS_T, RHS_T, Cmp_T, LHS_Trans_T, std::type_identity> { };

	template<COMPARE Cmp_T, TRANSFORM LHS_Trans_T>
	struct lhs_ : lhs_rhs_<Cmp_T, LHS_Trans_T, std::type_identity> { };

	template<typename LHS_T, typename RHS_T, COMPARE Cmp_T, TRANSFORM LHS_Trans_T>
	static constexpr bool lhs_v = lhs<LHS_T, RHS_T, Cmp_T, LHS_Trans_T>::value;
}

