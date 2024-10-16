#pragma once
#include "tuple_util.h"
#include "eval.h"

// [ ] copy_ const/volatile/reference/cv/cvref
namespace util
{
	template<typename T, typename U>
	struct copy_const { using type = T; };
	template<typename T, typename U>
	struct copy_const<T, const U> { using type = const T; };
	template<typename T, typename U>
	using copy_const_t = typename copy_const<T, U>::type;
	template<typename U>
	struct copy_const_ { template<typename T> using type = copy_const<T, U>; };

	template<typename T, typename U>
	struct copy_volatile { using type = T; };
	template<typename T, typename U>
	struct copy_volatile<T, volatile U> { using type = volatile T; };
	template<typename T, typename U>
	using copy_volatile_t = typename copy_volatile<T, U>::type;
	template<typename U>
	struct copy_volatile_ { template<typename T> using type = copy_volatile<T, U>; };

	template<typename T, typename U>
	struct copy_lval_ref { using type = T; };
	template<typename T, typename U>
	struct copy_lval_ref<T, U&> { using type = T&; };
	template<typename T, typename U>
	using copy_lval_ref_t = typename copy_lval_ref<T, U>::type;
	template<typename U>
	struct copy_lval_ref_ { template<typename T> using type = copy_lval_ref<T, U>; };

	template<typename T, typename U>
	struct copy_rval_ref { using type = T; };
	template<typename T, typename U>
	struct copy_rval_ref<T, U&&> { using type = T&&; };
	template<typename T, typename U>
	using copy_rval_ref_t = typename copy_rval_ref<T, U>::type;
	template<typename U>
	struct copy_rval_ref_ { template<typename T> using type = copy_rval_ref<T, U>; };

	template<typename T, typename U>
	struct copy_ref { using type = copy_lval_ref_t<copy_rval_ref_t<T, U>, U>; };
	template<typename T, typename U>
	using copy_ref_t = typename copy_ref<T, U>::type;
	template<typename U>
	struct copy_ref_ { template<typename T> using type = copy_ref<T, U>; };


	template<typename T, typename U>
	struct copy_cv { using type = copy_const_t<copy_volatile_t<T, U>, U>; };
	template<typename T, typename U>
	using copy_cv_t = typename copy_cv<T, U>::type;
	template<typename U>
	struct copy_cv_ { template<typename T> using type = copy_cv<T, U>; };

	template<typename T, typename U>
	struct copy_cvref { using type = copy_cv_t<copy_ref_t<T, U>, U>; };
	template<typename T, typename U>
	using copy_cvref_t = typename copy_cvref<T, U>::type;
	template<typename U>
	struct copy_cvref_ { template<typename T> using type = copy_cvref<T, U>; };
}

// propagate const/volatile/cv
namespace util {
	template<typename T, TRANSFORM ... Trans_Ts>
	struct propagate_const : eval<T, Trans_Ts...> { };

	template<typename T, TRANSFORM ... Trans_Ts>
	struct propagate_const<const T, Trans_Ts...> : eval<const T, Trans_Ts..., std::add_const> { };

	template<TRANSFORM ... Trans_Ts>
	struct propagate_const_ { template<typename T> using type = propagate_const<T, Trans_Ts...>; };

	template<typename T, TRANSFORM ... Trans_Ts>
	using propagate_const_t = typename propagate_const<T, Trans_Ts...>::type;



	template<typename T, TRANSFORM ... Trans_Ts>
	struct propagate_const_each : eval<T, Trans_Ts...> { };

	template<typename T, TRANSFORM ... Trans_Ts>
	struct propagate_const_each<const T, Trans_Ts...> : eval<const T, Trans_Ts..., eval_each_<std::add_const>::template type> { };

	template<TRANSFORM ... Trans_Ts>
	struct propagate_const_each_ { template<typename T> using type = propagate_const_each<T, Trans_Ts...>; };

	template<typename T, TRANSFORM ... Trans_Ts>
	using propagate_const_each_t = typename propagate_const_each<T, Trans_Ts...>::type;



	template<typename T, TRANSFORM ... Trans_Ts>
	struct propagate_volatile : eval<T, Trans_Ts...> { };

	template<typename T, TRANSFORM ... Trans_Ts>
	struct propagate_volatile<volatile T, Trans_Ts...> : eval<volatile T, Trans_Ts..., std::add_volatile> { };

	template<TRANSFORM ... Trans_Ts>
	struct propagate_volatile_ { template<typename T> using type = propagate_volatile<T, Trans_Ts...>; };

	template<typename T, TRANSFORM ... Trans_Ts>
	using propagate_volatile_t = typename propagate_volatile<T, Trans_Ts...>::type;



	template<typename T, TRANSFORM ... Trans_Ts>
	struct propagate_volatile_each : eval<T, Trans_Ts...> { };

	template<typename T, TRANSFORM ... Trans_Ts>
	struct propagate_volatile_each<volatile T, Trans_Ts...> : eval<volatile T, Trans_Ts..., eval_each_<std::add_volatile>::template type> { };

	template<TRANSFORM ... Trans_Ts>
	struct propagate_volatile_each_ { template<typename T> using type = propagate_volatile_each<T, Trans_Ts...>; };

	template<typename T, TRANSFORM ... Trans_Ts>
	using propagate_volatile_each_t = typename propagate_volatile_each<T, Trans_Ts...>::type;



	template<typename T, TRANSFORM ... Trans_Ts>
	struct propagate_cv :eval<T, Trans_Ts...> { };

	template<typename T, TRANSFORM ... Trans_Ts>
	struct propagate_cv<const T, Trans_Ts...> : eval<T, Trans_Ts..., std::add_const> { };

	template<typename T, TRANSFORM ... Trans_Ts>
	struct propagate_cv<volatile T, Trans_Ts...> : eval<T, Trans_Ts..., std::add_volatile> { };

	template<typename T, TRANSFORM ... Trans_Ts>
	struct propagate_cv<const volatile T, Trans_Ts...> : eval<T, Trans_Ts..., std::add_const, std::add_volatile> { };

	template<TRANSFORM ... Trans_Ts>
	struct propagate_cv_ { template<typename T> using type = propagate_cv<T, Trans_Ts...>; };

	template<typename T, TRANSFORM ... Trans_Ts>
	using propagate_cv_t = typename propagate_cv<T, Trans_Ts...>::type;



	template<typename T, TRANSFORM ... Trans_Ts>
	struct propagate_cv_each : eval<T, Trans_Ts...> { };

	template<typename T, TRANSFORM ... Trans_Ts>
	struct propagate_cv_each<const T, Trans_Ts...> : eval<T, Trans_Ts..., std::add_const> { };

	template<typename T, TRANSFORM ... Trans_Ts>
	struct propagate_cv_each<volatile T, Trans_Ts...> : eval<T, Trans_Ts..., std::add_volatile> { };

	template<typename T, TRANSFORM ... Trans_Ts>
	struct propagate_cv_each<const volatile T, Trans_Ts...> : eval<T, Trans_Ts..., std::add_const, std::add_volatile> { };



	template<TRANSFORM ... Trans_Ts>
	struct propagate_cv_each_ { template<typename T> using type = propagate_cv_each<T, Trans_Ts...>; };

	template<typename T, TRANSFORM ... Trans_Ts>
	using propagate_cv_each_t = typename propagate_cv_each<T, Trans_Ts...>::type;
}

namespace util::cmp {
	template<typename LHS_T, typename RHS_T>
	struct is_ignore_cvref_same : std::is_same<std::remove_cvref_t<LHS_T>, std::remove_cvref_t<RHS_T>> { };

	template<typename LHS_T, typename RHS_T>
	static constexpr bool is_ignore_cvref_same_v = is_ignore_cvref_same<LHS_T, RHS_T>::value;



	template<typename LHS_T, typename RHS_T>
	struct is_ignore_cv_same : std::is_same<std::remove_cv_t<LHS_T>, std::remove_cv_t<RHS_T>> { };

	template<typename LHS_T, typename RHS_T>
	static constexpr bool is_ignore_cv_same_v = is_ignore_cv_same<LHS_T, RHS_T>::value;



	template<typename LHS_T, typename RHS_T>
	struct is_ignore_reference_same : std::is_same<std::remove_reference_t<LHS_T>, std::remove_reference_t<RHS_T>> { };

	template<typename LHS_T, typename RHS_T>
	static constexpr bool is_ignore_reference_same_v = is_ignore_reference_same<LHS_T, RHS_T>::value;



	template<typename LHS_T, typename RHS_T>
	struct is_ignore_volatile_same : std::is_same<std::remove_volatile_t<LHS_T>, std::remove_volatile_t<RHS_T>> { };

	template<typename LHS_T, typename RHS_T>
	static constexpr bool is_ignore_volatile_same_v = is_ignore_volatile_same<LHS_T, RHS_T>::value;



	template<typename LHS_T, typename RHS_T>
	struct is_ignore_const_same : std::is_same<std::remove_const_t<LHS_T>, std::remove_const_t<RHS_T>> { };

	template<typename LHS_T, typename RHS_T>
	static constexpr bool is_ignore_const_same_v = is_ignore_const_same<LHS_T, RHS_T>::value;



	template<typename LHS_T, typename RHS_T>
	struct is_const_accessible : std::disjunction<std::is_same<LHS_T, RHS_T>, std::is_same<LHS_T, std::add_const_t<RHS_T>>> { };

	template<typename LHS_T, typename RHS_T>
	static constexpr bool is_const_accessible_v = is_const_accessible<LHS_T, RHS_T>::value;
}

namespace util::pred {
	template<typename T> struct is_ignore_ref_const : std::is_const<std::remove_reference_t<T>> { };
	template<typename T> static constexpr bool is_ignore_ref_const_v = is_ignore_ref_const<T>::value;

	template<typename T> struct is_ignore_ref_volatile : std::is_volatile<std::remove_reference_t<T>> { };
	template<typename T> static constexpr bool is_ignore_ref_volatile_v = is_ignore_ref_volatile<T>::value;
}


namespace util {
	template<typename T> using add_ignore_ref_const = std::conditional<std::is_reference_v<T>, const std::remove_reference_t<T>&, const T>;
	template<typename T> using add_ignore_ref_const_t = typename add_ignore_ref_const<T>::type;

	template<typename T> using add_ignore_ref_volatile = std::conditional<std::is_reference_v<T>, volatile std::remove_reference_t<T>&, volatile T>;
	template<typename T> using add_ignore_ref_volatile_t = typename add_ignore_ref_volatile<T>::type;
	
	template<typename T, typename U, typename=std::void_t<>> struct copy_ignore_ref_const : std::type_identity<T> { };
	template<typename T, typename U> struct copy_ignore_ref_const<T, U, std::enable_if_t<pred::is_ignore_ref_const_v<U>>> : add_ignore_ref_const<T> { };
	template<typename T, typename U> using copy_ignore_ref_const_t = typename copy_ignore_ref_const<T, U>::type;

	template<typename T, typename U, typename=std::void_t<>> struct copy_ignore_ref_volatile : std::type_identity<T> { };
	template<typename T, typename U> struct copy_ignore_ref_volatile<T, U, std::enable_if_t<pred::is_ignore_ref_volatile_v<U>>> : add_ignore_ref_volatile<T> { };
	template<typename T, typename U> using copy_ignore_ref_volatile_t = typename copy_ignore_ref_volatile<T, U>::type;

	template<typename T, typename U, typename=std::void_t<>> struct copy_ignore_ref_cv;
	template<typename T, typename U> struct copy_ignore_ref_cv<T, U, std::enable_if_t<!pred::is_ignore_ref_const_v<U> && !pred::is_ignore_ref_volatile_v<U>>> : std::type_identity<T> { };
	template<typename T, typename U> struct copy_ignore_ref_cv<T, U, std::enable_if_t<pred::is_ignore_ref_const_v<U> && !pred::is_ignore_ref_volatile_v<U>>> : add_ignore_ref_const<T> { };
	template<typename T, typename U> struct copy_ignore_ref_cv<T, U, std::enable_if_t<!pred::is_ignore_ref_const_v<U> && pred::is_ignore_ref_volatile_v<U>>> : add_ignore_ref_volatile<T> { };
	template<typename T, typename U> struct copy_ignore_ref_cv<T, U, std::enable_if_t<pred::is_ignore_ref_const_v<U> && pred::is_ignore_ref_volatile_v<U>>>
	 : std::conditional<std::is_reference_v<T>, const volatile std::remove_reference_t<T>&, const volatile T> { };
	template<typename T, typename U> using copy_ignore_ref_cv_t = typename copy_ignore_ref_cv<T, U>::type;



}

static_assert(std::is_same_v<util::copy_ignore_ref_const_t<int&, int>, int&>);
static_assert(std::is_same_v<util::copy_ignore_ref_const_t<int&, const int>, const int&>);
static_assert(std::is_same_v<util::copy_ignore_ref_const_t<int&, const int>, const int&>);
static_assert(std::is_same_v<util::copy_ignore_ref_const_t<int&, const int>, const int&>);
static_assert(std::is_same_v<util::copy_ignore_ref_const_t<int, int>, int>);
static_assert(std::is_same_v<util::copy_ignore_ref_const_t<int, const int>, const int>);
static_assert(std::is_same_v<util::copy_ignore_ref_const_t<int, const int>, const int>);
static_assert(std::is_same_v<util::copy_ignore_ref_const_t<int, const int>, const int>);