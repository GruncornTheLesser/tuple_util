#pragma once
#include "util/set.h"
#include <utility>
namespace util::details { 
    template<typename Tup, typename Func_T, typename ... Arg_Ts, std::size_t ... Is> 
    inline constexpr decltype(auto) apply(Func_T&& func, std::index_sequence<Is...> ind, Arg_Ts&& ... args) {
        return func.template operator()<arg_element_t<Is, Tup>...>();
    }
}

namespace util {
    template<typename Tup, typename Func_T, typename ... Arg_Ts> 
    inline constexpr decltype(auto) apply(Func_T&& func, Arg_Ts&& ... args) {
        return details::apply<Tup>(std::forward<Func_T>(func), std::make_index_sequence<arg_count_v<Tup>>{}, std::forward<Arg_Ts>(args)...);
    }
    
    template<typename Tup, typename Ret_T, typename Func_T, typename ... Arg_Ts>
    inline constexpr decltype(auto) apply_each(Func_T&& func, Arg_Ts&& ... args) {
        return apply<Tup>([&]<typename ... Ts>{ return Ret_T{ func.template operator()<Ts>()... }; });
    }
}