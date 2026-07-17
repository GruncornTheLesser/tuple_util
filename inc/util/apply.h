#pragma once
#include "util/set.h"
#include <utility>
namespace TUPLE_UTIL_NAMESPACE::details { 
    template<typename Tup, typename Func_T, typename ... Arg_Ts, std::size_t ... Is> 
    inline constexpr decltype(auto) apply(Func_T&& func, std::index_sequence<Is...> ind, Arg_Ts&& ... args) {
        return func.template operator()<arg_at_t<Is, Tup>...>();
    }
}

namespace TUPLE_UTIL_NAMESPACE {
    template<typename Func, CONTAINER tup=TUPLE_UTIL_DEFAULT_CONTAINER>
	struct get_func_args;
	template<class T, CONTAINER tup, typename ... Dom_Ts>
	struct get_func_args<void(T::*)(const Dom_Ts&...), tup> {
		using type = tup<Dom_Ts...>;
	};
    template<CONTAINER tup>
	struct get_func_args_ {
        template<typename Func> using type = get_func_args<Func, tup>;
    };
    template<typename Func, CONTAINER tup=TUPLE_UTIL_DEFAULT_CONTAINER>
	using get_func_args_t = get_func_args<Func, tup>::type;
	


    template<typename Tup, typename Func_T, typename ... Arg_Ts> 
    inline constexpr decltype(auto) apply(Func_T&& func, Arg_Ts&& ... args) {
        return details::apply<Tup>(std::forward<Func_T>(func), std::make_index_sequence<arg_count_v<Tup>>{}, std::forward<Arg_Ts>(args)...);
    }
    
    template<typename Tup, typename Func_T, typename ... Arg_Ts>
    inline constexpr void apply_each(Func_T&& func, Arg_Ts&& ... args) {
        return details::apply<Tup>([&]<typename ... Ts>{ (func.template operator()<Ts>(), ...); }, std::make_index_sequence<arg_count_v<Tup>>{}, std::forward<Arg_Ts>(args)...);
    }
}