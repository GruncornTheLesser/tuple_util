#pragma once
#include "util/macro.h"
#include "util/eval.h"
#include "util/compare.h"
#include <type_traits>

// [ ] copy_ const/volatile/reference/cv/cvref
namespace TUPLE_UTIL_NAMESPACE {
	template<typename T> using add_const = std::add_const<T>;
	template<typename T> using add_const_t = typename add_const<T>::type;

	template<typename T> using add_volatile = std::add_volatile<T>;
	template<typename T> using add_volatile_t = typename add_volatile<T>::type;

	template<typename T> using add_ptr = std::add_pointer<T>; ;
	template<typename T> using add_ptr_t = typename add_ptr<T>::type;

	template<typename T> using add_lval_ref = std::add_lvalue_reference<T>;
	template<typename T> using add_lval_ref_t = typename add_lval_ref<T>::type;

	template<typename T> using add_rval_ref = std::add_rvalue_reference<T>;
	template<typename T> using add_rval_ref_t = typename add_rval_ref<T>::type;
}

namespace TUPLE_UTIL_NAMESPACE {
	template<typename T, typename U> struct copy_const { using type = T; };
	template<typename T, typename U> struct copy_const<T, const U> { using type = const T; };
	template<typename T, typename U> using copy_const_t = typename copy_const<T, U>::type;
	template<typename U> struct copy_const_ { template<typename T> using type = copy_const<T, U>; };

	template<typename T, typename U> struct copy_volatile { using type = T; };
	template<typename T, typename U> struct copy_volatile<T, volatile U> { using type = volatile T; };
	template<typename T, typename U> using copy_volatile_t = typename copy_volatile<T, U>::type;
	template<typename U> struct copy_volatile_ { template<typename T> using type = copy_volatile<T, U>; };

	template<typename T, typename U> struct copy_ptr { using type = T; };
	template<typename T, typename U> struct copy_ptr<T, U*> { using type = T*; };
	template<typename T, typename U> using copy_ptr_t = typename copy_ptr<T, U>::type;
	template<typename U> struct copy_ptr_ { template<typename T> using type = copy_ptr<T, U>; };

	template<typename T, typename U> struct copy_lval_ref { using type = T; };
	template<typename T, typename U> struct copy_lval_ref<T, U&> { using type = T&; };
	template<typename T, typename U> using copy_lval_ref_t = typename copy_lval_ref<T, U>::type;
	template<typename U> struct copy_lval_ref_ { template<typename T> using type = copy_lval_ref<T, U>; };

	template<typename T, typename U> struct copy_rval_ref { using type = T; };
	template<typename T, typename U> struct copy_rval_ref<T, U&&> { using type = T&&; };
	template<typename T, typename U> using copy_rval_ref_t = typename copy_rval_ref<T, U>::type;
	template<typename U> struct copy_rval_ref_ { template<typename T> using type = copy_rval_ref<T, U>; };

	template<typename T, typename U> struct copy_ref { using type = copy_lval_ref_t<copy_rval_ref_t<T, U>, U>; };
	template<typename T, typename U> using copy_ref_t = typename copy_ref<T, U>::type;
	template<typename U> struct copy_ref_ { template<typename T> using type = copy_ref<T, U>; };

	template<typename T, typename U> struct copy_cv { using type = copy_const_t<copy_volatile_t<T, U>, U>; };
	template<typename T, typename U> using copy_cv_t = typename copy_cv<T, U>::type;
	template<typename U> struct copy_cv_ { template<typename T> using type = copy_cv<T, U>; };

	template<typename T, typename U> struct copy_cv_ref { using type = copy_cv_t<copy_ref_t<T, U>, U>; };
	template<typename T, typename U> using copy_cv_ref_t = typename copy_cv_ref<T, U>::type;
	template<typename U> struct copy_cv_ref_ { template<typename T> using type = copy_cv_ref<T, U>; };
	
	template<typename T, typename U> struct copy_indirect { using type = copy_ptr_t<copy_ref_t<T, U>, U>; };
	template<typename T, typename U> using copy_indirect_t = typename copy_indirect<T, U>::type;
	template<typename U> struct copy_indirect_ { template<typename T> using type = copy_indirect<T, U>; };

	template<typename T, typename U> struct copy_cv_indirect { using type = copy_ptr_t<copy_cv_ref_t<T, U>, U>; };
	template<typename T, typename U> using copy_cv_indirect_t = typename copy_cv_indirect<T, U>::type;
	template<typename U> struct copy_cv_indirect_ { template<typename T> using type = copy_cv_indirect<T, U>; };

}

namespace TUPLE_UTIL_NAMESPACE::pred {
	template<typename T> using is_const = std::is_const<T>;
	template<typename T> static constexpr bool is_const_v = is_const<T>::value;
	
	template<typename T> using is_volatile = std::is_volatile<T>;
	template<typename T> static constexpr bool is_volatile_v = is_volatile<T>::value;
	
	template<typename T> using is_ptr = std::is_pointer<T>;
	template<typename T> static constexpr bool is_ptr_v = is_ptr<T>::value;
	
	template<typename T> using is_lval_ref = std::is_lvalue_reference<T>;
	template<typename T> static constexpr bool is_lval_ref_v = is_lval_ref<T>::value;
	
	template<typename T> using is_rval_ref = std::is_rvalue_reference<T>;
	template<typename T> static constexpr bool is_rval_ref_v = is_rval_ref<T>::value;
	
	template<typename T> using is_ref = std::is_reference<T>; 
	template<typename T> static constexpr bool is_ref_v = is_rval_ref<T>::value;
	
	template<typename T> struct is_indirect { static constexpr bool value = is_ptr_v<T> || is_ref_v<T>; };
	template<typename T> static constexpr bool is_indirect_v = is_rval_ref<T>::value;
}

namespace TUPLE_UTIL_NAMESPACE {
	template<typename T> using remove_const = std::remove_const<T>;
	template<typename T> using remove_const_t = typename remove_const<T>::type;
	
	template<typename T> using remove_volatile = std::remove_volatile<T>;
	template<typename T> using remove_volatile_t = typename remove_volatile<T>::type;

	template<typename T> using remove_ptr = std::remove_pointer<T>;
	template<typename T> using remove_ptr_t = typename remove_ptr<T>::type;
	
	template<typename T> struct remove_lval_ref { using type = T; };
	template<typename T> struct remove_lval_ref<T&> { using type = T; };
	template<typename T> using remove_lval_ref_t = typename remove_lval_ref<T>::type;

	template<typename T> struct remove_rval_ref { using type = T; };
	template<typename T> struct remove_rval_ref<T&&> { using type = T; };
	template<typename T> using remove_rval_ref_t = typename remove_rval_ref<T>::type;

	template<typename T> using remove_cv = std::remove_cv<T>;
	template<typename T> using remove_cv_t = std::remove_cv_t<T>;

	template<typename T> using remove_ref = std::remove_reference<T>;
	template<typename T> using remove_ref_t = typename remove_ref<T>::type;

	template<typename T> using remove_cv_ref = std::remove_cvref<T>;
	template<typename T> using remove_cv_ref_t = std::remove_cvref_t<T>;

	template<typename T> struct remove_indirect { using type = T; };
	template<typename T> struct remove_indirect<T*> { using type = T; };
	template<typename T> struct remove_indirect<T&> { using type = T; };
	template<typename T> struct remove_indirect<T&&> { using type = T; };
	template<typename T> using remove_indirect_t = typename remove_indirect<T>::type;
	
	template<typename T, TUPLE_UTIL_TRANSFORM Trans_T> struct eval_indirect : eval<T, remove_indirect, Trans_T, copy_indirect_<T>::template type>  { };
	template<typename T, TUPLE_UTIL_TRANSFORM Trans_T> using eval_indirect_t = typename eval_indirect<T, Trans_T>::type;
	template<TUPLE_UTIL_TRANSFORM Trans_T> struct eval_indirect_ { template<typename T> using type = eval_indirect<T, Trans_T>; };
		
	template<typename T, typename U> struct copy_indirect_const : eval<T, remove_indirect, copy_const_<U>::template type, copy_indirect_<T>::template type> { };
	template<typename T, typename U> using copy_indirect_const_t = typename copy_indirect_const<T, U>::type;

	template<typename T, typename U> struct copy_indirect_volatile : eval<T, remove_indirect, copy_volatile_<U>::template type, copy_indirect_<T>::template type> { };
	template<typename T, typename U> using copy_indirect_volatile_t = typename copy_indirect_volatile<T, U>::type;
	
	template<typename T, typename U> struct copy_indirect_lval_ref : eval<T, remove_indirect, copy_lval_ref_<U>::template type, copy_indirect_<T>::template type> { };
	template<typename T, typename U> using copy_indirect_lval_ref_t = typename copy_indirect_lval_ref<T, U>::type;
	
	template<typename T, typename U> struct copy_indirect_rval_ref : eval<T, remove_indirect, copy_rval_ref_<U>::template type, copy_indirect_<T>::template type> { };
	template<typename T, typename U> using copy_indirect_rval_ref_t = typename copy_indirect_rval_ref<T, U>::type;

	template<typename T, typename U> struct copy_indirect_ref : eval<T, remove_indirect, copy_ref_<U>::template type, copy_indirect_<T>::template type> { };
	template<typename T, typename U> using copy_indirect_ref_t = typename copy_indirect_ref<T, U>::type;	

	template<typename T, typename U> struct copy_indirect_cv : eval<T, remove_indirect, copy_cv_<U>::template type, copy_indirect_<T>::template type> { };
	template<typename T, typename U> using copy_indirect_cv_t = typename copy_indirect_cv<T, U>::type;

	template<typename T, typename U> struct copy_indirect_cvref : eval<T, remove_indirect, copy_cv_ref_<U>::template type, copy_indirect_<T>::template type> { };
	template<typename T, typename U> using copy_indirect_cvref_t = typename copy_indirect_cvref<T, U>::type;
}

// propagate const/volatile/cv
namespace TUPLE_UTIL_NAMESPACE {
	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_const : eval<T, Trans_Ts...> { };
	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_const<const T, Trans_Ts...> : eval<const T, Trans_Ts..., add_const> { };
	template<TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_const_ { template<typename T> using type = propagate_const<T, Trans_Ts...>; };
	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> using propagate_const_t = typename propagate_const<T, Trans_Ts...>::type;



	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_const_each : eval<T, Trans_Ts...> { };
	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_const_each<const T, Trans_Ts...> : eval<const T, Trans_Ts..., eval_each_<add_const>::template type> { };
	template<TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_const_each_ { template<typename T> using type = propagate_const_each<T, Trans_Ts...>; };
	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> using propagate_const_each_t = typename propagate_const_each<T, Trans_Ts...>::type;



	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_volatile : eval<T, Trans_Ts...> { };
	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_volatile<volatile T, Trans_Ts...> : eval<volatile T, Trans_Ts..., add_volatile> { };
	template<TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_volatile_ { template<typename T> using type = propagate_volatile<T, Trans_Ts...>; };
	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> using propagate_volatile_t = typename propagate_volatile<T, Trans_Ts...>::type;



	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_volatile_each : eval<T, Trans_Ts...> { };
	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_volatile_each<volatile T, Trans_Ts...> : eval<volatile T, Trans_Ts..., eval_each_<add_volatile>::template type> { };
	template<TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_volatile_each_ { template<typename T> using type = propagate_volatile_each<T, Trans_Ts...>; };
	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> using propagate_volatile_each_t = typename propagate_volatile_each<T, Trans_Ts...>::type;



	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_cv :eval<T, Trans_Ts...> { };
	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_cv<const T, Trans_Ts...> : eval<T, Trans_Ts..., add_const> { };
	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_cv<volatile T, Trans_Ts...> : eval<T, Trans_Ts..., add_volatile> { };
	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_cv<const volatile T, Trans_Ts...> : eval<T, Trans_Ts..., add_const, add_volatile> { };
	template<TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_cv_ { template<typename T> using type = propagate_cv<T, Trans_Ts...>; };
	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> using propagate_cv_t = typename propagate_cv<T, Trans_Ts...>::type;



	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_cv_each : eval<T, Trans_Ts...> { };
	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_cv_each<const T, Trans_Ts...> : eval<T, Trans_Ts..., add_const> { };
	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_cv_each<volatile T, Trans_Ts...> : eval<T, Trans_Ts..., add_volatile> { };
	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_cv_each<const volatile T, Trans_Ts...> : eval<T, Trans_Ts..., add_const, add_volatile> { };
	template<TUPLE_UTIL_TRANSFORM ... Trans_Ts> struct propagate_cv_each_ { template<typename T> using type = propagate_cv_each<T, Trans_Ts...>; };
	template<typename T, TUPLE_UTIL_TRANSFORM ... Trans_Ts> using propagate_cv_each_t = typename propagate_cv_each<T, Trans_Ts...>::type;
}

namespace TUPLE_UTIL_NAMESPACE::cmp {
	template<typename LHS_T, typename RHS_T>
	struct is_ignore_cvref_same : is_same<remove_cv_ref_t<LHS_T>, remove_cv_ref_t<RHS_T>> { };

	template<typename LHS_T, typename RHS_T>
	static constexpr bool is_ignore_cvref_same_v = is_ignore_cvref_same<LHS_T, RHS_T>::value;



	template<typename LHS_T, typename RHS_T>
	struct is_ignore_cv_same : is_same<remove_cv_t<LHS_T>, remove_cv_t<RHS_T>> { };

	template<typename LHS_T, typename RHS_T>
	static constexpr bool is_ignore_cv_same_v = is_ignore_cv_same<LHS_T, RHS_T>::value;



	template<typename LHS_T, typename RHS_T>
	struct is_ignore_ref_same : is_same<remove_ref_t<LHS_T>, remove_ref_t<RHS_T>> { };

	template<typename LHS_T, typename RHS_T>
	static constexpr bool is_ignore_ref_same_v = is_ignore_ref_same<LHS_T, RHS_T>::value;



	template<typename LHS_T, typename RHS_T>
	struct is_ignore_volatile_same : is_same<remove_volatile_t<LHS_T>, remove_volatile_t<RHS_T>> { };

	template<typename LHS_T, typename RHS_T>
	static constexpr bool is_ignore_volatile_same_v = is_ignore_volatile_same<LHS_T, RHS_T>::value;



	template<typename LHS_T, typename RHS_T>
	struct is_ignore_const_same : is_same<remove_const_t<LHS_T>, remove_const_t<RHS_T>> { };

	template<typename LHS_T, typename RHS_T>
	static constexpr bool is_ignore_const_same_v = is_ignore_const_same<LHS_T, RHS_T>::value;



	template<typename LHS_T, typename RHS_T>
	struct is_const_accessible {
		static constexpr bool value = !pred::is_const_v<LHS_T> || (pred::is_const_v<LHS_T> == pred::is_const_v<RHS_T>); 
	};

	template<typename RHS_T>
	struct is_const_accessible_ { template<typename LHS_T> using type = is_const_accessible<LHS_T, RHS_T>; };

	template<typename LHS_T, typename RHS_T>
	static constexpr bool is_const_accessible_v = is_const_accessible<LHS_T, RHS_T>::value;
}

namespace TUPLE_UTIL_NAMESPACE::pred {
	template<typename T> struct is_ref_const : is_const<remove_ref_t<T>> { };
	template<typename T> static constexpr bool is_ref_const_v = is_ref_const<T>::value;

	template<typename T> struct is_ref_volatile : is_volatile<remove_ref_t<T>> { };
	template<typename T> static constexpr bool is_ref_volatile_v = is_ref_volatile<T>::value;
}