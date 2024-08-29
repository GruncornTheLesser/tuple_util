#pragma once
#include "tuple_util.h"
#include "eval.h"

namespace util {
	template<typename T, TRANSFORM Trans_T>
	struct propagate_const : post_eval_if<T, Trans_T, std::is_const, std::add_const> { };
	
	template<TRANSFORM Trans_T>
	struct propagate_const_ { template<typename T> using type = propagate_const<T, Trans_T>; };
	
	template<typename T, TRANSFORM Trans_T>
	using propagate_const_t = typename propagate_const<T, Trans_T>::type; 
	
	template<typename T, TRANSFORM Trans_T>
	struct propagate_const_each : post_eval_if<T, Trans_T, std::is_const, eval_each_<std::add_const>::template type> { };
	
	template<TRANSFORM Trans_T>
	struct propagate_const_each_ { template<typename T> using type = propagate_const_each<T, Trans_T>; };
	
	template<typename T, TRANSFORM Trans_T>
	using propagate_const_each_t = typename propagate_const_each<T, Trans_T>::type;
	
	template<typename T, CONTAINER Tup>
	using propagate_const_wrap = propagate_const<T, eval_<std::remove_const, wrap_<Tup>::template type>::template type>;

	template<CONTAINER Tup>
	struct propagate_const_wrap_ { template<typename T> using type = propagate_const_wrap<T, Tup>; };

	template<typename T, CONTAINER Tup>
	using propagate_const_wrap_t = propagate_const_wrap<T, Tup>::type;
}

// [ ] propagate_volatile 
namespace util {
	template<typename T, TRANSFORM Trans_T>
	struct propagate_volatile : post_eval_if<T, Trans_T, std::is_volatile, std::add_volatile> { };
	
	template<TRANSFORM Trans_T>
	struct propagate_volatile_ { template<typename T> using type = propagate_volatile<T, Trans_T>; };
	
	template<typename T, TRANSFORM Trans_T>
	using propagate_volatile_t = typename propagate_volatile<T, Trans_T>::type; 
	
	template<typename T, TRANSFORM Trans_T>
	struct propagate_volatile_each : post_eval_if<T, Trans_T, std::is_volatile, eval_each_<std::add_volatile>::template type> { };
	
	template<TRANSFORM Trans_T>
	struct propagate_volatile_each_ { template<typename T> using type = propagate_volatile_each<T, Trans_T>; };
	
	template<typename T, TRANSFORM Trans_T>
	using propagate_volatile_each_t = typename propagate_volatile_each<T, Trans_T>::type;
	
	template<typename T, CONTAINER Tup>
	using propagate_volatile_wrap = propagate_volatile<T, eval_<std::remove_volatile, wrap_<Tup>::template type>::template type>;

	template<CONTAINER Tup>
	struct propagate_volatile_wrap_ { template<typename T> using type = propagate_volatile_wrap<T, Tup>; };

	template<typename T, CONTAINER Tup>
	using propagate_volatile_wrap_t = propagate_volatile_wrap<T, Tup>::type;
}

// [ ] propagate_pointer
namespace util {
	template<typename T, TRANSFORM Trans_T>
	struct propagate_pointer : post_eval_if<T, Trans_T, std::is_pointer, std::add_pointer> { };
	
	template<TRANSFORM Trans_T>
	struct propagate_pointer_ { template<typename T> using type = propagate_pointer<T, Trans_T>; };
	
	template<typename T, TRANSFORM Trans_T>
	using propagate_pointer_t = typename propagate_pointer<T, Trans_T>::type; 
	
	template<typename T, TRANSFORM Trans_T>
	struct propagate_pointer_each : post_eval_if<T, Trans_T, std::is_pointer, eval_each_<std::add_pointer>::template type> { };
	
	template<TRANSFORM Trans_T>
	struct propagate_pointer_each_ { template<typename T> using type = propagate_pointer_each<T, Trans_T>; };
	
	template<typename T, TRANSFORM Trans_T>
	using propagate_pointer_each_t = typename propagate_pointer_each<T, Trans_T>::type;
	
	template<typename T, CONTAINER Tup>
	using propagate_pointer_wrap = propagate_pointer<T, eval_<std::remove_pointer, wrap_<Tup>::template type>::template type>;

	template<CONTAINER Tup>
	struct propagate_pointer_wrap_ { template<typename T> using type = propagate_pointer_wrap<T, Tup>; };

	template<typename T, CONTAINER Tup>
	using propagate_pointer_wrap_t = propagate_pointer_wrap<T, Tup>::type;
}

// [ ] propagate_reference
namespace util {
	template<typename T, TRANSFORM Trans_T>
	struct propagate_rvalue_reference : post_eval_if<T, Trans_T, std::is_rvalue_reference, std::add_rvalue_reference> { };
	
	template<TRANSFORM Trans_T>
	struct propagate_rvalue_reference_ { template<typename T> using type = propagate_rvalue_reference<T, Trans_T>; };
	
	template<typename T, TRANSFORM Trans_T>
	using propagate_rvalue_reference_t = typename propagate_rvalue_reference<T, Trans_T>::type;

	template<typename T, TRANSFORM Trans_T>
	struct propagate_rvalue_reference_each : post_eval_if<T, Trans_T, std::is_rvalue_reference, eval_each_<std::add_rvalue_reference>::template type> { };
	
	template<TRANSFORM Trans_T>
	struct propagate_rvalue_reference_each_ { template<typename T> using type = propagate_rvalue_reference_each<T, Trans_T>; };
	
	template<typename T, TRANSFORM Trans_T>
	using propagate_rvalue_reference_each_t = typename propagate_rvalue_reference_each<T, Trans_T>::type;
	
	template<typename T, CONTAINER Tup>
	using propagate_rvalue_reference_wrap = propagate_rvalue_reference<T, eval_<std::remove_reference, wrap_<Tup>::template type>::template type>;

	template<CONTAINER Tup>
	struct propagate_rvalue_reference_wrap_ { template<typename T> using type = propagate_rvalue_reference_wrap<T, Tup>; };

	template<typename T, CONTAINER Tup>
	using propagate_rvalue_reference_wrap_t = propagate_rvalue_reference_wrap<T, Tup>::type;



	template<typename T, TRANSFORM Trans_T>
	struct propagate_lvalue_reference : post_eval_if<T, Trans_T, std::is_lvalue_reference, std::add_lvalue_reference> { };
	
	template<TRANSFORM Trans_T>
	struct propagate_lvalue_reference_ { template<typename T> using type = propagate_lvalue_reference<T, Trans_T>; };
	
	template<typename T, TRANSFORM Trans_T>
	using propagate_lvalue_reference_t = typename propagate_lvalue_reference<T, Trans_T>::type;

	template<typename T, TRANSFORM Trans_T>
	struct propagate_lvalue_reference_each : post_eval_if<T, Trans_T, std::is_lvalue_reference, eval_each_<std::add_lvalue_reference>::template type> { };
	
	template<TRANSFORM Trans_T>
	struct propagate_lvalue_reference_each_ { template<typename T> using type = propagate_lvalue_reference_each<T, Trans_T>; };
	
	template<typename T, TRANSFORM Trans_T>
	using propagate_lvalue_reference_each_t = typename propagate_lvalue_reference_each<T, Trans_T>::type;
	
	template<typename T, CONTAINER Tup>
	using propagate_lvalue_reference_wrap = propagate_lvalue_reference<T, eval_<std::remove_reference, wrap_<Tup>::template type>::template type>;

	template<CONTAINER Tup>
	struct propagate_lvalue_reference_wrap_ { template<typename T> using type = propagate_lvalue_reference_wrap<T, Tup>; };

	template<typename T, CONTAINER Tup>
	using propagate_lvalue_reference_wrap_t = propagate_lvalue_reference_wrap<T, Tup>::type;



	template<typename T, TRANSFORM Trans_T>
	struct propagate_reference
	 : eval_if<T, std::is_rvalue_reference, eval_<Trans_T, std::add_rvalue_reference>::template type, 
		eval_if_<std::is_lvalue_reference, eval_<Trans_T, std::add_lvalue_reference>::template type,
		Trans_T>::template type> { };
	
	template<TRANSFORM Trans_T>
	struct propagate_reference_ { template<typename T> using type = propagate_reference<T, Trans_T>; };
	
	template<typename T, TRANSFORM Trans_T>
	using propagate_reference_t = typename propagate_lvalue_reference<T, Trans_T>::type;

	template<typename T, TRANSFORM Trans_T>
	struct propagate_reference_each
	 : eval_if<T, std::is_rvalue_reference, eval_<Trans_T, eval_each_<std::add_rvalue_reference>::template type>::template type, 
		eval_if_<std::is_lvalue_reference, eval_<Trans_T, eval_each_<std::add_lvalue_reference>::template type>::template type,
		Trans_T>::template type> { };
	
	template<TRANSFORM Trans_T>
	struct propagate_reference_each_ { template<typename T> using type = propagate_lvalue_reference_each<T, Trans_T>; };
	
	template<typename T, TRANSFORM Trans_T>
	using propagate_reference_each_t = typename propagate_lvalue_reference_each<T, Trans_T>::type;
	
	template<typename T, CONTAINER Tup>
	using propagate_reference_wrap = propagate_lvalue_reference<T, eval_<std::remove_reference, wrap_<Tup>::template type>::template type>;

	template<CONTAINER Tup>
	struct propagate_reference_wrap_ { template<typename T> using type = propagate_lvalue_reference_wrap<T, Tup>; };

	template<typename T, CONTAINER Tup>
	using propagate_reference_wrap_t = propagate_lvalue_reference_wrap<T, Tup>::type;
}

// [ ] propagate_cv
namespace util {
	template<typename T, TRANSFORM Trans_T>
	struct propagate_cv
	 : eval_if<T, std::is_const, eval_<Trans_T, std::add_const>::template type, 
		eval_if_<std::is_volatile, eval_<Trans_T, std::add_volatile>::template type,
		Trans_T>::template type> { };
	
	template<TRANSFORM Trans_T>
	struct propagate_cv_ { template<typename T> using type = propagate_cv<T, Trans_T>; };
	
	template<typename T, TRANSFORM Trans_T>
	using propagate_cv_t = typename propagate_cv<T, Trans_T>::type; 
	
	template<typename T, TRANSFORM Trans_T>
	struct propagate_cv_each
	 : eval_if<T, std::is_const, eval_<Trans_T, eval_each_<std::add_const>::template type>::template type, 
		eval_if_<std::is_volatile, eval_<Trans_T, eval_each_<std::add_volatile>::template type>::template type,
		Trans_T>::template type> { };
	
	template<TRANSFORM Trans_T>
	struct propagate_cv_each_ { template<typename T> using type = propagate_cv_each<T, Trans_T>; };
	
	template<typename T, TRANSFORM Trans_T>
	using propagate_cv_each_t = typename propagate_cv_each<T, Trans_T>::type;
	
	template<typename T, CONTAINER Tup>
	using propagate_cv_wrap = propagate_cv<T, eval_<std::remove_cv, wrap_<Tup>::template type>::template type>;

	template<CONTAINER Tup>
	struct propagate_cv_wrap_ { template<typename T> using type = propagate_cv_wrap<T, Tup>; };

	template<typename T, CONTAINER Tup>
	using propagate_cv_wrap_t = propagate_cv_wrap<T, Tup>::type;
}

// [ ] propagate_cvref
namespace util {
	template<typename T, TRANSFORM Trans_T>
	struct propagate_cvref
	 : eval_if<T, std::is_const, eval_<Trans_T, std::add_const>::template type, 
		eval_if_<std::is_volatile, eval_<Trans_T, std::add_volatile>::template type,
		eval_if_<std::is_lvalue_reference, eval_<Trans_T, std::add_lvalue_reference>::template type,
		eval_if_<std::is_rvalue_reference, eval_<Trans_T, std::add_rvalue_reference>::template type,
		Trans_T>::template type>::template type>::template type> { };
	
	template<TRANSFORM Trans_T>
	struct propagate_cvref_ { template<typename T> using type = propagate_cvref<T, Trans_T>; };
	
	template<typename T, TRANSFORM Trans_T>
	using propagate_cvref_t = typename propagate_cvref<T, Trans_T>::type; 
	
	template<typename T, TRANSFORM Trans_T>
	struct propagate_cvref_each
	 : eval_if<T, std::is_const, eval_<Trans_T, eval_each_<std::add_const>::template type>::template type, 
		eval_if_<std::is_volatile, eval_<Trans_T, eval_each_<std::add_volatile>::template type>::template type,
		eval_if_<std::is_lvalue_reference, eval_<Trans_T, eval_each_<std::add_lvalue_reference>::template type>::template type,
		eval_if_<std::is_rvalue_reference, eval_<Trans_T, eval_each_<std::add_rvalue_reference>::template type>::template type,
		Trans_T>::template type>::template type>::template type> { };
	
	template<TRANSFORM Trans_T>
	struct propagate_cvref_each_ { template<typename T> using type = propagate_cvref_each<T, Trans_T>; };
	
	template<typename T, TRANSFORM Trans_T>
	using propagate_cvref_each_t = typename propagate_cvref_each<T, Trans_T>::type;
	
	template<typename T, CONTAINER Tup>
	using propagate_cvref_wrap = propagate_cvref<T, eval_<std::remove_cvref, wrap_<Tup>::template type>::template type>;

	template<CONTAINER Tup>
	struct propagate_cvref_wrap_ { template<typename T> using type = propagate_cvref_wrap<T, Tup>; };

	template<typename T, CONTAINER Tup>
	using propagate_cvref_wrap_t = propagate_cvref_wrap<T, Tup>::type;
}

// [ ] copy_ const/volatile/reference/cv/cvref
namespace util
{
	template<typename T, typename U>
	struct copy_const { using type = T; };
	template<typename T, typename U>
	struct copy_const<T, const U> { using type = const T; };
	template<typename T, typename U>
	using copy_const_t = copy_const<T, U>::type;
	template<typename U>
	struct copy_const_ { template<typename T> using type = copy_const<T, U>; };

	template<typename T, typename U>
	struct copy_volatile { using type = T; };
	template<typename T, typename U>
	struct copy_volatile<T, volatile U> { using type = volatile T; };
	template<typename T, typename U>
	using copy_volatile_t = copy_volatile<T, U>::type;
	template<typename U>
	struct copy_volatile_ { template<typename T> using type = copy_volatile<T, U>; };
	
	template<typename T, typename U>
	struct copy_lvalue_reference { using type = T; };
	template<typename T, typename U>
	struct copy_lvalue_reference<T, U&> { using type = T&; };
	template<typename T, typename U>
	using copy_lvalue_reference_t = copy_lvalue_reference<T, U>::type;
	template<typename U>
	struct copy_lvalue_reference_ { template<typename T> using type = copy_lvalue_reference<T, U>; };

	template<typename T, typename U>
	struct copy_rvalue_reference { using type = T; };
	template<typename T, typename U>
	struct copy_rvalue_reference<T, U&&> { using type = T&&; };
	template<typename T, typename U>
	using copy_rvalue_reference_t = copy_rvalue_reference<T, U>::type;
	template<typename U>
	struct copy_rvalue_reference_ { template<typename T> using type = copy_rvalue_reference<T, U>; };

	template<typename T, typename U>
	struct copy_reference { using type = copy_lvalue_reference_t<copy_rvalue_reference_t<T, U>, U>; };
	template<typename T, typename U>
	using copy_reference_t = copy_reference<T, U>::type;
	template<typename U>
	struct copy_reference_ { template<typename T> using type = copy_reference<T, U>; };


	template<typename T, typename U>
	struct copy_cv { using type = copy_const_t<copy_volatile_t<T, U>, U>; };
	template<typename T, typename U>
	using copy_cv_t = copy_cv<T, U>::type;
	template<typename U>
	struct copy_cv_ { template<typename T> using type = copy_cv<T, U>; };

	template<typename T, typename U>
	struct copy_cvref { using type = copy_cv_t<copy_reference_t<T, U>, U>; };
	template<typename T, typename U>
	using copy_cvref_t = copy_cvref<T, U>::type;
	template<typename U>
	struct copy_cvref_ { template<typename T> using type = copy_cvref<T, U>; };
};

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
