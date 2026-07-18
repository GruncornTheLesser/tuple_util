#pragma once
#include "util/macro.h"
#include <type_traits>

namespace TUPLE_UTIL_NAMESPACE::cmp {
	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_COMPARE Cmp_Tp>
	using negate = std::negation<Cmp_Tp<LHS_T, RHS_T>>;

	template<TUPLE_UTIL_COMPARE Cmp_Tp>
	struct negate_ {
		template<typename LHS_T, typename RHS_T> using type = std::negation<Cmp_Tp<LHS_T, RHS_T>>;
	};

	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_COMPARE Cmp_Tp>
	static constexpr bool negate_v = negate<LHS_T, RHS_T, Cmp_Tp>::value;

	

	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_COMPARE ... Cmp_Tps>
	using disj = std::disjunction<Cmp_Tps<LHS_T, RHS_T>...>;
	
	template<TUPLE_UTIL_COMPARE ... Cmp_Tps>
	struct disj_ {
		template<typename LHS_T, typename RHS_T> using type = std::disjunction<Cmp_Tps<LHS_T, RHS_T>...>;
		template<typename LHS_T, typename RHS_T> using inv =  std::negation<type<LHS_T, RHS_T>>;
	};

	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_COMPARE ... Cmp_Tps>
	static constexpr bool disj_v = disj<LHS_T, RHS_T, Cmp_Tps...>::value;



	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_COMPARE ... Cmp_Tps>
	using conj = std::conjunction<Cmp_Tps<LHS_T, RHS_T>...>;

	template<TUPLE_UTIL_COMPARE ... Cmp_Tps>
	struct conj_ {
		template<typename LHS_T, typename RHS_T> using type = std::conjunction<Cmp_Tps<LHS_T, RHS_T>...>;
		template<typename LHS_T, typename RHS_T> using inv =  std::negation<type<LHS_T, RHS_T>>;
	};

	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_COMPARE ... Cmp_Tps>
	static constexpr bool conj_v = conj<LHS_T, RHS_T, Cmp_Tps...>::value;

	template<typename LHS_T, TUPLE_UTIL_COMPARE Cmp_Tp=std::is_same, TUPLE_UTIL_TRANSFORM Trans_T=std::type_identity> 
	struct to_ {
		template<typename RHS_T> using type = Cmp_Tp<LHS_T, typename Trans_T<RHS_T>::type>;
		template<typename RHS_T> using inv =  std::negation<type<RHS_T>>;
	};
}

namespace TUPLE_UTIL_NAMESPACE {
	// default Attrib_Tp
	template<typename T> struct get_value { static constexpr auto value = T::value; };
}

// compare attribs
namespace TUPLE_UTIL_NAMESPACE::cmp {
	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_ATTRIBUTER Attrib_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	struct lt : std::bool_constant<(Attrib_Tp<LHS_T>::value < Attrib_Tp<RHS_T>::value)> { };

	template<TUPLE_UTIL_ATTRIBUTER Attrib_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	struct lt_ { 
		template<typename LHS_T, typename RHS_T> using type = cmp::lt<LHS_T, RHS_T, Attrib_Tp>;
		template<typename LHS_T, typename RHS_T> using inv =  cmp::lt<RHS_T, LHS_T, Attrib_Tp>;
	};

	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_ATTRIBUTER Attrib_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	static constexpr bool lt_v = lt<LHS_T, RHS_T, Attrib_Tp>::value;


	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_ATTRIBUTER Attrib_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	struct lteq : std::bool_constant<(Attrib_Tp<LHS_T>::value <= Attrib_Tp<RHS_T>::value)> { };

	template<TUPLE_UTIL_ATTRIBUTER Attrib_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	struct lteq_ { 
		template<typename LHS_T, typename RHS_T> using type = cmp::lteq<LHS_T, RHS_T, Attrib_Tp>;
		template<typename LHS_T, typename RHS_T> using inv =  cmp::lteq<RHS_T, LHS_T, Attrib_Tp>;
	};

	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_ATTRIBUTER Attrib_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	static constexpr bool lteq_v = lteq<LHS_T, RHS_T, Attrib_Tp>::value;


	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_ATTRIBUTER Attrib_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	struct gt : std::bool_constant<(Attrib_Tp<LHS_T>::value > Attrib_Tp<RHS_T>::value)> { };

	template<TUPLE_UTIL_ATTRIBUTER Attrib_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	struct gt_ { 
		template<typename LHS_T, typename RHS_T> using type = cmp::gt<LHS_T, RHS_T, Attrib_Tp>;
		template<typename LHS_T, typename RHS_T> using inv =  cmp::gt<RHS_T, LHS_T, Attrib_Tp>;
	};

	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_ATTRIBUTER Attrib_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	static constexpr bool gt_v = gt<LHS_T, RHS_T, Attrib_Tp>::value;


	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_ATTRIBUTER Attrib_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	struct gteq : std::bool_constant<(Attrib_Tp<LHS_T>::value >= Attrib_Tp<RHS_T>::value)> { };

	template<TUPLE_UTIL_ATTRIBUTER Attrib_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	struct gteq_ { 
		template<typename LHS_T, typename RHS_T> using type = cmp::gteq<LHS_T, RHS_T, Attrib_Tp>;
		template<typename LHS_T, typename RHS_T> using inv =  cmp::gteq<RHS_T, LHS_T, Attrib_Tp>; 
	};

	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_ATTRIBUTER Attrib_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	static constexpr bool gteq_v = gteq<LHS_T, RHS_T, Attrib_Tp>::value;


	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_ATTRIBUTER Attrib_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	struct eq : std::bool_constant<(Attrib_Tp<LHS_T>::value == Attrib_Tp<RHS_T>::value)> { };

	template<TUPLE_UTIL_ATTRIBUTER Attrib_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	struct eq_ { 
		template<typename LHS_T, typename RHS_T> using type = cmp::eq<LHS_T, RHS_T, Attrib_Tp>;
		template<typename LHS_T, typename RHS_T> using inv =  cmp::eq<RHS_T, LHS_T, Attrib_Tp>;
	};

	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_ATTRIBUTER Attrib_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	static constexpr bool eq_v = eq<LHS_T, RHS_T, Attrib_Tp>::value;


	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_ATTRIBUTER Attrib_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	struct neq : std::bool_constant<(Attrib_Tp<LHS_T>::value != Attrib_Tp<RHS_T>::value)> { };
	
	template<TUPLE_UTIL_ATTRIBUTER Attrib_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	struct neq_ { template<typename LHS_T, typename RHS_T> using type = cmp::neq<LHS_T, RHS_T, Attrib_Tp>; };

	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_ATTRIBUTER Attrib_Tp=TUPLE_UTIL_DEFAULT_ATTRIBUTER>
	static constexpr bool neq_v = neq<LHS_T, RHS_T, Attrib_Tp>::value;
}

namespace TUPLE_UTIL_NAMESPACE::cmp {
	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_COMPARE ... Cmp_Tps>
	struct priority;

	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_COMPARE Cmp_Tp, TUPLE_UTIL_COMPARE ... Cmp_Tps>
	struct priority<LHS_T, RHS_T, Cmp_Tp, Cmp_Tps...>
	 : std::disjunction<Cmp_Tp<LHS_T, RHS_T>, std::conjunction<eq<Cmp_Tp<LHS_T, RHS_T>, Cmp_Tp<RHS_T, LHS_T>>, priority<LHS_T, RHS_T, Cmp_Tps...>>> { };

	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_COMPARE Cmp_Tp>
	struct priority<LHS_T, RHS_T, Cmp_Tp>
	 : Cmp_Tp<LHS_T, RHS_T> { };

	template<TUPLE_UTIL_COMPARE ... Cmp_Tps>
	struct priority_ { template<typename LHS_T, typename RHS_T> using type = priority<LHS_T, RHS_T, Cmp_Tps...>; };

	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_COMPARE ... Cmp_Tps>
	static constexpr bool priority_v = priority<LHS_T, RHS_T, Cmp_Tps...>::value;




	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_ATTRIBUTER ... attribs>
	using attrib = priority<LHS_T, RHS_T, cmp::lt_<attribs>::template type...>;
	
	template<TUPLE_UTIL_ATTRIBUTER ... attribs>
	struct attrib_ { template<typename LHS_T, typename RHS_T> using type = priority<LHS_T, RHS_T, cmp::lt_<attribs>::template type...>; };

	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_ATTRIBUTER ... attribs>
	static constexpr bool attrib_v = priority_v<LHS_T, RHS_T, cmp::lt_<attribs>::template type...>;
	
}

namespace TUPLE_UTIL_NAMESPACE::cmp::evaled {
	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_COMPARE Cmp_Tp, TUPLE_UTIL_TRANSFORM LHS_Trans_T, TUPLE_UTIL_TRANSFORM RHS_Trans_T=LHS_Trans_T> 
	struct lhs_rhs : Cmp_Tp<typename LHS_Trans_T<LHS_T>::type, typename RHS_Trans_T<RHS_T>::type> { };

	template<TUPLE_UTIL_COMPARE Cmp_Tp, TUPLE_UTIL_TRANSFORM LHS_Trans_T, TUPLE_UTIL_TRANSFORM RHS_Trans_T=LHS_Trans_T>
	struct lhs_rhs_ {
		template<typename LHS_T, typename RHS_T> using type = lhs_rhs<LHS_T, RHS_T, Cmp_Tp, LHS_Trans_T, RHS_Trans_T>;
		template<typename LHS_T, typename RHS_T> using inv =  std::negation<type<LHS_T, RHS_T>>;
	};

	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_COMPARE Cmp_Tp, TUPLE_UTIL_TRANSFORM LHS_Trans_T, TUPLE_UTIL_TRANSFORM RHS_Trans_T=LHS_Trans_T>
	static constexpr bool lhs_rhs_v = lhs_rhs<LHS_T, RHS_T, Cmp_Tp, LHS_Trans_T, RHS_Trans_T>::value;



	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_COMPARE Cmp_Tp, TUPLE_UTIL_TRANSFORM RHS_Trans_T>
	struct rhs : lhs_rhs<LHS_T, RHS_T, Cmp_Tp, std::type_identity, RHS_Trans_T> { };

	template<TUPLE_UTIL_COMPARE Cmp_Tp, TUPLE_UTIL_TRANSFORM RHS_Trans_T>
	struct rhs_ : lhs_rhs_<Cmp_Tp, std::type_identity, RHS_Trans_T> { };

	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_COMPARE Cmp_Tp, TUPLE_UTIL_TRANSFORM RHS_Trans_T>
	static constexpr bool rhs_v = rhs<LHS_T, RHS_T, Cmp_Tp, RHS_Trans_T>::value;



	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_COMPARE Cmp_Tp, TUPLE_UTIL_TRANSFORM LHS_Trans_T>
	struct lhs : lhs_rhs<LHS_T, RHS_T, Cmp_Tp, LHS_Trans_T, std::type_identity> { };

	template<TUPLE_UTIL_COMPARE Cmp_Tp, TUPLE_UTIL_TRANSFORM LHS_Trans_T>
	struct lhs_ : lhs_rhs_<Cmp_Tp, LHS_Trans_T, std::type_identity> { };

	template<typename LHS_T, typename RHS_T, TUPLE_UTIL_COMPARE Cmp_Tp, TUPLE_UTIL_TRANSFORM LHS_Trans_T>
	static constexpr bool lhs_v = lhs<LHS_T, RHS_T, Cmp_Tp, LHS_Trans_T>::value;
}

