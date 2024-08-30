## Intro
metaprogramming library for people who dont like coding in c++ and would instead prefer repeated smashing their head against the nearest hard surface. 
works in c++20 and above.

## syntax construction
this is an example how most classes are constructed
```c++
template<typename T, typename Arg>
struct foobar { using type = ...; };

template<typename T, typename Arg>
using foobar_t = typename foobar::type;

template<typename Arg>
struct foobar_ { template<typename T> using type = foobar<T, Arg>; };
```

macros exist for the different types of template parameter argument but they translate to template constructions
```c++
#define ATTRIBUTER template<typename> typename // describes an attribute of a class. eg std::tuple_size
#define TRANSFORM template<typename> typename // has 'type' eg std::add_const
#define PREDICATE template<typename> typename // has bool 'value' eg std::is_const
#define COMPARE template<typename, typename> typename // has bool 'value' eg std::is_same
#define CONTAINER template<typename...> typename // has n type args... eg std::tuple
```

## code example
```c++
// tuple manipulation
using sort_example = util::sort_t<std::tuple<val<3>, val<2>, val<1>>, util::cmp::lt_<>::type>; // std::tuple<val<1>, val<2>, val<3>> 
using filter_example = util::filter_t<std::tuple<int, float, char>, util::cmp::to_<float>::type>; // tuple<float>
using unique_example = util::unique_t<std::tuple<int, int, float, char>>; // tuple<int, float, char>
using find_example = util::find_t<std::tuple<const int, float>, util::cmp::to_<int, util::cmp::is_ignore_const_same>::type>; // const int
using set_intersect_example = util::set_intersect_t<std::tuple<int, float>, std::tuple<float, char>>; // tuple<float>
using set_union_example = util::set_union_t<std::tuple<int, float>, std::tuple<float, char>>; // tuple<int, float, char>
using concat_example = util::concat_t<std::tuple<std::tuple<int, int>, std::tuple<float>>>; // std::tuple<int, int, float>

// boring tuple manipulation that I've never ac used
using append_example = util::append_t<std::tuple<int, float>, int>; // tuple<int, float, int>
using prepend_example = util::prepend_t<std::tuple<int, float>, int>; // tuple<int, int, float>
using pop_front_example = util::pop_front_t<std::tuple<int, float>>; // tuple<float>;
using pop_back_example = util::pop_back_t<std::tuple<int, float>>; // tuple<int>;
using get_front_example = util::get_front_t<std::tuple<int, float>>; // int;
using get_back_example = util::get_back_t<std::tuple<int, float>>; // float;

// evaluation
using eval_example = util::eval_t<int, std::add_const, std::add_volatile>; // const volatile int;
using eval_each_example = util::eval_each_t<std::tuple<int, float, char>, std::add_const>; // tuple<const int, const float const char>
using eval_if_example = util::eval_if_t<const int, std::is_const, std::add_pointer, std::add_volatile>; // const int*
using eval_branch_example = util::eval_branch_t<int, std::add_const, std::add_pointer, std::add_cv>; // tuple<const int, int*, const volatile int>;
using post_eval_if_example = util::post_eval_if_t<const std::tuple<int>, util::unwrap, std::is_const, std::add_const>; // const int

// wrapping
using wrap_example = util::wrap_t<int, std::tuple>; // tuple<int>
using unwrap_example = util::unwrap_t<std::tuple<int>>; // int
template<typename ... Ts> struct example_tuple { };
using rewrap_example = util::rewrap_t<std::tuple<int, float, char>, example_tuple>; // example_tuple<int, float, char>;
```
## motivation
I apparently dont like coding in c++ and would instead prefer smashing my head against the nearest hard surface. 
