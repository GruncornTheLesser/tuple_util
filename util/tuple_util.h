#pragma once
#include <tuple>
#include <type_traits>
#define EVALUATE template<typename> typename // describes an attribute of a class. eg std::tuple_size
#define TRANSFORM template<typename> typename // has 'type' eg std::add_const
#define PREDICATE template<typename> typename // has bool 'value' eg std::is_const
#define COMPARE template<typename, typename> typename // has bool 'value' eg std::is_same
#define CONTAINER template<typename...> typename // has n type args... eg std::tuple

// TODO: naming convention for pred
// TODO: find a way to remove cmp:: for operations such as negate, disjunction, etc -> they conflict with pred operations of the same name
// TODO: descriptions
// TODO: organize into separate files
// Design: 
// transforms - a transform operation is a template class that with a template parameter and a template member type
// 		eg std::add_const, std::remove_const, std::type_identity
// pred - a pred operation is a template class with 1 template parameter and a static constexpr bool value
//		eg a std::is_const, std::is_reference
// compare - a compare operation is a template class with 2 template parameter and a static constexpr bool value
// 		eg std::is_same, lt_alpha