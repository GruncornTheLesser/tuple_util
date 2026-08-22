#pragma once
#include "util/set.h"

namespace TUPLE_UTIL_NAMESPACE::details { 
    template<typename Tup, typename Func_T, typename ... Arg_Ts, std::size_t ... Is> 
    inline constexpr decltype(auto) apply(Func_T&& func, std::index_sequence<Is...> ind, Arg_Ts&& ... args) {
        return func.template operator()<at_t<Is, Tup>...>(std::forward<Arg_Ts>(args)...);
    }
}

namespace TUPLE_UTIL_NAMESPACE::pred {
    template<typename Func>
    struct is_func { static constexpr bool value = false; };

    template<typename Ret_T, typename ... Arg_Ts>
    struct is_func<Ret_T(Arg_Ts...)> { static constexpr bool value = true; };

    template<typename Ret_T, typename ... Arg_Ts>
    struct is_func<Ret_T(&)(Arg_Ts...)> { static constexpr bool value = true; };

    template<typename Ret_T, typename ... Arg_Ts>
    struct is_func<Ret_T(*)(Arg_Ts...)> { static constexpr bool value = true; };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts>
    struct is_func<Ret_T(Base_T::*)(Arg_Ts...)> { static constexpr bool value = true; };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts>
    struct is_func<Ret_T(Base_T::*)(Arg_Ts...) const> { static constexpr bool value = true; };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts>
    struct is_func<Ret_T(Base_T::*)(Arg_Ts...) &> { static constexpr bool value = true; };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts>
    struct is_func<Ret_T(Base_T::*)(Arg_Ts...) const &> { static constexpr bool value = true; };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts>
    struct is_func<Ret_T(Base_T::*)(Arg_Ts...) &&> { static constexpr bool value = true; };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts>
    struct is_func<Ret_T(Base_T::*)(Arg_Ts...) const &&> { static constexpr bool value = true; };
    
    template<typename Func>
    static constexpr bool is_func_v = is_func<Func>::value;   
}

namespace TUPLE_UTIL_NAMESPACE::func {
    template<typename Func>
    struct get_return;

    template<typename Ret_T, typename ... Arg_Ts>
    struct get_return<Ret_T(Arg_Ts...)> : std::type_identity<Ret_T> { };

    template<typename Ret_T, typename ... Arg_Ts>
    struct get_return<Ret_T(&)(Arg_Ts...)> : std::type_identity<Ret_T> { };

    template<typename Ret_T, typename ... Arg_Ts>
    struct get_return<Ret_T(*)(Arg_Ts...)> : std::type_identity<Ret_T> { };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts>
    struct get_return<Ret_T(Base_T::*)(Arg_Ts...)> : std::type_identity<Ret_T> { };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts>
    struct get_return<Ret_T(Base_T::*)(Arg_Ts...) const> : std::type_identity<Ret_T> { };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts>
    struct get_return<Ret_T(Base_T::*)(Arg_Ts...) &> : std::type_identity<Ret_T> { };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts>
    struct get_return<Ret_T(Base_T::*)(Arg_Ts...) const &> : std::type_identity<Ret_T> { };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts>
    struct get_return<Ret_T(Base_T::*)(Arg_Ts...) &&> : std::type_identity<Ret_T> { };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts>
    struct get_return<Ret_T(Base_T::*)(Arg_Ts...) const &&> : std::type_identity<Ret_T> { };
    
    template<typename Func>
    using get_return_t = get_return<Func>::type;
    


    template<typename Func>
    struct get_base;
    
    template<typename Base_T, typename Ret_T, typename ... Arg_Ts>
    struct get_base<Ret_T(Base_T::*)(Arg_Ts...)> : std::type_identity<Base_T> { };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts>
    struct get_base<Ret_T(Base_T::*)(Arg_Ts...) const> : std::type_identity<Base_T> { };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts>
    struct get_base<Ret_T(Base_T::*)(Arg_Ts...) &> : std::type_identity<Base_T> { };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts>
    struct get_base<Ret_T(Base_T::*)(Arg_Ts...) const &> : std::type_identity<Base_T> { };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts>
    struct get_base<Ret_T(Base_T::*)(Arg_Ts...) &&> : std::type_identity<Base_T> { };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts>
    struct get_base<Ret_T(Base_T::*)(Arg_Ts...) const &&> : std::type_identity<Base_T> { };

    template<typename Func>
    using get_base_t = get_base<Func>::type;



    template<typename Func, TUPLE_UTIL_CONTAINER Tup=TUPLE_UTIL_DEFAULT_CONTAINER>
	struct get_args;
    
    template<typename Ret_T, typename ... Arg_Ts, TUPLE_UTIL_CONTAINER Tup>
    struct get_args<Ret_T(Arg_Ts...), Tup> : std::type_identity<Tup<Arg_Ts...>> { };

    template<typename Ret_T, typename ... Arg_Ts, TUPLE_UTIL_CONTAINER Tup>
    struct get_args<Ret_T(&)(Arg_Ts...), Tup> : std::type_identity<Tup<Arg_Ts...>> { };

    template<typename Ret_T, typename ... Arg_Ts, TUPLE_UTIL_CONTAINER Tup>
    struct get_args<Ret_T(*)(Arg_Ts...), Tup> : std::type_identity<Tup<Arg_Ts...>> { };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts, TUPLE_UTIL_CONTAINER Tup>
    struct get_args<Ret_T(Base_T::*)(Arg_Ts...), Tup> : std::type_identity<Tup<Arg_Ts...>> { };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts, TUPLE_UTIL_CONTAINER Tup>
    struct get_args<Ret_T(Base_T::*)(Arg_Ts...) const, Tup> : std::type_identity<Tup<Arg_Ts...>> { };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts, TUPLE_UTIL_CONTAINER Tup>
    struct get_args<Ret_T(Base_T::*)(Arg_Ts...) &, Tup> : std::type_identity<Tup<Arg_Ts...>> { };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts, TUPLE_UTIL_CONTAINER Tup>
    struct get_args<Ret_T(Base_T::*)(Arg_Ts...) const &, Tup> : std::type_identity<Tup<Arg_Ts...>> { };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts, TUPLE_UTIL_CONTAINER Tup>
    struct get_args<Ret_T(Base_T::*)(Arg_Ts...) &&, Tup> : std::type_identity<Tup<Arg_Ts...>> { };

    template<typename Base_T, typename Ret_T, typename ... Arg_Ts, TUPLE_UTIL_CONTAINER Tup>
    struct get_args<Ret_T(Base_T::*)(Arg_Ts...) const &&, Tup> : std::type_identity<Tup<Arg_Ts...>> { };
    
    template<TUPLE_UTIL_CONTAINER Tup=TUPLE_UTIL_DEFAULT_CONTAINER>
	struct get_args_ {
        template<typename Func> using type = get_args<Func, Tup>;
    };

    template<typename Func, TUPLE_UTIL_CONTAINER Tup=TUPLE_UTIL_DEFAULT_CONTAINER>
	using get_args_t = get_args<Func, Tup>::type;
}

namespace TUPLE_UTIL_NAMESPACE {
    template<typename Tup, typename Func_T, typename ... Arg_Ts> 
    inline constexpr decltype(auto) apply(Func_T&& func, Arg_Ts&& ... args) {
        return details::apply<Tup>(std::forward<Func_T>(func), std::make_index_sequence<count_v<Tup>>{}, std::forward<Arg_Ts>(args)...);
    }
    
    template<typename Tup, typename Func_T, typename ... Arg_Ts>
    inline constexpr void apply_each(Func_T&& func, Arg_Ts&& ... args) {
        return details::apply<Tup>([&]<typename ... Ts>{ (func.template operator()<Ts>(), ...); }, std::make_index_sequence<count_v<Tup>>{}, std::forward<Arg_Ts>(args)...);
    }
}